# -*- mode: cmake; -*-

############################################################
## sources
#file(GLOB cppsrcs "*.cpp")

link_libraries(CAENComm CAENDigitizer m pthread)

# WaveDump
add_executable( wavedump
  WaveDump.c WDconfig.c WDplot.c X742CorrectionRoutines.c fft.c keyb.c )

############################################################
## install

install( TARGETS wavedump
  RUNTIME
  DESTINATION ${INSTALL_LIBEXECDIR}/bin )

