
add_library( CAENdigitizerSDK  STATIC # SHARED
  cvt_board_commons.c
  cvt_V1724.c )
set_target_properties( CAENdigitizerSDK PROPERTIES LINKER_LANGUAGE C
  LINK_FLAGS "-nostartfiles -s ${LDFLAGS}")
# target_link_libraries( CAENdigitizerSDK CAENVME )
