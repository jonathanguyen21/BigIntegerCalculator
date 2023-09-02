/*********************************************************************************
* Arithmetic.cpp
* Makes use of List ADT and BigInteger ADT to do arithmetic calculations
* on arbitrarily large signed integers given in an input file
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include<iomanip>
#include<fstream>
#include <chrono>
#include"BigInteger.h"

int main(int argc, char *argv[]) {
    if ( argc!=3 ) {
        std::string errorMessage = std::string("Usage: ")+argv[0]+std::string(" <input file> <output file>");
        throw std::invalid_argument(errorMessage);
    }

    // opening and reading in from input file
    std::fstream input;
    input.open(argv[1], std::ios::in);
    if (!input) {
        throw std::runtime_error("Could not open input file");
    }
    std::string parsedLine;
    getline(input, parsedLine);
    BigInteger A = BigInteger(parsedLine);
    getline(input, parsedLine);
    getline(input, parsedLine);
    BigInteger B = BigInteger(parsedLine);

    // creating output file
    std::fstream output;
    output.open(argv[2], std::ios::out);
    if (!output) {
        throw std::runtime_error("Could not create output file");
    }

    BigInteger C = A+B;
    BigInteger J = A-B;
    BigInteger D = A-A;
    BigInteger E = 3*A-2*B;
    BigInteger F = A*B;
    BigInteger G = A*A;
    BigInteger H = B*B;
    BigInteger I = 9*(G*G)+16*(H*H*B);
    output << A << std::endl << std::endl;
    output << B << std::endl << std::endl;
    output << C << std::endl << std::endl;
    output << J << std::endl << std::endl;
    output << D << std::endl << std::endl;
    output << E << std::endl << std::endl;
    output << F << std::endl << std::endl;
    output << G << std::endl << std::endl;
    output << H << std::endl << std::endl;
    output << I << std::endl;

    input.close();
    output.close();
    return 0;
}
