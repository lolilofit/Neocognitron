//
// Created by User on 29.04.2020.
//

#ifndef NEOCOGNITRON_CCELL_H
#define NEOCOGNITRON_CCELL_H

#include <vector>

class CCell {
    //std::vector<float> cof_corr;
public:
    CCell();
    //float calk_result(std::vector<std::vector<float>> &planes_part, std::vector<std::vector<float>> &d);
    float calk_result(std::vector<float> &planes_part, std::vector<float> &d);
};


#endif //NEOCOGNITRON_CCELL_H
