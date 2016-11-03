#ifndef GUARD_RootFileManager_h
#define GUARD_RootFileManager_h

/*------------------------------------------------------------------------------
  RootFileManager Class

 Created : 2016-11-03  godshalk
 Modified: 2016-11-03  godshalk

 DESCRIBE HERE.

------------------------------------------------------------------------------*/

// Standard Libraries
#include <string>
// Root Classes
// Project Specific classes
#include "Logger.h"


class RootFileManager
{
  public:
    RootFileManager(std::string);
    ~RootFileManager(){}

  private:
    std::string timestamp_;
    Logger logger_;
};

#endif
