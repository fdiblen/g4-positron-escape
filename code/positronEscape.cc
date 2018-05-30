
#include "positronEscapeDetectorConstruction.hh"
#include "positronEscapeActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"


#include <time.h>

#include "positronEscapePhysicsList.hh"

#include "positronEscapeSimulationInfo.hh"


 

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  // random seed
  G4long seed=time(0); //returns time in seconds as an integer
  CLHEP::HepRandom::setTheSeed(seed);
  CLHEP::HepRandom::showEngineStatus();



  // Construct the default run manager
  //
//#ifdef G4MULTITHREADED
//  G4MTRunManager* runManager = new G4MTRunManager;
//  runManager->SetNumberOfThreads(1);
//#else
//  G4RunManager* runManager = new G4RunManager;
//#endif

  G4RunManager* runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new positronEscapeDetectorConstruction());

  // Physics list
  G4VModularPhysicsList* physicsList = new positronEscapePhysicsList();
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  //runManager->SetUserInitialization(new positronEscapePhysicsList);
    

  // Initialize positronEscapeSimulationInfo class
  positronEscapeSimulationInfo* siminfo = positronEscapeSimulationInfo::GetInstance();


  // User action initialization
  runManager->SetUserInitialization(new positronEscapeActionInitialization());

  

 // AnalysisManager* analysis = AnalysisManager::GetInstance();

 // //Check if root filename is given as a Commandline parameter
 // //otherwise create ROOT file under "data" directory and its name is "SlitDataG4.root"
 // if( outputFile && outputFile != "" ){

 //         analysis->SetAnalysisFileName(outputFile);

 // }

 // //Create ROOT file etc...
 // analysis->book();




  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();



  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  


 ////FINISH ANALYSIS
 //if (analysis -> IsTheTFile()) analysis->flush();     // Finalize & write the root file


  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
