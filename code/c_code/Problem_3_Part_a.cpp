// Akash Mukesh Joshi
// USC ID :4703642421
// USC Email : akashjos@usc.edu
// Submission Date : 6th November 2016
// Poblem 3.a : Canny Edge Detection 

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//////////////////////////////////////////////
int main(int argc, char** argv )
{
	// Define file pointer and variables
	FILE *file = NULL;
	int BytesPerPixel = 3;
	int Size_col = 481;
	int Size_row = 321;
	double low_threshold = 400;
	double high_threshold = 600;
	int framesize = Size_col * Size_row;

	// Allocate image data array
	unsigned char Imagedata_Z[Size_row][Size_col][BytesPerPixel] = {0};
	unsigned char Imagedata_J[Size_row][Size_col][BytesPerPixel] = {0};
	unsigned char ImagedataGS_Z[Size_row][Size_col] = {0};
	unsigned char ImagedataGS_J[Size_row][Size_col] = {0};	
	unsigned char ICanny[Size_row][Size_col] = {0};

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

	//////////////////////// INSERT CODE HERE /////////////////
	// Converting Image into Grayscale
	for(int i = 0; i <  Size_row; i++)
		for(int j = 0; j < Size_col; j++)
			{
				ImagedataGS_Z[i][j] = floor (Imagedata_Z[i][j][0] * 0.29 
									 + Imagedata_Z[i][j][1] * 0.59
									 + Imagedata_Z[i][j][2] * 0.11);
			
				ImagedataGS_J[i][j] = floor (Imagedata_J[i][j][0] * 0.29 
									 + Imagedata_J[i][j][1] * 0.59
									 + Imagedata_J[i][j][2] * 0.11);
			}

	Mat M = Mat::zeros(321, 481, CV_8UC1);
	Mat N = Mat::zeros(321, 481, CV_8UC1);
	Mat N_Invert = Mat::zeros(321, 481, CV_8UC1);
	
	// Zebra
	M = Mat(321, 481, CV_8UC1, &ImagedataGS_Z);

	Canny(M,N,low_threshold,high_threshold,3);
    threshold(N, N_Invert, 70, 255, CV_THRESH_BINARY_INV);

    imwrite("/home/acewalker/Documents/EE569DIP/Homework3/HW3 Images/P3/Zebra_Canny.jpg",N_Invert);
    waitKey();

    // Jaguar
	M = Mat(321, 481, CV_8UC1, &ImagedataGS_J);

	Canny(M,N,low_threshold,high_threshold,3);
    threshold(N, N_Invert, 70, 255, CV_THRESH_BINARY_INV);

    imwrite("/home/acewalker/Documents/EE569DIP/Homework3/HW3 Images/P3/Jaguar_Canny.jpg",N_Invert);
    waitKey();    

    return 0;
}