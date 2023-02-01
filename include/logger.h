#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include "colorProperties.h"

class Logger
{
private:
    char *get_date();

    ColorProperties colors;
    void print_info() const;
    void print_warn() const;
    char actual_time[19]{};

public:
    Logger();
    ~Logger();

    void info(std::string &msg, std::string &file_name);
    void info(const char *msg, std::string &file_name);
    void info(const char *msg, const char *exception);
    void info(const char *msg);

    void warn(std::string &msg, std::string &file_name);
    void warn(const char *msg, std::string &file_name);
    void warn(const char *msg, const char *exception);
    void warn(const char *msg);

    void error(std::string &msg);
    void error(std::string &msg, std::string &file_name);
    void error(const char *msg, const char *exception);
    void error(const char *msg, std::string &file_name);
};

#endif // !LOGGER_H
