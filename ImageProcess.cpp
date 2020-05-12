//
// Created by User on 29.04.2020.
//

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "ImageProcess.h"

int ImageProcess::reverseInt(int i) {
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void ImageProcess::readImage(int NumberOfImages, int DataOfAnImage, std::vector<std::vector<float>> &arr, std::string filename) {
    arr.resize(NumberOfImages, std::vector<float>(DataOfAnImage));

    std::ifstream file(filename, std::ios::in|std::ios::binary);

    char* data;

    if (file.is_open()) {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;

        file.read((char *) &magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        file.read((char *) &number_of_images, sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);

        file.read((char *) &n_rows, sizeof(n_rows));
        n_rows = reverseInt(n_rows);

        file.read((char *) &n_cols, sizeof(n_cols));
        n_cols = reverseInt(n_cols);

        /*
        arr.reserve(number_of_images);
        for(int i = 0; i < number_of_images; i++) {
            arr[i].reserve(n_rows*n_cols);
        }
         */

        data = new char[number_of_images*n_cols*n_rows];
        file.read(data, number_of_images*n_cols*n_rows);

        for(int j = 0; j < number_of_images; j++) {
            for(int k = 0; k < n_rows; k++) {
                for(int l = 0; l < n_cols; l++) {
        //            std::cout << data[j*n_cols*n_rows + k*n_rows + l];
                    arr[j][k*n_cols + l] =  (float)data[j*n_cols*n_rows + k*n_cols + l];
                }
          //      std::cout << "\n";
            }
            //std::cout << "\n\n";
        }
        //std::cout << "";

/*
        for (int i = 0; i < number_of_images; ++i) {
            for (int r = 0; r < n_rows; ++r) {
                for (int c = 0; c < n_cols; ++c) {
                    unsigned char temp = 0;
                    file.read((char *) &temp, sizeof(temp));
                    arr[i][(n_cols * r) + c] = (float) temp;
                }
            }
        }
         */

        file.close();
        delete[](data);
    }
}

void ImageProcess::read_label(std::vector<int> &arr, std::string filename) {
   // arr.resize(NumberOfImages, std::vector<float>(DataOfAnImage));
    std::ifstream file(filename);

    if (file.is_open()) {
        int magic_number = 0;
        int number_of_labels = 0;

        file.read((char *) &magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        file.read((char *) &number_of_labels, sizeof(number_of_labels));
        number_of_labels = reverseInt(number_of_labels);

        arr.resize(number_of_labels, sizeof(int));

        for(int i = 0; i < number_of_labels; i++) {
            unsigned char temp = 0;
            file.read((char *) &temp, sizeof(temp));
            arr[i] = (int) temp;
        }
    }
    }

ImageProcess::~ImageProcess() {

}
