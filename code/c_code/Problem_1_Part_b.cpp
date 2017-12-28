// Akash Mukesh Joshi
// USC ID :4703642421
// USC Email : akashjos@usc.edu
// Submission Date : 6th November 2016
// Problem 1.a : Texture Segmentation

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include "law_filters.h"
#include "kmeans.c"
#include <fstream>
#include <sstream>

using namespace std;

// Allocate image data array
double c[25][1] = {0}, c_norm[25][1] = {0}; 
unsigned char Imagedata[512][512][1] = {0};
unsigned char IMean[512][512][1] = {0};
unsigned char ImagedataFil[512][512][25] = {0};

double mean_5(int i, int j, int k)
{
	double x = (Imagedata[i-2][j-2][k] + Imagedata[i-1][j-2][k] + Imagedata[i][j-2][k] + Imagedata[i+1][j-2][k] + Imagedata[i+2][j-2][k] +
			 Imagedata[i-2][j-1][k] + Imagedata[i-1][j-1][k] + Imagedata[i][j-1][k] + Imagedata[i+1][j-1][k] + Imagedata[i+2][j-1][k] +
			 Imagedata[i-2][j][k]   + Imagedata[i-1][j][k]   + Imagedata[i][j][k]   + Imagedata[i+1][j][k]   + Imagedata[i+2][j][k]   +
			 Imagedata[i-2][j+1][k] + Imagedata[i-1][j+1][k] + Imagedata[i][j+1][k] + Imagedata[i+1][j+1][k] + Imagedata[i+2][j+1][k] +
			 Imagedata[i-2][j+2][k] + Imagedata[i-1][j+2][k] + Imagedata[i][j+2][k] + Imagedata[i+1][j+2][k] + Imagedata[i+2][j+2][k]) /25;
	return x;
}

double law_fil(int i, int j, int k, int fil)
{
	char m = 2, n = 2;
	double x = (double)(Imagedata[i-2][j-2][k]*(double)law_filters_25[m-2][n-2][fil] + Imagedata[i-1][j-2][k]*(double)law_filters_25[m-1][n-2][fil] + Imagedata[i][j-2][k]*(double)law_filters_25[m][n-2][fil] + Imagedata[i+1][j-2][k]*(double)law_filters_25[m+1][n-2][fil] + Imagedata[i+2][j-2][k]*(double)law_filters_25[m+2][n-2][fil] +
				Imagedata[i-2][j-1][k]*(double)law_filters_25[m-2][n-1][fil] + Imagedata[i-1][j-1][k]*(double)law_filters_25[m-1][n-1][fil] + Imagedata[i][j-1][k]*(double)law_filters_25[m][n-1][fil] + Imagedata[i+1][j-1][k]*(double)law_filters_25[m+1][n-1][fil] + Imagedata[i+2][j-1][k]*(double)law_filters_25[m+2][n-1][fil] +
			 	Imagedata[i-2][j][k]*(double)law_filters_25[m-2][n][fil]     + Imagedata[i-1][j][k]*(double)law_filters_25[m-1][n][fil] 	+ Imagedata[i][j][k]*(double)law_filters_25[m][n][fil]     + Imagedata[i+1][j][k]*(double)law_filters_25[m+1][n][fil]     + Imagedata[i+2][j][k]*(double)law_filters_25[m+2][n][fil]     +
			 	Imagedata[i-2][j+1][k]*(double)law_filters_25[m-2][n+1][fil] + Imagedata[i-1][j+1][k]*(double)law_filters_25[m-1][n+1][fil] + Imagedata[i][j+1][k]*(double)law_filters_25[m][n+1][fil] + Imagedata[i+1][j+1][k]*(double)law_filters_25[m+1][n+1][fil] + Imagedata[i+2][j+1][k]*(double)law_filters_25[m+2][n+1][fil] +
			 	Imagedata[i-2][j+2][k]*(double)law_filters_25[m-2][n+2][fil] + Imagedata[i-1][j+2][k]*(double)law_filters_25[m-1][n+2][fil] + Imagedata[i][j+2][k]*(double)law_filters_25[m][n+2][fil] + Imagedata[i+1][j+2][k]*(double)law_filters_25[m+1][n+2][fil] + Imagedata[i+2][j+2][k]*(double)law_filters_25[m+2][n+2][fil])/255.0;
	// cout << x << " ";
	return x;
}

void Out_Fil(int Size_row, int Size_col)
{
	// Define file pointer and variables
	FILE *file;
    ifstream ifile;
    ofstream ofile;

	// Ouput Image After Applying 25 Law Filters
	unsigned char Outputimage[Size_row][Size_col][1] = {0}; 
	string out_image[] = {"Fil1.raw", "Fil2.raw", "Fil3.raw", "Fil4.raw", "Fil5.raw",
						  "Fil6.raw", "Fil7.raw", "Fil8.raw", "Fil9.raw", "Fil10.raw",
						  "Fil11.raw", "Fil12.raw", "Fil13.raw", "Fil14.raw", "Fil15.raw",
				  		  "Fil16.raw", "Fil17.raw", "Fil18.raw", "Fil19.raw", "Fil20.raw",
				  		  "Fil21.raw", "Fil22.raw", "Fil23.raw", "Fil24.raw", "Fil25.raw"};

	for(int l = 0; l < 25; l++)
	{
		const char *raw = out_image[l].c_str();

		if (!(file=fopen(raw,"wb"))) {
			cout << "Error in writing file: " <<endl;
			exit(1);
		}

		for (int i = 0; i < Size_row; i++)
			for (int j = 0; j < Size_col; j++)
				Outputimage[i][j][0] = ImagedataFil[i][j][l];

		fwrite(Outputimage, sizeof(unsigned char), Size_row*Size_col, file);
		fclose(file);

	}	
}

double energy_5(int i, int j, int k, int fil)
{
	char m = 2, n = 2;
	double x = (double)(IMean[i-2][j-2][k]*(double)law_filters_25[m-2][n-2][fil] + IMean[i-1][j-2][k]*(double)law_filters_25[m-1][n-2][fil] + IMean[i][j-2][k]*(double)law_filters_25[m][n-2][fil] + IMean[i+1][j-2][k]*(double)law_filters_25[m+1][n-2][fil] + IMean[i+2][j-2][k]*(double)law_filters_25[m+2][n-2][fil] +
				IMean[i-2][j-1][k]*(double)law_filters_25[m-2][n-1][fil] + IMean[i-1][j-1][k]*(double)law_filters_25[m-1][n-1][fil] + IMean[i][j-1][k]*(double)law_filters_25[m][n-1][fil] + IMean[i+1][j-1][k]*(double)law_filters_25[m+1][n-1][fil] + IMean[i+2][j-1][k]*(double)law_filters_25[m+2][n-1][fil] +
			 	IMean[i-2][j][k]*(double)law_filters_25[m-2][n][fil]     + IMean[i-1][j][k]*(double)law_filters_25[m-1][n][fil] 	+ IMean[i][j][k]*(double)law_filters_25[m][n][fil]     + IMean[i+1][j][k]*(double)law_filters_25[m+1][n][fil]     + IMean[i+2][j][k]*(double)law_filters_25[m+2][n][fil]     +
			 	IMean[i-2][j+1][k]*(double)law_filters_25[m-2][n+1][fil] + IMean[i-1][j+1][k]*(double)law_filters_25[m-1][n+1][fil] + IMean[i][j+1][k]*(double)law_filters_25[m][n+1][fil] + IMean[i+1][j+1][k]*(double)law_filters_25[m+1][n+1][fil] + IMean[i+2][j+1][k]*(double)law_filters_25[m+2][n+1][fil] +
			 	IMean[i-2][j+2][k]*(double)law_filters_25[m-2][n+2][fil] + IMean[i-1][j+2][k]*(double)law_filters_25[m-1][n+2][fil] + IMean[i][j+2][k]*(double)law_filters_25[m][n+2][fil] + IMean[i+1][j+2][k]*(double)law_filters_25[m+1][n+2][fil] + IMean[i+2][j+2][k]*(double)law_filters_25[m+2][n+2][fil]);
	// cout << x << " ";
	return x;
}

void feature_norm()
{
	double array[12] = {0};
	for(int i = 0; i < 12; i++)
	{
		for(int j = 0; j < 25; j++)
		{
			array[i] = c[i][j];
		}

		double min  = *std::min_element(array,array+12);
		double max  = *std::max_element(array,array+12);

		for(int j = 0; j < 25; j++)
		{
			c_norm[i][j] = (c[i][j] - min) / (max - min);
			cout << c_norm[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	// Generate 25 5x5 Law Filter Masks
	law_filters_init();

	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 1;
	int Size_col = 128;
	int Size_row = 128;
	
	// Define file pointer and variables
    ifstream ifile;
    ofstream ofile;

	// Check for proper syntax
	if (argc < 1){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name" << endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 2){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[2]);
		// Check if size is specified
		if (argc >= 4){
			Size_col = atoi(argv[3]);
			Size_row = atoi(argv[4]);
		}
	}

	// unsigned char Imagedata[Size_row][Size_col][BytesPerPixel] = {0};
	// unsigned char IMean[Size_row][Size_col][BytesPerPixel] = {0};
	// unsigned char ImagedataFil[Size_row][Size_col][25] = {0};

	if (!(file=fopen(argv[1],"rg"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}

	fread(Imagedata, sizeof(unsigned char), Size_row*Size_col*1, file);
	fclose(file);
	
	//////////////////// insert code here //////////////////

	double mean5 = 0;
	double energy5 = 0, fil_val = 0;

	//Applying All 25 Filters to Normalized Image	
	for (int l = 0; l < 25; l++)
		for (int i = 2; i < Size_row-2; i++)
			for (int j = 2; j < Size_col-2; j++)
			{	
				ImagedataFil[i][j][l] = double(law_fil(i,j,0,l));
			}

	// Re-Normalize Image 
	double minimum = 0,  maximum = 0;
	for (int l = 0; l < 25; l++)
	{
		for (int i = 2; i < Size_row-2; i++)
			for (int j = 2; j < Size_col-2; j++)
			{
				maximum = std::max((double)ImagedataFil[i][j][l], maximum);
				minimum = std::min((double)ImagedataFil[i][j][l], minimum);
			}
		for (int i = 2; i < Size_row-2; i++)
			for (int j = 2; j < Size_col-2; j++)
			ImagedataFil[i][j][l] = floor(255.0 * (ImagedataFil[i][j][l] - minimum) / (maximum - minimum)); 	
	}

	// Output Raw Images 
	Out_Fil(Size_row,Size_col);
	 
	// Re-Initalize IMean as zero Matrix 
	for (int i = 0; i < Size_row; i++)
		for (int j = 0; j < Size_col; j++)
			IMean[i][j][0] = 0;

	// Subtract the Global Mean in Neighbhorhood
	for (int i = 2; i < Size_row-2; i++)
		for (int j = 2; j < Size_col-2; j++)
		{	
			mean5 = mean_5(i,j,0);
			IMean[i][j][0] = double(Imagedata[i][j][0]) - double(mean5);
		}

	
	  
	return 0;
}
