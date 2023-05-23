#include<iostream>
#include<fstream>
#include<string>
#include <TGraph.h>
#include "TH1.h"
#include "TLegend.h"
#include <sstream>
#include <TH1F.h>
#include <TFile.h>
#include <TCanvas.h>
using namespace std;

void evif(){

//read the .txt file
ifstream rsp("sp.txt");
ifstream rcc("cc.txt");
ifstream rce("ce.txt");
ifstream rec("ec.txt");
ifstream ree("ee.txt");
int N=1000;//number of events
double de=1;
int sp=1;
int cc=1;
int ce=1;
int ec=1;
int ee=1;

//define the .root file and tree
TFile *evif = new TFile("600evif.root","RECREATE");
TTree *evif_tree = new TTree("evif_tree","my first tree");
//open the .root file and tree
TFile *B1 = new TFile("B1.root","READ");
TTree*tree1 = dynamic_cast<TTree*>(B1->Get("B1"));
double_t rde;
TBranch*branch1 = tree1->GetBranch("Edev");
branch1->SetAddress(&rde);

//define six branches adopt to six parameter 
evif_tree->Branch("de",&de,"de/D");
evif_tree->Branch("sp",&sp,"sp/I");
evif_tree->Branch("cc",&cc,"cc/I");
evif_tree->Branch("ce",&ce,"ce/I");
evif_tree->Branch("ec",&ec,"ec/I");
evif_tree->Branch("ee",&ee,"ee/I");


//input the data
for(int i=0; i<N; i++){
   branch1->GetEntry(i);
   de  = rde;   
   rsp >> sp;
   rcc >> cc;
   rce >> ce;
   rec >> ec;
   ree >> ee;
   evif_tree->Fill();
}

evif->cd();//cd the second .root file
evif_tree->Write();//i think this is used for writing the tree into the .root file
evif->Close();
B1->Close();
return 0;
}
