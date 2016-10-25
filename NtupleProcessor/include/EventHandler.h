#ifndef GUARD_EventHandler_h
#define GUARD_EventHandler_h

/*------------------------------------------------------------------------------
   EventHandler

 Created : 2016-10-25  godshalk
 Modified: 2016-10-25  godshalk

 Class created to map event values in a TTree into structs/classes/variables.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <memory>
#include <string>
// Submodules
#include "spdlog/spdlog.h"
// Root Classes
// Project Specific classes
#include "Logger.h"

class EventHandler
{
  public:
    EventHandler();
    ~EventHandler(){}

    float m_Vtype_ = -1;

  private:
  // Logging
    Logger logger_;
};


#endif
