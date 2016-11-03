#ifndef GUARD_HistogramExtractor_h
#define GUARD_HistogramExtractor_h

/*------------------------------------------------------------------------------
   HistogramExtractor Virtual Class

 Created : 2015-05-14  godshalk
 Modified: 2016-11-02  godshalk

 Virtual class used as a base for classes that extract information from ntuples
 in the form of ROOT histograms.

 Designed to save the histograms as output to a folder in a root object.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
// Root Classes
#include <TDirectory.h>
#include <TH1.h>
// Project Specific classes
#include "Logger.h"


class HistogramExtractor {
  public:
    HistogramExtractor(EventHandler* eh) : evt_(eh) {}
    virtual ~HistogramExtractor(){}

    virtual void process(){}     // Called per event. Processes information and fills histograms.
    virtual void terminate(){}   // Function that saves the histograms and performs any final actions before processing is completed.

  protected:
    EventHandler* evt_;   // Contains event information (selection profile, mapped variables, etc.)

  // Histogram collection
//    TDirectory* hDir;            // Root file directory where histograms are stored.
//    std::map<TString, TH1*> h;   // List of histograms that will be filled by the fillHistos function

};

#endif
