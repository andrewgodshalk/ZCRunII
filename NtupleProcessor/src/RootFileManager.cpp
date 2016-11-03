/*------------------------------------------------------------------------------
RootFileManager.cpp
 Created : 2016-11-03  godshalk
 Modified: 2016-11-03  godshalk
------------------------------------------------------------------------------*/


// Project Specific classes
#include "RootFileManager.h"

using std::string;

RootFileManager::RootFileManager(string ts)
  : timestamp_(ts),
    logger_("NtupleProcessor", "[RF]   ")
{
    logger_.debug("RootFileManager created.");
}
