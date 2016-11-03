/*------------------------------------------------------------------------------
RootFileManager.cpp
 Created : 2016-11-03  godshalk
 Modified: 2016-11-03  godshalk
------------------------------------------------------------------------------*/


// Project Specific classes
#include "RootFileManager.h"

using std::string;

RootFileManager::RootFileManager(string f)
  : fileName_(f), filePath_("output/"), hProps_(10,""), (logger_("NtupleProcessor", "[RF]       ")
{ //
    logger_.debug("RootFileManager created.");
    logger_.debug("File name: {}", fileName_);
    logger_.debug("File path: {}", filePath_);

  // Open root file.
    logger_.debug("Opening file {}", (filePath_+fileName_).c_str() );
    file_ = TFile::Open((filePath_+fileName_).c_str(), "RECREATE");
}

TH1* createHistogram(string configStr)
{ // Creates a histogram within the root file, based on a configuration string.
    getHistoPropsFromString(configStr);

  // Move to file within ROOT framework.
    file_->cd();
}

void RootFileManager::close()
{ // Saves and closes the root file.
    logger_.trace("RootFileManager closing file: {}", fileName_);
    file_->Close();
}

bool RootFileManager::getHistoPropsFromString(const string& cfgStr)
{ // Pulls histogram properties from the input string, stores in hProps_;
  // Configuration string formats:
  // <path>; <name> ;<title> ;<xlabel> ;<ylabel> ;<binsize> ;<xmax> ;<ymax> [;<type>] [;other options]
  // - type float by default. Can also say int.
  // - properties are delimited by semicolons.
  // - extra space before or after the semicolon will be ignored.
     logger_.trace("getHistoPropsFromString() called {}", cfgStr);
    // string::const_iterator strIter     = cfgStr.begin();
    // string::const_iterator strEnd      = cfgStr.end()  ;
    // string::const_iterator substrBegin = cfgStr.begin();
    // string::const_iterator substrEnd   = cfgStr.begin();
    // int storedProps = 0;
    // while(strIter!=strEnd)
    // { // Until the end of the string has been met...
    //   // Move through the string until the end or the next semicolon is met.
    //
    // }

  // Check to make sure the correct number of properties are stored. Return false if not.
    // if(currentProp != 10)
    // {   logger_.error("getHistoPropsFromString(): Only {} properties specified in histogram configurationstring: {}", storedProps, cfgStr);
    //     return false;
    // }

    return true;
}
