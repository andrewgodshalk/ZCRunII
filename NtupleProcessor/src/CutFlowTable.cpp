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
    TH1* htemp = rfManager_->createHistogram("CFT_Zll_cutFlow ; Cut Flow Table (Zll); Cuts ;; 1 ; 0 ; 10 ;     int  ; OPTIONLISTING");
    histograms_[htemp->GetName()] = htemp;
}

void CutFlowTable::process()
{ // Called per event. Processes information and fills histograms.
  // logger_.trace("process() called.");
  if     (evt_->evtMap_.Vtype == 0) n_["VtypeZuu"]  ++;
  else if(evt_->evtMap_.Vtype == 1) n_["VtypeZee"]  ++;
  else if(evt_->evtMap_.Vtype == 5) n_["Vtype5"]    ++;
  else                              n_["VtypeOther"]++;
}

void CutFlowTable::terminate()
{ // Function that saves the histograms and performs any final actions before processing is completed.
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
    {   if(          kv.first  .length() > maxStringLength) maxStringLength =           kv.first  .length();
        if(to_string(kv.second).length() > maxCountLength ) maxCountLength  = to_string(kv.second).length();
    }
    // logger_.trace("printTable(): maxStringLength = {}", maxStringLength);
    // logger_.trace("printTable(): maxCountLength  = {}", maxCountLength);

  // Print to log.
    logger_.info(" === Cut Flow Table ================");
    string countOutputFormat = "";
    countOutputFormat += "{0:>"+to_string(maxStringLength)+"s} : {1:"+to_string(maxCountLength)+"}";
    for(auto &kv : n_) logger_.info(countOutputFormat, kv.first, kv.second);
}
