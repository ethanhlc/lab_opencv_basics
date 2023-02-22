#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void color_inverse();
void color_split();

int main(void)
{
    // color_inverse();
    color_split();

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
