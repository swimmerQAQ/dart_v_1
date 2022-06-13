/**
 * @file detect_h
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 识别cpp文件
 * @version 1.0
 * @date 2022-01-27
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#include "detect.h"
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;

void Detect::init_detect(int type)
{//申请videocapture 设置 capture
    invert_box = std::make_shared<invert_img>();
    invert_box->init_camera(type);
    invert_box->set_cap(BLUE_BAR);
}
void Detect::init_detect(String path)
{
    invert_box = std::make_shared<invert_img>();
    invert_box->init_video(path);
}
void Detect::read_camera(int color)
{
    invert_box->read_camera(color);
    Bar_img = invert_box->get_bar();
    Green_img = invert_box->get_green();
    origin = invert_box->get_origin();
}
void Detect::get_invert(int color)
{
    //都要读入图片
    log_box->once_term((double)getTickCount());
    if (color == 0)
    {
        //运算大头！！operate，强烈掉帧
        invert_box->operate_img(BLUE_BAR);
        Bar_img = invert_box->get_bar();
        Green_img = invert_box->get_green();
        origin = invert_box->get_origin();
    }
    else if (color == 2)
    {
        /* code */
        invert_box->operate_img(RED_BAR);
        Bar_img = invert_box->get_bar();
        Green_img = invert_box->get_green();
        origin = invert_box->get_origin();
    }
}
void Detect::match(void)
{
    predict_box->predict_inition();
    limit_lightbar();
    cv::findContours(Bar_img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    vector<float> area;area.resize(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        lightbar_p temp_p = std::make_shared<Lightbar>();
        if (temp_p->is_match(contours[i]))
        {
            lightbar_box.push_back(temp_p);
            temp_p->fpp_show(origin);
        }
    }
    //此处生成所有的的灯条已获得，准备拿绿点，using (greendot _ ptr)
    // cout << "lightbar_box.size() = " << lightbar_box.size()  << endl;
    // swap vector
    limit_greendot();
    // cv::cvtColor(*Green_img, *Green_img, cv::COLOR_BGR2GRAY);
    cv::findContours(Green_img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (int j = 0; j < contours.size(); j++)
    {
        greendot_p temp_green = std::make_shared<greendot>();
        if (temp_green->is_match(contours[j]))//////if green light occur some problems all detect break down
        {
            greendot_box.push_back(temp_green);
            temp_green->greendot_show(origin);
            predict_box->read_point(temp_green->get_centre_point());
            log_box->write_file("---green_dot---",(double)getTickCount(),(double)getTickFrequency());
            predict_box->set_flag(1);

        }
    }
    
}
void Detect::model(void)
{
    float long_line,short_line , temp_long ,temp_short, proportion, similar, limit_lightbar;
    for(int i =0 ; i <lightbar_box.size() ; i++)
    {
        if(greendot_box.size() > 1)///////////////comfirm only one greendot
        {
            cout << " Why you get more than one greendot ? " << endl;
            break;
        }
        for(auto greendot : greendot_box)
        {
            limit_lightbar = get_distance(greendot->get_centre_point(),lightbar_box[i]->get_centre());
            if (limit_lightbar < greendot->get_wideth()*5 )
            {
                continue;
            }
            long_line = get_distance(greendot->get_centre_point(),lightbar_box[i]->get_fpp(0));//旋转情况下不确定长短 对应 0和2点就行
            short_line = get_distance(greendot->get_centre_point(), lightbar_box[i]->get_fpp(2));

            temp_long = sqrt(pow(long_line, 2) - pow(lightbar_box[i]->get_longer(),2)/4 );//都是减长边
            temp_short = sqrt(pow(short_line, 2) - pow(lightbar_box[i]->get_longer(), 2)/4 );

            // cout << "big_line short_line" << temp_long << " " << temp_short << "  " << lightbar_box[i]->get_shorter() << endl;

            proportion = lightbar_box[i]->get_shorter() / fabs((temp_long - temp_short));
            // cout << " proportion = " << proportion << endl;
            if (proportion > 0.8 && proportion < 1.2)
            {
                line(origin, lightbar_box[i]->get_centre(), greendot->get_centre_point(), Scalar(0, 0, 255), 1, 8);
                predict_box->read_bar(lightbar_box[i]->get_centre());
                log_box->write_file("---model_bar---",(double)getTickCount(),(double)getTickFrequency());
            }
            similar = lightbar_box[i]->get_longer() / fabs((temp_long - temp_short));
            if (similar > 1.2 && similar < 1.5)
            {
                circle(origin,lightbar_box[i]->get_centre(),10,Scalar(255,255,255),-1);
            }
        }
        
    }
}
void Detect::match_triagle(void)
{
    if(lightbar_box.size()<3)
    {
        return;
    }
    limit_triangle();
    for (int i = 0; i < lightbar_box.size() - 2; i++)
    {
        for (int j = i + 1; j < lightbar_box.size() - 1; j++)
        {
            for (int k = i + 2; k < lightbar_box.size(); k++)
            {
                triangle_p temp = make_shared<Triangle>();
                if (!temp->match_angle(lightbar_box[i]->get_angle(), lightbar_box[j]->get_angle(), lightbar_box[k]->get_angle()))
                {
                    cout << "推测角违规!" << endl;
                    cout << "three angle = " << lightbar_box[i]->get_angle() << " " << lightbar_box[j]->get_angle() << " " << lightbar_box[k]->get_angle() << endl;
                    continue;
                }
                // cout << "推测角通过!" << endl;
                // cout << "three angle = " << lightbar_box[i]->get_angle() << " " << lightbar_box[j]->get_angle() << " " << lightbar_box[k]->get_angle() << endl;
                if (!temp->match_three(
                        lightbar_box[i]->get_h_point(), lightbar_box[i]->get_w_point(),
                        lightbar_box[j]->get_h_point(), lightbar_box[j]->get_w_point(),
                        lightbar_box[k]->get_h_point(), lightbar_box[k]->get_w_point()))
                {
                    cout << " 聚点违规! " << endl;
                    cout << " Invalid-number " << temp->get_score() << endl;
                    // line(*origin, temp->get_one(), temp->get_two(), Scalar(0, 0, 255), 3, 8);
                    // line(*origin, temp->get_one(), lightbar_box[i]->get_centre(), Scalar(0, 0, 255), 3, 8);
                    // line(*origin, temp->get_two(), temp->get_three(), Scalar(0, 255, 0), 3, 8);
                    // line(*origin, temp->get_two(), lightbar_box[j]->get_centre(), Scalar(0, 0, 255), 3, 8);
                    // line(*origin, temp->get_three(), temp->get_one(), Scalar(255, 0, 0), 3, 8);
                    // line(*origin, temp->get_three(), lightbar_box[k]->get_centre(), Scalar(0, 0, 255), 3, 8);
                    continue;
                }
                // cout << " 聚点通过! " << endl;
                // cout << " Valid-number " << temp->get_score() << endl;
                if (!temp->match_margin(lightbar_box[i]->get_h_point(), lightbar_box[i]->get_w_point(), lightbar_box[i]->get_longer(),
                                        lightbar_box[j]->get_h_point(), lightbar_box[j]->get_w_point(), lightbar_box[j]->get_longer(),
                                        lightbar_box[k]->get_h_point(), lightbar_box[k]->get_w_point(), lightbar_box[k]->get_longer()))
                {
                    cout << " 三边比例违规! " << endl;
                    cout << " Invalid-number " << temp->get_score() << endl;
                    continue;
                }
                // cout << " 三边比例通过! " << endl;
                // cout << " Valid-number " << temp->get_score() << endl;
                // cout << "three angle = " << lightbar_box[i]->get_angle() << " " << lightbar_box[j]->get_angle() << " " << lightbar_box[k]->get_angle() << endl;
                // circle(*origin, lightbar_box[i]->get_centre(), 6, Scalar(0, 0, 255), -1);
                // circle(*origin, lightbar_box[j]->get_centre(), 6, Scalar(0, 255, 0), -1);
                // circle(*origin, lightbar_box[k]->get_centre(), 6, Scalar(255, 0, 0), -1);

                triangle_box.push_back(temp);
            }
        }
    }
    if(triangle_box.size() == 0)
    {
        return;
    }
            auto temp = triangle_box[0];
            for(auto tri : triangle_box)
            {
                if (tri->get_score() < temp->get_score())
                {
                    temp = tri;
                }
            }
            {
                log_box->write_file("---triangle---",(double)getTickCount(),(double)getTickFrequency());
                predict_box->read_point(temp->get_bar_1(),temp->get_bar_2(),temp->get_bar_3(),temp->get_bar_4(),temp->get_bar_5(),temp->get_bar_6());
                if (predict_box->ret_flag() == 1)
                {
                    predict_box->set_flag(3);
                }else
                {
                    predict_box->set_flag(2);
                }
                if(showmod == 1 || showmod == -1)
                {
                    return;
                }
                line(origin, temp->get_one(), temp->get_two(), Scalar(0, 0, 255), 3, 8);
                line(origin, temp->get_three(), temp->get_four(), Scalar(0, 255, 0), 3, 8);
                line(origin, temp->get_five(), temp->get_six(), Scalar(255, 0, 0), 3, 8);

                line(origin, (temp->get_bar_1()+temp->get_bar_2())/2, 
                                (temp->get_bar_3()+temp->get_bar_4())/2, Scalar(255, 255, 255), 3, 8);

                line(origin, (temp->get_bar_3()+temp->get_bar_4())/2, 
                                (temp->get_bar_5()+temp->get_bar_6())/2, Scalar(255, 255, 255), 3, 8);

                line(origin, (temp->get_bar_1()+temp->get_bar_2())/2, 
                                (temp->get_bar_5()+temp->get_bar_6())/2, Scalar(255, 255, 255), 3, 8);
            }
}
void Detect::show_bar(void)
{
    imshow("bar",Bar_img);
}
void Detect::show_green_dot(void)
{
    imshow("green_dot", Green_img);
}
void Detect::show_origin(void)
{
    imshow(" origin !", origin);
}
float Detect::get_distance(cv::Point2f p1, cv::Point2f p2)
{
    return sqrt ( pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2) );
}
void Detect::prediction(void)
{
    cv::Point2f temp = predict_box->predict_some_fucking_thing();
    predict_box->displace();
    if(showmod < 1)
    {
        return;
    }
    circle(origin,temp,10,Scalar(255,0,255));
    line(origin, temp,temp - cv::Point2f(0,12) , Scalar(0,255,255),2);
    line(origin, temp - cv::Point2f(-6,6),temp - cv::Point2f(6,6) , Scalar(0,255,255),2);
    line(origin, temp,temp - cv::Point2f(-6,0) , Scalar(0,255,255),2);
    line(origin, temp - cv::Point2f(-6,0),temp - cv::Point2f(-6,3) , Scalar(0,255,255),2);

    line(origin, temp- cv::Point2f(12,18),temp - cv::Point2f(-12,18) , Scalar(0,255,255),2);
    line(origin, temp- cv::Point2f(-9,15),temp - cv::Point2f(-12,18) , Scalar(0,255,255),2);
    line(origin, temp- cv::Point2f(12,18),temp - cv::Point2f(12,-18) , Scalar(0,255,255),2);
    line(origin, temp- cv::Point2f(18,-24),temp - cv::Point2f(12,-18) , Scalar(0,255,255),2);
    line(origin, temp- cv::Point2f(18,-24),temp - cv::Point2f(21,-27) , Scalar(0,255,255),2);

    line(origin, temp- cv::Point2f(0,18),temp - cv::Point2f(0,26) , Scalar(0,255,255),2);
    line(origin, temp- cv::Point2f(0,22),temp - cv::Point2f(-6,22) , Scalar(0,255,255),2);

    line(origin, temp- cv::Point2f(6,-6),temp - cv::Point2f(-6,-6) , Scalar(0,255,255),2);
    line(origin, temp- cv::Point2f(6,-24),temp - cv::Point2f(6,-6) , Scalar(0,255,255),2);
    line(origin, temp- cv::Point2f(6,-24),temp - cv::Point2f(9,-27) , Scalar(0,255,255),2);
    line(origin, temp- cv::Point2f(-6,-6),temp - cv::Point2f(-6,-27) , Scalar(0,255,255),2);
    line(origin, temp- cv::Point2f(-12,-27),temp - cv::Point2f(-6,-27) , Scalar(0,255,255),2);
    line(origin, temp- cv::Point2f(-12,-27),temp - cv::Point2f(-12,-20) , Scalar(0,255,255),2);
}

bool Detect::clc(int num, char* input[])
{
    if(num>1)
    {
        if(strcmp(input[1],"-c")==0)
        {
            init_detect(0);
            readmod = 0;
            return true;
        }
        if(strcmp(input[1],"-v")==0)
        {
            init_detect("/home/ksc/Documents/Project_Base/raspberry2/src/video/cuowei1.avi");
            readmod = 1;
        }
        return true;
    }
    readmod = -1;
    return false;
}
void Detect::read_frame(void)
{
    if(readmod == 1)
    {
        get_invert(BLUE_BAR);
    }
    else if(readmod == 0){
        read_camera(BLUE_BAR);
    }
}
void Detect::show_mod(int num, char* mod[])
{
    if(num>2)
    {
        if(strcmp(mod[2],"-o")==0)
        {
            show_origin();
        }
        if(strcmp(mod[2],"-b")==0)
        {
            show_bar();
        }
        if(strcmp(mod[2],"-g")==0)
        {
            show_green_dot();
        }
    }
    if (num>3)
    {
        if(strcmp(mod[3],"-tri")==0)
        {
            showmod = 0;
            return;
        }
        if(strcmp(mod[3],"-all")==0)
        {
            showmod = 2;
            return;
        }
        if(strcmp(mod[3],"-aim")==0)
        {
            showmod = 1;
            return;
        }
    }
    showmod = -1;
}