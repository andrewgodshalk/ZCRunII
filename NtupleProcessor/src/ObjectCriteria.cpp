/*
ObjectCriteria.cpp

 Created : 2016-11-30  godshalk
 Modified: 2016-11-30  godshalk

*/

// Standard Libraries
#include <array>
// Project Specific classes
#include "Logger.h"
#include "ObjectCriteria.h"

using std::array;
using std::map;
using std::string;
using std::vector;
typedef string::const_iterator str_iter;

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
ObjectCriteria* ObjectCriteria::createNew(std::string& type, std::string& specifier)
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
    //jsonCheck = [](EventMap*){return true;};
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

TriggerCriteria::TriggerCriteria(string op) : ObjectCriteria("T", op)
{   logger_.trace("TriggerCriteria() created w/ profile: {}", op);
  // Get Trigger setting from strings. String breakdown: T[ll]
  // Only one input, so just set to default if empty.
    fullSpecStr_ = specStr_.empty() ? defaultObjectProfiles_["T"] : specStr_;
  // Set type to whatever follows the first character
    trigger_ = fullSpecStr_.substr(1);
    logger_.trace("TriggerCriteria() trigger set to : {}", trigger_);
}

bool TriggerCriteria::evaluate(EventHandler* evt)
{ if(evaluatated_) return meetsCriteria_;
  else if(trigger_ == "n")  meetsCriteria_ = true;
  else if(trigger_ == "e")  meetsCriteria_ = false;
  else if(trigger_ == "u")  meetsCriteria_ = false;
  else if(trigger_ == "l")  meetsCriteria_ = false;
  else if(trigger_ == "ee") meetsCriteria_ = evt->evtMap_->HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v;
  else if(trigger_ == "eu") meetsCriteria_ = false;
  else if(trigger_ == "uu") meetsCriteria_ = evt->evtMap_->HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v + evt->evtMap_->HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v;
  else if(trigger_ == "ll") meetsCriteria_ =   evt->evtMap_->HLT_BIT_HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
                                            + evt->evtMap_->HLT_BIT_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v
                                            + evt->evtMap_->HLT_BIT_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v;
  evaluatated_ = true;
  return meetsCriteria_;
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
