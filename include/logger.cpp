#include "logger.h"
#include <time.h>
#include <iostream>

Logger::Logger(){};

Logger::~Logger(){};

std::string Logger::get_date()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char time[19];
    memset(time, 0, sizeof(time));
    sprintf(time, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return std::string(time);
}

void Logger::report_info(const char *msg)
{
    std::cout << get_date() << " - INFO - " << msg << '\n';
}

void Logger::report_info(const char *msg, std::string &file_name)
{
    std::cout << get_date() << " - INFO - " << msg << " : " << file_name << '\n';
}

void Logger::report_info(std::string &msg, std::string &file_name)
{
    std::cout << get_date() << " - INFO - " << msg << " : " << file_name << '\n';
}

void Logger::report_info(const char *msg, const char *e)
{
    std::cout << get_date() << " - INFO - " << msg << " : " << e << '\n';
}

void Logger::report_error(std::string &msg)
{
    std::cout << get_date() << " - ERROR - " << msg << '\n';
}

void Logger::report_error(std::string &msg, std::string &file_name)
{
    std::cout << get_date() << " - ERROR - " << msg << " : " << file_name << '\n';
}

void Logger::report_error(const char *msg, std::string &file_name)
{
    std::cout << get_date() << " - ERROR - " << msg << " : " << file_name << '\n';
}

void Logger::report_error(const char *msg, const char *e)
{
    std::cout << get_date() << " - ERROR - " << msg << " : " << e << '\n';
}