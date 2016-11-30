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
// Root Classes
// Project Specific classes
//#include "EventHandler.h"
#include "Logger.h"

class SelectionProfile
{
  public:
    SelectionProfile(std::string str="");
    ~SelectionProfile(){}

  // Accessors.
    const std::string full()     {return fullProfileStr_ ;}
    const std::string truncated(){return specifierStr_   ;}
    const std::string getObjectCriteriaString(const std::string);

  private:
    void breakDownSelectionByObject();
    // Function that breaks down selection into strings for each object.
    // Information not completely specified is filled in from default profile.
    // Final strings are put together into full specifier string.

  // String storage.
    std::string specifierStr_; // String used in constructor. Specifies the differences from default.
    std::string fullProfileStr_;      // String created by class, filling in holes in specifier string with default values.

  // Static default value for SelectionString
    const static std::string defaultProfileStr_;
  // Variables for processing string.
    static std::map<std::string, std::pair<std::size_t, std::size_t> > objectSubstrRange_;

    Logger logger_    ;
};

#endif
