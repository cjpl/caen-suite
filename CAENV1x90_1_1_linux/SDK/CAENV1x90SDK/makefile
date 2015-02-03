
LIB	=	libCAENV1x90SDK.so.1.1

CC	=	gcc

COPTS	=	-fPIC -DLINUX -Wall 
#COPTS	=	-g -fPIC -DLINUX -Wall 

FLAGS	=	-shared -Wall,-soname -nostartfiles -s
#FLAGS	=	-shared -Wall,-soname -nostartfiles

DEPLIBS	=       -lCAENVME

LIBS	=	

INCLUDEDIR =	-I./include/

INSTALLDIR =	/usr/lib

OBJS	=	cvt_board_commons.o cvt_V1190.o 

#########################################################################

all	:	$(LIB)

clean	:
		/bin/rm -f $(OBJS) $(LIB)

install	:	$(LIB)
		/bin/rm -f $(INSTALLDIR)/libCAENV1x90SDK.so
		cp include/cvt_V1190.h /usr/include/
		cp include/cvt_board_commons.h /usr/include/
		cp include/cvt_common_defs.h /usr/include/
		install $(LIB) $(INSTALLDIR)
		ln -sf $(INSTALLDIR)/$(LIB) $(INSTALLDIR)/libCAENV1x90SDK.so
		ldconfig

$(LIB)	:	$(OBJS)
		/bin/rm -f $(BINLIB)
		$(CC) $(FLAGS) -o $(LIB) $(OBJS) $(DEPLIBS)

$(OBJS)	:	makefile

%.o	:	%.c
		$(CC) $(COPTS) $(INCLUDEDIR) -c -o $@ $<

