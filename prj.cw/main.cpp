#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>


using namespace cv;


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
    Mat show_dst_zero;

    cv::Sobel(src_gray, dst, CV_8U, 1, 0, 3);
    dst.convertTo(show_dst_x, CV_8UC1, 1, 0);

    cv::Sobel(src_gray, dst, CV_8U, 0, 1, 3);
    dst.convertTo(show_dst_y, CV_8UC1, 1, 0);

    // костыль
    dst.convertTo(show_dst_zero, CV_8UC1, 0, 0);

    Mat output;

    auto channels = std::vector<Mat>{show_dst_x, show_dst_y, show_dst_zero};

    merge(channels, output);

    imshow("Display window", output);

    waitKey(0);

    return 0;
}