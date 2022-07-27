#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "fileHandler.h"

class Differentiator
{
private:
    FileHandler file_handler;
    bool debug_mode = false;
    Logger log;

public:
    Differentiator(std::string &first_file_name, std::string &second_file_name, bool debug_mode = false);
    ~Differentiator();

    void basic_comparing();
    void side_by_side_comparing();
    void set_debug_mode(bool mode);

private:
    void compare(std::ifstream *first_file, std::ifstream *second_file, std::string file_name);
    void print_difference(std::string &line, std::string &file_name);
};

#endif // !DIFFERENTIATOR_H
