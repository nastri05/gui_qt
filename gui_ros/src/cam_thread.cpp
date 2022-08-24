#include "cam_thread.h"
#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>

using namespace cv;
cam_thread::cam_thread(cv::VideoCapture *cap) : QObject(),cap(cap)
{
}

void cam_thread::handleFrame(){
//  *original= cv::imread("/home/hoangtuan/Pictures/anh1.png");
  cap->read(*original);

  cv::resize(*original,*original,cv::Size(300,200),cv::INTER_LINEAR);
  flip(*original,*original,1);
  cv::cvtColor(*original,*original,cv::COLOR_BGR2RGB);
  QImage qimgProcessed((uchar*)original->data,
                           original->cols,
                           original->rows,
                           original->step,
                           QImage::Format_RGB888);
  emit frameReady(qimgProcessed);

}
cam_thread::~cam_thread()
{
    if(cap->isOpened()) cap->release();
 }

