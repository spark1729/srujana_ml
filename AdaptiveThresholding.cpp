#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int blur_filter_value = 5;
int const max_value = 10;
int block_size = 7;
int const max_block_size = 15;
int mean_value = 2;
int const max_mean_value = 10;

Mat src, src_Gray, blurred, hist, final;

char* trackbar_blur = "Mask width";
char* block_name = "Block size";
char* mean_value_trackbar_name = "mean_value value";
char* window_name = "Adaptive Threshold";

void Adaptive_threshold_demo( int, void* ){

    medianBlur(src_Gray, blurred, blur_filter_value);
    equalizeHist(blurred, hist);
    adaptiveThreshold(hist, final, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, block_size, mean_value);
    imshow(window_name,final);

}

int main( int argc, char** argv){

    src_Gray = imread( argv[1], 0 );
    //cvtColor(src, src_Gray, CV_BGR2GRAY );
    namedWindow(window_name, CV_WINDOW_AUTOSIZE);

    createTrackbar(trackbar_blur,
                    window_name, &blur_filter_value,
                    max_value, Adaptive_threshold_demo );

    createTrackbar(block_name,
                window_name, &block_size,
                max_block_size, Adaptive_threshold_demo );

    createTrackbar(mean_value_trackbar_name,
                    window_name, &mean_value,
                    max_mean_value, Adaptive_threshold_demo );

    Adaptive_threshold_demo(0,0);

    while(true)
    {
      int c;
      c = waitKey( 20 );
      if( (char)c == 27 )
          { break; }
    }
}
