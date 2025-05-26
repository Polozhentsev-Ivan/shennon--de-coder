#include "filemanager.h"

void FileWriter::put(bool bit)
{
    buf = (buf << 1) | (bit ? 1 : 0);
    if (++filled == 8) {
        out.put(static_cast<char>(buf));
        buf = filled = 0;
    }
}

void FileWriter::put(const std::string& code)
{
    for (char c : code) put(c == '1');
}

void FileWriter::flush()
{
    if (filled) {
        buf <<= (8 - filled);
        out.put(static_cast<char>(buf));
        buf = filled = 0;
    }
}

bool FileReader::get(bool& bit)
{
    if (left == 0) {
        int ch = in.get();
        if (ch == EOF) return false;
        buf  = static_cast<uint8_t>(ch);
        left = 8;
    }
    bit = (buf & 0x80);
    buf <<= 1;
    --left;
    return true;
}