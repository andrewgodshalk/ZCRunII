#ifndef GUARD_CutFlowTable_h
#define GUARD_CutFlowTable_h

/*------------------------------------------------------------------------------
   CutFlowTable Class

 Created : 2016-11-02  godshalk
 Modified: 2016-11-03  godshalk

 Inherits from HistogramExtractor. Counts events passing each step of selection.
 Outputs counts to histogram.

 2016-11-03 - Set up histogram output.
            - Set up automatic length formatting on printTable()
 2016-11-02 - Set up with basic log output of counts.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
#include <string>
// ROOT Libraries
#include <TH1.h>
// Project Specific classes
#include "EventHandler.h"
#include "HistogramExtractor.h"
#include "Logger.h"


class CutFlowTable : public HistogramExtractor
{
  public:
    // CutFlowTable(EventHandler*);
    CutFlowTable(std::string);
    ~CutFlowTable(){}

    void process();     // Called per event. Processes information and fills histograms.
    void terminate();   // Function that saves the histograms and performs any final actions before processing is completed.

  private:
    std::map<std::string, float> n_;   // Counts
    Logger logger_;

    void printTable();  // Prints table to log.

};

#endif
