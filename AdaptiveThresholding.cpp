/*
 *  Project name: Custom adaptive filtering
 *  Authors: Dhaivat Bhatt, Mudit Jain, Aparajita sahoo
 *  Date: 20/12/2014
 */

// Importing necessary packages

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>

// Defining namespace
using namespace cv;

// Defining global variable

int blur_filter_parameter = 5;                              // Initializing blur filter parameter(n). Mask size will be 2*n + 3
int const blur_filter_parameter_max_value = 10;             // Defining maximum value fir blur filter parameter
int block_size_parameter = 7;                               // Defining block size parameter(n). Actual block size will be 2*n + 3
int const max_block_size_parameter = 15;                    // Defining maximum value for block size parameter
int mean_value = 2;                                         // Mean value, to be subtracted from thresholded image
int const max_mean_value = 10;                              // Maximum value mean value can take

/*
 * src : Input image
 * src_gray: gray scaled image of input image
 * blurred: blurred image acquired using blur_filter_parameter
 * hist: Histogram equalized image
 * final: Final image after performing adaptive_thresholding on hist.
 */

Mat src, src_Gray, blurred, hist, final;

// Defining names of trackbars and window

char* trackbar_blur = "Mask width Parameter";
char* block_name = "Block size parameter";
char* mean_value_trackbar_name = "mean_value value";
char* window_name = "Adaptive Threshold";

// This function will be called everytime any of the trackbars will change it's value.

void Adaptive_threshold_demo( int, void* ){

    // Applying medianBlur() to smooth the image
    medianBlur(src_Gray, blurred, 2*blur_filter_parameter + 3);

    // Performing histogram equalization on blurred image
    equalizeHist(blurred, hist);

    // Applying adaptivethresholding on hist image
    adaptiveThreshold(hist, final, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 2*block_size_parameter + 3, mean_value);

    // Displaying the image and trackbars
    imshow(window_name,final);
}


int main( int argc, char** argv){

    // Input image
    src_Gray = imread( argv[1], 0 );

    // Creating window to display image and trackbars
    namedWindow(window_name, CV_WINDOW_AUTOSIZE);

    // Creating trackbars

    /*
     *  Parameters:
     *      1. Name of the trackbar
     *      2. Name of the window in which trackbar is to be displayed
     *      3. Passing reference of the parameteric value
     *      4. Maximum value
     *      5. Function which will be called when trackbar value is changed
     */
    createTrackbar(trackbar_blur,
                    window_name, &blur_filter_parameter,
                    blur_filter_parameter_max_value, Adaptive_threshold_demo );

    createTrackbar(block_name,
                window_name, &block_size_parameter,
                max_block_size_parameter, Adaptive_threshold_demo );

    createTrackbar(mean_value_trackbar_name,
                    window_name, &mean_value,
                    max_mean_value, Adaptive_threshold_demo );

    // Initializing function
    Adaptive_threshold_demo(0,0);

    // Waiting for key from user to terminate the program
    while(true)
    {
      int c;
      c = waitKey( 20 );
      if( (char)c == 27 )
          { break; }
    }
}
