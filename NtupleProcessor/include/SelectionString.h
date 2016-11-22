#ifndef GUARD_SelectionString_h
#define GUARD_SelectionString_h

/*------------------------------------------------------------------------------
   SelectionString

 Created : 2016-11-22  godshalk
 Modified: 2016-11-22  godshalk

 Class that parses and processes a selection profile string.

 For the format of the string, see NtupleProcessor/doc/SelectionProfile_format.txt

------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
#include <string>
#include <utility>
// Root Classes
// Project Specific classes
#include "Logger.h"

// Forward declaration of interdependent class.
class EventHandler;

class SelectionString
{
  public:
    SelectionString(std::string str="");
    ~SelectionString(){}

  // Accessors.
    const std::string full() {return fullStr_     ;}
    const std::string truncated(){return specifierStr_;}
    const std::string getObjectCriteriaString(const std::string);

  private:
  // Function that processes short specifier string into full selection string.
    void fleshOutSelectionString();

  // String storage.
    std::string specifierStr_;                    // String used in constructor. Specifies the differences from default.
    std::string fullStr_;                         // String created by class, filling in holes in specifier string with default values.

  // Static default value for SelectionString
    const static std::string defaultStr_;
  // Variables for processing string.
    static std::vector<std::string> objects_;
    static std::map<std::string, std::pair<std::size_t, std::size_t> > objectSubstrRange_;

    Logger logger_;
};

#endif
