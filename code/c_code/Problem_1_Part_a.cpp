// Akash Mukesh Joshi
// USC ID :4703642421
// USC Email : akashjos@usc.edu
// Submission Date : 6th November 2016
// Problem 1.a : 

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
unsigned char Imagedata[128][128][12] = {0};
unsigned char IMean[128][128][12] = {0};
double c[25][12] = {0}, c_norm[25][12] = {0}; 

int mean_5(int i, int j, int k)
{
	int x = (Imagedata[i-2][j-2][k] + Imagedata[i-1][j-2][k] + Imagedata[i][j-2][k] + Imagedata[i+1][j-2][k] + Imagedata[i+2][j-2][k] +
			 Imagedata[i-2][j-1][k] + Imagedata[i-1][j-1][k] + Imagedata[i][j-1][k] + Imagedata[i+1][j-1][k] + Imagedata[i+2][j-1][k] +
			 Imagedata[i-2][j][k]   + Imagedata[i-1][j][k]   + Imagedata[i][j][k]   + Imagedata[i+1][j][k]   + Imagedata[i+2][j][k]   +
			 Imagedata[i-2][j+1][k] + Imagedata[i-1][j+1][k] + Imagedata[i][j+1][k] + Imagedata[i+1][j+1][k] + Imagedata[i+2][j+1][k] +
			 Imagedata[i-2][j+2][k] + Imagedata[i-1][j+2][k] + Imagedata[i][j+2][k] + Imagedata[i+1][j+2][k] + Imagedata[i+2][j+2][k]) /25;

	return x;
}

double energy_5(int i, int j, int k, int fil)
{
	char m = 2, n = 2;
	double x = (IMean[i-2][j-2][k]*(double)law_filters_25[m-2][n-2][fil] + IMean[i-1][j-2][k]*(double)law_filters_25[m-1][n-2][fil] + IMean[i][j-2][k]*(double)law_filters_25[m][n-2][fil] + IMean[i+1][j-2][k]*(double)law_filters_25[m+1][n-2][fil] + IMean[i+2][j-2][k]*(double)law_filters_25[m+2][n-2][fil] +
				IMean[i-2][j-1][k]*(double)law_filters_25[m-2][n-1][fil] + IMean[i-1][j-1][k]*(double)law_filters_25[m-1][n-1][fil] + IMean[i][j-1][k]*(double)law_filters_25[m][n-1][fil] + IMean[i+1][j-1][k]*(double)law_filters_25[m+1][n-1][fil] + IMean[i+2][j-1][k]*(double)law_filters_25[m+2][n-1][fil] +
			 	IMean[i-2][j][k]*(double)law_filters_25[m-2][n][fil]     + IMean[i-1][j][k]*(double)law_filters_25[m-1][n][fil] 	+ IMean[i][j][k]*(double)law_filters_25[m][n][fil]     + IMean[i+1][j][k]*(double)law_filters_25[m+1][n][fil]     + IMean[i+2][j][k]*(double)law_filters_25[m+2][n][fil]     +
			 	IMean[i-2][j+1][k]*(double)law_filters_25[m-2][n+1][fil] + IMean[i-1][j+1][k]*(double)law_filters_25[m-1][n+1][fil] + IMean[i][j+1][k]*(double)law_filters_25[m][n+1][fil] + IMean[i+1][j+1][k]*(double)law_filters_25[m+1][n+1][fil] + IMean[i+2][j+1][k]*(double)law_filters_25[m+2][n+1][fil] +
			 	IMean[i-2][j+2][k]*(double)law_filters_25[m-2][n+2][fil] + IMean[i-1][j+2][k]*(double)law_filters_25[m-1][n+2][fil] + IMean[i][j+2][k]*(double)law_filters_25[m][n+2][fil] + IMean[i+1][j+2][k]*(double)law_filters_25[m+1][n+2][fil] + IMean[i+2][j+2][k]*(double)law_filters_25[m+2][n+2][fil]);
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

	// Input Image Raw File Names 
	string ip_image[] = { "Texture1.raw", "Texture2.raw",  "Texture3.raw",  "Texture4.raw",
				  		  "Texture5.raw", "Texture6.raw",  "Texture7.raw",  "Texture8.raw",
				  		  "Texture9.raw", "Texture10.raw", "Texture11.raw", "Texture12.raw"};

	// Read image (filename specified by first argument) into image data matrix
	unsigned char Inputimage[Size_row][Size_col] = {0};
	for(int k = 0; k < 12; k++)
	{
		const char *raw = ip_image[k].c_str();

		if (!(file=fopen(raw,"rg"))) {
			cout << "Cannot open file: " << argv[1] <<endl;
			exit(1);
		}

		fread(Inputimage, sizeof(unsigned char), Size_row*Size_col*1, file);
		fclose(file);

		for (int i = 0; i < Size_row; i++)
			for (int j = 0; j < Size_col; j++)
				Imagedata[i][j][k] = Inputimage[i][j];
	}

	//////////////////// INSERT CODE HERE ///////////////////////
	// Subtract the Global Mean in Neighbhorhood 
	int k = 0; 		
	int mean5 = 0;
	double energy5 = 0, fil_val = 0;
	for(k = 0; k < 12; k++) // For all 12 Images
	{
		for (int i = 2; i < Size_row-2; i++)
			for (int j = 2; j < Size_col-2; j++)
			{	
				mean5 = mean_5(i,j,k);
				IMean[i][j][k] = Imagedata[i][j][k] - mean5;
			}

		//Applying All 25 Filters to find energy
		for (int l = 0; l < 25; l++)
		{
			energy5 = 0;
			for (int i = 2; i < Size_row-2; i++)
				for (int j = 2; j < Size_col-2; j++)
				{	
					fil_val = energy_5(i,j,k,l);
					energy5 += fil_val*fil_val;
				}
			c[l][k] = energy5 / Size_row * Size_col;
			// cout << c[k][l] << endl;
		}
	}
	// Feature Normalization
	feature_norm();

	//Output Data in .csv File
    ofile.open("prb1prta.csv", ios::out | ios::trunc);
    for(int i = 0; i < 25; i++) 
    {
        for(int j = 0; j < 12 ;j++) 
            ofile << c_norm[i][j]<< ",";
        ofile << endl;
    }
    ofile.close();

return 0;
}

// % Akash Mukesh Joshi
// % USC ID :4703642421
// % USC Email : akashjos@usc.edu
// % Submission Date : 6th November 2016
// % Problem 1.a : PCA and KMeans Algorithm

// clc; clear; close all;
// fv_norm = csvread('prb1prta.csv');

// % Initializing First Centroid Clustering Points
// centroid = [ 1.50  -0.30  0.20;
//             -10.0   0.00  0.00;
//              2.00  -0.20 -0.40;
//              6.00   0.40  0.10];

// %% Running PCA for Dimensinality Reduction 25D to 3D
// [~,score,~,~,explainedVar] = pca(fv_norm(:,1:12)');
// figure;
// bar(explainedVar)
// for i = 1 : 1 : 12
//     for j = 1 : 1 : 3
//         fv_pca(i,j) = score(i,j);
//     end
// end

// %% Running KMeans on 3D Feature Vector
// [clusters(:,1), centroid] = kmeans(fv_pca,4,'MaxIter',1000,'Start',centroid);
// figure;
// scatter3(fv_pca(:,1),fv_pca(:,2),fv_pca(:,3),'r*');
// figure;
// gscatter(fv_pca(:,1),fv_pca(:,2),clusters)

// %% Running KMeans on 25D Feature Vector
// [clusters(:,2), ~] = kmeans(fv_norm(:,1:12)',4,'MaxIter',1000)