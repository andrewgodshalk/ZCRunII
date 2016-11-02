#ifndef GUARD_LeptonObject_h
#define GUARD_LeptonObject_h

/*------------------------------------------------------------------------------
   LeptonObjects

 Created : 2016-11-02  godshalk
 Modified: 2016-11-02  godshalk

 Struct that contains information about lepton physics objects mapped from Z+c
   Ntuples.

 2016-11-02 - Split from PhysicsObjects.h file.

------------------------------------------------------------------------------*/

// Root libraries
#include <Rtypes.h>
// Project Specific Headers
#include "EventMap.h"
#include "Logger.h"

class EventMap;

class LeptonObject
{
  public:
  // Constructor
    LeptonObject()   // Default, empty constructor.
      : evt_(NULL), index_(-1), charge(NULL), pt(NULL), eta(NULL), phi(NULL), pfRelIso04(NULL),
        logger_("NtupleProcessor", "[LO-EMPTY]       ")
    {}
    LeptonObject(EventMap*, int);   // Intended constructor: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.

  // Variable return functions.
    Int_t   getCharge    () {return *charge    ;}
    Float_t getPt        () {return *pt        ;}  // Will redefine later to include modifications for JEC, etc.
    Float_t getEta       () {return *eta       ;}
    Float_t getPhi       () {return *phi       ;}
    Float_t getPfRelIso04() {return *pfRelIso04;}

  private:
  // Originating EventMap info
    EventMap* evt_  ;
    int       index_;     // Index location of this particular object.

  // Pointers to mapped variables.
    Int_t   *charge    ;
    Float_t *pt        ;
    Float_t *eta       ;
    Float_t *phi       ;
    Float_t *pfRelIso04;

    Logger logger_;

};

#endif
