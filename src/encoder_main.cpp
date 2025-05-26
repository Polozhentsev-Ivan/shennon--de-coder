#include "encoder.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: encode <in.*> <out.sf> <dict.txt>\n";
        return 1;
    }
    return encodeFile(argv[1], argv[2], argv[3]);
}