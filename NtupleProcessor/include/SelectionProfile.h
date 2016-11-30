#ifndef GUARD_SelectionProfile_h
#define GUARD_SelectionProfile_h

/*------------------------------------------------------------------------------
   SelectionProfile

 Created : 2016-11-04  godshalk
 Modified: 2016-11-30  godshalk

 Specifies the desired selection criteria for an event. Can be specified and
 parsed from a string.

 For the format of the string, see NtupleProcessor/doc/SelectionProfile_format.txt

------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
#include <string>
#include <utility>
#include <vector>
// Project Specific classes
#include "ObjectCriteria.h"
#include "SelectionProfileCollection.h"
#include "Logger.h"

// Forward declare interdependent class
class SelectionProfileCollection;


class SelectionProfile
{
  public:
    SelectionProfile(SelectionProfileCollection*, std::string str="");
    ~SelectionProfile(){}

  // Accessors.
    const std::string full()     {return fullProfileStr_ ;}
    const std::string specifier(){return specifierStr_   ;}
    const std::string getObjectCriteriaString (const std::string obj) { return objCriteria_[obj]->criteriaStr() ;}
    const std::string getObjectSpecifierString(const std::string obj) { return objCriteria_[obj]->specifierStr();}

  private:
    void breakDownSelectionByObject();
      // Function that breaks down selection into strings for each object.
      // Information not completely specified is filled in from default profile.
      // Final strings are put together into full specifier string.
    void getObjectSplitLocations(std::vector<std::size_t>&);
      // Finds starting location of each object in specifier string. Set to -1 if object is specified.
    // void partionSpecifierString(const std::vector<std::size_t>&, std::vector<std::string>&);
    void partionSpecifierString(const std::vector<std::size_t>&);
      // Returns specifier string split by object. Passed references to object start locations and vector of strings to fill.

    SelectionProfileCollection* parentCollection_; // Pointer to parent collection, which contains original instances of criteria.

  // String storage.
    std::string specifierStr_;    // String used in constructor. Specifies the differences from default.
    std::string fullProfileStr_;  // String created by class, filling in holes in specifier string with default values.
    std::map<std::string, std::string> objectSpecifierStrs_; // Strings for each object, taken from specifierStr_.

  // Object Criteria Pointers
    std::map<std::string, ObjectCriteria*> objCriteria_;

  // Static default value for SelectionString
    const static std::string defaultProfileStr_;

  // Variables for processing string.
    static std::vector<std::string> objectLabelStrs_;
    // static std::map<std::string, std::pair<std::size_t, std::size_t> > objectSubstrRange_;

    Logger logger_;

    friend class SelectionProfileCollection;
};

#endif
