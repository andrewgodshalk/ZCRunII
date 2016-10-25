#ifndef GUARD_NtupleProcessor_h
#define GUARD_NtupleProcessor_h

/*------------------------------------------------------------------------------
 NtupleProcessor
   Created : 2015-09-14  godshalk
   Modified: 2016-10-24  godshalk
 Main class of NtupleProcessor program. Created to handle input and running of
 ntuple processing.
 Takes input variables (datasets, configurations, etc) and sets up the
 appropriate classes to handle each portion of the analysis process.

 2016-10-24 - Integrated loggers.
 2016-10-20 - Moved main function into source for this class.
 2016-10-19 - Started work on adding logging.
------------------------------------------------------------------------------*/
#include <exception>
#include <string>
#include <vector>
// ROOT Libraries
#include <TChain.h>
// Submodules
#include "spdlog/spdlog.h"
// Project Specific classes
#include "TreeIterator.h"
#include "TimeStamp.h"

typedef unsigned long counter;

class NtupleProcessor
{
  public:
    NtupleProcessor(int argc, char* argv[]);  // Primary constructor.
   ~NtupleProcessor(){}
    //static constexpr char loggerName_[] = "NtupleProcessor_log";
      // TO DO: Figure out how to get this to work across classes.

  private:
    // Helper methods
    void initializeLogging();
    bool processCommandLineInput(int, char*[]);

    // Command Line Input
    bool logQuiet_;
    bool logDebug_;
    std::string procLocation_;  // Included to specify running on LPC or on personal computer.
    counter eventsToProcess_;
    std::string options_;

    // File Information
    std::vector<std::string> ntupleFileNames_;
    TChain* ntuples_;
    TreeIterator* tIter_;

    // Processing information
    std::shared_ptr<spdlog::logger> logger_;
    std::string logPrefix_;
    TimeStamp beginTime_;
    TimeStamp endTime_;
};

#endif
