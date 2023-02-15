#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void affine_transform();

int main(void)
{
    affine_transform();

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
