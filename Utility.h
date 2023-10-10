//
// Created by Linki on 10/10/2023.
//

#ifndef CLASSWORK_051023_UTILITY_H
#define CLASSWORK_051023_UTILITY_H

cv::Mat LoadImage(const std::string& filename, int flags);
cv::Mat Erosion(cv::Mat bin);
cv::Mat Opening(cv::Mat&Ero);

#endif //CLASSWORK_051023_UTILITY_H
