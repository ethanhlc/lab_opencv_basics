#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//// Function Declarations ////
void PointExercise(void);

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

    PointExercise();

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
