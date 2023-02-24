#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void color_inverse();
void color_split();
void color_eq();

// HSV color segmentation
void color_segmentation();
void on_hue_changed(int, void *);

void hist_backproj();
void hist_backproj_nomask();
void mouseCallback(int event, int x, int y, int flags, void *userdata);
void get_backproj_img();
#define HIST_BACKPROJ

#ifdef COLOR_SEG
int lower_hue = 40, upper_hue = 80;
Mat src, src_hsv, mask;
#endif

#ifdef HIST_BACKPROJ
Mat ref_img, ref_ycrcb, mask;
Mat hist, dst_backproj;
Mat src, src_ycrcb;
#endif

int main(void)
{
    // color_inverse();
    // color_split();
    // color_eq();
    // color_segmentation();
    // hist_backproj();

    hist_backproj_nomask();

    waitKey();
    destroyAllWindows();

    return 0;
}

/// Function Definitions
void color_inverse()
{
    Mat src = imread("img/butterfly.jpg");

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    // Mat dst(src.rows, src.cols, src.type());

    // for (int j = 0; j < src.rows; j++)
    // {
    //     for (int i = 0; i < src.cols; i++)
    //     {
    //         Vec3b &p1 = src.at<Vec3b>(j, i);
    //         Vec3b &p2 = dst.at<Vec3b>(j, i);

    //         p2[0] = 255 - p1[0];    // B
    //         p2[1] = 255 - p1[1];    // G
    //         p2[2] = 255 - p1[2];    // R
    //     }
    // }

    // simpler form
    // for (int j = 0; j < src.rows; j++)
    // {
    //     for (int i = 0; i < src.cols; i++)
    //     {
    //         dst.at<Vec3b>(j, i) = Vec3b(255, 255, 255) - src.at<Vec3b>(j, i);
    //     }
    // }

    // simplest form
    Mat dst = ~src;


    imshow("src", src);
    imshow("dst", dst);
}

void color_split()
{
    Mat src = imread("img/candies.png");

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    vector<Mat> bgr_planes;
    split(src, bgr_planes);

    imshow("src", src);
    imshow("B_plane", bgr_planes[0]);
    imshow("G_plane", bgr_planes[1]);
    imshow("R_plane", bgr_planes[2]);

    Mat yellow = 0.7 * bgr_planes[1] + 0.3 * bgr_planes[2];
    imshow("yellow", yellow);

    Mat yellow_bi;
    threshold(yellow, yellow_bi, 190, 255, THRESH_BINARY);
    imshow("yellow_bi", yellow_bi);

    // Mat yellowMM(src.rows, src.cols, src.type());
    Mat yellowMM;
    src.copyTo(yellowMM, yellow_bi);
    imshow("yMM", yellowMM);

    waitKey();
    destroyAllWindows();
}

void color_eq()
{
    Mat src = imread("img/pepper.bmp", IMREAD_COLOR);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat src_ycrcb;
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    vector<Mat> ycrcb_planes;
    split(src_ycrcb, ycrcb_planes);

    equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); // Y channel
    // normalize(ycrcb_planes[0], ycrcb_planes[0], 0, 255, NORM_MINMAX);

    Mat dst_ycrcb;
    merge(ycrcb_planes, dst_ycrcb);

    Mat dst;
    cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

    imshow("src", src);
    imshow("dst", dst);
}

#ifdef COLOR_SEG // COLOR_SEG requires global vars
void color_segmentation()
{
    src = imread("img/candies.png", IMREAD_COLOR);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    src_hsv;
    cvtColor(src, src_hsv, COLOR_BGR2HSV);

    imshow("src", src);

    namedWindow("mask");
    createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
    createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
    on_hue_changed(0, 0);

    waitKey();
    return;
}

void on_hue_changed(int, void *)
{
    Scalar lowerb(lower_hue, 100, 0);
    Scalar upperb(upper_hue, 255, 255);
    inRange(src_hsv, lowerb, upperb, mask);

    imshow("mask", mask);
}
#endif // END_COLOR_SEG

void hist_backproj()
{
    // Calculate CrCb histogram from reference image
    Mat ref, ref_ycrcb, mask;
    ref = imread("img/ref.png", IMREAD_COLOR);
    mask = imread("img/mask.bmp", IMREAD_GRAYSCALE);
    if (ref.empty() || mask.empty())
    {
        cerr << "Ref image load failed!" << endl;
        return;
    }
    cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

    Mat hist;
    int channels[] = {1, 2};
    int cr_bins = 128, cb_bins = 128;
    int histSize[] = {cr_bins, cb_bins};
    float cr_range[] = {0, 256};
    float cb_range[] = {0, 256};
    const float *ranges[] = {cr_range, cb_range};

    calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

    // Apply histogram backprojection to input image
    Mat src, src_ycrcb;
    src = imread("img/kids.png", IMREAD_COLOR);
    if (src.empty())
    {
        cerr << "Src image load failed!" << endl;
        return;
    }
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    Mat backproj;
    calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

    imshow("src", src);
    imshow("backproj", backproj);
}

#ifdef HIST_BACKPROJ
void hist_backproj_nomask()
{
    // load ref image
    ref_img = imread("img/ref.png", IMREAD_COLOR);
    if (ref_img.empty())
    {
        cerr << "Reference image load failed!" << endl;
        return;
    }
    cvtColor(ref_img, ref_ycrcb, COLOR_BGR2YCrCb);

    // set correct type for Mat mask & init
    // mask.create(ref_img.rows, ref_img.cols, CV_8UC1);
    // mask.setTo(0);
    mask = Mat::zeros(ref_img.size(), CV_8UC1);

    namedWindow("ref_image");
    setMouseCallback("ref_image", mouseCallback);
    imshow("ref_image", ref_img);

}

void mouseCallback(int event, int x, int y, int flags, void *userdata)
{
    static Mat ref_clone = ref_img.clone();
    static vector<Point2i> poly;  // store mouse clicks

    // left click
    if (event == EVENT_LBUTTONDOWN)
    {
        circle(ref_clone, Point(x, y), 5, Scalar(0, 0, 255), -1);  // draw circle @ click
        if (poly.size() > 0)    // draw connecting line
        {
            line(ref_clone, poly.back(), Point(x, y), Scalar(0, 0, 255));
        }
        poly.push_back(Point(x, y));    // store click
    }
    // right click - connect lines & create mask polygon
    if (event == EVENT_RBUTTONDOWN)
    {
        line(ref_clone, poly.front(), poly.back(), Scalar(0, 0, 255));
        fillPoly(mask, poly, Scalar(255));
        poly.clear();
        imshow("mask", mask);
        get_backproj_img();
    }
    // middle click - reset mask & polygon
    if (event == EVENT_MBUTTONDOWN)
    {
        poly.clear();
        ref_clone = ref_img.clone();
        mask.setTo(0);
    }

    imshow("ref_image", ref_clone);
}

void get_backproj_img()
{
    int channels[] = {1,2};
    int cr_bins = 128, cb_bins = 128;
    int histSize[] = {cr_bins, cb_bins};
    float cr_range[] = {0, 256};
    float cb_range[] = {0, 256};
    const float *ranges[] = {cr_range, cb_range};

    calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

    src = imread("img/kids.png", IMREAD_COLOR);
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    calcBackProject(&src_ycrcb, 1, channels, hist, dst_backproj, ranges, 1, true);

    imshow("backproj", dst_backproj);
    imshow("histogram", hist);
}
#endif
