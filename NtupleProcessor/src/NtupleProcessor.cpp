/*------------------------------------------------------------------------------
NtupleProcessor.cpp
 Created : 2015-09-14  godshalk
 Modified: 2016-11-21  godshalk
------------------------------------------------------------------------------*/

// Standard Libraries
#include <iostream>
#include <memory>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
// Boost Libraries
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
// ROOT Libraries
//#include "TApplication.h"
// Project Specific classes
#include "ControlPlotExtractor.h"
#include "CutFlowTable.h"
#include "NtupleProcessor.h"


using std::cout;     using std::endl;
using std::string;   using std::vector;

typedef unsigned long counter;
namespace po = boost::program_options;

// MAIN() - Used only to pass on input to NtupleProcessor class.
int main(int argc, char* argv[])
{ // Set up NtupleProcessor
  // Set up root environment
  // Needed to make sure ROOT libraries "link correctly. Receive seg faults while trying to use TH2F in LeptonSFData otherwise.
  // Recommendation found at link: https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=18101&p=76968#p76968
    //TApplication a("a", 0, 0); // just to make sure that the autoloading of ROOT libraries works
    // Commented out again because it was causing problems on LPC. Seems to work okay for now.

  // Try/catch set up for the sole pupose of catching false return on
    try { NtupleProcessor nProc (argc, argv); }
    catch(const char* msg)
    {
        if(string(msg) != "help") std::cerr << msg << endl;
        return 1;
    }
    return 0;
}

NtupleProcessor::NtupleProcessor(int argc, char* argv[])
  : logQuiet_(false), logDebug_(false), procLocation_(""), eventsToProcess_(0), options_(""), ntupleFileNames_(), logger_("NtupleProcessor", "[NP] ")
{ // Class initialization
    beginTime_.update();
    if(!processCommandLineInput(argc, argv)) throw("help");
    logger_.info("");
    logger_.info("====================================================================================================");
    logger_.info("===Initializing===");
    logger_.debug("NtupleProcessor Created.");

  // Initialize Helper Classes, histogram makers, ntuples.
    initializeNtuples();
    initializeHistogramExtractors();
    tIter_ = new TreeIterator(hExtractors_);

    logger_.info("NtupleProcessor initizated {}", beginTime_.log_str());
    if(eventsToProcess_>0) logger_.info("Number of events to process: {}", eventsToProcess_);

  // Process the tree.
    processNtuples();

  // Terminate histogram extractors and print closing output.
    logger_.info("");
    for( HistogramExtractor* h: hExtractors_ ) h->terminate();

  // Print closing output.
    endTime_.update();
    logger_.info("");
    logger_.info("===NtupleProcessor complete {}===", endTime_.log_str());
    logger_.info("====================================================================================================");

  // Clean up
    delete ntuples_;
}

bool NtupleProcessor::processCommandLineInput(int argc, char* argv[])
{ // Process command line input.
  // Returns false if help is called or input is invalid.
    logger_.trace("processCommandLineInput() called.");

  // TEMP: Set up ntuple object
    ntupleName_ = "dy";

  // Set up options
    po::options_description opDesc("NtupleProcessor options", 150);
    opDesc.add_options()
        ("help"     ",h",                                                         "Print help message"                                   )
        ("debug"    ",d",                                                         "Increased output for debugging purposes."             )
        ("quiet"    ",q",                                                         "Minimal console output. Output still logged in file." )
        ("location" ",l",  po::value<string>()->default_value(procLocation_    ), "Location of processing (currently either CUJO or LPC)")
        ("maxevents"",m",  po::value<int>()   ->default_value(eventsToProcess_ ), "Number of events to process"                          )
        ("options"  ",o",  po::value<string>()->default_value(options_         ), "Misc. options"                                        )
    ;
    po::variables_map cmdInput;
    po::store(po::parse_command_line(argc, argv, opDesc), cmdInput);
    po::notify(cmdInput);
    if(cmdInput.count("help"))
    {   cout << "\n" << opDesc << endl; return false; }

  // Extract and store variables.
    if(cmdInput.count("location"))
        procLocation_ = cmdInput["location"].as<string>();
    logDebug_         = cmdInput.count("debug");
    logQuiet_         = cmdInput.count("quiet");
    eventsToProcess_  = ( cmdInput.count("maxevents") ? cmdInput["maxevents"].as<int>() : -1);

    if(logDebug_)
    {   logger_.setFormat("[%Y-%m-%d %H:%M:%S.%e|%l]%v");
        logger_.setDebug(true);
    }
    if(logQuiet_)
        logger_.setQuiet(true);
    return true;
}

void NtupleProcessor::initializeNtuples()
{ // Set up ntuples from file.
    logger_.trace("initializeNtuples() called.");

  // Handle file/tree input. (TEMPORARY: will eventually be replaced w/ input options.)
    if(procLocation_=="LPC")   // If an option specifying that the program is runnong on LPC is specified, set the appropriate variables.
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
    {   ntuples_->Add(fn.c_str());
        logger_.info("Adding ntuple file to chain: {}", fn);
    }
}

void NtupleProcessor::processNtuples()
{ // Process ntuples using tree iterator.
    logger_.trace("processNtuples() called.");

    logger_.info("");
    logger_.info("====================================================================================================");
    logger_.info("===Beginning Event Processing===");

    if(eventsToProcess_>0) ntuples_->Process(tIter_, "", eventsToProcess_);
    else ntuples_->Process(tIter_);

    logger_.info("");
    logger_.info("===End Event Processing===");
    logger_.info("====================================================================================================");
}

void NtupleProcessor::initializeHistogramExtractors()
{ // Sets up histogram extractors using input configuration files.
    logger_.trace("initializeHistogramExtractors() called.");

  // HARDCODED cutFlowTable initializer
    vector<string> spForCounting =
    { "jnTn",         // NULL CHOICE
      "Zllf071c111Le24sfn",
      "Zllf071c111Le24sfnMETJ1HFCSVT",
      "jg", "js", "jn",
      "Te", "Tu", "Tl", "Tee", "Tuu", "Teu", "Tll",
    };
    hExtractors_.push_back(new CutFlowTable(ntupleName_, spForCounting));

  // HARDCODED controlPlotExtractor initialization
    hExtractors_.push_back(new ControlPlotExtractor(ntupleName_));

}
