/**
 * @file main.cpp
 * @brief A program for applying regions on an image.
 * @author Eduardo Ulises Martínez Vaca
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utility.h"

using namespace cv;
using namespace std;

Mat Binary(Mat ori);
void Region(int x, int y, int cont, Mat& g, Mat& Ori);
void FindCentroids(Mat& labeledRegions);
void Read(Mat bin);

Mat Binary(Mat ori) {
    Mat msk(ori.rows, ori.cols, CV_8U, Scalar(0));

    for(int row = 0; row < ori.rows; row++){
        for(int col = 0; col < ori.cols; col++){
            if(ori.at<uchar>(row, col) > 125){
                msk.at<uchar>(row,col) = uchar(255);
            }
            else{
                msk.at<uchar>(row,col) = uchar(0);
            }
        }

    }
    imwrite("bin.jpg", msk);
    return msk;
}

void Region(int x, int y, int cont, Mat& g, Mat& Ori){
    queue<pair<int, int>> pixelQueue;
    pixelQueue.emplace(x, y);

    while (!pixelQueue.empty()) {
        pair<int, int> currentPixel = pixelQueue.front();
        pixelQueue.pop();

        int currentX = currentPixel.first;
        int currentY = currentPixel.second;

        if (currentX < 0 || currentY < 0 || currentX >= Ori.rows || currentY >= Ori.cols) {
            continue;  // Avoid accessing out-of-bounds pixels
        }

        if (Ori.at<uchar>(currentX, currentY) == 255 && g.at<uchar>(currentX, currentY) == 0) {
            g.at<uchar>(currentX, currentY) = cont;

            // Add neighboring pixels to the queue
            pixelQueue.emplace(currentX + 1, currentY);
            pixelQueue.emplace(currentX - 1, currentY);
            pixelQueue.emplace(currentX, currentY + 1);
            pixelQueue.emplace(currentX, currentY - 1);
        }
    }
}

/*void FindCentroids(Mat& labeledRegions) {
    vector<Point2f> centroids;
    for (int label = 125; label <= 255; label += 5) {
        Mat mask = (labeledRegions == label);
        Moments m = moments(mask, true);
        Point2f centroid(m.m10 / m.m00, m.m01 / m.m00);
        centroids.push_back(centroid);
    }

    for (const Point2f& centroid : centroids) {
        circle(labeledRegions, centroid, 2, Scalar(255), -1); // Draw a white circle at the centroid
    }
}*/

void FindCentroids(Mat& labeledRegions){
    for(int label = 125; label <= 255; label += 5){
        vector<Point> points;

        //Encontremos todos los puntos de la región etiquetada
        for(int row = 0; row < labeledRegions.rows; row++){
            for(int col = 0; col < labeledRegions.cols; col++){
                if(labeledRegions.at<uchar>(row, col) == label){
                    points.push_back(Point(col, row));
                }
            }
        }

        //Calculamos el centroide como el promedio de las coordenadas x e y
        Point2f centroid(0.0,0.0);

        for(const Point& point: points) {
            centroid.x += point.x;
            centroid.y += point.y;
        }

        if(!points.empty()) {
            centroid.x /= points.size();
            centroid.y /= points.size();
            circle(labeledRegions, centroid, 2, Scalar(255), -1); // Dibuja un círculo blanco en el centroide
        }
    }
}

void Read(Mat bin){
    int cont = 125;
    Mat g(bin.rows, bin.cols, CV_8U, Scalar(0));

    for (int row = 0; row < bin.rows; row++) {
        for (int col = 0; col < bin.cols; col++) {
            if (bin.at<uchar>(row, col) == 255 && g.at<uchar>(row, col) == 0) {
                Region(row, col, cont, g, bin);
                cont += 5;
            }
        }
    }
    imwrite("labeled_regions.jpg", g);

    // Find centroids and mark them in the labeled image
    FindCentroids(g);
    imwrite("centroids.jpg", g);
}



int main() {
    Mat Ori = LoadImage("../img.png", IMREAD_GRAYSCALE);
    Mat Bin = Binary(Ori);
    Mat Ope = Erosion(Bin);

    Read(Ope);

    return 0;
}
