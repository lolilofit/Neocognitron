//
// Created by User on 29.04.2020.
//

#ifndef NEOCOGNITRON_IMAGEPROCESS_H
#define NEOCOGNITRON_IMAGEPROCESS_H


class ImageProcess {
private:
   // std::string test_labels_name = "mnist_data/t10k-labels.idx1-ubyte";
   // std::string test_images_name = "mnist_data/t10k-images.idx3-ubyte";
   // std::string train_labels_name = "mnist_data/train-labels.idx1-ubyte";
   // std::string train_images_name = "mnist_data/train-labels.idx1-ubyte";

    int reverseInt(int i);
public:
    ~ImageProcess();
    void readImage(int NumberOfImages, int DataOfAnImage, std::vector<std::vector<float>> &arr, std::string filename);
    void read_label(std::vector<int> &arr, std::string filename);
};


#endif //NEOCOGNITRON_IMAGEPROCESS_H
