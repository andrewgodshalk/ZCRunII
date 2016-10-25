/*
EventHandler.cpp

 Created : 2016-10-25  godshalk
 Modified: 2016-10-25  godshalk

*/

// Standard Libraries
#include <iostream>
// Project Specific
#include "EventHandler.h"


EventHandler::EventHandler() :
  logger_("NtupleProcessor_log", "[EH]     ")
{
  // Set up logger
    // logger_ = spdlog::get("NtupleProcessor_log");
    // if(!logger_) std::cerr << "ERROR: LOGGER NOT FOUND." << std::endl;
    // logPrefix_ = (logger_->level() == spdlog::level::trace ? "[EH]    " : "    ");
    logger_.debug("EventHandler Created.");
}
