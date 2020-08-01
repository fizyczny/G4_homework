//
// $Id: SteppingAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
#include "SteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "NaIHit.hh"
#include "OutputRoot.hh"

SteppingAction::SteppingAction():G4UserSteppingAction()
{
     outputFile=OutputRoot::GetInstance();
     outputFile->CreateFile("POS.root");
}

SteppingAction::~SteppingAction() 
{
     outputFile->SaveOutput();
}


G4int licz=0;

void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
    /*G4Track* theTrack = theStep->GetTrack();
    G4String volumeName = theTrack->GetVolume()->GetName();
    if(volumeName == "fantom")
    {
        
	auto secondaries = theStep->GetSecondaryInCurrentStep();
	nrOfSec+=secondaries->size();
	
    }
    
    if(volumeName =="spinePhys")
    {
	
	//PrintStep(theStep);
        double energy =theStep->GetDeltaEnergy ();
        dep_en-=energy;
        ///std::cout << dep_en << std::endl;
	
    }*/
    G4double energy = theStep ->GetDeltaEnergy();

    if (energy != 0)
    {
       G4StepPoint* prePoint = theStep-> GetPreStepPoint();
       G4double pos_x = prePoint ->GetPosition().x();
       G4double pos_y = prePoint ->GetPosition().y();
       energy=(-energy);
       outputFile->AddPos(licz,energy,pos_x,pos_y);
       ++licz;
       //std::cout << "nr "<< licz << " X_pos "<< pos_x<< " Y_pos "<< pos_y<< " energia "<< energy<<std::endl;
    }
    
    
    
}



void SteppingAction::PrintStep(const G4Step* theStep)
{

    G4Track* theTrack = theStep->GetTrack();
    G4String particleName = theTrack->GetDefinition()->GetParticleName();      
    G4String processName =theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    
    G4double energy = theTrack->GetKineticEnergy() ;
    G4String volumeName = theTrack->GetVolume()->GetName();
    G4double deltaEn = theStep->GetDeltaEnergy();
    int trackNr = theTrack->GetTrackID ();    

    std::cout << " trackNr: " << trackNr
              << " particle: " << particleName
	      << " process: " << processName
	      << " kinetic energy " << energy
	      << " delta en: " << deltaEn
	      << " voulme name: " << volumeName << std::endl;

}

double SteppingAction::dep_en=0;
//double SteppingAction::licznik=0;
int SteppingAction::nrOfSec=0;

