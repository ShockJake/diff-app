#include "./include/functions.h"
#include <csignal>

Differentiator *diffApp = nullptr;

void signal_handler(int singal_number)
{
    printf("\nInterrupting program...\n");
    diffApp->~Differentiator();
    exit(singal_number);
}

int main(int argc, const char **argv)
{
    try
    {
        if (argc < 3)
            perform_fail("Wrong amount of parameters", argc, argv);

        bool parameters[PARAMETERS_AMOUNT];
        read_parameters(argc, argv, parameters);
        signal(SIGINT, signal_handler);

        std::string file1 = argv[1];
        std::string file2 = argv[2];

        if (parameters[DEBUG])
        {
            std::cout << "First file:  " << file1 << '\n';
            std::cout << "Second file: " << file2 << '\n';
            std::cout << "Provided parameters: ";
            print_provided_parameters(argc, argv, 3);
        }
        Differentiator app(file1, file2, parameters[DEBUG], parameters[SHOW_LINE_AND_FILE_NAME]);
        diffApp = &app;
        if (parameters[BASIC_COMPARING])
            diffApp->basic_comparing();
        else if (parameters[SBS_COMPARING])
            diffApp->side_by_side_comparing();
        else if (parameters[SMART_COMPARING])
            diffApp->smart_comparing();
    }
    catch (const std::exception &e)
    {
        perform_fail(std::string("Failed: ").append(e.what()), argc, argv);
    }

    printf("\nEnd of program...\n");
    return 0;
}
