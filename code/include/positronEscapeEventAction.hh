
#ifndef positronEscapeEventAction_h
#define positronEscapeEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class positronEscapeEventAction : public G4UserEventAction
{
  public:
    positronEscapeEventAction();
    virtual ~positronEscapeEventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    G4double  fEdep;
};

#endif

    
