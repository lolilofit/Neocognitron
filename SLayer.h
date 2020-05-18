//
// Created by User on 29.04.2020.
//

#ifndef NEOCOGNITRON_SLAYER_H
#define NEOCOGNITRON_SLAYER_H


#include <vector>
#include "SCell.h"
#include "VCell.h"
#include "ColumnResult.h"


class SLayer {
private:
    std::vector<std::vector<std::vector<SCell*>>> s_cells;
    std::vector<std::vector<VCell*>> v_cells;

    float q;

    std::vector<float> b;

    std::vector<std::vector<std::vector<float>>> a;

    std::vector<std::vector<float>> c;
    std::vector<float> initial_c;

    int planes_number;
    int plane_size;
    int col_size;
    int w_size;

    float r;

    void init_weights(std::vector<float> &new_a);

    void add_new_plane(ColumnResult &prev_col_result, ColumnResult &columnResult);
public:
//    SLayer(NeocognithronConfiguration configuration, int layer_number);
    SLayer(int planes_number, float q, int plane_size, int w_size, int col_size, int planes_num_prev, std::vector<float> c, float r, std::vector<std::vector<std::vector<float>>> a);

    void init_layer(int planes_num_prev, int prev_area_size);

    ColumnResult calk_column_result(ColumnResult prev_col_result, std::vector<std::vector<float>> &v_cells_result);

    ColumnResult calk_with_train(ColumnResult prev_col_result);

    ColumnResult calkAndTrainAgain(ColumnResult &prev_col_result);

    ColumnResult calkResWithoutAdd(ColumnResult prev_col_result, std::vector<std::vector<float>> &v_cells_result);

    void get_res_per_plane(int plane_number, std::vector<Position*> &res, std::vector<Position*> &res_per_plane);
};


#endif //NEOCOGNITRON_SLAYER_H
