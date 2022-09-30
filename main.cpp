#include "./include/functions.h"

int main(int argc, const char **argv)
{
    try
    {
        if (argc < 3)
            perform_fail("Wrong amount of parameters", argc, argv);

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
        Differentiator diffApp(file1, file2, parameters[DEBUG], parameters[SHOW_LINE_AND_FILE_NAME]);
        if (parameters[BASIC_COMPARING])
            diffApp.basic_comparing();
        else if (parameters[SBS_COMPARING])
            diffApp.side_by_side_comparing();
        else if (parameters[SMART_COMPARING])
            diffApp.smart_comparing();
    }
    catch (const std::exception &e)
    {
        perform_fail(std::string("Failed: ").append(e.what()), argc, argv);
    }

    std::cout << "\nEnd of program...\n";

    return 0;
}
