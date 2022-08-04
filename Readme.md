# Diff App

A simple tool that performs comparison of two files in differen ways.

## Functionality

### Basic comparing

**Basic comparing** (one side comparing) - it's taking each line in one file and trying to find such line in second file.

### Side by Side comparing

**Side by Side comparing** (two sides comparing) - performing basic comparing in two ways. So you can see how to files can differ.

### Smart comparing

**Smart comparing** - search for similarities and differences of files and displays them.

## Compilation and Running

### Compilation

Compiles all source code and links it to the executable file in `target` folder.
In order to compile just type:

    make

*"Clean"* rule also provided:

    make clean

### Running

The Programs runs in different ways.

    ./diffApp file1 file2 -b/-s -D

Parameters:

- *file1*, *file2* - files that you want to compare

- *-b* - Basic comparing flag (is set by default)

- *-s* - Side by side comparing flag

- *-D* - Debug mode (displays info about program flow)
