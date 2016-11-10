/*
SelectionProfile.cpp

 Created : 2016-11-02  godshalk
 Modified: 2016-11-02  godshalk

*/

// Standard Libraries
#include <regex>
#include <string>
#include <utility>
#include <vector>
// Root Classes
// Project Specific classes
#include "EventHandler.h"
#include "Logger.h"
#include "SelectionProfile.h"

using std::string;
using std::pair;
using std::regex;
using std::vector;
//using std::map;

// Define default selection profile and object criteria
//const string SelectionProfile::defaultProfile_ = "Zllf0070c0110ncLp20e21id3iso2sfcTllJ0p30e25jeccflvaMETptf0pfHF0NoHFsfn";
const string SelectionProfile::defaultProfile_ = "j1Zllf70c110ncLp20e21id3iso2sfc";
vector<pair<const string, const string>> SelectionProfile::defaultObjectCriteria_ =
{ {  "j", "j1"               },
  {  "Z", "Zllf0070c0110nc"  },
  {  "L", "Lp20e21id3iso2sfc"},
  {  "T", "Tll"              },
  {  "J", "J0p30e25jecc"     },
  {"MET", "METptf0pf"        },
  { "HF", "HFNoHFsfn"        },
};

vector<vector<regex> > SelectionProfile::criteriaRegex_ =
{ {/*   j */ regex("[01]") },
  {/*   Z */ regex("ll|ee|eu|ue|uu"), regex("f[0-9]{1,5}"), regex("c[0-9]{1,5}"), regex("[rn]c") },
  {/*   L */ regex("p20"), regex("e21"), regex("id3"), regex("iso2"), regex("sfc") },
  {/*   T */ regex("ll") },
  {/*   J */ regex("0"), regex("p30"), regex("e25"), regex("jecc"),  },
  {/* MET */ regex("ptf0"), regex("pf") },
  {/*  HF */ regex("NoHF"), regex("sfn") },
};

// Intended constructor: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.
SelectionProfile::SelectionProfile(string str)
  : profileStr_(str), fullProfileStr_(""),
    logger_("NtupleProcessor", "[SP]       ")
{
    logger_.trace("SelectionProfile initialized: {}", profileStr_);

  // Check whether SP string is valid. Set validity to true if so.
  if(processProfileString()) valid_ = true;

  // Set object criteria to the default values.
  for( auto &kv : defaultObjectCriteria_) objectCriteria_[kv.first] = kv.second;
}

bool SelectionProfile::evaluateEvent(EventHandler *evt, string options)
{ // Checks criteria required for SP against EH values.
    logger_.trace("evaluateEvent() called with options {}", options);
  // TO DO: IMPLEMENT
    // Evaluate Leptons.
    return true;
}

string SelectionProfile::getLeptonCriteria()
{
    return objectCriteria_["L"];
}

bool SelectionProfile::setCriteria(string& obj, string& crit)
{ // Basically a switch function between the other object criteria functions.
    if(obj==  "j") return setJSON             (crit);
    if(obj==  "Z") return setDileptonCriteria (crit);
    if(obj==  "L") return setLeptonCriteria   (crit);
    if(obj==  "T") return setTriggerCriteria  (crit);
    if(obj==  "J") return setJetCriteria      (crit);
    if(obj=="MET") return setMETCriteria      (crit);
    if(obj== "HF") return setHFTaggingCriteria(crit);
    return false;
}

bool SelectionProfile::setJSON(string& crit)
{
    return false;
}

bool SelectionProfile::setDileptonCriteria(string& crit)
{
    return false;
}

bool SelectionProfile::setLeptonCriteria(string& crit)
{
    return false;
}

bool SelectionProfile::setTriggerCriteria(string& crit)
{
    return false;
}

bool SelectionProfile::setJetCriteria(string& crit)
{
    return false;
}

bool SelectionProfile::setMETCriteria(string& crit)
{
    return false;
}

bool SelectionProfile::setHFTaggingCriteria(string& crit)
{
    return false;
}


bool SelectionProfile::processProfileString()
{ // Stores criteria for seperate objects from main values, returns false if string is invalid.
    logger_.trace("processProfileString() called");

  /////// TO DO ////////
  // Figure out how SP, EH interact to select events, objects, etc from the initial SP string.
  //  - By comparing strings? By straight checks determined by the strings?
  //  - Does EH evaluate the profile, or does SP?
  //  - Does it do it all at once, or in pieces?
  //  - Object SPs seems to be a good idea.
  //  - Should we break up the SPs into sub classes/sandbox classes?

  // Initialize working variables, storage.
    bool processingSuccessfulSoFar = true;
    typedef string::const_iterator str_citer;
    typedef vector<pair<const string, const string> >::const_iterator vec_citer;
    str_citer profIter = profileStr_.begin();
    str_citer profEnd  = profileStr_.end();
    vec_citer objIter = defaultObjectCriteria_.begin();
    vec_citer objEnd  = defaultObjectCriteria_.end();
    string currentObj = "";
    string currentDefaultCriteria = "";

  // Cycle through individual objects and set up criteria.
    while(objIter != objEnd) // While there are still objects to be written...
    { // Check if the next value in the default map is specified in the profile string.
      currentObj = objIter->first; currentDefaultCriteria = objIter->second;
      logger_.debug("processProfileString(): Checking object \"{}\"", currentObj);

      if(string(profIter, profIter+currentObj.length()) != currentObj)
      { // If the profile string has no specification for the next object, specify the default criteria.
          logger_.debug("processProfileString(): No specification for \"{}\", setting to default (\"{}\")", currentObj, currentDefaultCriteria);
          objectCriteria_[currentObj] = currentDefaultCriteria;
      }
      else
      { // If this is the last object, save the rest of the profile as its criteria.
          if( (objIter+1)==objEnd ) objectCriteria_[currentObj] = string(profIter, profEnd);
          else
          { // Find the next object in the profile and save up to that point.
              string nextObj = (objIter+1)->first;
              size_t
              // str_citer spcIter = profIter; // Set to beginning of current obj specs.
          }
      }
    // Set class variables the given object criteria.
      processingSuccessfulSoFar = setCriteria(currentObj, objectCriteria_[currentObj]);
      objIter++;
    }

  // If some of the profile string was not processed, it is invalid. Output remaining and return false.
    if(profIter != profEnd)
    {   logger_.warn("processProfileString(): Unable to parse full profileString. Defaults used where possible.");
        logger_.warn("processProfileString(): Unparsed portion of profile: {}", string(profIter, profEnd));
        return false;
    }
    return true;
}
