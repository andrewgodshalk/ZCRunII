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
//#include "../ZCLibrary/timestamp.h"                       // Project Specific classes
#include "../include/NtupleProcessor.h"

using std::cout;     using std::endl;
using std::string;   using std::ifstream;
using std::vector;

namespace po = boost::program_options;

int main(int argc, char* argv[])
{

  // INITIAL COMMAND LINE OUTPUT
    cout << "\n\n"
            "================================================================================\n"
            "===NtupleProcessor==============================================================\n"
            //"  Processing Begun: " << ts_mainBegin << "\n"
            "\n";

  // PROCESS INPUT

  // SET UP NTUPLEPROCESSOR
    NtupleProcessor nProc;

  // CLOSING OUTPUT.
    //TString ts_mainEnd = timeStamp();
    cout << "\n"
            //"  Completion time: " << ts_mainEnd <<      "\n"

            "===NtupleProcessor - COMPLETE===================================================\n"
            "================================================================================\n"
         << endl;

    return 0;
}

