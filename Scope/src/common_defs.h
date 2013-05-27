/////////////////////////////////////////////////////////////////////////////
// Name:        common_defs.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _COMMON_DEFS_H_
#define _COMMON_DEFS_H_

extern "C" 
{
	#include "cvt_common_defs.h"
}

//
// Status bar pane indexes
#define STS_BAR_PANE_DUMMY		0
#define STS_BAR_PANE_BOARD		1
#define STS_BAR_PANE_RUN		2
#define STS_BAR_PANE_REC		3
#define STS_BAR_PANE_EXT_CLOCK	4
#define STS_BAR_PANE_EXT_TRIG	5
#define STS_BAR_PANE_AUTO_TRIG	6
#define STS_BAR_PANE_TRIG_EDGE	7
#define STS_BAR_PANE_NIM		8

#define STS_BAR_NUM_PANES		9

//
// Scope panes' number
#define SCOPE_NUM_PANELS		4
//
// Scope panes' cursor number
#define SCOPE_NUM_CURSORS		2


// Declare the end of record event
DECLARE_EVENT_TYPE( wxEVT_RECORD_END_EVENT, -1)
#define BOARD_WORKER_THREAD_ID	(wxID_HIGHEST+ 1)

#endif	// _COMMON_DEFS_H_
