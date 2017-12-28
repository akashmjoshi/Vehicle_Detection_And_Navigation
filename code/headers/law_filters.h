#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
	
using namespace std;

// Global Variables
double law_filters_25[5][5][25] = {0};

void matrix_multi(int a[5], int b[5], int c)
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
           law_filters_25[i][j][c] = a[i] * b[j];
           // cout << law_filters_25[i][j][c] << " ";
		}
		// cout << endl;
	}
	// cout << endl;
}

void law_filters_init()
{
	// Intializing Level, Edge, Spot, Wave and Ripple Filters
	int l5[5] = {1, 4, 6, 4, 1};	// Level
	int e5[5] = {-1, -2, 0, 2, 1};	// Edge
	int s5[5] = {-1, 0, 2, 0, 1};	// Spot
	int w5[5] = {-1, 2, 0, -2, 1};	// Wave
	int r5[5] = {1, -4, 6, -4, 1};	// Ripple

	matrix_multi(l5,l5,0); 
	matrix_multi(l5,e5,1); 
	matrix_multi(l5,s5,2); 
	matrix_multi(l5,w5,3); 
	matrix_multi(l5,r5,4); 

	matrix_multi(e5,l5,5); 
	matrix_multi(e5,e5,6); 
	matrix_multi(e5,s5,7); 
	matrix_multi(e5,w5,8); 
	matrix_multi(e5,r5,9); 

	matrix_multi(s5,l5,10); 
	matrix_multi(s5,e5,11); 
	matrix_multi(s5,s5,12); 
	matrix_multi(s5,w5,13); 
	matrix_multi(s5,r5,14); 

	matrix_multi(w5,l5,15); 
	matrix_multi(w5,e5,16); 
	matrix_multi(w5,s5,17); 
	matrix_multi(w5,w5,18); 
	matrix_multi(w5,r5,19); 

	matrix_multi(r5,l5,20); 
	matrix_multi(r5,e5,21); 
	matrix_multi(r5,s5,22); 
	matrix_multi(r5,w5,23); 
	matrix_multi(r5,r5,24); 
}