#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>
using namespace std;
using namespace cv;
//定义图片路径
string  base_path ="/home/ww/opencv/test/DM_test/";
string name1="4.jpg_r.jpg";
string name2="4.jpg_l.jpg";
//得到完整图片路径
string all_path1=base_path+name1;
string all_path2=base_path+name2;
//读取图片
Mat im0=imread(all_path1);
Mat im1=imread(all_path2);
//定义灰度图和输出图
Mat im0_gray,im1_gray,im_end;
//定义BM算子
Ptr<StereoBM> dm=StereoBM::create(16,5); 
  
/*
DM1 block 
DM2 
*/
int DM1=5,DM2=1,DM3=0,DM4=1,DM5=1,DM6=1,DM7=1,DM8=1;


void total_callback(int ,void *)
{

        //设置参数setNumDisparities
        dm->setNumDisparities(DM2*16);
        //设置DM1 奇偶 和 范围 5～255 odd
                if(DM1<5)
                {
                    DM1=5;
                }
                else{
                            if(DM1%2==0)
                        {
                            DM1++;
                        }  
                }
    dm->setBlockSize(DM1);          
    dm->setPreFilterCap(DM5);
    dm->setMinDisparity(DM3);
    dm->setTextureThreshold(DM4);
    dm->setUniquenessRatio(DM6);
    dm->setSpeckleWindowSize(DM7);
    dm->setSpeckleRange(DM8);
    dm->setDisp12MaxDiff(1);
     dm->compute(im0_gray,im1_gray,im_end);
    //视差数据处理
    im_end.convertTo(im_end, CV_16F); 
    im_end.convertTo(im_end, CV_8UC1,255 / (DM2*16.0*16)); 
    imshow("win",im_end);

}

int main(int, char**) {
dm->setNumDisparities(16);
dm->setBlockSize(5);
     
      dm->setMinDisparity(0); 
    dm->setTextureThreshold(10);
    dm->setPreFilterCap(31);
   dm->setUniquenessRatio(15);
    dm->setSpeckleWindowSize(100);
    dm->setSpeckleRange(32);
    dm->setDisp12MaxDiff(1);
    
   //得到灰度图
    cvtColor(im0,im0_gray,COLOR_BGR2GRAY);
    cvtColor(im1,im1_gray,COLOR_BGR2GRAY);
    //创建一个窗口
    namedWindow("win",WINDOW_FREERATIO);  
    //创建2个bar
    createTrackbar("DM1_block","win",&DM1,255,total_callback);
    createTrackbar("DM2_numdisp","win",&DM2,100,total_callback);
    createTrackbar("MinDisparity","win",&DM3,100,total_callback);
    createTrackbar("setTextureThreshold","win",&DM4,100,total_callback);
    createTrackbar("setPreFilterCap","win",&DM5,1.63,total_callback);
    createTrackbar("setUniquenessRatio","win",&DM6,100,total_callback);
    createTrackbar("setSpeckleWindowSize","win",&DM7,100,total_callback);
    createTrackbar("setSpeckleRange","win",&DM8,100,total_callback);
    //阻塞
    waitKey(0);
}
