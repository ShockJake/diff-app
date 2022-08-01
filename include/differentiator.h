#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "fileHandler.h"
#include <set>
class Differentiator
{
private:
    FileHandler file_handler;
    bool debug_mode = false;
    Logger log;

    std::set<std::string> *first_file_data = nullptr;
    std::set<std::string> *second_file_data = nullptr;

public:
    Differentiator(std::string &first_file_name, std::string &second_file_name, bool debug_mode = false);
    ~Differentiator();

    void basic_comparing();
    void side_by_side_comparing();
    void set_debug_mode(bool mode);
    void set_files_data();

private:
    void compare(std::set<std::string> *first_file_data, std::set<std::string> *second_file_data, std::string file_name);
    void print_difference(std::string line, std::string &file_name);
};

#endif // !DIFFERENTIATOR_H
