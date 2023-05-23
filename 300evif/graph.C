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

void graph(){

TFile *evif = new TFile("300evif1.root","UPDATE");

TCanvas *graph = new TCanvas();
TTree* tree = (TTree*)evif->Get("evif_tree");


tree->Draw("de","cc>=1","colz");
evif->WriteObject(&graph, "graph");






return 0;
}
