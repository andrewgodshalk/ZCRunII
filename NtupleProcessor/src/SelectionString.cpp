/*
SelectionString.cpp

 Created : 2016-11-22  godshalk
 Modified: 2016-11-22  godshalk

*/

// Standard Libraries
#include <map>
#include <string>
#include <utility>
// Root Classes
// Project Specific classes
#include "Logger.h"
#include "SelectionString.h"

using std::map;
using std::pair;
using std::size_t;
using std::string;
typedef pair<size_t, size_t> str_rng;

// STATICS DEFINITIONS
// Default selection profile and object criteria (see doc/SelectionProfile_format.txt)
const string SelectionString::defaultStr_ = "jgZllf0070c0110ncLp20e21id3iso2sfcJ0sip30e25jeccflvaMETptc0000tpfHF0iNoHFSVnsfn";

// Object subtring ranges.
map<string, str_rng > SelectionString::objectSubstrRange_ =
{ {   "j", str_rng( 0,  1) },
  {   "Z", str_rng( 2, 16) },
  {   "L", str_rng(17, 33) },
  {   "J", str_rng(34, 51) },
  { "MET", str_rng(52, 64) },
  {  "HF", str_rng(65, 78) },
};


// Intended constructor:
SelectionString::SelectionString(string str)
  : specifierStr_(str), fullStr_(""),
    logger_("NtupleProcessor", "[SS]       ")
{
    logger_.trace("SelectionString initialized: specifier: {}", specifierStr_);

  // Set up full string
    fleshOutSelectionString();
    logger_.trace("SelectionString initialized: full str : {}", fullStr_     );
    logger_.trace("SelectionString initialized: default  : {}", defaultStr_  );
}

const string SelectionString::getObjectCriteriaString(const string objStr)
{ // Returns selection criteria for the given object.
    logger_.trace("getObjectCriteriaString() called for {}", objStr);

  // If input object isn't listed, return empty string.
    if (objectSubstrRange_.find(objStr) == objectSubstrRange_.end())
    {
      logger_.trace("getObjectCriteriaString(): {} not found, return blank string.", objStr);
      return "";
    }

  // Return substring for given object, determined by hard-coded substring ranges.
    str_rng rng = objectSubstrRange_[objStr];
    size_t length = rng.second-rng.first+1;
    string returnStr = fullStr_.substr(rng.first, length);
    logger_.trace("getObjectCriteriaString(): returning {}", returnStr);
    return returnStr;
}


void SelectionString::fleshOutSelectionString()
{ // Make a full selection string out of the smaller specifier string.
    fullStr_ = defaultStr_;
    fullStr_[23] = '4';
}
