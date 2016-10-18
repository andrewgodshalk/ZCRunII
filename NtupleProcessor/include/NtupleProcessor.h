#ifndef GUARD_NtupleProcessor_h
#define GUARD_NtupleProcessor_h

/*------------------------------------------------------------------------------
 NtupleProcessor
   Created : 2015-09-14  godshalk
   Modified: 2016-08-16  godshalk
 Main class of NtupleProcessor program. Created to handle input and running of
 ntuple processing.
 Takes input variables (datasets, configurations, etc) and sets up the
 appropriate classes to handle each portion of the analysis process.
------------------------------------------------------------------------------*/
#include <string>
#include <vector>
// ROOT Libraries
#include <TChain.h>
//#include <TFile.h>
// Project Specific classes
#include "TreeIterator.h"
#include "../../Utilities/include/TimeStamp.h"

//class TimeStamp;

class NtupleProcessor
{
  public:
    NtupleProcessor(int argc, char* argv[]);  // Primary constructor.
   ~NtupleProcessor(){}

  private:
    // File Information
    std::vector<std::string> ntupleFileNames_;
//    TFile* ntupleFile_;
    TChain* ntuples_;

    TreeIterator tIter_;

    // Processing information
    counter   eventsToProcess_;
    TimeStamp beginTime_;
    TimeStamp endTime_;
};

#endif
