#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void camera_in();
void video_in();
void camera_in_video_out();
void drawLines();

int main()
{
    // camera_in();
    // video_in();
    // camera_in_video_out();
    drawLines();

    return 0;
}

void camera_in()
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Camera open failed!" << endl;
        return;
    }

    cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
    cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

    Mat frame, inversed;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        inversed = ~frame;

        imshow("frame", frame);
        imshow("inversed", inversed);

        if (waitKey(10) == 27)      // ESC key
            break;
    }

    destroyAllWindows();
}

void video_in()
{
    VideoCapture cap("img/stopwatch.avi");

    if (!cap.isOpened())
    {
        cerr << "Video open failed!" << endl;
        return;
    }

    cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
    cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
    cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;

    double fps = cap.get(CAP_PROP_FPS);
    cout << "FPS: " << fps << endl;

    int delay = cvRound(1000 / fps);

    Mat frame, inversed;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        inversed = ~frame;

        imshow("frame", frame);
        imshow("inversed", inversed);

        if (waitKey(delay) == 27)      // ESC key
            break;
    }

    destroyAllWindows();
}

void camera_in_video_out()
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Camera open failed!" << endl;
        return;
    }

    int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
    int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
    // double fps = cvRound(cap.get(CAP_PROP_FPS));
    double fps = 30;

    int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
    int delay = cvRound(1000 / fps);

    VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

    if (!outputVideo.isOpened())
    {
        cout << "File open failed!" << endl;
        return;
    }

    Mat frame, inversed;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        inversed = ~frame;
        outputVideo << inversed;

        imshow("frame", frame);
        imshow("inversed", inversed);

        if (waitKey(delay) == 27)
            break;
    }

    destroyAllWindows();
}

void drawLines()
{
    Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

    line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));
    line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);
    line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);

    line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
    line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
    line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);

    arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);
    arrowedLine(img, Point(50, 250), Point(350, 250), Scalar(255, 0, 255), 1);
    arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05);

    drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);
    drawMarker(img, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS);
    drawMarker(img, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);
    drawMarker(img, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);
    drawMarker(img, Point(250, 350), Scalar(0, 0, 255), MARKER_SQUARE);
    drawMarker(img, Point(300, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_UP);
    drawMarker(img, Point(350, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_DOWN);

    imshow("img", img);
    waitKey(0);

    destroyAllWindows();
}
