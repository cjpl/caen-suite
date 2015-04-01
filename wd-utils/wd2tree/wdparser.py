#!/usr/bin/env python
# -*- coding: utf-8 -*- 

'''
Parse data output from WaveDump.
'''
from struct import unpack,calcsize

class WDParser():
    '''WaveDump data Parser.
    Event structure: Header (7I) + Data
    Header:
        Record Length
        BoardID
        Channel
        Event Number
        Pattern
        Trigger Time Stamp
        DC offset (DAC)
    P.S.: Header in binary files does not contain DC offset (DAC).
    '''

    __fmt_bhead = '@6I' # binary header, 6I (24 bytes)
    
    def __init__(self, fndata, isASCII=True, hasHeader=True, rLen=1024, dType='H'):
        self.__isASCII = isASCII     # ASCII format or not
        self.__hasHeader = hasHeader # contain header or not
        self.__recLen = rLen         # record length
        self.__dType = dType         # array type: 'H' -- 2-byte, short int; 'B' -- 1-byte
        self.__fdata = open(fndata,"r")

    def close(self):
        if self.__fdata:
            self.__fdata.close()
        
    def get_one_event(self):
        '''Read one event from data file. '''
        if not self.__fdata: return None
        if self.__isASCII:
            return self.get_one_event_text()
        else:
            return self.get_one_event_bin()

    def get_one_event_text(self):
        # test ...
        stmp = self.__fdata.readline().strip()
        if not stmp: return None
        #### read header
        hdict = {}
        hlist = 7*[0]
        while not stmp.isdigit():
            kdat = stmp.split(':')
            hdict[kdat[0].strip()] = int(kdat[1],0)
            stmp = self.__fdata.readline().strip()
        if "Record Length" in hdict:
            self.__recLen = hdict["Record Length"]
            hlist[0] = hdict["Record Length"]
        if "BoardID" in hdict: hlist[1] = hdict["BoardID"]
        if "Channel" in hdict: hlist[2] = hdict["Channel"]
        if "Pattern" in hdict: hlist[3] = hdict["Pattern"]
        if "Event Number" in hdict: hlist[4] = hdict["Event Number"]
        if "Trigger Time Stamp" in hdict: hlist[5] = hdict["Trigger Time Stamp"]
        if "DC offset (DAC)" in hdict: hlist[6] = hdict["DC offset (DAC)"]
        #### read data
        dlist = [int(stmp,0), ] # add last read data
        for _ in range(self.__recLen - 1): # read the rest data (rLen-1)
            stmp = self.__fdata.readline().strip()
            if not stmp.isdigit(): break
            dlist.append( int(stmp,0) )
        #### return
        return (hlist, dlist)

    def get_one_event_bin(self):
        hlist = 7*[0]
        #### no header file
        if not self.__hasHeader:
            fmt_data = '@%d%s'%(self.__recLen, self.__dType)
            dlen = calcsize( fmt_d )
            stmp = self.__fdata.read(dlen)
            if len(stmp) < dlen: return None
            dlist = unpack(fmt_d, stmp)
            return (hlist, dlist)
        #### header and data
        stmp = self.__fdata.read(24)
        if len(stmp) < 24: return None
        head = unpack( self.__fmt_bhead, stmp )
        for i in range(1,6): hlist[i] = head[i]
        readlength = head[0]-24
        if self.__dType == 'B':
            fmt_data = '@%dB'%(readlength)
            hlist[0] = readlength
        else:
            fmt_data = '@%dH'%(readlength/2)
            hlist[0] = readlength/2
        self.__recLen = hlist[0]
        stmp = self.__fdata.read( readlength )
        if len(stmp) < readlength: return None
        dlist = unpack( fmt_data, stmp )
        return (hlist, dlist)
        
    def get_events(self,N=-1):
        '''Read N (-1 means all) events from data file.'''
        elist = []
        # read all events
        if N == -1:
            p = self.get_one_event()
            while p:
                elist.append(p)
                p = self.get_one_event()
            return elist
        # read N events
        for _ in range(N):
            p = self.get_one_event()
            if p: elist.append(p)
            else: break
        return elist

############################################################
## Test
if __name__ == "__main__":
    import sys
    from pprint import pprint
    for name in sys.argv[1:]:
        isASCII = True if name[-4:] == '.txt' else False
        pWD = WDParser(name, isASCII=isASCII)
        event = pWD.get_one_event()
        pprint(event[0])
        pprint(event[1][:10])
        pWD.close()

