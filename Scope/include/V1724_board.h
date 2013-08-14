/////////////////////////////////////////////////////////////////////////////
// Name:        V1724_board.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _V1724_board_H_
#define _V1724_board_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "V1724_board.h"
#endif

/*!
 * Includes
 */

extern "C" 
{
	#include "cvt_V1724.h"
}
#include "V17XX_board.h"

class AppSettings;

class V1724Board :	public V17XXBoard
{
public:
	V1724Board( int board_index, void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings* p_app_settings, V17XXBoard::BOARD_VARIANT board_variant);

	//
	// Pure virtual implememtation
	wxString GetTypeString() 
	{ 
		switch( m_board_variant)
		{
		case BV_VME:
			return _("V1724");
		case BV_DESKTOP:
			return _("DT5724");
		case BV_NIM:
			return _("N6724");
		}
		return _("XXX724 undef variant");
	};
	CVT_V17XX_TYPES GetType() { return CVT_V1724;}
	double GetClockMHz() const { return CVT_V17XX_BOARD_CLOCK_KHZ[ CVT_V1724_BOARD_CLOCK_INDEX]*0.001;};
	int GetSampleBit() const { return 14;} 
	double GetVolt2Bit() const { return ((double)( 1<< 16)) / 2.25;};
	UINT8 GetChEnableMsk() const 
	{ 
		switch( m_board_variant)
		{
		case BV_VME:
			return 0xff;
		case BV_DESKTOP:
		case BV_NIM:
			return 0x0f;
		}
		return 0x00;
	}
	bool GetBoardMemory( UINT32 &num_ksamples_per_channel);
	int GetPostTriggerDivider() const { return 2;}

};


#endif	// _V1721_board_H_

