#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "logger.h"
#include "FileTypes.h"
#include <fstream>
#include <set>
class FileHandler
{
private:
    std::ifstream first_file;
    std::ifstream second_file;

    std::string first_file_name;
    std::string second_file_name;

    bool debug_mode = false;
    Logger log;
    FileTypes types;

    std::set<std::string> first_file_data;
    std::set<std::string> second_file_data;

    class FailbitException : public std::ios_base::failure::exception
    {
        const char *what() const throw()
        {
            return "Delimiting character was not found or no characters were extracted at all";
        }
    };

    class BadbitException : public std::ios_base::failure::exception
    {
        const char *what() const throw()
        {
            return "Error occured on stream";
        }
    };

public:
    FileHandler(std::string &first_file_name, std::string &second_file_name);
    FileHandler();
    ~FileHandler();

    void open_files(std::string &first_file_name, std::string &second_file_name);

    std::ifstream *get_first_file();
    std::ifstream *get_second_file();

    std::string get_first_file_name();
    std::string get_second_file_name();

    void set_debug_mode(bool mode);
    void set_files_to_start();

    std::set<std::string> *get_first_file_data();
    std::set<std::string> *get_second_file_data();

    class FileOpeningFailure : public std::exception
    {
        const char *what() const throw()
        {
            return "File opening failure";
        }
    };

private:
    std::string get_file_type(std::string &file_name);
    std::string get_parsed_line_number(int line_number);
    bool check_file_type();
    bool check_file_state(std::ifstream *file);
    bool verify_files();
    void read_files();
    void read_file(std::ifstream *file, std::set<std::string> *file_data);
    void close_files();
};

#endif // !FILEHANDLER_H
