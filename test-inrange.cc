#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    string inputFileName(argv[1]);
    Mat imgOriginal = imread(inputFileName, 1);

    Mat img;

    if (imgOriginal.rows < imgOriginal.cols)
        resize(imgOriginal, img, Size(640, 480));
    else
        resize(imgOriginal, img, Size(480, 640));

    Mat hsv;
    cvtColor(img, hsv, CV_BGR2HSV);

    int low_h = 0;
    int hi_h  = 360;
    int low_s = 20;
    int hi_s  = 255;
    int low_v = 0;
    int hi_v  = 255;

    auto low = Scalar(low_h, low_s, low_v);
    auto hi  = Scalar(hi_h, hi_s, hi_v);

    Mat hsv_binary;
    inRange(hsv, low, hi, hsv_binary);

    imwrite("new-" + inputFileName, hsv_binary);

    return 0;
}
