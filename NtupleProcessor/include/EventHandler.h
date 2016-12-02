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
#include "SelectionProfileCollection.h"

class EventHandler
{
  public:
    EventHandler();
    ~EventHandler(){}

    void mapTree(TTree*);
    void evaluateEvent();

    EventMap* evtMap_;

    SelectionProfile* getSelectionProfile(const std::string& spStr);  // Returns SP pointer for given string.

  // Calculated Event Values.
    float wt_;  // Combined weight of the event. Defaults to 1.0.

  // Array variables mapped to objects.
    std::vector<   JetObject> jets_   ;
    std::vector<LeptonObject> leptons_;

  // Accessors
    // bool evtSatisfies(const std::string& sp) {return selectionProfiles_->getSelectionProfile("SP")->evaluate(this);}
    bool evtSatisfies(const std::string&);
    // bool jetSatisfies(const std::string& jc) {return jetSatisfies_[jc];}
    // bool lepSatisfies(const std::string& lc) {return lepSatisfies_[lc];}

  // Collections of objects satisfying given object criteria.
    // TO DO: CREATE!

  private:
  // Collection of selection profiles to evaulate each event.
    SelectionProfileCollection* selectionProfiles_;
  // Collections of object and full event eval information. Rewritten each event.
    // std::map<std::string, std::map<std::string, bool> > eval_;

  // Helper function to set up physics object lists
    void mapPhysicsObjects();
    void resetEventVariables();

    Logger logger_;
};


#endif
