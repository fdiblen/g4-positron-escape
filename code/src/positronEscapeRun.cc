
#include "positronEscapeRun.hh"

 

positronEscapeRun::positronEscapeRun()
: G4Run(),
  fEdep(0.), 
  fEdep2(0.)
{} 

 

positronEscapeRun::~positronEscapeRun()
{} 
 
 

void positronEscapeRun::Merge(const G4Run* run)
{
  const positronEscapeRun* localRun = static_cast<const positronEscapeRun*>(run);
  fEdep  += localRun->fEdep;
  fEdep2 += localRun->fEdep2;

  G4Run::Merge(run); 
} 

 

void positronEscapeRun::AddEdep (G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}

 


