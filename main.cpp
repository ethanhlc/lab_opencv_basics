#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//// Function Declarations ////
void PointExercise(void);
void RectExercise(void);

int main()
{
    //cout << "Hello OpenCV " << CV_VERSION << endl;

    //Mat img;
    //img = imread("lenna.bmp", IMREAD_GRAYSCALE);

    //if (img.empty())
    //{
    //    cerr << "Image load failed!" << endl;
    //    return 1;
    //}

    //vector<int> params;
    //params.push_back(IMWRITE_JPEG_QUALITY);
    //params.push_back(95);
    //imwrite("lenna.jpg", img, params);

    //namedWindow("image");
    //imshow("image", img);

    //waitKey(0);

    //PointExercise();
    RectExercise();

    return 0;
}

//// Function Definitions ////
void PointExercise(void)
{
    Point pt1;
    pt1.x = 15;
    pt1.y = 20;

    Point pt2(10, 30);

    Point pt3 = pt1 + pt2;
    Point pt4 = pt1 * 2;

    cout << "pt1: " << pt1 << endl;
    cout << "pt2: " << pt2 << endl;
    cout << "pt3 = pt1 + pt2: " << pt3 << endl;
    cout << "pt4 = pt1 * 2: " << pt4 << endl;
}

void RectExercise(void)
{
    Rect rc1;
    Rect rc2(10, 10, 60, 40);

    Rect rc3 = rc1 + Size(50, 40);
    Rect rc4 = rc2 + Point(10, 10);

    Rect rc5 = rc3 & rc4;
    Rect rc6 = rc3 | rc4;

    cout << "rc1: " << rc1 << endl;
    cout << "rc2: " << rc2 << endl;
    cout << "rc3: " << rc3 << endl;
    cout << "rc4: " << rc4 << endl;
    cout << "rc5 = rc3 & rc4: " << rc5 << endl;
    cout << "rc6 = rc3 | rc4: " << rc6 << endl;
    cout << endl;

    Rect rc7(70, 50, 10, 10);
    Rect rc8 = rc2 | rc7;
    cout << "rc7: " << rc7 << endl;
    cout << "rc8 = rc2 | rc7: " << rc8 << endl;
}
