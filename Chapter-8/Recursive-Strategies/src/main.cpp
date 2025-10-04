/*
Author: Logan Kronforst
Date: 09/23/25

"Tactics without strategy is the noise before defeat"
- Sun Tzu, ~5th Century BCE

*/

#include <gtest/gtest.h>
#include <iostream>
#include <math.h>
#include <set>
using namespace std; 



set<string> generatePermutations(string str){
    set<string> result = {};
    if (str == ""){
        result.insert("");
    }
    for (int i = 0; i < str.length(); i++){
        char ch = str[i];
        string rest = str.substr(0, i) + str.substr(i + 1);
        for (string s: generatePermutations(rest)){
            result.insert(ch + s);
        }
    }
    return result; 
}

bool subsetSumExists(set<int>& s, int target){
    if (s.empty()){
        return target == 0;
    }
    auto firstIter = s.begin();
    int element = *firstIter; 
    
    set<int> rest = s;
    rest.erase(rest.begin());

    return subsetSumExists(rest, target)
        || subsetSumExists(rest, target - element); 
}

void moveSingleDisk(char start, char finish);

void moveTower(int n, char start, char finish, char tmp){
    if (n == 1){
        moveSingleDisk(start, finish);
    } else {
        moveTower(n - 1, start, tmp, finish);
        moveSingleDisk(start, finish);
        moveTower(n - 1, tmp, finish, start);
    }
}

void moveSingleDisk(char start, char finish){
    cout << start << "-->" << finish << endl;
}

/*--- subsetSumExists Testing Suite ----*/
TEST(subsetSumExists, Testing){
    set<int> s = {-2 ,1, 3, 8};
    EXPECT_TRUE(subsetSumExists(s, 7));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    moveTower(2, 'A', 'B', 'C');

    for (string s: generatePermutations("ABCDE")){
        cout << "  \"" << s << "\"" << endl;
    }

    return RUN_ALL_TESTS();
}
