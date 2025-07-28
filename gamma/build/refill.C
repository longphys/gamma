#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1.h"

#include "TStopwatch.h"

void refill()
{
  auto timer = new TStopwatch();
  timer->Start();

  //! Files and trees
  TFile* fileOpen = new TFile("./out.root", "read");
  TTree* treeOpen =  (TTree*) fileOpen->Get("Tree");

  //! Get Events
	double eventOpen;
	treeOpen->SetBranchAddress("Scintillator", &eventOpen);

  double x_min = 0.;
  double x_max = 2.;
  int bin = 2000;
  TH1D* histogram = new TH1D("histogram", "histogram", bin, x_min, x_max);
  
  //! Fill experiment histograms
  TFile* fileSave = new TFile("./simulation_Na22.root", "recreate");
  TTree* treeSave =  new TTree("Events", "Events");
  double energySave;
  treeSave->Branch("Energy", &energySave);

  int entries = treeOpen->GetEntries();

  for(int i = 0; i<entries; i++){
    if(i%100000==0){std::cout << "Event: " << i << "\n";}
    treeOpen->GetEntry(i);
    energySave = eventOpen;
    treeSave->Fill();
  }

  fileSave->Write();
  fileSave->Close();

  std::cout << "time: " << timer->RealTime() << " seconds \n";
}
