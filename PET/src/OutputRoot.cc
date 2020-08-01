#include "OutputRoot.hh"


OutputRoot::OutputRoot()
{
   rootManager=G4RootAnalysisManager::Instance();
   
   rootManager->SetFirstNtupleId(0);
   

}

void OutputRoot::CreateFile(G4String filename)
{
    rootManager->OpenFile(filename);
    //NaIDetectorTupleId=0;
    //CreateNaITuple();
    PosTupleId=0;
    CreatePosTuple();
}
void OutputRoot::SaveOutput()
{
   rootManager->Write();
   rootManager->CloseFile();
}

void OutputRoot::CreateNaITuple()
{
   rootManager->CreateNtuple("NaIInfo","Energy deposit and step lenght in NaI detector");
   rootManager->CreateNtupleIColumn("eventId");
   rootManager->CreateNtupleIColumn("detectorId");
   rootManager->CreateNtupleDColumn("energyDep");
   rootManager->CreateNtupleDColumn("stepLength");
  
   rootManager->FinishNtuple();
}



void OutputRoot::AddNaIHit(int eventId, int detectorId, double enDep, double stepLength)
{
    int cloId=0;
    rootManager->FillNtupleIColumn(NaIDetectorTupleId, cloId, eventId);
    rootManager->FillNtupleIColumn(NaIDetectorTupleId, ++cloId, detectorId);
    rootManager->FillNtupleDColumn(NaIDetectorTupleId, ++cloId, enDep);
    rootManager->FillNtupleDColumn(NaIDetectorTupleId, ++cloId, stepLength);
    rootManager->AddNtupleRow(NaIDetectorTupleId);
}

void OutputRoot::CreatePosTuple()
{
   rootManager->CreateNtuple("PosInfo","Position and energy");
   rootManager->CreateNtupleIColumn("eventId");
   rootManager->CreateNtupleDColumn("energy");
   rootManager->CreateNtupleDColumn("pos_x");
   rootManager->CreateNtupleDColumn("pos_y");

   rootManager->FinishNtuple();
}
void OutputRoot::AddPos(int eventId, double energy, double pos_x, double pos_y)
{
    int cloId=0;
    
    rootManager->FillNtupleIColumn(PosTupleId, cloId, eventId);
    rootManager->FillNtupleDColumn(PosTupleId, ++cloId, energy);
    rootManager->FillNtupleDColumn(PosTupleId, ++cloId, pos_x);
    rootManager->FillNtupleDColumn(PosTupleId, ++cloId, pos_y);
    rootManager->AddNtupleRow(PosTupleId);
}


OutputRoot* OutputRoot::instance=0;
