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

    const bool SIMILARITIES = true;
    const bool DIFFERENCES = false;

    std::set<std::string> *first_file_data = nullptr;
    std::set<std::string> *second_file_data = nullptr;
    std::set<std::string> similarities;
    std::set<std::string> differences;

public:
    Differentiator(std::string &first_file_name, std::string &second_file_name, bool debug_mode = false);
    ~Differentiator();

    void set_debug_mode(bool mode);

    void basic_comparing();
    void side_by_side_comparing();
    void smart_comparing();

private:
    void set_files_data();
    void print_names_of_comparing_files(std::string first_file_name, std::string second_file_name);
    void compare(std::set<std::string> *first_file_data, std::set<std::string> *second_file_data);
    void print_result(bool result_type, std::string file_name);
    void write_data(std::string line, std::set<std::string> *file_data);
    void print_result(bool result_type);
    void cleanup();

    std::set<std::string> *get_similarities();
    std::set<std::string> *get_differences();
};

#endif // !DIFFERENTIATOR_H
