
#include "./include/differentiator.h"
#include <iostream>
#include <cstring>

#define PARAMETERS_AMOUNT 4

enum States
{
    BASIC_COMPARING,
    SBS_COMPARING,
    DEBUG,
    SMART_COMPARING
};

void print_usage()
{
    printf("Usage:\n");
    printf("./program file1 file2 -b/-s (for comparing mode) -D (for debug info)\n");
}

void print_provided_parameters(int argc, const char **argv, int start_point)
{
    for (int i = start_point; i < argc; i++)
    {
        std::cout << argv[i] << ' ';
    }
    std::cout << '\n';
}

void perform_fail(std::string error_msg, int argc, const char **argv)
{
    std::cout << error_msg << '\n';
    print_provided_parameters(argc, argv, 0);
    print_usage();

    fgetc(stdin);
    exit(1);
}

void fill_parameters_with_false(bool *parameters, const int length)
{
    for (int i = 0; i < length; i++)
    {
        parameters[i] = false;
    }
}

bool check_provided_parameter(const char *parameter, bool *parameters)
{
    if (!strcmp(parameter, "-b"))
    {
        parameters[BASIC_COMPARING] = true;
    }
    else if (!strcmp(parameter, "-sbs"))
    {
        parameters[SBS_COMPARING] = true;
    }
    else if (!strcmp(parameter, "-D"))
    {
        parameters[DEBUG] = true;
    }
    else if (!strcmp(parameter, "-smt"))
    {
        parameters[SMART_COMPARING] = true;
    }
    else
    {
        return false;
    }
    return true;
}

void read_parameters(int argc, const char **argv, bool *parameters)
{
    fill_parameters_with_false(parameters, PARAMETERS_AMOUNT);
    if (argc == 3)
    {
        parameters[BASIC_COMPARING] = true;
    }
    for (int i = 3; i < argc; i++)
    {
        if (!check_provided_parameter(argv[i], parameters))
        {
            char err_msg[20] = "Unknown parameter :";
            perform_fail(strcat(err_msg, argv[i]), argc, argv);
        }
    }
    if ((parameters[BASIC_COMPARING] && parameters[SBS_COMPARING]))
    {
        perform_fail("More than one mode is activated", argc, argv);
    }
    if (!parameters[BASIC_COMPARING] && !parameters[SBS_COMPARING] && !parameters[SMART_COMPARING])
    {
        perform_fail("Any mode isn't activated", argc, argv);
    }
}

int main(int argc, const char **argv)
{
    if (argc < 3)
    {
        perform_fail("Wrong amount of parameters", argc, argv);
    }
    bool parameters[PARAMETERS_AMOUNT];
    read_parameters(argc, argv, parameters);

    std::string file1 = argv[1];
    std::string file2 = argv[2];

    if (parameters[DEBUG])
    {
        std::cout << "First file: provided:" << file1 << '\n';
        std::cout << "Second file: provided:" << file2 << '\n';
        print_provided_parameters(argc, argv, 3);
    }

    try
    {
        Differentiator diffApp(file1, file2, parameters[DEBUG]);
        if (parameters[BASIC_COMPARING])
        {
            diffApp.basic_comparing();
        }
        else if (parameters[SBS_COMPARING])
        {
            diffApp.side_by_side_comparing();
        }
        else if (parameters[SMART_COMPARING])
        {
            diffApp.smart_comparing();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "\nEnd of program...\n";

    return 0;
}
