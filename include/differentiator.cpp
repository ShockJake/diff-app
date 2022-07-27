#include "differentiator.h"
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

void Differentiator::print_difference(std::string &line, std::string &file_name)
{
    std::cout << "[>>] " << line << " [<<] in file: " << file_name << '\n';
}

void Differentiator::compare(std::ifstream *first_file, std::ifstream *second_file, std::string file_name)
{
    try
    {
        file_handler.set_files_to_start();
        while (!first_file->eof())
        {
            std::string line1, line2;
            std::getline(*first_file, line1);
            bool is_found = false;
            while (!second_file->eof())
            {
                std::getline(*second_file, line2);
                if (line1 == line2)
                {
                    is_found = true;
                    break;
                }
            }
            if (!is_found)
            {
                print_difference(line1, file_name);
            }
        }
        file_handler.set_files_to_start();
    }
    catch (const std::ifstream::failure &e)
    {
        log.report_error("Reading files failure", e.what());
    }
    catch (const std::exception &e)
    {
        log.report_error("Reading files failure", e.what());
    }
}

void Differentiator::basic_comparing()
{
    std::ifstream *first_file = file_handler.get_first_file();
    std::ifstream *second_file = file_handler.get_second_file();

    std::cout << "||| BASIC COMPARING |||\n";
    if (file_handler.get_first_file_size() > file_handler.get_second_file_size())
    {
        compare(second_file, first_file, file_handler.get_second_file_name());
    }
    else
    {
        compare(first_file, second_file, file_handler.get_first_file_name());
    }
}

void Differentiator::side_by_side_comparing()
{
    std::cout << "\\\\\\ SIDE BY SIDE COMPARING //////\n";
    std::cout << file_handler.get_first_file_name() << " >> " << file_handler.get_second_file_name() << '\n';
    basic_comparing();
    std::cout << "\n\n";
    std::cout << file_handler.get_second_file_name() << " >> " << file_handler.get_first_file_name() << '\n';
    compare(file_handler.get_second_file(), file_handler.get_first_file(), file_handler.get_second_file_name());
}

void Differentiator::set_debug_mode(bool mode)
{
    this->debug_mode = mode;
    file_handler.set_debug_mode(mode);
}