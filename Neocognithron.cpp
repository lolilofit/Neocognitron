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

    ColumnResult prevResult = ColumnResult(28, 1);
    ColumnResult columnResult = ColumnResult(28, 1);

    std::vector<ColumnResult> s_res;
    int prev_layer_num = 1, prev_layer_size = 28;

    
    for (int train_layer = 0; train_layer < s_layers.size() - 1; train_layer++) {
        for (train_example = 0; train_example < train_set.size(); train_example++) {
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

               if(i == train_layer && train_example == (train_set.size() - 1)) {
                    c_layers[i]->init_c_layer(columnResult.get_planes_number(), columnResult.get_plane_size());
               }

               prev_layer_num = prevResult.get_planes_number();
               prev_layer_size = prevResult.get_plane_size();

            }
        }
        std::cout << "\n\n---------NEW_LAYER------------\n\n";
    }

    train_again(prev_layer_num);
    return prevResult;
}

Neocognithron::Neocognithron() {
}

Neocognithron::~Neocognithron() {

}

void Neocognithron::train_again(int last_layers_num) {
    /*
    ColumnResult prevResult = ColumnResult(28, 1);
    ColumnResult columnResult = ColumnResult(28, 1);

    for (int train_example = 0; train_example < 2; train_example++) {
        std::vector<std::vector<float>> example;
        example.resize(28);
        for (int i = 0; i < 28; i++) {
            example[i].resize(28);
            for (int j = 0; j < 28; j++)
                example[i][j] = test_set[train_example][i * 28 + j];
        }

        prevResult = ColumnResult(28, 1);
        prevResult.set_plane(0, example);

        columnResult = s_layers[0]->calkAndTrainAgain(prevResult);

    }

    c_layers[0]->init_c_layer(columnResult.get_planes_number(), columnResult.get_plane_size());
    prevResult = c_layers[0]->calk_result(columnResult);

    //for(int loop = 0; loop < 4; loop++) {
    for (int i = 1; i < s_layers.size(); i++) {
        columnResult = s_layers[i]->calkAndTrainAgain(prevResult);
        prevResult = c_layers[i]->calk_result(columnResult);
    }
    */

    std::vector<std::vector<int>> result_labels;
    result_labels.resize(last_layers_num);

    ColumnResult columnResult1 = ColumnResult(28, 1);
    int max_pos = -1;
    float max_val = 0.0;
    float val;

    //int train_example = 1;
    for (int train_example = 0; train_example < 4; train_example++) {
        std::vector<std::vector<float>> example;
        example.resize(28);
        for (int i = 0; i < 28; i++) {
            example[i].resize(28);
            for (int j = 0; j < 28; j++)
                example[i][j] = train_set[train_example][i * 28 + j];
        }

        ColumnResult prevResult1 = ColumnResult(28, 1);
        prevResult1.set_plane(0, example);

        //int i =0;
        for (int i = 0; i < s_layers.size() - 1; i++) {

            columnResult1 = s_layers[i]->calkAndTrainAgain(prevResult1);
        //    if(train_labels[train_example] == 1) {
       //         std::cout << "S-layer result #" << i << "\n";
        //        columnResult1.calkData();
        //    }

            prevResult1 = c_layers[i]->calk_result(columnResult1);
         //   if(train_labels[train_example] == 1) {
        //        std::cout << "C-layer result #" << i << "\n";
        //        prevResult1.calkData();
         //   }
        }

        //prevResult1.calkData();
        // std::cout << "Label " << train_example << "\n";

        for(int res = 0; res < prevResult1.get_planes_number(); res++) {
            val = prevResult1.get_val(res);
            if(val > max_val) {
                max_val = val;
                max_pos = res;
            }
        }

        //std::cout << "\n" << max_pos << "\n";
        if(max_pos == -1)
            std::cout << "ZERO RESULT" << "\n";
        else
            result_labels[max_pos].push_back(train_labels[train_example]);
        max_pos = -1;
        max_val = 0.0;
    }


    for(int i = 0; i < result_labels.size(); i++) {
        for(int j = 0; j < result_labels[i].size(); j++) {
            std::cout << result_labels[i][j] << " ";
        }
        std::cout << "\n";
    }

    test_network(result_labels);
}

void Neocognithron::test_network(std::vector<std::vector<int>> &result_labels) {
    ColumnResult columnResult1 = ColumnResult(28, 1);

    int max_pos = -1;
    float max_val = 0.0;
    float val;
    int total_number = 0;
    int good = 0;
    int bad = 0;


    for(int train_example = 0; train_example < 10; train_example++) {
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
            std::cout << "S-layer result #" << i << "\n";
           // columnResult1.calkData();

            prevResult1 = c_layers[i]->calk_result(columnResult1);

            std::cout << "C-layer result #" << i << "\n";
            prevResult1.calkData();
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
           if(test_labels[train_example] == result_labels[max_pos][0])
               good++;
           else
               bad++;
            std::cout << "\nCompare " << test_labels[train_example] << " and " << result_labels[max_pos][0];
        }
        total_number++;
        max_val = -1.0;
        max_pos = -1;
    //    std::cout << "\nCompare " << test_labels[train_example] << " and " << result_labels[max_pos][0];
    }
    std::cout << "\n Total good examples = " << good << ";\nTotal bad = " << bad << "Total examples number = " << total_number;
}
