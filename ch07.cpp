#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void filter_emboss();

int main(void)
{
    filter_emboss();

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
