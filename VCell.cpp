//
// Created by User on 29.04.2020.
//

#include <iostream>
#include "VCell.h"

float VCell::calkOutput(std::vector<std::vector<float>> &input, std::vector<std::vector<float>> &c) {
    float res = 0.0;

    for(int plane = 0; plane < input.size(); plane++) {
        std::vector<float> onePlane = input[plane];
        for(int cell = 0; cell < onePlane.size(); cell++) {
            res += (float) std::pow(onePlane[cell], 2) * c[plane][cell];
        }
    }

    if(res < 0)
        std::cout << "";

    return std::sqrt(res);
}

VCell::VCell(std::vector<float> &initialWeights) {
   // this->c = initialWeights;
}
