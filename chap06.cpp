#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void imgAdd();
void cameraDiff();
void logicalOp();

int main(void)
{
    // imgAdd();
    // cameraDiff();
    logicalOp();

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

        char keypress = waitKey(10);
        if (keypress == 'q')
        {
            break;
        }
        else if (keypress == 's')
        {
            cap >> orig_frame;
            cvtColor(orig_frame, orig_frame, COLOR_BGR2GRAY);
        }
    }
    destroyAllWindows();
}

void logicalOp()
{
    Mat src1 = imread("img/lenna256.bmp", IMREAD_GRAYSCALE);
    Mat src2 = imread("img/square.bmp", IMREAD_GRAYSCALE);

    if (src1.empty() || src2.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    imshow("src1", src1);
    imshow("src2", src2);

    Mat dst1, dst2, dst3, dst4;

    bitwise_and(src1, src2, dst1);
    bitwise_or(src1, src2, dst2);
    bitwise_xor(src1, src2, dst3);
    bitwise_not(src1, dst4);

    imshow("dst1", dst1);
    cout << "src1 AND src2" << endl;
    waitKey();
    imshow("dst2", dst2);
    cout << "src1 OR src2" << endl;
    waitKey();
    imshow("dst3", dst3);
    cout << "src1 XOR src2" << endl;
    waitKey();
    imshow("dst4", dst4);
    cout << "NOT src1" << endl;

    waitKey();
    destroyAllWindows();
}
