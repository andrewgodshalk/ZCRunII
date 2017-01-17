/*
ObjectCriteria.cpp

 Created : 2016-11-30  godshalk
 Modified: 2016-11-30  godshalk

*/

// Standard Libraries
// Project Specific classes
#include "Logger.h"
#include "ObjectCriteria.h"

using std::map;
using std::string;
using std::vector;
//typedef string::const_iterator str_iter;

// Static Variables
map<string, string> ObjectCriteria::defaultObjectProfiles_ =
{ {   "j", "jg"                 },
  {   "T", "Tll"                },
  {   "Z", "Zllf0070c0110nc"    },
  {   "L", "Lp20e21idtisotsfc"  },
  {   "J", "J0sip30e25jeccflva" },
  { "MET", "METc0000tpf"        },
  {  "HF", "HF0iNoHFSVnsfn"     },
};
// String breakdown: j[g] T[ll] Z[ll][f0070][c0110][rc] L[p20][e21][idt][iso2][sfc]  J[0si][0ti][p30][e25][jecc][flva] MET[f0000][c9999][tpf] HF[0i][NoHF][SVn][sfn]

//------------------------------------------------------------------------------
// VIRTUAL CLASS
ObjectCriteria::ObjectCriteria(string ot, string op)
  : objTypeStr_(ot), specStr_(op), fullSpecStr_(ot),
    evaluatated_(false), meetsCriteria_(false),
    logger_("NtupleProcessor", "[OC]         ")
{   logger_.trace("ObjectCriteria() created w/ type, profile: {}, {}", ot, op); }

// FACTORY FUNCTION
ObjectCriteria* ObjectCriteria::createNew(string& type, string& specifier)
{ // Returns pointer to object made of with given type and specifier.
    if(type ==   "j") return (ObjectCriteria*) new     JSONCriteria(specifier);
    if(type ==   "T") return (ObjectCriteria*) new  TriggerCriteria(specifier);
    if(type ==   "Z") return (ObjectCriteria*) new DileptonCriteria(specifier);
    if(type ==   "L") return (ObjectCriteria*) new   LeptonCriteria(specifier);
    if(type ==   "J") return (ObjectCriteria*) new      JetCriteria(specifier);
    if(type == "MET") return (ObjectCriteria*) new      METCriteria(specifier);
    if(type ==  "HF") return (ObjectCriteria*) new       HFCriteria(specifier);
    return NULL;
}

void ObjectCriteria::reset()
{   logger_.trace("reset(): called");
    evaluatated_ = meetsCriteria_ = false;
}


//------------------------------------------------------------------------------
// JSON CRITERIA

JSONCriteria::JSONCriteria(string op) : ObjectCriteria( "j", op)
{   logger_.trace("JSONCriteria() created w/ profile: {}", op);
  // Get JSON setting from strings. String breakdown: j[g]
  // Only one input, so just set to default if empty.
    fullSpecStr_ = specStr_.empty() ? defaultObjectProfiles_["j"] : specStr_;
  // Set JSON type to whatever was specfied in the second character.
    jsonType_ = fullSpecStr_[1];
  // Set up function pointer based on input json type.
    switch(jsonType_)
    {
        case 'g': jsonCheck_ = [](EventMap* em) -> bool {return em->json       ;}; break;
        case 's': jsonCheck_ = [](EventMap* em) -> bool {return em->json_silver;}; break;
        case 'n': jsonCheck_ = [](EventMap* em) -> bool {return true           ;}; break;
        default : logger_.warn("Invalid JSON type specified: {}", jsonType_);
                  jsonCheck_ = [](EventMap* em){return true           ;}; break;
    }
}

bool JSONCriteria::evaluate(EventHandler* evt)
{   if(!evaluatated_)
    {   meetsCriteria_ = jsonCheck_(evt->evtMap_);
        evaluatated_ = true;
    }
    return meetsCriteria_;
}


//------------------------------------------------------------------------------
// TRIGGER CRITERIA

// Statics
// TRIGGER INFO: SEE https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_Trigger
map<string, vector<string> > TriggerCriteria::triggerFullNames_
{   { "n",  {} },
    { "e",  { "HLT_BIT_HLT_Ele27_WPLoose_Gsf_v" }},
    { "u",  { "HLT_BIT_HLT_IsoMu20_v",
              "HLT_BIT_HLT_IsoTkMu20_v",
    }       },
    { "ee", { "HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v" }},
    { "uu", { "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v",
              "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
              "HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v",
              "HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v",
    }       },
    { "eu", { "HLT_BIT_HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v",
              "HLT_BIT_HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v",
    }       },
};
map<string, vector<string> > TriggerCriteria::triggerComposite_
{   { "n" , {}         },
    { "e" , {"e"}      },
    { "u" , {"u"}      },
    { "l" , {"e","u"}  },
    { "ee", {"ee"}     },
    { "uu", {"uu"}     },
    { "eu", {"eu"}     },
    { "ll", {"ee","uu"}},
};
// const map<string, bool (*)(EventMap*)      > TriggerCriteria::triggerFuncs_
// {   { "ee",
// { "uu",
// { "ll",
// }

TriggerCriteria::TriggerCriteria(string op) : ObjectCriteria("T", op)
{   logger_.trace("TriggerCriteria() created w/ profile: {}", op);

  // Get Trigger setting from strings. String breakdown: T[ll]
  // Only one input, so just set to default if empty.
    fullSpecStr_ = specStr_.empty() ? defaultObjectProfiles_["T"] : specStr_;

  // Set type to whatever follows the first character
    triggerAbbrev_ = fullSpecStr_.substr(1);
    logger_.trace("TriggerCriteria() trigger set to : {}", triggerAbbrev_);

  // Set up triggers to check each event.
    for(const auto& trig : triggerComposite_[triggerAbbrev_])
    {   logger_.trace("TriggerCriteria(): Pure trigger set up : {}", trig);
        evtTriggered_[trig] = false;
    }
}

bool TriggerCriteria::evaluate(EventHandler* evt)
{   if(evaluatated_) return meetsCriteria_;
  // Check every trig channel in the list of event triggers
    for(auto& channel : evtTriggered_)   // i.e. "ee" and "uu" when checking "ll"
    { // Check the individual triggers for this trigger channel
        for(const auto& trigName : triggerFullNames_[channel.first])    // i.e. multiple HLT names for "uu"
            channel.second = channel.second || evt->evtMap_->trigger[trigName];
      // Set the full event variable.
        meetsCriteria_ = meetsCriteria_ || channel.second;
    }
  // Return results
    evaluatated_ = true;
    return meetsCriteria_;

  //// ???????????
  //   NEED TO THINK ABOUT THIS - HE, EH might need to know about which trigger is active (for SF reasons is the main reason that comes to mind.)
  //   Thus, should EH handle this?
  //   Should SP Collection keep track of weights needed based on is OC?
  //   How will SFs work in general?
  //// ???????????

  // ALSO TO THINK ABOUT
  // May want to create check functions on the fly. There are a lot of references to vectors within maps within etc.
  // There may be a more efficient way to create runtime functions using lambdas, pointers, etc.

}

void TriggerCriteria::reset()
{ // Need to reset individual trigger statuses.
    for(auto& trig : evtTriggered_) trig.second = false;
    ObjectCriteria::reset();
}

//------------------------------------------------------------------------------
// DILEPTON CRITERIA

DileptonCriteria::DileptonCriteria(string op) : ObjectCriteria("Z", op){}

bool DileptonCriteria::evaluate(EventHandler* evt)
{ if(!evaluatated_) evaluatated_ = meetsCriteria_ = true;
  return meetsCriteria_;
}


//------------------------------------------------------------------------------
// LEPTON CRITERIA

LeptonCriteria::LeptonCriteria(string op) : ObjectCriteria("L", op){}

bool LeptonCriteria::evaluate(EventHandler* evt)
{ if(!evaluatated_) evaluatated_ = meetsCriteria_ = true;
  return meetsCriteria_;
}


//------------------------------------------------------------------------------
// MET CRITERIA

METCriteria::METCriteria(string op) : ObjectCriteria("MET", op){}

bool METCriteria::evaluate(EventHandler* evt)
{ if(!evaluatated_) evaluatated_ = meetsCriteria_ = true;
  return meetsCriteria_;
}


//------------------------------------------------------------------------------
// JET CRITERIA

JetCriteria::JetCriteria(string op) : ObjectCriteria("J", op){}

bool JetCriteria::evaluate(EventHandler* evt)
{ if(!evaluatated_) evaluatated_ = meetsCriteria_ = true;
  return meetsCriteria_;
}


//------------------------------------------------------------------------------
// HF CRITERIA

HFCriteria::HFCriteria(string op) : ObjectCriteria("HF", op){}

bool HFCriteria::evaluate(EventHandler* evt)
{ if(!evaluatated_) evaluatated_ = meetsCriteria_ = true;
  return meetsCriteria_;
}



//getCriteriaFromSelectionProfile("j%c", jsonType_);
/*
Work to automatically pull information from the OC. Too much work. Just hardcoding it for now. Could always come back and work on this later.

// String pattern:   j%c  Z %z  f%i    c%i    r%s L p%i  e%i  id%l iso%l sf%s
// Patterns to match:
// %c = character
// %i = integer
// %s = application_status
// %l = application_level
// %z = z decay channel

template <typename T>
void ObjectCriteria::getCriteriaFromSelectionProfile(const std::string& pattern, T& valRef)
{ // Use pattern to get next piece of information from profile. If not found, use information in default profile.
    logger_.trace("getCriteriaFromSelectionProfile(): Looking for pattern {}", pattern);
  // Process pattern - make list of pattern's pieces.
    vector<string> patPieces; partitionPattern(pattern, patPieces);
    // DEBUG: Print pieces of pattern.
    string patPiecesStr = ""; for(string &s : patPieces) patPiecesStr+= s+", ";
    logger_.trace("{} broken into peices: {}", pattern, patPiecesStr);

  // For each piece of the pattern...
    for(string& miniPat: patPieces)
    {   if(miniPat[0]!='%')   // If not looking for a special value, check for a string match.
            if(checkProfileForStr(miniPat[0]))
        else switch (miniPat[1])
        { // Otherwise, look for the corresponding value type.
            case 'c': getCharFromProfile     (valRef);   // %c = character
            case 'i': getIntFromProfile      (valRef);   // %i = integer
            case 's': getAppStatusFromProfile(valRef);   // %s = application_status
            case 'l': getAppLevelFromProfile (valRef);   // %l = application_level
            case 'z': getZDecayFromProfile   (valRef);   // %z = z decay channel
        }
      // If result was unsuccessful, use default value.
      // Concatenate result onto full spec string.
    }
}

void ObjectCriteria::partitionPattern(const string& pattern, vector<string>& results)
{ // Breaks a match pattern into its pieces to be processed individually. Clears vector and stores results for output.
    logger_.trace("partitionPattern({})", pattern);
    if(pattern.empty()) {logger_.warn("partitionPattern() fed empty string."); return;}
    results.clear();

  // Iterate through string. Find pieces and save to results.
    str_iter curPartStart, curChar, patternEnd;
    curPartStart = curChar = pattern.begin();   patternEnd = pattern.end();
    while((curPartStart=curChar) != patternEnd) // While there is still pattern to process...
    {   while(*curChar != '%' && curChar != patternEnd) curChar++; // Increment until the next %-pattern or the end is found.
        if(curChar==curPartStart) curChar += 2; // If this part begins with a percentage, save the next two characters.
        results.push_back(string(curPartStart, curChar));
    }
}

bool checkProfileForStr(string s){}
*/
