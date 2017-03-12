#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<bits/stdc++.h>
#include"opencv/cv.h"

using namespace cv;
using namespace std;

Mat a;
int th1,th2;

int main()
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<Point> node;
    th1=50;
    th2=130;
    a=imread("hm3.jpg",1);
    if( !a.data )
     return -1;
    Mat edge;
    Mat a1=a.clone();
    cvtColor(a, a, CV_BGR2GRAY);
    blur( a, a, Size( 3, 3 ));
    Canny(a, edge, th1, th2, 3);
    findContours(edge,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
    //CV_RETR_EXTERNAL retrieves only the extreme outer contours. It sets hierarchy[i][2]=hierarchy[i][3]=-1 for all the contours.
    
    //CV_CHAIN_APPROX_SIMPLE compresses horizontal, vertical, 
    //and diagonal segments and leaves only their end points. For example, an up-right rectangular contour is encoded with 4 points.

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
        node.push_back(Point(-1,-1));
    }

    int X,Y;Mat b=draw.clone();int pixel=20;int min=INT_MAX,max=0,xmin,xmax,ymin,ymax;
    for(int i=0;i<node.size();i++)
        {
            X=node[i].x;
            Y=node[i].y;
            if(X==-1)
            {
                circle(b,Point(xmax,ymax),5,Scalar(255,0,0), -1,8);
                circle(b,Point(xmin,ymin),5,Scalar(0,255,0), -1,8);
                min=INT_MAX;
                max=0;
            }
            else//for extremities
            {
                if((X+Y)<=min)
                    {
                        min=X+Y;
                        xmin=X;
                        ymin=Y;
                    }
                if((X+Y)>=max)
                    {
                        max=X+Y;
                        xmax=X;
                        ymax=Y;
                    }
            }
            cout << "X=" << X <<" Y=" << Y;
            printf("\n");
        }

    imshow("Original Image", a1);
    //imshow("edges",edge);
    imshow("hullconvex",draw);
    imshow("Point",b);
    waitKey(0);
    return 0;
}
