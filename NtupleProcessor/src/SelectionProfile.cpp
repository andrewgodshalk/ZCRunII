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
//#include "EventHandler.h"
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
std::vector<std::string> SelectionProfile::objectLabelStrs_ = {"j","Z","L","J","MET","HF"};

// CONSTRUCTOR
SelectionProfile::SelectionProfile(SelectionProfileCollection* pc, string str)
  : parentCollection_(pc), specifierStr_(str), fullProfileStr_(""),
    evaluatated_(false), meetsCriteria_(false),
    logger_("NtupleProcessor", "[SP]       ")
{
    logger_.trace("SelectionProfile() specifier: {}", specifierStr_);

  // Initialize objectSpecifierStrs_
    for(string& l : objectLabelStrs_) objectSpecifierStrs_[l] = "";

  // Set up full string
    breakDownSelectionByObject();

    logger_.trace("SelectionProfile() full str : {}", fullProfileStr_     );
    logger_.trace("SelectionProfile() default  : {}", defaultProfileStr_  );
}

const string SelectionProfile::getObjectCriteriaString (const std::string obj) { return objCriteria_[obj]->criteriaStr() ;}
const string SelectionProfile::getObjectSpecifierString(const std::string obj) { return objectSpecifierStrs_[obj];}


void SelectionProfile::breakDownSelectionByObject()
{ // Make a full selection string out of the smaller specifier string.
  // String breakdown: j[g] Z[ll][f0070][c0110][nc] L[p20][e21][id3][iso2][sfc] J[0si][p30][e25][jecc][flva] MET[c0000][tpf] HF[0i][NoHF][SVn][sfn]
    //typedef string::const_iterator str_iter;
    logger_.trace("breakDownSelectionByObject() called");

  // Find object strings within specifier string.
    vector<size_t> objLocs    (objectLabelStrs_.size(), string::npos);
    // vector<string> objSpecStrs(objectLabelStrs_.size(), "");
    getObjectSplitLocations(objLocs);
    // partionSpecifierString (objLocs, objSpecStrs);
    partionSpecifierString (objLocs);

  // Set up object for each substring.
    // for(size_t i=0; i<objectLabelStrs_.size(); i++) objCriteria_[objectLabelStrs_[i]] = new ObjectCriteria(objSpecStrs[i]);
    // for(size_t i=0; i<objectLabelStrs_.size(); i++) objectSpecifierStrs_[objectLabelStrs_[i]] = objSpecStrs[i];

  // Initialize ObjectCriteria classes using parent SPC.
    parentCollection_->addObjectCriteriaToCollection(this);

    fullProfileStr_ = defaultProfileStr_;
    fullProfileStr_[23] = '4';
}

void SelectionProfile::getObjectSplitLocations(vector<size_t>& locations)
{ // Find starting locations of each object in specifier string.
    logger_.trace("getObjectSplitLocations() called");

  // Find each object in the string remaining after the previously found object.
    size_t searchStartingPoint = 0;  // Set equal to index after last found object string.
    for(size_t i=0; i<objectLabelStrs_.size(); i++)
    { // Find start location of next object
        locations[i] = specifierStr_.find(objectLabelStrs_[i], searchStartingPoint);
      // If a valid position was found, set the new search starting point to just after the found object string.
        if(locations[i]!=string::npos) searchStartingPoint = locations[i]+objectLabelStrs_[i].length();
    }

  // **DEBUG** Print string information.
    logger_.trace("{}", specifierStr_);
    logger_.trace("0123456789012345678901234567890123456789012345678901234567890123456789012345678");
    logger_.trace("0         1         2         3         4         5         6         7        ");

  // Print locations found.
    for(size_t i=0; i<locations.size(); i++)
      logger_.trace("Found {} at {}", objectLabelStrs_[i], locations[i]);
}

void SelectionProfile::partionSpecifierString(const std::vector<std::size_t>& locations)
{ // Returns specifier string split by object. Passed references to object start locations and vector of strings to fill.
    logger_.trace("partionSpecifierString() called");
  // Find index of first object specified in specifier (use difference in iterators).
    size_t iThisObj = std::find_if(locations.begin(), locations.end(), [](size_t i){return i!=string::npos;}) - locations.begin();
    logger_.trace("First object found {}: {} at {}", iThisObj, objectLabelStrs_[iThisObj], locations[iThisObj]);
    size_t iNextObj=iThisObj+1;
    while(iNextObj<objectLabelStrs_.size())
    { // For each object found...
        if(locations[iNextObj] != string::npos)
        {   objectSpecifierStrs_[objectLabelStrs_[iThisObj]] = specifierStr_.substr(locations[iThisObj], locations[iNextObj]-locations[iThisObj]);
            iThisObj=iNextObj;
        }
        iNextObj++;
    }
  // Set the final string with no endpoint.
    objectSpecifierStrs_[objectLabelStrs_[iThisObj]] = specifierStr_.substr(locations[iThisObj]);

  // Print substrings found.
    // for(size_t i=0; i<substrings.size(); i++)
    //   logger_.trace("Spec for {} is {}", objectLabelStrs_[i], substrings[i]==""?"not specified":substrings[i]);
    for(auto &kv : objectSpecifierStrs_)
      logger_.trace("Spec for {} is {}", kv.first, kv.second==""?"not specified":kv.second);
}

// Evaluation functions.
bool SelectionProfile::evaluate(EventHandler* evt)
{   if(!evaluatated_)
    {   for( auto& obj : objCriteria_) meetsCriteria_ = meetsCriteria_ && obj.second->evaluate(evt);
        evaluatated_ = true;
    }
    logger_.trace("Returning {}.", (meetsCriteria_?"true":"false"));
    return meetsCriteria_;
}

void SelectionProfile::reset()
{   logger_.trace("reset(): called");
    evaluatated_ = false; meetsCriteria_ = true;
    for( auto& obj : objCriteria_) obj.second->reset();
}
