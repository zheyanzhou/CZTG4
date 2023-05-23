#include <iostream>
#include <fstream>
#include <string>
#include <TGraph.h>
#include "TH1.h"
#include "TLegend.h"
#include <sstream>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
using namespace std;
void evif() {
  // read the .txt file
  ifstream rsp("sp.txt");
  ifstream rcc("cc.txt");
  ifstream rce("ce.txt");
  ifstream rec("ec.txt");
  ifstream ree("ee.txt");
  int N = 1000; // number of events
  Double_t de = 0;
  Int_t sp = 0;
  Int_t cc = 0;
  Int_t ce = 0;
  Int_t ec = 0;
  Int_t ee = 0;
  // define the .root file and tree
  TFile *h = new TFile("600evif.root", "RECREATE");
  TTree *evif_tree = new TTree("evif_tree", "my first tree");
  TFile *B1 = new TFile("B1.root", "read");
  TTree *tree1 = dynamic_cast<TTree*>(B1->Get("B1"));
  Double_t rde;
  TBranch *branch1 = tree1->GetBranch("Edev");
  branch1->SetAddress(&rde);
  // define four branches adopt to four runs 
  evif_tree->Branch("de", &de, "de/D");
  evif_tree->Branch("sp", &sp, "sp/I");
  evif_tree->Branch("cc", &cc, "cc/I");
  evif_tree->Branch("ce", &ce, "ce/I");
  evif_tree->Branch("ec", &ec, "ec/I");
  evif_tree->Branch("ee", &ee, "ee/I");
  // input the data
  for (int i = 0; i < N; i++) {
    if (!branch1->GetEntry(i)) {
      cerr << "Error: failed to read entry " << i << " from B1.root" << endl;
      break;
    }
    de = rde;
    rsp >> sp;
    rcc >> cc;
    rce >> ce;
    rec >> ec;
    ree >> ee;
    evif_tree->Fill();
  }
  evif_tree->Write(); // write the tree into the .root file
  B1->Close();
  h->Close();
}
int main() {
  evif();
  return 0;
}
