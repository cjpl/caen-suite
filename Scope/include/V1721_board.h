/////////////////////////////////////////////////////////////////////////////
// Name:        V1721_board.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _V1721_board_H_
#define _V1721_board_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "V1721_board.h"
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

class V1721Board :	public V17XXBoard
{
public:
	V1721Board( int board_index, void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings* p_app_settings, V17XXBoard::BOARD_VARIANT board_variant);

	//
	// Pure virtual implememtation
	wxString GetTypeString() 
	{ 
		switch( m_board_variant)
		{
		case BV_VME:
			return _("V1721");
		case BV_DESKTOP:
			return _("DT5721");
		case BV_NIM:
			return _("N6721");
		}
		return _("XXX721 undef variant");
	};

	CVT_V17XX_TYPES GetType() { return CVT_V1721; }
	double GetClockMHz() const { return CVT_V17XX_BOARD_CLOCK_KHZ[ CVT_V1721_BOARD_CLOCK_INDEX]*0.001;};
	int GetSampleBit() const { return 8;} 
	double GetVolt2Bit() const { return ((double)( 1<< 16)) / 1.081;};
	bool Init( long vme_handle);
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
	int GetPostTriggerDivider() const { return 8;}

	//
	// Virtuals override
	virtual double GetDACUpdateFactor( void){ return 8.0;};

};


#endif	// _V1721_board_H_

