#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void brightness1();

int main(void)
{
    brightness1();

    return 0;
}

void brightness1()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    // Mat dst = src + 100;
    Mat dst_add;
    add(src, 100, dst_add);         // can also use add function

    // Mat dst_sub = src - 100;
    Mat dst_sub;
    subtract(src, 100, dst_sub);    // subtract function

    imshow("src", src);
    imshow("dst_add", dst_add);
    imshow("dst_sub", dst_sub);
    waitKey();

    destroyAllWindows();
}
