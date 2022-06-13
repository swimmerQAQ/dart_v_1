/**
 * @file triangle_cpp
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 三角形.h文件
 * @version 1.0
 * @date 2022-02-06
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#include <opencv2/core/types.hpp>
#include <memory>
#include <opencv2/core/persistence.hpp>
#include <iostream>
struct triangle_edge
{
    float edge;
    float angle;
};
class Triangle
{
private:
    float score=10000;
    triangle_edge t_edge[3];
    bool is_triangle = false;

    cv::Point2f one;//test
    cv::Point2f two;
    cv::Point2f three;
    cv::Point2f four;
    cv::Point2f five;
    cv::Point2f six;

    cv::Point2f bar_1;//three bars
    cv::Point2f bar_2;
    cv::Point2f bar_3;
    cv::Point2f bar_4;
    cv::Point2f bar_5;
    cv::Point2f bar_6;
    ///read parameter
    float max_predict_angle;
    float min_predict_angle;
    float three_scale;
    float max_three_propotion;
    float min_three_propotion;
    float max_margin_propotion;
    float min_margin_propotion;
    void Read_model_p(const std::string &path);

public:
    Triangle() { Read_model_p("/home/ksc/Documents/Project_Base/raspberry2/parameter/model.yml"); };
    ~Triangle(){};

    bool match_margin(cv::Point2f _f_, cv::Point2f _s_, float _f_len, cv::Point2f _t_, cv::Point2f _fo_, float _s_len, cv::Point2f _fi_, cv::Point2f _l_, float _t_len);
    bool match_angle(float one, float two, float three);
    bool match_three(cv::Point2f _f_, cv::Point2f _s_, cv::Point2f _t_, cv::Point2f _fo_, cv::Point2f _fi_, cv::Point2f _l_);
    //垂线k
    float func_k(cv::Point2f one, cv::Point2f two);
    float get_score(void);

    float get_distance(cv::Point2f p1, cv::Point2f p2);
    cv::Point2f get_one(void) { return one; } //、、、、、、、、、、、、、、、、、、、、 test
    cv::Point2f get_two(void) { return two; } // test
    cv::Point2f get_three(void) { return three; } // test
    cv::Point2f get_four(void) { return four; } // test
    cv::Point2f get_five(void) { return five; } // test
    cv::Point2f get_six(void) { return six; }   // test
    cv::Point2f get_bar_1(void) { return bar_1; } //、、、、、、、、、、、、、、、、、  bar
    cv::Point2f get_bar_2(void) { return bar_2; } // test
    cv::Point2f get_bar_3(void) { return bar_3; } // test
    cv::Point2f get_bar_4(void) { return bar_4; } // test
    cv::Point2f get_bar_5(void) { return bar_5; } // test
    cv::Point2f get_bar_6(void) { return bar_6; }   // test
    bool compare(float one, float two);
};
using triangle_p = std::shared_ptr<Triangle>;