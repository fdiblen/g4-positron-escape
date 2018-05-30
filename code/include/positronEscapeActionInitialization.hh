#ifndef positronEscapeActionInitialization_h
#define positronEscapeActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class positronEscapeActionInitialization : public G4VUserActionInitialization
{
  public:
    positronEscapeActionInitialization();
    virtual ~positronEscapeActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
