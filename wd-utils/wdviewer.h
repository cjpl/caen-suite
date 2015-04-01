#ifndef WDVIEWER_H
#define WDVIEWER_H

//
// Author: Exaos Lee  2015-03-22

#include <TApplication.h>

#include <TGClient.h>
#include <TGFrame.h>
#include <TFrame.h>

#include <TRootEmbeddedCanvas.h>
#include <TCanvas.h>
#include <TH1F.h>

#include <TGButton.h>
#include <TGStatusBar.h>
#include <TGNumberEntry.h>
#include <TGSlider.h>

//************************************************************
// WFMainFrame declaration

// the WdPulse class => to handle the tree
#include "WdPulse.h"

class WFMainFrame: public TGMainFrame {
private:
  TRootEmbeddedCanvas  *fWcan;
  TGStatusBar          *fStatusBar;
  TGTextButton         *fBtFile;
  TGNumberEntry        *fNumEntry;
  TGHSlider            *fHSlider;

  // The Pulse processor
  WdPulse    *fWD;
  Long64_t    nEntries;
  Long64_t    entry;

  // Data manipulation
  TFile  *fWfile;
  TTree  *fWtree;
  TH1    *fHfft;
  Bool_t  fOpened;
  Bool_t  fFFT;

public:
  WFMainFrame(const TGWindow *p, UInt_t w, UInt_t h);
  virtual ~WFMainFrame();
  
  void DoExit();
  void SetStatusText( const char *txt, Int_t pi);
  void EventInfo(Int_t event, Int_t px, Int_t py, TObject *selected);
  
  void DoFile();      // Open/Close file
  void DoPrevious();  // Load previous entry
  void DoNext();      // Load next entry
  void DoNumEntry();  // Set entry from widget NumberEntry
  void DoSlider();    // Slider position changed
  void ToggleFFT(Bool_t on); // Toggle FFT
  
  void OpenData( const char *filename );
  void CloseData();
  void UpdateEntry(); // Update while entry loaded

  ClassDef(WFMainFrame, 0)
};

#endif
