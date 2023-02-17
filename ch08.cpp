#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void affine_transform();
void affine_translate();
void affine_shear();
void affine_scale();    // resize
void affine_rotation();
void affine_flip();
void perspective();
void on_Mouse(int event, int x, int y, int flags, void *userdata);

Point2f srcQuad[4];     // src points for perpective warp

int main(void)
{
    // affine_transform();
    // affine_translate();
    // affine_shear();
    // affine_scale();
    // affine_rotation();
    // affine_flip();
    perspective();

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

void affine_rotation()
{
    Mat src = imread("img/tekapo.bmp", IMREAD_COLOR);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    double degrees = 20.0;

    Mat M = getRotationMatrix2D(Point2f(src.cols / 2, src.rows / 2), degrees, 1);

    Mat dst_orig, dst_resize;
    warpAffine(src, dst_orig, M, Size(0, 0));

    // double radians = degrees * 3.14159265 / 180.0;     // cvt degrees to rad

    // // calculate new img size
    // Size_<double> imgsize(src.cols * cos(radians) + src.rows * sin(radians),
    //                       src.rows * cos(radians) + src.cols * sin(radians));

    // alternate method to get image size
    vector<Point2f> srcPts = {Point(0, 0), Point(src.cols - 1, src.rows - 1),
                              Point(src.cols - 1, 0), Point(0, src.rows - 1)};
    vector<Point2f> dstPts;
    transform(srcPts, dstPts, M);

    Size_<double> imgsize(dstPts[1].x - dstPts[0].x, dstPts[3].y - dstPts[2].y);

    // resize image
    Mat M_translate = Mat_<double>({2,3}, {1, 0, (imgsize.width - src.cols) / 2.0, 0, 1, (imgsize.height - src.rows) / 2.0});
    warpAffine(src, dst_resize, M_translate, imgsize);

    // rotate image
    Mat M_resize = getRotationMatrix2D(Point2f(dst_resize.cols / 2, dst_resize.rows / 2), degrees, 1);
    warpAffine(dst_resize, dst_resize, M_resize, Size(0, 0));


    cout << M << endl;

    imshow("src", src);
    imshow("dst_noresize", dst_orig);
    imshow("dst_resize", dst_resize);

    waitKey();
    destroyAllWindows();
}

void affine_flip()
{
    Mat src = imread("img/tekapo.bmp", IMREAD_COLOR);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    imshow("src", src);

    Mat dst;
    int flipCode[] = {1, 0, -1};
    for (int i = 0; i < 3; i++)
    {
        flip(src, dst, flipCode[i]);

        String desc = format("flipCode: %d", flipCode[i]);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0,
                Scalar(255, 0, 0), 1, LINE_AA);

        imshow(desc, dst);
        waitKey();
    }

    destroyAllWindows();
}

void perspective()
{
    Mat src = imread("img/card.bmp");

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    namedWindow("src");
    setMouseCallback("src", on_Mouse, &src);

    imshow("src", src);

    waitKey();
    destroyAllWindows();
}

void on_Mouse(int event, int x, int y, int flags, void *userdata)
{
    static int cnt = 0;
    int w = 200;
    int h = 300;

    static Mat src = (*(Mat *)userdata).clone();

    Point2f dstQuad[4] = {Point2f(0, 0),
                          Point2f(w - 1, 0),
                          Point2f(w - 1, h - 1),
                          Point2f(0, h - 1)};

    if (event == EVENT_LBUTTONDOWN)
    {
        if (cnt < 4)
        {
            srcQuad[cnt++] = Point2f(x, y);

            circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1);
            imshow("src", src);

            if (cnt == 4)
            {
                Mat pers = getPerspectiveTransform(srcQuad, dstQuad);

                Mat dst;
                warpPerspective(*(Mat *)userdata, dst, pers, Size(w, h));

                imshow("dst", dst);

                // reset
                cnt = 0;
                src = (*(Mat *)userdata).clone();
            }
        }
    }
}
