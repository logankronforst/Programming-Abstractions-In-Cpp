#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

long long permutations(int n, int r) {
    if (n < 0 || r < 0 || r > n) {
        throw invalid_argument("permutations require 0 <= r <= n");
    }

    long long result = 1;
    for (int value = n; value > n - r; --value) {
        result *= value;
    }
    return result;
}

struct CalendarDate {
    string month;
    int day;

    bool operator==(const CalendarDate&) const = default;
};

CalendarDate findEaster(int year) {
    if (year < 1583) {
        throw invalid_argument("Gregorian Easter requires a year of 1583 or later");
    }

    const int a = year % 19;
    const int b = year / 100;
    const int c = year % 100;
    const int d = b / 4;
    const int e = b % 4;
    const int f = (b + 8) / 25;
    const int g = (b - f + 1) / 3;
    const int h = (19 * a + b - d - g + 15) % 30;
    const int i = c / 4;
    const int k = c % 4;
    const int l = (32 + 2 * e + 2 * i - h - k) % 7;
    const int m = (a + 11 * h + 22 * l) / 451;
    const int month = (h + l - 7 * m + 114) / 31;
    const int day = (h + l - 7 * m + 114) % 31 + 1;
    return {month == 3 ? "March" : "April", day};
}

double successiveApproximation(double number) {
    if (number < 0.0) {
        throw invalid_argument("square root is undefined for negative values");
    }
    if (number == 0.0) {
        return 0.0;
    }

    double guess = max(1.0, number / 2.0);
    for (int iteration = 0; iteration < 1000; ++iteration) {
        const double next = (guess + number / guess) / 2.0;
        if (abs(next - guess) <= 1e-12 * max(1.0, next)) {
            return next;
        }
        guess = next;
    }
    throw runtime_error("successive approximation did not converge");
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

bool isPerfect(int number) {
    if (number < 2) {
        return false;
    }

    int divisorSum = 1;
    for (int divisor = 2; divisor <= number / divisor; ++divisor) {
        if (number % divisor != 0) {
            continue;
        }
        divisorSum += divisor;
        if (divisor != number / divisor) {
            divisorSum += number / divisor;
        }
    }
    return divisorSum == number;
}

vector<int> perfectNumbersUpTo(int limit) {
    vector<int> result;
    for (int number = 2; number <= limit; ++number) {
        if (isPerfect(number)) {
            result.push_back(number);
        }
    }
    return result;
}

double windChill(double temperature, double windSpeed) {
    if (temperature > 40.0) {
        throw invalid_argument("wind chill is undefined above 40 degrees Fahrenheit");
    }
    if (windSpeed < 0.0) {
        throw invalid_argument("wind speed cannot be negative");
    }
    if (windSpeed == 0.0) {
        return temperature;
    }

    const double velocityFactor = pow(windSpeed, 0.16);
    return 35.74 + 0.6215 * temperature - 35.75 * velocityFactor
        + 0.4275 * temperature * velocityFactor;
}

int roundToNearestInt(double number) {
    return static_cast<int>(number >= 0.0 ? number + 0.5 : number - 0.5);
}

TEST(Combinatorics, Permutations) {
    EXPECT_EQ(permutations(8, 3), 336);
    EXPECT_EQ(permutations(5, 0), 1);
    EXPECT_THROW(permutations(3, 4), invalid_argument);
}

TEST(Calendar, Easter) {
    EXPECT_EQ(findEaster(2025), (CalendarDate{"April", 20}));
    EXPECT_EQ(findEaster(2026), (CalendarDate{"April", 5}));
}

TEST(NumericalMethods, SuccessiveApproximation) {
    EXPECT_NEAR(successiveApproximation(2.0), sqrt(2.0), 1e-12);
    EXPECT_DOUBLE_EQ(successiveApproximation(0.0), 0.0);
}

TEST(NumberTheory, PrimesAndPerfectNumbers) {
    EXPECT_TRUE(isPrime(97));
    EXPECT_FALSE(isPrime(91));
    EXPECT_TRUE(isPerfect(6));
    EXPECT_FALSE(isPerfect(29));
    EXPECT_EQ(perfectNumbersUpTo(10000), (vector<int>{6, 28, 496, 8128}));
}

TEST(Utilities, WindChillAndRounding) {
    EXPECT_DOUBLE_EQ(windChill(30.0, 0.0), 30.0);
    EXPECT_NEAR(windChill(30.0, 10.0), 21.2482932556, 1e-9);
    EXPECT_THROW(windChill(41.0, 10.0), invalid_argument);
    EXPECT_EQ(roundToNearestInt(4.49), 4);
    EXPECT_EQ(roundToNearestInt(4.5), 5);
    EXPECT_EQ(roundToNearestInt(-4.5), -5);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
