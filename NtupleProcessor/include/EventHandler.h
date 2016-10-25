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

class EventHandler
{
  public:
    EventHandler();
    ~EventHandler(){}

    float m_Vtype_ = -1;

  private:
  // Logging
    std::shared_ptr<spdlog::logger> logger_;
    std::string logPrefix_;
};


#endif
