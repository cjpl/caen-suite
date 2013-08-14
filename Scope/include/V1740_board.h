/////////////////////////////////////////////////////////////////////////////
// Name:        V1740_board.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _V1740_board_H_
#define _V1740_board_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "V1740_board.h"
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

class V1740Board :	public V17XXBoard
{
public:
	V1740Board( int board_index, void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings* p_app_settings, V17XXBoard::BOARD_VARIANT board_variant);

	//
	// Pure virtual implememtation
	wxString GetTypeString() 
	{ 
		switch( m_board_variant)
		{
		case BV_VME:
			return _("V1740");
		case BV_DESKTOP:
			return _("DT5740");
		case BV_NIM:
			return _("N6740");
		}
		return _("XXX740 undef variant");
	};

	CVT_V17XX_TYPES GetType() { return CVT_V1740;}

	double GetClockMHz() const { return CVT_V17XX_BOARD_CLOCK_KHZ[ CVT_V1740_BOARD_CLOCK_INDEX]*0.001;};
	int GetSampleBit() const { return 12;} 
	double GetVolt2Bit() const { return ((double)( 1<< 16)) / 2.00;};		// HACK TBV
	UINT8 GetChEnableMsk() const 
	{ 
		switch( m_board_variant)
		{
		case BV_VME:
		case BV_DESKTOP:
		case BV_NIM:
			// The number of channels per group is the same for every board variant
			return 0xff;
		}
		return 0x00;
	}
	bool GetBoardMemory( UINT32 &num_ksamples_per_channel);

	//
	// Virtuals override
	virtual double GetDACUpdateFactor( void){ return 4.0;};
	virtual GenericBoardChannel* CreateChannel( int ch_index, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex);
	virtual bool LoadConfig( wxConfigBase* p_config, const wxString& base_section);
	virtual bool SaveConfig( wxConfigBase* p_config, const wxString& base_section);
	bool WriteSampleBufferSize( void);
	bool DoStartAcquisition( void);
	int GetPostTriggerDivider() const { return 3;}
	bool WriteTriggerChannelMsk( UINT32 chMsk);

	//
	// Properties
	int m_channel_group;
};


#endif	// _V1740_board_H_

