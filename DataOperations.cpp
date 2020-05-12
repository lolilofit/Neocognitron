//
// Created by User on 29.04.2020.
//

#include <cmath>
#include <iostream>
#include "DataOperations.h"

float DataOperations::scalar_multiply(std::vector<float> &first, std::vector<float> &second) {
    if(first.size() != second.size())
        throw "arrays should have equals size";

    float res = 0.0;
    for(int i = 0; i < first.size(); i++) {
        res += first[i]*second[i];
    }
    return res;
}

int DataOperations::init_d(std::vector<std::vector<float>> &d, int layers_num, int w_size) {

//    std::vector<float> d_cof = {0.49, 0.87, 0.52, 0.45};
 //   std::vector<float> d_cof_add = {0.39, 0.68, 0.39, 0.68};

    d.resize(layers_num);

    for(int i = 0; i < layers_num; i++) {
        d[i] = decr_f(w_size);
        for(int j = 0; j < d[i].size(); j++) {
            d[i][j] = d[i][j] * 0.39;
        }
    }
}

std::vector<float> DataOperations::decr_f(int size) {
    std::vector<float> res;
    res.resize(size*size);
/*
    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            res[x*size + y] = 10000.0f*(1.0f/3.14)*(1.0f - (0.5)*(x*x + y*y))*(float)std::exp(-0.5 * (x*x + y*y));
            std::cout << res[x*size + y] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n-----------------\n\n";
    */

    res[1] = 1.0;

    float half_x = ((float)size - 1.0f)/2.0f;
    float half_y = half_x;
    float metric;
    float dx;
    float dy;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            dx = (float)i - half_x;
            dy = (float)j - half_y;
            metric = std::sqrt(dx*dx+dy*dy);
            res[i*size + j] = std::pow(2.0, metric);
        }
    }

    return res;
}


void DataOperations::decr_f_norm(std::vector<float> &f, int planes_number) {
    float sum = 0.0f;

    for(int i = 0; i < f.size(); i++)
        sum += f[i];

    for(int i = 0; i < f.size(); i++) {
        f[i] = f[i] / ((float)planes_number * sum);
    }
}