#ifndef GUARD_PhysicsObjects_h
#define GUARD_PhysicsObjects_h

/*------------------------------------------------------------------------------
   PhysicsObjects

 Created : 2016-10-25  godshalk
 Modified: 2016-11-02  godshalk

 Structs that contain information about physics objects (leptons, jets, etc)
 mapped from Z+c ntuples.

 To do:
 - Add returns (i.e. JetObject.getPt()), where a modifier can be added within the function for JEC, error, etc.

------------------------------------------------------------------------------*/

// Root libraries
#include <Rtypes.h>
// Project Specific Headers
#include "EventMap.h"


// Forward define EventMap to prevent errors from interdependancy.
class EventMap;

struct JetObject
{
  // Constructor
    // Default, empty constructor.
    // JetObject() : pt(BLANK_f), eta(BLANK_f), phi(BLANK_f), mcFlavour(BLANK_i), btagCSV(BLANK_f), vtxMass(BLANK_f), evt_(NULL), index_(-1) {}
    JetObject();

    // Intended constructor: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.
    JetObject(EventMap*, int);
    // JetObject(EventMap* e, int i)
    //   : evt_(e), index_(i)
    // {
    //     pt        = evt_->Jet_pt       [index_];
    //     eta       = evt_->Jet_eta      [index_];
    //     phi       = evt_->Jet_phi      [index_];
    //     mcFlavour = evt_->Jet_mcFlavour[index_];
    //     btagCSV   = evt_->Jet_btagCSV  [index_];
    //     vtxMass   = evt_->Jet_vtxMass  [index_];
    // }

  // Originating EventMap info
    EventMap* evt_  ;
    int       index_;     // Index location of this particular object.

  // Mapped variables.
    Float_t &pt       ;
    Float_t &eta      ;
    Float_t &phi      ;
    Int_t   &mcFlavour;
    Float_t &btagCSV  ;
    Float_t &vtxMass  ;

  // Default variable locations.
    Float_t BLANK_f = -9999;
    Int_t   BLANK_i = -99;

};

JetObject::JetObject() : evt_(NULL), index_(-1), pt(BLANK_f), eta(BLANK_f), phi(BLANK_f), mcFlavour(BLANK_i), btagCSV(BLANK_f), vtxMass(BLANK_f) {}

// Intended constructor: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.
JetObject::JetObject(EventMap* e, int i)
  : evt_(e), index_(i)
{
    pt        = evt_->Jet_pt       [index_];
    eta       = evt_->Jet_eta      [index_];
    phi       = evt_->Jet_phi      [index_];
    mcFlavour = evt_->Jet_mcFlavour[index_];
    btagCSV   = evt_->Jet_btagCSV  [index_];
    vtxMass   = evt_->Jet_vtxMass  [index_];
}




struct LeptonObject
{
  Int_t   &charge    ;
  Float_t &pt        ;
  Float_t &eta       ;
  Float_t &phi       ;
  Float_t &pfRelIso04;

  // Constructor
  LeptonObject() : charge(BLANK_i), pt(BLANK_f), eta(BLANK_f), phi(BLANK_f), pfRelIso04(BLANK_f) {}

  // Default variable locations.
    Float_t BLANK_f = -9999;
    Int_t   BLANK_i = -99;
};

#endif
