#ifndef GUARD_EventHandler_h
#define GUARD_EventHandler_h

/*------------------------------------------------------------------------------
   EventHandler

 Created : 2016-10-25  godshalk
 Modified: 2016-10-25  godshalk

 Class that handles physics objects from event map.

  2016-11-02 - Added Jet/LeptonObjects and mapPhysicsObjects() to initialize them.
------------------------------------------------------------------------------*/

// Standard Libraries
#include <vector>
// Root Classes
#include <TChain.h>
// Project Specific classes
#include "EventMap.h"
#include "Logger.h"
#include "JetObject.h"
#include "LeptonObject.h"

class EventHandler
{
  public:
    EventHandler();
    ~EventHandler(){}

    void mapTree(TTree*);
    void evaluateEvent();

    EventMap evtMap_;

  // Array variables mapped to objects.
    std::vector<   JetObject> jets_   ;
    std::vector<LeptonObject> leptons_;

  private:
    Logger   logger_;

  // Helper function to set up physics object lists
    void mapPhysicsObjects();


};


#endif
