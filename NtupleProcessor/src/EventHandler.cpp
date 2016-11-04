/*
EventHandler.cpp

 Created : 2016-10-25  godshalk
 Modified: 2016-11-02  godshalk

*/

// Standard Libraries
// Project Specific
#include "EventHandler.h"

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
    //logger_.trace("evaluateEvent(): called");
  // Reset working variables.
    resetEventVariables();
    // Take variables from EventMap, input into this class.
    // Variables that don't need any modification
    // Variables that are mapped onto structs (jets, leptons)
}

void EventHandler::mapPhysicsObjects()
{ // Helper Function. Helps create vectors of mapped physics objects.
    logger_.trace("mapPhysicsObjects(): called");
    for (size_t i = 0; i < EventMap::maxNumJets_; i++)    jets_.push_back(   JetObject(&evtMap_, i));
    for (size_t i = 0; i < EventMap::maxNumLeps_; i++) leptons_.push_back(LeptonObject(&evtMap_, i));
}

void EventHandler::resetEventVariables()
{ // Called at beginning of evaluateEvent() to reset calculated variables to their initial, default values.
    wt_ = 1.0;
}
