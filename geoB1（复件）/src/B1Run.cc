
//
/// \file B4dRun.cc
/// \brief Implementation of the B4dRun class

#include "B1Run.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1Run::B1Run()
 : G4Run(), 
   fCollID_core(-1)
{
  for (int i=0;i<9;i++) {
	fedep[i]=0.0;
   }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1Run::~B1Run()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1Run::RecordEvent(const G4Event* event)
{

  if ( fCollID_core < 0 ) {
   fCollID_core 
     = G4SDManager::GetSDMpointer()->GetCollectionID("Mydet/Edep");
   //G4cout << " fCollID_core: " << fCollID_core << G4endl;   
  }
 
  //Hits collections
  //  
  G4HCofThisEvent* HCE = event->GetHCofThisEvent();
  if(!HCE) return;
               
   
  G4THitsMap<G4double>* evtMap = 
    static_cast<G4THitsMap<G4double>*>(HCE->GetHC(fCollID_core));
  
//  G4int index=0;
//  G4double Cs137=1.17*MeV;
  G4int index=0;
  G4double edep;            
  std::map<G4int,G4double*>::iterator itr;
  for (itr = evtMap->GetMap()->begin(); itr != evtMap->GetMap()->end(); itr++) {
    index=(itr->first);
    edep=*(itr->second);
    fedep[index]+=edep;

  } 

 

  G4Run::RecordEvent(event);      
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1Run::Merge(const G4Run* aRun)
{
  const B1Run* localRun = static_cast<const B1Run*>(aRun);
  for (int i=0;i<9;i++) {

  	fedep[i]+=localRun->fedep[i];
    
  }

  G4Run::Merge(aRun); 
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
