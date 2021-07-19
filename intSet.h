#include <stdbool.h>
#ifndef INTSET_H
#define INTSET_H

typedef struct intsetType *intSet;

intSet createSet(); // returns an intSet created at runtime using malloc
void destroySet(intSet); // frees up the memory associated with its argument
void clear(intSet); // clears set to empty (does not free up memory)
int card(const intSet); // returns the cardinality of the set
bool equals(const intSet,const intSet); // returns true if 2 sets are equal, false
// otherwise; two sets are equal if they contain
// all of the same values
bool contains(const intSet,int); // retuns true if argument is in set, false otherwise
int largest(const intSet); // returns the largest item in the set; print error message
// and exit if set is empty
int smallest(const intSet); // returns the smallest item in the set print error message
// and exit if set is empty
void add(intSet s,int item); // adds item to s or does nothing if it is in set
void remove_(intSet s,int item); // removes item from s or does nothing if it is not in set
intSet union_(const intSet, const intSet); // set union
intSet intersect(const intSet, const intSet); // set intersection
intSet diff(const intSet s1, const intSet s2); // set difference, i.e. s1 - s2
bool isEmpty(const intSet); // returns true if the set is empty, false otherwise
int *toArray(const intSet); // returns an array representation of the set in
// sorted ascending order
char *toString(const intSet); // returns a string representation of the set in sorted
// ascending order; e.g. an empty set returns "{}", and
// a non-empty set containing the values 9,-52,17 would
// return the string "{-52,9,17}"
#endif
