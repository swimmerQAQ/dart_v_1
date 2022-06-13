/**
 * @file greendot_cpp
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 绿灯.cpp文件
 * @version 1.0
 * @date 2022-01-27
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#include "greendot.h"
using namespace cv;
using namespace std;
bool greendot::is_match(std::vector<cv::Point> contours)
{   
    _area = contourArea(contours);
    if(_area > 50)
    {
        RotatedRect temp = minAreaRect(contours);
        if(temp.size.height/temp.size.height < 1.1 && temp.size.height/temp.size.height > 0.9)
        {
            _centre_green = centrePoint(contours);
            _is_green = true;
            _wideth = (temp.size.height+temp.size.height)/2;
            return true;
        }
    }
    _is_green = false;
    return false;
}
void greendot::greendot_show(cv::Mat &origin)
{
    // line(*origin, _centre_green,_centre_green - cv::Point2f(0,12) , Scalar(0,255,255),2);
    // line(*origin, _centre_green - cv::Point2f(-6,6),_centre_green - cv::Point2f(6,6) , Scalar(0,255,255),2);
    // line(*origin, _centre_green,_centre_green - cv::Point2f(-6,0) , Scalar(0,255,255),2);
    // line(*origin, _centre_green - cv::Point2f(-6,0),_centre_green - cv::Point2f(-6,3) , Scalar(0,255,255),2);

    // line(*origin, _centre_green- cv::Point2f(12,18),_centre_green - cv::Point2f(-12,18) , Scalar(0,255,255),2);
    // line(*origin, _centre_green- cv::Point2f(-9,15),_centre_green - cv::Point2f(-12,18) , Scalar(0,255,255),2);
    // line(*origin, _centre_green- cv::Point2f(12,18),_centre_green - cv::Point2f(12,-18) , Scalar(0,255,255),2);
    // line(*origin, _centre_green- cv::Point2f(18,-24),_centre_green - cv::Point2f(12,-18) , Scalar(0,255,255),2);
    // line(*origin, _centre_green- cv::Point2f(18,-24),_centre_green - cv::Point2f(21,-27) , Scalar(0,255,255),2);

    // line(*origin, _centre_green- cv::Point2f(0,18),_centre_green - cv::Point2f(0,26) , Scalar(0,255,255),2);
    // line(*origin, _centre_green- cv::Point2f(0,22),_centre_green - cv::Point2f(-6,22) , Scalar(0,255,255),2);

    // line(*origin, _centre_green- cv::Point2f(6,-6),_centre_green - cv::Point2f(-6,-6) , Scalar(0,255,255),2);
    // line(*origin, _centre_green- cv::Point2f(6,-24),_centre_green - cv::Point2f(6,-6) , Scalar(0,255,255),2);
    // line(*origin, _centre_green- cv::Point2f(6,-24),_centre_green - cv::Point2f(9,-27) , Scalar(0,255,255),2);
    // line(*origin, _centre_green- cv::Point2f(-6,-6),_centre_green - cv::Point2f(-6,-27) , Scalar(0,255,255),2);
    // line(*origin, _centre_green- cv::Point2f(-12,-27),_centre_green - cv::Point2f(-6,-27) , Scalar(0,255,255),2);
    // line(*origin, _centre_green- cv::Point2f(-12,-27),_centre_green - cv::Point2f(-12,-20) , Scalar(0,255,255),2);
    circle(origin, _centre_green, 6, Scalar(255,255,0),2);
    // circle(*origin, _centre_green, 6, Scalar(0, 0, 255), 3);
}
cv::Point2f greendot::centrePoint(std::vector<cv::Point> in_contours)
{
    vector<Point> contours_Bulf;
    contours_Bulf = in_contours;
    Point2f centre;
    Moments contours_moments;
    contours_moments = moments(contours_Bulf);
    centre = Point(static_cast<float>(contours_moments.m10 / contours_moments.m00), static_cast<float>(contours_moments.m01 / contours_moments.m00));

    return centre;
}