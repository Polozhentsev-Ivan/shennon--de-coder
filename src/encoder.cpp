#include "encoder.h"
#include "filemanager.h"
#include "wordlist.h"
#include <fstream>
#include <vector>

int encodeFile(const std::string& inPath,
               const std::string& outPath,
               const std::string& dictPath)
{
    std::ifstream fin(inPath, std::ios::binary);
    if (!fin) return 1;

    std::vector<uint64_t> freq(256, 0);
    std::vector<uint8_t>  data;
    char ch;
    while (fin.get(ch)) {
        uint8_t b = static_cast<uint8_t>(ch);
        ++freq[b];
        data.push_back(b);
    }
    fin.close();

    Map codes = buildWordList(freq);

    std::ofstream dict(dictPath);
    for (auto& [sym, code] : codes)
        dict << static_cast<int>(sym) << ' ' << code << '\n';

    std::ofstream fout(outPath, std::ios::binary);

    uint64_t origSize = data.size();
    fout.write(reinterpret_cast<const char*>(&origSize), sizeof(origSize));

    FileWriter bw(fout);
    for (uint8_t b : data) bw.put(codes[b]);
    bw.flush();
    return 0;
}