/*
SelectionProfileCollection.cpp

 Created : 2016-11-30  godshalk
 Modified: 2016-11-30  godshalk

*/

// Project Specific classes
#include "SelectionProfileCollection.h"

// CONSTRUCTOR
SelectionProfileCollection::SelectionProfileCollection()
  : logger_("NtupleProcessor", "[SPC]       ")
{
    logger_.trace("SelectionProfileCollection() created.");
}

SelectionProfile* SelectionProfileCollection::getSelectionProfile(std::string spStr)
{ // Returns a pointer to an SP. If it doesn't exist, it creates it based on the given string.
    logger_.debug("getSelectionProfile() called for {}", spStr);

  // If the SP doesn't exist, create it.
    if(!selectionProfiles_.count(spStr))
    {   logger_.debug("Key not found in list of SPs. Creating new SP({})", spStr);
        selectionProfiles_[spStr] = new SelectionProfile(spStr);

      // If the specified lepton criteria isn't already stored, store it.
        // string newLepCrit = selectionProfiles_[spStr]->getObjectCriteriaString("L");
        // if(!lepCriteria_.count(newLepCrit))
        // {   logger_.debug("Adding Lepton Criteria to lepCriteria_: {}", newLepCrit);
        //     lepCriteria_[newLepCrit] = vector<LeptonObject*>(0);
        // }
    }

  // Return pointer to SP in list.
    return selectionProfiles_[spStr];
}
