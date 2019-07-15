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
    string strFileName = "num2.txt";
    int r = 366, c = 362;
    float V[r*c];
    
    readFile(strFileName, V, inFile);

    //int r = 366, c = 362;
    //Mat1d M(r,c,CV_32FC1);
    //Mat1d dsrc(CV_32FC1,CV_32FC1);
    //Mat1d copy_1 = Mat(dsrc.rows, dsrc.cols, CV_32F, V.data()).clone();
    //memcpy(M.data,V.data(),V.size()*sizeof(float));

    //Copying vector to Mat
    //int r = 366, c = 362;
    Mat M(r,c,CV_32FC1,V);

    /// Declare variables  
    Mat intMat; 
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
    kernel_size = 3;
    kernel = Mat::ones( kernel_size, kernel_size, CV_32FC1 )/ (float)(kernel_size*kernel_size);
    /// Apply filter
    cv::filter2D(M, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
    //imshow("t",dst);

    // Min and Max value of Mat
    minMaxLoc(dst,&minVal,&maxVal,&minLoc,&maxLoc);
    cout << "min: " << minVal << endl;
    cout << "max: " << maxVal << endl;
    if (minVal!=maxVal){
        M.convertTo(intMat,CV_8U,255.0/(maxVal-minVal),-255.0*minVal/(maxVal-minVal));
    }
    
    Mat map;
    M.convertTo(map,CV_8U,255.0/(maxVal-minVal),-255.0*minVal/(maxVal-minVal));
    //Loop to display values and see if they are correct
    //Loop to display values and see if they are correct
    cout << "Dims M " << M.rows << " " << M.cols << endl;
    for(int i = 0; i < M.rows; i++){
        for(int j = 0; j < M.cols; j++){
            std::cout << int(M.at<float>(i,j)) << " ";
        }
        std::cout << std::endl;
    }
    /*for(int i = 0; i < intMat.rows; i++){
        for(int j = 0; j < intMat.cols; j++){
            std::cout << int(intMat.at<uchar>(i,j)) << " ";
        }
        std::cout << std::endl;
    }*/

    imshow("t",map);
    imwrite("map_image.jpg",map);
    waitKey(0);

return 0;

}

void readFile(string strFile, float v[], ifstream &iFile){
    iFile.open(strFile.c_str());
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
