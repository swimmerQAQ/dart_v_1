/**
 * @file predict_H
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief predict.h文件
 * @version 1.0
 * @date 2022-03-12
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#pragma once
#include <opencv2/imgproc.hpp>
#include <math.h>
#include <memory>
#include "../serialPort/SerialPort.h"
#define PI 3.141592
struct SendData
{
    /* distance & angle */
    float dist;
    cv::Point2f angle;
};

class Predict
{
private:
    /* 标志位flag 0 1 2 3 */
    int _flag=0;
    /* loacal one triangle pnp */
    cv::Point2f _tri_1;
    cv::Point2f _tri_2;
    cv::Point2f _tri_3;
    cv::Point2f _tri_4;
    cv::Point2f _tri_5;
    cv::Point2f _tri_6;

    /**
     * @brief read the data in the model
     * @param _greendot             green_light (Point)                                             high convince
     * @param _bar_dot_dis          bar to greenlight (distance)                                    low convince
     * @param _pre_bar              the Point of bar                                                low convince
     * @param _bias_dot             only a dot                                                      high convince
     * 
     * @brief read in the triangle
     * @param _green_triangle_dist  the distance from triangle to dot;(in the high _Y_principle_ )   high convince
     * 
     * case 0 nothing
     * case 1 only dot (maybe a pre bar & nothing we get bias)
     * case 2 only triangle ( match in the principle high _Y_ )// deceded by installation of camera
     * case 3 have triangle and dot
     * 
     */
    cv::Point2f _greendot;
    float _bar_dot_dis;
    cv::Point2f _pre_bar = cv::Point2f(-1.0,-1.0);
    cv::Point2f _green_triangle_;
    cv::Point2f _bias_dot;
    /* using count distance */
    float _k_dist;
    /* anti_point */
    cv::Point2f _anti_point;
    /* send data */
    SendData SD;


    /*read matrix*/
    void Read_pre(const std::string &path);
    cv::Mat cam_mx;
    cv::Mat dis_mx;

    /*serial port*/
    SerialPort Port;
public:
    Predict(/* args */){ Read_pre("/home/ksc/Documents/Project_Base/raspberry2/parameter/predict.yml"); };
    ~Predict(){};
    void predict_inition(void);

    /*--------------reading in model----------------*/
    void read_point(cv::Point2f tri_1,
                    cv::Point2f tri_2, cv::Point2f tri_3,
                    cv::Point2f tri_4, cv::Point2f tri_5,
                    cv::Point2f tri_6);
    void read_point(cv::Point2f greendot);
    void read_bar(cv::Point2f bar_point);

    /* greendot and triangle (combine functions: bias_dot() only_tri() ) */
    void match(void);
    /* only _greendot */
    void bias_dot(void);
    /* only greendot */
    void a_tri(void);
    /* update flag */
    void set_flag(int flag){_flag = flag;}
    inline int ret_flag(void){ return _flag; }

 
    cv::Point2f predict_some_fucking_thing(void);
    cv::Point2f calculateRelativeAngle(const cv::Mat &cameraMatrix, cv::Point2f center);
    inline float rad2deg(float rad){ return rad* 180.f / PI; }

    /*test print*/
    void displace(void);
    /*get_distance*/
    float get_distance(cv::Point2f p1, cv::Point2f p2);
};
using predict_sp = std::shared_ptr<Predict>;

