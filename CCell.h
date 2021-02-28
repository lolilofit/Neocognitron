//
// Created by User on 29.04.2020.
//

#ifndef NEOCOGNITRON_CCELL_H
#define NEOCOGNITRON_CCELL_H

#include <vector>

class CCell {
public:
    CCell();
    float calk_result(std::vector<float> &planes_part, std::vector<float> &d);
};


#endif //NEOCOGNITRON_CCELL_H
