#include <iostream>
#include <fstream>
#include <string>
#include <TGraph.h>
#include "TH1.h"
#include "TLegend.h"
using namespace std;


//this is a file that can run correctly, maybe it is the last successful file, so don't touch it easilly.
//yes , i am very scared about the security of this file.


void modifyFile(string fileName)
{
    string line; // 用于存储读取的每一行内容
    // 打开指定的txt文件
    ifstream infile(fileName);
    string result = ""; // 用于存储修改后的内容
    while (getline(infile, line)) {
       if (line.find("Energy deposited-") == 0) {
            // 如果该行以"Energy deposited-"开头，则将该行中的"Energy deposited-"字符全部删除
            line = line.substr(17);
        } else {
            // 如果该行不以"Energy deposited-"开头，则将该行删除
            continue;
        }
        result += line + "\n"; // 将修改后的行添加到结果中
    }
    // 关闭文件
    infile.close();
    // 将修改后的内容重新写入txt文件中
    ofstream outfile(fileName);
    outfile << result;
    outfile.close();
    cout << "文件修改成功！" << endl;
    return;
}
void myfit(string filename, TH1F* h, int color=1)
{
    //ifstream in_hist;
    //in_hist.open(filename.c_str()); // 使用c_str()函数将string类型的filename转换成const char类型
    //ifstream inFile("input.txt");
    //read the data
    ifstream in_hist;
    in_hist.open(filename.c_str()); // 使用c_str()函数将string类型的filename转换成const char*类型
    Float_t ene;
    while(in_hist >> ene) // 读取文件数据并填充到h对象中
    {
        h->Fill(ene);
    }
    in_hist.close();
    //draw and maquillage
    h->Draw("same");
    //h->Fit("expo");
    h->SetLineColor(color);
    h->SetLineWidth(2);
}
void hist3()
{
    /*modifyFile("6exampleB1.out");
    modifyFile("8exampleB1.out");
    modifyFile("10exampleB1.out");
    modifyFile("12exampleB1.out");*/
    TCanvas *c1 = new TCanvas();
    TLegend *legend = new TLegend(0.6,0.7,0.9,0.9);
    TH1F *h1 = new TH1F("h1","deposited energy;energy/MeV;numbers of event",12,0,3); // 创建h1对象
    TH1F *h2 = new TH1F("h2","deposited energy;energy/MeV;numbers of event",12,0,3); // 创建h2对象
    TH1F *h3 = new TH1F("h3","deposited energy;energy/MeV;numbers of event",12,0,3); 
    TH1F *h4 = new TH1F("h4","deposited energy;energy/MeV;numbers of event",12,0,3); 
    myfit("6exampleB1.out",h1, kRed); // 对h1对象进行拟合
    myfit("8exampleB1.out",h2, kBlue); // 对h2对象进行拟合
    myfit("10exampleB1.out",h3, kGreen);
    myfit("12exampleB1.out",h4, kYellow);
    legend->AddEntry(h1, "6cm", "l"); // 添加h1的legend标签
    legend->AddEntry(h2, "8cm", "l"); // 添加h2的legend标签
    legend->AddEntry(h3, "10cm", "l");
    legend->AddEntry(h4, "12cm", "l");
    legend->Draw();
}