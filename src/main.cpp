#include "encoder.h"
#include "decoder.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 5) {
        std::cerr << "Usage: \n -encode <in.*> <out.sf> <dict.txt>\n -decode <in.sf> <dict.txt> <outfile>\n";
        return 1;
    }
    std::string cmd = argv[1];

    if (cmd == "-e" || cmd == "-encode")
        return encodeFile(argv[2], argv[3], argv[4]);

    if (cmd == "-d" || cmd == "-decode")
        return decodeFile(argv[2], argv[3], argv[4]);
}