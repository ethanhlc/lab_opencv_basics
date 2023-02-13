#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void filter_emboss();
void blurring_mean();

int main(void)
{
    // filter_emboss();
    blurring_mean();

    return 0;
}

void filter_emboss()
{
    Mat src = imread("img/rose.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    float data[] = {-1, -1, 0, -1, 0, 1, 0, 1, 1};
    Mat emboss(3, 3, CV_32FC1, data);

    Mat dst;
    filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}

void blurring_mean()
{
    Mat src = imread("img/rose.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    imshow("src", src);

    Mat dst3, dst5, dst7;


    TickMeter tm;   // create TickMeter object
    tm.start();     // start time measure
    blur(src, dst3, Size(3, 3));
    tm.stop();      // end time measure & get time in ms
    cout << "3x3 took: " << tm.getTimeMilli() << "ms." << endl;

    tm.start();     // start time measure
    blur(src, dst5, Size(5, 5));
    tm.stop();      // end time measure & get time in ms
    cout << "5x5 took: " << tm.getTimeMilli() << "ms." << endl;

    tm.start();     // start time measure
    blur(src, dst7, Size(7, 7));
    tm.stop();      // end time measure & get time in ms
    cout << "7x7 took: " << tm.getTimeMilli() << "ms." << endl;


    // print filter kernel size @ top left
    putText(dst3, "Mean: 3x3", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
            Scalar(255), 2, LINE_AA);
    putText(dst5, "Mean: 5x5", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
            Scalar(255), 2, LINE_AA);
    putText(dst7, "Mean: 7x7", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
            Scalar(255), 2, LINE_AA);

    imshow("dst3", dst3);
    imshow("dst5", dst5);
    imshow("dst7", dst7);

    waitKey();
    destroyAllWindows();
}
