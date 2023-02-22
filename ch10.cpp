#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void color_inverse();

int main(void)
{
    color_inverse();

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

    Mat dst(src.rows, src.cols, src.type());

    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            Vec3b &p1 = src.at<Vec3b>(j, i);
            Vec3b &p2 = dst.at<Vec3b>(j, i);

            p2[0] = 255 - p1[0];    // B
            p2[1] = 255 - p1[1];    // G
            p2[2] = 255 - p1[2];    // R
        }
    }

    imshow("src", src);
    imshow("dst", dst);
}
