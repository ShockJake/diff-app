# Diff App

A simple command line tool that performs comparison of two files in different ways.

## Functionality

### Basic comparing

**Basic comparing** (one side comparing) - it's taking each line in one file and trying to find such line in second file.

### Side by Side comparing

**Side by Side comparing** (two sides comparing) - performing basic comparing in two ways. So you can see how to files can differ.

### Smart comparing

**Smart comparing** - search for similarities and differences of files and displays them. Can show
whether files are identical or don't have anything in common.

## Compilation and Running

### Compilation

Compiles all source code and links it to the executable file in `target` folder.
In order to compile just type:

    make all

To install it on your machine use:

    sudo make install 

*"Clean"* rule also provided:

    make clean

### Running

The Programs runs in different ways.

    diffApp file1 file2 -b/-sbs/-smt -D

Parameters:

- *file1*, *file2* - files that you want to compare

- *-b* - Basic comparing flag (is set by default)

- *-sbs* - Side by side comparing flag

- *-smt* - Smart comparing mode

- *-D* - Debug mode (displays info about program flow)
