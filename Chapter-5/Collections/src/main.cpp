#include <gtest/gtest.h>

#include <cmath>
#include <istream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

using IntGrid = vector<vector<int>>;

vector<double> readVector(istream& input) {
    vector<double> values;
    double value = 0.0;
    while (input >> value) {
        values.push_back(value);
    }
    return values;
}

double mean(const vector<double>& data) {
    if (data.empty()) {
        throw invalid_argument("mean requires at least one value");
    }

    double total = 0.0;
    for (double value : data) {
        total += value;
    }
    return total / static_cast<double>(data.size());
}

double populationStdDev(const vector<double>& data) {
    const double average = mean(data);
    double squaredDifferenceSum = 0.0;
    for (double value : data) {
        const double difference = value - average;
        squaredDifferenceSum += difference * difference;
    }
    return sqrt(squaredDifferenceSum / static_cast<double>(data.size()));
}

IntGrid fillGrid(size_t rows, size_t columns, const vector<int>& values) {
    if (rows * columns != values.size()) {
        throw invalid_argument("value count must match the grid dimensions");
    }

    IntGrid grid(rows, vector<int>(columns));
    size_t index = 0;
    for (auto& row : grid) {
        for (int& cell : row) {
            cell = values[index++];
        }
    }
    return grid;
}

bool isRectangular(const IntGrid& grid) {
    if (grid.empty() || grid.front().empty()) {
        return false;
    }
    const size_t columns = grid.front().size();
    for (const auto& row : grid) {
        if (row.size() != columns) {
            return false;
        }
    }
    return true;
}

bool isMagicSquare(const IntGrid& square) {
    if (!isRectangular(square) || square.size() != square.front().size()) {
        return false;
    }

    const size_t size = square.size();
    const int target = [&square] {
        int total = 0;
        for (int value : square.front()) {
            total += value;
        }
        return total;
    }();

    set<int> values;
    int firstDiagonal = 0;
    int secondDiagonal = 0;
    for (size_t row = 0; row < size; ++row) {
        int rowTotal = 0;
        int columnTotal = 0;
        for (size_t column = 0; column < size; ++column) {
            const int value = square[row][column];
            if (value < 1 || value > static_cast<int>(size * size)) {
                return false;
            }
            values.insert(value);
            rowTotal += value;
            columnTotal += square[column][row];
        }
        if (rowTotal != target || columnTotal != target) {
            return false;
        }
        firstDiagonal += square[row][row];
        secondDiagonal += square[row][size - row - 1];
    }

    return values.size() == size * size
        && firstDiagonal == target
        && secondDiagonal == target;
}

bool containsOneThroughNine(const set<int>& values) {
    static const set<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    return values == expected;
}

bool checkSudokuSolution(const IntGrid& puzzle) {
    if (!isRectangular(puzzle) || puzzle.size() != 9 || puzzle.front().size() != 9) {
        return false;
    }

    for (size_t index = 0; index < 9; ++index) {
        set<int> rowValues;
        set<int> columnValues;
        for (size_t offset = 0; offset < 9; ++offset) {
            rowValues.insert(puzzle[index][offset]);
            columnValues.insert(puzzle[offset][index]);
        }
        if (!containsOneThroughNine(rowValues) || !containsOneThroughNine(columnValues)) {
            return false;
        }
    }

    for (size_t blockRow = 0; blockRow < 9; blockRow += 3) {
        for (size_t blockColumn = 0; blockColumn < 9; blockColumn += 3) {
            set<int> blockValues;
            for (size_t row = blockRow; row < blockRow + 3; ++row) {
                for (size_t column = blockColumn; column < blockColumn + 3; ++column) {
                    blockValues.insert(puzzle[row][column]);
                }
            }
            if (!containsOneThroughNine(blockValues)) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
queue<T> reverseQueue(queue<T> input) {
    stack<T> reversed;
    while (!input.empty()) {
        reversed.push(input.front());
        input.pop();
    }
    while (!reversed.empty()) {
        input.push(reversed.top());
        reversed.pop();
    }
    return input;
}

bool isBalanced(const string& expression) {
    stack<char> openBrackets;
    for (char character : expression) {
        if (character == '(' || character == '{' || character == '[') {
            openBrackets.push(character);
            continue;
        }
        if (character != ')' && character != '}' && character != ']') {
            continue;
        }
        if (openBrackets.empty()) {
            return false;
        }

        const char open = openBrackets.top();
        openBrackets.pop();
        if ((character == ')' && open != '(')
            || (character == '}' && open != '{')
            || (character == ']' && open != '[')) {
            return false;
        }
    }
    return openBrackets.empty();
}

TEST(SequentialCollections, ReadMeanAndStandardDeviation) {
    istringstream input("2 4 4 4 5 5 7 9");
    const vector<double> values = readVector(input);
    EXPECT_DOUBLE_EQ(mean(values), 5.0);
    EXPECT_DOUBLE_EQ(populationStdDev(values), 2.0);
}

TEST(GridExercises, FillAndMagicSquare) {
    const IntGrid filled = fillGrid(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    EXPECT_EQ(filled, (IntGrid{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));

    EXPECT_TRUE(isMagicSquare({{8, 1, 6}, {3, 5, 7}, {4, 9, 2}}));
    EXPECT_FALSE(isMagicSquare({{8, 1, 6}, {3, 5, 7}, {4, 8, 3}}));
}

TEST(GridExercises, SudokuValidation) {
    const IntGrid valid{
        {3, 9, 2, 4, 6, 5, 8, 1, 7},
        {7, 4, 1, 8, 9, 3, 6, 2, 5},
        {6, 8, 5, 2, 7, 1, 4, 3, 9},
        {2, 5, 4, 1, 3, 8, 7, 9, 6},
        {8, 3, 9, 6, 2, 7, 1, 5, 4},
        {1, 7, 6, 9, 5, 4, 2, 8, 3},
        {9, 6, 7, 5, 8, 2, 3, 4, 1},
        {4, 2, 3, 7, 1, 9, 5, 6, 8},
        {5, 1, 8, 3, 4, 6, 9, 7, 2},
    };
    EXPECT_TRUE(checkSudokuSolution(valid));

    IntGrid invalid = valid;
    invalid[0][0] = invalid[0][1];
    EXPECT_FALSE(checkSudokuSolution(invalid));
}

TEST(StackQueueExercises, ReverseAndBalance) {
    queue<string> words;
    words.push("first");
    words.push("second");
    words.push("third");
    words = reverseQueue(words);
    EXPECT_EQ(words.front(), "third");
    words.pop();
    EXPECT_EQ(words.front(), "second");

    EXPECT_TRUE(isBalanced("{ s = 2 * (a[2] + 3); x = (1 + (2)); }"));
    EXPECT_FALSE(isBalanced("([)]"));
    EXPECT_FALSE(isBalanced("(("));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
