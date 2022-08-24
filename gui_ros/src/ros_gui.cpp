#include "ros_gui.h"
#include "ui_ros_gui.h"
#include"cam_thread.h"
Ros_Gui::Ros_Gui(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Ros_Gui)
{
  ui->setupUi(this);
  nhPt_.reset(new ros::NodeHandle("~"));
  cv::VideoCapture *cap1 = new cv::VideoCapture(0,cv::CAP_V4L2);
  ros_timer = new QTimer(this);
  cam_timer = new QTimer(this);
  connect(ros_timer,SIGNAL(timeout()),this,SLOT(spinOnce()));
  ros_timer->start(30);
  handler = new cam_thread(cap1);
  cam_timer->setInterval(60);
  QObject::connect(cam_timer,SIGNAL(timeout()),handler,SLOT(handleFrame()));
  QObject::connect(handler, SIGNAL(frameReady(QImage)),this,SLOT(onFrame(QImage)));
//  QObject::connect(qth,SIGNAL(started()),&cam_timer,SLOT(start()));
//  QObject::connect(ui->pushButton,SIGNAL(clicked()),&handler,SLOT(handleFrame()));
  cam_timer->start();
  handler->moveToThread(qth);
  cam_timer->moveToThread(qth);
  qth->start();
}

Ros_Gui::~Ros_Gui()
{
  delete ui;
}
void Ros_Gui::spinOnce(){
  if(ros::ok()){

    ros::spinOnce();

  }
  else
      QApplication::quit();
}
void Ros_Gui::imageCallback(const sensor_msgs::ImageConstPtr& msg)
   {
      try
      {
       cv::Mat img = cv_bridge::toCvShare(msg, "bgr8")->image;
       cv::Mat resized_down;

         cv::resize(img, resized_down,cv::Size(300,200),cv::INTER_LINEAR);

       cv::imshow("view",resized_down );
       cv::waitKey(1);

     }
     catch (cv_bridge::Exception& e)
    {
       ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
   }
void Ros_Gui::imshowImage(){
image_transport::ImageTransport it_(nh_);
image_transport::Subscriber sub = it_.subscribe("/camera/image", 1,&Ros_Gui::imageCallback,this);

ros::spin();
}

void Ros_Gui::on_pushButton_clicked()
{
  ui->pushButton->setText("haler");
}
void Ros_Gui::onFrame(QImage src){

  //ui->pushButton->setText("hello");
  ui->label->setPixmap(QPixmap::fromImage(src));
}
void Ros_Gui::onFix(){
  ui->pushButton->setText("dmcsa");
}
