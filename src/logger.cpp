#include "../include/logger.h"
#include <time.h>
#include <iostream>
#include <string.h>

Logger::Logger() {}

Logger::~Logger() {}

char *Logger::get_date()
{
    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    char pattern[] = "%d-%02d-%02d %02d:%02d:%02d";
    memset(actual_time, 0, sizeof(actual_time));
    sprintf(actual_time, pattern, time.tm_mday, time.tm_mon + 1, time.tm_year + 1900, time.tm_hour, time.tm_min, time.tm_sec);
    return actual_time;
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
    printf("%s", get_date());
    print_info();
    printf("%s\n", msg);
}

void Logger::report_info(const char *msg, std::string &file_name)
{
    printf("%s", get_date());
    print_info();
    printf("%s : %s\n", msg, file_name.c_str());
}

void Logger::report_info(std::string &msg, std::string &file_name)
{
    printf("%s", get_date());
    print_info();
    printf("%s : %s\n", msg.c_str(), file_name.c_str());
}

void Logger::report_info(const char *msg, const char *e)
{
    printf("%s", get_date());
    print_info();
    printf("%s : %s\n", msg, e);
}

void Logger::report_warn(const char *msg)
{
    printf("%s", get_date());
    print_warn();
    printf("%s\n", msg);
}

void Logger::report_warn(const char *msg, std::string &file_name)
{
    printf("%s", get_date());
    print_warn();
    printf("%s : %s\n", msg, file_name.c_str());
}

void Logger::report_warn(std::string &msg, std::string &file_name)
{
    printf("%s", get_date());
    print_warn();
    printf("%s : %s\n", msg.c_str(), file_name.c_str());
}

void Logger::report_warn(const char *msg, const char *e)
{
    printf("%s", get_date());
    print_warn();
    printf("%s : %s\n", msg, e);
}

void Logger::report_error(std::string &msg)
{
    printf("%s%s - ERROR - %s%s\n", colors.RED, get_date(), msg.c_str(), colors.DEFAULT);
}

void Logger::report_error(std::string &msg, std::string &file_name)
{
    printf("%s%s - ERROR - %s: %s%s\n", colors.RED, get_date(), msg.c_str(), file_name.c_str(), colors.DEFAULT);
}

void Logger::report_error(const char *msg, std::string &file_name)
{
    printf("%s%s - ERROR - %s: %s%s\n", colors.RED, get_date(), msg, file_name.c_str(), colors.DEFAULT);
}

void Logger::report_error(const char *msg, const char *exception)
{
    printf("%s%s - ERROR - %s: %s%s\n", colors.RED, get_date(), msg, exception, colors.DEFAULT);
}
