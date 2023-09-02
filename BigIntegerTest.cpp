/*********************************************************************************
* Jonathan Nguyen, jnguy330
* 2023 Spring CSE101 PA6
* BigIntegerTest.cpp
* Test client for BigInteger ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include<math.h>
#include"BigInteger.h"

int main () {

    // Class Constructors----------------------------------------

    // Testing List Constructor and Destructor
    BigInteger B;

    // BigInteger(long x)
    BigInteger test = BigInteger(1321312);

    // BigInteger(std::string s)
    BigInteger string = BigInteger("00000000012321312321312");

    // copy constructor
    BigInteger copy = string;

    // Access functions --------------------------------------------------------

    // sign()
    std::cout << "sign() copy sign: " <<copy.sign() << std::endl;

    // compare()
    BigInteger compare1 = BigInteger("-99999999990");
    BigInteger compare2 = BigInteger("99999999991");
    std::cout << "compare(): " << compare1.compare(compare2) << std::endl;

    // makeZero()
    test.makeZero();
    std::cout << "makeZero() sign: " << test.sign() << std::endl;
    std::cout << "makeZero() compare: " << test.compare(copy) << std::endl;

    // negate()
    copy.negate();
    std::cout << "negate() sign: " << copy.sign() << std::endl;
    copy.negate();
    std::cout << "negate() sign: " << copy.sign() << std::endl;

    // BigInteger Arithmetic operations ----------------------------------------

    // add()
    BigInteger add1 = BigInteger("434029710130888164");
    BigInteger add2 = BigInteger("089633921255113060");
    std::cout << "add(): " << add1.add(add2) << std::endl;


    // sub()
    std::cout << "sub(): " << add1.sub(add2) << std::endl;

    // mult
    BigInteger A = BigInteger("-0085449");
    BigInteger C = BigInteger("099357");
    std::cout << "mult(): " << A.mult(C) << std::endl;

    // Overriden Operators -----------------------------------------------------

    // ==
    BigInteger D = BigInteger("123456789");
    BigInteger E = BigInteger("123456789");
    bool equals = D==E;
    std::cout << "D==E: " << equals << std::endl;

    // <
    equals = D<E;
    std::cout << "D<E: " << equals << std::endl;

    // <=
    equals = D<=E;
    std::cout << "D<=E: " << equals << std::endl;

    // >
    equals = D>E;
    std::cout << "D>E: " << equals << std::endl;

    // >=
    equals = D>=E;
    std::cout << "D>=E: " << equals << std::endl;

    // +
    std::cout << "D+E: " << D+E << std::endl;

    // +=
    BigInteger F;
    F+=D;
    std::cout << "F+=D: " << F << std::endl;

    // -
    std::cout << "D-E: " << D-E << std::endl;

    // -=
    F-=D;
    std::cout << "F-=D: " << F << std::endl;

    // *
    std::cout << "D*E: " << D*E << std::endl;

    // *=
    F*=D;
    std::cout << "F*=D: " << F << std::endl;

    return 0;
}