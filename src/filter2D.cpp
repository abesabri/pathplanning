// A C++ Program to implement filter2D for reducing the map

#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

void readFile(string, float[], ifstream &);
void writeFile(string, Mat &down, ofstream &);
void printvals(Mat &matname);
void displaymat(Mat& matname, Mat &dst);

/** @function main */
int main ( int argc, char** argv )
{
    ifstream inFile;
    ofstream outFile;
    string strFileName = "num2.txt";
    string strOutFile = "downsample3.txt";
    int r = 366, c = 362;
    float V[r*c];
    
    readFile(strFileName, V, inFile);

    
    //Copying vector to Mat
  
    Mat dst1;

    Mat M(r,c,CV_32FC1,V);
    printvals(M);
    // displaymat(M, dst1);
    // imshow("dst1",dst1);
    
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
    
    // Initialize arguments for the filter
    anchor = Point( -1, -1 );
    delta = 0;
    ddepth = -1;
    
    // Update kernel size for a normalized box filter
    kernel_size = 3;
    kernel = Mat::ones( kernel_size, kernel_size, CV_32FC1 )/ (float)(kernel_size*kernel_size);
    // Apply filter
    cv::filter2D(M, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
    //imshow("t",dst);

    // Min and Max value of Mat 
    displaymat(M,intMat);


    //Loop to display values and see if they are correct
  
    // cout << "Dims M " << M.rows << " " << M.cols << endl;
    // for(int i = 0; i < M.rows; i++){
    //     for(int j = 0; j < M.cols; j++){
    //         std::cout << int(M.at<float>(i,j)) << " ";
    //     }
    //     std::cout << std::endl;
    // }
    imshow("Filter Map",intMat);
    imwrite("Filter_Map.jpg",intMat);

    int dr = ceil(float(M.rows)/kernel_size);
    int dc = ceil(float(M.cols)/kernel_size);
    

    Mat downsample(dr,dc,CV_32FC1);;
    Mat intdownsample;
    
    int newrow = 0, newcol = 0;
    for(int i = kernel_size/2; i<dst.rows; i+=kernel_size){
        //cout << "a" << endl;
        newcol=0;
        for(int j = kernel_size/2; j<dst.cols; j+=kernel_size){
            //cout << "b" << endl;
            if(dst.at<float>(i,j) > 0){
                downsample.at<float>(newrow,newcol) = 3;
            }
            else if(dst.at<float>(i,j) < 0){
                downsample.at<float>(newrow,newcol) = -1;
            }
            else{
                downsample.at<float>(newrow,newcol) = 0;
            }
            //downsample.at<float>(newrow,newcol) = dst.at<float>(i,j);
            //cout << int(downsample.at<float>(x,y)) << " ";
            newcol++;
        } 
        cout <<  endl;
        newrow++;
    }

    displaymat(downsample,intdownsample);
    printvals(downsample);
    // minMaxLoc(downsample,&minVal,&maxVal,&minLoc,&maxLoc);
    // cout << "min: " << minVal << endl;
    // cout << "max: " << maxVal << endl;
    // if (minVal!=maxVal){
    //     downsample.convertTo(intdownsample,CV_8U,255.0/(maxVal-minVal),-255.0*minVal/(maxVal-minVal));
    // }


    imshow("downscaled",intdownsample);
    writeFile(strOutFile,downsample,outFile);
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
        if(value == 100){
            value = 3;
        }
        v[i] = value;
        i++;
    }

    iFile.close();

}


void writeFile(string strFile, Mat &down, ofstream &oFile){
    oFile.open(strFile);
    if(!oFile){
        cout << "Error opening file" << endl;
        exit(1);
    }
    cout << down.rows << " " << down.cols << endl;
    int i,j;
    for(i=0; i<down.rows;i++){
        for(j=0; j<down.cols;j++){
            oFile <<down.at<float>(i,j) << ",";
        }
    }
    cout << endl;
    oFile.close();
}

void printvals(Mat &matname){
    for(int i=0; i<matname.rows;i++){
        for(int j=0;j<matname.cols;j++){
            cout << matname.at<float>(i,j) << " " ;
        }
        cout << endl;
    }
}

void displaymat(Mat& matname, Mat &dst){
    
    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    minMaxLoc(matname,&minVal,&maxVal,&minLoc,&maxLoc);
    cout << "min: " << minVal << endl;
    cout << "max: " << maxVal << endl;
    if (minVal!=maxVal){
        matname.convertTo(dst,CV_8U,255.0/(maxVal-minVal),-255.0*minVal/(maxVal-minVal));
    }
    

}