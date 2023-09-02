/*********************************************************************************
* ListTest.cpp
* Test client for List ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

int main() {

    // Class Constructors & Destructors ----------------------------------------

    // Testing List Constructor and Destructor
    List L;

    // Testing Copy Constructor
    List D;
    D.insertAfter(3);
    D.insertAfter(4);
    D.insertAfter(5);
    List C = D;
    std::cout << "copy contructor" << std::endl;
    std::cout << D << std::endl;
    std::cout << C << "position: " << C.position() << std::endl;

    // Access functions --------------------------------------------------------

    // testing length()
    std::cout << "length(): " << L.length() << std::endl;
    L.insertAfter(3);
    L.insertAfter(4);
    L.insertAfter(5);
    std::cout << "length(): " << L.length() << std::endl;
    std::cout << L << std::endl;

    // testing front()
    std::cout << "front(): " << L.front() << std::endl;

    // testing back()
    std::cout << "back(): " << L.back() << std::endl;

    // testing position()
    std::cout << "position(): " << L.position() << std::endl;
    L.moveNext();
    std::cout << "position(): " << L.position() << std::endl;

    // testing peekNext()
    std::cout << "peekNext(): " << L.peekNext() << std::endl;

    // testing peekPrev()
    std::cout << "peekPrev(): " << L.peekPrev() << std::endl;

    // Manipulation procedures -------------------------------------------------

    // testing clear()
    std::cout << "clear(): " << std::endl;
    L.clear();
    std::cout << "length: " << L.length() << std::endl;
    std::cout << "position: " << L.position() << std::endl;

    // testing moveFront()
    L.insertAfter(3);
    L.insertAfter(4);
    L.insertAfter(5);
    L.moveNext();
    std::cout << "moveFront(): " << std::endl;
    std::cout << L << std::endl;
    std::cout << "position: " << L.position() << " peekPrev: " << L.peekPrev() << " peekNext: " << L.peekNext() << std::endl;
    L.moveFront();
    std::cout << "position: " << L.position() << " peekNext: " << L.peekNext() << std::endl;

    // testing moveBack()
    L.moveBack();
    std::cout << "moveBack()" << std::endl;
    std::cout << "position: " << L.position() << " peekPrev: " << L.peekPrev() << std::endl;

    // testing movePrev()
    L.movePrev();
    std::cout << "movePrev()" << std::endl;
    std::cout << "position: " << L.position() << " peekPrev: " << L.peekPrev() << " peekNext: " << L.peekNext() << std::endl;

    // testing insertBefore()
    L.insertBefore(6);
    std::cout << "insertBefore()" << std::endl;
    std::cout << L << std::endl;
    std::cout << "position: " << L.position() << " peekPrev: " << L.peekPrev() << " peekNext: " << L.peekNext() << std::endl;

    // testing setAfter()
    L.setAfter(1);
    std::cout << "setAfter()" << std::endl;
    std::cout << L << std::endl;
    std::cout << "position: " << L.position() << " peekPrev: " << L.peekPrev() << " peekNext: " << L.peekNext() << std::endl;

    // testing setBefore()
    L.setBefore(3);
    std::cout << "setBefore()" << std::endl;
    std::cout << L << std::endl;
    std::cout << "position: " << L.position() << " peekPrev: " << L.peekPrev() << " peekNext: " << L.peekNext() << std::endl;


    // testing eraseBefore()
    L.eraseBefore();
    std::cout << "eraseBefore()" << std::endl;
    std::cout << L << std::endl;
    std::cout << "position: " << L.position() << " peekPrev: " << L.peekPrev() << " peekNext: " << L.peekNext() << std::endl;

    // Other Functions ---------------------------------------------------------

    // testing findNext()
    L.moveFront();
    L.moveNext();
    std::cout << "findNext(): " << L.findNext(5) << " Cursor Positon: " << L.position() << std::endl;

    // testing findPrev()
    L.moveBack();
    //L.movePrev();
    std::cout << "findPrev(): " << L.findPrev(6) << " Cursor Positon: " << L.position() << std::endl;

    // testing cleanup()
    std::cout << "cleanup()" << std::endl;
    L.insertAfter(1);
    L.insertAfter(4);
    L.insertAfter(6);
    L.insertAfter(5);
    L.insertAfter(5);
    L.moveNext();
    L.moveNext();
    L.moveNext();
    L.moveNext();
    L.insertAfter(6);
    L.insertAfter(6);
    std::cout << L << " position: " << L.position() << std::endl;
    L.cleanup();
    std::cout << L << " position: " << L.position() << std::endl;

    // testing concat()
    List conc = L.concat(L);
    std::cout << "concat()" << std::endl;
    std::cout << conc << " position: " << conc.position() << " length: " << conc.length() << std::endl;

    // testing equals()
    std::cout << "equals()" << std::endl;
    std::cout << L.equals(D) << std::endl;

    // testing ==
    std::cout << "operator==" << std::endl;
    std::cout << (L==L?"true":"false") << std::endl;

    // testing =
    std::cout << "operator=" << std::endl;
    std::cout << L << std::endl;
    std::cout << D << std::endl;
    D=L;
    std::cout << L << std::endl;
    std::cout << D << std::endl;

    // other tests
    List A;
    List B;
    A.insertBefore(1);
    A.insertAfter(2);
    B.insertBefore(1);
    B.insertBefore(2);
    A.eraseAfter();
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << (A==B?"true":"false") << std::endl;
    return 0;
}
