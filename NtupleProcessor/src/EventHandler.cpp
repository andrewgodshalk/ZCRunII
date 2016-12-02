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

EventHandler::EventHandler()
  : evtMap_(new EventMap()), selectionProfiles_(new SelectionProfileCollection()),
    logger_("NtupleProcessor", "[EH]   ")
{   logger_.debug("EventHandler Created."); }

void EventHandler::mapTree(TTree* tree)
{ // Map the input tree to variables locally
    logger_.trace("mapTree(): called");
    evtMap_->mapTree(tree);
    mapPhysicsObjects();
}

void EventHandler::evaluateEvent()
{ // Use tree map to set up physics objects
    logger_.trace("evaluateEvent(): called");

  // Reset working variables.
    resetEventVariables();

  // Evaluate selection profiles and individual objects
    selectionProfiles_->evaluate(this);

  // Make lists of individual objects that pass selection: Leptons, (HF)Jets
  // Evaluate SelectionProfiles that are per-Event: JSON, Dilepton, MET, number of jets, HFJets, Leptons
    //for( auto &kv : selectionProfiles_)
    //{   logger_.trace("Evaluating selection profile: {}", kv.first);
    //    kv.second->evaluateEvent(this);
    //}
}

bool EventHandler::evtSatisfies(const std::string& sp)
{   logger_.trace("evtSatisfies({})", sp);
    return selectionProfiles_->getSelectionProfile(sp)->evaluate(NULL);
}

void EventHandler::mapPhysicsObjects()
{ // Helper Function. Helps create vectors of mapped physics objects.
    logger_.trace("mapPhysicsObjects(): called");
    for (size_t i = 0; i < EventMap::maxNumJets_; i++)    jets_.push_back(   JetObject(evtMap_, i));
    for (size_t i = 0; i < EventMap::maxNumLeps_; i++) leptons_.push_back(LeptonObject(evtMap_, i));
}

void EventHandler::resetEventVariables()
{ // Called at beginning of evaluateEvent() to reset calculated variables to their initial, default values.
    logger_.trace("resetEventVariables(): called");
  // Reset event weight.
    wt_ = 1.0;
  // Reset SP and OC collections.
    selectionProfiles_->reset();
  // Reset object collections
    // TO DO - implement
}

SelectionProfile* EventHandler::getSelectionProfile(const std::string& spStr)
{ // Returns a pointer to an SP. If it doesn't exist, it creates it based on the given string.
    logger_.debug("getSelectionProfile() called for {}", spStr);

  // Let the SelectionProfileCollection handle this mess.
    SelectionProfile* sp = selectionProfiles_->getSelectionProfile(spStr);

  // Add objects to lists.
    // eval_[ "SP"][spStr] = false;
    // for( string& objStr : SelectionProfile::objectLabelStrs_)
    //   eval_[objStr][sp->getObjectSpecifierString(objStr)] = false;

  // Set up lists of object pointers for Leptons, Jets based on SP just input.
    // TO DO!! Old code shown below:
    // If the specified lepton criteria isn't already stored, store it.
      // string newLepCrit = selectionProfiles_[spStr]->getObjectCriteriaString("L");
      // if(!lepCriteria_.count(newLepCrit))
      // {   logger_.debug("Adding Lepton Criteria to lepCriteria_: {}", newLepCrit);
      //     lepCriteria_[newLepCrit] = vector<LeptonObject*>(0);
      // }

    return sp;
}
