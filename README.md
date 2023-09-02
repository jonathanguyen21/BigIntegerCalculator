# Info
* Jonathan Nguyen, jnguy330
* 2023 Spring CSE101 PA6
* README.md
* Lists and gives brief description of each file in pa6

## List.cpp
Implementation file for List ADT.
Contains all functions in the List ADT.

## List.h
Header file for List ADT

## ListTest.cpp
Test client for List ADT.
Tests all functions in the List ADT for correct usability.

How to build and run ListTest.cpp:
1. Open Terminal
2. Go into the same directory as ListTest.cpp
3. Compile using Makefile by entering `make ListTest` into terminal
4. Run program with `./ListTest`

## BigInteger.cpp
Implementation file for BigInteger ADT.
Contains all functions in the BigInteger ADT.

## BigInteger.h
Header file for BigInteger ADT

## BigIntegerTest.cpp
Test client for BigInteger ADT.
Tests all functions in the BigInteger ADT for correct usability.

How to build and run BigIntegerTest.cpp:
1. Open Terminal
2. Go into the same directory as BigIntegerTest.cpp
3. Compile using Makefile by entering `make BigIntegerTest` into terminal
4. Run program with `./BigIntegerTest`

## Arithmetic.cpp
Makes use of List ADT and BigInteger ADT to do arithmetic calculations on arbitrarily large signed integers given in an input file

How to build and run Arithmetic.cpp:
1. Open Terminal
2. Go into the same directory as Arithmetic.cpp
3. Compile using Makefile by entering `make Arithmetic` into terminal
4. Run program with `./Arithmetic <input> <output>`

## Makefile
Compiles files with certain flags in pa6

- `make`                   compiles Arithmetic
- `make ListTest`          compiles ListTest
- `make BigIntegerTest`    compiles BigIntegerTest
- `make clean`             removes all binaries