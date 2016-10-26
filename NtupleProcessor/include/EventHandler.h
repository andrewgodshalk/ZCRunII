#ifndef GUARD_EventHandler_h
#define GUARD_EventHandler_h

/*------------------------------------------------------------------------------
   EventHandler

 Created : 2016-10-25  godshalk
 Modified: 2016-10-25  godshalk

 Class that handles physics objects from event map.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
// Submodules
#include "spdlog/spdlog.h"
// Root Classes
#include <TChain.h>
// Project Specific classes
#include "Logger.h"

typedef double (*getVal)(int);

class EventHandler
{
  public:
    EventHandler();
    ~EventHandler(){}

    void mapTree(TTree*);
    void evaluateEvent();

    getVal operator[](const char* v){return vals[v];}

  private:
    TTree *tree_;
    Logger logger_;
    std::map<const char*,getVal> vals;
    // double getValue(const char*, int);
    inline double getValue(const char* label, int i) { return tree_->GetLeaf(label)->GetValue(i); }
};


#endif
