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
// Project Specific classes
//#include "SelectionProfile.h"
#include "Logger.h"

class ObjectCriteria
{
  public:
    ObjectCriteria(std::string op="");
    ~ObjectCriteria(){}

    // Virtual functions
    // virtual ObjectCriteria* createNew(std::string op);  // Factory function. Creates a new object of this type.
    // virtual void setCriteria();  // Sets the criteria of the object based on its specifier string.

  // Enums defining options for various selection features.
    enum class application_status : char {none = 'n', central = 'c', err_up = 'u', err_down = 'd'};
    enum class application_level  : char {none = 'n', loose = 'l', medium = 'm', tight = 't'};

  // Accessors
    const std::string& criteriaStr() {return fullSpecStr_;}
    const std::string& specifierStr(){return     specStr_;}

    static std::map<std::string, std::string> defaultObjectProfiles_;


  protected:
    std::string specStr_;
    std::string fullSpecStr_;
    Logger logger_;
};

class JSONCriteria : protected ObjectCriteria
{
  public:
    JSONCriteria(std::string op="");
    ~JSONCriteria(){}

  // Criteria Variables.
    char jsonType_;
};

class DileptonCriteria : protected ObjectCriteria
{
  public:
    DileptonCriteria(std::string op="");
    ~DileptonCriteria(){}

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

  // Criteria Variables.
    std::string hfTag;
    application_status hfTagApplication;
};


#endif
