#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void brightness1();
void brightness2();
void brightness3();
void brightness4();
void on_brightness(int pos, void *userdata);

void contrast1();
void contrast2();
void contrast_trackbar();
void on_contrast(int pos, void *userdata);

Mat calcGrayHist(const Mat &img);
Mat getGrayHistImage(const Mat &hist);
Mat getColorHistImage(const Mat &hist, char color, double histMax);
void drawHistogram();
void drawColorHistogram();
void histogramStretching();
void histogramEqualization();

int main(void)
{
    // brightness1();
    // brightness2();
    // brightness3();
    // brightness4();

    // contrast1();
    // contrast2();
    // contrast_trackbar();

    // drawHistogram();
    // drawColorHistogram();
    // histogramStretching();
    histogramEqualization();

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

void brightness2()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    // create empty Mat object
    Mat dst(src.rows, src.cols, src.type());

    // manually iterate through & add value (saturation not considered)
    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            dst.at<uchar>(j, i) = src.at<uchar>(j, i) - 100;
        }
    }

    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    destroyAllWindows();
}

void brightness3()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dst(src.rows, src.cols, src.type());

    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            // add saturation check to manual iteration
            // int v = src.at<uchar>(j, i) + 100;
            // dst.at<uchar>(j, i) = v > 255 ? 255 : v < 0 ? 0 : v;
            dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
        }
    }

    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    destroyAllWindows();
}

void brightness4()
{
    Mat img = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    namedWindow("img");
    createTrackbar("Brightness", "img", NULL, 100, on_brightness, &img);
    on_brightness(0, &img);

    waitKey();
    destroyAllWindows();
}

void on_brightness(int pos, void *userdata)
{
    Mat src = *(Mat *)userdata;
    Mat dst = src + pos;
    // *(Mat *)userdata = *(Mat *)userdata + pos;   // wrong, constant inc in brightness

    imshow("img", dst);
}

void contrast1()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    float s = 2.f;
    Mat dst = s * src;

    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    destroyAllWindows();
}

void contrast2()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    float alpha = 1.f;
    Mat dst = src + (src - 128) * alpha;

    imshow("src", src);
    imshow("dst", dst);
    waitKey();

    destroyAllWindows();
}

void contrast_trackbar()
{
    Mat img = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    namedWindow("img");
    createTrackbar("Contrast", "img", NULL, 100, on_contrast, &img);
    on_contrast(50, &img);

    waitKey();
    destroyAllWindows();
}

void on_contrast(int pos, void *userdata)
{
    Mat src = *(Mat *)userdata;
    float fpos = pos;

    if (fpos < 51)
    {
        fpos = fpos - 50;
        fpos = fpos / 50;
    }
    else
    {
        fpos = fpos - 50;
        fpos = fpos / 10;
    }

    Mat dst = src + (src - 128) * fpos;

    imshow("img", dst);
}

Mat calcGrayHist(const Mat &img)
{
    CV_Assert(img.type() == CV_8UC1);

    Mat hist;
    int channels[] = {0};
    int dims = 1;
    const int histSize[] = {256};
    float graylevel[] = {0, 256};
    const float *ranges[] = {graylevel};

    calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

    return hist;
}

Mat getGrayHistImage(const Mat &hist)
{
    CV_Assert(hist.type() == CV_32FC1);
    CV_Assert(hist.size() == Size(1, 256));

    double histMax;
    minMaxLoc(hist, NULL, &histMax);

    Mat imgHist(100, 256, CV_8UC1, Scalar(255));
    for (int i = 0; i < 256; i++)
    {
        line(imgHist, Point(i, 100),
             Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
    }

    return imgHist;
}

Mat getColorHistImage(const Mat &hist, char color, double histMax)
{
    CV_Assert(hist.type() == CV_32FC1);
    CV_Assert(hist.size() == Size(1, 256));

    // double histMax;
    // minMaxLoc(hist, NULL, &histMax);

    Mat imgHist(100, 256, CV_8UC3, Scalar(255, 255, 255));
    for (int i = 0; i < 256; i++)
    {
        if (color == 'b')
            line(imgHist, Point(i, 100),
                 Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(255, 0, 0));
        else if (color == 'g')
            line(imgHist, Point(i, 100),
                 Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0, 255, 0));
        else if (color == 'r')
            line(imgHist, Point(i, 100),
                 Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0, 0, 255));
    }

    return imgHist;
}

void drawHistogram()
{
    Mat img = imread("img/camera.bmp", IMREAD_GRAYSCALE);

    if (img.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat hist = calcGrayHist(img);
    Mat hist_img = getGrayHistImage(hist);

    imshow("img", img);
    imshow("histogram", hist_img);
    // imshow("histogram", getGrayHistImage(calcGrayHist(img));

    waitKey();
    destroyAllWindows();
}

void drawColorHistogram()
{
    Mat img = imread("img/lenna.bmp", IMREAD_COLOR);

    if (img.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    // split channels into separate Mat objects
    vector<Mat> bgr_lenna;
    split(img, bgr_lenna);

    // get max hist value (draw correctly weighted histograms)
    Mat hist_b = calcGrayHist(bgr_lenna[0]);
    Mat hist_g = calcGrayHist(bgr_lenna[1]);
    Mat hist_r = calcGrayHist(bgr_lenna[2]);

    double histMax;
    double histMax_color[3];
    minMaxLoc(hist_b, NULL, &histMax_color[0]);
    minMaxLoc(hist_g, NULL, &histMax_color[1]);
    minMaxLoc(hist_r, NULL, &histMax_color[2]);

    histMax = histMax_color[0];
    for (int i = 1; i < 3; i++)
    {
        if (histMax_color[i] > histMax)
            histMax = histMax_color[i];
    }

    imshow("lenna", img);
    imshow("hist_blue", getColorHistImage(hist_b, 'b', histMax));
    imshow("hist_green", getColorHistImage(hist_g, 'g', histMax));
    imshow("hist_red", getColorHistImage(hist_r, 'r', histMax));

    waitKey();
    destroyAllWindows();
}

void histogramStretching()  // basically normalization
{
    Mat src = imread("img/hawkes.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    double gmin, gmax;
    minMaxLoc(src, &gmin, &gmax);

    Mat dst = (src - gmin) * 255 / (gmax - gmin);

    imshow("src", src);
    imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

    imshow("dst", dst);
    imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

    Mat img_norm;
    normalize(src, img_norm, 0, 255, NORM_MINMAX);
    imshow("norm", img_norm);
    imshow("normHist", getGrayHistImage(calcGrayHist(img_norm)));

    // use absdiff() to calculate difference between images
    // Mat img_diff;
    // double maxdiff;
    // absdiff(dst, img_norm, img_diff);
    // imshow("diff", img_diff);

    // minMaxLoc(img_diff, NULL, &maxdiff);
    // cout << "Max diff: " << maxdiff << endl;    // print max difference value

    waitKey();
    destroyAllWindows();
}

void histogramEqualization()
{
    Mat src = imread("img/hawkes.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dst;
    equalizeHist(src, dst);

    imshow("src", src);
    imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

    imshow("dst", dst);
    imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

    waitKey();
    destroyAllWindows();
}
