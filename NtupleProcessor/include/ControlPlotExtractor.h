#ifndef GUARD_ControlPlotExtractor_h
#define GUARD_ControlPlotExtractor_h

/*------------------------------------------------------------------------------
   ControlPlotExtractor Class

 Created : 2016-11-04  godshalk
 Modified: 2016-11-04  godshalk

 TEXT HERE

 2016-11-03

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


class ControlPlotExtractor : public HistogramExtractor
{
  public:
    ControlPlotExtractor(std::string);
    ~ControlPlotExtractor(){}

    void process();     // Called per event. Processes information and fills histograms.
    void terminate();   // Function that saves the histograms and performs any final actions before processing is completed.

  private:
    std::map<std::string, float> n_;   // Counts
    Logger logger_;
};

#endif
