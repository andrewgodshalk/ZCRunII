#ifndef GUARD_RootFileManager_h
#define GUARD_RootFileManager_h

/*------------------------------------------------------------------------------
  RootFileManager Class

 Created : 2016-11-03  godshalk
 Modified: 2016-11-03  godshalk

 Class that manages the creation of a TFile, the creation of histograms within
 that file, and the saving of that file.



------------------------------------------------------------------------------*/

// Standard Libraries
#include <map>
#include <string>
#include <vector>
// Root Classes
#include <TFile.h>
#include <TH1.h>
// Project Specific classes
#include "Logger.h"


class RootFileManager
{
  public:
    RootFileManager(std::string);
    ~RootFileManager(){}

    TH1* createHistogram(std::string);   // Creates a histogram within the root file, based on a configuration string.
    void close();   // Saves and closes the root file.

  private:
    bool getHistoPropsFromString(const std::string&);   // Pulls histogram properties from the input string, stores in hProps_;

  // File information
    std::string fileName_;
    std::string filePath_;
    TFile* file_;

    std::map<TH1F*> histograms_;       // Map of histograms, keyed by their names.
    std::vector<std::string> hProps_;  // Vector initialized at runtime to store histogram properties read in from a configuration string.

    Logger logger_;
};

#endif
