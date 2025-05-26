#include "decoder.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: decode <in.sf> <dict.txt> <outfile>\n";
        return 1;
    }
    return decodeFile(argv[1], argv[2], argv[3]);
}