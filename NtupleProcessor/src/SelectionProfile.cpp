/*
SelectionProfile.cpp

 Created : 2016-11-02  godshalk
 Modified: 2016-11-30  godshalk

*/

// Standard Libraries
#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>
// Project Specific classes
#include "EventHandler.h"
#include "Logger.h"
#include "SelectionProfile.h"

using std::map;
using std::pair;
using std::string;
using std::vector;
typedef pair<size_t, size_t> str_rng;

// Define default selection profile and object criteria (see doc/SelectionProfile_format.txt)
const string SelectionProfile::defaultProfileStr_ = "jgZllf0070c0110rcLp20e21id3iso2sfcJ0sip30e25jeccflvaMETptc0000tpfHF0iNoHFSVnsfn";

// Object specifiers strings
std::vector<std::string> SelectionProfile::objectSpecifierStrs_ = {"j","Z","L","J","MET","HF"};

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
    logger_.trace("breakDownSelectionByObject() called");

  // Find object strings within specifier string.
    vector<size_t> objLocs    (objectSpecifierStrs_.size(), string::npos);
    vector<string> objSpecStrs(objectSpecifierStrs_.size(), "");
    getObjectSplitLocations(objLocs);
    partionSpecifierString (objLocs, objSpecStrs);

    fullProfileStr_ = defaultProfileStr_;
    fullProfileStr_[23] = '4';
}

void SelectionProfile::getObjectSplitLocations(vector<size_t>& locations)
{ // Find starting locations of each object in specifier string.
    logger_.trace("getObjectSplitLocations() called");

  // Find each object in the string remaining after the previously found object.
    size_t searchStartingPoint = 0;  // Set equal to index after last found object string.
    for(size_t i=0; i<objectSpecifierStrs_.size(); i++)
    { // Find start location of next object
        locations[i] = specifierStr_.find(objectSpecifierStrs_[i], searchStartingPoint);
      // If a valid position was found, set the new search starting point to just after the found object string.
        if(locations[i]!=string::npos) searchStartingPoint = locations[i]+objectSpecifierStrs_[i].length();
    }

  // **DEBUG** Print string information.
    logger_.trace("{}", specifierStr_);
    logger_.trace("0123456789012345678901234567890123456789012345678901234567890123456789012345678");
    logger_.trace("0         1         2         3         4         5         6         7        ");

  // Print locations found.
    for(size_t i=0; i<locations.size(); i++)
      logger_.trace("Found {} at {}", objectSpecifierStrs_[i], locations[i]);
}

void SelectionProfile::partionSpecifierString(const std::vector<std::size_t>& locations, std::vector<std::string>& substrings)
{ // Returns specifier string split by object. Passed references to object start locations and vector of strings to fill.
    logger_.trace("partionSpecifierString() called");
  // Find index of first object specified in specifier (use difference in iterators).
    size_t iThisObj = std::find_if(locations.begin(), locations.end(), [](size_t i){return i!=string::npos;}) - locations.begin();
    logger_.trace("First object found {}: {} at {}", iThisObj, objectSpecifierStrs_[iThisObj], locations[iThisObj]);
    size_t iNextObj=iThisObj+1;
    while(iNextObj<objectSpecifierStrs_.size())
    { // For each object found...
        if(locations[iNextObj] != string::npos)
        {   substrings[iThisObj] = specifierStr_.substr(locations[iThisObj], locations[iNextObj]-locations[iThisObj]);
            iThisObj=iNextObj;
        }
        iNextObj++;
    }
  // Set the final string with no endpoint.
    substrings[iThisObj] = specifierStr_.substr(locations[iThisObj]);

  // Print substrings found.
    for(size_t i=0; i<substrings.size(); i++)
      logger_.trace("Spec for {} is {}", objectSpecifierStrs_[i], substrings[i]==""?"not specified":substrings[i]);
}
