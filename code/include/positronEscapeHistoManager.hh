#ifndef positronEscapeHistoManager_h
#define positronEscapeHistoManager_h 1

#include "globals.hh"

#include "g4root.hh"

const G4int MaxHisto = 5;
const G4int MaxNtCol = 9;

class positronEscapeHistoManager
{
  public:

    positronEscapeHistoManager();
   ~positronEscapeHistoManager();

   static positronEscapeHistoManager* GetInstance();

    void book();
    void save();

    void FillHisto(G4int id, G4double e, G4double weight = 1.0);
    void Normalize(G4int id, G4double fac);    


    void FillNtupleStopped(G4double sourceID, G4double trackID,
                                     G4double pdg, G4double posx,
                                     G4double posy, G4double posz);



    void FillNtupleGenerated(G4double sourcePosX, G4double sourcePosY,
                                     G4double sourcePosZ);


    
    void PrintStatistic();        

  private:

    static positronEscapeHistoManager* instance;

    G4String      fFileName[2];
    G4bool        fFactoryOn;    

    G4int         fHistId[MaxHisto];
    G4AnaH1*      fHistPt[MaxHisto];
    G4int         fNtColId[MaxNtCol];
};

#endif

