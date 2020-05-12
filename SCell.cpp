//
// Created by User on 29.04.2020.
//

#include "SCell.h"

SCell::SCell(float layer_r, float b) {
    this->r = layer_r;
  //  this->b = b;
}

float SCell::calkOutput(std::vector<std::vector<float>> &input, std::vector<std::vector<float>> &a, float v_ing, float b_coef) {
    float s = 0.0;

    for(int plane = 0; plane < input.size(); plane++)
        s += DataOperations::scalar_multiply(input[plane], a[plane]);

    float ing = 1.0f + r/(1.0f+r)*b_coef*v_ing;
    float res = (1 + s)/ing - 1;

    if(res <= 0.0)
        return 0.0;
    return  r*res;
}
