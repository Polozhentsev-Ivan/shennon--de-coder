#include "decoder.h"
#include "filemanager.h"
#include <fstream>
#include <map>
#include <string>

static std::map<std::string, uint8_t> loadDict(const std::string& path)
{
    std::map<std::string, uint8_t> m;
    std::ifstream f(path);
    int sym; std::string code;
    while (f >> sym >> code) m[code] = static_cast<uint8_t>(sym);
    return m;
}

int decodeFile(const std::string& inPath,
               const std::string& dictPath,
               const std::string& outPath)
{
    std::ifstream fin(inPath, std::ios::binary);
    if (!fin) return 1;

    uint64_t origSize = 0;
    if (!fin.read(reinterpret_cast<char*>(&origSize), sizeof(origSize)))
        return 1;

    if (origSize == 0) {
        std::ofstream(outPath, std::ios::binary);  
        return 0;
    }

    auto dict = loadDict(dictPath);
    if (dict.empty()) return 1;

    std::ofstream fout(outPath, std::ios::binary);

    FileReader br(fin);
    std::string cur;
    uint64_t written = 0;
    bool bit;
    while (written < origSize && br.get(bit)) {
        cur.push_back(bit ? '1' : '0');
        auto it = dict.find(cur);
        if (it != dict.end()) {
            fout.put(static_cast<char>(it->second));
            cur.clear();
            ++written;
        }
    }
    return 0;
}