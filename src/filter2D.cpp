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
    float V[10];
    
    readFile(strFileName, V, inFile);

    //int r = 366, c = 362;
    //Mat1d M(r,c,CV_32FC1);
    //Mat1d dsrc(CV_32FC1,CV_32FC1);
    //Mat1d copy_1 = Mat(dsrc.rows, dsrc.cols, CV_32F, V.data()).clone();
    //memcpy(M.data,V.data(),V.size()*sizeof(float));

    //Copying vector to Mat
    int r = 1, c = 10;
    Mat M(r,c,CV_32FC1,V);

    /// Declare variables  
    Mat intMat = Mat::zeros(cv::Size(r,c),CV_8UC1); 
    Mat dst;
    Mat kernel;
    Point anchor;
    double delta;
    int ddepth;
    int kernel_size;
    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    
    /// Initialize arguments for the filter

    anchor = Point( -1, -1 );
    delta = 0;
    ddepth = -1;
    
    /// Update kernel size for a normalized box filter
    kernel_size = 3 + 2;
    kernel = Mat::ones( kernel_size, kernel_size, CV_32FC1 )/ (float)(kernel_size*kernel_size);
    /// Apply filter
    cv::filter2D(M, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
    //imshow("t",dst);

    // Min and Max value of Mat
    minMaxLoc(dst,&minVal,&maxVal,&minLoc,&maxLoc);
    cout << "min: " << minVal << endl;
    cout << "max: " << maxVal << endl;
    if (minVal!=maxVal){
        dst.convertTo(intMat,CV_8UC1,255.0/(maxVal-minVal),-255.0*minVal/(maxVal-minVal));
    }
    
    //Loop to display values and see if they are correct
    for(int i = 0; i < intMat.rows; i++){
        for(int j = 0; j < intMat.cols; j++){
            std::cout << int(intMat.at<uchar>(i,j)) << " ";
        }
        std::cout << std::endl;
    }

    //Dummy Mat -- it can be used it with imshow to see that imshow works
    //Mat test = Mat::zeros(cv::Size(50,50),CV_8UC3);
    //imshow("t",test);
    
    imshow("t",intMat);
    //A waitKey must be included to keep the image window open until a key is pressed
    //Otherwise the windows appears and disappears to quickly for it to be seen
    waitKey(0);
    

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
