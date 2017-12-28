// Akash Mukesh Joshi
// USC ID :4703642421
// USC Email : akashjos@usc.edu
// Submission Date : 6th November 2016
// Poblem 3.b : Structured Edge Detection 

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
using namespace cv;
using namespace cv::ximgproc;
using namespace std;

///////////////////////////////////////////////////
int main(int argc, char** argv )
{
	FILE *file = NULL;
	int BytesPerPixel = 3;
	int Size_col = 481;
	int Size_row = 321;
	int framesize = Size_col * Size_row;

	// Allocate image data array
	unsigned char Imagedata_Z[Size_row][Size_col][BytesPerPixel] = {0};
	unsigned char Imagedata_J[Size_row][Size_col][BytesPerPixel] = {0};

	// Check for proper syntax
	if (argc < 1){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name" << endl;
		return 0;
	}

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rg"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}

	fread(Imagedata_Z, sizeof(unsigned char), Size_row*Size_col*BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen(argv[2],"rg"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}

	fread(Imagedata_J, sizeof(unsigned char), Size_row*Size_col*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT CODE HERE ///////////////// 

    Ptr<StructuredEdgeDetection> pDollar = createStructuredEdgeDetection("/home/acewalker/Documents/EE569DIP/Homework3/HW3 Images/P3/model.yml.gz");
    // pDollar->detectEdges(image, edges);
    // Mat3b src = imread("path_to_image");

    // Mat3f fsrc;
    // src.convertTo(fsrc, CV_32F, 1.0 / 255.0);

    // Mat1f edges;
    // pDollar->detectEdges(fsrc, edges);

    // imshow("Image", src);
    // imshow("Edges", edges);
    // waitKey();

    return 0;
}