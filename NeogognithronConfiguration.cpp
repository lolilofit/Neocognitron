//
// Created by User on 03.05.2020.
//

#include <iostream>
#include "NeogognithronConfiguration.h"
int NeocognithronConfiguration::get_planes_number(int layer_number, bool s_flag) {
    if(s_flag)
        return s_num_pl[layer_number];
    return c_num_pl[layer_number];
}

float NeocognithronConfiguration::get_q(int layer_number) {
    return q[layer_number];
}

int NeocognithronConfiguration::get_plane_size(int layer_number, bool s_flag) {
    if(s_flag)
        return s_layer_size[layer_number];
    return c_layer_size[layer_number];
}

int NeocognithronConfiguration::get_w_size(int layer_number, bool s_flag) {
    if(s_flag)
        return s_w_size[layer_number];
    return c_w_size[layer_number];
}

int NeocognithronConfiguration::get_column_size(int layer_number) {
    return s_col_size[layer_number];
}

NeocognithronConfiguration::NeocognithronConfiguration() {
    r.reserve(layers_num);
    q.reserve(layers_num);

    r[0] = 1.8;
    r[1] = 1.8;
    r[2] = 1.8;
    r[3] = 2.0;

    q[0] = 10;
    q[1] = 55;
    q[2] = 90;
    q[3] = 100;

    c.resize(layers_num);
    a.resize(layers_num);
}

std::vector<float> NeocognithronConfiguration::get_c_weights(int layer_number) {
    return c[layer_number];
}

float NeocognithronConfiguration::get_r(int player_number) {
    return r[player_number];
}

std::vector<std::vector<float>> NeocognithronConfiguration::get_d_weights(int layer_number) {
    return d;
}

std::vector<float> NeocognithronConfiguration::get_coef_corr(int planes_num, int prev_planes_num) {
    std::vector<float> cof;
    cof.resize(planes_num*prev_planes_num);

    for(int i = 0; i < prev_planes_num; i++) {
        for(int j = 0; j < planes_num; j++) {
            cof[i*planes_num + j] = 0.1f;
        }
    }
    return  cof;
}

std::vector<std::vector<std::vector<float>>> NeocognithronConfiguration::get_a(int layer_number) {
    return a[layer_number];
}

/*
void NeocognithronConfiguration::init_a() {
    a.resize(layers_num);

    int count = 0;
    count += init_lines();

    s_num_pl[0] = count;
}

int NeocognithronConfiguration::init_lines() {
    int count = 2;

    a[0].resize(2);
    a[0][0].resize(1);
    a[0][1].resize(1);

    std::vector<float> add;

    add.resize(25);

    for(int j = 0; j < 5; j++) {
        for (int i = 0; i < 5; i++) {
            if(i == 2)
                add[j*5 + i] = 1.0/5.0;
            else
                add[j*5 + i] = 0.0;
        }
    }

    a[0][0][0] =  add;

    std::vector<float> add1;
    add1.resize(25);

    for(int j = 0; j < 5; j++) {
        for (int i = 0; i < 5; i++) {
            if(j == 2)
                add1[j*5 + i] = 1.0/5.0;
            else
                add1[j*5 + i] = 0.0;
        }
    }


    a[0][1][0] = add1;
    return count;
}
*/
