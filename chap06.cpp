#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void imgAdd();
void cameraDiff();

int main(void)
{
    // imgAdd();
    cameraDiff();

    return 0;
}

void imgAdd()
{
    Mat src1 = imread("img/camera.bmp", IMREAD_GRAYSCALE);
    Mat src2 = imread("img/dog.bmp", IMREAD_GRAYSCALE);

    Mat dst1, dst2;

    add(src1, src2, dst1);
    addWeighted(src1, 0.5, src2, 0.5, 0, dst2);

    imshow("dst1_simple", dst1);
    imshow("dst2_weighted", dst2);

    waitKey();
    destroyAllWindows();
}

void cameraDiff()
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Camera open failed!" << endl;
        return;
    }

    Mat orig_frame, live_frame, diff_frame;

    cap >> orig_frame;
    cvtColor(orig_frame, orig_frame, COLOR_BGR2GRAY);
    while (true)
    {
        cap >> live_frame;
        cvtColor(live_frame, live_frame, COLOR_BGR2GRAY);

        absdiff(orig_frame, live_frame, diff_frame);

        imshow("live", live_frame);
        imshow("diff", diff_frame);

        if (waitKey(10) == 'q')
        {
            break;
        }
    }
    destroyAllWindows();
}
