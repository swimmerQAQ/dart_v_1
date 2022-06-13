/**
 * @file lightbar_cpp
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 灯条.cpp文件
 * @version 1.0
 * @date 2022-01-27
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#include "lightbar.h"
using namespace cv;
using namespace std;
bool Lightbar::is_match(std::vector<cv::Point> a_contour)
{
    float area = contourArea(a_contour);
    if(area > 5)//===============================area面积
    {
        RotatedRect temp = minAreaRect(a_contour);
        // cout << "proportion " << (temp.size.width / temp.size.height) << endl;
        if ((temp.size.width / temp.size.height) < 1.2 && (temp.size.width / temp.size.height) > 0.6)
        {
            return false;
        }
        temp.points(four_pp);
        _angle = temp.angle;
        _wideth = temp.size.width;
        _height = temp.size.height;
        // cout << "the width height angle" << _wideth<<" " << _height <<" " << _angle << endl;
        if(_wideth  < _height)
        {
            _h_point = (four_pp[1] + four_pp[2]) / 2;
            _w_point = (four_pp[0] + four_pp[3]) / 2;
            _angle = 90 - _angle;
        }else{
            _h_point = (four_pp[0] + four_pp[1]) / 2;
            _w_point = (four_pp[2] + four_pp[3]) / 2;
            _angle = 180 - _angle;
        }

        // cout << "after angle" << _angle << endl;
        centre_p = temp.center;
        _is_bar = true;
        return true;
    }
    return false;
}
void Lightbar::fpp_show(Mat& origin)
{
    if(!_is_bar)
    {
        return;
    }
    // if(_angle > 80)
    {
    circle(origin, four_pp[0], 1, Scalar(255, 0, 0), -1);//blue
    circle(origin, four_pp[1], 1, Scalar(0, 255, 0), -1);//green
    circle(origin, four_pp[2], 1, Scalar(0, 0, 255), -1);//red
    circle(origin, four_pp[3], 1, Scalar(255, 255, 255), -1);//white

    }
    
}
cv::Point2f Lightbar::get_fpp(int num)
{
    if(num>3 || num < 0)
    {
        return Point2f(0,0);
        cout << "Invalid get fp points" << endl;
    }
    return four_pp[num];
}