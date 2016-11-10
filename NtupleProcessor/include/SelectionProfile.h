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
#include <regex>
#include <string>
#include <utility>
#include <vector>
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
    bool setCriteria(std::string&, std::string&);
    bool setJSON             (std::string&);
    bool setDileptonCriteria (std::string&);
    bool setLeptonCriteria   (std::string&);
    bool setTriggerCriteria  (std::string&);
    bool setJetCriteria      (std::string&);
    bool setMETCriteria      (std::string&);
    bool setHFTaggingCriteria(std::string&);

  // Selection Criteria, input from intializing string.
    bool inJSON_;
    // Dilepton
    std::string dilepConstituents_;
    float dilepFloor_, dilepCeiling_;
    char dilepRCApplication_;
    // Leptons
    float lepPtMin_, lepEtaMax_;
    int lepIDLvl_, lepIsoLvl_;
    char lepSF_;
    // Trigger
    std::string trigger_;
    // Jet
    int jetMinimum_;
    float jetPtMin_, jetEtaMax_;
    char jetJECApplication_, jetFlavor_;
    // MET
    float metPtFloor_;
    std::string type_;
    // HF
    std::string hfTag;
    char hfTagApplication;

  private:
    bool processProfileString();  // Stores string values, returns false if string is invalid.

    std::string profileStr_;       // String specifier for SP
    std::string fullProfileStr_;   // Profile string with default values inserted. Initizlized in processProfileString()
    std::map<const std::string, std::string> objectCriteria_;
    bool        valid_     ;   // Validity of SP based on profileStr_
    Logger      logger_    ;

  // Static default values for selectionProfile and objectCriteria, as well as the regex expressions used for extracting
    const static std::string defaultProfile_;
    static std::vector<std::pair<const std::string, const std::string> > defaultObjectCriteria_;
      // map of object/criteria pairs. Use vector<pair> instead of map for the sake of ordering.
    static std::vector<std::vector<std::regex> > criteriaRegex_;
};

#endif
