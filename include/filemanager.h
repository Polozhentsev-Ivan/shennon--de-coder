#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <cstdint>
#include <ostream>
#include <istream>

class FileWriter {
public:
    explicit FileWriter(std::ostream& out) : out(out) {}
    void put(bool bit);          
    void put(const std::string& code);
    void flush(); // заполняет нулями
private:
    std::ostream& out;
    uint8_t  buf{0};
    uint8_t  filled{0};
};

class FileReader {
public:
    explicit FileReader(std::istream& in) : in(in) {}
    bool get(bool& bit);
private:
    std::istream& in;
    uint8_t  buf{0};
    uint8_t  left{0};
};

#endif