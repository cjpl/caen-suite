/////////////////////////////////////////////////////////////////////////////
// Name:        V1740_board.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////


#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "V1740_board.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "V1740_board.h"
#include "V17XX_board_channel.h"
#include "V1740_board_channel.h"
#include "appsettings.h"

V1740Board::V1740Board( int board_index, void (*scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings *p_app_settings, V17XXBoard::BOARD_VARIANT board_variant): 
			V17XXBoard( board_index, scope_refresh, update_samples_ready_led, p_data_mutex, p_app_settings, board_variant)
{
	m_channel_group= 0;
}
bool V1740Board::GetBoardMemory( UINT32 &num_ksamples_per_channel)
{
	UINT32 reg_value32= 0;
	// 
	// read the board id
	if( !cvt_read( this->m_p_data, CVT_V1724_BOARD_INFO_ADD, &reg_value32, CVT_V1724_BOARD_INFO_AM, CVT_V1724_BOARD_INFO_DATA_SIZE))
	{
		return false;
	}

	num_ksamples_per_channel= ( CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)* 36 /* bits per word*/)/4 /* bits per nibble */ / 3 /* bits per sample */;
	num_ksamples_per_channel/= CVT_V1724_MAX_CHANNEL;

	return true;
}
GenericBoardChannel* V1740Board::CreateChannel( int ch_index, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex)
{
	return new V1740BoardChannel( this, ch_index, this->m_p_data, scope_refresh, p_data_mutex, this->m_p_app_settings);
}
bool V1740Board::LoadConfig( wxConfigBase* p_config, const wxString& base_section)
{
	/*
		Application setting board parameters' file structure

	      |- ADDRESS= 0xee00				// Hex board base address
          |- NUM_CHANNEL= N					
          |- NUM_VIRTUAL_CHANNEL= M					
          |- CHANNEL_GROUP= ##					
          |- [0]
          |   |- { CHANNEL DATA }
		  |   | ...
          |- [N-1]
          |   |- { CHANNEL DATA }
          |- [VIRT_0]
          |   |- { VIRTUAL CHANNEL DATA }
		  |   | ...
          |- [VIRT_(M-1)]
          |   |- { VIRTUAL CHANNEL DATA }
	*/
	if( this->m_p_data== NULL) 
		return false;

	//
	// Get the Channel Number
	int channel_number= 0;
	p_config->Read( base_section+ _("NUM_CHANNEL"), &channel_number, 0);
	for( int i= 0; i< channel_number; i++)
	{
		//
		// Get Channel specific parameters
		wxString channel_string= wxString::Format( _T("%s%i/"), base_section.c_str(), i);
		this->m_channel_array.Add( this->CreateChannel( i+ ( this->m_channel_group* CVT_V1724_MAX_CHANNEL) , this->ScopeRefresh, this->m_p_data_mutex));
		//
		// Load channel section
		if( !((GenericBoardChannel*)this->m_channel_array[i])->LoadConfig( p_config, channel_string))
			return false;
	}
	//
	// Get the Virtual Channel Number
	int virtual_channel_number= 0;
	p_config->Read( base_section+ _("NUM_VIRTUAL_CHANNEL"), &virtual_channel_number, 0);
	for( int i= 0; i< virtual_channel_number; i++)
	{
		//
		// Get Virtual Channel specific parameters
		wxString channel_string= wxString::Format( _T("%sVIRT_%i/"), base_section.c_str(), i);
		this->m_virtual_channel_array.Add( this->CreateVirtualChannel( i, this->ScopeRefresh, this->m_p_data_mutex));
		//
		// Load Virtual channel section
		if( !((GenericBoardChannel*)this->m_virtual_channel_array[i])->LoadConfig( p_config, channel_string))
			return false;
	}

	return true;


}
bool V1740Board::SaveConfig( wxConfigBase* p_config, const wxString& base_section)
{
	if( this->m_p_data== NULL)
		return false;

	//
	// Set the Channel Number
	if( !p_config->Write( base_section+ _("NUM_CHANNEL"), (int)this->m_channel_array.GetCount()))
		return false;
	for( size_t i= 0; i< this->m_channel_array.GetCount(); i++)
	{
		//
		// Set Channel specific parameters
		wxString channel_string= wxString::Format( _T("%s%i/"), base_section.c_str(), i);
		//
		// Save channel section
		if( !((GenericBoardChannel*)this->m_channel_array[i])->SaveConfig( p_config, channel_string))
			return false;
	}

	//
	// Set the Virtual Channel Number
	if( !p_config->Write( base_section+ _("NUM_VIRTUAL_CHANNEL"), (int)this->m_virtual_channel_array.GetCount()))
		return false;
	for( size_t i= 0; i< this->m_virtual_channel_array.GetCount(); i++)
	{
		//
		// Set Virtual Channel specific parameters
		wxString channel_string= wxString::Format( _T("%sVIRT_%i/"), base_section.c_str(), i);
		//
		// Save Virtual channel section
		if( !((GenericBoardChannel*)this->m_virtual_channel_array[i])->SaveConfig( p_config, channel_string))
			return false;
	}
	return true;
}
bool V1740Board::WriteSampleBufferSize( void)
{
	CVT_V1724_NUM_BLOCKS num_block_written;
	UINT16 num_k_samples= ( UINT16)( UINT32)(( UINT32)( this->m_p_app_settings->m_num_sample* CVT_V1724_MAX_CHANNEL)>> 10);
#ifndef SIMUL	
	if( !cvt_V1724_set_buffer_samples( (cvt_V1724_data* )this->m_p_data, num_k_samples, &num_block_written))
		return false;
	// Adjust the X size to the buffer size really setted 
	if( !cvt_V1724_get_buffer_samples( (cvt_V1724_data* )this->m_p_data, &num_k_samples, &num_block_written))
		return false;
	this->m_p_app_settings->m_max_log_X= (((int)num_k_samples)<< 10)/ CVT_V1724_MAX_CHANNEL;

	if( !cvt_V1724_set_acquisition_mode( (cvt_V1724_data* )this->m_p_data, false, num_block_written, CVT_V1724_ACQCTRL_ACQ_MODE_REGISTER_CTRL, FALSE, 0))
		return false;
	return cvt_V1724_data_clear( (cvt_V1724_data* )this->m_p_data)!= FALSE;
#else
	return true;
#endif
}
bool V1740Board::DoStartAcquisition( void) {
	if( cvt_V1724_set_readout_mode( (cvt_V1724_data* )this->m_p_data, TRUE, 1)== FALSE) {
		return false;
	}
	return cvt_V1724_start_acquisition( (cvt_V1724_data* )this->m_p_data, 1<< this->m_channel_group)!= FALSE;
}

bool V1740Board::WriteTriggerChannelMsk( UINT32 chMsk)
{
	int channelGroup= m_channel_group;
#ifndef SIMUL
	return cvt_write( m_p_data, 0x10A8+ ( m_channel_group<< 8), &chMsk, cvA32_S_DATA, cvD32)!= 0;
#else
	return true;
#endif
}
