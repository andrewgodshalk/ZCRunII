#ifndef GUARD_CutFlowTable_h
#define GUARD_CutFlowTable_h

/*------------------------------------------------------------------------------
   CutFlowTable Class

 Created : 2016-11-02  godshalk
 Modified: 2016-11-02  godshalk

 Inherits from HistogramExtractor. Counts events passing each step of selection.
 Outputs counts to histogram.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
#include <string>
// Root Classes
// #include <TDirectory.h>
// #include <TH1.h>
// Project Specific classes
#include "EventHandler.h"
#include "HistogramExtractor.h"
#include "Logger.h"


class CutFlowTable : public HistogramExtractor
{
  public:
    CutFlowTable(EventHandler*);
    ~CutFlowTable(){}

    void process();     // Called per event. Processes information and fills histograms.
    void terminate();   // Function that saves the histograms and performs any final actions before processing is completed.

  private:
    std::map<std::string, unsigned int> n_;   // Counts
    unsigned int maxStringLength_;
    Logger logger_;

    void printTable();  // Prints table to log.

};

#endif
