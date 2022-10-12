#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "fileHandler.h"
#include <exception>
#include "colorProperties.h"

class Differentiator
{
private:
    FileHandler file_handler;
    bool debug_mode = false;
    bool print_lines = false;
    Logger log;
    ColorProperties colors;

    const bool SIMILARITIES = true;
    const bool DIFFERENCES = false;
    std::string line_separator = "----------------------------------------------";

    std::list<std::string> *first_file_data = nullptr;
    std::list<std::string> *second_file_data = nullptr;

    std::list<std::string> similarities;
    std::list<std::string> differences;

    class FileProceedingFailure : public std::exception
    {
        const char *what() const throw()
        {
            return "Failed to proceed file";
        }
    };

public:
    Differentiator(std::string &first_file_name, std::string &second_file_name, bool debug_mode = false, bool print_lines = false);
    ~Differentiator();

    void set_debug_mode(bool mode);
    void set_print_lines(bool print_lines);

    void basic_comparing();
    void side_by_side_comparing();
    void smart_comparing();

private:
    std::string get_parsed_line_number(int line_number);
    std::string get_line_prefix(std::string &parsed_line_number, std::string &file_name);
    void set_files_data();
    void print_names_of_comparing_files(std::string first_file_name, std::string second_file_name);
    void compare(std::list<std::string> *first_file_data, std::list<std::string> *second_file_data, std::string file_name);
    void print_result(bool result_type, std::string file_name);
    void write_data(std::string line, std::list<std::string> *file_data, std::string &file_name, int line_number);
    void print_result(bool result_type);
    void print_difference_percentage();
    void cleanup();
    bool check_blank_line(std::list<std::string> *file_data);
    void print_number_of_lines(int differences, int similarities, int all);
    bool check_identical_or_totally_different();
};

#endif // !DIFFERENTIATOR_H
