#include <bits/stdc++.h>
#include "ImageOperation.h"
using namespace std;

int main(int argc,char *argv[]){
	
	if(argc > 2){
		cout<<"Too many arguments supplied.\n";
	}
	else if(argc <= 1){
		cout<<"Two arguments expected.\n";
	}
	else{
		Image img;
		img = ReadImage(argv[1]);
		cout<<"Image Loaded Successfully.\n";
		string str = showMessage(img);
		cout<<"Hidden message was:  "<<str<<endl;


	}
	return 0;
}