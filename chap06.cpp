#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void imgAdd();

int main(void)
{
    imgAdd();

    return 0;
}

void imgAdd()
{
    Mat src1 = imread("img/camera.bmp", IMREAD_GRAYSCALE);
    Mat src2 = imread("img/dog.bmp", IMREAD_GRAYSCALE);

    Mat dst1, dst2;

    add(src1, src2, dst1);
    addWeighted(src1, 0.5, src2, 0.5, 0, dst2);

    imshow("dst1_simple", dst1);
    imshow("dst2_weighted", dst2);

    waitKey();
    destroyAllWindows();
}