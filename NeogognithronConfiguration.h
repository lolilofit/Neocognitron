//
// Created by User on 03.05.2020.
//

#ifndef NEOCOGNITRON_NEOGOGNITHRONCONFIGURATION_H
#define NEOCOGNITRON_NEOGOGNITHRONCONFIGURATION_H

#include "SLayer.h"
#include "CLayer.h"

class NeocognithronConfiguration {
private:

    //int planes_num = 6;
    std::vector<int> s_num_pl =  {0, 0, 0, 0};
    std::vector<int> c_num_pl =  {16, 16, 16, 16};

    std::vector<int> s_layer_size = {0, 0, 0, 0};
    std::vector<int> c_layer_size = {0, 0, 0, 0};
    std::vector<int> s_w_size = {5, 5, 5, 5};
    std::vector<int> c_w_size = {3, 3, 5, 11};
    std::vector<int> s_col_size = {5, 5, 5, 28};

    std::vector<float> r;
    std::vector<float> q;

    std::vector<std::vector<float>> d;
    std::vector<std::vector<float>> c;

    std::vector<std::vector<std::vector<std::vector<float>>>> a;

    std::vector<std::vector<float>> coef_cor;

    int init_lines();
    void init_a();
public:
    int layers_num = 4;

    NeocognithronConfiguration();

    int get_planes_number(int layer_number, bool s_flag);
    float get_q(int layer_number);
    int get_plane_size(int layer_number, bool s_flag);
    int get_w_size(int layer_number, bool s_flag);
    std::vector<float> get_c_weights(int layer_number);
    float get_r(int player_number);
    std::vector<std::vector<float>> get_d_weights(int layer_number);
    std::vector<float> get_coef_corr(int planes_num, int prev_planes_num);

    std::vector<float> decr_f(float cof, int size);
    void decr_f_norm(std::vector<float> &f, int planes_number);

    //init in layers!!1
    int get_column_size(int layer_number);

    std::vector<std::vector<std::vector<float>>> get_a(int layer_number);

};



#endif //NEOCOGNITRON_NEOGOGNITHRONCONFIGURATION_H
