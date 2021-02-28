//
// Created by User on 29.04.2020.
//

#include "CCell.h"
#include "DataOperations.h"


CCell::CCell() {
}

float CCell::calk_result(std::vector<float> &planes_part, std::vector<float> &d) {
    float res = 0.0f;

    res += DataOperations::scalar_multiply(planes_part, d);

    if(res <= 0.0)
        return 0.0;
    return res/(1 + res);
}
