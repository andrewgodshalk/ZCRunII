/*------------------------------------------------------------------------------
CutFlowTable.cpp
 Created : 2016-11-02  godshalk
 Modified: 2016-12-01  godshalk
------------------------------------------------------------------------------*/

// Project Specific classes
#include "CutFlowTable.h"

using std::pair;
using std::string;
using std::vector;
using std::to_string;

CutFlowTable::CutFlowTable(string n, vector<string>& spList)
  : HistogramExtractor(n, "CFT", spList[0]),
    logger_("NtupleProcessor", "[CF]     ")
{   logger_.debug("CutFlowTable created.");
  // Set up with a list of selection profiles to count.
  // TO DO: Set it up to auto-generate SPs to count.
    vector<string>::const_iterator sp = spList.begin();
    for(vector<string>::const_iterator sp = spList.begin(); sp!=spList.end(); ++sp)
    {   logger_.trace("Adding to the cut flow list: {}", *sp);
        n_[*sp] = 0;
    }
}

void CutFlowTable::setEventHandler(EventHandler* eh)
{ // Overridden version of HE's setEventHandler. A special case to add extra SPs to master list.
    logger_.trace("setEventHandler() called.");
    HistogramExtractor::setEventHandler(eh);  // Call base class function.
  // Set up SPs for each specified count.
    for(auto& sp : n_) spPtr_[sp.first] = evt_->getSelectionProfile(sp.first);
}

void CutFlowTable::process()
{ // Called per event. Processes information and fills histograms.
    logger_.trace("process() called.");
  // Find the event weight from EH and increment each counter.
    float wt = evt_->wt_;
  // Cycle through profiles to check.
    // for( auto& sp : n_) if(evt_->evtSatisfies(sp.first)) sp.second += wt;
    for( auto& sp : spPtr_) if(sp.second->evaluate()) n_[sp.first] += wt;
}

void CutFlowTable::terminate()
{ // Function that saves the histograms and performs any final actions before processing is completed.
    logger_.trace("terminate() called.");

  // Create histogram
    int hSize = n_.size();
    string hConfigStr = string("CFT_Zll_cutFlow, Cut Flow Table (Zll), Cuts, Counts, 1, 0,")+to_string(hSize);
    TH1* htemp = rfManager_->createHistogram(hConfigStr);
    histograms_[htemp->GetName()] = htemp;

  // Set bin name and contents for each bin.
    int currentHBin=1;   // Visible TH1 bins start at 1. 0 is underflow.
    for( const auto &keyAndCount : n_ )  // For every key and value in n_...
    {   htemp->GetXaxis()->SetBinLabel(currentHBin, keyAndCount.first.c_str());
        htemp->SetBinContent(          currentHBin, keyAndCount.second       );
        currentHBin++;
    }
  // Set some drawing options.
    htemp->SetOption("TEXT45");

  // Perform closeout.
    printTable();
    rfManager_->close();
}

void CutFlowTable::printTable()
{
  logger_.trace("printTable() called.");

  // Find max length of strings
    unsigned int maxStringLength = 0;
    unsigned int maxCountLength  = 0;
    for(auto &kv : n_)
    {   if(               kv.first  .length() > maxStringLength) maxStringLength =                kv.first  .length();
        if(to_string((int)kv.second).length() > maxCountLength ) maxCountLength  = to_string((int)kv.second).length();
    } // Second cast to int to get number of digits after decimal.
    maxCountLength+=2;  // Add 2 digits for tenths decimal.
    // logger_.trace("printTable(): maxStringLength = {}", maxStringLength);
    // logger_.trace("printTable(): maxCountLength  = {}", maxCountLength);

  // Print to log.
    logger_.info(" === Cut Flow Table ================");
    string countOutputFormat = "";
    countOutputFormat += "{0:>"+to_string(maxStringLength)+"s} : {1:"+to_string(maxCountLength)+".1f}";
    for(auto &kv : n_) logger_.info(countOutputFormat, kv.first, kv.second);
}
