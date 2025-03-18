/*

How to compile:
cl /EHsc /std:c++17 /I C:\Python312\include /I F:\OpenCV_Course\myenv\Lib\site-packages\numpy\_core\include /I F:\AI_Componets\OpenCV\build\install\include matplotlib_display_arbitary_pic.cpp /link /LIBPATH:F:\AI_Componets\OpenCV\build\install\x64\vc17\lib /LIBPATH:C:\Python312\libs python312.lib opencv_core500.lib opencv_imgcodecs500.lib opencv_highgui500.lib opencv_imgproc500.lib

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
        // Load an image from disk
        std::string image_path = "F:/OpenCV_Course/CVIP/week_1/week1-cpp/data/images/number_zero.jpg";  // Replace with the actual image path
        cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);

        if (image.empty()) {
            throw std::runtime_error("Failed to load image from disk");
        }

        // Convert the OpenCV image to a format that matplotlibcpp can use
        // Matplotlib expects the data in a 1D vector format: [r1, g1, b1, r2, g2, b2, ...]
        std::vector<uint8_t> image_data(image.rows * image.cols * 3);
        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                cv::Vec3b color = image.at<cv::Vec3b>(i, j);
                int index = (i * image.cols + j) * 3;
                image_data[index + 0] = color[2]; // Red
                image_data[index + 1] = color[1]; // Green
                image_data[index + 2] = color[0]; // Blue
            }
        }

        // Create a matplotlib figure and plot the image
        plt::figure();

        // Pass the pointer to the vector data instead of the vector itself
        plt::imshow(&image_data[0], image.rows, image.cols, 3);  // 3 channels for RGB
       
        plt::title("My matrix");    // Add a title to the figure plot.
        
        plt::axis("on");  // Optional: turn off the axis in the figure plot.

        // Save the plot to a buffer in memory
        std::vector<uint8_t> buffer = plt::save_to_buffer();

        // Decode the buffer into an OpenCV Mat object
        cv::Mat plot_image = cv::imdecode(buffer, cv::IMREAD_COLOR);
        if (plot_image.empty()) {
            throw std::runtime_error("Failed to decode image from buffer");
        }

        // Display the image using OpenCV
        cv::imshow("Matplotlib Plot with Image", plot_image);
        cv::waitKey(0);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}