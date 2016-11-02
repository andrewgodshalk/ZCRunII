/*
EventHandler.cpp

 Created : 2016-10-25  godshalk
 Modified: 2016-10-25  godshalk

*/

// Standard Libraries
//#include <fstream>
//#include <sstream>
// Root Classes
//#include <TLeaf.h>
// Project Specific
#include "EventHandler.h"

//using std::string;
//using std::ifstream;
//using std::stringstream;

EventHandler::EventHandler() :
  logger_("NtupleProcessor", "[EH]     ")//, evtMap_()
{
    logger_.debug("EventHandler Created.");
}

void EventHandler::mapTree(TTree* tree)
{ // Map the input tree to variables locally
    logger_.trace("mapTree(): called");
    tree_ = tree;
    //

  // Current goal: map single level of variabels from tree.
  // Pseudo:
    // Deactivate all variables in tree to save memory. Will reactivate later.
    tree->SetBranchStatus("*",0);

    // Collect list of variables from input (function()) (collect three lists?)
    //getActiveVariables("")
    // Reactivate relavent variables.
    //

/*
  // FOR TEST PURPOSES
    tree_->GetEntry(0);

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
    }
    mappedVariablesFile.close();
*/
}

void EventHandler::evaluateEvent()
{ // Use tree map to set up physics objects
    logger_.trace("evaluateEvent(): called");

    // Do some work
}

/*
double EventHandler::getValueDebug(const char* label, int i)
{
    logger_.trace("Accessing Tree with name {}", tree_->GetName());
    logger_.trace("Accessing Leaf with name {}", tree_->GetLeaf(label)->GetName());
    return 0;
}

double EventHandler::get(const char* v, int i)
{
    if(valFunctions[v] == NULL)
    {
        logger_.error("Function for {} not properly linked.", v);
        return -1;
    }
    return (this->*valFunctions[v]))(v,i);
//    return (this->*(this->valFunctions[v]))(v,i);
}
*/
