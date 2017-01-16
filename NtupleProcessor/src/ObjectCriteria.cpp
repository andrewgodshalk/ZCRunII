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
  {   "T", "ll"                 },
  {   "Z", "Zllf0070c0110nc"    },
  {   "L", "Lp20e21idtisotsfc"  },
  {   "J", "J0sip30e25jeccflva" },
  { "MET", "METc0000tpf"        },
  {  "HF", "HF0iNoHFSVnsfn"     },
};
// String breakdown: j[g] T[ll] Z[ll][f0070][c0110][rc] L[p20][e21][idt][iso2][sfc]  J[0si][0ti][p30][e25][jecc][flva] MET[f0000][c9999][tpf] HF[0i][NoHF][SVn][sfn]

// CONSTRUCTORS: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.
ObjectCriteria::ObjectCriteria(string ot, string op)
  : objTypeStr_(ot), specStr_(op), fullSpecStr_(ot),
    evaluatated_(false), meetsCriteria_(false),
    logger_("NtupleProcessor", "[OC]         ")
{   logger_.trace("ObjectCriteria() created w/ type, profile: {}, {}", ot, op); }

JSONCriteria::JSONCriteria(string op) : ObjectCriteria( "j", op)
{   logger_.trace("JSONCriteria() created w/ profile: {}", op);
  // Get JSON setting from strings. String breakdown: j[g]
  // Only one input, so just set to default if empty.
    fullSpecStr_ = specStr_.empty() ? defaultObjectProfiles_["j"] : specStr_;
  // Set JSON type to whatever was specfied in the second character.
    jsonType_ = fullSpecStr_[1];
}

TriggerCriteria::TriggerCriteria(string op) : ObjectCriteria(  "T", op){}
DileptonCriteria::DileptonCriteria(string op) : ObjectCriteria(  "Z", op){}
LeptonCriteria::LeptonCriteria(string op) : ObjectCriteria(  "L", op){}
JetCriteria::JetCriteria(string op) : ObjectCriteria(  "J", op){}
METCriteria::METCriteria(string op) : ObjectCriteria("MET", op){}
HFCriteria::HFCriteria(string op) : ObjectCriteria( "HF", op){}

// Factory Function
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

// Evaluation Functions
bool JSONCriteria::evaluate(EventHandler* evt)
{   if(evaluatated_) return meetsCriteria_;
    switch(jsonType_)
    {
        case 'g': meetsCriteria_ = evt->evtMap_->json;        break;
        case 's': meetsCriteria_ = evt->evtMap_->json_silver; break;
        case 'n': meetsCriteria_ = true;                      break;
        default : logger_.warn("Invalid JSON type specified: {}", jsonType_);
                  meetsCriteria_=false;
    }
    evaluatated_ = true;
    return meetsCriteria_;
}

bool DileptonCriteria::evaluate(EventHandler* evt)
{ if(!evaluatated_) evaluatated_ = meetsCriteria_ = true;
  return meetsCriteria_;
}

bool TriggerCriteria::evaluate(EventHandler* evt)
{ if(!evaluatated_) evaluatated_ = meetsCriteria_ = true;
  return meetsCriteria_;
}

bool LeptonCriteria::evaluate(EventHandler* evt)
{ if(!evaluatated_) evaluatated_ = meetsCriteria_ = true;
  return meetsCriteria_;
}

bool JetCriteria::evaluate(EventHandler* evt)
{ if(!evaluatated_) evaluatated_ = meetsCriteria_ = true;
  return meetsCriteria_;
}

bool METCriteria::evaluate(EventHandler* evt)
{ if(!evaluatated_) evaluatated_ = meetsCriteria_ = true;
  return meetsCriteria_;
}

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
