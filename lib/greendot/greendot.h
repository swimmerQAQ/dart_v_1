/**
 * @file greendot_h
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 绿灯.h文件
 * @version 1.0
 * @date 2022-01-27
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
class greendot
{
private:
    cv::Point2f _centre_green;
    float _area;
    //确认
    bool _is_green;
    //averge distance
    float _wideth;
public:
    greendot(){};
    bool is_match(std::vector<cv::Point>);
    void greendot_show(cv::Mat &origin);
    ~greendot(){};
    inline cv::Point2f get_centre_point(void){return _centre_green;};
    inline float get_wideth(void){ return _wideth; }
    cv::Point2f centrePoint(std::vector<cv::Point> in_contours);
};
using greendot_p = std::shared_ptr<greendot>;