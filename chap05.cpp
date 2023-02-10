#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void brightness1();
void brightness2();
void brightness3();
void brightness4();
void on_brightness(int pos, void *userdata);

void contrast1();
void contrast2();
void contrast_trackbar();
void on_contrast(int pos, void *userdata);

int main(void)
{
    // brightness1();
    // brightness2();
    // brightness3();
    // brightness4();

    // contrast1();
    // contrast2();
    contrast_trackbar();

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

void brightness4()
{
    Mat img = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    namedWindow("img");
    createTrackbar("Brightness", "img", NULL, 100, on_brightness, &img);
    on_brightness(0, &img);

    waitKey();
    destroyAllWindows();
}

void on_brightness(int pos, void *userdata)
{
    Mat src = *(Mat *)userdata;
    Mat dst = src + pos;
    // *(Mat *)userdata = *(Mat *)userdata + pos;   // wrong, constant inc in brightness

    imshow("img", dst);
}

void contrast1()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    float s = 2.f;
    Mat dst = s * src;

    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    destroyAllWindows();
}

void contrast2()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    float alpha = 1.f;
    Mat dst = src + (src - 128) * alpha;

    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    destroyAllWindows();
}

void contrast_trackbar()
{
    Mat img = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    namedWindow("img");
    createTrackbar("Contrast", "img", NULL, 100, on_contrast, &img);
    // setTrackbarMin("Contrast", "img", -1);
    on_contrast(50, &img);

    waitKey();
    destroyAllWindows();
}

void on_contrast(int pos, void *userdata)
{
    Mat src = *(Mat *)userdata;
    float fpos = pos;

    if (fpos < 51)
    {
        fpos = 50 - fpos;
        fpos = fpos / 50;
    }
    else
    {
        fpos = fpos - 50;
        fpos = fpos / 10;
    }

    Mat dst = src + (src - 128) * fpos;

    imshow("img", dst);
}
