int read(){

TFile *f1 = new TFile("300evif1.root");
TTree *t1 = (TTree*)f1->Get("evif_tree");

TFile *f2 = new TFile("600evif.root");
TTree *t2 = (TTree*)f2->Get("evif_tree");

Double_t de1,de2;

t1->SetBranchAddress("de",&de1);
t2->SetBranchAddress("de",&de2);

//create histograms
TH1F *h2 = new TH1F("h2","deposited energy spectrum(de>0.0018MeV);deposited energy/MeV;number of events",100,0,0.6);
TH1F *h1 = new TH1F("h1","deposited energy spectrum(de>0.0018MeV);deposited energy/MeV;number of events",100,0,0.6);


//read all entries and fill the histogram
Long64_t nentries = t1->GetEntries();
for (Long64_t i =0; i<nentries; i++){
    t1->GetEntry(i);
    if(de1>0.0018){
    h1->Fill(de1);
    }
    
    t2->GetEntry(i);    
    if(de2>0.0018){
    h2->Fill(de2);
    }

 }
 
 
TCanvas *c1 = new TCanvas();
h1->Draw();
h2->Draw("same");
h2->SetLineColor(kBlue);
h1->SetLineColor(kRed);
h1->SetLineWidth(2);
h2->SetLineWidth(2);
//h1->SetLineStyle(5);



TLegend *legend = new TLegend(0.6,0.6,0.9,0.9);
legend->AddEntry(h1, "0.3MeV", "l"); // 添加h1的legend标签
legend->AddEntry(h2, "0.6MeV", "l"); // 添加h2的legend标签
legend->Draw();
  
return 0;
}
