#include <iostream>
#include <fstream>
#include <math.h>

#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

double toX(double x) {
  return 0.2985*(x/720)-0.1530;
}


int main(int argc, char** argv) {

  Rect2d roi;
  Mat frame;

  Ptr<Tracker> tracker = TrackerKCF::create();

  const std::string video = "video_editado.mp4";
  VideoCapture cap(video);

  cap >> frame;
  roi = selectROI("tracker", frame);

  ofstream outputFile;
  
  outputFile.open ("output.txt");

  std::cout << "INICIAL: " << " " << roi.x << " " << roi.y << " " << roi.width << " " << roi.height  << std::endl;


  if (roi.width == 0 || roi.height == 0) return 0;

  tracker->init(frame, roi);

  double t = 0;
  double x = toX(roi.y);
  

  while (t <= 60) {

    cap >> frame;

    if (frame.rows == 0 || frame.cols == 0) break;

    

    cout << t << " " << x << endl;
    outputFile << t << " " << x << '\n';

    t += 1.0/30;
    x = toX(roi.y);

    tracker->update(frame, roi);
    
    rectangle (frame, roi, Scalar (255, 0, 0), 2, 1);

    imshow("tracker", frame);

    if (waitKey(1) == 27) break;
  }

  outputFile.flush();
  outputFile.close();

  system("rm fit.log");
  system("gnuplot <gnuplot.ps");



  ifstream leitorBW;
  leitorBW.open("fit_results.txt");

  double b, w;
  leitorBW >> b;
  leitorBW >> w;
  leitorBW.close();
  
  cout << "\n\n b: " << b << "\n w: " << w << endl;

  ofstream final;
  final.open("Q.txt");

  double Q =  sqrt(w*w + b*b)/(2*b);

  cout << "fator de qualidade: " << Q << endl;

  final << Q << endl;

  final.close();

  return 0;

}