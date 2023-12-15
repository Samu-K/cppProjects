#include "array_operations.hh"

#include <iostream>

using std::cout;
using std::endl;

int greatest_v1(int *itemptr, int size)
{
    int greatest_val = *itemptr;
    int n = 0;

    while (n<size) {
        if (*itemptr > greatest_val) {
            greatest_val = *itemptr;
        }
        ++itemptr;
        ++n;
    }

    return greatest_val;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest_val = *itemptr;
    while (itemptr < endptr) {
        if (*itemptr > greatest_val) {
            greatest_val = *itemptr;
        }
        ++itemptr;
    }
    return greatest_val;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    int index = 0;
    while (itemptr < endptr) {
        *(targetptr+index) = *itemptr;
        ++itemptr;
        ++index;
    }

}

void reverse(int *leftptr, int *rightptr)
{

   while (leftptr < rightptr) {
       int temp;
       temp = *leftptr;
       *leftptr = *rightptr;
       *rightptr = temp;
       leftptr++;
       rightptr--;

   }
}
