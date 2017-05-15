#include "ImageOperation.h"
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main(int argc,char *argv[]){

	if(argc > 4){
		printf("Too many arguments supplied.\n");
	}
	else if(argc <= 3){
		printf("Three arguments expected.\n");
	}
	else{
		mkdir(argv[3],0777);

		Image img;
		img = ReadImage(argv[1]);
		int K = atoi(argv[2]);
		kMeansCluster(img,K,"cluster");

		cout<<"K different images for k cluster have saved in the folder cluster successfully\n"; 


	}
	return 0;
}