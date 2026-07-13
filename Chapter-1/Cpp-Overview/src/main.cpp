#include <gtest/gtest.h>

#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

double convertCelsius(double celsius) {
    return (9.0 / 5.0 * celsius) + 32.0;
}

pair<int, double> convertMeters(double meters) {
    if (meters < 0.0) {
        throw invalid_argument("distance cannot be negative");
    }

    const double totalInches = meters / 0.0254;
    const int feet = static_cast<int>(totalInches / 12.0);
    return {feet, fmod(totalInches, 12.0)};
}

int sumNumbers(int number) {
    if (number < 0) {
        throw invalid_argument("number must be nonnegative");
    }

    int result = 0;
    for (int value = 1; value <= number; ++value) {
        result += value;
    }
    return result;
}

int recursiveSum(int number) {
    if (number < 0) {
        throw invalid_argument("number must be nonnegative");
    }
    if (number <= 1) {
        return number;
    }
    return number + recursiveSum(number - 1);
}

double averageScore(const vector<double>& scores) {
    if (scores.empty()) {
        throw invalid_argument("at least one score is required");
    }

    double total = 0.0;
    for (double score : scores) {
        total += score;
    }
    return total / static_cast<double>(scores.size());
}

int reverseInteger(int number) {
    const int sign = number < 0 ? -1 : 1;
    number = abs(number);

    int reversed = 0;
    while (number > 0) {
        reversed = reversed * 10 + number % 10;
        number /= 10;
    }
    return sign * reversed;
}

bool isPrime(int number) {
    if (number < 2) {
        return false;
    }
    for (int divisor = 2; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            return false;
        }
    }
    return true;
}

vector<int> primeFactorization(int number) {
    if (number < 2) {
        throw invalid_argument("number must be at least two");
    }

    vector<int> factors;
    for (int divisor = 2; divisor <= number / divisor; ++divisor) {
        while (number % divisor == 0) {
            factors.push_back(divisor);
            number /= divisor;
        }
    }
    if (number > 1) {
        factors.push_back(number);
    }
    return factors;
}

vector<long long> hailstoneSequence(long long number) {
    if (number <= 0) {
        throw invalid_argument("starting value must be positive");
    }

    vector<long long> sequence{number};
    while (number != 1) {
        number = number % 2 == 0 ? number / 2 : number * 3 + 1;
        sequence.push_back(number);
    }
    return sequence;
}

double approximatePiLeibniz(int terms) {
    if (terms <= 0) {
        throw invalid_argument("term count must be positive");
    }

    double quarterPi = 0.0;
    for (int index = 0; index < terms; ++index) {
        const double term = 1.0 / static_cast<double>(2 * index + 1);
        quarterPi += index % 2 == 0 ? term : -term;
    }
    return 4.0 * quarterPi;
}

double approximateQuarterCircleArea(int rectangles, double radius = 2.0) {
    if (rectangles <= 0 || radius <= 0.0) {
        throw invalid_argument("rectangle count and radius must be positive");
    }

    const double width = radius / static_cast<double>(rectangles);
    double area = 0.0;
    for (int index = 0; index < rectangles; ++index) {
        const double midpoint = (static_cast<double>(index) + 0.5) * width;
        const double height = sqrt(radius * radius - midpoint * midpoint);
        area += height * width;
    }
    return area;
}

TEST(Conversions, CelsiusAndMeters) {
    EXPECT_DOUBLE_EQ(convertCelsius(32.0), 89.6);
    const auto [feet, inches] = convertMeters(1.0);
    EXPECT_EQ(feet, 3);
    EXPECT_NEAR(inches, 3.3700787402, 1e-9);
}

TEST(Summation, IterativeAndRecursive) {
    EXPECT_EQ(sumNumbers(100), 5050);
    EXPECT_EQ(recursiveSum(100), 5050);
}

TEST(NumberExercises, AverageReverseAndPrimeFactors) {
    EXPECT_DOUBLE_EQ(averageScore({90.0, 80.0, 70.0}), 80.0);
    EXPECT_EQ(reverseInteger(123456789), 987654321);
    EXPECT_EQ(reverseInteger(-120), -21);
    EXPECT_TRUE(isPrime(97));
    EXPECT_FALSE(isPrime(91));
    EXPECT_EQ(primeFactorization(60), (vector<int>{2, 2, 3, 5}));
}

TEST(Sequences, Hailstone) {
    EXPECT_EQ(hailstoneSequence(5), (vector<long long>{5, 16, 8, 4, 2, 1}));
}

TEST(Approximations, PiAndQuarterCircle) {
    const double pi = acos(-1.0);
    EXPECT_NEAR(approximatePiLeibniz(200000), pi, 1e-5);
    EXPECT_NEAR(approximateQuarterCircleArea(10000), pi, 1e-5);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
