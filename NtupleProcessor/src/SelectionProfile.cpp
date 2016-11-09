/*
SelectionProfile.cpp

 Created : 2016-11-02  godshalk
 Modified: 2016-11-02  godshalk

*/

// Standard Libraries
#include <map>
#include <string>
// Root Classes
// Project Specific classes
#include "EventHandler.h"
#include "Logger.h"
#include "SelectionProfile.h"

using std::string;
using std::map;

// Define default selection profile and object criteria
const string SelectionProfile::defaultProfile_ = "Zllf070c110ncLp20e21id3iso2sfcTllJ0p30e25jeccMETptf0pfHF0NoHFsfn";
map<const string, const string> SelectionProfile::defaultObjectCriteria_ =
{ {  "Z", "Zllf070c110nc"    },
  {  "L", "Lp20e21id3iso2sfc"},
  {  "T", "Tll"              },
  {  "J", "J0p30e25jecc"     },
  {"MET", "METptf0pf"        },
  { "HF", "HFNoHFsfn"        },
};

// Intended constructor: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.
SelectionProfile::SelectionProfile(string str)
  : profileStr_(str),
    logger_("NtupleProcessor", "[SP]       ")
{
  logger_.trace("SelectionProfile initialized: {}", profileStr_);

  // Check whether SP string is valid. Set validity to true if so.
  if(processProfileString()) valid_ = true;

}

bool SelectionProfile::evaluateEvent(EventHandler *evt, string options)
{ // Checks criteria required for SP against EH values.
    logger_.trace("evaluateEvent() called with options {}", options);
  // TO DO: IMPLEMENT
    // Evaluate Leptons.
    return true;
}

bool SelectionProfile::processProfileString()
{ // Checks validity of string initializer.
  // TO DO: IMPLEMENT
    return true;
}

string SelectionProfile::getLeptonCriteria()
{
    return defaultObjectCriteria_["L"];
    //return "**LEPTONCRIT**";
}
