#include "../include/logger.h"
#include <time.h>
#include <iostream>
#include <string.h>

Logger::Logger() {}

Logger::~Logger() {}

std::string Logger::get_date()
{
    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    char result[19];
    memset(result, 0, sizeof(result));
    char pattern[] = "%d-%02d-%02d %02d:%02d:%02d";
    sprintf(result, pattern, time.tm_mday, time.tm_mon + 1, time.tm_year + 1900, time.tm_hour, time.tm_min, time.tm_sec);
    return std::string(result);
}

void Logger::print_info()
{
    printf("%s - INFO - %s", colors.GREEN, colors.DEFAULT);
}

void Logger::print_warn()
{
    printf("%s - WARN - %s", colors.YELLOW, colors.DEFAULT);
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
    std::cerr << colors.RED << get_date() << " - ERROR - ";
    std::cerr << msg << colors.DEFAULT << '\n';
}

void Logger::report_error(std::string &msg, std::string &file_name)
{
    std::cerr << colors.RED << get_date() << " - ERROR - ";
    std::cerr << msg << ": " << file_name << colors.DEFAULT << '\n';
}

void Logger::report_error(const char *msg, std::string &file_name)
{
    std::cerr << colors.RED << get_date() << " - ERROR - ";
    std::cerr << msg << ": " << file_name << colors.DEFAULT << '\n';
}

void Logger::report_error(const char *msg, const char *exception)
{
    std::cerr << colors.RED << get_date() << " - ERROR - ";
    std::cerr << msg << ": " << exception << colors.DEFAULT << '\n';
}
