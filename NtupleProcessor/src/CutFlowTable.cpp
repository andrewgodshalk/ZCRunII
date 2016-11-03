/*------------------------------------------------------------------------------
CutFlowTable.cpp
 Created : 2016-11-02  godshalk
 Modified: 2016-11-02  godshalk
------------------------------------------------------------------------------*/

// Project Specific classes
#include "CutFlowTable.h"

//CutFlowTable::CutFlowTable(EventHandler* e)
CutFlowTable::CutFlowTable()
  : // HistogramExtractor(e), maxStringLength_(0),
    logger_("NtupleProcessor", "[CF]       ")
{
    logger_.debug("CutFlowTable created.");
}

void CutFlowTable::process()
{ // Called per event. Processes information and fills histograms.
  if     (evt_->evtMap_.Vtype == 0) n_["Zuu"]      ++;
  else if(evt_->evtMap_.Vtype == 1) n_["Zee"]      ++;
  else if(evt_->evtMap_.Vtype == 5) n_["Vtype5"]   ++;
  else                             n_["VtypeOther"]++;
}

void CutFlowTable::terminate()
{ // Function that saves the histograms and performs any final actions before processing is completed.
    printTable();
}

void CutFlowTable::printTable()
{
  // Find max length of strings
    // for(auto &kv : n_)
    //     if(kv.first.length() > maxStringLength_)
    //         maxStringLength_ = kv.first.length();

  // Print to log.
    logger_.info(" === Cut Flow Table ================");
    for(auto &kv : n_) logger_.info("{0:>20s} : {1:10}", kv.first, kv.second);

}
