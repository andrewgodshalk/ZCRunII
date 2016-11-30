/*
SelectionProfile.cpp

 Created : 2016-11-02  godshalk
 Modified: 2016-11-30  godshalk

*/

// Standard Libraries
#include <map>
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
//using std::regex;
using std::string;
using std::vector;
typedef pair<size_t, size_t> str_rng;

// Define default selection profile and object criteria (see doc/SelectionProfile_format.txt)
const string SelectionProfile::defaultProfileStr_ = "jgZllf0070c0110rcLp20e21id3iso2sfcJ0sip30e25jeccflvaMETptc0000tpfHF0iNoHFSVnsfn";

// Object subtring ranges.
map<string, str_rng > SelectionProfile::objectSubstrRange_ =
{ {   "j", str_rng( 0,  1) },
  {   "Z", str_rng( 2, 16) },
  {   "L", str_rng(17, 33) },
  {   "J", str_rng(34, 51) },
  { "MET", str_rng(52, 64) },
  {  "HF", str_rng(65, 78) },
};

// CONSTRUCTOR: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.
SelectionProfile::SelectionProfile(string str)
  : specifierStr_(str), fullProfileStr_(""),
    logger_("NtupleProcessor", "[SP]       ")
{
    logger_.trace("SelectionProfile() specifier: {}", specifierStr_);

  // Set up full string
    breakDownSelectionByObject();
    logger_.trace("SelectionProfile() full str : {}", fullProfileStr_     );
    logger_.trace("SelectionProfile() default  : {}", defaultProfileStr_  );
}

const string SelectionProfile::getObjectCriteriaString(const string objStr)
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
    string returnStr = fullProfileStr_.substr(rng.first, length);
    logger_.trace("getObjectCriteriaString(): returning {}", returnStr);
    return returnStr;
}

void SelectionProfile::breakDownSelectionByObject()
{ // Make a full selection string out of the smaller specifier string.
  // String breakdown: j[g] Z[ll][f0070][c0110][nc] L[p20][e21][id3][iso2][sfc] J[0si][p30][e25][jecc][flva] MET[c0000][tpf] HF[0i][NoHF][SVn][sfn]
    //typedef string::const_iterator str_iter;

    fullProfileStr_ = defaultProfileStr_;
    fullProfileStr_[23] = '4';
}
