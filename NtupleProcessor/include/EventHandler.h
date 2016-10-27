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
#include <TLeaf.h>
// Project Specific classes
#include "Logger.h"


class EventHandler
{
  public:
    EventHandler();
    ~EventHandler(){}

    void mapTree(TTree*);
    void evaluateEvent();

    //double get(const char* v, int i=0){return (this->*valFunctions[v])(v,i);};
    double get(const char*, int i=0);
    // getVal operator[](const char* v){return vals[v];}
    // double getValue(const char*, int);
    inline double getValue(const char* label, int i) { return tree_->GetLeaf(label)->GetValue(i); }
    double getValueDebug(const char*, int);

  private:
    TTree *tree_;
    Logger logger_;
    typedef double (EventHandler::*getVal)(const char*, int);
    std::map<const char*,getVal> valFunctions;
};

#endif
