/*
EventHandler.cpp

 Created : 2016-10-25  godshalk
 Modified: 2016-10-25  godshalk

*/

// Standard Libraries
// Project Specific
#include "EventHandler.h"


EventHandler::EventHandler() :
  evtMap_(), logger_("NtupleProcessor", "[EH]     ")
{
    logger_.debug("EventHandler Created.");
}

void EventHandler::mapTree(TTree* tree)
{ // Map the input tree to variables locally
    logger_.trace("mapTree(): called");
    evtMap_.mapTree(tree);
}

void EventHandler::evaluateEvent()
{ // Use tree map to set up physics objects
    logger_.trace("evaluateEvent(): called");

    // Take variables from EventMap, input into this class.
    // Variables that don't need any modification
    // Variables that are mapped onto structs (jets, leptons)
}
