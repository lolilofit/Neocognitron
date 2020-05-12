//
// Created by User on 29.04.2020.
//

#ifndef NEOCOGNITRON_SCELL_H
#define NEOCOGNITRON_SCELL_H


#include <vector>
#include "DataOperations.h"

class SCell {
private:
    float r;
   // float b;
public:
    SCell(float layer_r, float b);
    float calkOutput(std::vector<std::vector<float>> &input, std::vector<std::vector<float>> &a, float v_ing, float b_coef);
};


#endif //NEOCOGNITRON_SCELL_H
