/**
 * @file main_cpp
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief main主函数文件
 * @version 1.0
 * @date 2022-04-30
 * 
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "../lib/detect/detect.h"
using namespace std;
using namespace cv;
int main (int numofinput , char* content[])
{
    Detect detect_box;
    bool run = detect_box.clc(numofinput,content);
    if(!run)
    {
        cout << "NO controling commend......" << endl;
        return 0;
    }
    double time;
    while (1)
    {
        time = (double)cv::getTickCount();
        detect_box.read_frame();
        detect_box.show_mod(numofinput , content);
        detect_box.match();
        detect_box.model();
        detect_box.match_triagle();
        detect_box.prediction();
        detect_box.show_mod(numofinput , content);
        time = ((double)cv::getTickCount() - time)/cv::getTickFrequency();
        cout << "fps = " << (int)(1.0/time) << endl;
         if(waitKey(1)==32)
         {
             if(waitKey()==27)
             {
                 break;
             }
         }
    }
    return 0;
}