#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "differentiator.h"
#include <iostream>

#define PARAMETERS_AMOUNT 5

enum States
{
    BASIC_COMPARING,
    SBS_COMPARING,
    SMART_COMPARING,
    DEBUG,
    SHOW_LINE_AND_FILE_NAME
};

void print_usage(ColorProperties &colors);

void print_provided_parameters(int argc, const char **argv, int start_point);

void perform_fail(const std::string &error_msg, int argc, const char **argv, const Differentiator *diffApp);

void fill_parameters_with_false(bool *parameters, int length);

bool check_provided_parameter(const char *parameter, bool *parameters);

bool check_activated_modes(const bool parameters[]);

bool check_basic_comparing(int argc, const char **argv);

void read_parameters(int argc, const char **argv, bool *parameters, const Differentiator *diffApp);

#endif // __FUNCTIONS_H__