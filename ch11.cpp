#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(void)
{
    Mat img = imread("img/lenna.bmp");

    if (img.empty())
    {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    imshow("img", img);

    waitKey();
    destroyAllWindows();

    return 0;
}
