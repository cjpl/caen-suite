################################################################################
#                                                                       
#  -- CAEN SpA - Divisione Sistemi Informatici
#
#
################################################################################
SUBDIRS = src

clean:
	@-for i in $(SUBDIRS); do \
		(cd $$i; echo begin SSi; make clean); done

all:
	@-for i in $(SUBDIRS); do \
		(cd $$i; echo begin SSi; make all); done
install:
	@-for i in $(SUBDIRS); do \
		(cd $$i; echo begin SSi; make install); done
