/**
 * @file detect_h
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 识别.h文件
 * @version 1.0
 * @date 2022-01-27
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#pragma once
#include "../invertimg/invertimg.h"
#include "../lightbar/lightbar.h"
#include "../greendot/greendot.h"
#include "../triangle/triangle.h"
#include "../log/log.h"
#include "../predict/predict.h"
#define GREEN_IMG 1
#define BLUE_BAR 0
#define RED_BAR 2
class Detect
{
    private:
    int readmod;
    int showmod;
    //extra-pointer
    /**
     * @brief 外部指针都是作为插件使用
     * @param _box 例如_box后缀变量均为单独功能：意为工具箱
     * @param detect detect类别在main中申请——detect_box 同上，对于内部_box类别
     * @param origin  origin,原图 ，bar和green储存红蓝绿黑白图
     * @param triangle 三角形识别
     * @param log 识别记录
     * @param predict 根据具体识别特征的机械结构模型，计算预测的位置
     */
    invert_sp invert_box;
    std::vector<lightbar_p> lightbar_box;
    std::vector<greendot_p> greendot_box;
    //basic 
    cv::Mat Bar_img;
    cv::Mat Green_img;
    cv::Mat origin;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<std::vector<cv::Point>> contours;

    //triangle
    std::vector<triangle_p> triangle_box;

    //a log
    log_sp log_box;

    //predict
    predict_sp predict_box;
public:
    Detect(){ log_box = std::make_shared<alog>(); predict_box = std::make_shared<Predict>();};

    //video and camera
    void init_detect(int);
    void init_detect(std::string);
    bool clc(int num , char* input[]);

    /**
     * @brief Get the invert object
     * @details 得到转换图 ---- 匹配固定件 ---- 模型对比
     * 优先匹配横条bar
     */
    void read_frame(void);
    void read_camera(int color);//camera
    void get_invert(int color);//得到处理过的video
    
    /*
    公用识别:matach:灯条及绿灯
            model:匹配垂直灯条
            security:使用了非智能指针，手动清理
            prediction:解算
    */
    void match(void);
    void model(void);
    void prediction(void);
    /*-----------------------find---triangle三角形---------------*/
    void match_triagle(void);

    //显示数据不同图像
    void show_mod(int num, char* mod[]);
    void show_bar(void);
    void show_green_dot(void);
    void show_origin(void);
    /*不能用fps*/
    void show_fps(void){
        std::cout << " fps is " << invert_box->get_fps() << std::endl;
        };
    /*获得两点距离*/
    float get_distance(cv::Point2f p1,cv::Point2f p2);
    //基本保护
    void limit_lightbar(){std::vector<lightbar_p>().swap(lightbar_box);}
    void limit_greendot(){std::vector<greendot_p>().swap(greendot_box);}
    void limit_triangle(){std::vector<triangle_p>().swap(triangle_box);}

    ~Detect(){};
};