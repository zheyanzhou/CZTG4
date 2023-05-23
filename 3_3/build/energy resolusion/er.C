#include <iostream>
#include <fstream>

#include <TROOT.h>
#include <TH1D.h>
#include <TChain.h>
#include <TRandom.h>
#include <TNtuple.h>

void er(){
    using namespace std;

    ifstream datafile1,datafile2;
    datafile1.open("edep.txt",ios_base::in);
   // datafile2.open("edeps.txt",ios_base::out);    //创建输出文件

    //h1--initial data, h2--gauss energy broadening
    TH1F* h1 = new TH1F("h1","initial energy;energy/MeV;numbers of event",1024,0.000001,0.35);
    TH1F* h2 = new TH1F("h2","gauss energy broadening;energy/MeV;numbers of event",1024,0.000001,0.35);      //创建直方图


    double geb;     //展宽后能量
    double sigma;   //半高宽
    double a=0.0607;
    double b=3.8402e-8;
    double c=0; 
    double ene=0.2;

    TCanvas *c1 = new TCanvas();
    c1->Divide(2);

    while(datafile1 >> ene) {
       
         h1->Fill(ene);      //填充直方图
         //下限设置为 0.000001 MeV
        if(ene>=0){
            sigma=(a+b*sqrt(ene+c*ene*ene))/2.35482;;    
            geb=gRandom->Gaus(ene,sigma);       //以初始为期望值，半高宽为sigma生成随机数
            h2->Fill(geb);
           
        }
    }
    c1->cd(1);h1->Draw();
    c1->cd(2);h2->Draw();
/*    double energy_geb=0;
    double energy=0;
    int count=0;

    for(int i=0;i<1024;i++){
        count=h2->GetBinContent(i+1);
        energy_geb=h2->GetBinLowEdge(i+1);
        datafile2<<energy_geb<<"\t"<<count<<endl;

        count=h1->GetBinContent(i+1);
        energy=h1->GetBinLowEdge(i+1);
        datafile1<<energy<<"\t"<<count<<endl;       //读出直方图中的计数和能量区间
    }
*/

    //h1->Delete();
   // h2->Delete();
    datafile1.close();
    datafile2.close();
}
