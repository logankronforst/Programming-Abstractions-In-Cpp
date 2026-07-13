/*
Author: Logan Kronforst
Date:   09/15/2025

Description: 

This program contains solutions to the excercise problems at the end of Chapter 7, 
Introduction to Recursion, from the textbook Programming Abtractions in C++, by
Eric S. Roberts. The solutions are entirely my own. Each problem solution comes
complete with its own unit testing suite, using the google test framework. The
google test framework is fetched through the CMakeLists.txt, and linked to the main 
executable file, so everything lives in main.cpp. This is a lean testing framework,
that doesn't use bezel. 
*/

#include <iostream>
#include <math.h>
#include <gtest/gtest.h>
using namespace std; 

/*
9.  As you know from Chapter 2, the mathematical combinations function c(n, k) is
    usually defined in terms of factorials, as follows:

              c(n, k) = n! / k! x (n - k)! 

    The values of c(n, k) can also be arranged geometrically to form a triangle in
    which n increases as you move down the triangle and k increases as you move 
    from left to right. THe resulting structure, which is called Pascal's Triangle
    after the French mathematician Blaise Pascal, is arranged like this:

                                        c(0, 0) 

                                   c(1, 0)    c(1, 1)

                             c(2, 0)    c(2, 1)    c(2, 2) 

                        c(3, 0)   c(3, 1)     c(3, 2)   c(3, 3)

                  c(4, 0)    c(4, 1)    c(4, 2)    c(4, 3)    c(4, 4)

    Pascal's Triangle has the interesting property that every entry is the sum of the
    two entries above it, except along the left and right edges, where the values are
    always 1. Consider for example, the circled entry in the follwing display of 
    Pascal's Triangle: 
    
                                          1
                                        1   1
                                      1   2   1
                                    1   3   3   1
                                  1   4   6   4   1
                                1   5  10   10  5   1
                              1   6 (15)  20  15  6   1  
                            1   7  21  35   35  21  7   1  

    This entry, which corresponds to c(6, 2) is the sum of the two entries-5 and
    10-that appear above it to either side. Use this relationshop between entries in
    Pascal's Triangle to write a recursive implementation of the c(n, k) function
    that uses no loops, no multiplication, and no calls to `fact`. 
*/
int c(int n, int k){
    if (n == k || k == 0) return 1; 
    return c(n - 1, k - 1) + c(n - 1, k);
}

/*
8.  The digital root of an integer n is defined as the result of summing the digits 
    repeatedly until only a single digit remains. For example, the digital root of
    1729 can be calulated using the following steps:

             Step 1:    1 + 7 + 2 + 9 --> 19
             Step 2:    1 + 9         --> 10
             Step 3:    1 + 0         -->  1
             
    Because the total at the end of step 3 is the single digit 1, that value is the
    digital root. 

        Write a function `digitalRoot(n)` that returns the digital root of its
    argument. Although it is easy to implement digitalRoot using the digitSum
    function from exercise 7 and a `while` loop, part of the challenge of this
    problem is to write the function recursively without using any explicit 
    loop constructs. 
*/
int digitSum(int n);

int digitalRootIterative(int n){
    
    while (n >= 10){
        n = digitSum(n); 
    }
    return n; 
}

int digitalRoot(int n){
    if (n < 10) return n; 
    n = digitalRoot(digitSum(n)); 
    return n; 
}

/*
7.  Write a recursive function `digitSum(n)` that takes a nonnegative integer and
    returns the sum of its digits. For example, calling `digitSum(1729)` should 
    return 1 + 7 + 2 + 9, which is 19. 

        The recursive implementation of `digitSum` depends on the fact that it is
    very easy to break an integer into two components using division by 10. 
    For example, given the integer 1729, you can divide it into two pieces as 
    follows:

                                        1729
                                       /    \
                                     172     9
                                     / \    
                                   17   2
                                  /  \
                                 1    7  

    Each of the resulting integers is strictly smaller than the original and thus 
    represents a simpler case. 
*/
int digitSum(int n){
    /*      __
           |  
           |  n                  n < 10
    f(n) = | 
           |  n % 10 + f(n / 10) otherwise
           |__ 
           
    
    */
    if (n < 10) return n;
    return n % 10 + digitSum(n / 10);
}

/*
6.	Write a programming abstraction that counts the recursive calls 
	to a fibbonaci and additive sequence. 
*/
class countRecursive{
    public:
        int countFib = 0;
        int countAdditive = 0; 

        int fib(int n){
            countFib++;
            if (n < 2) return n; 
            return fib(n - 1) + fib(n - 2);
        }		

        int additiveSequence(int n, int t0, int t1){
            countAdditive++;
            if (n == 0) return t0; 
            if (n == 1) return t1; 
            return additiveSequence(n - 1, t1, t0 + t1); 
        }

        int additiveSequence(int n){
            countAdditive++;
            return additiveSequence(n, 0, 1);
        }

        int getFibCount(){
            return countFib;
        }

        int getAdditiveCount(){
            return countAdditive;
        }

        void printRecursiveCalls(){
            cout << left << setw(4) << "n"
                 << setw(10) << "fib"
                 << setw(10) << "additive" << endl;
            cout << string(24, '-') << endl;

            for (int i = 0; i <= 12; i++){
                fib(i);
                additiveSequence(i);
                cout << left << setw(4) << i
                     << setw(10) << getFibCount()
                     << setw(10) << getAdditiveCount() << endl;
                countFib = 0;
                countAdditive = 0;

            }
        }
};

/*
5.  Write an interative implementation of the function `fib(n)`

        int fib(n){
            if (n < 2) return n;
            return fib(n - 1) + fib(n - 2); 
        }
*/
int fib(int n){
    if (n == 1) return 1; 
    int *dp = new int[n + 1];
    dp[1] = 1; 
    dp[2] = 2;
    for (int i = 3; i <= n; i++){
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n]; 
}

/*
4.  The `greatest common divisor` (often abbreviated to gcd) of two nonnegative
    integers is the largest integer that divides evenly into both. in the third 
    century BCE, the Greek mathematician Euclid discoevered that the greatest 
    common divisor of x and y can always be computed as follows:

        - If x is evenly divisible by y then y is the greatest common divisor.

        - Otherwise, the greatest common divisor of x and y is always equal to the
        greatest common divisor of y and the remainder of x divided by y. 

    Use Euclid's insight to write a recursive function `gcd(x, y)` that computes 
    the greatest common divisor of x and y.
*/
long long gcd(long long x, long long y){
    if (x % y == 0) return y; 
    return gcd(y, x % y);
}

/*
3.  In the 18th century, the astronomer Johann Daniel Titius proposed a rule, later
    recorded by Johann Elert Bode, for calculating the distance from the sun to
    each of the planets known at the time. To apply that rule, which is now known 
    as the `Titius-Bode Law`, you begin by writing down the sequence 

            b_1 = 1  b_2 = 3  b_3 = 6  b_4 = 12  b_5 = 24  b_6 = 48 . . .

    where each subsequent element in the sequence is twice the preceding one. It 
    turns out that an approximate distance to the ith plaent can be computed from
    this series by applying the formula

                            d_i = (4 + b_i) / 10

    The distance d_i is expressed in `astronomical units` (AU), which correpond to
    the average distance from the earth to the sun (approximately 93,000000 miles.)
    Except for a disconcerting gap between Mars and Jupite, the Titius-Bode law gives 
    reasonable apporoximations for the distances to the seven planets known at the 
    time: 

                            Mercury  0.5 AU
                            Venus    0.7 AU
                            Earth    1.0 AU
                            Mars     1.6 AU
                            ?        2.8 AU
                            Jupiter  5.2 AU
                            Saturn  10.0 AU
                            Uranus  19.6 AU

    Write a recursive function `getTitiusBodeDistance(k)` that calculates
    the expected distance between the sun and the kth planet, numering 
    outward from Mercury starting with 1. 
*/
int b(int i){
    if (i < 2) return 1;
    else if (i == 2) return 3; 
    return 2 * b(i - 1); 
}

double getTitiusBodeDistance(int k){
    if (k == 1) return (4.0 + k) / 10.0;
    return (4.0 + b(k)) / 10.0; 
}

/*
2.  Unlike many programming languages, C++ does not include a predifined 
    operator that raises a number to a power. As a partial remedy for this
    deficiency, write a recursive implementation of a function

                int raiseToPower(int n, int k)
   
    that calculates n^k. The recursive insight that you need to solve this problem is
    the mathematical property that 
               ___  
              | 
              |  1               if k is 0
        n^k = | 
              |  n * n ^ (k - 1) otherwise
              |___ 
*/             
int raiseToPower(int n, int k){
    if (k == 0) return 1; 
    return n * raiseToPower(n, k - 1); 
}

/*
1.  Spherical objects, such as cannonballs, can be stacked to form a pyramid with
    one cannonball at the top, sitting on top of a square composed of four 
    cannonballs, sitting on top of a square composed of nine cannonballs, and so 
    forth. Write a recursive function `cannonball` that takes as its argument the 
    height of the pyramid and returns the number of cannonballs it contains. Your
    function must operate recursively and must not use any iterative constructs,
    such as `while` or `for`. 
*/
int cannonBall(int k){
    if (k <= 1) return k; 
    return k * k + cannonBall(k - 1);
}

/*--- cannonBall Testing ---*/
TEST(CannonBallTest, BaseCases) {
    EXPECT_EQ(cannonBall(0), 0);  // 0 blocks
    EXPECT_EQ(cannonBall(1), 1);  // 1 block
}

TEST(CannonBallTest, smallInputs){
    EXPECT_EQ(cannonBall(2), 5);
    EXPECT_EQ(cannonBall(3), 14);
    EXPECT_EQ(cannonBall(4), 30);
}

/*--- raiseToPower Testing ---*/
TEST(raiseToPower, BaseCase){
    EXPECT_EQ(raiseToPower(1, 0), 1);
    EXPECT_EQ(raiseToPower(0, 1), 0);
}

TEST(raiseToPower, smallInputs){
    EXPECT_EQ(raiseToPower(3, 2), 9);
    EXPECT_EQ(raiseToPower(4, 2), 16);
    EXPECT_EQ(raiseToPower(10, 2), 100); 
    EXPECT_EQ(raiseToPower(8, 4), 4096);  
}

/*--- getTitiusBodeDistance Testing ---*/
TEST(getTitiusBodeDistance, sevenPlanets){
    EXPECT_EQ(getTitiusBodeDistance(1), 0.5);
    EXPECT_EQ(getTitiusBodeDistance(2), 0.7);
    EXPECT_EQ(getTitiusBodeDistance(3), 1.0);
    EXPECT_EQ(getTitiusBodeDistance(4), 1.6);
    EXPECT_EQ(getTitiusBodeDistance(5), 2.8);
    EXPECT_EQ(getTitiusBodeDistance(6), 5.2);
    EXPECT_EQ(getTitiusBodeDistance(7), 10.0);
    EXPECT_EQ(getTitiusBodeDistance(8), 19.6);
}

/*--- gcd Testing ---*/
TEST(gcd, smallInputs){
    EXPECT_EQ(gcd(1, 2), 1);
    EXPECT_EQ(gcd(2, 10), 2);
    EXPECT_EQ(gcd(15, 30), 15); 
}

TEST(gcd, largeInputs){
    EXPECT_EQ(gcd(50, 422), 2);
    EXPECT_EQ(gcd(9876543210LL, 1234567890LL), 90);
    EXPECT_EQ(gcd(1LL << 40, 1LL << 35), 1LL << 35);
}

/*--- digitSum Testing ---*/
TEST(digitSum, simpleTest){
    EXPECT_EQ(digitSum(1729), 19); 
    EXPECT_EQ(digitSum(1234), 10);
    EXPECT_EQ(digitSum(80085), 21);
}

/*--- digitalRoot Testing ---*/
TEST(digitalRoot, simpleTest){
    EXPECT_EQ(digitalRoot(1729), 1); 
    EXPECT_EQ(digitalRoot(1234), 1); 
    EXPECT_EQ(digitalRoot(80085), 3); 

}

/*--- combinatorial Testing ---*/
TEST(nChooseK, simpleTest){
    EXPECT_EQ(c(6, 2), 15);
    EXPECT_EQ(c(10, 4), 210);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    countRecursive count;
    count.printRecursiveCalls(); 
    
    return RUN_ALL_TESTS();
}
