/*********************************************************************************
* Jonathan Nguyen, jnguy330
* 2023 Spring CSE101 PA6
* List.cpp
* Implementation file for List ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates new List in the empty state.
List::List() {
    frontDummy = new Node(-1);
    backDummy = new Node(-2);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
    // making empty List
    frontDummy = new Node(-1);
    backDummy = new Node(-2);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    // load elements of L into this List
    Node* N = L.frontDummy->next;
    while (N->next!=nullptr) {
        insertBefore(N->data);
        N = N->next;
    }
    moveFront();
}

// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if ( !(length()>0) ) {
        throw std::length_error("List: front(): empty List");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if ( !(length()>0) ) {
        throw std::length_error("List: back(): empty List");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if ( !(position()<length()) ) {
        throw std::length_error("List: peekNext(): empty list or at max cursor position");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if ( !(position()>0) ) {
        throw std::length_error("List: peekPrev(): empty list or at smallest cursor position");
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveFront();
    while (length() != 0) {
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = length();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext() {
    if ( !(position()<length()) ) {
        throw std::length_error("List: moveNext(): cursor position at max index");
    }
    pos_cursor++;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev() {
    if ( !(position()>0) ) {
        throw std::length_error("List: movePrev(): cursor position at smallest index");
    }
    pos_cursor--;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    return afterCursor->data;

}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    afterCursor->prev = N;
    beforeCursor->next = N;
    afterCursor = N;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev= beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if ( !(position()<length()) ) {
        throw std::length_error("List: setAfter(): no List Element after cursor position of max index");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if ( !(position()>0) ) {
        throw std::length_error("List: setBefore(): no List Element before cursor position of smallest index");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    if ( !(position()<length()) ) {
        throw std::length_error("List: eraseAfter(): no List Element after cursor position of max index");
    }
    Node* N = afterCursor;
    if (length() > 1) {
        afterCursor->next->prev = beforeCursor;
        beforeCursor->next = afterCursor->next;
        afterCursor = afterCursor->next;
    }
    else {
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        beforeCursor = frontDummy;
        afterCursor = backDummy;
    }
    num_elements--;
    delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if ( !(position()>0) ) {
        throw std::length_error("List: eraseBefore(): no List Element before cursor position of smallest index");
    }
    Node* N = beforeCursor;
    if (length() > 1) {
        beforeCursor->prev->next = afterCursor;
        afterCursor->prev = beforeCursor->prev;
        beforeCursor = beforeCursor->prev;
    }
    else {
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        beforeCursor = frontDummy;
        afterCursor = backDummy;
    }
    pos_cursor--;
    num_elements--;
    delete N;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {
    bool xFound = false;
    while (afterCursor->next!=nullptr) {
        if (afterCursor->data == x) {
            xFound = true;
            moveNext();
            break;
        }
        moveNext();
    }
    if (xFound) {
        return pos_cursor;
    }
    else {
        moveBack();
        return -1;
    }
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    bool xFound = false;
    while (beforeCursor->data!=-1) {
        if (beforeCursor->data == x) {
            xFound = true;
            movePrev();
            break;
        }
        movePrev();
    }
    if (xFound) {
        return pos_cursor;
    }
    else {
        moveFront();
        return -1;
    }
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    // if element before cursor is removed do pos--
    // if element after cursor do nothing
    int originalPos = pos_cursor;
    moveFront();
    while (afterCursor->next!=nullptr) {
        moveNext();
        int returnCursor = pos_cursor;
        int del = findNext(beforeCursor->data);
        if (del != -1) {
            eraseBefore();
            returnCursor--;
            if (del <= originalPos) {
                originalPos--;
            }
        }
        moveFront();
        while (pos_cursor != returnCursor) {
            moveNext();
        }
    }
    if (pos_cursor!=originalPos) {
        moveFront();
        while ( pos_cursor!=originalPos ) {
            moveNext();
        }
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List C;
    Node* N = this->frontDummy->next;
    Node* M = L.frontDummy->next;
    while (N->next!=nullptr) {
        C.insertBefore(N->data);
        N = N->next;
    }
    while (M->next!=nullptr) {
        C.insertBefore(M->data);
        M = M->next;
    }
    C.moveFront();
    return C;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    Node* N = nullptr;
    std::string s = "";

    for(N=frontDummy->next; N->next!=nullptr; N=N->next){
        s += std::to_string(N->data)+" ";
    }
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    if (this->num_elements != R.num_elements) {
        return false;
    }
    Node* N = this->frontDummy->next;
    Node* M = R.frontDummy->next;
    while (N->next!=nullptr) {
        if (N->data != M->data) {
            return false;
        }
        N = N->next;
        M = M->next;
    }
    return true;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    if( this != &L ){
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}