#ifndef GUARD_EventMap_h
#define GUARD_EventMap_h

/*------------------------------------------------------------------------------
   EventMap

 Created : 2016-10-25  godshalk
 Modified: 2016-11-02  godshalk

 Class created to map event values in a TTree into structs/classes/variables,
 which are then accessed by EventHandler.

 New variables need to be added in multiple locations:

 - Map variable needs to be added to class def
    (include/EventMap.h)
 - Branch needs to be added to list of branches
    (src/EventMap.cpp :  mapTree())
 - Branch needs to be mapped to map variable
    (src/EventMap.cpp : mapTree())
 If the value is part of a physics object (jet, lepton)
 - Variable may need to be added to PhysicsObjects.h if its a property of a jet or lepton.
    (include/PhysicsObjects.h)
 - Mapping needs to be done to the PhysicsObject
    (src/EventMap.cpp : map[Jet|Lepton]Object())
 - Some sort of interface needs to be coded into EventHandler class for use in HistogramMakers.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <string>
#include <vector>
// Submodules
#include "spdlog/spdlog.h"
// Root Classes
#include <TChain.h>
// Project Specific classes
#include "Logger.h"
#include "PhysicsObjects.h"

// Global variables to determine size of mapped arrays.
//const static int MAXNUMJETS = 130;
//const static int MAXNUMLEPS = 100;

class EventMap
{
  public:
    EventMap();
    ~EventMap(){}

    void mapTree(TTree*);

    const static size_t maxNumJets_ = 130;   // TEMPORARY WORKING VARIABLE - will be included in config file?
    const static size_t maxNumLeps_ = 100;   // TEMPORARY WORKING VARIABLE - will be included in config file?

    // Map variables
    Float_t json  ;
    Float_t Vtype ;
    Float_t V_pt  ;
    Float_t V_eta ;
    Float_t V_phi ;
    Float_t V_mass;
    Int_t   HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v;
    Int_t   HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v         ;
    Int_t   HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v       ;
    Float_t met_pt     ;
    Float_t met_phi    ;
    Float_t met_sumEt  ;
    Int_t   nselLeptons;
    Int_t   selLeptons_charge    [maxNumLeps_];
    Float_t selLeptons_pt        [maxNumLeps_];
    Float_t selLeptons_eta       [maxNumLeps_];
    Float_t selLeptons_phi       [maxNumLeps_];
    Float_t selLeptons_pfRelIso04[maxNumLeps_];
    Int_t   nJet;
    Float_t Jet_pt       [maxNumJets_];
    Float_t Jet_eta      [maxNumJets_];
    Float_t Jet_phi      [maxNumJets_];
    Int_t   Jet_mcFlavour[maxNumJets_];
    Float_t Jet_btagCSV  [maxNumJets_];
    Float_t Jet_vtxMass  [maxNumJets_];

    // Array variables mapped to objects.
    std::vector<   JetObject> jets_   ;
    std::vector<LeptonObject> leptons_;

  private:
    Logger logger_;

    // Helper function to set up physics object lists
    void mapPhysicsObjects();


};

#endif
