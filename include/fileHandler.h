#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "logger.h"
#include "FileTypes.h"
#include <fstream>
#include <list>

class FileHandler
{
private:
    std::ifstream first_file;
    std::ifstream second_file;

    std::string first_file_name;
    std::string second_file_name;

    bool debug_mode = false;
    Logger log;
    FileTypes types;

    std::list<std::string> first_file_data_list;
    std::list<std::string> second_file_data_list;

    class FailBitException : public std::ios_base::failure::exception
    {
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Delimiting character was not found or no characters were extracted at all";
        }
    };

    class BadBitException : public std::ios_base::failure::exception
    {
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Error occurred on stream";
        }
    };

public:
    FileHandler();
    ~FileHandler();

    void open_files(std::string &first_file_to_open, std::string &second_file_to_open);

    std::string get_first_file_name();
    std::string get_second_file_name();

    void set_debug_mode(bool mode);
    void set_files_to_start();

    std::list<std::string> *get_first_file_data();
    std::list<std::string> *get_second_file_data();

    class FileOpeningFailure : public std::exception
    {
        [[nodiscard]] const char *what() const noexcept override
        {
            return "File opening failure";
        }
    };

private:
    std::string get_file_type(std::string &file_name) const;
    bool check_files_type();
    bool check_file_type(std::string &file_type, std::string &file_name);
    static bool check_file_state(std::ifstream *file);
    bool verify_files();
    void read_files();
    static void read_file(std::ifstream *file, std::list<std::string> *file_data);
    void close_files();
};

#endif // !FILEHANDLER_H
