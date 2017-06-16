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
  Mat src = imread(argv[1]);

  Mat img;
  cvtColor(src, img, COLOR_RGB2GRAY);

  // Neighborhood length
  int w = 10;
  int wSize = w * w;

  int diffThresh = 5;

  Mat img2(img.rows, img.cols, CV_8U);

  // How much to throw away (in fractional percent)
  double x = 0.05;

  for (int i = 0; i < img.cols - w; i += w)
  {
      for (int j = 0; j < img.rows - w; j += w)
      {
          Rect roi(i, j, w, w);
          Mat square = img(roi).clone();

          vector<uchar> pixels;
          for (int a = 0; a < w; a++)
              for (int b = 0; b < w; b++)
                  pixels.push_back(square.at<uchar>(a, b));

          sort(pixels.begin(), pixels.end());

          // Get min and max at x%
          int min = pixels[(int)(wSize * x)];
          int max = pixels[(int)(wSize * (1.0 - x))];

          uchar diff = max - min;
          uchar mean = (max - min) / 2;

          for (int a = 0; a < w; a++)
          {
              for (int b = 0; b < w; b++)
              {
                  if (diff > 20)
                  {
                      if (square.at<uchar>(a, b) <= mean)
                          img2.at<uchar>(j + b, i + a) = 255;
                      else
                          img2.at<uchar>(j + b, i + a) = 0;
                  }
              }
          }
      }
  }

  namedWindow("Grayscale", WINDOW_AUTOSIZE);
  imshow("Grayscale", img2);

  waitKey();

  return 0;
}
