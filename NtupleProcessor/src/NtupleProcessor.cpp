/*------------------------------------------------------------------------------
NtupleProcessor.cpp
 Created : 2015-09-14  godshalk
 Modified: 2016-08-16  godshalk
------------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TString.h>
#include "../include/NtupleProcessor.h"

using std::cout;   using std::endl;   using std::vector;   using std::ifstream;

NtupleProcessor::NtupleProcessor()
{
  // Initial output
    cout << "  NtupleProcessor: Created.\n"
         << endl;
}
