#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/highgui/highgui_c.h"
using namespace cv;


int main(int argc, char* argv[])
{
  vector<Point> contour;

  while (!cin.eof())
  {
    Point p;
    cin >> p.x >> p.y;
    if (p.x == 0 && p.y == 0)
      break;
    contour.push_back(p);
  }

  vector<Point>::iterator it;
  for (it = contour.begin(); it != contour.end(); )
      if (find(contour.begin(), it, *it) != it) {
          it = contour.erase(it);
          cout << "Found: " << *it << endl;
      }
      else {
          cout << "Not found: " << *it << endl;
          ++it;
      }

  for (int i = 0; i < contour.size(); i++)
    cout << contour[i].x << " " << contour[i].y << endl;

  vector< vector<Point> > contours;
  contours.push_back(contour);

  Mat imgContour = Mat::zeros(480, 640, CV_8UC3);
  Scalar color(rand() % 255, rand() % 255, rand() % 255);
  drawContours(imgContour, contours, 0, color, -1);

  namedWindow("Contour", WINDOW_NORMAL);
  resizeWindow("Contour", 640, 480);
  imshow("Contour", imgContour);
 
  cout << "Area : " << contourArea(contour) << endl;

  waitKey(0);
}
