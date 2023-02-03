#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//// Function Declarations ////
void PointExercise(void);
void RectExercise(void);
void RotatedRectExercise(void);
void MatOp1(void);
void MatOp2(void);

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
    //RectExercise();
    //RotatedRectExercise();
    //MatOp1();
    MatOp2();

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

void RotatedRectExercise(void)
{
    RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f);

    Point2f pts[4];
    rr1.points(pts);

    Rect br = rr1.boundingRect();
    Rect2f br_f = rr1.boundingRect2f();

    cout << "rr1.center: " << rr1.center << " rr1.size: " << rr1.size << " rr1.angle: " << rr1.angle << endl;
    cout << "pts[0]: " << pts[0] << " pts[1]: " << pts[1] << endl << "pts[2]: " << pts[2] << " pts[3]: " << pts[3] << endl << endl;
    cout << "br: " << br << endl;
    cout << "br_float: " << br_f << endl;
}

void MatOp1(void)
{
    Mat img1;       // empty matrix

    Mat img2(480, 640, CV_8UC1);        // unsigned char, 1-channel
    Mat img3(480, 640, CV_8UC3);        // unsigned char, 3-channels
    Mat img4(Size(640, 480), CV_8UC3);  // Size(width, height)

    Mat img5(480, 640, CV_8UC1, Scalar(128));           // initial values, 128
    Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));     // initial values, red

    Mat mat1 = Mat::zeros(3, 3, CV_32SC1);  // 0's matrix
    Mat mat2 = Mat::ones(3, 3, CV_32FC1);   // 1's matrix
    Mat mat3 = Mat::eye(3, 3, CV_32FC1);    // identity matrix

    float data[] = { 1,2,3,4,5,6 };
    Mat mat4(2, 3, CV_32FC1, data);

    Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
    Mat mat6 = Mat_<uchar>({ 2, 3 }, { 1, 2, 3, 4, 5, 6 });

    mat4.create(256, 256, CV_8UC3);
    mat5.create(4, 4, CV_32FC1);

    mat4 = Scalar(255, 0, 0);
    mat5.setTo(1.f);
}

void MatOp2(void)
{
    Mat img1 = imread("img/dog.bmp");
    
    Mat img2 = img1;
    Mat img3;
    img3 = img1;

    Mat img4 = img1.clone();
    Mat img5;
    img1.copyTo(img5);

    img1.setTo(Scalar(0, 255, 255));    // yellow

    imshow("img1", img1);
    imshow("img2", img2);
    imshow("img3", img3);
    imshow("img4", img4);
    imshow("img5", img5);

    waitKey();
    destroyAllWindows();
}
