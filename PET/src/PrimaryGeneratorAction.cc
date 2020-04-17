
// $Id: PrimaryGeneratorAction.cc 15.10.2018 A Fijalkowska $
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
#include <math.h>
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
using namespace std;


PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();
    SetUpDefault();
    
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::SetUpDefault()
{
	
     G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
     particleGun->SetParticleDefinition(particle);
     particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
     particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
     particleGun->SetParticleEnergy(500.0*keV);
     
     int size =particleTable->size();
     cout <<"Rozmiar tablicy czastek "<<size<<endl;
     for (int i = 0; i!=size; i++)
     {
         cout << particleTable->GetParticleName(i)<<" ";
     }
     cout<<endl;

}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
     GeneratePosirtonIncident(anEvent);

    // GenerateBackgroundIncident(anEvent);
}	

void PrimaryGeneratorAction::GeneratePosirtonIncident(G4Event* anEvent)
{
     G4double thetaMin =0*deg;
     G4double thetaMax =180*deg;
     G4double phiMin =0*deg;
     G4double phiMax =360*deg;
     G4ParticleDefinition* particle = particleTable->FindParticle("e+");
     particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
     particleGun->SetParticleDefinition(particle);
     particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection(thetaMin,thetaMax,phiMin,phiMax));
     particleGun->SetParticleEnergy(587.0*keV);
     particleGun->GeneratePrimaryVertex(anEvent);

     
}	


//G4ThreeVector PrimaryGeneratorAction::GenerateIsotropicDirection()
//{
//   double cosTheta = 2.*G4UniformRand() - 1.;
//   double sinTheta = pow(1.-cosTheta*cosTheta, 0.5);
//   double phi = G4UniformRand()*2.*M_PI;
//   return G4ThreeVector(sinTheta*cos(phi), sinTheta*sin(phi), cosTheta);
//}


G4ThreeVector PrimaryGeneratorAction::GenerateIsotropicDirection(G4double thetaMin,G4double thetaMax,G4double phiMin,G4double phiMax)
{
  
   double cosTheta = G4UniformRand()*(cos(thetaMin) - cos(thetaMax)) + cos(thetaMax);

   double sinTheta = pow(1-pow(cosTheta, 2), 0.5);
   double phi = G4UniformRand()*(phiMax-phiMin)+phiMin;

   return G4ThreeVector(sinTheta*cos(phi), sinTheta*sin(phi), cosTheta);
   
}

void PrimaryGeneratorAction::GenerateBackgroundIncident(G4Event* anEvent)
{
     double wym = 1.5*m;
     G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
     particleGun->SetParticleDefinition(particle);
     particleGun->SetParticleEnergy(587.0*keV);
     particleGun->SetParticlePosition(G4ThreeVector((2*G4UniformRand()-1)*wym,(2*G4UniformRand()-1)*wym,(2*G4UniformRand()-1)*wym));
     particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection(0*deg,180*deg,0*deg,360*deg));
     particleGun->GeneratePrimaryVertex(anEvent);

     
}
