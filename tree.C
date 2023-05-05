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
//this file is used for read the data from 6target.txt
//then store the data to a .root file
//in fact, I hope this .root file have a tree which contains four branches. 
//now, this file can run correctly, just a branch, and it doesn't work as a function form.
//update:now, it can creat four branches in a tree from four .txt files.
//I am very happy because it is written by myself totally independently.
//Next:I think we should learn how to draw the histogram and of course decorate it.
 
 
//from exampleB1.out to target.txt
void modifyFile(string fileName, string outfile)
{
    
    ofstream data_file(outfile);
    // 2.打开“example.out”文件，找到其中以“Energy deposited-”开头的行，将其复制到"data.txt"文件中，删除“Energy deposited-”字符
    ifstream input_file(fileName);
    string line;
    while (getline(input_file, line))
    {
        if (line.find("Energy deposited-") == 0 )
        {
            line.erase(0, 17); // 删除前18个字符
            data_file << line << endl;
        }
    }
    data_file.close();
    input_file.close();
    return 0;
}

int tree(){
//from exampleB1.out to target.txt
modifyFile("0.6exampleB1.out","0.6target.txt");
modifyFile("0.8exampleB1.out","0.8target.txt");
modifyFile("1.0exampleB1.out","1.0target.txt");
modifyFile("1.2exampleB1.out","1.2target.txt");
//read the .txt file
ifstream read6("0.6target.txt");
ifstream read8("0.8target.txt");
ifstream read10("1.0target.txt");
ifstream read12("1.2target.txt");
int N=1000;//number of events
float ene6=1;
float ene8=1;
float ene10=1;
float ene12=1;

//define the .root file and tree
TFile *h = new TFile("h.root","RECREATE");
TTree *ene_tree = new TTree("ene_tree","my first tree");

//define four branches adopt to four runs 
ene_tree->Branch("0.6MeV",&ene6,"ene6/F");
ene_tree->Branch("0.8MeV",&ene8,"ene8/F");
ene_tree->Branch("1.0MeV",&ene10,"ene10/F");
ene_tree->Branch("1.2MeV",&ene12,"ene12/F");

//input the data
for(int i=0; i<N; i++){
   read6 >> ene6;
   read8 >> ene8;
   read10 >> ene10;
   read12 >> ene12;
   ene_tree->Fill();
}

ene_tree->Write();//i think this is used for writing the tree into the .root file
ene_tree->Scan();

return 0;//finsished!
}