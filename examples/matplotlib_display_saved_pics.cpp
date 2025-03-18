/*

How to compile:

cl /EHsc /std:c++17 /I C:\Python312\include /I F:\OpenCV_Course\myenv\Lib\site-packages\numpy\_core\include /I F:\AI_Componets\OpenCV\build\install\include matplotlib_display_saved_pics.cpp /link /LIBPATH:F:\AI_Componets\OpenCV\build\install\x64\vc17\lib /LIBPATH:C:\Python312\libs python312.lib opencv_core500.lib opencv_imgcodecs500.lib opencv_highgui500.lib opencv_imgproc500.lib

*/


#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "F:\OpenCV_Course\matplotlib-cpp\matplotlibcpp.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
namespace plt = matplotlibcpp;

int main()
{
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

    // Show plots
    plt::save("imshow.png");
    std::cout << "Result saved to 'imshow.png'.\n";

    // OpenCV

    // Read the image from file
    cv::Mat image = cv::imread("imshow.png", cv::IMREAD_COLOR);

    // Check if the image was successfully loaded
    if (image.empty())
    {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }

    // Create a window to display the image
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);

    // Show the image in the window
    cv::imshow("Display Image", image);

    // Wait for a keystroke in the window
    cv::waitKey(0);

    // Destroy the window
    cv::destroyAllWindows();


}



