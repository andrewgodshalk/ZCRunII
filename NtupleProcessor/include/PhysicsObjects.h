#ifndef GUARD_PhysicsObjects_h
#define GUARD_PhysicsObjects_h

/*------------------------------------------------------------------------------
   PhysicsObjects

 Created : 2016-10-25  godshalk
 Modified: 2016-10-25  godshalk

 Structs that contain information about physics objects (leptons, jets, etc)
 mapped from Z+c ntuples.

------------------------------------------------------------------------------*/

// Root libraries
#include <Rtypes.h>
// Project Specific Headers
#include "EventMap.h"

struct JetObject
{
  Float_t &pt       ;
  Float_t &eta      ;
  Float_t &phi      ;
  Int_t   &mcFlavour;
  Float_t &btagCSV  ;
  Float_t &vtxMass  ;

  Float_t BLANK_f = -9999;
  Int_t   BLANK_i = -99;

  // Constructor
  JetObject() : pt(BLANK_f), eta(BLANK_f), phi(BLANK_f), mcFlavour(BLANK_i), btagCSV(BLANK_f), vtxMass(BLANK_f) {}
};

struct LeptonObject
{
  Int_t   &charge    ;
  Float_t &pt        ;
  Float_t &eta       ;
  Float_t &phi       ;
  Float_t &pfRelIso04;

  Float_t BLANK_f = -9999;
  Int_t   BLANK_i  = -99;

  // Constructor
  LeptonObject() : charge(BLANK_i), pt(BLANK_f), eta(BLANK_f), phi(BLANK_f), pfRelIso04(BLANK_f) {}

};

#endif
