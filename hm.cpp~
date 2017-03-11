#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<bits/stdc++.h>
#include"opencv/cv.h"

using namespace cv;
using namespace std;

int th1,th2;

int main()
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<Point> node;
    th1=50;
    th2=130;
    Mat a=imread("hm2.jpg",1);
    if( !a.data )
     return -1;
    Mat edge;
    cvtColor(a, a, CV_BGR2GRAY);
    blur( a, a, Size( 3, 3 ));
    Canny(a, edge, th1, th2, 3);
    findContours(edge,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);

    vector<vector<Point> >hull(contours.size());
    for(int i=0;i<contours.size();i++)
    convexHull(Mat(contours[i]),hull[i],false);

    Mat draw = Mat::zeros(edge.size(), CV_8UC3);//all black

    for(int i=0;i<contours.size();i++)
    {
        Scalar color = Scalar(255, 255, 255);
        drawContours(draw, hull,i,color,1,8,vector<Vec4i>(),0,Point());
        for(int j = 0;j<hull[i].size();j++)
        {
            node.push_back(hull[i][j]);
        }
    }
    imshow("edges",edge);
    imshow("hullconvex",draw);
    waitKey(0);
    return 0;
}
