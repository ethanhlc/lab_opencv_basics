#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void filter_emboss();
void blurring_mean();
void blurring_gaussian();
void unsharpen_mask();
void noise_gaussian();
void filter_bilateral();

int main(void)
{
    // filter_emboss();
    // blurring_mean();
    // blurring_gaussian();
    // unsharpen_mask();
    // noise_gaussian();
    filter_bilateral();

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

void blurring_gaussian()
{
    Mat src = imread("img/rose.bmp");

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    imshow("src", src);

    Mat dst;
    for (int sigma = 1; sigma <= 5; sigma++)
    {
        GaussianBlur(src, dst, Size(), (double)sigma);

        String text = format("sigma = %d", sigma);
        putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
                Scalar(255), 2, LINE_AA);

        String winname = format("dst%d", sigma);
        imshow(winname, dst);
        waitKey();
    }

    destroyAllWindows();
}

void unsharpen_mask()
{
    Mat src = imread("img/rose.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    imshow("src", src);

    for (int sigma = 1; sigma <= 5; sigma++)
    {
        Mat blurred;
        GaussianBlur(src, blurred, Size(0, 0), sigma);

        float alpha = 1.f;
        Mat dst = (1 + alpha) * src - alpha * blurred;

        String text = format("sigma: %d", sigma);
        putText(dst, text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
                Scalar(255), 2, LINE_AA);

        String winname = format("dst%d", sigma);
        imshow(winname, dst);
        waitKey();
    }

    destroyAllWindows();
}

void noise_gaussian()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    imshow("src", src);

    for (int stddev = 10; stddev <= 30; stddev += 10)
    {
        Mat noise(src.size(), CV_32FC1);
        randn(noise, 0, stddev);

        Mat dst;
        add(src, noise, dst, Mat(), CV_8UC1);

        String desc = format("stddev = %d", stddev);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
                Scalar(255), 2, LINE_AA);

        imshow(desc, dst);
        waitKey();
    }

    destroyAllWindows();
}

void filter_bilateral()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    imshow("src_orig", src);

    // add noise to img
    Mat noise(src.size(), CV_32SC1);
    randn(noise, 0, 5);
    add(src, noise, src, noArray(), CV_8UC1);

    // simple gaussian blur to remove noise
    Mat dst1;
    GaussianBlur(src, dst1, Size(), 5);

    // bilateral filter to remove noise
    Mat dst2;
    bilateralFilter(src, dst2, -1, 10, 5);

    imshow("src_noise", src);
    imshow("dst1_gaussian", dst1);
    imshow("dst2_bilateral", dst2);

    waitKey();
    destroyAllWindows();
}
