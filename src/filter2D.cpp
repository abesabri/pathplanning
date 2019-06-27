// A C++ Program to implement filter2D for reducing the map

#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;

void readFile(string, float[], ifstream &);

/** @function main */
int main ( int argc, char** argv )
{
    ifstream inFile;
    string strFileName = "new";
    float V[100];
    
    readFile(strFileName, V, inFile);

    int r = 366, c = 362;
    //Mat1d M(r,c,CV_32FC1);
    Mat1d dsrc(CV_32FC1,CV_32FC1);
    Mat1d copy_1 = Mat(dsrc.rows, dsrc.cols, CV_32F, V);
    //memcpy(M.data,V.data(),V.size()*sizeof(float));
  
    
    /// Declare variables 
    Mat dst;
    Mat kernel;
    Point anchor;
    double delta;
    int ddepth;
    int kernel_size;

    /// Initialize arguments for the filter
    anchor = Point( -1, -1 );
    delta = 0;
    ddepth = -1;

    /// Update kernel size for a normalized box filter
    kernel_size = 3 + 2;
    kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);

    /// Apply filter
    cv::filter2D(copy_1, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );

return 0;

}

void readFile(string strFile, float v[], ifstream &iFile){
    iFile.open("new.txt");
    if(!iFile){
        cout << "Error opening file" << endl;
        system("pause");
    }
    int value, i = 0;
    while(iFile >> value){
        v[i] = value;
        i++;
    }

    iFile.close();
}
