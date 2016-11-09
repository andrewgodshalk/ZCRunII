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
#include <map>
#include <string>
#include <vector>
// Root Classes
#include <TChain.h>
// Project Specific classes
#include "EventMap.h"
#include "JetObject.h"
#include "LeptonObject.h"
#include "Logger.h"
#include "SelectionProfile.h"

class EventHandler
{
  public:
    EventHandler();
    ~EventHandler(){}

    void mapTree(TTree*);
    void evaluateEvent();

    EventMap evtMap_;

    SelectionProfile* getSelectionProfile(std::string spStr);  // Returns SP pointer for given string.
      // Creates the SP if it isn't already in its set.

  // Calculated Event Values.
    float wt_;  // Combined weight of the event. Defaults to 1.0.

  // Array variables mapped to objects.
    std::vector<   JetObject> jets_   ;
    std::vector<LeptonObject> leptons_;

  private:
    Logger   logger_;

  // List of selection profiles to evaulate each event.
    std::map<std::string, SelectionProfile*> selectionProfiles_;
    std::map<std::string, std::vector<LeptonObject*> > lepCriteria_;

  // Helper function to set up physics object lists
    void mapPhysicsObjects();
    void resetEventVariables();

};


#endif
