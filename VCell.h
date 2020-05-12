//
// Created by User on 29.04.2020.
//

#ifndef NEOCOGNITRON_VCELL_H
#define NEOCOGNITRON_VCELL_H


#include <vector>
#include<math.h>

class VCell {
private:
    //std::vector<float> c;

public:
    explicit VCell(std::vector<float> &initialWeights);

    float calkOutput(std::vector<std::vector<float>> &input, std::vector<std::vector<float>> &c);
};


#endif //NEOCOGNITRON_VCELL_H
