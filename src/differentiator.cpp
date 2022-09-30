#include "../include/differentiator.h"
#include "../include/colorProperties.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <utility>

Differentiator::Differentiator(std::string &first_file_name, std::string &second_file_name, bool debug_mode, bool print_lines)
{
    try
    {
        set_debug_mode(debug_mode);
        set_print_lines(print_lines);
        file_handler.open_files(first_file_name, second_file_name);
        set_files_data();
    }
    catch (const std::ifstream::failure &e)
    {
        if (debug_mode)
            log.report_error("Opening files failure", e.what());
        throw FileHandler::FileOpeningFailure();
    }
    catch (const std::exception &e)
    {
        if (debug_mode)
            log.report_error("File reading error", e.what());
        throw FileProceedingFailure();
    }
}

Differentiator::~Differentiator() {}

void Differentiator::print_number_of_lines(int differences, int similarities, int all)
{
    std::string msg(std::string("Different lines: \t"));
    log.report_info(msg.append(std::to_string(differences)).c_str());

    msg = std::string("Similar lines: \t");
    log.report_info(msg.append(std::to_string(similarities)).c_str());

    msg = std::string("All lines: \t");
    log.report_info(msg.append(std::to_string(all)).c_str());
}

void Differentiator::print_difference_percentage()
{
    double different_lines = (double)differences.size();
    double similar_lines = (double)similarities.size();
    double all_lines = different_lines + similar_lines;
    double result = different_lines / all_lines * 100;

    if (debug_mode)
        print_number_of_lines(different_lines, similar_lines, all_lines);

    std::cout << colors.GREEN << "Files are " << result << "%"
              << " different" << colors.DEFAULT << std::endl;
}

void Differentiator::print_result(bool result_type, std::string file_name)
{
    std::list<std::string>::iterator i;
    std::list<std::string>::iterator begin;
    std::list<std::string>::iterator end;

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

bool Differentiator::check_blank_line(std::list<std::string> *file_data)
{
    if (file_data->size() == 1)
    {
        auto i = file_data->begin();
        if (std::string("") == *i || std::string("\n") == *i)
        {
            return true;
        }
    }
    return false;
}

void Differentiator::print_result(bool result_type)
{
    std::list<std::string>::iterator i;
    std::list<std::string>::iterator begin;
    std::list<std::string>::iterator end;

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
        if (std::string("\n") == *i || std::string("") == *i)
            std::cout << " -- Blank line -- " << std::endl;
        else
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

std::string Differentiator::get_parsed_line_number(int line_number)
{
    std::string parser_line_number = std::to_string(line_number);
    if (line_number < 10)
        return std::string("00").append(parser_line_number);

    if (line_number >= 10 && line_number < 100)
        return std::string("0").append(parser_line_number);
    else
        return parser_line_number;
}

std::string Differentiator::get_line_prefix(std::string &parsed_line_number, std::string &file_name)
{
    return std::string(colors.YELLOW)
        .append("[")
        .append(parsed_line_number)
        .append(",")
        .append(file_name)
        .append("] ")
        .append(colors.DEFAULT);
}

void Differentiator::write_data(std::string line, std::list<std::string> *file_data, std::string &file_name, int line_number)
{
    std::list<std::string>::iterator result;
    std::string parsed_line_number = get_parsed_line_number(line_number);
    std::string prefix = get_line_prefix(parsed_line_number, file_name);

    if (std::find(file_data->begin(), file_data->end(), line) == file_data->end())
    {
        if (print_lines)
            line = prefix.append(line);

        result = differences.insert(differences.end(), line);
        if (debug_mode)
            log.report_info("Difference spotted", line);
    }
    else
    {
        if (print_lines)
            line = prefix.append(line);

        result = similarities.insert(similarities.end(), line);
        if (debug_mode)
            log.report_info("Similarity spotted", line);
    }
}

void Differentiator::compare(std::list<std::string> *first_file_data, std::list<std::string> *second_file_data, std::string file_name)
{
    try
    {
        std::list<std::string>::iterator i;
        auto begin = first_file_data->begin();
        auto end = first_file_data->end();
        int line_number = 1;

        if (debug_mode)
            log.report_info("Writing Data started");
        for (i = begin; i != end; i++)
        {
            write_data(*i, second_file_data, file_name, line_number);
            line_number++;
        }
        if (debug_mode)
            log.report_info("Writing Data finished successfully\n");
    }
    catch (const std::exception &e)
    {
        log.report_error("Comparing files failure", e.what());
    }
}

void Differentiator::basic_comparing()
{
    std::cout << colors.BLUE << "<=> BASIC COMPARING <=>\n"
              << colors.DEFAULT;
    print_names_of_comparing_files(file_handler.get_first_file_name(), file_handler.get_second_file_name());
    compare(first_file_data, second_file_data, file_handler.get_first_file_name());
    print_result(DIFFERENCES, file_handler.get_first_file_name());
}

void Differentiator::side_by_side_comparing()
{
    std::cout << colors.PURPLE << "\\\\\\\\\\\\ SIDE BY SIDE COMPARING //////\n"
              << colors.PURPLE;
    print_names_of_comparing_files(file_handler.get_first_file_name(), file_handler.get_second_file_name());
    compare(first_file_data, second_file_data, file_handler.get_first_file_name());
    print_result(DIFFERENCES, file_handler.get_first_file_name());
    cleanup();
    std::string line_separator = "----------------------------------------------";
    std::cout << "\n"
              << colors.PURPLE
              << line_separator << colors.DEFAULT << "\n\n";
    print_names_of_comparing_files(file_handler.get_second_file_name(), file_handler.get_first_file_name());
    compare(second_file_data, first_file_data, file_handler.get_second_file_name());
    print_result(DIFFERENCES, file_handler.get_second_file_name());
}

void Differentiator::smart_comparing()
{
    std::cout << colors.YELLOW << "<<{:}>> SMART COMPARING <<{:}>>\n"
              << colors.DEFAULT;
    print_names_of_comparing_files(file_handler.get_first_file_name(), file_handler.get_second_file_name());
    compare(first_file_data, second_file_data, file_handler.get_first_file_name());
    compare(second_file_data, first_file_data, file_handler.get_second_file_name());
    if (differences.empty() || check_blank_line(&differences))
    {
        if (debug_mode)
            print_number_of_lines(differences.size(), similarities.size(), differences.size() + similarities.size());

        std::cout << colors.BLUE << "Files are identical\n"
                  << colors.DEFAULT;
        return;
    }
    if (similarities.empty() || check_blank_line(&similarities))
    {
        if (debug_mode)
            print_number_of_lines(differences.size(), similarities.size(), differences.size() + similarities.size());

        std::cout << colors.BLUE << "Files are totally different\n"
                  << colors.DEFAULT;
        return;
    }
    std::cout << colors.YELLOW << "Differences:\n"
              << colors.DEFAULT;
    print_result(DIFFERENCES);
    std::cout << colors.BLUE << "\nSimilarities:\n"
              << colors.DEFAULT;
    print_result(SIMILARITIES);
    std::cout << "\n";
    print_difference_percentage();
}

void Differentiator::set_debug_mode(bool mode)
{
    this->debug_mode = mode;
    file_handler.set_debug_mode(mode);
}

void Differentiator::set_print_lines(bool print_lines)
{
    this->print_lines = print_lines;
    if (debug_mode && print_lines)
        log.report_info("Showing lines number and file name");
}