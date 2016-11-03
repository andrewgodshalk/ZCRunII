/*
LeptonObject.cpp

 Created : 2016-11-02  godshalk
 Modified: 2016-11-02  godshalk

*/

#include "LeptonObject.h"

// Intended constructor: Creates an object mapped to the variables at the 'i'th index of the given event's arrays.
LeptonObject::LeptonObject(EventMap* e, int i)
  : evt_(e), index_(i),
    charge     (&(evt_->selLeptons_charge    [index_])),
    pt         (&(evt_->selLeptons_pt        [index_])),
    eta        (&(evt_->selLeptons_eta       [index_])),
    phi        (&(evt_->selLeptons_phi       [index_])),
    pfRelIso04 (&(evt_->selLeptons_pfRelIso04[index_])),
    logger_("NtupleProcessor", "[LO]       ")
{
    //logger_.trace("LeptonObject created with index {}", index_);
}
