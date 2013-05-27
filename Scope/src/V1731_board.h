/////////////////////////////////////////////////////////////////////////////
// Name:        V1731_board.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _V1731_board_H_
#define _V1731_board_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "V1731_board.h"
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

class V1731Board :	public V17XXBoard
{
public:
	V1731Board( int board_index, void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings* p_app_settings, V17XXBoard::BOARD_VARIANT board_variant, bool is_des_mode);

	//
	// Pure virtual implementation
	wxString GetTypeString() 
	{ 
		switch( m_board_variant)
		{
		case BV_VME:
			return this->m_is_des_mode? _("V1731_DES"): _("V1731");
		case BV_DESKTOP:
			return this->m_is_des_mode? _("DT5731_DES"): _("DT5731");
		case BV_NIM:
			return this->m_is_des_mode? _("N6731_DES"): _("N6731");
		}
		return this->m_is_des_mode? _("XXX731_DES undef variant"):  _("XXX731 undef variant");
	};
	CVT_V17XX_TYPES GetType() { return CVT_V1731;}
	double GetClockMHz() const { return CVT_V17XX_BOARD_CLOCK_KHZ[ this->m_is_des_mode? CVT_V1731_DES_BOARD_CLOCK_INDEX: CVT_V1731_BOARD_CLOCK_INDEX]*0.001;};
	int GetSampleBit() const { return 8;} 
	double GetVolt2Bit() const { return ((double)( 1<< 16)) / 1.081;};
	bool Init( long vme_handle);
	UINT8 GetChEnableMsk() const 
	{ 
		switch( m_board_variant)
		{
		case BV_VME:
			return this->m_is_des_mode? 0x55: 0xff;
		case BV_DESKTOP:
		case BV_NIM:
			return this->m_is_des_mode? 0x05: 0x0f;
		}
		return 0x00;
	}
	bool GetBoardMemory( UINT32 &num_ksamples_per_channel);

	//
	// Virtuals override
	virtual double GetDACUpdateFactor( void){ return 8.0;};

	int GetPostTriggerDivider() const { return m_is_des_mode?  16: 8;}

protected:
	bool m_is_des_mode;

};


#endif	// _V1731_board_H_

