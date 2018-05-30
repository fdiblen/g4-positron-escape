#include "positronEscapeHistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

positronEscapeHistoManager* positronEscapeHistoManager::instance = 0;

positronEscapeHistoManager::positronEscapeHistoManager()
{
  fFileName[0] = "dataPositronEscape";
  fFactoryOn = false;
  
  // histograms
  for (G4int k=0; k<MaxHisto; k++) {
    fHistId[k] = 0;
    fHistPt[k] = 0;    
  }
  // ntuple
  for (G4int k=0; k<MaxNtCol; k++) {
    fNtColId[k] = 0;
  }  
}

positronEscapeHistoManager::~positronEscapeHistoManager()
{ }


positronEscapeHistoManager* positronEscapeHistoManager::GetInstance()
{
        if (instance == 0) instance = new positronEscapeHistoManager;
        return instance;
}


void positronEscapeHistoManager::book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in positronEscapeHistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(2);
  G4String extension = analysisManager->GetFileType();
  fFileName[1] = fFileName[0] + "." + extension;
      
  // Create directories 
  analysisManager->SetHistoDirectoryName("histo");
  analysisManager->SetNtupleDirectoryName("ntuple");
    
  // Open an output file
  //
  G4bool fileOpen = analysisManager->OpenFile(fFileName[0]);
  if (!fileOpen) {
    G4cout << "\n---> positronEscapeHistoManager::book(): cannot open " << fFileName[1] 
           << G4endl;
    return;
  }
  
  // create selected histograms
  //
  analysisManager->SetFirstHistoId(1);
  analysisManager->SetFirstNtupleId(1);

  fHistId[1] = analysisManager->CreateH1("primaryEnergy","Energy of the generated primary",
                                              100, 0., 4.9*CLHEP::MeV);
  fHistPt[1] = analysisManager->GetH1(fHistId[1]);
                                           
                                  
  // Create 1st ntuple (id = 1)
  analysisManager->CreateNtuple("stopped", "Primaries stopped in target");
  fNtColId[0] =  analysisManager->CreateNtupleDColumn("sourceID");
  fNtColId[1] =  analysisManager->CreateNtupleDColumn("trackID");
  fNtColId[2] =  analysisManager->CreateNtupleDColumn("pdg");
  fNtColId[3] =  analysisManager->CreateNtupleDColumn("posx");
  fNtColId[4] =  analysisManager->CreateNtupleDColumn("posy");
  fNtColId[5] =  analysisManager->CreateNtupleDColumn("posz");
  analysisManager->FinishNtuple();

  // Create 1st ntuple (id = 2)
  analysisManager->CreateNtuple("generated", "Primaries generated in target");
  fNtColId[6] =  analysisManager->CreateNtupleDColumn("sourcePosX");
  fNtColId[7] =  analysisManager->CreateNtupleDColumn("sourcePosY");
  fNtColId[8] =  analysisManager->CreateNtupleDColumn("sourcePosZ");
  analysisManager->FinishNtuple();


  fFactoryOn = true;       
  G4cout << "\n----> Histogram Tree is opened in " << fFileName[1] << G4endl;
}

 

void positronEscapeHistoManager::save()
{
  if (fFactoryOn) {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();    
    analysisManager->Write();
    analysisManager->CloseFile();  
    G4cout << "\n----> Histogram Tree is saved in " << fFileName[1] << G4endl;
      
    delete G4AnalysisManager::Instance();
    fFactoryOn = false;
  }                    
}

 

void positronEscapeHistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
{
  if (ih > MaxHisto) {
    G4cout << "---> warning from positronEscapeHistoManager::FillHisto() : histo " << ih
           << "does note xist; xbin= " << xbin << " w= " << weight << G4endl;
    return;
  }

  if (fHistPt[ih]) fHistPt[ih]->fill(xbin, weight);
}

 

void positronEscapeHistoManager::Normalize(G4int ih, G4double fac)
{
  if (ih >= MaxHisto) {
    G4cout << "---> warning from positronEscapeHistoManager::Normalize() : histo " << ih
           << "  fac= " << fac << G4endl;
    return;
  }

  if (fHistPt[ih]) fHistPt[ih]->scale(fac);
}

 

void positronEscapeHistoManager::FillNtupleStopped(G4double sourceID, G4double trackID,
                                     G4double pdg, G4double posx,
                                     G4double posy, G4double posz)
{                
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // Fill 1st ntuple ( id = 1)
  analysisManager->FillNtupleDColumn(1,fNtColId[0], sourceID);
  analysisManager->FillNtupleDColumn(1,fNtColId[1], trackID);
  analysisManager->FillNtupleDColumn(1,fNtColId[2], pdg);
  analysisManager->FillNtupleDColumn(1,fNtColId[3], posx);
  analysisManager->FillNtupleDColumn(1,fNtColId[4], posy);
  analysisManager->FillNtupleDColumn(1,fNtColId[5], posz);
  analysisManager->AddNtupleRow(1);  
}  


 

void positronEscapeHistoManager::FillNtupleGenerated(G4double sourcePosX, G4double sourcePosY,
                                     G4double sourcePosZ)
{                
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // Fill 1st ntuple ( id = 1)
  analysisManager->FillNtupleDColumn(2,fNtColId[6], sourcePosX);
  analysisManager->FillNtupleDColumn(2,fNtColId[7], sourcePosY);
  analysisManager->FillNtupleDColumn(2,fNtColId[8], sourcePosZ);
  analysisManager->AddNtupleRow(2);  
}  


void positronEscapeHistoManager::PrintStatistic()
{
  if(fFactoryOn) {
    G4cout << "\n ----> print histograms statistic \n" << G4endl;
    
    G4cout 
       << " Primary Energy : mean = " << G4BestUnit(fHistPt[1]->mean(), "Energy") 
               << " rms = " << G4BestUnit(fHistPt[1]->rms(),  "Energy") 
               << G4endl;
  }
}

 


