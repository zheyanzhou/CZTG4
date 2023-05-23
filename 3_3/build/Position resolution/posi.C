#include <iostream>
#include <fstream>
#include <sstream>

//this file is used to caculate the place of the event
//according to the deposited energy in the czt array
//predicted position

void posi(){
      using namespace std;

      int row=5000;//the number of emitted photons
      int column=9;//the txt file has 9 column, corresponding 9 units of the czt array
      int numczt=3;//the number of the czt of every side; numczt=sqrt(colum)
      //double gap=0.0000000000001;//the length of the gap;mm
      double sizexy=3; //the side length of every czt units;mm
     
      double x[column],y[column];
      //assign the value of position to every column, inculde x,y two dimensions
      for(int i=0;i<numczt;i++){
          for (int j=0;j<numczt;j++){
          x[numczt*i+j]=0.5*sizexy+j*(sizexy);//x[0-8]
          y[numczt*i+j]=0.5*sizexy+i*(sizexy);//y[0-8]
          }
      }
      
      
      //open fedep1.txt to read the data
      ifstream read;
      ifstream truep;
      // ofstream write;
      read.open("fedep1.txt");
      truep.open("gun_position.txt");
      // write.open("pos.txt");
      string line;      
      double d[column];//store the value of deposited energy every row
      TFile *h = new TFile("posi.root", "RECREATE");
      TTree *prepos = new TTree("prepos", "my first tree");
      // define four branches adopt to four runs 
      Double_t prex = 0;
      Double_t prey = 0;
      Double_t truex = 0;
      Double_t truey = 0;
      prepos->Branch("prex", &prex, "prex/D");
      prepos->Branch("prey", &prey, "prey/D");
      prepos->Branch("truex", &truex, "truex/D");
      prepos->Branch("truey", &truey, "truey/D");  
          
      while(getline(read, line)){
	     stringstream ss(line);
	     double sum =0;

	     //add the deposited energy in this line
	     for (int j=0;j<column;j++){
                       ss >> d[j];
			sum += d[j];
		}
	     
	     //caculate the position through the center method
	     double posx =0;
	     double posy =0;	
	     for (int j=0;j<column;j++){
	             if (sum==0){
	             //write<<"no deposited energy in the event!"<<endl;
	             break;
	             }
                      posx +=d[j]/sum*x[j];
                      posy +=d[j]/sum*y[j];                   
		  }
		  
		  
	     if (sum!=0){
	     //write<<posx <<" "<< posy<<endl;
	     prex = posx;
	     prey = posy;
	     
	     prepos->Fill();
	     }            
      }
      
      string line2;
      while(getline(read, line2)){
            stringstream ss(line2);
            
            for(int i=0;i<2*column;i++)
            //////////////////////////////////write here
            
      
      
      }
      
      
      
      
      
      prepos->Write();
      truep.close();
      read.close();
      //write.close();
      h->Close();

      return 0;
}
