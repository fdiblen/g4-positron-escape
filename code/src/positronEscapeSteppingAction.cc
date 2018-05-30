#include "positronEscapeSteppingAction.hh"
#include "positronEscapeEventAction.hh"
#include "positronEscapeDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


#include "positronEscapePrimaryGeneratorAction.hh"


#include "positronEscapeHistoManager.hh"



positronEscapeSteppingAction::positronEscapeSteppingAction(positronEscapeEventAction* eventAction)
: G4UserSteppingAction(),
    fEventAction(eventAction),
    fScoringVolume(0)
{}

 

positronEscapeSteppingAction::~positronEscapeSteppingAction()
{}

 

void positronEscapeSteppingAction::UserSteppingAction(const G4Step* step)
{
    if (!fScoringVolume) { 
        const positronEscapeDetectorConstruction* detectorConstruction
            = static_cast<const positronEscapeDetectorConstruction*>
            (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fScoringVolume = detectorConstruction->GetScoringVolume();   
    }

    // get volume of the current step
    G4LogicalVolume* volume 
        = step->GetPreStepPoint()->GetTouchableHandle()
        ->GetVolume()->GetLogicalVolume();

    // check if we are in scoring volume
    if (volume != fScoringVolume) return;

    // collect energy deposited in this step
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edepStep);  



    // FARUK
    // step info

    G4StepPoint* point1 = step->GetPreStepPoint();
    G4StepPoint* point2 = step->GetPostStepPoint();

    G4ThreeVector pos1 = point1->GetPosition();
    G4ThreeVector pos2 = point2->GetPosition();

    //G4double eDeposit = step->GetTotalEnergyDeposit();

    G4TouchableHandle touch1 = point1->GetTouchableHandle();
    G4VPhysicalVolume* volume1 = touch1->GetVolume();
    G4String volName1 = volume1->GetName();


    G4TouchableHandle touch2 = point2->GetTouchableHandle();
    G4VPhysicalVolume* volume2 = touch2->GetVolume();
    G4String volName2 = volume2->GetName();



    // get analysis manager
    //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    positronEscapeHistoManager* positronEscapeHistoManager = positronEscapeHistoManager::GetInstance();

    // get particle gun dosn't work
    //positronEscapePrimaryGeneratorAction* particleGun = positronEscapePrimaryGeneratorAction::GetParticleGun();

    // fill histograms


    if ( step->GetTrack()->GetTrackID() == 1){  // only primary particles !

        if ( step->GetTrack()->GetCurrentStepNumber() == 1 ) {
            //G4cout 
            //    << "-------------------------------" << G4endl
            //    << "*** NEW PARTICLE ***" << G4endl;
       
                //analysisManager->FillH1(1, point1->GetKineticEnergy());

                ;
        }



        if ( step->GetTrack()->GetTrackStatus() == 2 && volName2 == "Target" ){

            ////G4cout << "!!! PARTICLE STOPPED !!!" << G4endl;
            ////G4cout << "  volName1:" << volName1 << "   volname2:" << volName2 << G4endl;

            //// Fill 1st ntuple ( id = 1)
            ////analysisManager->FillNtupleDColumn(0, particleGun->GetCurrentSourceIndex());
            //analysisManager->FillNtupleDColumn(1,fNtColId[1], step->GetTrack()->GetTrackID());
            //analysisManager->FillNtupleDColumn(1,fNtColId[1], step->GetTrack()->GetDefinition()->GetPDGEncoding());
            //analysisManager->FillNtupleDColumn(1,fNtColId[1], point2->GetPosition().x());
            //analysisManager->FillNtupleDColumn(1,fNtColId[1], point2->GetPosition().y());
            //analysisManager->FillNtupleDColumn(1,fNtColId[1], point2->GetPosition().z());
            //analysisManager->AddNtupleRow(1);
            //
            //
            positronEscapeHistoManager->FillNtupleStopped(-1, step->GetTrack()->GetTrackID(),
                    step->GetTrack()->GetDefinition()->GetPDGEncoding(),point2->GetPosition().x(),
                    point2->GetPosition().y(),point2->GetPosition().z());

            ;
        }




        //if ( point2->GetStepStatus() == fGeomBoundary)
        //    G4cout << "=== PARTICLE LEAVING THE VOLUME ===" << G4endl;
        //

        //G4cout 
        //    << "  SteppingAction::current step:" << step->GetTrack()->GetCurrentStepNumber()
        //    << "  particle name:" << step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName()   
        //    << "  edep:" << eDeposit
        //    << "  step status1:" << point1->GetStepStatus()
        //    << "  step status2:" << point2->GetStepStatus()
        //    << "  volName1:" << volName1
        //    << "  volName2:" << volName2
        //    << "  track status:" << step->GetTrack()->GetTrackStatus() 
        //    << "  trackID:" << step->GetTrack()->GetTrackID() 
        //    << "  preEkine:"  << point1->GetKineticEnergy()
        //    << "  postEkine:" << point2->GetKineticEnergy()
        //    << "  prePos:"    << point1->GetPosition()
        //    << "  postPos:"    << point2->GetPosition()
        //    << "  deltaPos:" << step->GetDeltaPosition() / CLHEP::mm << " mm"
        //    << "  preTotEne:" << point1->GetTotalEnergy() / CLHEP::MeV << " MeV"
        //    << "  postCreatorProcess:" << point2->GetProcessDefinedStep()->GetProcessName()
        //    << G4endl;



    }


}

 

