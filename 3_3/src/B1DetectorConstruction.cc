//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4SDChargedFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
//#include "G4PSTrackLength.hh"
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4SDParticleWithEnergyFilter.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{


  // Define materials 
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance(); 
  // Envelope parameters
  G4double env_sizeXY = 60*mm, env_sizeZ = 60*mm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  //CZTmaterial
  //A mixture is defined by its mass fraction
  G4double z, a, density;
  G4int ncomponents, natoms;
  G4Element*Cd =new G4Element("Cadmium" , "Cd" , z=48., a =112.4*g/mole);
  G4Element*Zn =new G4Element("Zinc" , "Zn" , z=30., a =65.37*g/mole);
  G4Element*Te =new G4Element("Tellurium" , "Te" , z=52., a =127.6*g/mole);
  G4Material* czt_mat = new G4Material("CZT" , density=5.85*g/cm3 , ncomponents=3);
  czt_mat->AddElement(Cd, natoms=96);
  czt_mat->AddElement(Zn, natoms=4);
  czt_mat->AddElement(Te, natoms=100);
  
  
 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;

  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,0),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 

  //     
  // czt
  //
  //next command line is used if I want to change the czt mother world
  //G4ThreeVector pos2 = G4ThreeVector(0, -1*cm, 7*cm);
  //czt parameters
  G4double czt_sizeXY = 3*mm, czt_sizeZ = 10*mm;

  
  G4Box* solidczt =    
    new G4Box("czt",                    //its name
        0.5*czt_sizeXY, 0.5*czt_sizeXY, 0.5*czt_sizeZ); //its size
      
  G4LogicalVolume* logicczt =                         
    new G4LogicalVolume(solidczt,            //its solid
                        czt_mat,             //its material
                        "LOGICczt");              //its name
               


  G4int Numczt=3;
  G4int copynum=0;
  G4double x=0*mm;
  G4double y=0*mm;
  G4double kz=5*mm;
  G4double gap=0.0000000000001*mm;
  for (int i=0;i<Numczt;i++) {
      for (int j=0;j<Numczt;j++) {
          copynum=i*Numczt+j;
          x=0.5*czt_sizeXY+j*(czt_sizeXY+gap);
          y=0.5*czt_sizeXY+i*(czt_sizeXY+gap);
          new G4PVPlacement(0,
                        G4ThreeVector(x,y,kz),
                        logicczt,
                        "czt",
                        logicEnv,
                        false,
                        copynum,
                        false);
           }
     }        


  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void B1DetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  // 
  // Scorers
  //

  // declare Absorber as a MultiFunctionalDetector scorer
  //  
  G4MultiFunctionalDetector* myDetector 
    = new G4MultiFunctionalDetector("Mydet");
  G4SDManager::GetSDMpointer()->AddNewDetector(myDetector);

  G4PSEnergyDeposit* primitive;

  primitive = new G4PSEnergyDeposit("Edep",0);
 
  myDetector->RegisterPrimitive(primitive);
 

  SetSensitiveDetector("LOGICczt",myDetector);
  
  
}






















