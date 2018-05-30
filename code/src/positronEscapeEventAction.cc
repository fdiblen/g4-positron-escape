#include "positronEscapeEventAction.hh"
#include "positronEscapeRun.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

positronEscapeEventAction::positronEscapeEventAction()
: G4UserEventAction(),
  fEdep(0.)
{} 


positronEscapeEventAction::~positronEscapeEventAction()
{}


void positronEscapeEventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
}


void positronEscapeEventAction::EndOfEventAction(const G4Event*)
{   
  // accumulate statistics in positronEscapeRun
  positronEscapeRun* run 
    = static_cast<positronEscapeRun*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddEdep(fEdep);



  //// get analysis manager
  //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  //// fill histograms
  ////
  //analysisManager->FillH1(1, absoEdep);
  //analysisManager->FillH1(2, gapEdep);
  //analysisManager->FillH1(3, absoTrackLength);
  //analysisManager->FillH1(4, gapTrackLength);


  //  // fill ntuple
  ////
  //analysisManager->FillNtupleDColumn(0, absoEdep);
  //analysisManager->FillNtupleDColumn(1, gapEdep);
  //analysisManager->FillNtupleDColumn(2, absoTrackLength);
  //analysisManager->FillNtupleDColumn(3, gapTrackLength);
  //analysisManager->AddNtupleRow();




  ////print per event (modulo n)
  ////
  //G4int eventID = event->GetEventID();
  //G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  //if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
  //  G4cout << "---> End of event: " << eventID << G4endl;
  //  PrintEventStatistics(absoEdep, absoTrackLength, gapEdep, gapTrackLength);
  //}


}
