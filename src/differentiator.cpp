#include "../include/differentiator.h"
#include "../include/colorProperties.h"
#include <iostream>
#include <string>
#include <utility>

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
        if (debug_mode)
            log.report_error("Opening files failure", e.what());
        throw FileOpeningFailure();
    }
    catch (const std::exception &e)
    {
        if (debug_mode)
            log.report_error("Opening files failure", e.what());
        throw FileOpeningFailure();
    }
}

Differentiator::~Differentiator() {}

void Differentiator::print_difference_percentage()
{
    int different_lines = differences.size();
    if (debug_mode) 
    {
        std::string msg(std::string("Different lines: \t"));
        log.report_info(msg.append(std::to_string(different_lines)).c_str());
    }
    int similar_lines = similarities.size();
    if (debug_mode) 
    {
        std::string msg(std::string("Similar lines: \t"));
        log.report_info(msg.append(std::to_string(similar_lines)).c_str());
    }
    int all_lines = different_lines + similar_lines;
    if (debug_mode)
    {
        std::string msg(std::string("All lines: \t"));
        log.report_info(msg.append(std::to_string(all_lines)).c_str());
    }
    double result = (double) different_lines / (double) all_lines * 100;

    std::cout << colors.GREEN << "Files are " << result << "%" << " different" << colors.DEFAULT << std::endl;
}

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
    std::cout << colors.BLUE << "Lines that are only present in - " << file_name << colors.DEFAULT << std::endl;
    for (i = begin; i != end; i++)
    {
        std::cout << *i << std::endl;
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
    if (begin == end)
    {
        std::cout << colors.YELLOW << "No result..." << colors.DEFAULT << std::endl;
        return;
    }

    for (i = begin; i != end; i++)
    {
        std::cout << *i << std::endl;
    }
}

void Differentiator::cleanup()
{
    if (debug_mode)
        log.report_info("Clearing started...");
    similarities.clear();
    differences.clear();
    if (debug_mode)
        log.report_info("Clearing finished...");
}

void Differentiator::set_files_data()
{
    this->first_file_data = file_handler.get_first_file_data();
    this->second_file_data = file_handler.get_second_file_data();
}

void Differentiator::print_names_of_comparing_files(std::string first_file_name, std::string second_file_name)
{
    std::cout << colors.CYAN << "Comparing files: " << first_file_name << " ->>- " << second_file_name << colors.DEFAULT << std::endl;
}

void Differentiator::write_data(std::string line, std::set<std::string> *file_data)
{

    std::pair<std::set<std::string>::iterator, bool> result;

    if (file_data->find(line) == file_data->end())
    {
        result = differences.insert(line);
        if (!result.second && debug_mode)
        {
            log.report_warn(std::string().append("Insertion failed: ").append(line).c_str());
        }
        if (debug_mode)
            log.report_info("Difference spotted", line);
    }
    else
    {
        result = similarities.insert(line);
        if (!result.second && debug_mode)
        {
            log.report_warn(std::string().append("Insertion failed: ").append(line).c_str());
        }
        if (debug_mode)
            log.report_info("Similarity spotted", line);
    }
}

void Differentiator::compare(std::set<std::string> *first_file_data, std::set<std::string> *second_file_data)
{
    try
    {
        std::set<std::string>::iterator i;
        auto begin = first_file_data->begin();
        auto end = first_file_data->end();

        if (debug_mode)
            log.report_info("Writing Data started");
        for (i = begin; i != end; i++)
        {
            write_data(*i, second_file_data);
        }
        if (debug_mode)
            log.report_info("Writing Data finished successfully\n");
    }
    catch (const std::exception &e)
    {
        log.report_error("Comparing files failure", e.what());
    }
}

bool Differentiator::check_blank_line() 
{
    if (similarities.find(" ") != similarities.end() && similarities.size() == 1) 
    {
        if (debug_mode) 
            log.report_info("Only blank line is common in both files");
        return true;
    }
    return false;
}

void Differentiator::basic_comparing()
{
    std::cout << colors.BLUE << "<=> BASIC COMPARING <=>\n" << colors.DEFAULT;
    print_names_of_comparing_files(file_handler.get_first_file_name(), file_handler.get_second_file_name());
    compare(first_file_data, second_file_data);
    print_result(DIFFERENCES, file_handler.get_first_file_name());
}

void Differentiator::side_by_side_comparing()
{
    std::cout << colors.PURPLE << "\\\\\\\\\\\\ SIDE BY SIDE COMPARING //////\n" << colors.PURPLE;
    print_names_of_comparing_files(file_handler.get_first_file_name(), file_handler.get_second_file_name());
    compare(first_file_data, second_file_data);
    print_result(DIFFERENCES, file_handler.get_first_file_name());
    cleanup();
    std::string line_separator = "----------------------------------------------";
    std::cout << "\n" << colors.PURPLE
              << line_separator << colors.DEFAULT << "\n\n";
    print_names_of_comparing_files(file_handler.get_second_file_name(), file_handler.get_first_file_name());
    compare(second_file_data, first_file_data);
    print_result(DIFFERENCES, file_handler.get_second_file_name());
}

void Differentiator::smart_comparing()
{
    std::cout << colors.YELLOW << "<<{:}>> SMART COMPARING <<{:}>>\n" << colors.DEFAULT;
    print_names_of_comparing_files(file_handler.get_first_file_name(), file_handler.get_second_file_name());
    compare(first_file_data, second_file_data);
    compare(second_file_data, first_file_data);
    if (differences.empty() || check_blank_line()) {
        std::cout << colors.BLUE << "Files are identical\n" << colors.DEFAULT;
        return;
    }
    if (similarities.empty()) {
        std::cout << colors.BLUE << "Files are totally different\n" << colors.DEFAULT;
        return;
    }
    std::cout << colors.YELLOW << "Differences:\n" << colors.DEFAULT;
    print_result(DIFFERENCES);
    std::cout << colors.BLUE << "\nSimilarities:\n" << colors.DEFAULT;
    print_result(SIMILARITIES);
    std::cout << "\n";
    print_difference_percentage();
}

void Differentiator::set_debug_mode(bool mode)
{
    this->debug_mode = mode;
    file_handler.set_debug_mode(mode);
}
