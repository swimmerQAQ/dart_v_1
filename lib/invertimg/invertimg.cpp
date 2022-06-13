/**
 * @file invert_h
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 图形转换cpp文件
 * @version 1.0
 * @date 2022-01-26
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#include "invertimg.h"
using namespace cv;
using namespace std;
//初始化摄像头 1 and 0
void invert_img::init_camera(int type)
{
    /* code */
    capture_p = VideoCapture(type);
    Read_video_p("/home/ksc/Documents/Project_Base/raspberry2/parameter/videocapture.yml");
    // capture_p->set(CAP_PROP_FRAME_HEIGHT,720);
    // capture_p->set(CAP_PROP_FRAME_WIDTH,1280);
    if (!capture_p.isOpened())
    {
        cout << "Can not open camera !" << endl;
    }
}
void invert_img::init_video(string path)
{
    capture_p = VideoCapture(path);
    if (!capture_p.isOpened())
    {
        cout << "cannot read video!" << endl;
        return;
    }
}
// setting camera ! 设置参数-----曝光 ---- 亮度
// wait test !
void invert_img::set_cap(int flag)
{
    if (!capture_p.isOpened())
    {
        cout << "Invalid capture_p(nullptr) !" << endl;
        return;
    }
    capture_p.set(CAP_PROP_AUTO_EXPOSURE, 1);
    capture_p.set(CAP_PROP_EXPOSURE, exposure); //曝光
    capture_p.set(CAP_PROP_BRIGHTNESS, brigthness);
}
void invert_img::read_camera(int color)
{ // color暂时没有用，暂时不确定怎么筛选红蓝色
    if (!capture_p.isOpened())
    {
        cout << " Error, you cannot get image in matrix ! " << endl;
        return;
    }
    capture_p.read(image);
    bar_clone = Mat::zeros(image.size(),CV_8UC1);
    green_clone = Mat::zeros(image.size(),CV_8UC1);
    switch (color)
    {
    case 0:
        cap_blue();
        break;
    case 2:
        cap_red();
        break;
    default:
        cout << "Invalid setting the color selection!!!" << endl;
        cout << "Can not select your color, dangerous!! check your operate_img()" << endl;
        break;
    }
}
void invert_img::operate_img(int flag)
{
    if (!capture_p.isOpened())
    {
        cout << " Error, you cannot get image in matrix ! " << endl;
        return;
    }
    capture_p.read(image);
    bar_clone = Mat::zeros(image.size(),CV_8UC1);
    green_clone = Mat::zeros(image.size(),CV_8UC1);
    switch (flag)
    {
    case 0:
        cap_blue();
        // cap_green();
        break;
    case 2:
        cap_red();
        // cap_green();
        break;
    default:
        cout << "Invalid setting the color selection!!!" << endl;
        cout << "Can not select your color, dangerous!! check your operate_img()" << endl;
        break;
    }
}
void invert_img::security(void)
{
}

// get parameters
double invert_img::get_fps(void)
{
    if (!capture_p.isOpened())
    {
        cout << "Invalid capture_p(nullptr) !" << endl;
        return 0;
    }
    fps = capture_p.get(CAP_PROP_FPS);
    return fps;
}
// set_color!
void invert_img::cap_blue()
{
    parallel_for_(Range(0, image.rows),
                  [&](const Range &range)
                  {
                      for (int row = range.start; row < range.end; row++)
                      {
                          uchar *data_src = image.ptr<uchar>(row);
                          uchar *bar_bin = bar_clone.ptr<uchar>(row);
                          uchar *green_bin = green_clone.ptr<uchar>(row);
                          
                          for (int col = 0; col < image.cols; col++)
                          { //蓝-绿-红
                              if (data_src[3 * col + 1] > 90 && data_src[3 * col + 1] - data_src[3 * col + 0] > 50)
                              {
                                  green_bin[col] = 255;
                              }
                              if ( data_src[3 * col + 0] > 90 && data_src[3 * col + 0] - data_src[3 * col + 1] > 50)
                              {
                                  bar_bin[col] = 255;
                              }
                              /*----------------------------*/
                          }
                      }
                  });
}
void invert_img::cap_red()
{
    parallel_for_(Range(0, image.rows),
                  [&](const Range &range)
                  {
                      for (int row = range.start; row < range.end; row++)
                      {
                          uchar *data_src = image.ptr<uchar>(row);
                          uchar *bar_bin = bar_clone.ptr<uchar>(row);
                          uchar *green_bin = green_clone.ptr<uchar>(row);
                          for (int col = 0; col < image.cols; col++)
                          { //蓝-绿-红
                              if (data_src[3 * col + 2] > 90 && data_src[3 * col + 2] - data_src[3 * col] > 30)
                              { //原图条件 -》 bin -》 bar_clone
                                bar_bin[col] = 255;
                              }
                              if (data_src[3 * col + 1] > 90 && data_src[3 * col + 1] - data_src[3 * col + 0] > 30)
                              { //原图条件 -》 bin -》 bar_clone
                                green_bin[col] = 255;
                              }
                          }
                      }
                  }
                );
}
void invert_img::Read_video_p(const string &path)
{
    FileStorage buffer(path, FileStorage::READ);
    buffer["camera_exposure"] >> this->exposure;
    buffer["camera_brigthness"] >> this->brigthness;
    cout << "read parameter!" << brigthness << " " << exposure << endl;
}