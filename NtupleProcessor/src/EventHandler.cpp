/*
EventHandler.cpp

 Created : 2016-10-25  godshalk
 Modified: 2016-10-25  godshalk

*/

// Standard Libraries
#include <fstream>
#include <sstream>
// Root Classes
#include <TLeaf.h>
// Project Specific
#include "EventHandler.h"

using std::string;
using std::ifstream;
using std::stringstream;

EventHandler::EventHandler() :
  logger_("NtupleProcessor", "[EH]     ")//, evtMap_()
{
    logger_.debug("EventHandler Created.");
}

void EventHandler::mapTree(TTree* tree)
{ // Map the input tree to variables locally
    logger_.trace("mapTree(): called");
    tree_ = tree;

  // input mapped variabeles from file.
    string mappedVariablesFileName = "NtupleProcessor/config/mapped_variables.config";
    logger_.trace("Inputting mapped variables file: {}", mappedVariablesFileName);
    ifstream mappedVariablesFile(mappedVariablesFileName);
    if(!mappedVariablesFile.is_open()) logger_.error("Unable to open mapped variables file {}", mappedVariablesFileName);
    string line, label, option; TLeaf* leaf;
    while(getline(mappedVariablesFile, line))
    { // Configure mapped variable based on label given and options designated in config file
      logger_.trace("Read in line: {}", line);
      stringstream linestr(line);

      if(!(linestr >> label)) continue;
      logger_.trace("  Extracted part: {}", label);
      leaf = tree->GetLeaf(label.c_str());
      if(!leaf){ logger_.error("  Unable to map {} from tree", label); continue;}

      //vals[label.c_str()] = getVal{ [this,label](int i){getValue(label.c_str(), i);}};
      vals[label.c_str()] = getValue;
    }
    mappedVariablesFile.close();
}

void EventHandler::evaluateEvent()
{ // Use tree map to set up physics objects
    logger_.trace("evaluateEvent(): called");

    // Do some work
}

// double EventHandler::getValue(const char* label, int i)
// {
//     return tree_->GetLeaf(label.c_str())->GetValue(i);
// }
