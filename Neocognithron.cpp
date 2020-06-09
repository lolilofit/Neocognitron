//
// Created by User on 29.04.2020.
//

#include <iostream>
#include "Neocognithron.h"


void Neocognithron::train_in_loop(int loops) {
                int train_example = 0;
                one_train_iteration(train_example);
   }


Neocognithron::Neocognithron(std::vector<std::vector<float>> &train_set,
                             std::vector<std::vector<float>> &test_set, std::vector<int> &train_labels,
                             std::vector<int> &test_labels) {

    this->train_labels = train_labels;
    this->test_labels = test_labels;
    this->train_set = train_set;
    this->test_set = test_set;

   // configuration.init_network();

    s_layers.resize(configuration.layers_num);
    c_layers.resize(configuration.layers_num);

    int prev_planes_num = 1;

    for(int i = 0; i < configuration.layers_num; i++) {
        s_layers[i] = new SLayer(configuration.get_planes_number(i, true),
                configuration.get_q(i),
                configuration.get_plane_size(i, true),
                configuration.get_w_size(i, true),
                configuration.get_column_size(i),
                prev_planes_num,
                configuration.get_c_weights(i),
                configuration.get_r(i),
                configuration.get_a(i)
                );

        std::vector<std::vector<float>> d_w = configuration.get_d_weights(i);
//        std::vector<float> cof_cor = configuration.get_coef_corr(configuration.get_planes_number(i, true), prev_planes_num);
        std::vector<float> cof_cor;

        c_layers[i] = new CLayer(configuration.get_planes_number(i, false),
                configuration.get_plane_size(i, false),
                configuration.get_w_size(i, false),
                d_w,
                cof_cor);
        prev_planes_num = configuration.get_planes_number(i, false);
    }
}

ColumnResult Neocognithron::one_train_iteration(int train_example) {
    std::vector<int> result_labels;

    ColumnResult prevResult = ColumnResult(28, 1);
    ColumnResult columnResult = ColumnResult(28, 1);

    std::vector<ColumnResult> s_res;
    int prev_layer_num = 1, prev_layer_size = 28;

    
    for (int train_layer = 0; train_layer < s_layers.size() - 1; train_layer++) {
        for (train_example = 0; train_example < test_set.size(); train_example++) {
            std::vector<std::vector<float>> example;
            example.resize(28);
            for (int i = 0; i < 28; i++) {
                example[i].resize(28);
                for (int j = 0; j < 28; j++)
                    example[i][j] = train_set[train_example][i * 28 + j];
            }

            prevResult = ColumnResult(28, 1);
            prevResult.set_plane(0, example);

            for (int i = 0; i <= train_layer; i++) {
                if (train_layer == i && train_example == 0)
                    s_layers[i]->init_layer(prev_layer_num, prev_layer_size);
                columnResult = s_layers[i]->calk_with_train(prevResult);

               if(i < train_layer) {
                   prevResult = c_layers[i]->calk_result(columnResult);
               }

               if(i == train_layer && train_example == test_set.size() - 1) {
                    c_layers[i]->init_c_layer(columnResult.get_planes_number(), columnResult.get_plane_size());
               }

               prev_layer_num = prevResult.get_planes_number();
               prev_layer_size = prevResult.get_plane_size();
            }
            std::cout << "Train layer " << train_layer << "; Train example  " << train_example << "; S-layers_number" << s_layers[train_layer]->get_planes_number() << "\n";
            if(train_layer == s_layers.size() - 2) {
                result_labels.push_back(train_labels[train_example]);
            }
        }
        std::cout << "\n\n---------NEW_LAYER------------\n\n";
    }


    //test_network(result_labels);
    test_network1(result_labels);
    return prevResult;
}

Neocognithron::Neocognithron() {
}

Neocognithron::~Neocognithron() {

}

void Neocognithron::test_network(std::vector<int> &result_labels) {
    std::cout<< "\n\nSTART TEST ON TRAIN SET\n\n" ;

    ColumnResult columnResult1 = ColumnResult(28, 1);
    std::vector<float> r;
    r.reserve(4);
    r[0] = 2;
    r[1] = 1;
    r[2] = 2;
    r[3] = 2;
    for(int i = 0; i < 4; i++) {
        s_layers[i]->set_r(r[i]);
    }

    int max_pos = -1;
    float max_val = 0.0;
    float val;
    int total_number = 0;
    int good = 0;
    int bad = 0;


    for(int train_example = 0; train_example < train_set.size(); train_example++) {
        std::vector<std::vector<float>> example;
        example.resize(28);
        for (int i = 0; i < 28; i++) {
            example[i].resize(28);
            for (int j = 0; j < 28; j++)
                example[i][j] = train_set[train_example][i * 28 + j];
        }

        ColumnResult prevResult1 = ColumnResult(28, 1);
        prevResult1.set_plane(0, example);

        for (int i = 0; i < s_layers.size() - 1; i++) {
            columnResult1 = s_layers[i]->calkAndTrainAgain(prevResult1);
            //std::cout << "S-layer result #" << i << "\n";
           // columnResult1.calkData();

            prevResult1 = c_layers[i]->calk_result(columnResult1);

            //std::cout << "C-layer result #" << i << "\n";
            //prevResult1.calkData();
        }

        for(int res = 0; res < prevResult1.get_planes_number(); res++) {
            val = prevResult1.get_val(res);
            if(val > max_val) {
                max_val = val;
                max_pos = res;
            }
        }
        if(max_pos == -1)
            std::cout << "oh, zero\n";
        else {
            //for (int j = 0; j < result_labels[max_pos].size(); j++) {
            //    std::cout << result_labels[max_pos][j] << " ";
           // }
           if(train_labels[train_example] == result_labels[max_pos])
               good++;
           else
               bad++;
            std::cout << "\nCompare " << train_labels[train_example] << " and " << result_labels[max_pos];
        }
        total_number++;
        max_val = -1.0;
        max_pos = -1;
    //    std::cout << "\nCompare " << test_labels[train_example] << " and " << result_labels[max_pos][0];
    }
    std::cout << "\n Total good examples = " << good << ";\nTotal bad = " << bad << "Total examples number = " << total_number;
}


void Neocognithron::test_network1(std::vector<int> &result_labels) {
    std::cout<< "\n\nSTART TEST\n\n" ;

    std::vector<int> true_positive;
    true_positive.resize(10);
    std::fill(true_positive.begin(), true_positive.begin()+10, 0);

    std::vector<int> true_negative;
    true_negative.resize(10);
    std::fill(true_negative.begin(), true_negative.begin()+10, 0);

    std::vector<int> false_positive;
    false_positive.resize(10);
    std::fill(false_positive.begin(), false_positive.begin()+10, 0);

    std::vector<int> false_negative;
    false_negative.resize(10);
    std::fill(false_negative.begin(), false_negative.begin()+10, 0);

    ColumnResult columnResult1 = ColumnResult(28, 1);
    std::vector<float> r;
    r.reserve(4);
    r[0] = 2;
    r[1] = 1;
    r[2] = 2;
    r[3] = 2;
    for(int i = 0; i < 4; i++) {
        s_layers[i]->set_r(r[i]);
    }

    int max_pos = -1;
    float max_val = 0.0;
    float val;
    int total_number = 0;
    int good = 0;
    int bad = 0;


    for(int train_example = 0; train_example < test_set.size(); train_example++) {
        std::vector<std::vector<float>> example;
        example.resize(28);
        for (int i = 0; i < 28; i++) {
            example[i].resize(28);
            for (int j = 0; j < 28; j++)
                example[i][j] = test_set[train_example][i * 28 + j];
        }

        ColumnResult prevResult1 = ColumnResult(28, 1);
        prevResult1.set_plane(0, example);

        for (int i = 0; i < s_layers.size() - 1; i++) {
            columnResult1 = s_layers[i]->calkAndTrainAgain(prevResult1);
            //std::cout << "S-layer result #" << i << "\n";
            // columnResult1.calkData();

            prevResult1 = c_layers[i]->calk_result(columnResult1);

            //std::cout << "C-layer result #" << i << "\n";
            //prevResult1.calkData();
        }

        for(int res = 0; res < prevResult1.get_planes_number(); res++) {
            val = prevResult1.get_val(res);
            if(val > max_val) {
                max_val = val;
                max_pos = res;
            }
        }
        if(max_pos == -1)
            std::cout << "oh, zero\n";
        else {
            //for (int j = 0; j < result_labels[max_pos].size(); j++) {
            //    std::cout << result_labels[max_pos][j] << " ";
            // }
            if(test_labels[train_example] == result_labels[max_pos]) {
                good++;
                true_positive[test_labels[train_example]]++;
                for(int p = 0; p < 10; p++)
                    if(p != test_labels[train_example])
                        true_negative[p]++;
            }
            else {
                bad++;
                false_negative[test_labels[train_example]]++;
                false_positive[result_labels[max_pos]]++;
                for(int p = 0 ; p < 10; p++)
                    if(p != test_labels[train_example] && p != result_labels[max_pos])
                        true_negative[test_labels[train_example]]++;
            }
            std::cout << "\nCompare " << test_labels[train_example] << " and " << result_labels[max_pos];
        }
        total_number++;
        max_val = -1.0;
        max_pos = -1;
        //    std::cout << "\nCompare " << test_labels[train_example] << " and " << result_labels[max_pos][0];
    }
    std::cout << "\n Total good examples = " << good << ";\nTotal bad = " << bad << "Total examples number = " << total_number;

    std::cout << "\nAcc percent" << (float)good/(float)total_number << "\n";

    std::cout << "Metrics for every class\n";
    for(int i = 0; i < 10; i ++) {
        std::cout << "Class "  << i <<"\nPrecision = " << (float)true_positive[i]/((float)true_positive[i] + (float)false_positive[i])
        << "; Recall = " << (float)true_positive[i]/((float)true_positive[i] + (float)false_negative[i])
        << "; F1= " << (2.0 * (float)true_positive[i])/(2.0 * (float)true_positive[i] + (float)false_positive[i] + (float)false_negative[i]) << "\n";

        std::cout << "Sp = " << ((float)true_negative[i])/((float)true_negative[i] + (float)false_positive[i]) << "; Se = " << ((float)true_positive[i])/((float)true_positive[i] + (float)false_positive[i]) << "\n";
    }
}
