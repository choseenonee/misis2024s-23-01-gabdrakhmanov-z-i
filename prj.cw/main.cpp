#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
//Mat src, src_gray;
//Mat dst, detected_edges;
//int lowThreshold = 0;
//const int max_lowThreshold = 100;
//const int ratio = 3;
//const int kernel_size = 3;
//const char* window_name = "Edge Map";
//static void CannyThreshold(int, void*)
//{
//    blur( src_gray, detected_edges, Size(12,12) );
//    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
//    dst = Scalar::all(0);
//    src.copyTo( dst, detected_edges);
//    imshow( window_name, dst );
//}


int main()
{
    Mat src, src_gray;
    src = imread( samples::findFile( "/Users/thechosenone/CLionProjects/https:/github.com/choseenonee/123/misis2024s-23-01-gabdrakhmanov-z-i/prj.cw/bad/second.jpg" ), IMREAD_COLOR ); // Load an image
    if( src.empty() )
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        return -1;
    }

    std::cout << "channels: " << src.channels() << std::endl << "depth: "; // CV_8UC3
    switch (src.depth()) {
        case CV_16U:
            std::cout << "16 bit unsigned";
            break;
        case CV_8U:
            std::cout << "8 bit unsigned";
            break;
    };

    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    cv::Mat dst;

    Mat show_dst_x;
    Mat show_dst_y;

    cv::Sobel(src_gray, dst, CV_8U, 1, 0, 3);
    dst.convertTo(show_dst_x, CV_8UC1, 1, 0);

    cv::Sobel(src_gray, dst, CV_8U, 0, 1, 3);
    dst.convertTo(show_dst_y, CV_8UC1, 1, 0);

    imshow("Display window", show_dst_x);

    waitKey(0);

    imshow("Display window", show_dst_y);

    waitKey(0);

    return 0;
}