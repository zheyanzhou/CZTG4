
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
  for (int i=0;i<36;i++) {
	fedep[i]=0.0;
   }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1Run::~B1Run()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1Run::RecordEvent(const G4Event* event)
{
    for (int i=0;i<36;i++) {
        fedep1[i]=0.0;
    }
    
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
    fedep1[index]+=edep;
  } 

     
    
    //  G4int evtNb = event->GetEventID();
    //next add something to output the deposited energy of every gamma
    //打开文件imaging.txt。

     std::ofstream out;
     out.open("edep.txt",std::ios::app);
     
	 //将光纤矩阵中记录的能量沉积输入到文件imaging.txt中
	// for (int i=0;i<9;i++) {
            //if ((i+1)%3==0){
           // out<<evtNb<<'\n';
                   out<<edep<<'\n'<<std::flush;
                   //}
           // else{
	      // out<<std::setprecision (6) << std::scientific<<edep<<'\t'<<std::flush;
                //}           
          // }
          //  out<<'\n'<<std::endl;     
		 //关闭文件
	    out.close();
//////////////////////////////////////////////////////////////////////////	    
   
    out.open("fedep1.txt",std::ios::app);

    //将光纤矩阵中记录的能量沉积输入到文件imaging.txt中
    // for (int i=0;i<9;i++) {
    //if ((i+1)%3==0){
    //out<<evtNb<<'\n';
    for (int i=0;i<36;i++) {
        out<<fedep1[i]<<" "<<std::flush;
    }
    // else{
    // out<<std::setprecision (6) << std::scientific<<edep<<'\t'<<std::flush;
    //}
    // }
    out<<std::endl;
    //关闭文件
    out.close();
 

  G4Run::RecordEvent(event);      
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1Run::Merge(const G4Run* aRun)
{
  const B1Run* localRun = static_cast<const B1Run*>(aRun);
  for (int i=0;i<36;i++) {

  	fedep[i]+=localRun->fedep[i];
    
  }

  G4Run::Merge(aRun); 
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
