//
// Created by Linki on 10/10/2023.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utility.h"

cv::Mat LoadImage(const std::string& filename, int flags){
    cv::Mat image = cv::imread(filename, flags);
    if(image.empty()) {
        std::cerr << "Error: Unable to load image from file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    return image;
}

cv::Mat Erosion(cv::Mat bin) {
    int mask[3][3] = {
            {0,   255, 0},
            {255, 255, 255},
            {0,   255, 0}
    };

    cv::Mat g(bin.rows, bin.cols, CV_8U, cv::Scalar(0, 0, 0));

    for (int row = 1; row < bin.rows - 1; row++) {
        for (int col = 1; col < bin.cols - 1; col++) {
            int cont = 0;
            for (int l = -1; l <= 1; l++) {
                for (int k = -1; k <= 1; k++) {
                    if (bin.at<uchar>(row + l, col + k) == 255 & mask[1 + l][1 + k] == 255) {
                        cont++;
                    }
                }
            }
            if (cont == 5) {
                g.at<uchar>(row, col) = 255;
            }
        }
    }
    namedWindow("Ori", cv::WINDOW_NORMAL);
    imshow("Ori", bin);

    namedWindow("Eroded2", cv::WINDOW_NORMAL);
    imshow("Eroded2", g);
    imwrite("Eroded2.jpg", g);
    cv::waitKey(0);

    return Opening(g);
}

cv::Mat Opening(cv::Mat&Ero){
    int mask[3][3] = {
            {0, 255, 0},
            {255, 255, 255},
            {0, 255, 0}
    };

    cv::Mat g(Ero.rows, Ero.cols, CV_8U, cv::Scalar(0, 0, 0));

    for (int row = 1; row < Ero.rows - 1; row++) {
        for (int col = 1; col < Ero.cols - 1; col++) {
            bool pix = false;
            for (int l = -1; l <= 1; l++) {
                for (int k = -1; k <= 1; k++) {
                    if(Ero.at<uchar>(row + l, col + k) == 255 & mask[1 + l][1 + k] == 255){
                        pix = true;
                    }
                }
            }
            if (pix) {
                g.at<uchar>(row, col) = 255;
            }
        }
    }

    namedWindow("Opened", cv::WINDOW_NORMAL);
    imshow("Opened", g);
    imwrite("Opened.jpg", g);
    cv::waitKey(0);

    return g;
}
