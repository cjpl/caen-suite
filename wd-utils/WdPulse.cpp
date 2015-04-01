// #define WdPulse_cxx

#include "WdPulse.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

//   In a ROOT session, you can do:
//      Root > .L WdPulse.C
//      Root > WdPulse t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries

//************************************************************

// #ifdef WdPulse_cxx
WdPulse::WdPulse(TTree *tree) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the default file
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("test.root");
    if (!f || !f->IsOpen()) {
      f = new TFile("test.root");
    }
    f->GetObject("wdPulse",tree);
  }
  
  Init(tree);
}

WdPulse::~WdPulse()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t WdPulse::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  Int_t ret = fChain->GetEntry(entry);

  // generate histogram for current waveform
  fHist->Reset();
  for(Int_t i=0; i<Wave_nLen; i++) {
    fHist->Fill(i, Wave_WAVE[i]);
  }
  
  return ret;
}
Long64_t WdPulse::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void WdPulse::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize a new
  // tree or chain. Typically here the branch addresses and branch pointers of
  // the tree will be set.
  // It is normally not necessary to make changes to the generated code, but the
  // routine can be extended by the user if needed.  Init() will be called many
  // times when running on PROOF (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("Wave", &Wave_nLen, &b_Wave);

  nEntries = fChain->GetEntries();
  // Init histogram ? Or left to GetEntry()?
  fHist = new TH1F("hWave", "Entry Waveform", 1029, 0, 1029);

  //--
  Notify();
}

Bool_t WdPulse::Notify()
{
  // The Notify() function is called when a new file is opened. This can be
  // either for a new TTree in a TChain or when when a new TTree is started when
  // using PROOF. It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed. The return
  // value is currently not used.

  return kTRUE;
}

void WdPulse::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t WdPulse::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
// #endif // #ifdef WdPulse_cxx

void WdPulse::Loop()
{
  // ----  This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  // ----  To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
  }
}

