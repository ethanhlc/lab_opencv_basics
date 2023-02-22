#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(void)
{
    Mat img = imread("img/lenna.bmp");

    imshow("img", img);

    waitKey();
    destroyAllWindows();

    return 0;
}
