/**
 * @file invertimg_h
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 图像预处理.h文件
 * @version 1.0
 * @date 2022-01-26
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#pragma once
#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/videoio.hpp>
class invert_img
{
    private:
    //帧数
    double frame_count=0;
    //帧率
    double fps=0;
    //capture
    cv::VideoCapture capture_p;
    //mat
    cv::Mat image;
    //cv::Mat clone()
    cv::Mat green_clone;
    cv::Mat bar_clone;
    /////// read parameter
    float exposure;
    float brigthness;
    void Read_video_p(const std::string &path);

    public :
    //初始化摄像头 1 and 0
    invert_img(){};
    void init_camera(int type);
    //视频
    void init_video(std::string path);
    ~invert_img()
    {
        capture_p.release();
        // delete capture_p;
        // delete image;
        // delete green_clone;
        // delete bar_clone;
    };

    //setting camera !
    void set_cap(int flag);
    void read_camera(int flag);

    void security(void);

    void operate_img(int flag);
    void cap_blue(void);
    void cap_red(void);

    // get parameters
    double get_fps(void);
    inline cv::Mat get_bar(void) { return bar_clone; }
    inline cv::Mat get_green(void) { return green_clone; }
    inline cv::Mat get_origin(void) {  return image; }
};
using invert_sp = std::shared_ptr<invert_img>;