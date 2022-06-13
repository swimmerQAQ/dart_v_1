/**
 * @file triangle_cpp
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 三角形.cpp文件
 * @version 1.0
 * @date 2022-02-06
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#include "triangle.h"
bool Triangle::match_margin(cv::Point2f _f_, cv::Point2f _s_, float _f_len, cv::Point2f _t_, cv::Point2f _fo_, float _s_len, cv::Point2f _fi_, cv::Point2f _l_, float _t_len)
{
    int flag=3;//后四个排序位
    int flag_1=-1;//所有排序位
    float temp[4];
    bar_1 = _f_;
    bar_2 = _s_;
    bar_3 = _t_;
    bar_4 = _fo_;
    bar_5 = _fi_;
    bar_6 = _l_;

    temp[0] = get_distance(_f_, _t_);
    temp[1] = get_distance(_f_, _fo_);
    temp[2] = get_distance(_f_, _fi_);
    temp[3] = get_distance(_f_, _l_);
    for (int i = 0; i < 4; i++)//从第一个点出发的最短距离点
    {
        if(compare(temp[0],temp[i]))
        {
            flag = i+3;//最小标志位
            temp[0] = temp[i];//用于后续对比使用
        }
    }
    t_edge[0].edge = temp[0];//存储第一个夹距
    if(flag > 4)//链接的 后一个灯条
    {
        temp[0] = get_distance(_s_, _t_); //第二点出发---所以找寻前一个灯条
        temp[1] = get_distance(_s_, _fo_);
        if (temp[0] > temp[1])
        {
            flag_1 = 4;
            t_edge[1].edge = temp[1];
            if (flag == 6)
            {
                t_edge[2].edge = get_distance(_t_, _fi_);//-------16-----24----35
                one = _f_;
                two = _l_;
                three = _s_;
                four = _fo_;
                five = _t_;
                six = _fi_;
            }
            else
            {
                t_edge[2].edge = get_distance(_t_, _l_);//---------15----24-----36
                one = _f_;
                two = _fi_;
                three = _s_;
                four = _fo_;
                five = _t_;
                six = _l_;
            }
        }else{
            flag_1 = 3;
            t_edge[1].edge = temp[0];
            if (flag == 6)
            {
                t_edge[2].edge = get_distance(_fo_, _fi_);//--------16--23--45
                one = _f_;
                two = _l_;
                three = _s_;
                four = _t_;
                five = _fo_;
                six = _fi_;
            }
            else
            {
                t_edge[2].edge = get_distance(_fo_, _l_);//------15----23---46
                one = _f_;
                two = _fi_;
                three = _s_;
                four = _t_;
                five = _fo_;
                six = _l_;
            }
        }
    }else{//链接的 前一个灯条
        temp[0] = get_distance(_s_, _fi_); //所以找寻后一个灯条
        temp[1] = get_distance(_s_, _l_);
        if (temp[0] > temp[1])
        {
            flag_1 = 6;
            t_edge[1].edge = temp[1];
            if (flag == 4)
            {
                t_edge[2].edge = get_distance(_fi_, _t_);//--------14-----26----35
                one = _f_;
                two = _fo_;
                three = _s_;
                four = _l_;
                five = _t_;
                six = _fi_;
            }
            else
            {
                t_edge[2].edge = get_distance(_fi_, _fo_);//------13----26----45
                one = _f_;
                two = _t_;
                three = _s_;
                four = _l_;
                five = _fo_;
                six = _fi_;
            }
        }else{
            flag_1 = 5;
            t_edge[1].edge = temp[0];
            if (flag == 4)
            {
                t_edge[2].edge = get_distance(_l_, _t_);//-------------14---25----36
                one = _f_;
                two = _fo_;
                three = _s_;
                four = _fi_;
                five = _t_;
                six = _l_;
            }
            else
            {
                t_edge[2].edge = get_distance(_l_, _fo_);//---------13-----25----46
                one = _f_;
                two = _t_;
                three = _s_;
                four = _fi_;
                five = _fo_;
                six = _l_;
            }
        }
    }
    score = fabs((t_edge[0].edge + t_edge[1].edge + t_edge[2].edge) / (_f_len + _s_len + _t_len));
    if (score < max_margin_propotion && score > min_margin_propotion)
    {
        is_triangle = true;
    }else{
        is_triangle = false;
    }
    return is_triangle;
}
bool Triangle::match_angle(float one, float two, float three)
{
    if (one == two || one == three || two == three)
    {
        return false;
    }
    float angle_temp[3];
    angle_temp[0] = one;
    angle_temp[1] = two;
    angle_temp[2] = three;
    if (angle_temp[0] < angle_temp[1]) //三元对比
    {
        angle_temp[0] = two;
        angle_temp[1] = one;
    }
    if (angle_temp[0] < angle_temp[2])
    {
        angle_temp[2] = angle_temp[0];
        angle_temp[0] = three;
    }
    if(angle_temp[1] < angle_temp[2])
    {
        float temp;
        temp = angle_temp[1];
        angle_temp[1] = angle_temp[2];
        angle_temp[2] = temp;
    }
    // (angle_temp[0] - angle_temp[1] - 60 + angle_temp[2] - angle_temp[1] + 60);----原型
    // angle_temp[1] + angle_temp[2] + 180 - 2*angle_temp[0]-------------------------推测公式
    // angle_temp[1] - 2*angle_temp[2] - 180 + angle_temp[0]-------------------------推测公式
    if (fabs(angle_temp[1] - 2 * angle_temp[2] - 180 + angle_temp[0]) < min_predict_angle && fabs(angle_temp[1] + angle_temp[2] + 180 - 2 * angle_temp[0]) < min_predict_angle)
    {
        return true;
    }
    if (fabs(angle_temp[1] + angle_temp[2] + 180 - 2 * angle_temp[0]) < min_predict_angle && fabs(angle_temp[1] - 2 * angle_temp[2] - 180 + angle_temp[0]) > max_predict_angle)
    {
        return true;
    }
    if (fabs(angle_temp[1] - 2 * angle_temp[2] - 180 + angle_temp[0]) < min_predict_angle && fabs(angle_temp[1] + angle_temp[2] + 180 - 2 * angle_temp[0]) > max_predict_angle)
    {
        return true;
    }
    // std::cout << min_predict_angle << " " << max_predict_angle << std::endl;
    // std::cout << fabs(angle_temp[1] + angle_temp[2] + 180 - 2 * angle_temp[0]) << " ????? "
    //           << fabs(angle_temp[1] - 2 * angle_temp[2] - 180 + angle_temp[0]) << std::endl;
    return false;
}
bool Triangle::match_three(cv::Point2f _f_, cv::Point2f _s_, cv::Point2f _t_, cv::Point2f _fo_, cv::Point2f _fi_, cv::Point2f _l_)
{
    float k[3],b[3]; cv::Point2f temp[3];
    temp[0] = (_f_ + _s_) / 2;
    temp[1] = (_t_ + _fo_) / 2;
    temp[2] = (_fi_ + _l_) / 2;
    k[0] = func_k(_f_, _s_);
    k[1] = func_k(_t_, _fo_);
    k[2] = func_k(_fi_, _l_);
    for (int i = 0; i < 3; i++)
    {
        b[i] = temp[i].y - temp[i].x * k[i];
    }
    if (k[0] == k[1] || k[0] == k[2] || k[1] == k[2])//平行
    {
        return false;
    }
    //1和2
    temp[0].x = (b[1] - b[0]) / (k[0] - k[1]);
    temp[0].y = (k[0] * b[1] - k[1] * b[0]) / (k[0] - k[1]);
    //2和3
    temp[1].x = (b[2] - b[1]) / (k[1] - k[2]);
    temp[1].y = (k[1] * b[2] - k[2] * b[1] )/ (k[1] - k[2]);
    //3和1
    temp[2].x = (b[0] - b[2]) / (k[2] - k[0]);
    temp[2].y = (k[2] * b[0] - k[0] * b[2]) / (k[2] - k[0]);
    k[0] = get_distance(temp[0], temp[1]);
    k[1] = get_distance(temp[1], temp[2]);
    k[2] = get_distance(temp[2], temp[0]);
    one = temp[0];
    two = temp[1];
    three = temp[2];
    score = fabs(k[0] + k[1] + k[2])/3;
    if (score > three_scale)
    {
        return false;
    }
    score = score / k[0] + score / k[1] + score / k[2];
    if (score < max_three_propotion && score > min_three_propotion) //放大
    {
        is_triangle = true;
    }
    return is_triangle;
}
float Triangle::func_k(cv::Point2f one, cv::Point2f two)
{
    float k;
    if(one.x == two.x)
    {
        return 1000;
    }
    if(one.y == two.y)
    {
        return 0;
    }
    k = (one.x - two.x)/(two.y - one.y);
    if(k > 1000)
    {
        return 1000;
    }
    return k;
}
float Triangle::get_score(void)
{
    return score;
}
float Triangle::get_distance(cv::Point2f p1, cv::Point2f p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
bool Triangle::compare(float one, float two)//三次对比
{
    if(one < two)
    {
        return false;
    }
    return true;
}
void Triangle::Read_model_p(const std::string &path)
{
    cv::FileStorage buffer(path, cv::FileStorage::READ);
    buffer["max_predict_angle"] >> this->max_predict_angle; 
    buffer["min_predict_angle"] >> this->min_predict_angle;
    buffer["three_scale"] >> this->three_scale;
    buffer["max_three_propotion"] >> this->max_three_propotion;
    buffer["min_three_propotion"] >> this->min_three_propotion;
    buffer["max_margin_propotion"] >> this->max_margin_propotion;
    buffer["min_margin_propotion"] >> this->min_margin_propotion;
}