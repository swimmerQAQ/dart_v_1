/**
 * @file log_h
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 时间.h文件
 * @version 1.0
 * @date 2022-03-05
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#pragma once
#include <iostream>
#include <fstream>
#include <memory>
class alog
{
private:
    /* 创造时间 */
    double thrive;
    /* 时间周期 */
    unsigned int life_time=0;
    /* 写入文件 */
    std::ofstream ofs;
    const std::string file_name = "log.txt";
public:
    alog(/* args */) { ofs.open(file_name); };
    ~alog() { ofs.close(); };
    //输入一次
    void once_term(double);

    void set_file_name(void);
    void write_file(const std::string &str, double current_tick, double fre);
};
using log_sp = std::shared_ptr<alog>;