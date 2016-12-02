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
  : evaluatated_(false), meetsCriteria_(false),
    logger_("NtupleProcessor", "[SPC]       ")
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
    }

  // Return pointer to SP in list.
    return selectionProfiles_[spStr];
}

// Evaluating functions
void SelectionProfileCollection::evaluate(EventHandler* evt)
{ // Send evaluation command to all SPs.
    logger_.trace("evaluate(): called");
    for( auto& sp : selectionProfiles_ ) sp.second->evaluate(evt);
}


void SelectionProfileCollection::reset()
{ // Send reset commands to all SPs.
    logger_.trace("reset(): called");
    evaluatated_ = meetsCriteria_ = false;
    for( auto& sp : selectionProfiles_ ) sp.second->reset();
}


void SelectionProfileCollection::addObjectCriteriaToCollection(SelectionProfile* sp)
{ // Stores pointers to object criteria for each object in collection.
    logger_.debug("addObjectCriteriaToCollection() called for {}", sp->specifier());
  // Store/create an objectCriteria ptr for each object.
    for( string& obj : SelectionProfile::objectLabelStrs_) sp->objCriteria_[obj] = getObjectCriteria(obj, sp->objectSpecifierStrs_[obj]);
}

ObjectCriteria* SelectionProfileCollection::getObjectCriteria(string& type, string& specifier)
{ // Returns pointer to newly created or existing OC w/ given object type and specifier.
    // if(!objCriteria_[type].count(specifier)) objCriteria_[type][specifier] = new ObjectCriteria(specifier);
    if(!objCriteria_[type].count(specifier)) objCriteria_[type][specifier] = ObjectCriteria::createNew(type,specifier);
    return objCriteria_[type][specifier];
}
