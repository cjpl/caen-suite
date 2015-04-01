#!/usr/bin/env python2
# -*- coding: utf-8 -*- 
'''
@Exaos
'''

from wdparser import *
import ROOT
from ROOT  import TFile, TTree, gROOT
from array import array

# array typecode:
#   L -- 4-byte, unsigned int
#   H -- 2-byte, unsigned short
# TTree fType codes:
#   I -- 32-bit, signed integer
#   i -- 32-bit, unsigned integer
#   S -- 16-bit, signed short integer
#   s -- 16-bit, unsigned short integer

############################################################
def wd2tree(fndata="wave0.txt", fnout=None, isASCII=True, hasHeader=True, rLen=1024, dType='H'):
    # open parser
    pWD = WDParser(fndata, isASCII, hasHeader, rLen, dType)

    # open output TFile
    if not fnout:
        fnout = fndata[:fndata.index('.')] + '.root'
    froot = TFile(fnout, "RECREATE")

    ## Get one event, parser length of waveform
    event = pWD.get_one_event()
    rLen = event[0][0]

    ## TTree Structure
    tree = TTree("wavedump", "WaveDump pulses")

    # header
    pLen = array('L',[0])
    pBoardID = array('L',[0])
    pChannel = array('L',[0])
    pEventID = array('L',[0])
    pPattern = array('L',[0])
    pTimeStamp = array('L',[0])
    pDCoffset = array('L',[0])

    # data
    pLen[0] = rLen
    pData = array('H',pLen[0]*[0])

    # branchs
    tree.Branch("nLen", pLen, "nLen/i")
    tree.Branch("nBoardID", pBoardID, "nBoardID/i")
    tree.Branch("nChannel", pChannel, "nChannel/i")
    tree.Branch("nPattern", pPattern, "nPattern/i")
    tree.Branch("nEventID", pEventID, "nEventID/i")
    tree.Branch("nTimeStamp", pTimeStamp, "nTimeStamp/i")
    tree.Branch("nDAC", pDCoffset, "nDAC/i")
    tree.Branch("WAVE", pData, "WAVE[nLen]/s")

    ## Fill
    while event:
        # header
        pLen[0] = event[0][0]
        pBoardID[0] = event[0][1]
        pChannel[0] = event[0][2]
        pPattern[0] = event[0][3]
        pEventID[0] = event[0][4]
        pTimeStamp[0] = event[0][5]
        pDCoffset[0]  = event[0][6]
        for i in range(event[0][0]):
            pData[i] = event[1][i]
        tree.Fill()
        # get next event
        event = pWD.get_one_event()
        
    ##
    pWD.close()
    froot.Write()
    froot.Close()

############################################################
# Use C/C++ structure
str_branch_struct = """
struct wdPulse_t { \
   UInt_t  nLen; \
   UInt_t  nBoardID; \
   UInt_t  nChannel; \
   UInt_t  nPattern; \
   UInt_t  nEventID; \
   UInt_t  nTimeStamp; \
   UInt_t  nDAC; \
   UShort_t WAVE[%d]; \
};
"""
str_branch_fmt = 'nLen/i:nBoardID/i:nChannel/i:nPattern/i:nEventID/i:nTimeStamp/i:nDAC/i:WAVE[nLen]/s'

def wd2tree2(fndata="wave0.dat", fnout=None, isASCII=False, hasHeader=True, rLen=1024, dType='H'):
    # open parser
    pWD = WDParser(fndata, isASCII, hasHeader, rLen, dType)

    # open output TFile
    if not fnout:
        fnout = fndata[:fndata.index('.')] + '.root'
    froot = TFile(fnout, "RECREATE")

    ## Get one event, parser length of waveform
    event = pWD.get_one_event()
    rLen = event[0][0]

    ## TTree Structure
    tree = TTree("wdPulse", "WaveDump pulses")

    # branchs
    gROOT.ProcessLine( str_branch_struct%(rLen) )
    wp = ROOT.wdPulse_t()
    tree.Branch( "Wave", wp, str_branch_fmt )

    ## Fill
    while event:
        # header
        wp.nLen = event[0][0]
        wp.nBoardID   = event[0][1]
        wp.nChannel   = event[0][2]
        wp.nPattern   = event[0][3]
        wp.nEventID   = event[0][4]
        wp.nTimeStamp = event[0][5]
        wp.nDAC  = event[0][6]
        for i in range(event[0][0]):
            wp.WAVE[i] = event[1][i]
        tree.Fill()
        # get next event
        event = pWD.get_one_event()
        
    ##
    pWD.close()
    froot.Write()
    froot.Close()

############################################################
## Test
if __name__ == "__main__":
    import sys
    for name in sys.argv[1:]:
        isASCII = True if name[-4:] == ".txt" else False
        wd2tree2(name, isASCII=isASCII)

