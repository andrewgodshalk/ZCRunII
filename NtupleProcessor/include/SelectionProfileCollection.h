#ifndef GUARD_SelectionProfileCollection_h
#define GUARD_SelectionProfileCollection_h

/*------------------------------------------------------------------------------
   SelectionProfileCollection

 Created : 2016-11-30  godshalk
 Modified: 2016-11-30  godshalk

 Collects selection profiles specified for NtuplerProcessor. Stores profiles for
 individual physics objects and evaluates each once.

 For the format of the string, see NtupleProcessor/doc/SelectionProfile_format.txt

------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
#include <string>
// Project Specific classes
#include "EventHandler.h"
#include "Logger.h"
#include "SelectionProfile.h"

// Forward declare interdependent class
class SelectionProfile;
class EventHandler;
class ObjectCriteria;

class SelectionProfileCollection
{
  public:
    SelectionProfileCollection();
    ~SelectionProfileCollection(){}

  // Accessors
    SelectionProfile* getSelectionProfile(std::string spStr);
      // Returns SP pointer for given string. Creates the SP if it isn't already in its set.

  // Evaluating functions
    void evaluate(EventHandler*);  // Send evaluation command to all SPs.
    void reset();                  // Send reset commands to all SPs.

    void addObjectCriteriaToCollection(SelectionProfile*);
      // Sets ObjectCriteria pointers for SP from local collection. Creates new objects if not currently stored.
    ObjectCriteria* getObjectCriteria(std::string&, std::string&);
      // Returns pointer to newly created or existing OC w/ given type and specifier.

  private:
  // Collected Selection Profiles and Object Criteria.
    std::map<std::string, SelectionProfile*> selectionProfiles_;
    std::map<std::string, std::map<std::string, ObjectCriteria*> > objCriteria_;
      // Stores object criteria to check for each object.

  // Evaluation values.
    bool evaluatated_;   // Whether this object has been evaluated.
    bool meetsCriteria_; // Whether this object's criteria has been met.

    Logger logger_;

};

#endif
