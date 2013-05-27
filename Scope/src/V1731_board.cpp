/////////////////////////////////////////////////////////////////////////////
// Name:        V1731_board.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////


#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "V1731_board.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "V1731_board.h"
#include "V17XX_board_channel.h"
#include "appsettings.h"

V1731Board::V1731Board( int board_index, void (*scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings *p_app_settings, V17XXBoard::BOARD_VARIANT board_variant, bool is_des_mode): 
			V17XXBoard( board_index, scope_refresh, update_samples_ready_led, p_data_mutex, p_app_settings, board_variant), m_is_des_mode( is_des_mode)
{
}

bool V1731Board::Init( long	vme_handle)
{
	if( !V17XXBoard::Init( vme_handle))
		return false;

	// ADC Calibration
	UINT8 ch_msk= 0x00;
	//for( int i= 0; i< (UINT8)this->m_channel_array.GetCount(); i++)
	//{
	//	ch_msk|= 1<< i;
	//}
	ch_msk= GetChEnableMsk();

	// Prompt odd channel disconnect here
	//if( this->m_is_des_mode) {
	//	wxMessageBox( wxT("CAENScope is about to perform an ADCs' calibration!\nPlease make sure that odd channels' signals are disconnected "), wxT("Warning"), wxOK | wxCENTRE | wxICON_WARNING  );
	//}
	wxMessageBox( wxT("CAENScope is about to perform an ADCs' calibration!\nPlease make sure that channels' signals are disconnected "), wxT("Warning"), wxOK | wxCENTRE | wxICON_WARNING  );
	
	if( !cvt_V1724_adc_calib( (cvt_V1724_data* )this->m_p_data, ch_msk))
	{
		wxLogError( _T( "Error during ADCs' calibration\n"));
	}	
	if( !cvt_V1724_software_reset( (cvt_V1724_data* )this->m_p_data))
	{
		wxLogError( _T( "Error during software reset .\n"));
	}	

	if( !cvt_V1724_set_des_mode( (cvt_V1724_data* )this->m_p_data, this->m_is_des_mode? TRUE: FALSE))
	{
		wxLogError( _T( "Error during cvt_V1724_set_des_mode execution \n"));
	}	
	// Repeat some initialization after software reset

	//
	// Write trigger mode
	if( !this->WriteTriggerMode( false))
		return false;
	// 
	// Front Panel IO
	if( !this->SetFrontPanelIO( this->m_p_app_settings->m_use_TTL))
		return false;

	return true;
}


bool V1731Board::GetBoardMemory( UINT32 &num_ksamples_per_channel)
{
	UINT32 reg_value32= 0;

	// 
	// read the board id
	if( !cvt_read( this->m_p_data, CVT_V1724_BOARD_INFO_ADD, &reg_value32, CVT_V1724_BOARD_INFO_AM, CVT_V1724_BOARD_INFO_DATA_SIZE))
	{
		return false;
	}
	num_ksamples_per_channel= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32);
	num_ksamples_per_channel*= 4;		// 8 bit data
	return true;
}
