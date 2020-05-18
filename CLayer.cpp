//
// Created by User on 29.04.2020.
//

#include <iostream>
#include "CLayer.h"
#include "Neocognithron.h"

ColumnResult CLayer::calk_result(ColumnResult previous_column_result) {

    ColumnResult columnResult(plane_size, planes_number);

    int prev_area_size = previous_column_result.get_plane_size();

    int x = 0, y = 0, cnt = 0;

    for(int i = 0; i < prev_area_size; i = i + w_size) {
        for(int j = 0; j < prev_area_size; j = j + w_size) {

            std::vector<std::vector<float>> planes_part;
            previous_column_result.get_planes_parts(i, j, w_size, planes_part);

            for(int plane = 0; plane < planes_number; plane++) {

                float cell_res = c_cells[plane][x][y]->calk_result(planes_part[plane], d[plane]);
                if(cell_res > 0.0)
                    std::cout << "";
                columnResult.add_result(plane, x, y, cell_res);
            }
            y++;
        }
        x++;
        y = 0;
    }

    return columnResult;
}
/*
CLayer::CLayer(NeocognithronConfiguration configuration, int layer_num) {
    this->w_size = configuration.get_w_size(layer_num);
    this->planes_number = configuration.get_planes_number(layer_num);
    this->plane_size = configuration.get_plane_size(layer_num);

    init_c_layer();
}
 */

CLayer::CLayer(int planes_number, int plane_size, int w_size, std::vector<std::vector<float>> &d_init, std::vector<float> &cof_corr) {
    this->planes_number = planes_number;
    this->plane_size = plane_size;
    this->w_size = w_size;

    //init_c_layer();

}




void CLayer::init_c_layer(int new_planes_num, int prev_plane_size) {
    planes_number = new_planes_num;

    plane_size = 0;
    for(int i = 0; i < prev_plane_size; i+=w_size)
        plane_size++;

    d.resize(planes_number);

    //for(int i = 0; i < planes_number; i++)
    DataOperations::init_d(this->d, planes_number, w_size);

    c_cells.resize(planes_number);

    for(int plane = 0; plane < planes_number; plane++) {
        c_cells[plane].resize(plane_size);
        for(int i = 0; i< plane_size; i++) {
            c_cells[plane][i].resize(plane_size);
            for(int j = 0; j < plane_size; j++)
                c_cells[plane][i][j] = new CCell();
        }
    }

}

void CLayer::push_label(int labl) {
    labels.push_back(labl);
}

