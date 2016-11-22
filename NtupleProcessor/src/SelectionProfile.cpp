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

using std::map;
using std::pair;
using std::regex;
using std::string;
using std::vector;

// Define default selection profile and object criteria (see doc/SelectionProfile_format.txt)
//const string SelectionProfile::defaultProfile_ = "j1Zllf70c110ncLp20e21id3iso2sfc";
const string SelectionProfile::defaultProfile_ = "jgZllf0070c0110ncLp20e21id3iso2sfcJ0sip30e25jeccflvaMETptc0000tpfHF0iNoHFSVnsfn";
// vector<pair<const string, const string>> SelectionProfile::defaultObjectCriteria_ =
// { {  "j", "j1"               },
//   {  "Z", "Zllf0070c0110nc"  },
//   {  "L", "Lp20e21id3iso2sfc"},
//   {  "J", "J0p30e25jecc"     },
//   {"MET", "METptf0ptc9999pf" },
//   { "HF", "HFNoHFsfn"        },
// };


// WHEN IMPLEMENTING, LOOK AT SUBMATCHING AT http://www.cplusplus.com/reference/regex/ECMAScript/
// map<string, regex> SelectionProfile::criteriaRegex_ =
// { {   "j", regex("j[01]")                                                  },
//   {   "Z", regex("Z(ll|ee|eu|ue|uu)?(f[0-9]+)?(c[0-9]+)?([rn]c))?")        },
//   {   "L", regex("L(p[0-9]+)?(e[0-9]+)?(id[0123])?(iso[012])?(sf[nudc])?") },
//   {   "J", regex("J([0-4])?(p[0-9]+)?(e[0-9]+)?(jec[nudc])?")              },
//   { "MET", regex("MET(ptf[0-9]+)?(pf)?")                                   },
//   {  "HF", regex("HF(NoHF|CSV[LMTS]|CTAG)(sf[nudc])?")                     },
// };

// vector<vector<regex> > SelectionProfile::criteriaRegexSeparated_ =
// { {/*   j */ regex("[01]") },
//   {/*   Z */ regex("(ll|ee|eu|ue|uu)"), regex("f[0-9]+"), regex("c[0-9]+"), regex("[rn]c") },
//   {/*   L */ regex("p[0-9]+"), regex("e[0-9]+"), regex("id[0123]"), regex("iso[012]"), regex("sf[nudc]") },
//   {/*   J */ regex("[0-4]"), regex("p[0-9]+"), regex("e[0-9]+"), regex("jec[nudc]"),  },
//   {/* MET */ regex("ptf[0-9]+"), regex("pf") },
//   {/*  HF */ regex("(NoHF|CSV[LMTS]|CTAG)"), regex("sf[nudc]") },
// };


// Intended constructor: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.
SelectionProfile::SelectionProfile(string str)
  : //profileStr_(str), fullProfileStr_(""),
    selStr_(str),
    logger_("NtupleProcessor", "[SP]       ")
{
    logger_.trace("SelectionProfile initialized: {}", selStr_.truncated());

/*  // Set object criteria to the default values.
    for( auto &kv : defaultObjectCriteria_) objectCriteria_[kv.first] = kv.second;

  // Set up SP object based on input SP string. Set validity based on success.
    valid_ = processProfileString();
*/
}

bool SelectionProfile::evaluateEvent(EventHandler *evt, string options)
{ // Checks criteria required for SP against EH values.
    logger_.trace("evaluateEvent() called with options {}", options);
  // TO DO: IMPLEMENT
    // Evaluate Leptons.
    return true;
}
/*
string SelectionProfile::getLeptonCriteria()
{
    return objectCriteria_["L"];
}

bool SelectionProfile::setCriteria(const string& obj, const string& crit)
{ // Basically a switch function between the other object criteria functions.
    logger_.trace("setCriteria() called with obj = {}, crit = {}", obj, crit);
    if(obj==  "j") return setJSON             (crit);
    if(obj==  "Z") return setDileptonCriteria (crit);
    if(obj==  "L") return setLeptonCriteria   (crit);
    if(obj==  "J") return setJetCriteria      (crit);
    if(obj=="MET") return setMETCriteria      (crit);
    if(obj== "HF") return setHFTaggingCriteria(crit);
    return false;
}

bool SelectionProfile::setJSON(const string& crit)
{   logger_.trace("setJSON() called with crit = {}", crit);
    return false;
}

bool SelectionProfile::setDileptonCriteria(const string& crit)
{   logger_.trace("setDileptonCriteria() called with crit = {}", crit);
    return false;
}

bool SelectionProfile::setLeptonCriteria(const string& crit)
{   logger_.trace("setLeptonCriteria() called with crit = {}", crit);
    return false;
}

bool SelectionProfile::setJetCriteria(const string& crit)
{   logger_.trace("setJetCriteria() called with crit = {}", crit);
    return false;
}

bool SelectionProfile::setMETCriteria(const string& crit)
{   logger_.trace("setMETCriteria() called with crit = {}", crit);
    return false;
}

bool SelectionProfile::setHFTaggingCriteria(const string& crit)
{   logger_.trace("setHFTaggingCriteria() called with crit = {}", crit);
    return false;
}


bool SelectionProfile::processProfileString()
{ // Stores criteria for seperate objects from main values, returns false if string is invalid.
    logger_.trace("processProfileString() called");

  // Initialize working variables, storage.
    bool processingSuccessfulSoFar = true;
    size_t currentObjIdx = 0;
    size_t nextObjIdx = 0;
    size_t profEnd = profileStr_.length();
    typedef vector<pair<const string, const string> >::const_iterator vec_citer;
    vec_citer objIter = defaultObjectCriteria_.begin();
    vec_citer objEnd  = defaultObjectCriteria_.end();
    string currentObj = "";
    string    nextObj = "";

  // Find first object instance in profile.
    while(objIter != objEnd)
    {   nextObj = objIter->first;
        nextObjIdx = profileStr_.find(nextObj, 0);
        logger_.trace("processProfileString(): Searching profileStr_ {} for {} resulted in index {}", profileStr_, nextObj, nextObjIdx);
      // If the object is found at the beginning of the string, break from loop.
        if(nextObjIdx == 0)
        {   logger_.trace("processProfileString(): First obj ({}) found. Moving to next loop.", nextObj);
            currentObj = nextObj;
            break;
        }
      // If the object isn't found, leave criteria as default and move to the next.
        else if(nextObjIdx == string::npos) { objIter++; continue; }
      // If an object is found but is out of order, throw warnings and invalidate SP.
        else
        {   logger_.warn("processProfileString(): Unable to parse full profileString. Defaults used where possible.");
            return false;
        }
    }
  // Work through the profile, finding the beginning of the next object and using it as the end of the current object.
    while(++objIter != objEnd)
    {   nextObj = objIter->first;
        nextObjIdx = profileStr_.find(nextObj, currentObjIdx);
        logger_.trace("processProfileString(): Searching profileStr_ {} for {} resulted in index {}", profileStr_, nextObj, nextObjIdx);
      // If the object isn't found, leave criteria as default and move to the next object
        if(nextObjIdx == string::npos) continue;
      // If an object is found, use it as the end-point of the current object string...
        objectCriteria_[currentObj] = profileStr_.substr(currentObjIdx, nextObjIdx-currentObjIdx);
      // ...and set it up as the next object for which to find a criteria string.
        currentObjIdx = nextObjIdx;
        currentObj = nextObj;
    }
  // Set the final criteria string, assuming at least one object was found.
    if(currentObj!="") objectCriteria_[currentObj] = profileStr_.substr(currentObjIdx, profEnd-currentObjIdx);

  // ...set class variables the given object criteria,...
    for(auto& kv : objectCriteria_) processingSuccessfulSoFar &= setCriteria(kv.first, kv.second);

    return processingSuccessfulSoFar;
}
*/
