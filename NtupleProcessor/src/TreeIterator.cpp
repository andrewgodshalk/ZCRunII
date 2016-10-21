/*
TreeIterator.cpp

 Created : 2015-05-14  godshalk
 Modified: 2016-10-19  godshalk


 2016-10-19 -
 2016-10-16 - Transferred, slightly modified to work with new version of NtupleProcessor

*/

#include <iomanip>
#include <iostream>
#include "../include/TreeIterator.h"

using std::cout;  using std::endl;   using std::setw;   using std::string;


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

    cout << " Processing New Tree (# Entries: " << nEntries_ << ")" << endl;

  // Initialize Event Handler, adding the criteria of each HistoMaker to it's list of criteria.
    //eHandler.mapTree(fChain);
  // TEST
    fChain->SetBranchAddress("Vtype", &m_Vtype_);
}


Bool_t TreeIterator::Notify()
{
  // TO DO - Set up to work w/ TChain.
  //  Init(fChain);
    return kTRUE;
}


Bool_t TreeIterator::Process(Long64_t entry)
{
  // Load current entry
    fChain->GetTree()->GetEntry(entry);
    nEntriesProcessed_++;
    if(entry%100000 == 0 || (unsigned long) entry==finalEntry_) cout << "  #" << entry << endl;

  // Evaluate selection profiles.
  // TEST
    // if(m_Vtype_==0) cout << "    Entry " << entry << " == Zuu" << endl;

  // Call each HistogramMakers

    return true;
}

void TreeIterator::SlaveTerminate(){}
void TreeIterator::Terminate(){}
