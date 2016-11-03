/*
TreeIterator.cpp

 Created : 2015-05-14  godshalk
 Modified: 2016-10-24  godshalk


 2016-10-24 - Moved constructor into source.
 2016-10-16 - Transferred, slightly modified to work with new version of NtupleProcessor

*/

#include <iostream>
#include "TreeIterator.h"
#include "CutFlowTable.h"

using std::string;

TreeIterator::TreeIterator()
  : fChain(0), logger_("NtupleProcessor", "[TI]   "), nEntries_(0), finalEntry_(0), nEntriesProcessed_(0)
{
    logger_.debug("TreeIterator Created.");
    evt_ = new EventHandler();

  // Set up histogram extractors
    // TO DO: Decide where to set these up, how to configure.
    hExtractors_.push_back(new CutFlowTable(evt_));
}

void TreeIterator::Begin(TTree * /*tree*/){}


void TreeIterator::SlaveBegin(TTree * /*tree*/)
{
  // Initialize log, counters
    nEntries_          = 0;
    nEntriesProcessed_ = 0;
}


void TreeIterator::Init(TTree *tree)
{
  // TO DO: Set up to work with TChain.
  //   Seems to call at beginning of chain only, not at beginning of individual trees.
  // Initialize the current tree.
    if (!tree) return;
    fChain = tree;              // Commented, don't think I need to access tree information outside of this function.
    fChain->SetMakeClass(1);    // ??? Can't seem to get a good answer about what this is.
                                //    I think it recreates classes stored in the root tree as opposed to just mapping variables from the object.
    nEntries_   = tree->GetEntries();
    finalEntry_ = tree->GetEntries()-1;

    logger_.info("Processing New Tree (# Entries: {})", nEntries_);

  // Initialize Event Handler, adding the criteria of each HistoMaker to it's list of criteria.
    evt_->mapTree(fChain);
}

Bool_t TreeIterator::Notify()
{
  //  Init(fChain);
  // TO DO - Set up to work w/ TChain.
    return kTRUE;
}

Bool_t TreeIterator::Process(Long64_t entry)
{
  // Load current entry
    fChain->GetTree()->GetEntry(entry);

  // Set up status outputs
    logger_.trace("#{}:", nEntriesProcessed_);
    if(nEntriesProcessed_%100000 == 0 || nEntriesProcessed_==finalEntry_) logger_.info("#{}", nEntriesProcessed_);

  // Evaluate selection profiles.
    evt_->evaluateEvent();

  // Call each HistogramExtractors
    for( HistogramExtractor* h: hExtractors_ ) h->process();

    nEntriesProcessed_++;
    return true;
}

void TreeIterator::SlaveTerminate()
{
    for( HistogramExtractor* h: hExtractors_ ) h->terminate();
}

void TreeIterator::Terminate(){}
