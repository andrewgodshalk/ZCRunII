/*------------------------------------------------------------------------------
NtupleProcessor/main.cpp
Modified: 2016-08-16
Main file for the NtupleProcessor program.
Handles command line arguements.
------------------------------------------------------------------------------*/

#include <iostream>
// Project Specific classes
#include "../include/NtupleProcessor.h"

using std::cout;     using std::endl;

int main(int argc, char* argv[])
{
  // SET UP NTUPLEPROCESSOR
    NtupleProcessor nProc (argc, argv);

    return 0;
}
