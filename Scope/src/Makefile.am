datadir=/etc
#CAENScopeprgdir=
#CAENScopeprg_PROGRAMS=CAENScope
bin_PROGRAMS=CAENScope
CAENScope_SOURCES=V17XX_board.cpp caenscope.cpp physical_board_channel.cpp rpn_handler.cpp virtual_board_channel.cpp virtual_channel_def_dialog.cpp virtual_common_ch_control.cpp wxBackgroundBitmap.cpp common_ch_control_base.cpp appsettings.cpp boardworkerthread.cpp common_ch_control.cpp cursor_ch_control.cpp  drawing_canvas.cpp drawing_left_canvas.cpp drawing_panel.cpp generic_board.cpp generic_board_channel.cpp hyperlinkctrl.cpp infodialog.cpp mainframe.cpp record_ch_control.cpp trigger_ch_control.cpp V1724_board.cpp V1721_board.cpp V1720_board.cpp V1731_board.cpp V1740_board.cpp V17XX_board_channel.cpp V1740_board_channel.cpp view_ch_control.cpp  V1751_board.cpp device_select_dialog.cpp 
CAENScope_LDADD = -lCAENdigitizerSDK -lCAENVME
INCLUDES = -I../include
pkgdata_DATA=settings.txt ../img/about_34.png ../img/caen.png ../img/exit_34.png ../img/scope2.png ../img/scope_lb.png ../img/scope_lt.png ../img/scope_rb.png ../img/scope_rt.png ../img/view_bottom_34.PNG ../img/view_left_34.PNG ../img/scope2.xpm


install-data-hook:
	chmod 777 /etc/CAENScope
