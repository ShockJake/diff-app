#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <string.h>

class Logger
{
private:
    std::string get_date();

public:
    Logger();
    ~Logger();

    void report_info(std::string &msg, std::string &file_name);
    void report_info(const char *msg, std::string &file_name);
    void report_info(const char *msg, const char *e);
    void report_info(const char *msg);

    void report_error(std::string &msg);
    void report_error(std::string &msg, std::string &file_name);
    void report_error(const char *msg, const char *e);
    void report_error(const char *msg, std::string &file_name);
};

#endif // !LOGGER_H
