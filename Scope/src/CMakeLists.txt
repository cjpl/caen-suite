# -*- mode: cmake; -*-

############################################################
## sources
#file(GLOB cppsrcs "*.cpp")

# CAENScope
add_executable( CAENScope
  V17XX_board.cpp caenscope.cpp physical_board_channel.cpp rpn_handler.cpp
  virtual_board_channel.cpp virtual_channel_def_dialog.cpp
  virtual_common_ch_control.cpp wxBackgroundBitmap.cpp
  common_ch_control_base.cpp appsettings.cpp boardworkerthread.cpp
  common_ch_control.cpp cursor_ch_control.cpp drawing_canvas.cpp
  drawing_left_canvas.cpp drawing_panel.cpp generic_board.cpp
  generic_board_channel.cpp hyperlinkctrl.cpp infodialog.cpp mainframe.cpp
  record_ch_control.cpp trigger_ch_control.cpp V1724_board.cpp V1721_board.cpp
  V1720_board.cpp V1731_board.cpp V1740_board.cpp V17XX_board_channel.cpp
  V1740_board_channel.cpp view_ch_control.cpp V1751_board.cpp
  device_select_dialog.cpp )
set_target_properties( CAENScope PROPERTIES LINKER_LANGUAGE CXX )
target_link_libraries(CAENScope
  ${wxWidgets_LIBRARIES}
  CAENVME
  CAENdigitizerSDK
  )

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
