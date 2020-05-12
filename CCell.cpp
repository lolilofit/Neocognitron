//
// Created by User on 29.04.2020.
//

#include "CCell.h"
#include "DataOperations.h"


//std::vector<float> &cof_corr
CCell::CCell() {
  //  this->cof_corr = cof_corr;
}

//float CCell::calk_result(std::vector<std::vector<float>> &planes_part, std::vector<std::vector<float>> &d) {
float CCell::calk_result(std::vector<float> &planes_part, std::vector<float> &d) {
    float res = 0.0f;

    /*
    for(int plane = 0; plane < planes_part.size(); plane++) {
        res += DataOperations::scalar_multiply(planes_part[plane], d[plane]);
       // res *= cof_corr[plane];
    }
     */
    res += DataOperations::scalar_multiply(planes_part, d);

    if(res <= 0.0)
        return 0.0;
    return res/(1 + res);
}
