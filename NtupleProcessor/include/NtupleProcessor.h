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
// Project Specific classes
#include "HistogramExtractor.h"
#include "Logger.h"
#include "RootFileManager.h"
#include "TimeStamp.h"
#include "TreeIterator.h"

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
    bool processCommandLineInput(int, char*[]);  // Processes command line options/flags.
    void initializeHistogramExtractors();   // Sets up histogram extractors using input configuration files.
    void initializeNtuples();               // Set up ntuples from file.
    void processNtuples();                  // Process ntuples using tree iterator.

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
    RootFileManager* rfManager_;

    // Processing information
    Logger logger_;
    TimeStamp beginTime_;
    TimeStamp endTime_;

    std::vector<HistogramExtractor*> hExtractors_;
};

#endif
