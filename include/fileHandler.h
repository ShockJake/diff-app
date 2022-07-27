#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "logger.h"
#include <fstream>

class FileHandler
{
private:
    std::ifstream first_file;
    std::ifstream second_file;

    std::string first_file_name;
    std::string second_file_name;

    unsigned long int first_file_size = 0;
    unsigned long int second_file_size = 1;

    bool debug_mode = false;
    Logger log;

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

    unsigned long int get_first_file_size();
    unsigned long int get_second_file_size();

private:
    void close_files();
    bool verify_files();
    void read_files_size();
};

#endif // !FILEHANDLER_H
