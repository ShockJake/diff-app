#include "./include/differentiator.h"
#include "./include/colorProperties.h"
#include <iostream>
#include <cstring>

#define PARAMETERS_AMOUNT 4

enum States
{
    BASIC_COMPARING,
    SBS_COMPARING,
    SMART_COMPARING,
    DEBUG
};

void print_usage(ColorProperties &colors)
{

    printf("%sUsage:\n", colors.YELLOW);
    printf("%sdiffApp file1 file2 -b/-sbs/-smt (for comparing mode) -D (for debug info)\n", colors.GREEN);
    printf("\t-b   - Basic comparing (set by default)\n");
    printf("\t-sbs - Side by side comparing\n");
    printf("\t-smt - Smart comparing%s\n", colors.DEFAULT);
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
    ColorProperties colors;
    std::cout << colors.RED << error_msg << colors.DEFAULT << '\n';
    std::cout << "Provided arguments: ";
    print_provided_parameters(argc, argv, 0);

    print_usage(colors);
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

bool check_activated_modes(bool parameters[])
{
    int active_modes_number = 0;
    for (int i = 0; i < PARAMETERS_AMOUNT - 1; i++)
    {
        if (parameters[i])
        {
            active_modes_number++;
        }
    }

    if (active_modes_number > 1)
    {
        return false;
    }
    return true;
}

void read_parameters(int argc, const char **argv, bool *parameters)
{
    fill_parameters_with_false(parameters, PARAMETERS_AMOUNT);
    if (argc == 3 || (argc == 4 && !strcmp(argv[3], "-D")))
    {
        parameters[BASIC_COMPARING] = true;
    }
    for (int i = 3; i < argc; i++)
    {
        if (!check_provided_parameter(argv[i], parameters))
        {
            char err_msg[21] = "Unknown parameter : ";
            perform_fail(strcat(err_msg, argv[i]), argc, argv);
        }
    }
    if (!check_activated_modes(parameters))
    {
        perform_fail("More than one mode is activated", argc, argv);
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
        std::cout << "First file:  " << file1 << '\n';
        std::cout << "Second file: " << file2 << '\n';
        std::cout << "Provided parameters: ";
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
        perform_fail("Failed", argc, argv);
    }

    std::cout << "\nEnd of program...\n";

    return 0;
}
