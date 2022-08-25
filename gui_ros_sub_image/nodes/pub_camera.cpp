#include<image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include<ros/ros.h>
#include <opencv2/highgui.hpp>

using namespace cv;

int main(int argc, char **argv){
  ros::init(argc, argv, "listener");
  ros::NodeHandle nh_;
  image_transport::ImageTransport it(nh_);
  image_transport::Publisher pub = it.advertise("camera/image",1);

VideoCapture cap;
Mat Matvideo;
cap.open(0,cv::CAP_V4L2);

             //read video frame from camera and show in windows
while(true){
             cap.read(Matvideo);
//Matvideo = imread("/home/hoangtuan/Pictures/anh1.png");
             flip(Matvideo,Matvideo,1);
             sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",Matvideo).toImageMsg();

             imshow("VideoCapture", Matvideo);
             pub.publish(msg);
             ros::spinOnce();
             char c=(char)waitKey(33);
                if(c==27)
                  break;



}

     return 0;

}
