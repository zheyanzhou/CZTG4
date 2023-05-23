

/// \file B4dRun.hh
/// \brief Definition of the B4Run class

#ifndef B1Run_h
#define B1Run_h 1

#include "G4Run.hh"
#include "globals.hh"

/// Run class
///
/// In RecordEvent() there is collected information event per event 
/// from Hits Collections, and accumulated statistic for the run 

class B1Run : public G4Run
{
  public:
    B1Run();
    virtual ~B1Run();

    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);
    
  public:
   //  G4double* Getedep()  { return fedep; }    
   //  G4double* Getedep2()  { return fedep2; }  
    
   // G4double  Getedep() const { return fedep; }
    const G4double* Getedep() const { return fedep; }      

  private:
    G4int fCollID_core; 
    G4double fedep[9];//for Co-60  the number is copynumber+1
 //   G4double fedep2;//for Cs-137
      
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

