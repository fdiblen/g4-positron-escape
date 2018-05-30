#ifndef positronEscapeSteppingAction_h
#define positronEscapeSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class positronEscapeEventAction;

class G4LogicalVolume;

class positronEscapeSteppingAction : public G4UserSteppingAction
{
  public:
    positronEscapeSteppingAction(positronEscapeEventAction* eventAction);
    virtual ~positronEscapeSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    positronEscapeEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};

#endif
