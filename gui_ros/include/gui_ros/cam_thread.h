#ifndef CAM_THREAD_H
#define CAM_THREAD_H

#include <QObject>
#include<opencv2/highgui.hpp>
#include<QImage>
class cam_thread : public QObject
{
  Q_OBJECT
public:
  explicit cam_thread(QObject* parent = nullptr);
  ~cam_thread();
  cam_thread(cv::VideoCapture *cap);

signals:
  void frameReady(QImage );
  void Started();


public slots:
   void handleFrame();

private:
   cv::VideoCapture *cap = new cv::VideoCapture;
   cv::Mat *original = new cv::Mat;
};

#endif // CAM_THREAD_H
