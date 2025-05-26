#include "wordlist.h"
#include <algorithm>

namespace {
struct List { uint8_t sym; uint64_t freq; };

void split(std::vector<List>& v, size_t l, size_t r,
           Map& table, const std::string& pref)
{
    if (l == r) {
        table[v[l].sym] = pref.empty() ? "0" : pref;
        return;
    }
    uint64_t total = 0;
    for (size_t i = l; i <= r; ++i) total += v[i].freq;

    uint64_t acc = 0;
    size_t mid = l;
    while (mid < r && acc + v[mid].freq < total / 2) {
        acc += v[mid].freq;
        ++mid;
    }
    split(v, l, mid,   table, pref + '0');
    split(v, mid + 1, r, table, pref + '1');
}
}

Map buildWordList(const std::vector<uint64_t>& freq)
{
    std::vector<List> v;
    for (uint16_t i = 0; i < 256; ++i)
        if (freq[i]) v.push_back({static_cast<uint8_t>(i), freq[i]});

    std::sort(v.begin(), v.end(),
              [](const List& a, const List& b) { return a.freq > b.freq; });

    Map m;
    if (!v.empty()) split(v, 0, v.size() - 1, m, "");
    return m;
}