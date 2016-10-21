/*------------------------------------------------------------------------------
NtupleProcessor.cpp
 Created : 2015-09-14  godshalk
 Modified: 2016-10-17  godshalk
------------------------------------------------------------------------------*/

// Standard Libraries
#include <iostream>
// Submodules
#include "spdlog/spdlog.h"
// Project Specific classes
#include "NtupleProcessor.h"

using std::cout;   using std::endl;
using std::string;

typedef unsigned long counter;

int main(int argc, char* argv[])
{  // Set up logging
    try
    {
         //Multithreaded console logger(with color support)
        auto console = spdlog::stdout_color_mt("console");
        console->info("Welcome to spdlog!") ;
        console->info("An info message example {} ..", 1);

        // Create basic file logger (not rotated)
        auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
        my_logger->info("Some log message");

        // create a file rotating logger with 5mb size max and 3 rotated files
        auto file_logger = spdlog::rotating_logger_mt("file_logger", "myfilename", 1024 * 1024 * 5, 3);
        file_logger->info("Hello spdlog {} {} {}", 1, 2, "three");
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log failed: " << ex.what() << std::endl;
    }

   // SET UP NTUPLEPROCESSOR
    NtupleProcessor nProc (argc, argv);
    return 0;
}

NtupleProcessor::NtupleProcessor(int argc, char* argv[])
  : ntupleFileNames_(), tIter_(), eventsToProcess_(-1), o_location_("")
{
  // Class initialization
    beginTime_.update();

  // Handle file/tree input. (TEMPORARY: will eventually be replaced w/ input options.)
    if(argc>1) o_location_ = argv[1];
    if(o_location_=="lpc")   // If an option specifying that the program is runnong on LPC is specified, set the appropriate variables.
    {
        ntupleFileNames_.push_back("root://cmseos.fnal.gov//store/user/leptonjets/noreplica/godshalk/ZJNtuples_RunII/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_2016-04_1of7.root/tree");
        ntupleFileNames_.push_back("root://cmseos.fnal.gov//store/user/leptonjets/noreplica/godshalk/ZJNtuples_RunII/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_2016-04_2of7.root/tree");
    }
    else  // Ortherwise, run on a file from my local machine.
        ntupleFileNames_.push_back("/home/godshalk/Work/2016-05-24_ZCAnalysisRunII/DY_2015Cond_TestFile_v1.root/tree");

  // Set up tree chain.
    ntuples_ = new TChain("ntuples_", "Ntuples");
      // TO DO: Add ntuple names/labels/whatever as info for object.
    for(string fn : ntupleFileNames_)
      ntuples_->Add(fn.c_str());

    eventsToProcess_ = 1000;

  // INITIAL OUTPUT
    cout << "\n\n"
            "================================================================================\n"
            "===NtupleProcessor==============================================================\n"
            "  Processing Begun: " << beginTime_.log_str()                               << "\n"
            "  Number of events to process: " << eventsToProcess_                        << "\n"
            << endl;

  // Process the tree.
    if(eventsToProcess_>0) ntuples_->Process(&tIter_, "", eventsToProcess_);
    else ntuples_->Process(&tIter_);

  // CLOSING OUTPUT.
    endTime_.update();
    cout << "\n"
            "  Completion time: " << endTime_.log_str() << "\n"
            "===NtupleProcessor - COMPLETE===================================================\n"
            "================================================================================\n"
         << endl;


  //PSEUDO
  // Input configuration for handling Ntuple
  // - Ntuple
  //    - Location
  //    - Plotting information
  //    - Type (DY, SIM, etc)
  // - Plots that need to be created and filled
  //    - Plot identifier (use separate files w/ unique directory
  //    - Selection criteria
  //    - Fill value
  //    - Any functions
  // - Output location

  // Set up TreeIterator and EventHandler to deal with mapping and configuring the tree.

  // Run Everything

  // Output information

  // Clean up
    delete ntuples_;

}
