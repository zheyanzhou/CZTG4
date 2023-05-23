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
/// \file B1RunAction.cc
/// \brief Implementation of the B1RunAction class

#include "B1RunAction.hh"
#include "B1Run.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
// #include "B1Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
//#include "G4AccumulableManager.hh"
//#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include<iostream>
#include<fstream>
#include<iomanip>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::B1RunAction()
: G4UserRunAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4Run* B1RunAction::GenerateRun()
{
  return new B1Run; 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::BeginOfRunAction(const G4Run*)
{ 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::EndOfRunAction(const G4Run* run)
{

  // Print
  //  
  
   const B1Run* b1Run = static_cast<const B1Run*>(run);
  if (IsMaster()) {
  
     //调用run中创建的Getedep函数获得各个光纤的能量沉积，保存到数组edep中。
     const G4double* edep=b1Run->Getedep();
     
	 //打开文件imaging.txt。
     std::ofstream out;
	 	 out.open("Imaging.txt",std::ios::app);
     
	 //将光纤矩阵中记录的能量沉积输入到文件imaging.txt中
	 for (int i=0;i<9;i++) {
            if ((i+1)%3==0){
                   out<<std::setprecision (6) << std::scientific<<edep[i]<<'\n'<<std::flush;}
            else{
	       out<<std::setprecision (6) << std::scientific<<edep[i]<<'\t'<<std::flush;
                }           
           }
            out<<'\n'<<std::endl;     
		 //关闭文件
	    out.close();
	    
	      
      G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------"<< G4endl;
     
    }
    else
    {
    		G4cout
        << G4endl
        << "--------------------End of Local Run------------------------"<< G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
