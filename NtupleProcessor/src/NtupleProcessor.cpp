/*------------------------------------------------------------------------------
NtupleProcessor.cpp
 Created : 2015-09-14  godshalk
 Modified: 2016-10-17  godshalk
------------------------------------------------------------------------------*/

#include <iostream>
// Project Specific classes
#include "../include/NtupleProcessor.h"

using std::cout;   using std::endl;
using std::string;

typedef unsigned long counter;

NtupleProcessor::NtupleProcessor(int argc, char* argv[])
  : ntupleFileNames_(),
    tIter_(),
    eventsToProcess_(-1)
{
  // Class initialization

    beginTime_.update();

  // Handle file/tree input. (TEMPORARY: will eventually be replaced w/ input options.)
    ntupleFileNames_.push_back("/home/godshalk/Work/2016-05-24_ZCAnalysisRunII/DY1J_2015Cond_TestFile_v1.root/tree");

  // Set up tree chain.
    ntuples_ = new TChain("ntuples_", "Ntuples");
      // TO DO: Add ntuple names/labels/whatever as info for object.
    for(string fn : ntupleFileNames_)
      ntuples_->Add(fn.c_str());

//    ntupleFile_ = TFile::Open(ntupleFileName_.c_str(), "READ");
//    ntuple_ = (TTree*) ntupleFile_->Get("tree");
    eventsToProcess_ = 1000;

  // INITIAL OUTPUT
    cout << "\n\n"
            "================================================================================\n"
            "===NtupleProcessor==============================================================\n"
            "  Processing Begun: " << beginTime_.log_str()                               << "\n"
//            "  Files : " << ntupleFileName_                                               << "\n"
//            "  Trees : " << ntuples_->GetName()                                           << "\n"
            "  Number of events to process: " << eventsToProcess_                        << "\n"
         << endl;

  // Process the tree.
    ntuples_->Process(&tIter_, "", eventsToProcess_);

  // CLOSING OUTPUT.
    endTime_.update();
    cout << "\n"
            "  Completion time: " << endTime_.log_str() <<      "\n"
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
//    ntupleFile_->Close();
//    delete ntupleFile_;

}
