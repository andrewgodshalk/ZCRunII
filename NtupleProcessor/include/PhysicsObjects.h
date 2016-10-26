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

struct Jet
{
  Float_t pt            ;
  Float_t eta           ;
  Float_t phi           ;
  Int_t   mcFlavour     ;
  Float_t btagCSV       ;
  Float_t vtxMass       ;
};

struct Lepton
{
  Int_t   charge;
  Float_t pt;
  Float_t eta;
  Float_t phi;
  Float_t pfRelIso04;
};

#endif
