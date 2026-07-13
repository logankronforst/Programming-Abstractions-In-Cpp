# Programming Abstractions in C++

Original solutions to end-of-chapter exercises from Eric S. Roberts' *Programming Abstractions in C++*. Each chapter is a standalone CMake project with a GoogleTest suite.

## Exercise Coverage

| Chapter | Module | Topics |
| --- | --- | --- |
| 1 | `Chapter-1/Cpp-Overview` | conversions, iterative and recursive summation, averages, digit reversal, prime factorization, hailstone sequences, and numerical approximations of pi |
| 2 | `Chapter-2/Functions-Libraries` | permutations, Easter-date calculation, successive approximation, primes, perfect numbers, wind chill, and rounding |
| 3 | `Chapter-3/Strings` | prefixes and suffixes, whitespace removal, substrings, capitalization, Scrabble scoring, and palindromes |
| 5 | `Chapter-5/Collections` | vectors and streams, descriptive statistics, grids, magic squares, Sudoku validation, queues, stacks, and delimiter balancing |
| 7 | `Chapter-7/Recursion` | recursive arithmetic, sequences, Euclid's algorithm, digit sums, digital roots, and Pascal's triangle |
| 8 | `Chapter-8/Recursive-Strategies` | Towers of Hanoi, permutations, and subset-sum search |

## Build and Test

From any chapter module:

```sh
cmake --preset default
cmake --build --preset default
ctest --test-dir build --output-on-failure
```

GoogleTest is declared through CMake `FetchContent` and downloaded during the first configure.

## Academic Integrity

This repository contains only self-directed textbook exercise work. Stanford course assignments, assignment starter code, lecture materials, and section materials are intentionally excluded.
