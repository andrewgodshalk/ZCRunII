#ifndef GUARD_EventHandler_h
#define GUARD_EventHandler_h

/*------------------------------------------------------------------------------
   EventHandler

 Created : 2016-10-25  godshalk
 Modified: 2016-11-01  godshalk

 Class that handles physics objects from event map.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
// Submodules
#include "spdlog/spdlog.h"
// Root Classes
#include <Rtypes.h>  // Contains definitions for Root types (Float_t, Int_t, etc.)
#include <TChain.h>
#include <TLeaf.h>
// Project Specific classes
#include "Logger.h"
#include "MappedValue.h"


class EventHandler
{
  public:
    EventHandler();
    ~EventHandler(){}

    void mapTree(TTree*);
    void evaluateEvent();

  private:
    TTree *tree_;
    Logger logger_;

    // Event information
    double evtWt_;
    //std::map<

};

#endif
