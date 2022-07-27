#include "fileHandler.h"
#include <iostream>
#include <string>

FileHandler::FileHandler()
{
}

FileHandler::FileHandler(std::string &first_file_name, std::string &second_file_name)
{
    if (debug_mode)
    {
        log.report_info("Opening files");
    }
    open_files(first_file_name, second_file_name);
    if (debug_mode)
    {
        log.report_info("Files opened successfuly");
    }
}

FileHandler::~FileHandler()
{
    close_files();
}

void FileHandler::close_files()
{
    try
    {
        first_file.close();
        second_file.close();
    }
    catch (const std::ifstream::failure &e)
    {
        log.report_error("Cannot close file", e.what());
    }
}

bool FileHandler::verify_files()
{
    if (!first_file.is_open())
    {
        log.report_error("Cannot open file: ", first_file_name);
        return false;
    }
    if (!second_file.is_open())
    {
        log.report_error("Cannot open file", second_file_name);
        return false;
    }
    if (debug_mode)
    {
        log.report_info("Files are verified");
    }
    return true;
}

void FileHandler::set_files_to_start()
{
    try
    {
        if (first_file.tellg() != 0)
        {
            first_file.seekg(0);
        }
        if (second_file.tellg() != 0)
        {
            second_file.seekg(0);
        }
    }
    catch (const std::ios_base::failure &e)
    {
        log.report_error("Fail in setting files to start", e.what());
    }
    catch (const std::exception &e)
    {
        log.report_error("Fail in setting files to start", e.what());
    }
    if (debug_mode)
    {
        log.report_info("Files were set on the start position");
    }
}

void FileHandler::read_files_size()
{
    if (debug_mode)
    {
        log.report_info("Reding files to get their size");
    }
    first_file_size = first_file.seekg(0, std::ios::end).tellg();
    second_file_size = second_file.seekg(0, std::ios::end).tellg();
    if (debug_mode)
    {
        log.report_info("Reading files to get size ended");
        std::string first_file_info;
        first_file_info.append(first_file_name).append("=").append(std::to_string(first_file_size));
        log.report_info(first_file_info.c_str());
        std::string second_file_info;
        second_file_info.append(second_file_name).append("=").append(std::to_string(second_file_size));
        log.report_info(second_file_info.c_str());
    }
}

void FileHandler::open_files(std::string &first_file_name, std::string &second_file_name)
{
    this->first_file_name = first_file_name;
    this->second_file_name = second_file_name;

    this->first_file.open(first_file_name);
    this->second_file.open(second_file_name);

    if (debug_mode)
    {
        log.report_info("File verification start");
    }
    if (!verify_files())
    {
        close_files();
        throw std::fstream::failure::exception();
    }
    // read_files_size();
    //  set_files_to_start();
    //    swap_files();
}

std::ifstream *FileHandler::get_first_file()
{
    return &first_file;
}

std::ifstream *FileHandler::get_second_file()
{
    return &second_file;
}

std::string FileHandler::get_first_file_name()
{
    return first_file_name;
}

std::string FileHandler::get_second_file_name()
{
    return second_file_name;
}

unsigned long int FileHandler::get_first_file_size()
{
    return this->first_file_size;
}

unsigned long int FileHandler::get_second_file_size()
{
    return this->second_file_size;
}

void FileHandler::set_debug_mode(bool mode)
{
    this->debug_mode = mode;
    if (debug_mode)
    {
        log.report_info("Debug mode is activated");
    }
}
