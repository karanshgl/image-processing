#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;


struct Image
{
	vector<vector<unsigned char> > mat;
	char h1[100];
	char h2[100];
	char h3[100];
};

Image ReadImage(string str);
void WriteImage(string str,Image img);
Image bilinearInterpolation(Image img,int height,int width);
Image hideMessage(Image img,string str);
string showMessage(Image img);
void kMeansCluster(Image img,int k,string outputFolder);

Image ReadImage(string str)
{
	char cArray[100];
	int iWidth, iHeight;
	unsigned int cTemp;
	char *strPointer = new char[str.length() + 1];
	strcpy(strPointer, str.c_str());
	Image img;
	FILE *filePointer;
	filePointer = fopen(strPointer,"r");
	if (filePointer == NULL)
	{
		printf("cannot open file");
		return img;
	}	

	fgets (cArray, 99, filePointer);
	strcpy(img.h1, cArray);

	fgets (cArray, 99, filePointer);
	strcpy(img.h2, cArray);

	fscanf(filePointer,"%d %d\n", &iWidth, &iHeight);

	fgets (cArray, 99, filePointer);
	strcpy(img.h3, cArray);

	img.mat.resize(iHeight,vector<unsigned char> ());
	for (int i = 0; i < iHeight; ++i)
	{
		img.mat[i].resize(iWidth,0);
	}

	fprintf(filePointer,"%d %d\n", iWidth, iHeight);
	// cout<<iWidth<<"  "<<iHeight<<endl;

	for (int iRow = 0; iRow< iHeight; iRow++)

	{
		vector<unsigned char> temp;
		for (int iCol = 0; iCol< iWidth; iCol++)
		{
			fscanf(filePointer, "%d ", &cTemp);
			
			
			if (cTemp != EOF)
			{
				img.mat[iRow][iCol] = cTemp;
			}	
			
		}

		
	}
	cout<<img.mat.size()<<"  "<<img.mat[0].size()<<endl;
	return img;
}


void WriteImage(string str,Image img)
{
	char cArray[100];
	int iWidth, iHeight;
	unsigned int cTemp;
	char *strPointer = new char[str.length() + 1];
	strcpy(strPointer, str.c_str());
	FILE *filePointerOut;
	filePointerOut = fopen(strPointer,"w");
	if (filePointerOut == NULL)
	{
		printf("cannot open file");
		return;
	}	

	fputs (img.h1, filePointerOut);

	fputs (img.h2, filePointerOut);



	fprintf(filePointerOut,"%d %d\n", (int)img.mat[0].size(), (int)img.mat.size());
	fputs (img.h3, filePointerOut);
	for (int iRow = 0; iRow< img.mat.size(); iRow++)
	{
		for (int iCol = 0; iCol< img.mat[0].size(); iCol++)
		{
			
			if (cTemp != EOF)
			{ 
				fprintf(filePointerOut, "%d ", img.mat[iRow][iCol]);
			}	
			
		}

		
	}
}




Image bilinearInterpolation(Image img,int height,int width)
{
	
	Image im;
	for (int i = 0;i<height;i++)
	{
		vector<unsigned char> temp;
		for (int j = 0;j < width;j++)
		{
			temp.push_back(0);
		}
		im.mat.push_back(temp);
	}
	strcpy(im.h1,img.h1);
	strcpy(im.h2,img.h2);
	strcpy(im.h3,img.h3);
	float xRatio = (float)(img.mat[0].size() - 1)/width;
	float yRatio = (float)(img.mat.size() - 1)/height;
	// cout<<xRatio<<"  "<<yRatio<<endl;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0;j < width;j++)
		{
			int x = (int) (xRatio * j);
			int y = (int) (yRatio * i);
			float x_diff = xRatio * j - x;
			float y_diff = yRatio * i - y;
			int a = img.mat[y][x], b = img.mat[y][x + 1], c = img.mat[y + 1][x], d = img.mat[y + 1][x + 1];
			im.mat[i][j] = (unsigned char)(a * (1 - x_diff) * (1 - y_diff) + 
										   b * x_diff * (1 - y_diff) + 
						   				   c * (1 - x_diff) * y_diff +
						   				   d * x_diff * y_diff);
			im.mat[i][j]=(unsigned char)((a)/1);
		}
	}
	return im;
}

Image hideMessage(Image img,string str)
{
	Image im;
	vector<unsigned char> temp;
	for (int i = 0; i < img.mat.size(); ++i)
	{
		for (int j = 0;j < img.mat[0].size();j++)
		{
			temp.push_back(img.mat[i][j]);
		}
	}
	int j = 0;
	int k = 0;
	while (str[j] != '\0')
	{
		int i = 7;
		while(i >=0)
		{
			unsigned char tem = 1<<i;
			unsigned char tem2 = tem & str[j];
			tem2 = tem2>>i;
			temp[k] = (temp[k] & (~1)) | tem2;
			k++;

			i--;
		}
		j++;
	}
	int i = 7;
	while(i >=0)
	{
		unsigned char tem = 1<<i;
		unsigned char tem2 = tem & str[j];
		tem2 = tem2>>i;
		temp[k] = (temp[k] & (~1)) | tem2;
		k++;

		i--;
	}
	cout<<str[j]<<endl;
	k = 0;
	strcpy(im.h1,img.h1);
	strcpy(im.h2,img.h2);
	strcpy(im.h3,img.h3);
	for (int i = 0; i < img.mat.size(); ++i)
	{
		vector<unsigned char> vec;
		for (int j = 0;j < img.mat[0].size();j++)
		{
			vec.push_back(temp[k]);
			k++;
		}
		im.mat.push_back(vec);
	}
	return im;
}


string showMessage(Image img)
{
	vector<unsigned char> temp;
	for (int i = 0; i < img.mat.size(); ++i)
	{
		for (int j = 0;j < img.mat[0].size();j++)
		{
			temp.push_back(img.mat[i][j]);
		}
	}
	string str;
	for (int i = 0; i < temp.size();)
	{
		int j = 7;
		unsigned char t = 0;
		while (j >= 0 && i < temp.size())
		{	
			unsigned char tem = 1 & temp[i];
			tem = tem << j;
			t = t | tem;
			j--;
			i++;
		}
		str.push_back(t);
		if (t == 0)
			break;

	}
	return str;
}


void kMeansCluster(Image img,int k,string outputFolder)
{
	char *strPointer = new char[outputFolder.length() + 1];
	strcpy(strPointer, outputFolder.c_str());
	mkdir(strPointer,0777);
	unsigned int interval = 256/k;
	vector<unsigned char> means;
	vector<vector<unsigned char> > clusters;
	for (int i = 0; i < k; ++i)
	{
		means.push_back(i * interval + interval / 2);
		std::vector<unsigned char> v;
		clusters.push_back(v);
	}
	for (int m = 0;m < 10;m++)
	{
		for (int i = 0; i < k; ++i)
		{
			for (; clusters[i].size() != 0;)
			{
				clusters[i].erase(clusters[i].begin());
			}
		}
		for (int i = 0; i < img.mat.size(); ++i)
		{
			for (int j = 0; j < img.mat[0].size(); ++j)
			{
				int clus = 0,dist = INT_MAX;
				for (int l = 0; l < k; ++l)
				{
					if (abs(img.mat[i][j] - means[l]) < dist)
					{
						clus = l;
						dist = abs(img.mat[i][j] - means[l]);
					}
				}
				clusters[clus].push_back(img.mat[i][j]);
			}
		}
		for (int i = 0; i < k; ++i)
		{
			means.erase(means.begin());
		}
		for (int i = 0; i < k; ++i)
		{
			long long int sum = 0;
			for (int j = 0; j < clusters[i].size(); ++j)
			{
				sum += (long long int) clusters[i][j];
			}
			means.push_back((unsigned char) (sum / clusters.size()));
		}

	}

	for (int m = 0; m < k; ++m)
	{
		Image im;
		strcpy(im.h1,img.h1);
		strcpy(im.h2,img.h2);
		strcpy(im.h3,img.h3);
		for (int i = 0;i<img.mat.size();i++)
		{
			vector<unsigned char> temp;
			for (int j = 0;j < img.mat[0].size();j++)
			{
				temp.push_back(255);
			}
			im.mat.push_back(temp);
		}
		for (int i = 0;i<img.mat.size();i++)
		{
			for (int j = 0;j < img.mat[0].size();j++)
			{
				int clus = 0,dist = INT_MAX;
				for (int l = 0; l < k; ++l)
				{
					if (abs(img.mat[i][j] - means[l]) < dist)
					{
						clus = l;
						dist = abs(img.mat[i][j] - means[l]);
					}
				}
				if (clus == m)
				{
					im.mat[i][j] = 0;
				}
			}
		}
		string Result;
		stringstream convert;
		convert << m;
		Result = convert.str();
		WriteImage(outputFolder + "/cluster_" + Result + ".pgm",im);

	}

}