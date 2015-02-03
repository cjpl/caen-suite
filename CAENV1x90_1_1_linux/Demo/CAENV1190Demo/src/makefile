########################################################################
#                                                                      
#              --- CAEN SpA - Computing Division ---                   
#                                                                      
#   V1190Demo Software Project                                        
#                                                                      
#   Created  :  Apr 2007      (Rel. 1.0)                                             
#                                                                      
#   Auth: NDA
#                                                                      
########################################################################

EXE	=	CAENV1190Demo

CC	=	gcc

COPTS	=	-fPIC -DLINUX -Wall 
#COPTS	=	-g -fPIC -DLINUX -Wall 

FLAGS	=	-Wall -s
#FLAGS	=	-Wall

DEPLIBS	=       -lCAENVME -lcurses -lCAENV1x90SDK

LIBS	=	

INCLUDEDIR =	-I./ -I../../../SDK/CAENV1x90SDK/

OBJS	=	console.o user_settings.o main.o


#########################################################################

all	:	$(EXE)

clean	:
		/bin/rm -f $(OBJS) $(EXE)

$(EXE)	:	$(OBJS)
		/bin/rm -f $(EXE)
		$(CC) $(FLAGS) -o $(EXE) $(OBJS) $(DEPLIBS)

$(OBJS)	:	makefile

%.o	:	%.c
		$(CC) $(COPTS) $(INCLUDEDIR) -c -o $@ $<

