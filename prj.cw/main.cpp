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
//        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }
//    dst.create( src.size(), src.type() );
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
//    namedWindow( window_name, WINDOW_AUTOSIZE );
//    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
//    CannyThreshold(0, 0);

//    cv::imshow("Display window", src_gray);

//    cv::imshow("Display window", dst);

//    waitKey(0);

    cv::Mat dst;

    Mat show_dst_x;
    Mat show_dst_y;

    cv::Sobel(src_gray, dst, CV_16S, 1, 0, 3);
    dst.convertTo(show_dst_x, CV_8UC1, 0.5, 127);

    cv::Sobel(src_gray, dst, CV_16S, 0, 1, 3);
    dst.convertTo(show_dst_y, CV_8UC1, 0.5, 127);

    imshow("Display window", show_dst_x);

    waitKey(0);

    imshow("Display window", show_dst_y);

    waitKey(0);

    return 0;
}