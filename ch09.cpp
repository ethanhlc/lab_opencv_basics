#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void sobel_edge();
void canny_edge();
void hough_lines();
void hough_line_segments();
void hough_circles();

int main(void)
{
    // sobel_edge();
    // canny_edge();
    // hough_lines();
    // hough_line_segments();
    hough_circles();

    waitKey();
    destroyAllWindows();

    return 0;
}

/// Function Definitions
void sobel_edge()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dx, dy;
    Sobel(src, dx, CV_32FC1, 1, 0);
    Sobel(src, dy, CV_32FC1, 0, 1);

    Mat fmag, mag;
    magnitude(dx, dy, fmag);
    fmag.convertTo(mag, CV_8UC1);

    Mat edge = mag > 150;

    imshow("src", src);
    imshow("mag", mag);
    imshow("edge", edge);
}

void canny_edge()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dst1, dst2;
    Canny(src, dst1, 50, 100);
    Canny(src, dst2, 50, 150);

    imshow("src", src);
    imshow("dst1", dst1);
    imshow("dst2", dst2);
}

void hough_lines()
{
    Mat src = imread("img/building.jpg", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat edge;
    Canny(src, edge, 50, 150);

    vector<Vec2f> lines;
    // use canny_edge image, pixel resolution = 1, degree = 1, threshold 250
    HoughLines(edge, lines, 1, CV_PI / 180, 250);

    Mat dst;
    cvtColor(edge, dst, COLOR_GRAY2BGR);

    for (size_t i = 0; i < lines.size(); i++)
    {
        float r = lines[i][0];  // rho for each line
        float t = lines[i][1];  // theta for each line
        double cos_t = cos(t), sin_t = sin(t);  // calc cos(t) & sin(t)
        double x0 = r * cos_t, y0 = r * sin_t;  // calc x0, y0 from rho, theta
        double alpha = 1000;    // offset to calculate 2 points from single pt
        Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
        Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
        line(dst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
    }

    imshow("src", src);
    imshow("dst", dst);
}

void hough_line_segments()
{
    Mat src = imread("img/building.jpg", IMREAD_GRAYSCALE);
    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat edge;
    Canny(src, edge, 50, 150);

    vector<Vec4i> lines;
    HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

    Mat dst;
    cvtColor(edge, dst, COLOR_GRAY2BGR);

    for (Vec4i l : lines)
    {
        line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
    }

    imshow("src", src);
    imshow("dst", dst);
}

void hough_circles()
{
    Mat src = imread("img/coins.png", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat blurred;
    blur(src, blurred, Size(3, 3));

    vector<Vec3f> circles;
    HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (Vec3f c : circles)
    {
        Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);
        circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
    }

    imshow("src", src);
    imshow("dst", dst);
}
