#include "../include/logger.h"
#include <ctime>
#include <cstring>

Logger::Logger() = default;

Logger::~Logger() = default;

char *Logger::get_date()
{
    time_t t = time(nullptr);
    struct tm time = *localtime(&t);
    char pattern[] = "%d-%02d-%02d %02d:%02d:%02d";
    memset(actual_time, 0, sizeof(actual_time));
    sprintf(actual_time, pattern, time.tm_mday, time.tm_mon + 1, time.tm_year + 1900, time.tm_hour, time.tm_min, time.tm_sec);
    return actual_time;
}

void Logger::print_info() const
{
    printf("%s - INFO - %s", colors.GREEN, colors.DEFAULT);
}

void Logger::print_warn() const
{
    printf("%s - WARN - %s", colors.YELLOW, colors.DEFAULT);
}

void Logger::info(const char *msg)
{
    printf("%s", get_date());
    print_info();
    printf("%s\n", msg);
}

void Logger::info(const char *msg, std::string &file_name)
{
    printf("%s", get_date());
    print_info();
    printf("%s : %s\n", msg, file_name.c_str());
}

void Logger::info(std::string &msg, std::string &file_name)
{
    printf("%s", get_date());
    print_info();
    printf("%s : %s\n", msg.c_str(), file_name.c_str());
}

void Logger::info(const char *msg, const char *e)
{
    printf("%s", get_date());
    print_info();
    printf("%s : %s\n", msg, e);
}

void Logger::warn(const char *msg)
{
    printf("%s", get_date());
    print_warn();
    printf("%s\n", msg);
}

void Logger::warn(const char *msg, std::string &file_name)
{
    printf("%s", get_date());
    print_warn();
    printf("%s : %s\n", msg, file_name.c_str());
}

void Logger::warn(std::string &msg, std::string &file_name)
{
    printf("%s", get_date());
    print_warn();
    printf("%s : %s\n", msg.c_str(), file_name.c_str());
}

void Logger::warn(const char *msg, const char *e)
{
    printf("%s", get_date());
    print_warn();
    printf("%s : %s\n", msg, e);
}

void Logger::error(std::string &msg)
{
    printf("%s%s - ERROR - %s%s\n", colors.RED, get_date(), msg.c_str(), colors.DEFAULT);
}

void Logger::error(std::string &msg, std::string &file_name)
{
    printf("%s%s - ERROR - %s: %s%s\n", colors.RED, get_date(), msg.c_str(), file_name.c_str(), colors.DEFAULT);
}

void Logger::error(const char *msg, std::string &file_name)
{
    printf("%s%s - ERROR - %s: %s%s\n", colors.RED, get_date(), msg, file_name.c_str(), colors.DEFAULT);
}

void Logger::error(const char *msg, const char *exception)
{
    printf("%s%s - ERROR - %s: %s%s\n", colors.RED, get_date(), msg, exception, colors.DEFAULT);
}
