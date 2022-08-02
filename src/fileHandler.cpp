#include "../include/fileHandler.h"
#include <iostream>
#include <string>

FileHandler::FileHandler() {}

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

void FileHandler::open_files(std::string &first_file_name, std::string &second_file_name)
{
    this->first_file_name = first_file_name;
    this->second_file_name = second_file_name;

    this->first_file.open(first_file_name);
    this->second_file.open(second_file_name);

    if (debug_mode)
    {
        log.report_info("File verification started");
    }
    if (!verify_files())
    {
        close_files();
        throw std::fstream::failure("File verification failed");
    }
    read_files();
}

void FileHandler::read_files()
{
    while (!first_file.eof())
    {
        std::string line;
        std::getline(first_file, line);
        first_file_data.insert(line);
    }
    while (!second_file.eof())
    {
        std::string line;
        std::getline(second_file, line);
        second_file_data.insert(line);
    }
    set_files_to_start();
}

std::set<std::string> *FileHandler::get_first_file_data()
{
    if (first_file_data.size() == 0)
    {
        log.report_error("No input data from file", first_file_name);
        close_files();
        exit(1);
    }
    return &first_file_data;
}

std::set<std::string> *FileHandler::get_second_file_data()
{
    if (second_file_data.size() == 0)
    {
        log.report_error("No input data from file", second_file_name);
        close_files();
        exit(1);
    }
    return &second_file_data;
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

void FileHandler::set_debug_mode(bool mode)
{
    this->debug_mode = mode;
    if (debug_mode)
    {
        log.report_info("Debug mode is activated");
    }
}
