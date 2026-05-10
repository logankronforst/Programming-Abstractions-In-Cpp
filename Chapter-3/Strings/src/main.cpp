#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <array>
#include <chrono>
#include <cmath>
using namespace std;



/*
2.  The strlib.h function exports a function trim(str) that returns a new
    string formed by removing all whitespace characters from str. Write the
    corresponding implementation.
*/
string trim(string& str) {
    string res = str; 
    for (int i = 0; i < res.length(); i++) {
        if (res[i] == ' ') {
            res.erase(i, 1);
        }
    }
    return res; 
}

/*
1.  Implement the function endsWith(str, suffix), which returns true if
    str ends with suffix. Like its startsWith counterpart, the endsWith
    function should allow the second argument to be either a string or a 
    character.
*/
bool endsWith(string& str, string& suffix) {
    if (str.length() < suffix.length()) {return false;}
    int offset = str.length() - 1; 
    for (int i = suffix.length() - 1; i >= 0; i--) {
        if (str[offset] != suffix[i]) {return false;}
        offset--;
    }
    return true; 
}

bool startsWith(string& str, string& prefix) {
    if (str.length() < prefix.length()) {return false;}
    for (int i = 0; i < prefix.length(); i++){
        if (str[i] != prefix[i]) {return false;}
    }
    return true; 
}

bool isPalindrome(string str) {
    int n = str.length();
    for (int i = 0; i < n / 2; i++) {
        if (str[n - i - 1] != str[i]) {return false;}
    }
    return true; 
}

TEST(endsWith, simpleTest) {
    string str{"marigold"};
    string suffix{"gold"};
    EXPECT_TRUE(endsWith(str, suffix));
}

TEST(endsWith, simpleCase) {
    string str{"marigold"};
    string suffix{"goldd"};
    EXPECT_FALSE(endsWith(str, suffix));
}

TEST(endsWith, simple) {
    string str{"marigold"};
    string suffix{"ggold"};
    EXPECT_FALSE(endsWith(str, suffix));
}

TEST(trim, simpleTest) {
    string str{"Hello, world"}; 
    string trimmed{"Hello,world"};
    string res = trim(str);
    EXPECT_EQ(res, trimmed);
}

TEST(trim, simpleCase) {
    string str{" mo a n a "};
    string trimmed{"moana"};
    string res = trim(str);
    EXPECT_EQ(res, trimmed);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    string str{"mentos"};
    string suffix{"tos"};
    endsWith(str, suffix);
    
    return RUN_ALL_TESTS();
}