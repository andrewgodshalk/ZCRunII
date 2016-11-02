/*
EventMap.cpp

 Created : 2016-10-25  godshalk
 Modified: 2016-10-26  godshalk

*/

// Standard Libraries
#include <iostream>
#include <string>
#include <vector>
// Project Specific
#include "EventMap.h"

using std::string;   using std::vector;

EventMap::EventMap() :
  jets_(maxNumJets_), leptons_(maxNumLeps_),
  logger_("NtupleProcessor", "[EM]       ")
{
    logger_.debug("EventMap Created.");
}

void EventMap::mapTree(TTree* tree)
{ // Map the input tree to variables locally
    logger_.trace("mapTree(): called");

  // List all active branches.
    tree->SetBranchStatus("*",0);
    vector<string> eventBranches =
    {   "json"     ,
        "Vtype"    ,
        "V_pt"     ,
        "V_eta"    ,
        "V_phi"    ,
        "V_mass"   ,
        "met_pt"   ,
        "met_phi"  ,
        "met_sumEt",
        "HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v" ,
        "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"          ,
        "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
        "nselLeptons",
        "nJet"       ,
    };
    vector<string> jetBranches =
    {   "Jet_pt"       ,
        "Jet_eta"      ,
        "Jet_phi"      ,
        "Jet_mcFlavour",
        "Jet_btagCSV"  ,
        "Jet_vtxMass"  ,
    };
    vector<string> leptonBranches =
    {   "selLeptons_charge"    ,
        "selLeptons_pt"        ,
        "selLeptons_eta"       ,
        "selLeptons_phi"       ,
        "selLeptons_pfRelIso04",
    };
    logger_.trace("mapTree(): branch lists created.");


  // Deactivate all branches, reactivate as necessary.
    for(string& br :  eventBranches) tree->SetBranchStatus(br.c_str(), 1);
    for(string& br :    jetBranches) tree->SetBranchStatus(br.c_str(), 1);
    for(string& br : leptonBranches) tree->SetBranchStatus(br.c_str(), 1);
    logger_.trace("mapTree(): branch lists reactivated.");

    tree->SetBranchAddress( "json"                 , &json                  );
    tree->SetBranchAddress( "Vtype"                , &Vtype                 );
    tree->SetBranchAddress( "V_pt"                 , &V_pt                  );
    tree->SetBranchAddress( "V_eta"                , &V_eta                 );
    tree->SetBranchAddress( "V_phi"                , &V_phi                 );
    tree->SetBranchAddress( "V_mass"               , &V_mass                );
    tree->SetBranchAddress( "met_pt"               , &met_pt                );
    tree->SetBranchAddress( "met_phi"              , &met_phi               );
    tree->SetBranchAddress( "met_sumEt"            , &met_sumEt             );
    tree->SetBranchAddress( "nselLeptons"          , &nselLeptons           );
    tree->SetBranchAddress( "selLeptons_charge"    ,  selLeptons_charge     );
    tree->SetBranchAddress( "selLeptons_pt"        ,  selLeptons_pt         );
    tree->SetBranchAddress( "selLeptons_eta"       ,  selLeptons_eta        );
    tree->SetBranchAddress( "selLeptons_phi"       ,  selLeptons_phi        );
    tree->SetBranchAddress( "selLeptons_pfRelIso04",  selLeptons_pfRelIso04 );
    tree->SetBranchAddress( "nJet"                 , &nJet                  );
    tree->SetBranchAddress( "Jet_pt"               ,  Jet_pt                );
    tree->SetBranchAddress( "Jet_eta"              ,  Jet_eta               );
    tree->SetBranchAddress( "Jet_phi"              ,  Jet_phi               );
    tree->SetBranchAddress( "Jet_mcFlavour"        ,  Jet_mcFlavour         );
    tree->SetBranchAddress( "Jet_btagCSV"          ,  Jet_btagCSV           );
    tree->SetBranchAddress( "Jet_vtxMass"          ,  Jet_vtxMass           );
    tree->SetBranchAddress( "HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", &HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v );
    tree->SetBranchAddress( "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"         , &HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v          );
    tree->SetBranchAddress( "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"       , &HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v        );
    logger_.trace("mapTree(): branch variables mapped.");

  // Set up physics object lists.
    mapPhysicsObjects();
}

void EventMap::mapPhysicsObjects()
{ // Helper Function. Helps create vectors of mapped physics objects.
    logger_.trace("mapPhysicsObjects(): called");
    for (size_t i = 0; i < maxNumJets_; i++)
    {   jets_[i].pt        = &(Jet_pt       [i]);
        jets_[i].eta       = &(Jet_eta      [i]);
        jets_[i].phi       = &(Jet_phi      [i]);
        jets_[i].mcFlavour = &(Jet_mcFlavour[i]);
        jets_[i].btagCSV   = &(Jet_btagCSV  [i]);
        jets_[i].vtxMass   = &(Jet_vtxMass  [i]);
    }
    for (size_t i = 0; i < maxNumLeps_; i++)
    {   leptons_[i].charge     = selLeptons_charge    [i];
        leptons_[i].pt         = selLeptons_pt        [i];
        leptons_[i].eta        = selLeptons_eta       [i];
        leptons_[i].phi        = selLeptons_phi       [i];
        leptons_[i].pfRelIso04 = selLeptons_pfRelIso04[i];
    }
//    if(&jets_[0].pt == &(Jet_pt[0])) logger_.debug("mapPhysicsObjects(): test: references are equal.");
    if(&(jets_[0].pt) == &(Jet_pt[0])) logger_.debug("mapPhysicsObjects(): test: references are equal.");
    std::cout << &(jets_[0].pt) << std::endl;
    std::cout << &(Jet_pt[0]) << std::endl;
}
