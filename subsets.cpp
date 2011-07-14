// Copyright (C) 2011 David C. Haws

//This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

// See LICENSE

// David Haws
// 7/14/2011
// www.davidhaws.net
// https://github.com/dchaws

#include "subsets.h"

// Added file to git2.as.uky.edu

// Return true if two sets are equal
int setsEqual (set <int> setOne, set <int> setTwo)
{
    if (setOne.size() != setTwo.size())
    {
        return 0;
    }
    set <int>::const_iterator sitOne,sitTwo;

    sitOne = setOne.begin();
    sitTwo = setTwo.begin();

    while (sitOne != setOne.end() && sitTwo != setTwo.end())
    {
        if (*sitOne != *sitTwo)
        {
            return 0;
        }
        sitOne++;
        sitTwo++;
    }
    return 1;

}


// Returns the ith element. Index from 0.
int getEl (set <int> curSubset, int i)
{
    if (i > curSubset.size())
    {
        cout << "getEl called with i larger than curSubset.size()." << endl;
    }
    set <int>::const_iterator sit = curSubset.begin();
    for (int j=0;j<i;j++)
    {
        sit++;
    }
    return *sit;
}

// Checks if element is in subset
int inSubset(int x, set <int> curSubset)
{
    if (curSubset.find(x) == curSubset.end())
    {
        return 0;
    }
    return 1;
}

// This checks if subsetOne is a subset of subsetTwo
int isSubset(set <int> subsetOne, set <int> subsetTwo)
{
    if (subsetOne.size() > subsetTwo.size())
    {
        return 0;
    }
    set <int>::const_iterator sitOne;
    sitOne = subsetOne.begin();

    while(sitOne != subsetOne.end())
    {
        if (inSubset(*sitOne,subsetTwo) == 0)
        {
            return 0;
        }
        sitOne++;
    }
    return 1;

}

// This will take in a subsets of integers, and output the next lexicographic subset
// with the same cardinality. maxEl is the largest value the subsets can take.
// If it is successful, it sets success to 1. 0 else.
set <int> nextSubsetCard( set <int> curSubset, int maxEl, int &success)
{
    set <int> retSubset = curSubset;

    if (retSubset.size() == 0)
    {
        success = 0;
        return retSubset;
    }

    // Find last element
    set <int>::iterator sit;

    sit = retSubset.end();
    sit--;
    success = 0;
    while (success == 0)
    {
        if (*sit < maxEl && retSubset.find(*sit+1) == retSubset.end())
        {
            // Remove sit and any elements after it.
            int elRemoved = 0;
            int tempEl = *sit + 1;

            set <int>::iterator nextSit;
            while (sit!=retSubset.end())
            {
                nextSit = sit;
                nextSit++;
                retSubset.erase(sit);
                sit = nextSit;
                elRemoved++;
            }
            for (int i=0;i<elRemoved;i++)
            {
                retSubset.insert(tempEl + i);
            }
            success = 1;
        }
        else 
        {
            if (sit == retSubset.begin())
            {
                success = 0;
                return retSubset;
            }
            else {
                sit--;
            }
        }
    }
    return retSubset;
}

// Assumes curSubset is subset of supSet
// If supSet = {1,3,5,6} and curSubset = {1,5}, this returns
// {1,3}. That is, the position of the subset in the supSet.
set <int> mapOne (const set <int> curSubset, const set <int> supSet)
{
    set <int> retSubset;
    set <int>::const_iterator sitOne,sitTwo;
    sitOne = curSubset.begin();
    sitTwo = supSet.begin();

    int count = 1;
    while(sitTwo != supSet.end())
    {
        if (*sitTwo == *sitOne)
        {
            retSubset.insert(count);
            sitOne++;
        }
        sitTwo++;
        count++;
    }
    return retSubset;
}

// Assumes curSubset is subset of supSet
// This is the inverse of mapOne,
// If supSet = {1,3,5,6} and curSubset = {1,3}, this returns
// {1,5}. That is the values of the 1 and 3 position in supSet.
set <int> mapTwo (const set <int> curSubset, const set <int> supSet)
{
    set <int> retSubset;
    set <int>::const_iterator sitOne,sitTwo;
    sitOne = curSubset.begin();

    while(sitOne != curSubset.end())
    {
        sitTwo = supSet.begin();
        for(int i=0;i<*sitOne-1;i++)
        {
            sitTwo++;
        }
        retSubset.insert(*sitTwo);
        sitOne++;
    }
    return retSubset;
}

// This will take in curSubset, and will return the next subset that is a subset of supSet.
// If it succeeds, then success = 1. Else 0.
set <int> nextSubsetOfSubset( set <int> curSubset, const set <int> supSet, int &success)
{
    // This can be accomplished using nextSubsetCard.
    int mySuccess = 0;    
    set <int> retSubset;

    if (curSubset.size() == 0)
    {
        retSubset.insert( (*(supSet.begin())));
        success = 1;
        return retSubset;
    }

    set <int> mySubset = mapOne(curSubset,supSet);

    // Try to increase mySubset
    mySubset = nextSubsetCard(mySubset,supSet.size(),mySuccess);

    if (mySuccess == 1)
    {
        retSubset = mapTwo(mySubset,supSet);
        success = 1;
        return retSubset;
    }
    else 
    {
        // Try to increase the cardinality
        if (curSubset.size() < supSet.size())
        {
            int curSize = curSubset.size() + 1;
            set <int>::const_iterator sit = supSet.begin();
            for (int i=0;i<curSize;i++)
            {
                retSubset.insert(*sit);
                sit++;
            }
            success = 1;
            return retSubset;
        }
        else {
            // Can't increase
            success = 0;
            return curSubset;
        }
    }


}

// Prints a set of integers.
void const printSubset(const set <int> mySubset, int printNewline)
{
    set <int>::const_iterator sit = mySubset.begin();
    for (;sit!=mySubset.end();sit++)
    {
        cout << setw(4) << *sit << " ";
    }
    if (printNewline == 1)
    {
        cout << endl;
    }
}

// Prints a set of integers.
void const printSubset(const set <int> mySubset)
{
    printSubset(mySubset,1);
}

// So I can use cout << mySubset.
ostream &operator<<(ostream &outStream, set <int> mySubset)
{
    set <int>::const_iterator sit = mySubset.begin();
    set <int>::const_iterator tempSit;
    outStream << "(";
    for (;sit!=mySubset.end();sit++)
    {
        outStream << *sit;
        tempSit = sit;
        tempSit++;
        if (tempSit != mySubset.end())
        {
            outStream << ",";
        }
    }
    outStream << ")";

  return outStream;
}

// Returns a string representing mySubset.
// E.g. {0,1,3} -> "1101"
// maxEl tells how long of a string to return. If maxEl = -1, then use
// the max element.
char * setToString (const set <int> inputSubset, const char *pad, int stringMaxEl)
{
    set <int> mySubset = inputSubset;
    //cout << "\"" << pad << "\" " << strlen(pad) << endl;
    if (mySubset.size() == 0)
    {
        char *retString = new char[1];
        retString = 0;
        return retString;
    }
    else {
        set <int>::iterator sit = mySubset.end();
        set <int>::iterator tempSit;
        sit--;
        int maxEl;
        if (stringMaxEl != -1 && mySubset.find(stringMaxEl) == mySubset.end())
        {
            maxEl = stringMaxEl;
            mySubset.insert(stringMaxEl);
        }
        else
        {
            stringMaxEl = -1;
            maxEl = *sit;
        }
        int stringLength = (maxEl+1)*(1 + strlen(pad)) + 1;//Cutting it close. Need +2 since the indexing starts at 0

        char *retString = new char[stringLength]; 
        int curPos = 0; //multiple of (1 + strlen(pad))
        for(sit=mySubset.begin();sit!=mySubset.end();sit++)
        {
            if (curPos < *sit)
            {
                int posDiff = *sit - curPos;
                for(int i=0;i<posDiff;i++)
                {
                    retString[curPos*(1 + strlen(pad))] = '0';
                    for (int j=0;j<strlen(pad);j++)
                    {
                        retString[curPos*(1 + strlen(pad)) + j + 1] = pad[j];
                    }
                    curPos++;
                }
            }
            retString[curPos*(1 + strlen(pad))] = '1';
            tempSit = sit;
            tempSit++;
            if (tempSit != mySubset.end())
            {
                for (int j=0;j<strlen(pad);j++)
                {
                    retString[curPos*(1 + strlen(pad))  + j + 1] = pad[j];
                }
            }
            curPos++;
        }
        // Change the last 1 into a 0 if we artificially inserted stringMaxEl
        if (stringMaxEl != -1)
        {
            retString[(curPos-1)*(1 + strlen(pad))] = '0';
        }

        retString[curPos*(1 + strlen(pad)) - strlen(pad)] = 0; // Don't forget to null-terminate
        return retString;
    }
}
