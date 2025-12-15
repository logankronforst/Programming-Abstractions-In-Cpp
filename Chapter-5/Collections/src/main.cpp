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
#include <array>
#include <chrono>
#include <cmath>
using namespace std; 



/*
2.  Write a function

        double stddev(vector<double>& data);

    that returns the standard deviation of the data distribution

*/
long stddev(vector<long>& data) {
    long avg = mean(data);
    long sum = 0;

    for (int i = 0; i < data.size(); i++) {
        sum += powl(avg - data[i], 2);
    }
    return sqrt(sum / data.size());
}







/*
1.  
    Write a function 

        double mean(Vector<double>& data);

    that returns the mean of the vector. 
*/
long mean(vector<long>& data) {
    int n = data.size();
    double sum = 0;

    for (int i = 0; i < n; i++){
        sum+=data[i];
    }
    return sum / n;
}


/*----- Testing -----*/
TEST(testMean, simpleTest){
    vector<long> data = {10, 3, 2};
    EXPECT_EQ(mean(data), 5);
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    vector<long> data{11,2000000000,3,4,10000000,1000000000000,2000000000000};
    auto start(chrono::steady_clock::now());
    const auto m = mean(data);
    auto finish(chrono::steady_clock::now());
    const chrono::duration<double> elapsed_seconds = {finish - start};
    cout << elapsed_seconds << '\n';
    
        
    return RUN_ALL_TESTS();
}
