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

using std::map;
using std::string;
using std::vector;

EventMap::EventMap() :
  logger_("NtupleProcessor", "[EM]   ")
{
    logger_.trace("EventMap Created.");
}

void EventMap::mapTree(TTree* tree)
{ // Map the input tree to variables locally
    logger_.trace("mapTree(): called");

  // List all active branches.
    tree->SetBranchStatus("*",0);
    vector<string> triggerBranches =
    {   //"HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v" ,
        //"HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"          ,
        //"HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"        ,
        "HLT_BIT_HLT_Ele27_WPLoose_Gsf_v",
        "HLT_BIT_HLT_IsoMu20_v",
        "HLT_BIT_HLT_IsoTkMu20_v",
        "HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v",
        "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v",
        "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
        "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v",
        "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
        "HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v",
        "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v",
    };
    vector<string> eventBranches =
    {   "json"       ,
        "json_silver",
        "Vtype"      ,
        "V_pt"       ,
        "V_eta"      ,
        "V_phi"      ,
        "V_mass"     ,
        "met_pt"     ,
        "met_phi"    ,
        "met_sumEt"  ,
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
    vector<vector<string>*> allBranches = {&triggerBranches, &eventBranches, &jetBranches, &leptonBranches};
    for( auto list : allBranches)
        for(string& br : *list) tree->SetBranchStatus(br.c_str(), 1);

    // for(string& br : triggerBranches) tree->SetBranchStatus(br.c_str(), 1);
    // for(string& br :   eventBranches) tree->SetBranchStatus(br.c_str(), 1);
    // for(string& br :     jetBranches) tree->SetBranchStatus(br.c_str(), 1);
    // for(string& br :  leptonBranches) tree->SetBranchStatus(br.c_str(), 1);
    logger_.trace("mapTree(): branch lists reactivated.");

  // TEST! -- Trigger list
    //map<string, Int_t> trigger_ =
    // EVENTUALLY: Set up with TriggerConfig
    trigger =
    {   //{ "HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"     , 0},
        //{ "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"              , 0},
        //{ "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"            , 0},
        //{ "HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"      , 0},
        //{ "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"               , 0},
        //{ "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"             , 0},
        { "HLT_BIT_HLT_Ele27_WPLoose_Gsf_v"                          , 0},
        { "HLT_BIT_HLT_IsoMu20_v"                                    , 0},
        { "HLT_BIT_HLT_IsoTkMu20_v"                                  , 0},
        { "HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v"      , 0},
        { "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"               , 0},
        { "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"             , 0},
        { "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"               , 0},
        { "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"             , 0},
        { "HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", 0},
        { "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v" , 0},
    };
    for( auto& trigNameValue : trigger )
        tree->SetBranchAddress( trigNameValue.first.c_str(), &trigNameValue.second );
    // tree->SetBranchAddress( "HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", &HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v );
    // tree->SetBranchAddress( "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v"         , &HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v          );
    // tree->SetBranchAddress( "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v"       , &HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v        );
    tree->SetBranchAddress( "json"                 , &json                  );
    tree->SetBranchAddress( "json_silver"          , &json_silver           );
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
    logger_.trace("mapTree(): branch variables mapped.");

}
