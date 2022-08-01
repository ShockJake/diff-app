#include "../include/differentiator.h"
#include <iostream>

Differentiator::Differentiator(std::string &first_file_name, std::string &second_file_name, bool debug_mode)
{
    try
    {
        set_debug_mode(debug_mode);
        file_handler.open_files(first_file_name, second_file_name);
    }
    catch (const std::ifstream::failure &e)
    {
        log.report_error("Opening files failure", e.what());
    }
    catch (const std::exception &e)
    {
        log.report_error("Opening files failure", e.what());
    }
}

Differentiator::~Differentiator()
{
    file_handler.~FileHandler();
}

void Differentiator::print_difference(std::string line, std::string &file_name)
{
    std::cout << "[>>] " << line << " [<<] in file: " << file_name << '\n';
}

void Differentiator::set_files_data()
{
    this->first_file_data = file_handler.get_first_file_data();
    this->second_file_data = file_handler.get_second_file_data();
}

void Differentiator::compare(std::set<std::string> *first_file_data, std::set<std::string> *second_file_data, std::string file_name)
{
    try
    {
        std::set<std::string>::iterator i;
        auto begin = first_file_data->begin();
        auto end = first_file_data->end();

        for (i = begin; i != end; i++)
        {
            if (second_file_data->find(*i) == second_file_data->end())
            {
                print_difference(*i, file_name);
            }
        }
    }
    catch (const std::exception &e)
    {
        log.report_error("Reading files failure", e.what());
    }
}

void Differentiator::basic_comparing()
{
    set_files_data();

    std::cout << "||| BASIC COMPARING |||\n";
    compare(first_file_data, second_file_data, file_handler.get_first_file_name());
}

void Differentiator::side_by_side_comparing()
{
    std::cout << "\\\\\\ SIDE BY SIDE COMPARING //////\n";
    std::cout << file_handler.get_first_file_name() << " >> " << file_handler.get_second_file_name() << '\n';
    basic_comparing();
    std::cout << "\n\n";
    std::cout << file_handler.get_second_file_name() << " >> " << file_handler.get_first_file_name() << '\n';
    compare(second_file_data, first_file_data, file_handler.get_second_file_name());
}

void Differentiator::set_debug_mode(bool mode)
{
    this->debug_mode = mode;
    file_handler.set_debug_mode(mode);
}