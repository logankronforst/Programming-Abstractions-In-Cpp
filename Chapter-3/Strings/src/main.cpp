#include <gtest/gtest.h>

#include <array>
#include <cctype>
#include <stdexcept>
#include <string>

using namespace std;

bool endsWith(const string& text, const string& suffix) {
    if (text.size() < suffix.size()) {
        return false;
    }
    return text.compare(text.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool startsWith(const string& text, const string& prefix) {
    if (text.size() < prefix.size()) {
        return false;
    }
    return text.compare(0, prefix.size(), prefix) == 0;
}

string removeWhitespace(const string& text) {
    string result;
    for (unsigned char character : text) {
        if (!isspace(character)) {
            result += static_cast<char>(character);
        }
    }
    return result;
}

string substring(const string& text, size_t position, size_t length = string::npos) {
    if (position > text.size()) {
        throw out_of_range("substring position exceeds string length");
    }
    return text.substr(position, length);
}

string capitalize(const string& text) {
    if (text.empty()) {
        return text;
    }

    string result = text;
    for (char& character : result) {
        character = static_cast<char>(tolower(static_cast<unsigned char>(character)));
    }
    result.front() = static_cast<char>(toupper(static_cast<unsigned char>(result.front())));
    return result;
}

int scrabbleScore(const string& word) {
    static constexpr array<int, 26> points{
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10,
    };

    int total = 0;
    for (unsigned char character : word) {
        const unsigned char lower = static_cast<unsigned char>(tolower(character));
        if (lower >= 'a' && lower <= 'z') {
            total += points[lower - 'a'];
        }
    }
    return total;
}

bool isPalindrome(const string& text) {
    for (size_t index = 0; index < text.size() / 2; ++index) {
        if (text[index] != text[text.size() - index - 1]) {
            return false;
        }
    }
    return true;
}

TEST(PrefixSuffix, Matching) {
    EXPECT_TRUE(endsWith("marigold", "gold"));
    EXPECT_TRUE(endsWith("Cupcakes", "cakes"));
    EXPECT_FALSE(endsWith("marigold", "goldd"));
    EXPECT_TRUE(startsWith("Programming Abstractions", "Programming"));
}

TEST(StringTransforms, WhitespaceSubstringAndCapitalization) {
    EXPECT_EQ(removeWhitespace(" trim\tme \n"), "trimme");
    EXPECT_EQ(substring("Hello, world!", 1, 4), "ello");
    EXPECT_EQ(substring("Hello", 2), "llo");
    EXPECT_THROW(substring("short", 10), out_of_range);
    EXPECT_EQ(capitalize("boolean"), "Boolean");
    EXPECT_EQ(capitalize("BOOLEAN"), "Boolean");
    EXPECT_EQ(capitalize(""), "");
}

TEST(StringAlgorithms, ScrabbleAndPalindrome) {
    EXPECT_EQ(scrabbleScore("Farm"), 9);
    EXPECT_EQ(scrabbleScore("Stanford"), 12);
    EXPECT_TRUE(isPalindrome("racecar"));
    EXPECT_FALSE(isPalindrome("recursion"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
