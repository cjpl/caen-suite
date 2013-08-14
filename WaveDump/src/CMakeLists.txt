# -*- mode: cmake; -*-

############################################################
## sources
#file(GLOB cppsrcs "*.cpp")

link_libraries(CAENComm CAENDigitizer m pthread)

# WaveDump
add_executable( wavedump
  WaveDump.c WDconfig.c WDplot.c X742CorrectionRoutines.c fft.c keyb.c )
#target_link_libraries( WaveDump   ${CAENCOMM_LIB}   ${CAENDIGI_LIB} )

## ElDigi library
# add_library(ElDigi        SHARED ${cppsrcs})
# add_library(ElDigi-static STATIC ${cppsrcs})
# target_link_libraries(ElDigi        ${wxWidgets_LIBRARIES})
# target_link_libraries(ElDigi-static ${wxWidgets_LIBRARIES})

############################################################
## install
# install(TARGETS ElDigi  LIBRARY DESTINATION ${INSTALL_LIBDIR}
#   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
#   GROUP_READ GROUP_EXECUTE WORLD_EXECUTE WORLD_READ)
# install(TARGETS ElDigi-static  ARCHIVE DESTINATION ${INSTALL_LIBDIR})
