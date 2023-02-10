#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void brightness1();
void brightness2();
void brightness3();

int main(void)
{
    // brightness1();
    // brightness2();
    brightness3();

    return 0;
}

void brightness1()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    // Mat dst = src + 100;
    Mat dst_add;
    add(src, 100, dst_add);         // can also use add function

    // Mat dst_sub = src - 100;
    Mat dst_sub;
    subtract(src, 100, dst_sub);    // subtract function

    imshow("src", src);
    imshow("dst_add", dst_add);
    imshow("dst_sub", dst_sub);
    waitKey();

    destroyAllWindows();
}

void brightness2()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    // create empty Mat object
    Mat dst(src.rows, src.cols, src.type());

    // manually iterate through & add value (saturation not considered)
    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            dst.at<uchar>(j, i) = src.at<uchar>(j, i) - 100;
        }
    }

    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    destroyAllWindows();
}

void brightness3()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dst(src.rows, src.cols, src.type());

    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            // add saturation check to manual iteration
            // int v = src.at<uchar>(j, i) + 100;
            // dst.at<uchar>(j, i) = v > 255 ? 255 : v < 0 ? 0 : v;
            dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
        }
    }

    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    destroyAllWindows();
}
