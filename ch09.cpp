#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/// Function Declarations
void sobel_edge();
void canny_edge();
void hough_lines();
void hough_line_segments();
void hough_circles();
void coin_calc();
void readData();

int won500max, won100max, won50max, won10max;
int won500min, won100min, won50min, won10min;

int main(void)
{
    // sobel_edge();
    // canny_edge();
    // hough_lines();
    // hough_line_segments();
    // hough_circles();

    readData();
    coin_calc();

    waitKey();
    destroyAllWindows();

    return 0;
}

/// Function Definitions
void sobel_edge()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dx, dy;
    Sobel(src, dx, CV_32FC1, 1, 0);
    Sobel(src, dy, CV_32FC1, 0, 1);

    Mat fmag, mag;
    magnitude(dx, dy, fmag);
    fmag.convertTo(mag, CV_8UC1);

    Mat edge = mag > 150;

    imshow("src", src);
    imshow("mag", mag);
    imshow("edge", edge);
}

void canny_edge()
{
    Mat src = imread("img/lenna.bmp", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat dst1, dst2;
    Canny(src, dst1, 50, 100);
    Canny(src, dst2, 50, 150);

    imshow("src", src);
    imshow("dst1", dst1);
    imshow("dst2", dst2);
}

void hough_lines()
{
    Mat src = imread("img/building.jpg", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat edge;
    Canny(src, edge, 50, 150);

    vector<Vec2f> lines;
    // use canny_edge image, pixel resolution = 1, degree = 1, threshold 250
    HoughLines(edge, lines, 1, CV_PI / 180, 250);

    Mat dst;
    cvtColor(edge, dst, COLOR_GRAY2BGR);

    for (size_t i = 0; i < lines.size(); i++)
    {
        float r = lines[i][0];  // rho for each line
        float t = lines[i][1];  // theta for each line
        double cos_t = cos(t), sin_t = sin(t);  // calc cos(t) & sin(t)
        double x0 = r * cos_t, y0 = r * sin_t;  // calc x0, y0 from rho, theta
        double alpha = 1000;    // offset to calculate 2 points from single pt
        Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
        Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
        line(dst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
    }

    imshow("src", src);
    imshow("dst", dst);
}

void hough_line_segments()
{
    Mat src = imread("img/building.jpg", IMREAD_GRAYSCALE);
    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat edge;
    Canny(src, edge, 50, 150);

    vector<Vec4i> lines;
    HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);

    Mat dst;
    cvtColor(edge, dst, COLOR_GRAY2BGR);

    for (Vec4i l : lines)
    {
        line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
    }

    imshow("src", src);
    imshow("dst", dst);
}

void hough_circles()
{
    Mat src = imread("img/coins.png", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    Mat blurred;
    blur(src, blurred, Size(3, 3));

    vector<Vec3f> circles;
    HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (Vec3f c : circles)
    {
        Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);
        circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
    }

    imshow("src", src);
    imshow("dst", dst);
}

void coin_calc()
{
    VideoCapture cap(0);

    cap.set(CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(CAP_PROP_FRAME_HEIGHT, 1080);

    if (cap.isOpened() == false)
    {
        cout << "Error opening camera!" << endl;
        return;
    }

    cout << cap.get(CAP_PROP_FRAME_WIDTH) << endl;

    Mat frame, img;
    while (true)
    {
        cap >> frame;
        cvtColor(frame, img, COLOR_BGR2GRAY);     // convert feed to grayscale

        // drawMarker(img, Point(600, 100), Scalar(255));
        // drawMarker(img, Point(1200, 700), Scalar(255));
        img = img(Rect(Point(600, 100), Point(1200, 700)));   // crop feed
        // resize(img, img, Size(), 2, 2);


        vector<Vec3f> circles;
        HoughCircles(img, circles, HOUGH_GRADIENT, 1, 25, 200, 20, 20, 45);

        Mat dst;
        cvtColor(img, dst, COLOR_GRAY2BGR);

        // Canny(img, dst, 100, 150);
        int coin_sum = 0;
        String value;

        for (Vec3f c : circles)
        {
            Point center(cvRound(c[0]), cvRound(c[1]));
            int radius = cvRound(c[2]);
            circle(dst, center, radius, Scalar(0, 0, 255), 1, LINE_AA);

            if (radius >= won500min && radius <= won500max)
            {
                value = "500";
                coin_sum += 500;
            }
            if (radius >= won100min && radius <= won100max)
            {
                value = "100";
                coin_sum += 100;
            }
            if (radius >= won50min && radius <= won50max)
            {
                value = "50";
                coin_sum += 50;
            }
            if (radius >= won10min && radius <= won10max)
            {
                value = "10";
                coin_sum += 10;
            }

            // String txt = format("radius: %d", radius);
            // putText(dst, txt, center, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255));
            putText(dst, value, center, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 0), 2);
        }

        String coin_txt = format("%d", coin_sum);

        putText(dst, coin_txt, Point(10, 20), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 255), 2);

        imshow("image", img);
        imshow("dst", dst);

        if (waitKey(200) == 'q')
            break;
    }
}

void readData()
{
    FileStorage fs("coins.json", FileStorage::READ);

    if (!fs.isOpened())
    {
        cerr << "File open failed!" << endl;
        exit(-1);
    }

    fs["won500max"] >> won500max;
    fs["won500min"] >> won500min;
    fs["won100max"] >> won100max;
    fs["won100min"] >> won100min;
    fs["won50max"] >> won50max;
    fs["won50min"] >> won50min;
    fs["won10max"] >> won10max;
    fs["won10min"] >> won10min;

    cout << "500: " << won500max << endl;
    cout << "500: " << won500min << endl;
    cout << "100: " << won100max << endl;
    cout << "100: " << won100min << endl;
    cout << "50: " << won50max << endl;
    cout << "50: " << won50min << endl;
    cout << "10: " << won10max << endl;
    cout << "10: " << won10min << endl;

    fs.release();
}
