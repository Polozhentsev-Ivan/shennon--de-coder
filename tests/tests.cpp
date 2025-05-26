// tests/tests.cpp
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <random>
#include "../include/encoder.h"
#include "../include/decoder.h"

namespace fs = std::filesystem;


bool filesEquality(const fs::path& a, const fs::path& b)
{
    std::ifstream f1(a, std::ios::binary | std::ios::ate);
    std::ifstream f2(b, std::ios::binary | std::ios::ate);
    if (!f1 || !f2) return false;
    if (f1.tellg() != f2.tellg()) return false;
    f1.seekg(0); f2.seekg(0);
    std::istreambuf_iterator<char> it1(f1), it2(f2), end;
    return std::equal(it1, end, it2);
}

void writeRandomFile(const fs::path& p, std::size_t size)
{
    std::ofstream out(p, std::ios::binary);
    std::mt19937_64 gen{123456789};
    std::uniform_int_distribution<int> dist(0, 255);
    for (std::size_t i = 0; i < size; ++i)
        out.put(static_cast<char>(dist(gen)));
}


TEST(Shannon, SimpleString)
{
    fs::path tmp = fs::temp_directory_path();
    fs::path raw = tmp / "sf_raw.bin";
    fs::path packed = tmp / "sf_packed.sf";
    fs::path dict = tmp / "sf_dict.txt";
    fs::path restored = tmp / "sf_restored.bin";

    {
        std::ofstream(raw, std::ios::binary) << "ABBCCCDDDD";
    }

    ASSERT_EQ(encodeFile(raw.string(), packed.string(), dict.string()), 0);
    ASSERT_EQ(decodeFile(packed.string(), dict.string(), restored.string()), 0);
    EXPECT_TRUE(filesEquality(raw, restored));
}

TEST(Shannon, RandomFiles)
{
    fs::path tmp = fs::temp_directory_path();
    fs::path raw = tmp / "sf_rand_raw.bin";
    fs::path packed = tmp / "sf_rand_packed.sf";
    fs::path dict = tmp / "sf_rand_dict.txt";
    fs::path restored = tmp / "sf_rand_restored.bin";

    for (int i = 0; i < 5; ++i) {
        writeRandomFile(raw, 1000 + i * 2000);
        ASSERT_EQ(encodeFile(raw.string(), packed.string(), dict.string()), 0);
        ASSERT_EQ(decodeFile(packed.string(), dict.string(), restored.string()), 0);
        EXPECT_TRUE(filesEquality(raw, restored));
    }
}

TEST(Shannon, EmptyFile)
{
    fs::path tmp = fs::temp_directory_path();
    fs::path raw = tmp / "sf_empty.bin";
    fs::path packed = tmp / "sf_empty.sf";
    fs::path dict = tmp / "sf_empty.txt";
    fs::path restored = tmp / "sf_empty_restored.bin";

    std::ofstream(raw, std::ios::binary);     // пустой
    ASSERT_EQ(encodeFile(raw.string(), packed.string(), dict.string()), 0);
    ASSERT_EQ(decodeFile(packed.string(), dict.string(), restored.string()), 0);
    EXPECT_TRUE(filesEquality(raw, restored));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
