#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/highgui/highgui_c.h"
using namespace cv;


struct CannyData {
    Mat img;
    int canny_1;
    int canny_2;
};


void updateCanny1(int canny_1, void* param);
void updateCanny2(int canny_2, void* param);


int main(int argc, char* argv[])
{
  srand(time(0));

  string inputFileName(argv[1]);

  // Canny parameters
  int canny_1 = atoi(argv[2]);
  int canny_2 = atoi(argv[3]);
  int id = atoi(argv[4]);

  Mat imgOriginal = imread(inputFileName, 0);

  if(imgOriginal.empty())
    return -1;

  Mat img;
  resize(imgOriginal, img, Size(640, 480));

  namedWindow("Original", WINDOW_NORMAL);
  resizeWindow("Original", 640, 480);
  imshow("Original", img);

  // Log transformation
  double c = 45.98591;
  Mat temp(img.size().width, img.size().height, CV_32F);
  img.convertTo(temp, CV_32F);
  Mat temp2 = temp + 1.0;
  log(temp, temp2);
  temp = temp2 * c;
  temp.convertTo(img, CV_8U);
  namedWindow("Log", WINDOW_NORMAL);
  resizeWindow("Log", 640, 480);
  imshow("Log", img);

  medianBlur(img, img, 7);

  namedWindow("Median", WINDOW_NORMAL);
  resizeWindow("Median", 640, 480);
  imshow("Median", img);
/*
  Mat temp;
  morphologyEx(img, img, MORPH_CLOSE, temp, Point(-1, -1), 5);
  namedWindow("Morphology", WINDOW_NORMAL);
  resizeWindow("Morphology", 640, 480);
  imshow("Morphology", img);
*/

  namedWindow("Canny", WINDOW_NORMAL);
  resizeWindow("Canny", 640, 480);

/* CANNY TRACKBAR
  CannyData cannyData;
  cannyData.img = img;
  cannyData.canny_1 = canny_1;
  cannyData.canny_2 = canny_2;
  createTrackbar("Canny1", "Canny", &(cannyData.canny_1), 255, updateCanny1,
          &cannyData);
  createTrackbar("Canny2", "Canny", &(cannyData.canny_2), 255, updateCanny2,
          &cannyData);
*/

    Canny(img, img, canny_1, canny_2);
    Mat cannyTemp;
    morphologyEx(img, img, MORPH_CLOSE, cannyTemp, Point(-1, -1), 5);
    imshow("Canny", img);

  vector< vector<Point> > contours;
  findContours(img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  cout << "Number of contours detected: " << contours.size() << endl;
  
  Mat imgContour = Mat::zeros(img.rows, img.cols, CV_8UC3);

  Scalar color(rand() % 255, rand() % 255, rand() % 255);
  drawContours(imgContour, contours, -1, color, 1);
  //imwrite(string("out.png"), imgContour);

//  for (int i = 0; i < contours[atoi(argv[4])].size(); i++)
//    cout << contours[atoi(argv[4])][i].x << " " << contours[atoi(argv[4])][i].y << "\n";

  namedWindow("Contours", WINDOW_NORMAL);
  resizeWindow("Contours", 640, 480);
  imshow("Contours", imgContour);

  // Output contour areas and nearest distance from center
  for (int i = 0; i < contours.size(); i++)
  {
    cout << "Area " << i << ": " << contourArea(contours[i]) << ", "
         << "Dist from center: "
         << pointPolygonTest(contours[i], Point(320, 240), true) << endl;
  }

  waitKey( 0 );
}


void updateCanny1(int canny_1, void* param)
{
    cout << canny_1 << endl;
    CannyData* cannyData = (CannyData*)param;
    Mat cannyImg;
    Canny(cannyData->img, cannyImg, canny_1, cannyData->canny_2);
    Mat temp;
    morphologyEx(cannyImg, cannyImg, MORPH_CLOSE, temp, Point(-1, -1), 5);
    imshow("Canny", cannyImg);
}


void updateCanny2(int canny_2, void* param)
{
    cout << canny_2 << endl;
    CannyData* cannyData = (CannyData*)param;
    Mat cannyImg;
    Canny(cannyData->img, cannyImg, cannyData->canny_1, canny_2);
    Mat temp;
    morphologyEx(cannyImg, cannyImg, MORPH_CLOSE, temp, Point(-1, -1), 5);
    imshow("Canny", cannyImg);
}
