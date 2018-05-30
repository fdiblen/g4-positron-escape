#ifndef positronEscapeDetectorConstruction_h
#define positronEscapeDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class positronEscapeDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    positronEscapeDetectorConstruction();
    virtual ~positronEscapeDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume*  fScoringVolume;
};


#endif

