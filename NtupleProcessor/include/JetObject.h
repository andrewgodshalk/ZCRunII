#ifndef GUARD_JetObject_h
#define GUARD_JetObject_h

/*------------------------------------------------------------------------------
   JetObjects

 Created : 2016-11-02  godshalk
 Modified: 2016-11-02  godshalk

 Struct that contains information about jet phyiscs objects mapped from Z+c
   Ntuples.

 2016-11-02 - Split from PhysicsObjects.h file.

 To do:
 - Add returns (i.e. JetObject.getPt()), where a modifier can be added within the function for JEC, error, etc.

------------------------------------------------------------------------------*/

// Root libraries
#include <Rtypes.h>
// Project Specific Headers
#include "EventMap.h"
#include "Logger.h"

class EventMap;

class JetObject
{
  public:
  // Constructor
    JetObject()   // Default, empty constructor.
      : evt_(NULL), index_(-1), pt(NULL), eta(NULL), phi(NULL), mcFlavour(NULL), btagCSV(NULL), vtxMass(NULL),
        logger_("NtupleProcessor", "[JO-EMPTY]       ")
    {}
    JetObject(EventMap*, int);   // Intended constructor: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.

  // Variable return functions.
    Float_t getPt       () {return *pt       ;}  // Will redefine later to include modifications for JEC, etc.
    Float_t getEta      () {return *eta      ;}
    Float_t getPhi      () {return *phi      ;}
    Int_t   getMCFlavour() {return *mcFlavour;}
    Float_t getBtagCSV  () {return *btagCSV  ;}
    Float_t getVtxMass  () {return *vtxMass  ;}

  private:
  // Originating EventMap info
    EventMap* evt_  ;
    int       index_;     // Index location of this particular object.

  // Pointers to mapped variables.
    Float_t *pt       ;
    Float_t *eta      ;
    Float_t *phi      ;
    Int_t   *mcFlavour;
    Float_t *btagCSV  ;
    Float_t *vtxMass  ;

    Logger logger_;

};

#endif
