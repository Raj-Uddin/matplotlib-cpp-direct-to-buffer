/*

How to compile:
cl /EHsc /std:c++17 /I C:\Python312\include /I F:\OpenCV_Course\myenv\Lib\site-packages\numpy\_core\include /I F:\AI_Componets\OpenCV\build\install\include matplotlib_display_pics_from_memory.cpp /link /LIBPATH:F:\AI_Componets\OpenCV\build\install\x64\vc17\lib /LIBPATH:C:\Python312\libs python312.lib opencv_core500.lib opencv_imgcodecs500.lib opencv_highgui500.lib opencv_imgproc500.lib

*/


#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "F:\OpenCV_Course\matplotlib-cpp\matplotlibcpp.h"
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;
namespace plt = matplotlibcpp;



int main() {
    try {


    // Prepare data
    int ncols = 500, nrows = 300;
    std::vector<float> z(ncols * nrows);
    for (int j=0; j<nrows; ++j) {
        for (int i=0; i<ncols; ++i) {
            z.at(ncols * j + i) = std::sin(std::hypot(i - ncols/2, j - nrows/2));
        }
    }

    const float* zptr = &(z[0]);
    const int colors = 1;

    plt::title("My matrix");
    plt::imshow(zptr, nrows, ncols, colors);

        // Call the save_to_buffer function
        std::vector<uint8_t> buffer = plt::save_to_buffer();

        // Decode the buffer into an OpenCV Mat object
        cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);
        if (image.empty()) {
            throw std::runtime_error("Failed to decode image from buffer");
        }

        // Display the image using OpenCV
        cv::imshow("Plot", image);
        cv::waitKey(0);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}