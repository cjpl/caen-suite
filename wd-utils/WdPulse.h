//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Mar 22 10:52:32 2015 by ROOT version 5.34/26
// from TTree wdPulse/WaveDump pulses
// found on file: test1.root
//////////////////////////////////////////////////////////

#ifndef WdPulse_h
#define WdPulse_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TH1F.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class WdPulse {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  UInt_t          Wave_nLen;
  UInt_t          Wave_nBoardID;
  UInt_t          Wave_nChannel;
  UInt_t          Wave_nEventID;
  UInt_t          Wave_nPattern;
  UInt_t          Wave_nTimeStamp;
  UInt_t          Wave_nDAC;
  UShort_t        Wave_WAVE[1029];   //[nLen] -- pointer to a variable array?

  // List of branches
  TBranch        *b_Wave;   //!

  WdPulse(TTree *tree=0);
  virtual ~WdPulse();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);

  // The Pulse Histogram
  Long64_t nEntries;
  TH1F*    fHist;
};

#endif

