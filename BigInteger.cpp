/*********************************************************************************
* BigInteger.cpp
* Implementation file for BigInteger ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<cctype>
#include<stdexcept>
#include<math.h>
#include"BigInteger.h"

#define power 9
#define base (long)pow(10,power)

// Class Constructors & Destructors -------------------------------------------
// BigInteger()
// Constructor that creates a new BigInteger in the zero state:
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x) {
    if ( x > 0 ) {
        signum = 1;
    }
    else if ( x < 0 ) {
        signum = -1;
    }
    else {
        signum = 0;
        return;
    }
    long quotient = x;
    long remainder;
    while (quotient!=0) {
        remainder = quotient % base;
        quotient = quotient / base;
        digits.insertAfter(remainder);
    }
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    int len = s.length();
    if ( len == 0 ) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    std::size_t found = s.find_first_not_of("+-0123456789");
    if ( found!=std::string::npos || s.compare("+")==0 || s.compare("-")==0) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }

    // setting signum
    if (s.find_first_of("-")!=std::string::npos) {
        signum = -1;
    }
    else if ( s.find_first_of("123456789") != std::string::npos ) {
        signum = 1;
    }
    if (s.find_first_of("123456789") == std::string::npos) {
        signum = 0;
        return;
    }
    // iterating backwards through string
    int increment = power;
    int startingPoint = s.find_first_of("123456789");
    int index = s.length() - increment - startingPoint;
    if (s.length()<power || index < 0) {
        index = 0;
    }
    int iterations = ((s.length()-startingPoint) + power - 1) / power;

    for (int i = 0; i < iterations; i++) {
        if ( s.substr(startingPoint).substr(index, increment).find_first_of("+-") != std::string::npos) {
            digits.insertAfter(std::stoi(s.substr(index+1, increment-1)));
        }
        else {
            digits.insertAfter(std::stoi(s.substr(startingPoint).substr(index, increment)));
        }
        if ( increment > index ) {
            increment = increment - (increment-index);
            index = 0;
        }
        else {
            index = index - power;
        }
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits;
}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,
// negative or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    if ((signum==-1)^(N.signum==-1)) {
        if (signum==-1) {
            return -1;
        }
        else {
            return 1;
        }
    }
    if  (digits == N.digits) {
        return 0;
    }
    if ( digits.length() > N.digits.length() ) {
        return 1;
    }
    if ( digits.length() < N.digits.length() ) {
        return -1;
    }
    List a = digits;
    List b = N.digits;
    a.moveFront();
    b.moveFront();
    for (int i = 0; i < a.length(); i++) {
        if (a.peekNext() > b.peekNext()) {
            return 1;
        }
        if (a.peekNext() < b.peekNext()) {
            return -1;
        }
        a.moveNext();
        b.moveNext();
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate() {
    if (signum == 0) {
        return;
    }
    signum = -signum;
}

// BigInteger Arithmetic operations ----------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {
    L.moveBack();
    for (int i = 0; i < L.length(); i++) {
        L.setBefore(-L.peekPrev());
        L.movePrev();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn) {
    A.moveBack();
    B.moveBack();
    if (A.equals(B) && sgn == -1) {
        return;
    }
    int length;
    if ( A.length() > B.length()) {
        length = A.length();
    }
    else {
        length = B.length();
    }
    for (int i = 0; i < length; i++) {
        if (A.position()!=0 && B.position()!=0) {
            S.insertAfter(A.peekPrev()+(sgn*B.peekPrev()));
            A.movePrev();
            B.movePrev();
        }
        else if (A.position()!=0) {
             S.insertAfter(A.peekPrev());
             A.movePrev();
        }
        else {
            S.insertAfter((sgn*B.peekPrev()));
            B.movePrev();
        }
    }
    if (S.front()==0 && S.length()!=0) {
        S.eraseAfter();
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L) {
    // zero state
    if (L.length()==0) {
        return 0;
    }

    int sign;
    if (L.front() > 0) {
        sign = 1;
    }
    else {
        sign = -1;
    }
    int borrow = 0;
    int carry = 0;
    if (sign==-1) {
        negateList(L);
    }
    L.moveBack();
    for (int i = 0; i < L.length(); i++) {
        int current = L.peekPrev() - borrow + carry;
        carry = 0;
        borrow = 0;
        if (current < 0) {
            current = base + current;
            borrow = 1;
        }
        else if (current >= base) {
            carry = current / base;
            current = current % base;
        }
        L.setBefore(current);
        L.movePrev();
    }
    if (L.position()==0 && carry!=0) {
        L.insertAfter(carry);
    }
    // when the front is bigger than the base or equal carry over
    carry = L.front()/base;
    while (carry != 0) {
        int current = L.front() % base;
        L.setAfter(current);
        L.insertAfter(carry);
        carry = L.front()/base;
    }

    return sign;
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger sumBigInt;
    List sum;
    List A = digits;
    List B = N.digits;
    if (signum==0 && N.signum==0) {
        return sumBigInt;
    }
    else if (signum>=0 && N.signum>=0) {
        sumList(sum, A, B, N.signum);
        sumBigInt.signum = normalizeList(sum);
    }
    else if (signum==-1 && N.signum==-1) {
        sumList(sum, A, B, 1);
        normalizeList(sum);
        sumBigInt.signum = -1;
    }
    else if (signum==-1 && N.signum!=-1) {
        sumList(sum, B, A, -1);
        sumBigInt.signum = normalizeList(sum);
    }
    else { //signum!=-1 && N.signum==-1
        sumList(sum, A, B, -1);
        sumBigInt.signum = normalizeList(sum);
    }
    sumBigInt.digits = sum;
    return sumBigInt;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger subtracted;
    BigInteger copyN = N;
    copyN.signum = -(copyN.signum);
    subtracted = (*this).add(copyN);
    return subtracted;
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
    if (m == 0) {
        L = List();
        return;
    }
    if (m == 1) {
        return;
    }
    long long carry = 0;
    long long d = (long long) m;
    L.moveBack();
    for (int i = 0; i < L.length(); i++) {
        long long adder = (((long long)L.peekPrev()) * d) + carry;
        carry = 0;
        L.setBefore(adder % base);
        carry = adder/base;
        L.movePrev();
    }
    if (carry!=0) {
        L.insertAfter(carry);
    }
}

// mult()
// Returns a BigInteger representing the product of this and N.
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger multiplied;
    if (signum == 0 || N.signum == 0) {
        return multiplied;
    }
    BigInteger longNum = digits.length()>=N.digits.length()?(*this):N;
    BigInteger shortNum = digits.length()>=N.digits.length()?N:(*this);
    BigInteger manipulated;
    longNum.digits.moveBack();
    shortNum.digits.moveBack();
    for (int i = 0; i < shortNum.digits.length(); i++) {
        if (i != 0) {
            // shift list 1 zero every iteration after first
            longNum.digits.insertAfter(0);
        }
        manipulated = longNum;
        scalarMultList(manipulated.digits, shortNum.digits.peekPrev());
        multiplied = multiplied.add(manipulated);
        shortNum.digits.movePrev();
    }

    multiplied.signum = signum * N.signum;
    return multiplied;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    std::string s = "";
    if (signum == 0) {
        s += "0";
        return s;
    }
    if (signum == -1) {
        s += "-";
    }

    digits.moveFront();
    std::string inputs = "";
    while (digits.position() != digits.length()) {
        inputs = std::to_string(digits.peekNext());
        int strLength = power - inputs.length();
        if (digits.position() != 0) {
            for (int i = 0; i < strLength; i++) {
                inputs.insert(0, "0");
            }
        }
        s.append(inputs);
        digits.moveNext();
    }
    return s;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == 0) {
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == -1) {
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == -1 || A.BigInteger::compare(B) == 0) {
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B.
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == 1) {
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == 1 || A.BigInteger::compare(B) == 0) {
        return true;
    }
    return false;
}

// operator+()
// Returns the sum A+B.
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::add(B);
}

// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.BigInteger::add(B);
    return A;
}

// operator-()
// Returns the difference A-B.
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::sub(B);
}

// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.BigInteger::sub(B);
    return A;
}

// operator*()
// Returns the product A*B.
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.BigInteger::mult(B);
}

// operator*=()
// Overwrites A with the product A*B.
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.BigInteger::mult(B);
    return A;
}
