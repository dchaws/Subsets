// 5/30/11 David Haws
// Created to hold all the subset functions 

#ifndef SUBSETS_H
#define SUBSETS_H 1

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <set>
#include <ext/hash_set>

using namespace __gnu_cxx;
using namespace std;

// Return true if two sets are equal
int setsEqual (set <int> setOne, set <int> setTwo);

// Returns the ith element. Index from 0.
int getEl (set <int> curSubset, int i);

// Checks if element is in subset
int inSubset(int x, set <int> curSubset);

// This checks if subsetOne is a subset of subsetTwo
int isSubset(set <int> subsetOne, set <int> subsetTwo);

// This will take in a subsets of integers, and output the next lexicographic subset
// with the same cardinality. maxEl is the largest value the subsets can take.
// If it is successful, it sets success to 1. 0 else.
set <int> nextSubsetCard( set <int> curSubset, int maxEl, int &success);

// Assumes curSubset is subset of supSet
// If supSet = {1,3,5,6} and curSubset = {1,5}, this returns
// {1,3}. That is, the position of the subset in the supSet.
set <int> mapOne (const set <int> curSubset, const set <int> supSet);


// Assumes curSubset is subset of supSet
// This is the inverse of mapOne,
// If supSet = {1,3,5,6} and curSubset = {1,3}, this returns
// {1,5}. That is the values of the 1 and 3 position in supSet.
set <int> mapTwo (const set <int> curSubset, const set <int> supSet);

// This will take in curSubset, and will return the next subset that is a subset of supSet.
// If it succeeds, then success = 1. Else 0.
set <int> nextSubsetOfSubset( set <int> curSubset, const set <int> supSet, int &success);

// Prints a set of integers.
void const printSubset(const set <int> mySubset, int printNewline);

// Prints a set of integers.
void const printSubset(const set <int> mySubset);

// So I can use cout << mySubset.
ostream &operator<<(ostream &outStream, set <int> mySubset);

// Returns a string representing mySubset.
// E.g. {0,1,3} -> "1101"
// maxEl tells how long of a string to return. If maxEl = -1, then use
// the max element.
char * setToString (const set <int> inputSubset, const char *pad, int stringMaxEl);

// This is a necessary structure for my map of subsets
struct ltsetint
{
    bool operator()(const set <int> setOne, const set <int> setTwo) const
    {
        //cout << "Called with: " << endl;
        //cout << "    setOne(" << setOne.size() << "): ";
        //printSubset(setOne);
        //cout << "    setTwo(" << setTwo.size() << "): ";
        //printSubset(setTwo);
        if(setOne.size() == 0 && setTwo.size() == 0)
        {
            return 0;
        }

        if (setOne.size() < setTwo.size())
        {
            return 1;
        }
        else if (setOne.size() > setTwo.size())
        {
            return 0;
        }
        else if (setOne.size() == setTwo.size())
        {
            // Now must check if setOne is less than setTwo in lex order.
            set <int>::const_iterator sitOne,sitTwo;

            sitOne = setOne.begin();
            sitTwo = setTwo.begin();

            while (sitOne != setOne.end() && sitTwo != setTwo.end())
            {
                if (*sitOne > *sitTwo)
                {
                    return 0;
                }
                else if (*sitOne < *sitTwo)
                {
                    return 1;
                }
                sitOne++;
                sitTwo++;
            }
            return 0;
        }
    }
};

// For a hash map of subsets
struct eqSetInt
{
    bool operator()(const set <int> setOne, const set <int> setTwo) const
    {
        return setsEqual (setOne,setTwo);
    }
};

// Computes the has of a set of ints by converting to a string then hashing.
struct hashSetInt
{
    size_t operator()(const set <int> mySubset) const
    {
        hash <const char *> H;
        size_t retVal;
        char *subString = setToString(mySubset,"",-1);
        retVal = H(subString);
        delete [] subString;
        return retVal;
    }
};
#endif
