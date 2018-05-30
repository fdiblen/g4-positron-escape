#include "positronEscapePrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


#include "G4GeneralParticleSource.hh"



#include "positronEscapeHistoManager.hh"

 

positronEscapePrimaryGeneratorAction::positronEscapePrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0) 
{

    fParticleGun = new G4GeneralParticleSource();


  //G4int n_particle = 1;
  //fParticleGun  = new G4ParticleGun(n_particle);

  //// default particle kinematic
  //G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  //G4String particleName;
  //G4ParticleDefinition* particle
  //  = particleTable->FindParticle(particleName="gamma");
  //fParticleGun->SetParticleDefinition(particle);
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  //fParticleGun->SetParticleEnergy(6.*MeV);



}

 

positronEscapePrimaryGeneratorAction::~positronEscapePrimaryGeneratorAction()
{
  delete fParticleGun;
}

 

void positronEscapePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  ////this function is called at the begining of ecah event
  ////

  //// In order to avoid dependence of PrimaryGeneratorAction
  //// on DetectorConstruction class we get Envelope volume
  //// from G4LogicalVolumeStore.
  //
  //G4double envSizeXY = 5 * mm;
  //G4double envSizeZ =  5 * mm;

  //G4double x0 =  envSizeXY + (G4UniformRand()-0.5);
  //G4double y0 =  envSizeXY + (G4UniformRand()-0.5);
  //G4double z0 = -0.5 + envSizeZ;
  //
  //fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  fParticleGun->GeneratePrimaryVertex(anEvent);


    positronEscapeHistoManager* positronEscapeHistoManager = positronEscapeHistoManager::GetInstance();

    positronEscapeHistoManager->FillHisto(1, fParticleGun->GetParticleEnergy() ,1);

    positronEscapeHistoManager->FillNtupleGenerated(fParticleGun->GetParticlePosition().x(),
            fParticleGun->GetParticlePosition().y(), fParticleGun->GetParticlePosition().z());

  if(anEvent->GetEventID() <= 50){
      G4cout << "PrimaryGeneratorAction:"
          << "  event:" <<   anEvent->GetEventID()
          << "  #source:" << fParticleGun->GetNumberofSource()
          << "  currentSource:" << fParticleGun->GetCurrentSourceIndex()
          << "  #par:" << fParticleGun->GetNumberOfParticles()
          << "  name:" << fParticleGun->GetParticleDefinition()->GetParticleName()
          << "  energy:" << fParticleGun->GetParticleEnergy()
          << "  momentumn:" << fParticleGun->GetParticleMomentumDirection()
          << "  pos:" << fParticleGun->GetParticlePosition()
          << "  intensity:" << fParticleGun->GetCurrentSourceIntensity()
          << "  time:" << fParticleGun->GetParticleTime()
          << G4endl;

  }






}

 

