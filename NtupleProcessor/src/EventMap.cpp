/*
EventMap.cpp

 Created : 2016-10-25  godshalk
 Modified: 2016-10-26  godshalk

*/

// Standard Libraries
#include <string>
#include <vector>
// Project Specific
#include "EventMap.h"

using std::string;   using std::vector;

EventMap::EventMap() :
  logger_("NtupleProcessor", "[EM]       ")
{
    logger_.debug("EventMap Created.");
}

void EventMap::mapTree(TTree* tree)
{ // Map the input tree to variables locally
    logger_.trace("mapTree(): called");

  // Deactivate all branches, reactivate as necessary.
    tree->SetBranchStatus("*",0);
    vector<string> branchesToReactivate =
    {   "json"     , "nJet"         , "nselLeptons"          ,
        "Vtype"    , "Jet_pt"       , "selLeptons_charge"    ,
        "V_pt"     , "Jet_eta"      , "selLeptons_pt"        ,
        "V_eta"    , "Jet_phi"      , "selLeptons_eta"       ,
        "V_phi"    , "Jet_mcFlavour", "selLeptons_phi"       ,
        "V_mass"   , "Jet_btagCSV"  , "selLeptons_pfRelIso04",
        "met_pt"   , "Jet_vtxMass"  ,
        "met_phi"  ,
        "met_sumEt",
        "HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v" ,
        "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"          ,
        "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"
    };
    for(string& br : branchesToReactivate) tree->SetBranchStatus(br.c_str(), 1);

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
}
