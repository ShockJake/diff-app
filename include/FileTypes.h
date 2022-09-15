#ifndef FILETYPES_H
#define FILETYPES_H

class FileTypes
{
public:
    const char *FILE = "Regular File";
    const char *DIRECTORY = "Directory";
    const char *BLOCK_FILE = "Block File";
    const char *CHARACTER_DEVICE = "Character device";
    const char *FIFO = "FIFO pipe";
    const char *SOCKET = "Socket";
    const char *SYMLINK = "Symlink";
    const char *NONEXISTING = "Does not exist";
    const char *UNKNOWN = "Unknown";
};

#endif // !FILETYPES_H
