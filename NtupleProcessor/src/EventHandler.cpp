/*
EventHandler.cpp

 Created : 2016-10-25  godshalk
 Modified: 2016-11-02  godshalk

*/

// Standard Libraries
#include <string>
#include <vector>
// Root Classes
#include <TChain.h>
// Project Specific
#include "EventHandler.h"

using std::string;
using std::vector;

EventHandler::EventHandler() :
  evtMap_(), logger_("NtupleProcessor", "[EH]   ")
{
    logger_.debug("EventHandler Created.");
}

void EventHandler::mapTree(TTree* tree)
{ // Map the input tree to variables locally
    logger_.trace("mapTree(): called");
    evtMap_.mapTree(tree);
    mapPhysicsObjects();
}

void EventHandler::evaluateEvent()
{ // Use tree map to set up physics objects
    logger_.trace("evaluateEvent(): called");

  // Reset working variables.
    resetEventVariables();

  // Evaluate SelectionProfiles.
    // for( auto &kv : selectionProfiles_)
    // {   logger_.trace("Evaluating selection profile: {}", kv.first);
    //     kv.second->evaluateEvent(this);
    // }
}

void EventHandler::mapPhysicsObjects()
{ // Helper Function. Helps create vectors of mapped physics objects.
    logger_.trace("mapPhysicsObjects(): called");
    for (size_t i = 0; i < EventMap::maxNumJets_; i++)    jets_.push_back(   JetObject(&evtMap_, i));
    for (size_t i = 0; i < EventMap::maxNumLeps_; i++) leptons_.push_back(LeptonObject(&evtMap_, i));
}

void EventHandler::resetEventVariables()
{ // Called at beginning of evaluateEvent() to reset calculated variables to their initial, default values.
  // Reset event weight.
    wt_ = 1.0;
  // Reset vectors containing valid object pointers.
    //for( auto &kv : lepCriteria_) kv.second.clear();
}

SelectionProfile* EventHandler::getSelectionProfile(std::string spStr)
{ // Returns a pointer to an SP. If it doesn't exist, it creates it based on the given string.
    logger_.debug("getSelectionProfile() called for {}", spStr);

  // Let the SelectionProfileCollection handle this mess.
    return selectionCriteria_.getSelectionProfile(spStr);
}
