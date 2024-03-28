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
//    CommandLineParser parser( argc, argv, "{@input | fruits.jpg | input image}" );
    src = imread( samples::findFile( "/Users/thechosenone/CV-photo-analyzer/blur_service/src/bad/second.jpg" ), IMREAD_COLOR ); // Load an image
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

    cv::Mat dst;

    cv::Sobel(src_gray, dst, CV_16S, 1, 0, 3);

//    cv::imshow("Display window", dst);

//    waitKey(0);

    Mat show_dst_x;
//    convertTo(dst, abs_dst);

    dst.convertTo(show_dst_x, CV_8UC1, 0.5, 127);

//    imshow("Display window", show_dst);

//    waitKey(0);

    cv::Sobel(src_gray, dst, CV_16S, 0, 1, 3);

//    cv::imshow("Display window", dst);

//    waitKey(0);

//    convertTo(dst, abs_dst);

    Mat show_dst_y;

    dst.convertTo(show_dst_y, CV_8UC1, 0.5, 127);

    imshow("Display window", show_dst_y);

    waitKey(0);

    return 0;
}