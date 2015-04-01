// -*- mode: c++; coding: utf-8; -*-
// Author: Exaos Lee  2015-03-22

#include "wdviewer.h"

//************************************************************
// WFMainFrame definitions of members
WFMainFrame::WFMainFrame(const TGWindow *p, UInt_t w, UInt_t h)
  : TGMainFrame(p, w, h)
{
  //== create the embedded canvas
  fWcan = new TRootEmbeddedCanvas(0, this, 500, 400);
  Int_t wid = fWcan->GetCanvasWindowId();
  TCanvas *wcan = new TCanvas("WaveCanvas", 10, 10, wid);
  fWcan->AdoptCanvas(wcan);
  wcan->Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)",
                "WFMainFrame", this,
                "EventInfo(Int_t, Int_t, Int_t, TObject*)");
  AddFrame(fWcan,
           new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY,
                             0, 0, 1, 1));

  //== Add slider under canvas
  fHSlider = new TGHSlider(this, 50, kSlider1);
  fHSlider->Connect("Released()", "WFMainFrame", this, "DoSlider()");
  AddFrame(fHSlider,
           new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX,
                             0, 0, 1, 1));

  //== Buttons: Open/Close file, Next (Entry), Previous (Entry), Exit
  TGHorizontalFrame *hframe = new TGHorizontalFrame(this, 200, 40);

  // Open/Close file
  fBtFile = new TGTextButton(hframe, "&Open");
  fBtFile->Connect("Clicked()", "WFMainFrame", this, "DoFile()");
  hframe->AddFrame(fBtFile, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));

  // FFT
  TGCheckButton *fCheckFFT = new TGCheckButton(hframe, "FFT");
  fCheckFFT->Connect("Toggled(Bool_t)", "WFMainFrame", this, "ToggleFFT(Bool_t)");
  fCheckFFT->SetState(kButtonDisabled); // TPad problem ...
  hframe->AddFrame(fCheckFFT, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));
  
  // NumberEntry
  fNumEntry = new TGNumberEntry(hframe, 0, 9, 999,
                                TGNumberFormat::kNESInteger,
                                TGNumberFormat::kNEANonNegative, 
                                TGNumberFormat::kNELLimitMinMax,
                                0, 99999);
  fNumEntry->Connect("ValueSet(Long_t)", "WFMainFrame", this, "DoNumEntry()");
  (fNumEntry->GetNumberEntry())->Connect("ReturnPressed()",
                                         "WFMainFrame", this, "DoNumEntry()");
  hframe->AddFrame(fNumEntry, new TGLayoutHints( kLHintsCenterX, 5, 5, 3, 4));

  // Previous Entry
  TGTextButton *btpre = new TGTextButton(hframe, "&Previous");
  btpre->Connect("Clicked()", "WFMainFrame", this, "DoPrevious()");
  hframe->AddFrame(btpre, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));
  
  // Next Entry
  TGTextButton *btnext = new TGTextButton(hframe, "&Next");
  btnext->Connect("Clicked()", "WFMainFrame", this, "DoNext()");
  hframe->AddFrame(btnext, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));

  // Exit
  TGTextButton *btexit = new TGTextButton(hframe, "&Exit");
  btexit->Connect("Pressed()", "WFMainFrame", this, "DoExit()");
  hframe->AddFrame(btexit, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));
  
  // add hframe
  AddFrame(hframe, new TGLayoutHints(kLHintsCenterX, 2, 2, 2, 2));

  //== Status bar
  Int_t parts[] = {20, 10, 9, 9, 20, 10, 7, 15};
  fStatusBar = new TGStatusBar(this, 50, 10, kVerticalFrame);
  fStatusBar->SetParts(parts, 8);
  fStatusBar->Draw3DCorner(kFALSE);
  AddFrame(fStatusBar, new TGLayoutHints(kLHintsExpandX, 0, 0, 10, 0));

  //== Set mainframe's name
  SetWindowName("Waveform Viewer for WaveDump output");
  MapSubwindows();

  //== Initialize the layout algorithm
  Resize(GetDefaultSize());

  //== Map main frame
  MapWindow();

  // Init?
  fWD = NULL;
  fWfile = NULL;
  fWtree = NULL;
  nEntries = -1;
  entry = -1;

  fOpened = kFALSE;
  fFFT = kFALSE;
}

WFMainFrame::~WFMainFrame()
{
  Cleanup();
  CloseData();
  delete fWcan;
  delete fWD;
  if(fWtree) { delete fWtree; }
  delete fWfile;
}

void WFMainFrame::DoExit()
{
  printf("Exit application ...");
  gApplication->Terminate(0);
}

void WFMainFrame::SetStatusText(const char *txt, Int_t pi)
{
  // Set text in status bar
  fStatusBar->SetText(txt, pi);
}

void WFMainFrame::EventInfo(Int_t event, Int_t px, Int_t py, TObject *selected)
{
  // StatusBar:
  // <file>, <tree>, <total>, <entry>,
  // <Title>, <Name>, <event>, <position>
  const char *txt0, *txt1, *txt3;
  char txt2[50];
  
  txt0 = selected->GetTitle();
  SetStatusText(txt0, 4);
  txt1 = selected->GetName();
  SetStatusText(txt1, 5);
  if( event == kKeyPress ) {
    sprintf(txt2, "%c", (char) px);
  } else {
    sprintf(txt2, "%d,%d", px, py);
  }
  SetStatusText(txt2, 6);
  txt3 = selected->GetObjectInfo(px, py);
  SetStatusText(txt3, 7);
}

//**************************************************
#include <TGFileDialog.h>

const char *filetypes[] = {
  "ROOT files",  "*.root",
  "ROOT macros", "*.C",
  "Text files",  "*.[tT][xX][tT]",
  "All files",   "*",
  0, 0 };

void WFMainFrame::DoFile()
{
  fBtFile->SetState(kButtonDown);
  
  if( !fOpened ) { //== Open dialog to select the file
    static TString fdir(".");
    TGFileInfo fi;
    fi.fFileTypes = filetypes;
    fi.fIniDir = StrDup(fdir);
    new TGFileDialog(gClient->GetRoot(), this, kFDOpen, &fi);
    // printf("Open file: %s (dir: %s)\n", fi.fFilename, fi.fIniDir);
    fdir = fi.fIniDir;

    // Open data file
    OpenData(fi.fFilename);

    // Button status
    fOpened = kTRUE;
    fBtFile->SetText("&Close");
    
  } else {  //== Close current file
    CloseData();

    // Button status
    fOpened = kFALSE;
    fBtFile->SetText("&Open");
  }

  fBtFile->SetState(kButtonUp);
}

void WFMainFrame::OpenData( const char *filename )
{
  const char *txt0, *txt1;
  char txt2[50];

  //== Open the data file
  fWfile = new TFile(filename);
  if(fWfile) {
    fWtree = (TTree*)fWfile->Get("wdPulse");
    txt0 = fWfile->GetName();
    SetStatusText(txt0, 0);
  }
  if(fWtree) {
    txt1 = fWtree->GetName();
    SetStatusText(txt1, 1);

    fWD = new WdPulse(fWtree);
    nEntries = fWD->nEntries;
    entry = 0;
    fNumEntry->SetLimitValues(0, nEntries);
    fHSlider->SetRange(0, nEntries);
    
    sprintf(txt2, "%ld", nEntries);
    SetStatusText(txt2, 2);
    
    UpdateEntry();
  }
}

void WFMainFrame::CloseData()
{
  if(fWfile) {
    fWfile->Close();
  }
  // Clear Canvas
  fWcan->GetCanvas()->Clear();
  fWcan->GetCanvas()->Update();
}

void WFMainFrame::UpdateEntry()
{
  if( fWD==NULL || entry < 0 || entry >= nEntries )
    return;

  // Get entry data
  fWD->GetEntry(entry);

  // Display waveform
  TCanvas *c1 = fWcan->GetCanvas();
  if( fFFT ) {
    c1->Divide(2,1);
    c1->cd(1);
    fWD->fHist->Draw();
    c1->cd(2);
    fHfft = fWD->fHist->FFT(fHfft, "PH");
    fHfft->Draw();
    c1->Update();
  } else {
    c1->SetGrid();
    fWD->fHist->Draw();
    c1->Update();
  }

  // Update status bar and others
  char txt3[50];
  sprintf(txt3, "%ld", entry);
  SetStatusText(txt3, 3);

  fNumEntry->SetIntNumber(entry);
  fHSlider->SetPosition(entry);
}

void WFMainFrame::DoPrevious()
{
  if(entry > 0) entry--;
  UpdateEntry();
}

void WFMainFrame::DoNext()
{
  if(entry < nEntries) entry++;
  UpdateEntry();
}

void WFMainFrame::DoNumEntry()
{
  entry = fNumEntry->GetNumberEntry()->GetIntNumber();
  UpdateEntry();
}

void WFMainFrame::DoSlider()
{
  entry = fHSlider->GetPosition();
  UpdateEntry();
}

void WFMainFrame::ToggleFFT(Bool_t on)
{
  if(on) {
    fFFT = kTRUE;
  } else {
    fFFT = kFALSE;
  }

  UpdateEntry();
}

//************************************************************
// The Tree manipulation

// using TTree::MakeClass("name") ...

//************************************************************
// The Application

// The CINT Macro
#if defined(__CINT__)

void wdviewer()
{
  // Load the Class
  gROOT->ProcessLine(".x WdPulse.cpp");
  
  // Init main frame
  new WFMainFrame(gClient->GetRoot(), 800, 600);
}

#endif // defined(__CINT__)

// The Main for compiling
#if !defined(__CINT__)

#include <cstdlib>

int main(int argc, char** argv)
{
  // Start ROOT application
  TApplication theApp("wdviewer", &argc, argv);
  // Create the main frame
  new WFMainFrame(gClient->GetRoot(), 800, 600);
  // Application loop
  theApp.Run();
  // Quit
  return EXIT_SUCCESS;
}

#endif // !defined(__CINT__)

