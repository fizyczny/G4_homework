
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"


EventAction::EventAction()
{
     output.open("Energy_dep.txt");
     licznik=0;
     licz2=0;
}
 
EventAction::~EventAction()
{
     std::cout<<"liczba czastek wtornych #1 = "<<licznik<<std::endl;
     std::cout<<"liczba czastek wtornych #2 = "<<licz2<<std::endl;

     output.close();
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{	
     
     //std::cout<<SteppingAction::nrOfSec<<std::endl;
     licznik +=SteppingAction::nrOfSec;
     SteppingAction::nrOfSec=0;
     if (SteppingAction::dep_en!=0)
     {
     G4double eventID= anEvent -> GetEventID();
     output<< eventID<< "\t"<<SteppingAction::dep_en << std::endl;
     
     }
     SteppingAction::dep_en=0;
     
     
     G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
     if(!hitsCollOfThisEvent)
        return;


     G4SDManager* SDmanager2 = G4SDManager::GetSDMpointer();
     G4int fantom_nr = SDmanager2->GetCollectionID("hfSensitiveDet/nos");
     //std::cout<<fantom_nr << std::endl;



     G4THitsMap<G4double>* fantomCollection = static_cast<G4THitsMap<G4double>*>( hitsCollOfThisEvent->GetHC(fantom_nr));

     std::map< G4int,G4double*>* fantomcolMap = fantomCollection->GetMap();
     std::map< G4int,G4double*>::iterator itr;
     
     for (itr = fantomcolMap->begin(); itr != fantomcolMap->end(); itr++) 
     {
       // std::cout << (itr->first) << " " << *(itr->second) << std::endl;
	licz2+= *(itr->second);

     } 
/*
     
    G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    if(!hitsCollOfThisEvent)
        return;


    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    G4int naIcollId = SDmanager->GetCollectionID("naISensitiveDet/eDep");
    //std::cout<<naIcollId << std::endl;



    G4THitsMap<G4double>* NaIHitsCollection = static_cast<G4THitsMap<G4double>*>( hitsCollOfThisEvent->GetHC(naIcollId));

    std::map< G4int,G4double*>* NaIcolMap = NaIHitsCollection->GetMap();
    std::map< G4int,G4double*>::iterator itr;
    for (itr = NaIcolMap->begin(); itr != NaIcolMap->end(); itr++) 
    {
        std::cout << (itr->first) << " " << *(itr->second) << std::endl;

    } */
}



