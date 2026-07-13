/*
Author: Logan Kronforst
Date: 09/23/25

"Tactics without strategy is the noise before defeat"
- Sun Tzu, ~5th Century BCE
*/

#include <gtest/gtest.h>
#include <iostream>
#include <math.h>
#include <stack>
#include <map>
#include <set>
using namespace std; 








/*
3.  Rewrite the Towers of Hanoi program so that it uses an explicit stack of
    pending tasks instead of recursion. In this context, a task can be represented 
    more easily as a structure containing the number of disks to move and the 
    names of the spires used for the start, finish, and temporary repositories. At
    the beginning of the process, you push onto your stack a single task that 
*/

void moveSingleDisk(char start, char finish);

void iterativeHanoi(int n, char start, char finish, char tmp){
    stack<map<int, vector<char>>> s; 
    map<int, vector<char>> task;

    while (n > 1){
        if (!s.empty()){
            s.pop();
        }
        task = {{n - 1, {start, tmp, finish}}};
        s.push(task);
        moveSingleDisk(start, finish);
        s.pop();
        task = {{n-1, {tmp, finish, start}}};
        s.push(task);
    }
    moveSingleDisk(start, finish);
}




/*
2.  To make the operation of the program somewhat easier to explain, the
    implementation of `moveTower` in this chapter uses

            if (n == 1)

    as its simple cast test. Whenever you see a recursive program use 1 as its
    simple case, it pays to be a little skeptical; in most applications, 0 is 
    a more appropriate choice. Rewrite the Towers of Hanoi program so that the 
    `moveTower` function checks whether n is 0 instead. What happens to the 
    length of the `moveTower` implementation?
*/
void moveSingleDisk(char start, char finish);

void moveTower2(int n, char start, char finish, char tmp){
    if (n == 0){
        moveSingleDisk(start, finish);
    } else {
        moveTower2(n - 1, start, tmp, finish);
        moveSingleDisk(start, finish);
        moveTower2(n - 1, tmp, finish, start);
    }
}

/*
1.    Following the logic of the moveTower function, write a recursive function
      `countHanoiMoves(n)` that computes the number of moves required to solve
      the Towers of Hanoi puzzle for n disks. 
                __  
               | 
               | 1  if n = 1
        T(n) = |
               | 2T(n - 1) + 1 otherwise
               |__
*/               
int countHanoiMoves(int n){
    if (n == 1) return 1; 
    return 2 * countHanoiMoves(n - 1) + 1; 
}

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

/*--- countHanoiMoves Testing ---*/
TEST(countHanoiMoves, Testing){
    int n = 7; 
    EXPECT_EQ(countHanoiMoves(n), pow(2, n) - 1); 
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
