//
// Created by User on 29.04.2020.
//

#ifndef NEOCOGNITRON_NEOCOGNITHRON_H
#define NEOCOGNITRON_NEOCOGNITHRON_H


#include <vector>
#include <map>
#include "SLayer.h"
#include "CLayer.h"
#include "NeogognithronConfiguration.h"

class Clayer;


class Neocognithron {
private:

    std::vector<std::vector<float>> train_set;
    std::vector<int> train_labels;
    std::vector<std::vector<float>> test_set;
    std::vector<int> test_labels;

    std::vector<SLayer*> s_layers;
    std::vector<CLayer*> c_layers;


    NeocognithronConfiguration configuration;
public:
    Neocognithron();
    ~Neocognithron();

    //Neocognithron(std::vector<std::vector<std::vector<int>>> &train_set, std::vector<std::vector<std::vector<int>> &test_set);
    Neocognithron(std::vector<std::vector<float>> &train_set,
            std::vector<std::vector<float>> &test_set,
            std::vector<int> &train_labels,
            std::vector<int> &test_labels);

    ColumnResult one_train_iteration(int train_example);
    void train_in_loop(int loops);

    void train_again(int last_layers_num);

    void test_network(std::vector<int> &result_labels);
    void test_network1(std::vector<int> &result_labels);
};


#endif //NEOCOGNITRON_NEOCOGNITHRON_H
