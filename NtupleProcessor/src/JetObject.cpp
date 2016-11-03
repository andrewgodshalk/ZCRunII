/*
JetObject.cpp

 Created : 2016-11-02  godshalk
 Modified: 2016-11-02  godshalk

*/

#include "JetObject.h"

// Intended constructor: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.
JetObject::JetObject(EventMap* e, int i)
  : evt_(e), index_(i),
    pt        (&(evt_->Jet_pt       [index_])),
    eta       (&(evt_->Jet_eta      [index_])),
    phi       (&(evt_->Jet_phi      [index_])),
    mcFlavour (&(evt_->Jet_mcFlavour[index_])),
    btagCSV   (&(evt_->Jet_btagCSV  [index_])),
    vtxMass   (&(evt_->Jet_vtxMass  [index_])),
    logger_("NtupleProcessor", "[JO]       ")
{
    //logger_.trace("JetObject created with index {}", index_);
}
