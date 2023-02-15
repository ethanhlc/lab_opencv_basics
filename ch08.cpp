#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void affine_transform();
void affine_translate();
void affine_shear();
void affine_scale();    // resize

int main(void)
{
    // affine_transform();
    // affine_translate();
    // affine_shear();
    affine_scale();

    return 0;
}

/// Function Definitions
void affine_transform()
{
    Mat src = imread("img/tekapo.bmp");

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Point2f srcPts[3], dstPts[3];
    srcPts[0] = Point2f(0, 0);
    srcPts[1] = Point2f(src.cols - 1, 0);
    srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
    dstPts[0] = Point2f(50, 50);
    dstPts[1] = Point2f(src.cols - 100, 100);
    dstPts[2] = Point2f(src.cols - 50, src.rows - 50);

    // get transformation matrix from src/dst Points
    Mat M = getAffineTransform(srcPts, dstPts);

    // apply transformation to img
    Mat dst;
    warpAffine(src, dst, M, Size(0, 0), INTER_LINEAR);

    imshow("src", src);
    imshow("dst", dst);

    // get transformation of specific points using M transform matrix
    vector<Point2f> source = {Point2f(0,0), Point2f(639,0), Point2f(639, 479)};
    vector<Point2f> destination;
    transform(source, destination, M);
    cout << source << endl;
    cout << destination << endl;

    waitKey();
    destroyAllWindows();
}

void affine_translate()
{
    Mat src = imread("img/tekapo.bmp");

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat M = Mat_<double>({2,3}, {1, 0, 150, 0, 1, 100});

    Mat dst;
    warpAffine(src, dst, M, Size(0, 0));
    // warpAffine(src, dst, M, Size(800, 600), 1, 0, Scalar(255, 255, 0));
    // warpAffine(src, dst, M, Size(0, 0), INTER_LINEAR, BORDER_REFLECT_101);

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}

void affine_shear()
{
    Mat src = imread("img/tekapo.bmp");

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    double mx = 0.3;
    Mat Mx = Mat_<double>({2,3}, {1, mx, 0, 0, 1, 0});

    double my = 0.3;
    Mat My = Mat_<double>({2,3}, {1, 0, 0, my, 1, 0});

    Mat dst_x, dst_y;
    warpAffine(src, dst_x, Mx, Size(src.cols + mx * src.rows, src.rows));
    warpAffine(src, dst_y, My, Size(src.cols, src.rows + my * src.cols));

    imshow("src", src);
    imshow("dst_x", dst_x);
    imshow("dst_y", dst_y);

    waitKey();
    destroyAllWindows();
}

void affine_scale()
{
    Mat src = imread("img/rose.bmp");

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dst1, dst2, dst3, dst4;
    resize(src, dst1, Size(0, 0), 4, 4, INTER_NEAREST);
    resize(src, dst2, Size(1920, 1280));    // INTER_LINEAR
    resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
    resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

    imshow("src", src);
    imshow("dst1", dst1(Rect(400, 500, 400, 400)));
    imshow("dst2", dst2(Rect(400, 500, 400, 400)));
    imshow("dst3", dst3(Rect(400, 500, 400, 400)));
    imshow("dst4", dst4(Rect(400, 500, 400, 400)));

    waitKey();
    destroyAllWindows();
}
