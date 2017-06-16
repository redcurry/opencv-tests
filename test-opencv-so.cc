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

int main(int argc, char* argv[])
{
  Mat imgOriginal = imread(argv[1], 0);

  if(imgOriginal.empty())
    return -1;

  Mat img;
  resize(imgOriginal, img, Size(640, 480));

  medianBlur(img, img, 11);
  Canny(img, img, 25, 100);

  vector< vector<Point> > contours;
  findContours(img, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
  
  for (int i = 0; i < contours.size(); i++)
    cout << "Area " << i << ": " << contourArea(contours[i]) << endl;

  return 0;
}
