#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "logger.h"
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

    std::set<std::string> first_file_data;
    std::set<std::string> second_file_data;

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

private:
    bool verify_files();
    void read_files();
    void close_files();
};

#endif // !FILEHANDLER_H
