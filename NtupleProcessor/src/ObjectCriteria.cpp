/*
ObjectCriteria.cpp

 Created : 2016-11-30  godshalk
 Modified: 2016-11-30  godshalk

*/

// Project Specific classes
#include "Logger.h"
#include "ObjectCriteria.h"

using std::map;
using std::string;

// Static Variables
map<string, string> ObjectCriteria::defaultObjectProfiles_ =
{ {   "j", "jg"                 },
  {   "Z", "Zllf0070c0110nc"    },
  {   "L", "Lp20e21id3iso2sfc"  },
  {   "J", "J0sip30e25jeccflva" },
  { "MET", "METc0000tpf"        },
  {  "HF", "HF0iNoHFSVnsfn"     },
};
// String breakdown: j[g] Z[ll][f0070][c0110][nc] L[p20][e21][id3][iso2][sfc] J[0si][p30][e25][jecc][flva] MET[c0000][tpf] HF[0i][NoHF][SVn][sfn]

// CONSTRUCTORS: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.
ObjectCriteria::ObjectCriteria(string op)
  : specStr_(op), fullSpecStr_(""),
    logger_("NtupleProcessor", "[OC]       ")
  {
      logger_.trace("ObjectCriteria() created w/ profile: {}", op);
  }

JSONCriteria::JSONCriteria(string op)
  : ObjectCriteria(op)
{
  // String breakdown: j[g]
  if(fullSpecStr_=="") fullSpecStr_ = defaultObjectProfiles_["j"];
  // else setCriteria();
}

DileptonCriteria::DileptonCriteria(string op)
  : ObjectCriteria(op)
{
  // String breakdown: j[g]
  if(fullSpecStr_=="") fullSpecStr_ = defaultObjectProfiles_["Z"];
  // else setCriteria();
}

LeptonCriteria::LeptonCriteria(string op)
  : ObjectCriteria(op)
{
  // String breakdown: j[g]
  if(fullSpecStr_=="") fullSpecStr_ = defaultObjectProfiles_["L"];
  // else setCriteria();
}

JetCriteria::JetCriteria(string op)
  : ObjectCriteria(op)
{
  // String breakdown: j[g]
  if(fullSpecStr_=="") fullSpecStr_ = defaultObjectProfiles_["J"];
  // else setCriteria();
}

METCriteria::METCriteria(string op)
  : ObjectCriteria(op)
{
  // String breakdown: j[g]
  if(fullSpecStr_=="") fullSpecStr_ = defaultObjectProfiles_["MET"];
  // else setCriteria();
}

HFCriteria::HFCriteria(string op)
  : ObjectCriteria(op)
{
  // String breakdown: j[g]
  if(fullSpecStr_=="") fullSpecStr_ = defaultObjectProfiles_["HF"];
  // else setCriteria();
}
