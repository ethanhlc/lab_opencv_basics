#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void threshold_trackbar();
void on_threshold(int pos, void *userdata);
void threshold_otsu();
void threshold_adaptive();
void on_trackbar_adapt(int pos, void *userdata);
void erode_dilate();
void open_close();

int main(void)
{
    // threshold_trackbar();
    // threshold_otsu();
    // threshold_adaptive();
    // erode_dilate();
    open_close();

    destroyAllWindows();

    return 0;
}

/// Function Definitions
void threshold_trackbar()
{
    Mat src = imread("img/neutrophils.png", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    namedWindow("dst");
    int pos = 0;
    createTrackbar("Threshold", "dst", &pos, 255, on_threshold, &src);
    // createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void *)&src);
    setTrackbarPos("Threshold", "dst", 128);

    waitKey();  // required to keep Mat src in memory
}

void on_threshold(int pos, void *userdata)
{
    Mat src = *(Mat *)userdata;

    Mat dst;
    threshold(src, dst, pos, 255, THRESH_BINARY);

    imshow("dst", dst);
}

void threshold_otsu()
{
    Mat src = imread("img/camera.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dst;
    cout << "otsu threshold: ";
    cout << threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU) << endl;

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
}

void threshold_adaptive()
{
    Mat src = imread("img/sudoku.jpg", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    namedWindow("sudoku");
    int val = 0;
    createTrackbar("Block Size", "sudoku", &val, 200, on_trackbar_adapt, &src);
    setTrackbarPos("Block Size", "sudoku", 3);

    waitKey();
}

void on_trackbar_adapt(int pos, void *userdata)
{
    Mat src = *(Mat *)userdata;

    // set min value to 3 & force odd values
    if (pos % 2 == 0)
        pos--;
    if (pos < 3)
        pos = 3;

    Mat dst;
    adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, pos, 5);

    imshow("sudoku", dst);
}

void erode_dilate()
{
    Mat src = imread("img/milkdrop.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat bin;
    threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

    Mat kernel = getStructuringElement(MORPH_CROSS, Size(3, 3));

    Mat dst_erode, dst_dilate;
    Mat dst_erode2, dst_dilate2;
    erode(bin, dst_erode, kernel);
    dilate(bin, dst_dilate, kernel);
    erode(bin, dst_erode2, kernel, Point(-1, -1), 2);
    dilate(bin, dst_dilate2, kernel, Point(-1, -1), 2);

    imshow("src", src);
    imshow("bin", bin);
    while (1)
    {
        imshow("erode", dst_erode);
        imshow("dilate", dst_dilate);
        if (waitKey() == 'q')
            break;
        imshow("erode", dst_erode2);
        imshow("dilate", dst_dilate2);
        if (waitKey() == 'q')
            break;
    }

    waitKey();
}

void open_close()
{
    Mat src = imread("img/milkdrop.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat bin;
    threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

    Mat dst_open, dst_close;
    morphologyEx(bin, dst_open, MORPH_OPEN, Mat());
    morphologyEx(bin, dst_close, MORPH_CLOSE, Mat());

    Mat dst_erode, dst_dilate, dst_grad;
    morphologyEx(bin, dst_erode, MORPH_ERODE, Mat());
    morphologyEx(bin, dst_dilate, MORPH_DILATE, Mat());
    morphologyEx(bin, dst_grad, MORPH_GRADIENT, Mat());

    imshow("bin", bin);
    imshow("oepn", dst_open);
    imshow("close", dst_close);
    imshow("erode", dst_erode);
    imshow("dilate", dst_dilate);
    imshow("gradient", dst_grad);

    waitKey();
}
