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
 - Variable will need to be added to appropriate header
   (include/Lepton(Jet)Object.h)
  - Variable will need to be initialized in base constructor
   (include/Lepton(Jet)Object.h)
  - Variable will need to be initialized in intended constructor
   (src/Lepton(Jet)Object.cpp)
  - Variable will need an accessor function (header or src, depending on necessary modifications.)

 When changing jet/lepton collections (e.g. selLeptons->vLeptons), variables will
 need to be changed all over the place, including here and in the physics object
 files. Be wary.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
#include <string>
#include <vector>
// Root Classes
#include <TChain.h>
// Project Specific classes
#include "Logger.h"

struct EventMap
{
  public:
    EventMap();
    ~EventMap(){}

    void mapTree(TTree*);

    const static size_t maxNumJets_ = 130;   // TEMPORARY WORKING VARIABLE - will be included in config file?
    const static size_t maxNumLeps_ = 100;   // TEMPORARY WORKING VARIABLE - will be included in config file?

    // Map variables
    Float_t json         ;
    Float_t json_silver  ;
    Float_t Vtype ;
    Float_t V_pt  ;
    Float_t V_eta ;
    Float_t V_phi ;
    Float_t V_mass;
    // Int_t   HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v;
    // Int_t   HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v         ;
    // Int_t   HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v       ;
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

    std::map<std::string, Int_t> trigger;


  private:
    Logger logger_;

};

#endif
