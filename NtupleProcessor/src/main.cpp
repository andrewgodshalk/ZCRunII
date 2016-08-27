/*------------------------------------------------------------------------------
NtupleProcessor/main.cpp
Modified: 2016-08-16
Main file for the NtupleProcessor program.
Handles command line arguements.
------------------------------------------------------------------------------*/

// HEADERS
#include <algorithm>
#include <iostream>                 // stdlib
#include <string>
#include <vector>
#include <TFile.h>                  // ROOT classes
#include <TString.h>
#include <TTree.h>
#include <boost/program_options/options_description.hpp>    // boost classes
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include "../../Utilities/include/TimeStamp.h"                // Project Specific classes
#include "../include/NtupleProcessor.h"

using std::cout;     using std::endl;
using std::string;   using std::ifstream;
using std::vector;

//namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    TimeStamp beginTime;

  // INITIAL COMMAND LINE OUTPUT
    cout << "\n\n"
            "================================================================================\n"
            "===NtupleProcessor==============================================================\n"
            "  Processing Begun: " << beginTime.log_str() << "\n"
         << endl;

  // PROCESS INPUT

  // SET UP NTUPLEPROCESSOR
    NtupleProcessor nProc;

  // CLOSING OUTPUT.
    TimeStamp endTime;
    cout << "\n"
            "  Completion time: " << endTime.log_str() <<      "\n"
            "===NtupleProcessor - COMPLETE===================================================\n"
            "================================================================================\n"
         << endl;

    return 0;
}

