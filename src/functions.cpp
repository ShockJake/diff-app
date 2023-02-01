#include "../include/functions.h"

void print_usage(ColorProperties &colors)
{
    printf("%sUsage:\n", colors.YELLOW);
    printf("%sdiffApp file1 file2 [-b/-sbs/-smt] [-lf] [-D]\n", colors.GREEN);
    printf("\t-b   - Basic comparing (set by default)\n");
    printf("\t-sbs - Side by side comparing\n");
    printf("\t-smt - Smart comparing\n");
    printf("\t-D   - Debug (verbose) mode\n");
    printf("\t-lf  - Show line number and file name%s\n", colors.DEFAULT);
}

void print_provided_parameters(int argc, const char **argv, int start_point)
{
    for (int i = start_point; i < argc - 1; i++)
        printf("%s ", argv[i]);
    printf("%s\n", argv[argc - 1]);
}

void perform_fail(const std::string &error_msg, int argc, const char **argv, const Differentiator *diffApp)
{
    ColorProperties colors;
    printf("%s%s%s\n", colors.RED, error_msg.c_str(), colors.DEFAULT);
    printf("Provided arguments: ");
    print_provided_parameters(argc, argv, 0);
    print_usage(colors);
    delete diffApp;
    exit(1);
}

void fill_parameters_with_false(bool *parameters, const int length)
{
    for (int i = 0; i < length; i++)
        parameters[i] = false;
}

bool check_provided_parameter(const char *parameter, bool *parameters)
{
    if (std::string(parameter) == "-b")
        parameters[BASIC_COMPARING] = true;
    else if (std::string(parameter) == "-sbs")
        parameters[SBS_COMPARING] = true;
    else if (std::string(parameter) == "-D")
        parameters[DEBUG] = true;
    else if (std::string(parameter) == "-smt")
        parameters[SMART_COMPARING] = true;
    else if (std::string(parameter) == "-lf")
        parameters[SHOW_LINE_AND_FILE_NAME] = true;
    else
        return false;

    return true;
}

bool check_activated_modes(const bool parameters[])
{
    int active_modes_number = 0;
    for (int i = 0; i < PARAMETERS_AMOUNT - 2; i++)
    {
        if (parameters[i])
            active_modes_number++;
    }
    if (active_modes_number > 1)
        return false;

    return true;
}

bool check_basic_comparing(int argc, const char **argv)
{
    if (argc == 3)
        return true;
    if (argc == 4 && (std::string(argv[3]) == "-D" || std::string(argv[3]) == "-lf"))
        return true;
    if (argc == 5 && ((std::string(argv[3]) == "-D" && std::string(argv[4]) == "-lf") ||
                      (std::string(argv[3]) == "-lf" && std::string(argv[4]) == "-D")))
        return true;
    return false;
}

void read_parameters(int argc, const char **argv, bool *parameters, const Differentiator *diffApp)
{
    fill_parameters_with_false(parameters, PARAMETERS_AMOUNT);
    if (check_basic_comparing(argc, argv))
        parameters[BASIC_COMPARING] = true;

    for (int i = 3; i < argc; i++)
    {
        if (!check_provided_parameter(argv[i], parameters))
        {
            char err_msg[21] = "Unknown parameter : ";
            perform_fail(std::string(err_msg).append(argv[i]), argc, argv, diffApp);
        }
    }
    if (!check_activated_modes(parameters))
        perform_fail("More than one mode is activated", argc, argv, diffApp);
}