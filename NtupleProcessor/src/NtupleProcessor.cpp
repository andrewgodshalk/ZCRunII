/*------------------------------------------------------------------------------
NtupleProcessor.cpp
 Created : 2015-09-14  godshalk
 Modified: 2016-10-17  godshalk
------------------------------------------------------------------------------*/

// Standard Libraries
#include <iostream>
#include <memory>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
// Boost Libraries
// #include <boost/program_options/options_description.hpp>
// #include <boost/program_options/parsers.hpp>
// #include <boost/program_options/variables_map.hpp>
// Project Specific classes
#include "NtupleProcessor.h"
#include "TimeStamp.h"

using std::string;   using std::vector;

typedef unsigned long counter;

// MAIN() - Used only to pass on input to NtupleProcessor class.
int main(int argc, char* argv[])
{ // Set up NtupleProcessor
    NtupleProcessor nProc (argc, argv);
    return 0;
}

NtupleProcessor::NtupleProcessor(int argc, char* argv[])
  : logQuiet_(false), logDebug_(false), ntupleFileNames_(), eventsToProcess_(-1), o_location_("")
{
  // Class initialization
    beginTime_.update();
    processCommandLineInput(argc, argv);
    initializeLogging();
    tIter_ = new TreeIterator();

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

    logger_->info("{} NtupleProcessor initizated {}"  , logPrefix_, beginTime_.log_str());
    logger_->info("{} Number of events to process: {}", logPrefix_, eventsToProcess_);

  // Process the tree.
    if(eventsToProcess_>0) ntuples_->Process(tIter_, "", eventsToProcess_);
    else ntuples_->Process(tIter_);

  // CLOSING OUTPUT.
    endTime_.update();
    logger_->info("{} NtupleProcessor complete {}", logPrefix_, endTime_.log_str());

  // Clean up
    delete ntuples_;

}

void NtupleProcessor::initializeLogging()
{ // Set up logging
  // TO DO: Add directory creation? Boost libraries not loaded, so would need to do with unix-based commands.

  // Set up file name and location.
    string logDir = "logs/";
    string logFilename = "NtupleProcessor_";
    logFilename += beginTime_.fn_str() + ".log";

  // Log format
    string logFormat = "%v";

    try
    { // Create sinks (outputs) for loggers
        vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::simple_file_sink_st>((logDir+logFilename).c_str()));
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
        sinks.push_back(std::make_shared<spdlog::sinks::stderr_sink_st>());

      // Create logger, to be accessed globally from all classes.
        logger_ = std::make_shared<spdlog::logger>("NtupleProcessor_log", begin(sinks), end(sinks));

      // Set logger and sink levels.
        // Normal mode - file, stdout at info, stderr at err
        // Debug -> file at trace, stdout at debug, add time to log message
        // Quiet -> silences stdout
        logger_ ->set_level(spdlog::level::info);
        sinks[0]->set_level(spdlog::level::info);
        sinks[1]->set_level(spdlog::level::info);
        sinks[2]->set_level(spdlog::level::err );
        if(logDebug_)
        {
            logFormat = "[%Y-%m-%d %H:%M:%S.%e|%l] : %v";
            logger_ ->set_level(spdlog::level::trace);
            sinks[0]->set_level(spdlog::level::trace);
            sinks[1]->set_level(spdlog::level::debug);
        }
        if(logQuiet_)
            sinks[1]->set_level(spdlog::level::err);

      // Set log format and register logger globally
        logger_->set_pattern(logFormat.c_str());
        spdlog::register_logger(logger_);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log failed: " << ex.what() << std::endl;
    }
    logPrefix_ = (logDebug_ ? "[NP]" : "");
}

void NtupleProcessor::processCommandLineInput(int argc, char* argv[])
{
    eventsToProcess_ = 1000;
    logQuiet_ = true;
    logDebug_ = false;
}
