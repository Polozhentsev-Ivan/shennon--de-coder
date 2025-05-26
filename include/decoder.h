#ifndef DECODER_H
#define DECODER_H

#include <string>
int decodeFile(const std::string& inPath,
               const std::string& dictPath,
               const std::string& outPath);
#endif