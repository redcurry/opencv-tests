#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    const int K = 2;

    string inputFileName(argv[1]);
    Mat imgOriginal = imread(inputFileName, 1);

    Mat img;
    if (imgOriginal.rows < imgOriginal.cols)
        resize(imgOriginal, img, Size(640, 480));
    else
        resize(imgOriginal, img, Size(480, 640));

    Mat hsv;
    cvtColor(img, hsv, CV_BGR2HSV);

    vector<Mat> channels;
    split(hsv, channels);

    imwrite("s-" + inputFileName, channels[1]);

    Mat h, s, v;
//    channels[0].convertTo(h, CV_32F);
    channels[1].convertTo(s, CV_32F);
    channels[2].convertTo(v, CV_32F);

    vector<float> harray, sarray, varray;
//    harray.assign((float*)h.datastart, (float*)h.dataend);
    sarray.assign((float*)s.datastart, (float*)s.dataend);
    varray.assign((float*)v.datastart, (float*)v.dataend);

    vector<Point2f> farray;
    for (int i = 0; i < sarray.size(); i++)
    {
        farray.push_back(Point2f(sarray[i] * (255 - varray[i]), 0.0));
    }

    Mat centers;
    vector<int> labels;

    kmeans(farray, K, labels,
        TermCriteria(TermCriteria::COUNT, 100, 1.0),
           3, KMEANS_PP_CENTERS, centers);

    vector<uchar> labs;
    for (int i = 0; i < labels.size(); i++)
        labs.push_back((uchar)(labels[i] * 255));

    int rows = img.rows;
    int cols = img.cols;

    Mat m = Mat(rows, cols, CV_8UC1);
    memcpy(m.data, labs.data(), labs.size() * sizeof(uchar));

    imwrite("new-" + inputFileName, m);

    cout << centers << endl;

    return 0;
}
