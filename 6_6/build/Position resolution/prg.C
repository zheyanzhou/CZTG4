void prg(){

//prg means "position resolution graph"
//read the data of the posi.root
//draw the graph of the position resolution 


double truex=4.5, truey=4.5;//the true position of photons
double deltax,deltay;//the difference value between the true and the predicted

TFile *f1 = new TFile("posi.root");
TTree *t1 = (TTree*)f1->Get("prepos");

Double_t prex,prey;

t1->SetBranchAddress("prex",&prex);
t1->SetBranchAddress("prey",&prey);

TH1F *h1 = new TH1F("h1","position resolution(x);delta x;number of events",1024,-5,5);
TH1F *h2 = new TH1F("h2","position resolution(y);delta y;number of events",1024,-5,5);

//read all entries and fill the histogram
Long64_t nentries = t1->GetEntries();
for (Long64_t i =0; i<nentries; i++){
    t1->GetEntry(i);
    deltax = prex-truex;
    deltay = prey-truey;
    h1->Fill(deltax);
    h2->Fill(deltay);
 }

TCanvas *c1 = new TCanvas();
c1->Divide(2);
c1->cd(1);h1->Draw();
c1->cd(2);h2->Draw();


return 0;
}
