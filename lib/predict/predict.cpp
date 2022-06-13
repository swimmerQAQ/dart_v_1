/**
 * @file predict_cpp
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief predict.cpp文件
 * @version 1.0
 * @date 2022-03-12
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#include "predict.h"
#include <iostream>
using namespace std;
void Predict::read_point(cv::Point2f tri_1 ,
                cv::Point2f tri_2 , cv::Point2f tri_3 ,
                cv::Point2f tri_4 , cv::Point2f tri_5 ,
                cv::Point2f tri_6 )
                {
                    _tri_1 = tri_1;
                    _tri_2 = tri_2;
                    _tri_3 = tri_3;
                    _tri_4 = tri_4;
                    _tri_5 = tri_5;
                    _tri_6 = tri_6;
                }
void Predict::read_point(cv::Point2f greendot)
{
    _greendot = greendot;
}
void Predict::read_bar(cv::Point2f bar_point)
{
    _pre_bar = bar_point;
}
void Predict::match()//flag = 3
{
    float dis_1 = get_distance((_tri_1 + _tri_2) / 2, _greendot);
    float dis_2 = get_distance((_tri_3 + _tri_4) / 2, _greendot);
    float dis_3 = get_distance((_tri_5 + _tri_6) / 2, _greendot);
    int min_dis = 0;
    float temp = 0;
    if(dis_1 >= dis_2)
    {
        temp = dis_2;
        min_dis = 2;
    }
    else
    {
        temp = dis_1;
        min_dis = 1;
    }
    if(temp >= dis_3)
    {
        temp = dis_3;
        min_dis = 3;
    }
    //can get distance
    //temp
    switch (min_dis)
    {
    case 1:
        /* code */
        _green_triangle_ = (_greendot - (_tri_1 + _tri_2)/2 )*2/5 + (_tri_1 + _tri_2)/2;
        break;
    case 2:
        /* code */
        _green_triangle_ = (_greendot - (_tri_3 + _tri_4)/2 )*2/5 + (_tri_3 + _tri_4)/2;
        break;
    case 3:
        /* code */
        _green_triangle_ = (_greendot - (_tri_5 + _tri_6)/2 )*2/5 + (_tri_5 + _tri_6)/2;
        break;
    default:
        break;
    }
    // std::cout << "angle = " << calculateRelativeAngle(cam_mx,_green_triangle_) << std::endl;
    SD.angle = calculateRelativeAngle(cam_mx,_green_triangle_);
    SD.dist = 617.719*0.24/temp;//wait check the distance------green----tri
}
void Predict::bias_dot()//flag = 1
{
    if(_pre_bar.x < 0)
    {
        _bias_dot = _greendot;
    }
    else
    {
        _bias_dot = (_greendot - _pre_bar)*1/3 + _pre_bar;
        // _bias_dot = _greendot;
        SD.dist = 617.719*0.14/get_distance(_bias_dot,_greendot);
    }
    // std::cout << "angle = " << calculateRelativeAngle(cam_mx,_greendot) << std::endl;
    SD.angle = calculateRelativeAngle(cam_mx,_greendot);
}
void Predict::a_tri()//flag = 2
{
    float dis_1 = get_distance(_tri_1 , _tri_2);
    float dis_2 = get_distance(_tri_3 , _tri_4);
    float dis_3 = get_distance(_tri_5 , _tri_6);
    float max_distance = 0;
    int flag = 0;
    float temp;
    if(dis_1 >= dis_2)
    {
        flag = 1;
        temp = dis_1;
    }
    else
    {
        flag = 2;
        temp = dis_2;
    }
    if(temp <= dis_3)
    {
        temp = dis_3;
        flag = 3;
    }
    double left;
    double right;
    /// 617.719 = F   real_dis * F / pix_dis = distance

    double k=1,ssd=700,d_dis,sin_tri; 
    switch (flag)
    {
    case 1:
        /* code */
        max_distance = dis_1;
        k = (ssd-get_distance((_tri_1 + _tri_2)/2,(_tri_3 + _tri_4 + _tri_5 + _tri_6)/4) )/ssd;
        _anti_point = ((_tri_1 + _tri_2)/2 - (_tri_3 + _tri_4 + _tri_5 + _tri_6)/4)*1.7*k + (_tri_1 + _tri_2)/2;
        

        left = dis_2; right = dis_3;
        if(left < right)
        {
            double temp;
            temp = left;
            left = right;
            right = temp; 
        }

        d_dis = abs(617.719*0.05/left - 617.719*0.05/right);
        sin_tri;
        if(d_dis<=0.124)
        {
            sin_tri = d_dis/0.124;
        }
        else
        {
            sin_tri = 1;
        }

        // count distance

        SD.dist = 617.719*0.05*sin_tri/temp;
        std::cout << " k = " << k << " distance_static = " << get_distance(_anti_point,(_tri_1 + _tri_2)/2) << std::endl;
        break;
    case 2:
       /* code */
       max_distance = dis_2;
       k = (ssd - get_distance((_tri_3 + _tri_4)/2 , (_tri_1 + _tri_2 + _tri_5 + _tri_6)/4) )/ssd;
       _anti_point = ((_tri_3 + _tri_4)/2 - (_tri_1 + _tri_2 + _tri_5 + _tri_6)/4)*1.7*k + (_tri_3 + _tri_4)/2;
      
       left = dis_1; right = dis_3;
        if(left < right)
        {
            double temp;
            temp = left;
            left = right;
            right = temp;
        }
        
        d_dis = abs(617.719*0.05/left - 617.719*0.05/right);
        sin_tri;
        if(d_dis<=0.124)
        {
            sin_tri = d_dis/0.124;
        }
        else
        {
            sin_tri = 1;
        }
        SD.dist = 617.719*0.05*sin_tri/temp;
        // count distance
        std::cout << " k = " << k << " distance_static = " << get_distance(_anti_point,(_tri_3 + _tri_4)/2) << std::endl;
       break;
    case 3:
        /* code */
        max_distance = dis_3;
        k = (ssd - get_distance((_tri_5 + _tri_6)/2 , (_tri_1 + _tri_2 + _tri_3 + _tri_4)/4) )/ssd;
        _anti_point = ((_tri_5 + _tri_6)/2 - (_tri_1 + _tri_2 + _tri_3 + _tri_4)/4)*1.7*k + (_tri_5 + _tri_6)/2;

        left = dis_2; right = dis_1;
        if(left < right)
        {
            double temp;
            temp = left;
            left = right;
            right = temp;
        }

        d_dis = abs(617.719*0.05/left - 617.719*0.05/right);
        sin_tri;
        if(d_dis<=0.124)
        {
            sin_tri = d_dis/0.124;
        }
        else
        {
            sin_tri = 1;
        }
        // count distance

        SD.dist = 617.719*0.05*sin_tri/temp;
        std::cout << " k = " << k << " distance_static = " << get_distance(_anti_point,(_tri_5 + _tri_6)/2) << std::endl;
        break;
    default:
        break;
    }
    // std::cout << "angle = " << calculateRelativeAngle(cam_mx,_anti_point) << std::endl;
    SD.angle = calculateRelativeAngle(cam_mx,_anti_point);
    /**
     * @brief principle
     * @param _anti_point forward
     * @param angle x-----angle
     * @param distance movement
     * 
     * 
     */
//     if(left.x - right.x != 0)
//     {
//         float angle = 90 - atan(left.y - right.y)/(left.x - right.x);
// //   (-) -
// // angle  -
// //x---------
// //   angle-
// //    (+)-

//     }
//     else
//     {
//         float angle = 0;
//     }

    
}
float Predict::get_distance(cv::Point2f p1, cv::Point2f p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
using namespace std;
void Predict::displace(void)
{
    // cout << " greendot " << _greendot << endl;
    // cout << " bar " << _pre_bar << endl;
    // cout << " triangle " <<   _tri_1<<" "<<
    //                         _tri_2<<" "<<
    //                         _tri_3<<" "<<
    //                         _tri_4<<" "<<
    //                         _tri_5<<" "<<
    //                         _tri_6<< endl;
    // cout << " flag =  " << _flag << endl;
    cout << " SendData angle.distance =  " << SD.angle << " ; " << SD.dist << endl;
}
void Predict::predict_inition(void)
{
    /* 标志位flag 0 1 2 3 */
    _flag=0;
    /* loacal one triangle pnp */
    _tri_1 = cv::Point2f (-1,-1);
    _tri_2 = cv::Point2f (-1,-1);
    _tri_3 = cv::Point2f (-1,-1);
    _tri_4 = cv::Point2f (-1,-1);
    _tri_5 = cv::Point2f (-1,-1);
    _tri_6 = cv::Point2f (-1,-1);

    /* detect::model using data  using propotion( only one green )*/
    _greendot = cv::Point2f (-10,-10);;
    float _bar_dot_dis = -1;
    _pre_bar = cv::Point2f(-10.0,-10.0);
    _anti_point = cv::Point2f(-10.0,-10.0);
    /* local match using propotion */
    _green_triangle_ = cv::Point2f(-10,-10);
    /* bias greendot */
    _bias_dot = cv::Point2f (-10,-10);
    /* send data */
    SD.angle = cv::Point2f(-10,-10);
    SD.dist = -10;
}
cv::Point2f Predict::predict_some_fucking_thing(void)
{
    switch (_flag)
    {
    case 0:
        cout << "no fucking aim !" << endl;
        Port.writeStruct(SD);
        return cv::Point2f(-10,-10);
        break;
    case 1:
        bias_dot();
        cout << " bias_dot !" << endl;
        Port.writeStruct(SD);
        return _bias_dot;
        break;
    case 2:
        a_tri();
        cout << " a tri !" << endl;
        Port.writeStruct(SD);
        return _anti_point;
        break;
    case 3:
        match();
        cout << "  match !" << endl;
        Port.writeStruct(SD);
        return _green_triangle_;
        break;
    default:
        break;
    }
    return cv::Point2f(-1,-1);
}
cv::Point2f Predict::calculateRelativeAngle(const cv::Mat &cameraMatrix, cv::Point2f center)
{

    cv::Mat tf_point(3, 1, CV_32F);
    cv::Mat cameraMatrix_inverse;

    cameraMatrix.convertTo(cameraMatrix_inverse, CV_32F);

    cameraMatrix_inverse = cameraMatrix_inverse.inv();

    tf_point.at<float>(0.,0.) = center.x;

    tf_point.at<float>(1.,0.) = center.y;

    tf_point.at<float>(2.,0.) = 1;

    // 得到tan角矩阵

    cv::Mat tf_result = cameraMatrix_inverse * tf_point;

    // 从图像坐标系转换成世界坐标系角度
    // std::cout << cameraMatrix << "  " << tf_point << "  " << tf_result << std::endl;
    // yaw and pitch
    return {rad2deg(atan(tf_result.at<float>(0))),

            rad2deg(atan(tf_result.at<float>(1)))};

}
void Predict::Read_pre(const std::string &path)
{
    cv::FileStorage buffer(path, cv::FileStorage::READ);
    buffer["camera_matrix"] >> this->cam_mx;
    buffer["distortion_coefficients"] >> this->dis_mx;
}