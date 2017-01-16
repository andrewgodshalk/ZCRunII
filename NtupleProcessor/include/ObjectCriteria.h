#ifndef GUARD_ObjectCriteria_h
#define GUARD_ObjectCriteria_h

/*------------------------------------------------------------------------------
   ObjectCriteria

 Created : 2016-11-30  godshalk
 Modified: 2016-11-30  godshalk

 Contains and evaluates selection criteria for a given physics object.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <string>
#include <vector>
// Project Specific classes
//#include "SelectionProfile.h"
#include "EventHandler.h"
#include "Logger.h"

// Forward declare interdependent class
class EventHandler;

class ObjectCriteria
{
  public:
    ObjectCriteria(std::string, std::string);  // Constructor takes the object's type and profile.
    ~ObjectCriteria(){}

  // Evaluation functions.
    virtual bool evaluate(EventHandler*) = 0;
    void reset();

  // Factory Function
    static ObjectCriteria* createNew(std::string&, std::string&);  // Returns pointer to object made of with given type and specifier.

  // Enums defining options for various selection features.
    enum class application_status : char {none = 'n', central = 'c', err_up = 'u', err_down = 'd'};
    enum class application_level  : char {none = 'n', loose = 'l', medium = 'm', tight = 't'};
    enum class jet_selection_exclusivity : char {inclusive = 'i', exclusive = 'e'};

  // Accessors
    const std::string& criteriaStr() {return fullSpecStr_;}
    const std::string& specifierStr(){return     specStr_;}

    static std::map<std::string, std::string> defaultObjectProfiles_;

  protected:
    std::string objTypeStr_ ;   // Specifies what type of object OC describes.
    std::string specStr_    ;   // String used to define the object
    std::string fullSpecStr_;   // Full string describing the object's criteria

  // Evaluation values.
    bool evaluatated_;   // Whether this object has been evaluated.
    bool meetsCriteria_; // Whether this object's criteria has been met.

    // std::string::const_iterator specIter_;  // For iterating through specified profile
    // std::string::const_iterator dfltIter_;  // For iterating through default profile

    Logger logger_;

    void partitionPattern(const std::string&, std::vector<std::string>&);
      // Breaks a match pattern into its pieces to be processed individually. Clears vector and stores results for output.

    template <typename T>
    void getCriteriaFromSelectionProfile( const std::string&, T&);
      // Function that takes the next locations in the default and input specifier strings,
      //   looks to see if the given pattern is found in the specifier, sets the referenced variable to the Information
      //   from the pattern, and updates the fullSpecStr_ with the relavent information.
};

class JSONCriteria : protected ObjectCriteria
{
  public:
    JSONCriteria(std::string op="");
    ~JSONCriteria(){}
    bool evaluate(EventHandler* evt=NULL);

  // Criteria Variables.
    char jsonType_;
    bool (*jsonCheck_)(EventMap*);  // Function that is defined by constructor, based on input specifier, to be checked for every event.
};

class TriggerCriteria : protected ObjectCriteria
{
  public:
    TriggerCriteria(std::string op="");
    ~TriggerCriteria(){}
    bool evaluate(EventHandler* evt=NULL);

  // Criteria Variables.
    std::string trigger_;

  // Evaulation subfunctions. - List of function pointers for each JSON case.
    // static std::map<char, bool (*)(EventMap*)> jsonCheckFunctions;
    // bool (*jsonCheck_)(EventMap*);  // Function that is selected by constructor to be checked based on input.
};

class DileptonCriteria : protected ObjectCriteria
{
  public:
    DileptonCriteria(std::string op="");
    ~DileptonCriteria(){}
    bool evaluate(EventHandler* evt=NULL);

  // Criteria Variables.
    std::string dilepConstituents_;
    float dilepFloor_, dilepCeiling_;
    application_status dilepRCApplication_;
    std::vector<std::string> triggers_;
};

class LeptonCriteria : protected ObjectCriteria
{
  public:
    LeptonCriteria(std::string op="");
    ~LeptonCriteria(){}
    bool evaluate(EventHandler* evt=NULL);

  // Criteria Variables.
    float lepPtMin_, lepEtaMax_;
    application_level lepIDLvl_, lepIsoLvl_;
    application_status lepSF_;
};

class JetCriteria : protected ObjectCriteria
{
  public:
    JetCriteria(std::string op="");
    ~JetCriteria(){}
    bool evaluate(EventHandler* evt=NULL);

  // Criteria Variables.
    int jetMinimum_;
    float jetPtMin_, jetEtaMax_;
    application_status jetJECApplication_;
    char jetFlavor_;
};

class METCriteria : protected ObjectCriteria
{
  public:
    METCriteria(std::string op="");
    ~METCriteria(){}
    bool evaluate(EventHandler* evt=NULL);

  // Criteria Variables.
    float metPtFloor_  ;
    float metPtCeiling_;
    std::string type_  ;
};

class HFCriteria : protected ObjectCriteria
{
  public:
    HFCriteria(std::string op="");
    ~HFCriteria(){}
    bool evaluate(EventHandler* evt=NULL);

  // Criteria Variables.
    std::string hfTag;
    application_status hfTagApplication;
};

#endif
