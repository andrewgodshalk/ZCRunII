#ifndef GUARD_CutFlowTable_h
#define GUARD_CutFlowTable_h

/*------------------------------------------------------------------------------
   CutFlowTable Class

 Created : 2016-11-02  godshalk
 Modified: 2016-11-04  godshalk

 Inherits from HistogramExtractor. Counts events passing each step of selection.
 Outputs counts to histogram.

 2016-11-04 - Set up histogram output.
            - Set up automatic length formatting on printTable()
 2016-11-02 - Set up with basic log output of counts.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
#include <string>
#include <utility>
#include <vector>
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
    CutFlowTable(std::string, std::vector<std::string>&);
    ~CutFlowTable(){}

    void process();     // Called per event. Processes information and fills histograms.
    void terminate();   // Function that saves the histograms and performs any final actions before processing is completed.
    void setEventHandler(EventHandler*);  // Overridden version of HE's setEventHandler. A special case to add extra SPs to master list.

  private:
    std::map<std::string, float> n_;   // Counts
    std::map<std::string, SelectionProfile*> spPtr_;   // Pointers to selection profiles
      // Currently not implemented, since event handler owns pointers and isn't set in HE until after construction.
      // Could easily override HE.setEventHandler to include this, but currently no need to dig for individual SPs.
    Logger logger_;

    void printTable();  // Prints table to log.

};

#endif
