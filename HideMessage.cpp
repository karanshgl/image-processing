#include <bits/stdc++.h>
#include "ImageOperation.h"
using namespace std;

int main(int argc,char *argv[]){
	
	if(argc > 3){
		cout<<"Too many arguments supplied.\n";
	}
	else if(argc <= 2){
		cout<<"Two arguments expected.\n";
	}
	else{
		Image img;
		img = ReadImage(argv[1]);
		cout<<"Image Loaded Successfully.\n";
		char str[100];
		strcpy(str,argv[2]);
		Image im = hideMessage(img,str);
		WriteImage("hiddenMessageImage.pgm",im);


	}
	return 0;
}