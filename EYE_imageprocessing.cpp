/*
 *      Project: Applying smoothing and thresholding on EYE image and setting up the parameters using Graphical user interface
 *      Authors: Dhaivat Bhatt, Mudit Jain
 *      Date: 20/12/2014
 */


// Importing necessary packages

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/* Global declarations */

// Variables for smoothing and thresholding

/*
 *  Smoothing types:
 *      1. For median filter,   smoothing_type = 0
 *      2. For Gaussian filter, smoothing_type = 1
 */

int smoothing_type = 0;
int const no_of_smoothing_types = 1;

/*
 *  Thresholding types:
 *      1. For Otsu thresholding,       thresholding_type = 0
 *      2. For Thresholding,            thresholding_type = 1
 *      3. For Adaptive thresholding,   thresholding_type = 2
 *      4. For Canny edge detection,    thresholding_type = 3
 */

int thresholding_type = 2;
int const no_of_thresholding_types = 3;

// Defining median filter parameters
int blur_filter_parameter = 5;                       // Parameter(n) to set mask size, actual size of mask is 2*n + 3
int const blur_filter_parameter_max_value = 10;

// Defining gaussian filter parameters
int gaussian_filter_parameter = 5;                   // Parameter(n) to set mask size, actual size of mask is 2*n + 3
int const gaussian_filter_parameter_max_value = 10;

// Definint Otsu_thresholding parameters

// Defining thresholding parameters


// Defnining adaptive thresholding parameters
int block_size_parameter = 7;               // Block size
int const max_block_size_parameter = 15;
int mean_value = 2;                         // Mean value to be subtracted from adaptive thresholded image
int const max_mean_value = 10;

// Names of different trackbars
char* smoothing_name =  "Type: \n 0: Median filter \n 1: Gaussian filter ";
char* thresholding_name = "Type: \n 0: Otsu_thresholding \n 1: Thresholding \n 2: Adaptive thresholding \n 3: Canny edge detection";
char* median_smooth = "Mask width parameter: ";
char* gaussian_smooth = "Gaussian parameter: ";
char* block_name = "Block size parameter";
char* mean_value_trackbar_name = "Mean_value";

// Different windows
char* main_window_name = "Image processing on eye image"; // Main window which will display different trackbars
char* Thresholded_image_display = "Thresholded image";    // Thresholded image will be displayed in this window
char* Smooth_image_display = "Smoothened image";          // Smooth image will be displayed here


/*
 *      src_Gray: Source grayscaled image.
 *      smooth_image: Smoothened image will be stored here.
 *      Thresholded_image: Thresholded image will be stored here.
 */
Mat src_Gray, smooth_image, thresholded_image;

// This function will be called when any of the trackbar parameters will be changed
void Image_processing_function( int, void* ){

    switch(smoothing_type) {
        case 0:
            // smoothing_type 0 corresponds to median blurring
            medianBlur(src_Gray, smooth_image, 2 * blur_filter_parameter + 3);
            switch(thresholding_type){
                case 0:
                    cout << "Otsu thresholding" << endl;
                    break;
                case 1:
                    cout << "Thresholding" << endl;
                    break;
                case 2:
                    adaptiveThreshold(smooth_image, thresholded_image, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 2*block_size_parameter + 3, mean_value);
                    //cout << "Adaptive thresholding" << endl;
                    break;
                case 3:
                    cout << "canny edgeDetection" << endl;
                    break;

            }
            break;

        case 1:
            // smoothing_type 1 corresponds to Gaussian blur
            GaussianBlur(src_Gray, smooth_image, Size(2 * gaussian_filter_parameter + 1, 2 * gaussian_filter_parameter + 1), 0, 0);
            switch(thresholding_type){
                case 0:
                    cout << "Otsu thresholding1" << endl;
                    break;
                case 1:
                    cout << "Thresholding1" << endl;
                    break;
                case 2:
                    adaptiveThreshold(smooth_image, thresholded_image, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 2*block_size_parameter + 3, mean_value);
                    //cout << "Adaptive thresholding1" << endl;
                    break;
                case 3:
                    cout << "canny edgeDetection1" << endl;
                    break;
            }
            break;
    }

    imshow(Smooth_image_display, smooth_image);             // smooth image will be displayed
    imshow(Thresholded_image_display, thresholded_image);   // thresholded image will be displayed
}


int main( int argc, char** argv ){

    src_Gray = imread( argv[1], 0 );                    // Input image

    // Initializing windows
    namedWindow(main_window_name, CV_WINDOW_AUTOSIZE);
    namedWindow(Smooth_image_display, CV_WINDOW_AUTOSIZE);
    namedWindow(Thresholded_image_display, CV_WINDOW_AUTOSIZE);

    // Creating trackbars
    /*
    *  Parameters:
    *      1. Name of the trackbar
    *      2. Name of the window in which trackbar is to be displayed
    *      3. Passing reference of the parameteric value
    *      4. Maximum value
    *      5. Function which will be called when trackbar value is changed
    */
    createTrackbar(smoothing_name,
                    main_window_name, &smoothing_type,
                    no_of_smoothing_types, Image_processing_function );

    createTrackbar(thresholding_name,
                    main_window_name, &thresholding_type,
                    no_of_thresholding_types, Image_processing_function );

    createTrackbar(median_smooth,
                    main_window_name, &blur_filter_parameter,
                    blur_filter_parameter_max_value, Image_processing_function );

    createTrackbar(gaussian_smooth,
                    main_window_name, &gaussian_filter_parameter,
                    gaussian_filter_parameter_max_value, Image_processing_function );

    createTrackbar(block_name,
                    main_window_name, &block_size_parameter,
                    max_block_size_parameter, Image_processing_function );

    createTrackbar(mean_value_trackbar_name,
                    main_window_name, &mean_value,
                    max_mean_value, Image_processing_function );

    // initializing function
    Image_processing_function( 0, 0 );

    // Waiting for key from user to terminate the program
    while(true)
    {
        int c;
        c = waitKey( 20 );
        if( (char)c == 27 )
            { break; }
    }

}
