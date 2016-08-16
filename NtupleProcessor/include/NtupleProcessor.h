#ifndef GUARD_NtupleProcessor_h
#define GUARD_NtupleProcessor_h

/*------------------------------------------------------------------------------
 NtupleProcessor
   Created : 2015-09-14  godshalk
   Modified: 2016-08-16  godshalk
 Main class of NtupleProcessor program. Created to handle input and running of
 ntuple processing.
 Takes input variables (datasets, configurations, etc) and sets up the
 appropriate classes to handle each portion of the analysis process.
------------------------------------------------------------------------------*/
#include <TString.h>
#include <vector>


class NtupleProcessor
{
  public:
    NtupleProcessor();  // Primary constructor.
   ~NtupleProcessor(){}

};

#endif
