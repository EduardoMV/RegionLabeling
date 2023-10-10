//
// Created by Linki on 05/10/2023.
//
#include <cmath>
#include <iostream>
#include <queue>
#include <opencv2/opencv.hpp>

struct Coordinate {
    int x;
    int y;
};

const int thresholdValue = 125;

cv::Mat applyBinaryThreshold(const cv::Mat& inputImage, int thresholdValue) {
    cv::Mat resultImage(inputImage.rows, inputImage.cols, CV_8U, cv::Scalar(0));

    for (int y = 0; y < inputImage.rows; y++) {
        for (int x = 0; x < inputImage.cols; x++) {
            int pixelValue = inputImage.at<uchar>(y, x);
            resultImage.at<uchar>(y, x) = (pixelValue > thresholdValue) ? 255 : 0;
        }
    }

    return resultImage;
}

void performRegionGrowing(const cv::Mat& inputImage) {
    cv::Mat outputImage = cv::Mat::zeros(inputImage.size(), CV_8UC1);

    if (inputImage.empty()) {
        std::cerr << "Error al cargar la imagen" << std::endl;
        return;
    }

    int inputImageRows = inputImage.rows;
    int inputImageCols = inputImage.cols;
    int currentGrayscaleLevel = 40;

    std::queue<Coordinate> whitePixelQueue;

    for (int y = 0; y < inputImageRows; y++) {
        for (int x = 0; x < inputImageCols; x++) {
            if (inputImage.at<uchar>(y, x) == 255 && outputImage.at<uchar>(y, x) == 0) {
                Coordinate seedCoord = { x, y };
                whitePixelQueue.push(seedCoord);

                while (!whitePixelQueue.empty()) {
                    Coordinate currentCoord = whitePixelQueue.front();
                    whitePixelQueue.pop();

                    int x = currentCoord.x;
                    int y = currentCoord.y;

                    if (outputImage.at<uchar>(y, x) == 0 && inputImage.at<uchar>(y, x) == 255) {
                        outputImage.at<uchar>(y, x) = currentGrayscaleLevel;

                        if (x > 0) {
                            Coordinate leftCoord = { x - 1, y };
                            whitePixelQueue.push(leftCoord);
                        }
                        if (x < inputImageCols - 1) {
                            Coordinate rightCoord = { x + 1, y };
                            whitePixelQueue.push(rightCoord);
                        }
                        if (y > 0) {
                            Coordinate upCoord = { x, y - 1 };
                            whitePixelQueue.push(upCoord);
                        }
                        if (y < inputImageRows - 1) {
                            Coordinate downCoord = { x, y + 1 };
                            whitePixelQueue.push(downCoord);
                        }
                    }
                }

                currentGrayscaleLevel += 5;
            }
        }
    }
    cv::imshow("Region Grown Image", outputImage);
    cv::waitKey(0);
}

int main() {
    try {
        cv::Mat inputImage = cv::imread("img.png", cv::IMREAD_GRAYSCALE);
        cv::Mat binaryImage = applyBinaryThreshold(inputImage, thresholdValue);
        cv::imshow("Binary Image", binaryImage);
        performRegionGrowing(binaryImage);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
