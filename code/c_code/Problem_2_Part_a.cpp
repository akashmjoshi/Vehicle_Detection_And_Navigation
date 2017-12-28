// Akash Mukesh Joshi
// USC ID :4703642421
// USC Email : akashjos@usc.edu
// Submission Date : 6th November 2016
// Poblem 2.a : Extraction and Description of Salient Points
// cmake CMakeLists.txt && make
// 
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

int main(int argc, const char* argv[])
{
	Mat Imagedata_bus = imread( argv[1], IMREAD_GRAYSCALE );
	Mat Imagedata_jeep = imread( argv[2], IMREAD_GRAYSCALE );
	
  	int minHessian = 400;

  	Ptr<SURF> detector_surf = SURF::create( minHessian );
  	Ptr<Feature2D> detector_sift = xfeatures2d::SIFT::create();

  	std::vector<KeyPoint> keypoints_1, keypoints_2;

  	Mat Imagedata_bus_keypoints;
  	Mat Imagedata_jeep_keypoints;

  	// Keypoint Detection using SURF 
  	detector_surf->detect( Imagedata_bus, keypoints_1);
	detector_surf->detect( Imagedata_jeep, keypoints_2);

	drawKeypoints(Imagedata_bus, keypoints_1, Imagedata_bus_keypoints);
  	drawKeypoints(Imagedata_jeep, keypoints_2, Imagedata_jeep_keypoints);

	imwrite("Bus_Surf.jpg", Imagedata_bus_keypoints);
	imwrite("Jeep_Surf.jpg", Imagedata_jeep_keypoints);

	// Keypoint Detection using SIFT
	detector_sift->detect( Imagedata_bus, keypoints_1);
	detector_sift->detect( Imagedata_jeep, keypoints_2); 
	
  	drawKeypoints(Imagedata_bus, keypoints_1, Imagedata_bus_keypoints);
  	drawKeypoints(Imagedata_jeep, keypoints_2, Imagedata_jeep_keypoints);

	imwrite("Bus_Sift.jpg", Imagedata_bus_keypoints);
	imwrite("Jeep_Sift.jpg", Imagedata_jeep_keypoints);

    return 0;
}