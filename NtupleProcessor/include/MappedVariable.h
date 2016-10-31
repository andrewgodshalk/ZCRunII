#ifndef GUARD_MappedVariable_h
#define GUARD_MappedVariable_h

/*------------------------------------------------------------------------------
   MappedVariable/MappedArray

 Created : 2016-10-25  godshalk
 Modified: 2016-10-27  godshalk

 Classes that map arrays and variables from tree.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <string>
// Submodules
// Root Classes
// Project Specific classes
#include "Logger.h"

const static unsigned int MAXARRAYLENGTH = 100;

template<typename T>
class MappedVariables
{
    MappedVariable(TTree* tree, const char* n)
      : name_(n)
    {
        tree->SetBranchAddress(n, &value_);
    }
    ~MappedVariable(){}

    std::string name_;
    T value_;
};

template<typename T>
class MappedArray
{
    MappedArray(TTree* tree, const char* n, unsigned int l)
      : name_(n), length_(l)
    {
        tree->SetBranchAddress(n, array_);
    }
    ~MappedVariable(){}

    std::string name_;
    unsigned int length_;
    T array_[MAXARRAYLENGTH];
};

#endif
