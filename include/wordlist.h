#ifndef WORDLIST_H
#define WORDLIST_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

using Map = std::map<uint8_t, std::string>;

Map buildWordList(const std::vector<uint64_t>& freq);

#endif