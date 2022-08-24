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
#include<cam_thread.h>
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

public slots:
  void spinOnce();
  void imageCallback(const sensor_msgs::ImageConstPtr& msg);
  void imshowImage();
  void onFrame(QImage src);
  void onFix();
private:
  Ui::Ros_Gui *ui;
  ros::NodeHandlePtr nhPt_;
  ros::NodeHandle nh_;
  QTimer *cam_timer;
  QTimer *ros_timer;
  QThread *qth =new QThread ;
  cam_thread *handler  ;

signals:
private slots:
  void on_pushButton_clicked();
};



#endif // ROS_GUI_H
