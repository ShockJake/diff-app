#include "../include/fileHandler.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

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
        log.report_info("Files are opened successfully");
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
    catch (const std::exception &e)
    {
        log.report_error("Cannot close file", e.what());
    }
}

std::string FileHandler::get_file_type(std::string &file_name)
{
    fs::file_status s = fs::status(file_name);
    if (fs::is_regular_file(s))
        return types.FILE;
    if (fs::is_directory(s))
        return types.DIRECTORY;
    if (fs::is_block_file(s))
        return types.BLOCK_FILE;
    if (fs::is_character_file(s))
        return types.CHARACTER_DEVICE;
    if (fs::is_fifo(s))
        return types.FIFO;
    if (fs::is_socket(s))
        return types.SOCKET;
    if (fs::is_symlink(s))
        return types.SYMLINK;
    if (!fs::exists(s))
        return types.NONEXISTING;
    else
        return types.UNKNOWN;
}

bool FileHandler::check_file_type(std::string &file_type, std::string &file_name)
{
    if (file_type != types.FILE)
    {
        std::string error_msg = "Invalid file type of file ";
        if (debug_mode)
            log.report_error(error_msg
                                 .append(first_file_name)
                                 .append(", actual type is: ")
                                 .append(file_type));
        return false;
    }
    return true;
}

bool FileHandler::check_files_type()
{
    std::string first_file_type = get_file_type(first_file_name);
    std::string second_file_type = get_file_type(second_file_name);
    bool result = check_file_type(first_file_type, first_file_name) && check_file_type(second_file_type, second_file_name);
    return result;
}

bool FileHandler::verify_files()
{
    if (!first_file.is_open())
    {
        if (debug_mode)
            log.report_error("Cannot open file", first_file_name);
        return false;
    }
    if (!second_file.is_open())
    {
        if (debug_mode)
            log.report_error("Cannot open file ", second_file_name);
        return false;
    }

    if (!check_files_type())
        return false;

    if (debug_mode)
        log.report_info("Files are verified");

    return true;
}

void FileHandler::set_files_to_start()
{
    try
    {
        if (first_file.tellg() != 0)
            first_file.seekg(0);
        if (second_file.tellg() != 0)
            second_file.seekg(0);
    }
    catch (const std::ios_base::failure &e)
    {
        if (debug_mode)
            log.report_error("Fail in setting files to start", e.what());
    }
    catch (const std::exception &e)
    {
        if (debug_mode)
            log.report_error("Fail in setting files to start", e.what());
    }
    if (debug_mode)
        log.report_info("Files were set on the start position");
}

void FileHandler::open_files(std::string &first_file_name, std::string &second_file_name)
{
    this->first_file_name = first_file_name;
    this->second_file_name = second_file_name;

    this->first_file.open(first_file_name);
    this->second_file.open(second_file_name);

    if (debug_mode)
        log.report_info("File verification started");

    if (!verify_files())
    {
        close_files();
        throw std::fstream::failure("File verification failed");
    }
    read_files();
}

bool FileHandler::check_file_state(std::ifstream *file)
{
    if (file->good())
        return true;
    if (file->eof())
        return false;
    if (file->bad())
        throw BadbitException();
    if (file->fail())
        throw FailbitException();
    return true;
}

std::string FileHandler::get_parsed_line_number(int line_number)
{
    std::string parser_line_number = std::to_string(line_number);
    if (line_number < 10)
        return std::string("00").append(parser_line_number);

    if (line_number >= 10 && line_number < 100)
        return std::string("0").append(parser_line_number);
    else
        return parser_line_number;
}

void FileHandler::read_file(std::ifstream *file, std::list<std::string> *file_data)
{
    std::string line;
    while (check_file_state(file))
    {
        std::getline(*file, line);
        if (line == " " || line == "\n" || line == "")
            continue;
        file_data->push_back(line);
    }
}

void FileHandler::read_files()
{
    if (debug_mode)
        log.report_info("Files reading started");
    read_file(&first_file, &first_file_data_list);
    if (debug_mode)
        log.report_info("First file was read successfully", first_file_name);
    read_file(&second_file, &second_file_data_list);
    if (debug_mode)
        log.report_info("Second file was read successfully", second_file_name);
    set_files_to_start();
    if (debug_mode)
        log.report_info("Files reading ended successfully");
}

std::list<std::string> *FileHandler::get_first_file_data()
{
    if (first_file_data_list.size() == 0)
    {
        if (debug_mode)
            log.report_error("No input data from file", first_file_name);
        close_files();
        throw std::fstream::failure("File is empty");
    }
    return &first_file_data_list;
}

std::list<std::string> *FileHandler::get_second_file_data()
{
    if (second_file_data_list.size() == 0)
    {
        if (debug_mode)
            log.report_error("No input data from file", second_file_name);
        close_files();
        throw std::fstream::failure("File is empty");
    }
    return &second_file_data_list;
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
        log.report_info("Debug mode is activated");
}
