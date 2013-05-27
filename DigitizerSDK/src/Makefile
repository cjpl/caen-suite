
LIB	=	libCAENdigitizerSDK.so.1.3

CC	=	gcc

COPTS	=	-fPIC -DLINUX -Wall

FLAGS	=	-shared  -nostartfiles -s

DEPLIBS	=       -lCAENVME  -L.

LIBS	=	

INCLUDEDIR =	-I./ -I/usr/include/

INSTALLDIR =	/usr/lib

OBJS	=	cvt_board_commons.o cvt_V1724.o 

INCLUDES =	CAENVMElib.h CAENVMEtypes.h CAENVMEoslib.h

#########################################################################

all	:	$(LIB)

clean	:
		/bin/rm -f $(OBJS) $(LIB)

install	:	$(LIB)
		/bin/rm -f $(INSTALLDIR)/libCAENdigitizerSDK.so
		install $(LIB) $(INSTALLDIR)
		ln -sf $(INSTALLDIR)/$(LIB) $(INSTALLDIR)/libCAENdigitizerSDK.so
		ldconfig

$(LIB)	:	$(OBJS)
		/bin/rm -f $(BINLIB)
		$(CC) $(FLAGS) -o $(LIB) $(OBJS) $(DEPLIBS)

$(OBJS)		:	 Makefile

%.o	:	%.c
		$(CC) $(COPTS) $(INCLUDEDIR) -c -o $@ $<

