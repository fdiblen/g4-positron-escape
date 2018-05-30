#ifndef positronEscapePhysicsList_h
#define positronEscapePhysicsList_h 1

#include "G4VModularPhysicsList.hh"

/// Modular physics list
///
/// It includes the folowing physics builders
/// - G4DecayPhysics
/// - G4RadioactiveDecayPhysics
/// - G4EmStandardPhysics

class positronEscapePhysicsList: public G4VModularPhysicsList
{
public:
  positronEscapePhysicsList();
  virtual ~positronEscapePhysicsList();

  virtual void SetCuts();
};

#endif

