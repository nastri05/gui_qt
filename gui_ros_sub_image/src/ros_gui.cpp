#include "ros_gui.h"
#include "ui_ros_gui.h"

Ros_Gui::Ros_Gui(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Ros_Gui)
{
  ui->setupUi(this);
  nhPt_.reset(new ros::NodeHandle("~"));
  ros_timer = new QTimer(this);
  //ros::init(m_argc, m_argv, "camera_check");
  cam_timer = new QTimer(this);
  sub = it_->subscribe("/camera/image",100,&Ros_Gui::imageCallback,this);

//  cam_timer->setInterval(30);
 connect(cam_timer,SIGNAL(timeout()),this,SLOT(spinOnce()));
 connect(this,SIGNAL(frameReady(QImage)),this,SLOT(onFrame(QImage)));
 connect(this,SIGNAL(changeInt(int)),this,SLOT(onInt(int)));

  cam_timer->start(100);

}

Ros_Gui::~Ros_Gui()
{
  delete ui;
}
void Ros_Gui::spinOnce(){
  if(ros::ok()){
     //ui->label->setText("hien len");
     ros::spinOnce();

  }
  else
      QApplication::quit();
}
void Ros_Gui::spiNed(){
  if(ros::ok()){
    ros::spin();
  }

}
void Ros_Gui::imageCallback(const sensor_msgs::ImageConstPtr& msg)
   {
      try
      {
       cv::Mat img = cv_bridge::toCvShare(msg, "bgr8")->image;

         cv::resize(img, img,cv::Size(300,200),cv::INTER_LINEAR);
         cv::cvtColor(img,img,cv::COLOR_BGR2RGB);
         QImage qimgProcessed((uchar*)img.data,
                                   img.cols,
                                   img.rows,
                                   img.step,
                                   QImage::Format_RGB888);
         //ui->label->setPixmap(QPixmap::fromImage(qimgProcessed));

         //cv::imshow("anh",img);
         emit frameReady(qimgProcessed);
     }
     catch (cv_bridge::Exception& e)
    {
       ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }

   }


void Ros_Gui::on_pushButton_clicked()
{
  ui->pushButton->setText("haler");
  for(int i = 0 ; i< 1000;i++){
    emit changeInt(i);
    QThread::msleep(1000);
  }

}
void Ros_Gui::onFrame(QImage src){

  //ui->pushButton->setText("hello");
  ui->label->setPixmap(QPixmap::fromImage(src));
}
void Ros_Gui::onFix(){
  ui->pushButton->setText("dmcsa");
}
void Ros_Gui::onInt(int x){
  ui->label_2->setText(QString::number(x));
}
