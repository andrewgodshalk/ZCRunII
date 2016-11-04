/*------------------------------------------------------------------------------
ControlPlotExtractor.cpp
 Created : 2016-11-02  godshalk
 Modified: 2016-11-02  godshalk
------------------------------------------------------------------------------*/

// Project Specific classes
#include "ControlPlotExtractor.h"

using std::string;
using std::to_string;

ControlPlotExtractor::ControlPlotExtractor(string n)
  : HistogramExtractor(n, "CPT", "Zll"),
    logger_("NtupleProcessor", "[CP]     ")
{
    logger_.debug("ControlPlotExtractor created.");

  // Create histogram:
    // TH1* htemp = rfManager_->createHistogram("CFT_Zll_cutFlow ; Cut Flow Table (Zll); Cuts ;; 1 ; 0 ; 10 ;     int  ; OPTIONLISTING");
    // histograms_[htemp->GetName()] = htemp;
}

void ControlPlotExtractor::process()
{ // Called per event. Processes information and fills histograms.
   logger_.trace("process() called.");
}

void ControlPlotExtractor::terminate()
{ // Function that saves the histograms and performs any final actions before processing is completed.
    logger_.trace("terminate() called.");

  // Perform closeout.
    rfManager_->close();
}
