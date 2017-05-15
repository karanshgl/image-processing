#include <bits/stdc++.h>
#include "ImageOperation.h"
using namespace std;

int main(int argc,char *argv[]){
	
	if(argc > 3)
	{
		printf("Too many arguments supplied.\n");
	}
	else if(argc <= 2)
	{
		printf("Two arguments expected.\n");
	}
	else
	{
		Image img;
		img = ReadImage(argv[1]);
		printf("Image Loaded Successfully.\n");
		Image im = bilinearInterpolation(img,img.mat.size()*sqrt(2),img.mat[0].size()*sqrt(2));
		printf("Image Upscaled Successfully.\n");
		WriteImage(argv[2],im);
	}
	return 0;

}