/*------------------------------------------------------------------------------
CutFlowTable.cpp
 Created : 2016-11-02  godshalk
 Modified: 2016-11-02  godshalk
------------------------------------------------------------------------------*/

// Project Specific classes
#include "CutFlowTable.h"

using std::string;
using std::to_string;

CutFlowTable::CutFlowTable(string n)
  : HistogramExtractor(n, "CFT", "Zll"),
    logger_("NtupleProcessor", "[CF]     ")
{
    logger_.debug("CutFlowTable created.");

  // Create histogram:
    // TH1* htemp = rfManager_->createHistogram("CFT_Zll_cutFlow ; Cut Flow Table (Zll); Cuts ;; 1 ; 0 ; 10 ;     int  ; OPTIONLISTING");
    // histograms_[htemp->GetName()] = htemp;
  // MOVED TO TERMINATE.
}

void CutFlowTable::process()
{ // Called per event. Processes information and fills histograms.
  // logger_.trace("process() called.");
  // Find the event weight from EH and increment each counter.
    float wt = evt_->wt_;
    if     (evt_->evtMap_.Vtype == 0) n_["VtypeZuu"]   += wt;
    else if(evt_->evtMap_.Vtype == 1) n_["VtypeZee"]   += wt;
    else if(evt_->evtMap_.Vtype == 5) n_["Vtype5"]     += wt;
    else                              n_["VtypeOther"] += wt;
}

void CutFlowTable::terminate()
{ // Function that saves the histograms and performs any final actions before processing is completed.
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
    logger_.trace("terminate() called.");
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
