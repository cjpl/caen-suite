/////////////////////////////////////////////////////////////////////////////
// Name:        V1724_board.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////


#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "V1724_board.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "V1724_board.h"
#include "V17XX_board_channel.h"
#include "appsettings.h"

V1724Board::V1724Board( int board_index, void (*scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings *p_app_settings, V17XXBoard::BOARD_VARIANT board_variant): 
			V17XXBoard( board_index, scope_refresh, update_samples_ready_led, p_data_mutex, p_app_settings, board_variant)
{
}

bool V1724Board::GetBoardMemory( UINT32 &num_ksamples_per_channel)
{
	UINT32 reg_value32= 0;

	// 
	// read the board id
	if( !cvt_read( this->m_p_data, CVT_V1724_BOARD_INFO_ADD, &reg_value32, CVT_V1724_BOARD_INFO_AM, CVT_V1724_BOARD_INFO_DATA_SIZE))
	{
		return false;
	}
	num_ksamples_per_channel= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32);
	num_ksamples_per_channel*= 2;		// 14 bit data
	return true;
}
