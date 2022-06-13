/**
 * @file log_cpp
 * @author 旷绍宸 (1498507570@qq.com)
 * @brief 时间.cpp文件
 * @version 1.0
 * @date 2022-03-05
 *
 * @copyright Copyright SCUT RobotLab 2022
 *
 */
#include "log.h"
using namespace std;
void alog::once_term(double current_time)
{
    if(life_time == 0)
    {
        thrive = current_time;
        life_time++;
        return;
    }
    life_time++;
    return;
}
void alog::write_file(const std::string &str, double current_tick, double fre)
{
    set_file_name();
    double time = (current_tick - thrive)/fre;
    ofs << " time: " << time << ", notion:" << str << endl;
}
void alog::set_file_name(void)
{
    // ofstream
    if (this->ofs.is_open())
    {
        this->ofs.close();
    }
    this->ofs.open(file_name, ios::app);
}
