#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "fileHandler.h"
#include <exception>
#include <set>
#include "colorProperties.h"

class Differentiator
{
private:
    FileHandler file_handler;
    bool debug_mode = false;
    Logger log;
    ColorProperties colors; 

    const bool SIMILARITIES = true;
    const bool DIFFERENCES = false;

    std::set<std::string> *first_file_data = nullptr;
    std::set<std::string> *second_file_data = nullptr;
    std::set<std::string> similarities;
    std::set<std::string> differences;

    class FileOpeningFailure : public std::exception 
    {
        const char *what() const throw()
        {
            return "File opening failure";
        }
    };

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
    void print_difference_percentage(); 
    void cleanup();
};

#endif // !DIFFERENTIATOR_H
