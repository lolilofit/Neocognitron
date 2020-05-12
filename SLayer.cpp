//
// Created by User on 29.04.2020.
//

#include <cstdlib>
#include <iostream>
#include <utility>
#include "SLayer.h"


ColumnResult SLayer::calkAndTrainAgain(ColumnResult prev_col_result, bool train) {
    std::vector<std::vector<float>> v_cells_result;
    v_cells_result.resize(plane_size);
    for(int i = 0; i < plane_size; i++)
        v_cells_result[i].resize(plane_size);

    ColumnResult columnResult = calkResWithoutAdd(prev_col_result, v_cells_result);

    if(train) {
        float dlt = 0.0;
        std::vector<Position *> positions = columnResult.get_cell_to_update(col_size);

        for (int plane = 0; plane < planes_number; plane++) {
            //std::pair<int, int>* max_cell = columnResult.get_cell_to_update(plane, col_size);
            Position *max_cell = positions[plane];

            if (max_cell != nullptr) {
                dlt = q * v_cells_result[max_cell->x][max_cell->y];
                b[plane] += dlt;

                for (int inp_plane = 0; inp_plane < a[plane].size(); inp_plane++) {
                    std::vector<float> inp_plane_part = prev_col_result.get_plane_part(inp_plane, max_cell->x,
                                                                                       max_cell->y, w_size);

                    for (int i = 0; i < w_size * w_size; i++) {
                        dlt = q * c[inp_plane][i] * inp_plane_part[i];
                        a[plane][inp_plane][i] += dlt;
                    }
                }
            }
        }

        ColumnResult new_columnResult = calkResWithoutAdd(prev_col_result, v_cells_result);
        return new_columnResult;
    }
    return columnResult;
}


ColumnResult SLayer::calkResWithoutAdd(ColumnResult prev_col_result, std::vector<std::vector<float>> &v_cells_result) {
    float s_cell_res = 0.0;
    ColumnResult columnResult(plane_size, planes_number);

    for (int i = 0; i < plane_size; i++) {
        for (int j = 0; j < plane_size; j++) {

            std::vector<std::vector<float>> plane_part;
            prev_col_result.get_planes_parts(i, j, w_size, plane_part);

            v_cells_result[i][j] = v_cells[i][j]->calkOutput(plane_part, c);

            for (int plane = 0; plane < planes_number; plane++) {

                s_cell_res = s_cells[plane][i][j]->calkOutput(plane_part, a[plane], v_cells_result[i][j], b[plane]);
                columnResult.add_result(plane, i, j, s_cell_res);
            }
        }
    }
    return columnResult;
}


ColumnResult SLayer::calk_with_train(ColumnResult prev_col_result) {

    std::vector<std::vector<float>> v_cells_result;
    v_cells_result.resize(plane_size);
    for(int i = 0; i < plane_size; i++)
        v_cells_result[i].resize(plane_size);


    //for(int loop = 0; loop < 10; loop++) {

        ColumnResult columnResult = calk_column_result(prev_col_result, v_cells_result);

//        columnResult.calkData();

/*
  //  for(int loop = 0; loop < 10; loop++) {
        float dlt = 0.0;
        std::vector<Position *> positions = columnResult.get_cell_to_update(col_size);

        for(int plane = 0; plane < planes_number; plane++) {
            //std::pair<int, int>* max_cell = columnResult.get_cell_to_update(plane, col_size);
            Position* max_cell = positions[plane];

            if(max_cell != nullptr) {
                dlt = q * v_cells_result[max_cell->x][max_cell->y];
                b[plane] += dlt;

                for(int inp_plane = 0; inp_plane < a[plane].size(); inp_plane++) {
                    std::vector<float> inp_plane_part  = prev_col_result.get_plane_part(inp_plane, max_cell->x, max_cell->y, w_size);

                    for(int i = 0; i < w_size*w_size; i++) {
                        dlt = q * c[inp_plane][i] * inp_plane_part[i];
                        a[plane][inp_plane][i] += dlt;
                    }
                }
            }
        }

        ColumnResult new_columnResult = calk_column_result(prev_col_result, v_cells_result);
*/
/*
        for(int plane = 0; plane < a.size(); plane++) {
            for (int pr_pl = 0; pr_pl < a[plane].size(); pr_pl++) {
                for (int i1 = 0; i1 < w_size; i1++) {
                    for (int j1 = 0; j1 < w_size; j1++) {
                        if(a[plane][pr_pl][i1 * w_size + j1] > 0.0)
                            std::cout << 1;
                        else
                            std::cout << 0;
                        //std::cout << a[plane][pr_pl][i1 * w_size + j1];
                    }
                    std::cout << "\n";
                }
                std::cout << "\n\n";
            }
            std::cout << "\n\n";
        }
*/
        std::cout << "=======================\n";

//        new_columnResult.calkData();
 //   }

    //return new_columnResult;

    //columnResult.calkData();
    //columnResult.summ_data();
    return columnResult;
}

ColumnResult SLayer::calk_column_result(ColumnResult prev_col_result, std::vector<std::vector<float>> &v_cells_result) {

    bool non_null_out = false;
    float s_cell_res = 0.0;
    ColumnResult columnResult(plane_size, planes_number);

    //if(planes_number > 0) {
        for (int i = 0; i < plane_size; i++) {
            for (int j = 0; j < plane_size; j++) {

                if(i == 11 && j == 19)
                    std::cout << "";

                std::vector<std::vector<float>> plane_part;
                prev_col_result.get_planes_parts(i, j, w_size, plane_part);

                v_cells_result[i][j] = v_cells[i][j]->calkOutput(plane_part, c);

                for (int plane = 0; plane < planes_number; plane++) {

                    s_cell_res = s_cells[plane][i][j]->calkOutput(plane_part, a[plane], v_cells_result[i][j], b[plane]);
                    if (s_cell_res > 0)
                        non_null_out = true;

                    columnResult.add_result(plane, i, j, s_cell_res);
                }

                if(!non_null_out && v_cells_result[i][j] > 0) {
                    add_new_plane(prev_col_result, columnResult);

                    b[planes_number - 1] = q*v_cells_result[i][j];

                    for(int prev_plane = 0; prev_plane < plane_part.size(); prev_plane++) {
                        for(int shift = 0; shift < w_size*w_size; shift++) {
                            float val = c[prev_plane][shift] * plane_part[prev_plane][shift] * q;
                            if(val > 0.0)
                                a[planes_number - 1][prev_plane][shift] += val;
                            else
                                a[planes_number - 1][prev_plane][shift] = 0.0;
                        }
                    }
    /*
                    for(int pr_pl = 0; pr_pl < plane_part.size(); pr_pl++) {
                        for (int i1 = 0; i1 < w_size; i1++) {
                            for (int j1 = 0; j1 < w_size; j1++) {
                                if(a[planes_number - 1][pr_pl][i1 * w_size + j1] > 0.0)
                                    std::cout << 1;
                                else
                                    std::cout << 0;
                                //std::cout << a[planes_number - 1][pr_pl][i1 * w_size + j1];
                            }
                            std::cout << "\n";
                        }
                        std::cout << "\n\n";
                    }
                    */
             //   std::cout<< "**************\n";

                    s_cell_res = s_cells[planes_number - 1][i][j]->calkOutput(plane_part, a[planes_number - 1], v_cells_result[i][j], b[planes_number - 1]);
                    columnResult.add_result(planes_number - 1, i, j, s_cell_res);

                }
                non_null_out = false;
            }
        }
    //}
/*
    if(!non_null_out) {

        std::vector<float> new_plane_a;
        init_weights(new_plane_a);

        for(int i = 0; i < prev_col_result.get_planes_number(); i++) {
            a[i].push_back(new_plane_a);
        }

        columnResult.add_new_plane();

        planes_number++;
        s_cells.resize(planes_number);
        s_cells[planes_number - 1].resize(plane_size);

        for(int i = 0; i < plane_size; i++) {
            s_cells[planes_number - 1][i].resize(plane_size);
            for (int j = 0; j < plane_size; j++) {
                s_cells[planes_number - 1][i][j] = new SCell(r, 0.0);
            }
        }

        b.resize(planes_number);
        b[planes_number - 1]= 0.0;

        //v_cells.resize(planes_number);
        //add c_cell add c weights

        for(int i = 0; i < plane_size; i++) {
            for (int j = 0; j < plane_size; j++) {
                if(i == 11 && j == 19)
                    std::cout << "";

                std::vector<std::vector<float>> plane_part;
                prev_col_result.get_planes_parts(i, j, w_size, plane_part);

                v_cells_result[i][j] = v_cells[i][j]->calkOutput(plane_part, c);

                s_cell_res = s_cells[planes_number - 1][i][j]->calkOutput(plane_part,
                                a[planes_number - 1],
                                v_cells_result[i][j],
                                b[planes_number -1]);

                columnResult.add_result(planes_number - 1, i, j, s_cell_res);
            }
        }
    }
    */
    return columnResult;
}


void SLayer::init_weights(std::vector<float> &new_a) {
    new_a.resize(w_size*w_size);

    for(int k = 0; k < w_size*w_size; k++) {
        float generated_value = (((float)std::rand())/(RAND_MAX) * (0.4f)) * 0.000001f;
        new_a[k] = generated_value;
    }
}

/*
SLayer::SLayer(NeocognithronConfiguration configuration, int layer_number) {
    q = configuration.get_q(layer_number);
    planes_number = configuration.get_planes_number(layer_number);
    plane_size = configuration.get_plane_size(layer_number);
    w_size = configuration.get_w_size(layer_number);

    init_layer();
}
*/

SLayer::SLayer(int planes_number, float q,
        int plane_size,
        int w_size,
        int col_size,
        int planes_num_prev,
               std::vector<float> c,
        float r,
               std::vector<std::vector<std::vector<float>>> a) {
    this->q = q;
    this-> planes_number = planes_number;
    this->plane_size = plane_size;
    this->w_size = w_size;
    this->col_size = col_size;

    this->r = r;

    //this->initial_c = c;

}

void SLayer::init_layer(int planes_num_prev, int prev_area_size) {
    plane_size = prev_area_size;

    this->c.resize(planes_num_prev);
    std::vector<float> f = DataOperations::decr_f(w_size);
    DataOperations::decr_f_norm(f, 1);
    c[0] = f;

    for(int i = 1; i < planes_num_prev; i++) {
        f = DataOperations::decr_f(w_size);
        DataOperations::decr_f_norm(f, planes_num_prev);
        c[i] = f;
    }


    //set prev_planes_number in runtime
    //this->a = a;
    (this->a).resize(planes_num_prev);
    for(int i = 0; i < planes_num_prev; i++) {
        std::vector<std::vector<float>> filler;
        (this->a)[i] = filler;
    }

    b.resize(plane_size*plane_size);
    for(int i = 0; i < plane_size*plane_size; i++) {
        b[i] = 0;
    }

    v_cells.resize(plane_size);
    s_cells.resize(planes_number);

    for(int i = 0; i < planes_number; i++) {
        s_cells[i].resize(plane_size);
        for(int j = 0; j < plane_size; j++)
            s_cells[i][j].resize(plane_size);
    }

    for(int i = 0; i < plane_size; i++) {
        v_cells[i].resize(plane_size);

        for(int j = 0; j < plane_size; j++) {
            v_cells[i][j] = new VCell(c[j]);
            for(int plane = 0; plane < planes_number; plane++) {
                s_cells[plane][i][j] = new SCell(r, 0);
            }
        }
    }
}

void SLayer::add_new_plane(ColumnResult &prev_col_result, ColumnResult &columnResult) {
    std::vector<float> new_plane_a;
    init_weights(new_plane_a);

    planes_number++;

    a.resize(planes_number);

    for(int i = 0; i < prev_col_result.get_planes_number(); i++) {
        a[planes_number - 1].push_back(new_plane_a);
    }

    columnResult.add_new_plane();

    s_cells.resize(planes_number);
    s_cells[planes_number - 1].resize(plane_size);

    for(int i = 0; i < plane_size; i++) {
        s_cells[planes_number - 1][i].resize(plane_size);
        for (int j = 0; j < plane_size; j++) {
            s_cells[planes_number - 1][i][j] = new SCell(r, 0.0);
        }
    }

    b.resize(planes_number);
    b[planes_number - 1]= 0.0;

}


