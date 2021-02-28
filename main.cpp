#include <iostream>
#include <vector>
#include "ImageProcess.h"
#include "Neocognithron.h"


int main() {

    ImageProcess imageProcess;


    std::vector<std::vector<float>> ar;
    imageProcess.readImage(10000, 784, ar, "C:\\Users\\darya\\CLionProjects\\neocognithron\\mnist_data\\t10k-images.idx3-ubyte");


    std::vector<int> labels;
    imageProcess.read_label(labels, "C:\\Users\\darya\\CLionProjects\\neocognithron\\mnist_data\\t10k-labels.idx1-ubyte");


    std::cout << labels[101] << "\n";

    for(int k = 0; k < 10000; k++) {
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                if(ar[k][i* 28 + j] != 0)
                    ar[k][i*28 + j] = 1;
            }
        }
    }

    std::vector<std::vector<float>> train_set;
    imageProcess.readImage(60000, 784, train_set, "C:\\Users\\darya\\CLionProjects\\neocognithron\\mnist_data\\train-images.idx3-ubyte");

    for(int k = 0; k < 10000; k++) {
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                if(train_set[k][i* 28 + j] != 0)
                    train_set[k][i*28 + j] = 1;
            }
        }
    }

    std::vector<int> train_labels;
    imageProcess.read_label(train_labels, "C:\\Users\\darya\\CLionProjects\\neocognithron\\mnist_data\\train-labels.idx1-ubyte");

    Neocognithron* neocognithron = new Neocognithron(train_set, ar, train_labels, labels);

    neocognithron->train_in_loop(12);

    delete neocognithron;

    return 0;
}
