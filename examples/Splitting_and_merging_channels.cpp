
/*

How to compile:
cl /EHsc /std:c++17 /I C:\Python312\include /I F:\OpenCV_Course\myenv\Lib\site-packages\numpy\_core\include /I F:\AI_Componets\OpenCV\build\install\include Splitting_and_merging_channels.cpp /link /LIBPATH:F:\AI_Componets\OpenCV\build\install\x64\vc17\lib /LIBPATH:C:\Python312\libs python312.lib opencv_core500.lib opencv_imgcodecs500.lib opencv_highgui500.lib opencv_imgproc500.lib

Documentation for matplotlibcpp:
https://matplotlib-cpp.readthedocs.io/en/latest/index.html
*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "dataPath.hpp"
#include <cmath>
#include "F:\OpenCV_Course\matplotlib-cpp\matplotlibcpp.h"
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;
using namespace cv;
using namespace std;
namespace plt = matplotlibcpp;


int main() {
    try {
        // Load an image from disk
        std::string image_path = DATA_PATH + "/images/musk.jpg";  // Replace with the actual image path
        cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);

        if (image.empty()) {
            throw std::runtime_error("Failed to load image from disk");
        }

        // Split the image into its RGB channels
        cv::Mat channels[3];
        cv::split(image, channels);  // channels[0] = Blue, channels[1] = Green, channels[2] = Red

		// Below code is to quickly and directly view the image via OpenCV GUI:

        // Prepare OpenCV Mat objects for displaying
        //cv::Mat blue_channel, green_channel, red_channel;

        // // Blue channel
        // cv::merge(&channels[0], 1, blue_channel);
        // cv::imshow("Blue Channel", blue_channel);  // Display Blue Channel
        // cv::waitKey(0); // Wait for key press

        // // Green channel
        // cv::merge(&channels[1], 1, green_channel);
        // cv::imshow("Green Channel", green_channel);  // Display Green Channel
        // cv::waitKey(0); // Wait for key press

        // Red channel
        // cv::merge(&channels[2], 1, red_channel);
        // cv::imshow("Red Channel", red_channel);  // Display Red Channel
        // cv::waitKey(0); // Wait for key press


		// --------------------------------------------------------------------------------------------

		// Below code is to spice things up, take a boring picture and add spice things up, add axis information using matplotlibcpp and then have opencv to view it.
		// This requires some work, we first need to convert the OpenCV stored image matrix, to a matrix which is understandable for matplotlibcpp.
		// Then we use matplotlibcpp to spice up the image.
		// Then we need to store the spiced up results to memory buffer, so that we have a copy of it (a C++ vector).
		// Then we have opencv to decode and convert it back to an opencv 'mat' object. (Mat object is opencv's way to store images in memory)
		// Then we have opencv to view stored mat object using it's GUI (this is not needed, can also use matplotlibcpp GUI to view the image contents too but openCV GUI is better since we can do CV work to it)

		// Now lets take the separate color channels and insert them into a matplotlib diagrams, provides axis and metrics:

        // Matplotlib plotting - Convert channels and place them into 1D vectors since this is what matplotlib accepts
        std::vector<uint8_t> blue_data(image.rows * image.cols);
        std::vector<uint8_t> green_data(image.rows * image.cols);
        std::vector<uint8_t> red_data(image.rows * image.cols);

        for (int i = 0; i < image.rows; ++i) 
		{
            for (int j = 0; j < image.cols; ++j) 
			{
                blue_data[i * image.cols + j] = channels[0].at<uchar>(i, j);
                green_data[i * image.cols + j] = channels[1].at<uchar>(i, j);
                red_data[i * image.cols + j] = channels[2].at<uchar>(i, j);
            }
        }

        // Plot Blue channel using matplotlibcpp
        plt::figure();
        plt::imshow(&blue_data[0], image.rows, image.cols, 1, {{"cmap", "gray"}});  // 1 channel for grayscale
        plt::title("Blue Channel");
        plt::axis("on");
        // plt::show();			// This will show the plot via python's matplotlib GUI implementation.


		// Save the plot to a blue_buffer in memory - This is only for viewing the plot via OpenCV
        std::vector<uint8_t> blue_buffer = plt::save_to_buffer();

        // Decode the blue_buffer into an OpenCV Mat object
        cv::Mat blue_plot_channel = cv::imdecode(blue_buffer, cv::IMREAD_COLOR);
        if (blue_plot_channel.empty()) 
		{
            throw std::runtime_error("Failed to decode image from buffer");
        }


        // Plot Green channel using matplotlibcpp
        plt::figure();
        plt::imshow(&green_data[0], image.rows, image.cols, 1, {{"cmap", "gray"}});  // 1 channel for grayscale
        plt::title("Green Channel");
        plt::axis("on");
        // plt::show();			// This will show the plot via python's matplotlib GUI implementation.


        // Save the plot to a green_buffer in memory - This is only for viewing the plot via OpenCV
        std::vector<uint8_t> green_buffer = plt::save_to_buffer();		// save_to_buffer, is a custom function for matplotlibcpp.

        // Decode the green_buffer into an OpenCV Mat object
        cv::Mat green_plot_channel = cv::imdecode(green_buffer, cv::IMREAD_COLOR);
        if (green_plot_channel.empty()) 
		{
            throw std::runtime_error("Failed to decode image from buffer");
        }


        // Plot Red channel using matplotlibcpp
        plt::figure();
        plt::imshow(&red_data[0], image.rows, image.cols, 1, {{"cmap", "gray"}});  // 1 channel for grayscale, cmap is to set matplotlib to display the color scale in gray, else it will show coolwarm color as a color scale.
        plt::title("Red Channel");
        plt::axis("on");
        // plt::show();			// This will show the plot via python's matplotlib GUI implementation.


        // Save the plot to a red_buffer in memory - This is only for viewing the plot via OpenCV
        std::vector<uint8_t> red_buffer = plt::save_to_buffer();

        // Decode the red_buffer into an OpenCV Mat object
        cv::Mat red_plot_channel = cv::imdecode(red_buffer, cv::IMREAD_COLOR);
        if (red_plot_channel.empty()) 
		{
            throw std::runtime_error("Failed to decode image from buffer");
        }


        // Display the image using OpenCV GUI, all windows open simultaneously:
		
        cv::imshow("Original Image", image);
        cv::imshow("Matplotlib Plot with Image Red", red_plot_channel);
        cv::imshow("Matplotlib Plot with Image Green", green_plot_channel);
        cv::imshow("Matplotlib Plot with Image Blue", blue_plot_channel);
        
		cv::waitKey(0);

    } catch (const std::exception& e) 
	{
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
