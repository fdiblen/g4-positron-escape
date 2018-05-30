#include "positronEscapeRunAction.hh"
#include "positronEscapePrimaryGeneratorAction.hh"
#include "positronEscapeDetectorConstruction.hh"
#include "positronEscapeRun.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


#include "positronEscapeHistoManager.hh"

 

positronEscapeRunAction::positronEscapeRunAction()
: G4UserRunAction()
{ 

  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);


  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  //
  
  //histograms
  //
  positronEscapeHistoManager* positronEscapeHistoManager = positronEscapeHistoManager::GetInstance();
  positronEscapeHistoManager->book();



  // add new units for dose
  // 
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;  
  const G4double picogray  = 1.e-12*gray;
   
  new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);        
}

 

positronEscapeRunAction::~positronEscapeRunAction()
{}

 

G4Run* positronEscapeRunAction::GenerateRun()
{
  return new positronEscapeRun; 
}

 

void positronEscapeRunAction::BeginOfRunAction(const G4Run*)
{ 
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);


  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

}

 

void positronEscapeRunAction::EndOfRunAction(const G4Run* run)
{
  // G4int nofEvents = run->GetNumberOfEvent();
  // if (nofEvents == 0) return;
  
  // const positronEscapeRun* positronEscapeRun = static_cast <const positronEscapeRun*> (run);
 




  // // Compute dose
  // //
  // G4double edep  = positronEscapeRun->GetEdep();
  // G4double edep2 = positronEscapeRun->GetEdep2();
  // G4double rms = edep2 - edep*edep/nofEvents;
  // if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;




  //const positronEscapeDetectorConstruction* detectorConstruction
  // = static_cast<const positronEscapeDetectorConstruction*>
  //   (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  //G4double mass = detectorConstruction->GetScoringVolume()->GetMass();
  //G4double dose = edep/mass;
  //G4double rmsDose = rms/mass;

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  
  // FARUK commented
  //const positronEscapePrimaryGeneratorAction* generatorAction
  // = static_cast<const positronEscapePrimaryGeneratorAction*>
  //   (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());

  G4String runCondition;

  //if (generatorAction)
  //{
  //  //const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
  //  const G4GeneralParticleSource* particleGun = generatorAction->GetParticleGun();

  //  //runCondition += particleGun->GetParticleDefinition()->GetParticleName();
  //  //runCondition += " of ";
  //  //G4double particleEnergy = particleGun->GetParticleEnergy();
  //  //runCondition += G4BestUnit(particleEnergy,"Energy");
  //}
        
  // Print
  //  
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  //G4cout
  //   << G4endl
  //   << " The run consists of " << nofEvents << " "<< runCondition
  //   << G4endl
  //   << " Dose in scoring volume : " 
  //   << G4BestUnit(dose,"Dose") << " +- " << G4BestUnit(rmsDose,"Dose")
  //   << G4endl
  //   << "------------------------------------------------------------"
  //   << G4endl
  //   << G4endl;




  positronEscapeHistoManager* positronEscapeHistoManager = positronEscapeHistoManager::GetInstance();

  //save histograms
  //
  positronEscapeHistoManager->PrintStatistic();
  positronEscapeHistoManager->save();

}

 
