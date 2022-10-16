#include "student.hpp"

// node of linkedhashset
struct lhsnode{
    student element_;
    lhsnode *next_;
    lhsnode *prev_;
    lhsnode(student element, lhsnode *next, lhsnode *prev);
};

lhsnode::lhsnode(student element, lhsnode *next = nullptr, lhsnode *prev = nullptr) :
        element_(element),
        next_(next),
        prev_(prev) {

}