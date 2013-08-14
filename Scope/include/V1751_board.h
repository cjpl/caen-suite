/////////////////////////////////////////////////////////////////////////////
// Name:        V1751_board.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _V1751_board_H_
#define _V1751_board_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "V1751_board.h"
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

class V1751Board :	public V17XXBoard
{
public:
	V1751Board( int board_index, void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings* p_app_settings, V17XXBoard::BOARD_VARIANT board_variant, bool is_des_mode);

	//
	// Pure virtual implementation
	wxString GetTypeString() 
	{ 
		switch( m_board_variant)
		{
		case BV_VME:
			return this->m_is_des_mode? _("V1751_DES"): _("V1751");
		case BV_DESKTOP:
			return this->m_is_des_mode? _("DT5751_DES"): _("DT5751");
		case BV_NIM:
			return this->m_is_des_mode? _("N6751_DES"): _("N6751");
		}
		return this->m_is_des_mode? _("XXX751_DES undef variant"):  _("XXX751 undef variant");
	};
	CVT_V17XX_TYPES GetType() { return CVT_V1751;}

// HACK rivedere qui V1751Board::Parametri di configurazione
	double GetClockMHz() const { return CVT_V17XX_BOARD_CLOCK_KHZ[ this->m_is_des_mode? CVT_V1751_DES_BOARD_CLOCK_INDEX: CVT_V1751_BOARD_CLOCK_INDEX]*0.001;};
	int GetSampleBit() const { return 10;} 
	double GetVolt2Bit() const { return ((double)( 1<< 16)) / 1.014;};
	bool Init( long vme_handle);
	UINT8 GetChEnableMsk() const 
	{ 
		switch( m_board_variant)
		{
		case BV_VME:
			return this->m_is_des_mode? 0xaa: 0xff;
		case BV_DESKTOP:
		case BV_NIM:
			return this->m_is_des_mode? 0x0a: 0x0f;
		}
		return 0x00;
	}
	bool GetBoardMemory( UINT32 &num_ksamples_per_channel);

	//
	// Virtuals override
	virtual double GetDACUpdateFactor( void){ return 8.0;};
	int GetPostTriggerDivider() const { return m_is_des_mode ? 32: 16;}


protected:
	bool m_is_des_mode;

};


#endif	// _V1751_board_H_

