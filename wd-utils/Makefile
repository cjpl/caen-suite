# -*- mode: makefile-gmake; coding: utf-8; -*-
#  Created by:  Exaos Lee (exaos.lee@gmail.com)
############################################################

#---------- ROOT
ROOTCFG := $(shell which root-config)
ROOTCINT := $(shell which rootcint)
ifdef ROOTCFG
ROOTSYS = $(shell $(ROOTCFG) --prefix)
endif
ifdef ROOTSYS
ROOTCFLAGS := $(shell $(ROOTCFG) --cflags)
ROOTLIBS   := $(shell $(ROOTCFG) --libs) -lGui
endif

#------------------------------------------------------------
CXXFLAGS += -g -O2 ${ROOTCFLAGS}
LDFLAGS  += ${ROOTLIBS}
LINK.o = $(LINK.cc)

EXECS = wdviewer

all: ${EXECS}

.PHONY: clean

clean:
	rm -f *.o *~ ${EXECS} *Dict.cpp

wdviewer: wdviewer.o WdPulse.o wdDict.o

wdviewer.o: wdviewer.cpp WdPulse.h wdviewer.h

WdPulse.o: WdPulse.cpp WdPulse.h wdviewer.h

wdDict.o: wdDict.cpp wdviewer.h

wdDict.cpp: wdviewer.h wdLinkDef.h
	${ROOTCINT} -f $@ -c $^


