//
// Created by User on 29.04.2020.
//

#ifndef NEOCOGNITRON_DATAOPERATIONS_H
#define NEOCOGNITRON_DATAOPERATIONS_H


#include <vector>

class DataOperations {
public:
    static float scalar_multiply(std::vector<float> &first, std::vector<float> &second);
    static int init_d(std::vector<std::vector<float>> &d, int layers_num, int w_size);
    static std::vector<float> decr_f(int size);
    static void decr_f_norm(std::vector<float> &f, int planes_number);
};


#endif //NEOCOGNITRON_DATAOPERATIONS_H
