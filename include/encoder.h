#ifndef ENCODER_H
#define ENCODER_H

#include <string>

int encodeFile(const std::string& inPath,
               const std::string& outPath,
               const std::string& dictPath);

#endif