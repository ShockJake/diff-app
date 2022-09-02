#include "../include/logger.h"
#include <time.h>
#include <iostream>

Logger::Logger() {}

Logger::~Logger() {}

std::string Logger::get_date()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char time[19];
    memset(time, 0, sizeof(time));
    sprintf(time, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return std::string(time);
}

void Logger::print_info() 
{
    std::cout << " \033[0;32m- INFO -\033[0m ";
}

void Logger::print_warn()
{
    std::cout << " \033[1;33m- WARN -\033[0m ";
}

void Logger::report_info(const char *msg)
{
    std::cout << get_date();
    print_info();
    std::cout << msg << '\n';
}

void Logger::report_info(const char *msg, std::string &file_name)
{
    std::cout << get_date();
    print_info();
    std::cout << msg << " : " << file_name << '\n';
}

void Logger::report_info(std::string &msg, std::string &file_name)
{
    std::cout << get_date();
    print_info();
    std::cout << msg << " : " << file_name << '\n';
}

void Logger::report_info(const char *msg, const char *e)
{
    std::cout << get_date(); 
    print_info();
    std::cout << msg << " : " << e << '\n';
}

void Logger::report_warn(const char *msg)
{
    std::cout << get_date();
    print_warn();
    std::cout << msg << '\n';
}

void Logger::report_warn(const char *msg, std::string &file_name)
{
    std::cout << get_date();
    print_warn();
    std::cout << msg << " : " << file_name << '\n';
}

void Logger::report_warn(std::string &msg, std::string &file_name)
{
    std::cout << get_date();
    print_warn();
    std::cout << msg << " : " << file_name << '\n';
}

void Logger::report_warn(const char *msg, const char *e)
{
    std::cout << get_date(); 
    print_warn();
    std::cout << msg << " : " << e << '\n';
}

void Logger::report_error(std::string &msg)
{
    std::cerr << "\033[1;31m" << get_date() << " - ERROR - ";
    std::cerr << msg << "\033[0m\n";
}

void Logger::report_error(std::string &msg, std::string &file_name)
{
    std::cerr << "\033[1;31m" << get_date() << " - ERROR - ";
    std::cerr << msg <<  ':' << file_name << "\033[0m\n";
}

void Logger::report_error(const char *msg, std::string &file_name)
{
    std::cerr << "\033[1;31m" << get_date() << " - ERROR - ";
    std::cerr << msg <<  ':' << file_name << "\033[0m\n";
}

void Logger::report_error(const char *msg, const char *exception)
{
    std::cerr << "\033[1;31m" << get_date() << " - ERROR - ";
    std::cerr << msg << ':' << exception << "\033[0m\n";
}
