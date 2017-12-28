// Akash Mukesh Joshi
// USC ID :4703642421
// USC Email : akashjos@usc.edu
// Submission Date : 6th November 2016
// Poblem 2.b : Image Matching

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

int main(int argc, const char* argv[])
{
	Mat Imagedata_1 = imread( argv[1], IMREAD_GRAYSCALE );
	Mat Imagedata_2 = imread( argv[2], IMREAD_GRAYSCALE );
  	int minHessian = 400;

  	//Detect the keypoints using SURF Detector
  	Ptr<Feature2D> detector_sift = xfeatures2d::SIFT::create();
 	std::vector<KeyPoint> keypoints_1, keypoints_2;

  	detector_sift->detect( Imagedata_1, keypoints_1);
  	detector_sift->detect( Imagedata_2, keypoints_2);

  	//Calculate descriptors (feature vectors)
    Mat descriptors_1, descriptors_2;

    detector_sift->compute( Imagedata_1, keypoints_1, descriptors_1 );
    detector_sift->compute( Imagedata_2, keypoints_2, descriptors_2 );

    //Matching descriptor vectors using BFMatcher :
  	BFMatcher matcher;
  	std::vector< DMatch > matches;
  	matcher.match(descriptors_1, descriptors_2, matches);

  	//-- Quick calculation of max and min distances between keypoints
  	double max_dist = 0; double min_dist = 100;
  	for( int i = 0; i < descriptors_1.rows; i++ )
  	{ double dist = matches[i].distance;
  	  if( dist < min_dist ) min_dist = dist;
  	  if( dist > max_dist ) max_dist = dist;
  	}

  	//-- Draw only "good" matches
  	std::vector< DMatch > good_matches;

	for( int i = 0; i < descriptors_1.rows; i++ )
	{ if( matches[i].distance < 3*min_dist )
	   { good_matches.push_back( matches[i]); }
	}

  	Mat img_matches;
  	drawMatches( Imagedata_1, keypoints_1, Imagedata_2, keypoints_2,
               good_matches, img_matches);

  	//-- Show detected matches
	imwrite("matches_sift.jpg", img_matches);

//////////////// DOING SURF NOW ////////////////////////////
 	Ptr<SURF> detector_surf = SURF::create( minHessian );

	detector_surf->detect( Imagedata_1, keypoints_1);
  	detector_surf->detect( Imagedata_2, keypoints_2);

    detector_surf->compute( Imagedata_1, keypoints_1, descriptors_1 );
    detector_surf->compute( Imagedata_2, keypoints_2, descriptors_2 );

    matcher.match(descriptors_1, descriptors_2, matches);

    //-- Quick calculation of max and min distances between keypoints
  	for( int i = 0; i < descriptors_1.rows; i++ )
  	{ double dist = matches[i].distance;
  	  if( dist < min_dist ) min_dist = dist;
  	  if( dist > max_dist ) max_dist = dist;
  	}

  	//-- Draw only "good" matches

	for( int i = 0; i < descriptors_1.rows; i++ )
	{ if( matches[i].distance < 2*min_dist )
	   { good_matches.push_back( matches[i]); }
	}

    drawMatches( Imagedata_1, keypoints_1, Imagedata_2, keypoints_2,
               good_matches, img_matches);

  	//-- Show detected matches
	imwrite("matches_surf.jpg", img_matches);

    return 0;
}