#ifndef GUARD_NtupleProcessor_h
#define GUARD_NtupleProcessor_h

/*------------------------------------------------------------------------------
 NtupleProcessor
   Created : 2015-09-14  godshalk
   Modified: 2016-08-19  godshalk
 Main class of NtupleProcessor program. Created to handle input and running of
 ntuple processing.
 Takes input variables (datasets, configurations, etc) and sets up the
 appropriate classes to handle each portion of the analysis process.

 2016-10-19 - Started work on adding logging.
------------------------------------------------------------------------------*/
#include <string>
#include <vector>
// ROOT Libraries
#include <TChain.h>
// Project Specific classes
#include "TreeIterator.h"
#include "../../Utilities/include/TimeStamp.h"

typedef unsigned long counter;

class NtupleProcessor
{
  public:
    NtupleProcessor(int argc, char* argv[]);  // Primary constructor.
   ~NtupleProcessor(){}

  private:
    // File Information
    std::vector<std::string> ntupleFileNames_;
    TChain* ntuples_;

    TreeIterator tIter_;

    // Processing information
    counter   eventsToProcess_;
    TimeStamp beginTime_;
    TimeStamp endTime_;
    std::string o_location_;  // Included to specify running on LPC or on personal computer.
};

#endif
