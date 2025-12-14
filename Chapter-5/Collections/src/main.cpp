/*
Author: Logan Kronforst
Date:   09/01/2025

Description: 

This program contains solutions to the excercise problems at the end of Chapter 5, 
Collections, from the textbook Programming Abtractions in C++, by Eric S. Roberts.
The solutions are entirely my own. Each problem solution comes complete with its own
unit testing suite, using the google test framework. The google test framework is
fetched through the CMakeLists.txt, and linked to the main executable file, so
everything lives in main.cpp. This is a lean testing framework, that doesn't use
bezel. 
*/

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std; 



/*--- placeholder ---*/
TEST(CollectionsChapter, PlaceholderTest){
    vector<string> collections = {"sets", "maps", "queues"};
    EXPECT_FALSE(collections.empty());
    EXPECT_EQ(collections.front(), "sets");
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}
