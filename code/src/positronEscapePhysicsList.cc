#include "positronEscapePhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

 

positronEscapePhysicsList::positronEscapePhysicsList() 
: G4VModularPhysicsList(){
  SetVerboseLevel(1);



  G4cout <<  "*****************************" << G4endl
         <<  " CONSTRUCTING THE PHYSICS"
         << G4endl;

  G4int verbose = 1;
  // Default physics
  G4cout <<  "* Adding G4DecayPhysics" << G4endl;
  RegisterPhysics(new G4DecayPhysics(verbose));

  // Radioactive decay
  G4cout <<  "* Adding G4RadioactiveDecayPhysics" << G4endl;
  RegisterPhysics(new G4RadioactiveDecayPhysics(verbose));

  // EM physics
  G4cout <<  "* Adding G4EmStandardPhysics" << G4endl;
  RegisterPhysics(new G4EmStandardPhysics(verbose));



  G4cout <<  "*****************************" << G4endl
         << G4endl;


}

 

positronEscapePhysicsList::~positronEscapePhysicsList()
{ 
}

 

void positronEscapePhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}  
