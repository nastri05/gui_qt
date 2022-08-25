#ifndef ROS_GUI_H
#define ROS_GUI_H
#include <QWidget>
#include<ros/ros.h>
#include<qtimer.h>
#include <image_transport/image_transport.h>
#include<opencv2/highgui.hpp>
#include<cv_bridge/cv_bridge.h>
#include<QThread>
#include<QObject>
#include<QImage>


namespace Ui {
class Ros_Gui;
}

class Ros_Gui : public QWidget
{
  Q_OBJECT

public:
  explicit Ros_Gui(QWidget *parent = nullptr);
  ~Ros_Gui();
  void imageCallback(const sensor_msgs::ImageConstPtr& msg);
public slots:
  void spinOnce();
  void onFrame(QImage src);
  void onFix();
  void spiNed();
  void onInt(int x);
private:
  Ui::Ros_Gui *ui;
  ros::NodeHandlePtr nhPt_;
  ros::NodeHandle nh_;
  QTimer *cam_timer;
  QTimer *ros_timer;
  image_transport::ImageTransport *it_ = new image_transport::ImageTransport(nh_);
  image_transport::Subscriber sub;
  QThread *qth =new QThread ;
  int m_argc;
  char **m_argv;


signals:
  void frameReady(QImage);
  void changeInt(int);
private slots:
  void on_pushButton_clicked();


};



#endif // ROS_GUI_H
