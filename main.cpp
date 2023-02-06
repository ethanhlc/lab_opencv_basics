#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void camera_in();
void video_in();

int main()
{
    // camera_in();
    video_in();

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
