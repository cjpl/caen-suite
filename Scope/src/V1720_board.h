/////////////////////////////////////////////////////////////////////////////
// Name:        V1720_board.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _V1720_board_H_
#define _V1720_board_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "V1720_board.h"
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

class V1720Board :	public V17XXBoard
{
public:
	V1720Board( int board_index, void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings* p_app_settings, V17XXBoard::BOARD_VARIANT board_variant);

	//
	// Pure virtual implememtation
	wxString GetTypeString() 
	{ 
		switch( m_board_variant)
		{
		case BV_VME:
			return _("V1720");
		case BV_DESKTOP:
			return _("DT5720");
		case BV_NIM:
			return _("N6720");
		}
		return _("XXX720 undef variant");
	};
	CVT_V17XX_TYPES GetType(){ return CVT_V1720; }
	double GetClockMHz() const { return CVT_V17XX_BOARD_CLOCK_KHZ[ CVT_V1720_BOARD_CLOCK_INDEX]*0.001;};
	int GetSampleBit() const { return 12;} 
	double GetVolt2Bit() const { return ((double)( 1<< 16)) / 2.00;};
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
	int GetPostTriggerDivider() const { return 4;}


	//
	// Virtuals override
	virtual double GetDACUpdateFactor( void){ return 4.0;};

};


#endif	// _V1720_board_H_

