#include "MyTreeHandler.hh"

#include "G4ios.hh"

MyTreeHandler::MyTreeHandler()
{
    //fFile = new TFile("out.root", "recreate");
    fFile = new TFile();
    fTree = new TTree("Tree", "Tree");
    fEventNr = -1;
    fdE = -1.0;
    fcomptNr = -1;
    
    fTree->Branch("EventID", &fEventNr, "EventID/I");
    
    fTree->Branch("Scintillator", &fdE, "Scintillator/D");

    fTree->Branch("ComptonInteractions", &fcomptNr, "ComptonInteractions/L");
    fTree->Branch("BackScatteredComptonEnergyDeposition", &fbackEDep, "BackScatteredComptonEnergyDeposition/D");
}

G4int MyTreeHandler::Open()
{
    fFile = TFile::Open("out.root", "recreate");
    return 0;
}

G4int MyTreeHandler::Push(int64_t eventNr, G4double dE, int64_t comptNr, G4double backEDep)
{
    fEventNr = eventNr;

    fdE = dE;

    fcomptNr = comptNr;
    fbackEDep = backEDep;

    fTree->Fill();

    return 0;
}

G4int MyTreeHandler::Close()
{
    fTree->Write();
    fFile->Close();

    return 0;
}

G4int MyTreeHandler::Print()
{
    G4cout << "fEventNr = " << fEventNr << ": fdE = " << fdE << "\n";

    return 0;
}
