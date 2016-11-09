#ifndef GUARD_SelectionProfile_h
#define GUARD_SelectionProfile_h

/*------------------------------------------------------------------------------
   SelectionProfile

 Created : 2016-11-04  godshalk
 Modified: 2016-11-09  godshalk

 Specifies the desired selection criteria for an event. Can be specified and
 parsed from a string.

 For the format of the string, see NtupleProcessor/doc/SelectionProfile_format.txt

------------------------------------------------------------------------------*/

// Standard Libraries
#include <string>
// Root Classes
// Project Specific classes
#include "EventHandler.h"
#include "Logger.h"

// Forward declaration of interdependent class.
class EventHandler;

class SelectionProfile
{
  public:
    SelectionProfile(std::string str="");
    ~SelectionProfile(){}

    bool evaluateEvent(EventHandler*, std::string options = "");
    std::string getLeptonCriteria();

  private:
    bool processProfileString();  // Stores string values, returns false if string is invalid.

    std::string profileStr_;    // String specifier for SP
    bool valid_;                // Validity of SP based on profileStr_
    Logger   logger_;

    const static std::string defaultProfile_;
    static std::map<const std::string, const std::string> defaultObjectCriteria_;

};

#endif
