#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

using namespace std;

/*
1.  Write a program that reads in a temperature in degrees Celsius and displays the
    corresponding temperature in degrees Fahrenheit. The conversion formula is

            F = 9 / 5 * C + 32
*/

double convert_celsius(double C) {
   return (9.0 / 5.0 * C) + 32.0; 
}

/*
2.  Write a program that converts a distance in meters to the corresponding English 
    distance in feet and inches. The converstion factors you need are

                1 inch = 0.0254 meters
                1 foot = 12 inches
*/

void convert_meters(double meters) {
    double inches = meters / 0.0254; 
    double feet = inches / 12; 
    cout << static_cast<int>(feet) << " feet " << fmod(inches, 12.0) << " inches\n";
}

/*
3.  As mathematical historians have told the story, the German Mathematician Carl
    Friedrich Gauss (1777-1855) began to show his mathematical talent at a very
    early age. When he was in elementary school, Gauss was asked by his teacher
    to compute the sum of the numbers between 1 and 100. Gauss is said to have 
    given the answer instantly: 5050. Write a program that computes the answer to 
    the question Gauss's teacher posed. 
*/

int sum_numbers(int num) {
    int result = 0; 
    for (int i = 1; i <= num; i++) {
        result += i; 
    }
    return result; 
}
/*         __
           |
n          |    1              if n <= 1
sum(n) =   |
i = 0      |    n + f(n - 1)   else
           |__
*/          

int recursive_sum(int num) {
    if (num <= 1) {return num;}
    return num + recursive_sum(num - 1);
}


/**********************************TESTING **********************************/
TEST(SimpleTest, testCelsius) {
    double res = 89.6;
    EXPECT_EQ(convert_celsius(32.0), res);
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    convert_meters(1.0);
    cout << sum_numbers(100) << "\n";
    cout << recursive_sum(100) << "\n";
    
    return RUN_ALL_TESTS();
}
