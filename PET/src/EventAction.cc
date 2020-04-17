
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"


EventAction::EventAction()
{
     output.open("Energy_dep.txt");
}
 
EventAction::~EventAction()
{
     output.close();
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
     if (SteppingAction::dep_en!=0)
     {
     G4double eventID= anEvent -> GetEventID();
     output<< eventID<< "\t"<<SteppingAction::dep_en << std::endl;
     }
     SteppingAction::dep_en=0;
}



