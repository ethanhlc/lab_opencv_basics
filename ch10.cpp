#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void color_inverse();
void color_split();
void color_eq();

// HSV color segmentation
void color_segmentation();
void on_hue_changed(int, void *);

int lower_hue = 40, upper_hue = 80;
Mat src, src_hsv, mask;

int main(void)
{
    // color_inverse();
    // color_split();
    // color_eq();

    color_segmentation();

    waitKey();
    destroyAllWindows();

    return 0;
}

/// Function Definitions
void color_inverse()
{
    Mat src = imread("img/butterfly.jpg");

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    // Mat dst(src.rows, src.cols, src.type());

    // for (int j = 0; j < src.rows; j++)
    // {
    //     for (int i = 0; i < src.cols; i++)
    //     {
    //         Vec3b &p1 = src.at<Vec3b>(j, i);
    //         Vec3b &p2 = dst.at<Vec3b>(j, i);

    //         p2[0] = 255 - p1[0];    // B
    //         p2[1] = 255 - p1[1];    // G
    //         p2[2] = 255 - p1[2];    // R
    //     }
    // }

    // simpler form
    // for (int j = 0; j < src.rows; j++)
    // {
    //     for (int i = 0; i < src.cols; i++)
    //     {
    //         dst.at<Vec3b>(j, i) = Vec3b(255, 255, 255) - src.at<Vec3b>(j, i);
    //     }
    // }

    // simplest form
    Mat dst = ~src;


    imshow("src", src);
    imshow("dst", dst);
}

void color_split()
{
    Mat src = imread("img/candies.png");

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    vector<Mat> bgr_planes;
    split(src, bgr_planes);

    imshow("src", src);
    imshow("B_plane", bgr_planes[0]);
    imshow("G_plane", bgr_planes[1]);
    imshow("R_plane", bgr_planes[2]);

    Mat yellow = 0.7 * bgr_planes[1] + 0.3 * bgr_planes[2];
    imshow("yellow", yellow);

    Mat yellow_bi;
    threshold(yellow, yellow_bi, 190, 255, THRESH_BINARY);
    imshow("yellow_bi", yellow_bi);

    // Mat yellowMM(src.rows, src.cols, src.type());
    Mat yellowMM;
    src.copyTo(yellowMM, yellow_bi);
    imshow("yMM", yellowMM);

    waitKey();
    destroyAllWindows();
}

void color_eq()
{
    Mat src = imread("img/pepper.bmp", IMREAD_COLOR);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat src_ycrcb;
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    vector<Mat> ycrcb_planes;
    split(src_ycrcb, ycrcb_planes);

    equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); // Y channel
    // normalize(ycrcb_planes[0], ycrcb_planes[0], 0, 255, NORM_MINMAX);

    Mat dst_ycrcb;
    merge(ycrcb_planes, dst_ycrcb);

    Mat dst;
    cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

    imshow("src", src);
    imshow("dst", dst);
}

void color_segmentation()
{
    src = imread("img/candies.png", IMREAD_COLOR);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    src_hsv;
    cvtColor(src, src_hsv, COLOR_BGR2HSV);

    imshow("src", src);

    namedWindow("mask");
    createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
    createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
    on_hue_changed(0, 0);

    waitKey();
    return;
}

void on_hue_changed(int, void *)
{
    Scalar lowerb(lower_hue, 100, 0);
    Scalar upperb(upper_hue, 255, 255);
    inRange(src_hsv, lowerb, upperb, mask);

    imshow("mask", mask);
}
