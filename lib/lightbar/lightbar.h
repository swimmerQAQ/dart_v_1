/**
 * @file lightbar_h
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 灯条.h文件
 * @version 1.0
 * @date 2022-01-27
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#pragma once
#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
class Lightbar
{
private:
    /* basic feature */
    bool _is_bar = false;
    float _angle;
    float _wideth;
    float _height;
    cv::Point2f centre_p;
    cv::Point2f four_pp[4];
    /*using for triangle and more powerful feature*/
    cv::Point2f _h_point;
    cv::Point2f _w_point;
public:
    Lightbar(){};
    //匹配
    bool is_match(std::vector<cv::Point>);
    void fpp_show(cv::Mat& origin);


    //不需要保护-关于sharedptr
    //通用函数
    inline float get_shorter(void)
    {
        if (_height > _wideth)
        {
            return _wideth;
        }
        else
        {
            return _height;
        }
        return _height;
    };
    inline float get_longer(void)
    {

        if (_height > _wideth)
        {
            return _height;
        }
        else
        {
            return _wideth;
        }
        return _wideth;
    }
    inline cv::Point2f get_h_point(void) { return _h_point; }
    inline cv::Point2f get_w_point(void) { return _w_point; }
    inline cv::Point2f get_centre(void){return centre_p;}
    inline float get_angle(void){return _angle;}
    cv::Point2f get_fpp(int num);
    ~Lightbar(){};
};
using lightbar_p = std::shared_ptr<Lightbar>;