#ifndef GUARD_PhysicsObjects_h
#define GUARD_PhysicsObjects_h

/*------------------------------------------------------------------------------
   PhysicsObjects

 Created : 2016-10-25  godshalk
 Modified: 2016-10-25  godshalk

 Structs that contain information about physics objects (leptons, jets, etc)
 mapped from Z+c ntuples.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <vector>

struct Jet
{
  Float_t &Jet_pt       ;
  Float_t &Jet_eta      ;
  Float_t &Jet_phi      ;
  Int_t   &Jet_mcFlavour;
  Float_t &Jet_btagCSV  ;
  Float_t &Jet_vtxMass  ;
}

struct Lepton
{

}

#endif
