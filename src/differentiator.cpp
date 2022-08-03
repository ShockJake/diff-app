#include "../include/differentiator.h"
#include <iostream>

Differentiator::Differentiator(std::string &first_file_name, std::string &second_file_name, bool debug_mode)
{
    try
    {
        set_debug_mode(debug_mode);
        file_handler.open_files(first_file_name, second_file_name);
        set_files_data();
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

Differentiator::~Differentiator() {}

void Differentiator::print_result(bool result_type, std::string file_name)
{
    std::set<std::string>::iterator i;
    std::set<std::string>::iterator begin;
    std::set<std::string>::iterator end;

    if (result_type)
    {
        begin = similarities.begin();
        end = similarities.end();
    }
    else
    {
        
        begin = differences.begin();
        end = differences.end();
    }

    for (i = begin; i != end; i++)
    {
        std::cout << *i << "\t - in file: " << file_name << std::endl;
    }
}

void Differentiator::print_result(bool result_type)
{
    std::set<std::string>::iterator i;
    std::set<std::string>::iterator begin;
    std::set<std::string>::iterator end;

    if (result_type)
    {
        begin = similarities.begin();
        end = similarities.end();
    }
    else
    {
        
        begin = differences.begin();
        end = differences.end();
    }

    for (i = begin; i != end; i++)
    {
        std::cout << *i <<  std::endl;
    }
}

void Differentiator::cleanup()
{
    similarities.clear();
    differences.clear();
}

void Differentiator::set_files_data()
{
    this->first_file_data = file_handler.get_first_file_data();
    this->second_file_data = file_handler.get_second_file_data();
}

void Differentiator::print_names_of_comparing_files(std::string first_file_name, std::string second_file_name)
{
    std::cout << "Comparing files: " << first_file_name << " ->>- " << second_file_name << std::endl;
}

void Differentiator::compare(std::set<std::string> *first_file_data, std::set<std::string> *second_file_data)
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
                differences.insert(*i);
            }
            else
            {
                similarities.insert(*i);
            }
        }
    }
    catch (const std::exception &e)
    {
        log.report_error("Comparing files failure", e.what());
    }
}

void Differentiator::basic_comparing()
{
    std::cout << "<=> BASIC COMPARING <=>\n";
    print_names_of_comparing_files(file_handler.get_first_file_name(), file_handler.get_second_file_name());
    compare(first_file_data, second_file_data);
    print_result(DIFFERENCES, file_handler.get_first_file_name());
}

void Differentiator::side_by_side_comparing()
{
    std::cout << "\\\\\\\\\\\\ SIDE BY SIDE COMPARING //////\n";
    print_names_of_comparing_files(file_handler.get_first_file_name(), file_handler.get_second_file_name());
    compare(first_file_data, second_file_data);
    print_result(DIFFERENCES, file_handler.get_first_file_name());
    cleanup();
    std::string line_separator = "----------------------------------------------";
    std::cout << '\n'
              << line_separator << "\n\n";
    print_names_of_comparing_files(file_handler.get_second_file_name(), file_handler.get_first_file_name());
    compare(second_file_data, first_file_data);
    print_result(DIFFERENCES, file_handler.get_second_file_name());
}

void Differentiator::smart_comparing()
{
    std::cout << "<<{:}>> SMART COMPARING <<{:}>>\n";
    print_names_of_comparing_files(file_handler.get_first_file_name(), file_handler.get_second_file_name());
    compare(first_file_data, second_file_data);
    compare(second_file_data, first_file_data);
    std::cout << "Differences:\n";
    print_result(DIFFERENCES);
    std::cout << "\nSIMILARITIES:\n";
    print_result(SIMILARITIES, std::string(file_handler.get_first_file_name().append(" & ").append(file_handler.get_second_file_name())));
    cleanup();
}

void Differentiator::set_debug_mode(bool mode)
{
    this->debug_mode = mode;
    file_handler.set_debug_mode(mode);
}