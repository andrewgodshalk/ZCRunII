/*
SelectionProfileCollection.cpp

 Created : 2016-11-30  godshalk
 Modified: 2016-11-30  godshalk

*/

// Project Specific classes
#include "SelectionProfileCollection.h"

using std::string;

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
        selectionProfiles_[spStr] = new SelectionProfile(this, spStr);
        //addObjectCriteriaToCollection(selectionProfiles_[spStr]);
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

void SelectionProfileCollection::addObjectCriteriaToCollection(SelectionProfile* sp)
{ // Stores pointers to object criteria for each object in collection.
    logger_.debug("addObjectCriteriaToCollection() called for {}", sp->specifier());
  // Store/create an objectCriteria ptr for each object.
    for( string& obj : SelectionProfile::objectLabelStrs_) sp->objCriteria_[obj] = getObjectCriteria(obj, sp->objectSpecifierStrs_[obj]);
}

ObjectCriteria* SelectionProfileCollection::getObjectCriteria(string& type, string& specifier)
{ // Returns pointer to newly created or existing OC w/ given object type and specifier.
    if(!objCriteria_[type].count(specifier)) objCriteria_[type][specifier] = new ObjectCriteria(specifier);
    return objCriteria_[type][specifier];
}
