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

int main(void)
{
    // threshold_trackbar();
    // threshold_otsu();
    threshold_adaptive();

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
