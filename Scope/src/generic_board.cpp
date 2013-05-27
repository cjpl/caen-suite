/////////////////////////////////////////////////////////////////////////////
// Name:        generic_board.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////


#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "generic_board.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "generic_board.h"
#include "appsettings.h"
#include "boardworkerthread.h"
#include "record_ch_control.h"

GenericBoard::GenericBoard( int board_index, void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings *p_app_settings): 
							ScopeRefresh( scope_refresh), UpdateSamplesReadyLed(update_samples_ready_led), m_p_data_mutex( p_data_mutex), m_p_worker_thread(NULL), 
							m_p_app_settings( p_app_settings), m_board_index( board_index)
{
	this->m_p_data= NULL;
	this->m_is_running= false;
	this->m_is_recording= false;
	this->m_record_max_buffers= 0;
	this->m_record_use_max_buffers= false;
	m_isDPP= false;
}

GenericBoard::~GenericBoard( )
{
	// Stops the thread
	this->DoStopRunning();

	// Delete channel list
	for( size_t i= 0; i< this->m_channel_array.GetCount(); i++)
	{
		delete (GenericBoardChannel*)this->m_channel_array[i];
	}
	this->m_channel_array.Clear();
	// Delete virtual channel list
	for( size_t i= 0; i< this->m_virtual_channel_array.GetCount(); i++)
	{
		delete (GenericBoardChannel*)this->m_virtual_channel_array[i];
	}
	this->m_virtual_channel_array.Clear();
	
}
bool GenericBoard::LoadConfig( wxConfigBase* p_config, const wxString& base_section)
{
	/*
		Application setting board parameters' file structure

          |- NUM_CHANNEL= N					
          |- NUM_VIRTUAL_CHANNEL= M					
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
		this->m_channel_array.Add( this->CreateChannel( i, this->ScopeRefresh, this->m_p_data_mutex));
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
bool GenericBoard::SaveConfig( wxConfigBase* p_config, const wxString& base_section)
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
bool GenericBoard::DoStartRunning( void)
{
	if( this->IsRunning())
		return true;

	// Starts the thread
	this->m_p_worker_thread= new BoardWorkerThread( this);
	switch( this->m_p_worker_thread->Create( ))
	{
	case wxTHREAD_NO_ERROR:
		break;
	default:
		this->DoStopRunning();
		return false;
	}

	if( !this->DoStartAcquisition())
	{
		this->DoStopRunning();
	}

	// this->m_worker_thread->SetPriority( WXTHREAD_MAX_PRIORITY);

	switch( this->m_p_worker_thread->Run( ))
	{
	case wxTHREAD_NO_ERROR:
		break;
	default:
		this->DoStopRunning();
		return false;
	}
    this->SetRunning( true);
	return true;
}

void GenericBoard::DoStopRunning( void)
{

	if( !this->IsRunning())
		return;
//    this->m_thread_exited= false;

	
	this->DoStopAcquisition();

	// Stops the thread
	if( this->m_p_worker_thread)
	{
		switch( this->m_p_worker_thread->Delete( ))
		{
		case wxTHREAD_NO_ERROR:
/*
            while( !this->m_thread_exited)
            {
                // HACK insert timeout here !!!
            }
*/
			break;
		default:
			this->m_p_worker_thread->Kill();
			break;
		}
		this->m_p_worker_thread= NULL;
        this->SetRunning( false);
	}
}

void GenericBoard::DrawCursor( int scope_index, wxDC &dc)
{
	// 
	// Loop channels
	for( size_t j= 0; j< this->m_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_channel_array[ j];
		board_channel->DrawCursor( scope_index,  dc);
	}
	// 
	// Loop virtual channels
	for( size_t j= 0; j< this->m_virtual_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_virtual_channel_array[ j];
		board_channel->DrawCursor( scope_index,  dc);
	}
}
void GenericBoard::DrawTrigger( int scope_index, wxDC &dc)
{
	// 
	// Loop channels
	for( size_t j= 0; j< this->m_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_channel_array[ j];
		board_channel->DrawTrigger( scope_index, dc);
	}
	// 
	// Loop Virtual channels
	for( size_t j= 0; j< this->m_virtual_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_virtual_channel_array[ j];
		board_channel->DrawTrigger( scope_index, dc);
	}
}
void GenericBoard::DrawPosition( int scope_index, wxDC &dc)
{
	// 
	// Loop channels
	for( size_t j= 0; j< this->m_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_channel_array[ j];
		board_channel->DrawPosition( scope_index, dc);
	}
	// 
	// Loop Virtual channels
	for( size_t j= 0; j< this->m_virtual_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_virtual_channel_array[ j];
		board_channel->DrawPosition( scope_index, dc);
	}
}

void GenericBoard::SetDiv2Pix( int scope_index, double div_2_pix_Y)
{
	// 
	// Loop channels
	for( size_t j= 0; j< this->m_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_channel_array[ j];
		board_channel->SetDiv2Pix( scope_index, div_2_pix_Y);
	}
	// 
	// Loop Virtual channels
	for( size_t j= 0; j< this->m_virtual_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_virtual_channel_array[ j];
		board_channel->SetDiv2Pix( scope_index, div_2_pix_Y);
	}
}

void GenericBoard::SetLeftDiv2Pix( int scope_index, double div_2_pix_Y)
{
	// 
	// Loop channels
	for( size_t j= 0; j< this->m_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_channel_array[ j];
		board_channel->SetLeftDiv2Pix( scope_index, div_2_pix_Y);
	}
	// 
	// Loop Virtual channels
	for( size_t j= 0; j< this->m_virtual_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_virtual_channel_array[ j];
		board_channel->SetLeftDiv2Pix( scope_index, div_2_pix_Y);
	}
}
void GenericBoard::SetPix( int scope_index, int pix_X, int pix_Y)
{
	// 
	// Loop channels
	for( size_t j= 0; j< this->m_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_channel_array[ j];
		board_channel->SetPix( scope_index, pix_X, pix_Y);
	}
	// 
	// Loop virtual channels
	for( size_t j= 0; j< this->m_virtual_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_virtual_channel_array[ j];
		board_channel->SetPix( scope_index, pix_X, pix_Y);
	}
}
void GenericBoard::SetLeftPix( int scope_index, int pix_X, int pix_Y)
{
	// 
	// Loop channels
	for( size_t j= 0; j< this->m_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_channel_array[ j];
		board_channel->SetLeftPix( scope_index, pix_X, pix_Y);
	}
	// 
	// Loop Virtual channels
	for( size_t j= 0; j< this->m_virtual_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_virtual_channel_array[ j];
		board_channel->SetLeftPix( scope_index, pix_X, pix_Y);
	}
}

void GenericBoard::DrawSamples( int scope_index, wxDC &dc)
{
	// 
	// Loop channels
	for( size_t j= 0; j< this->m_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_channel_array[ j];
		board_channel->DrawSamples( scope_index, dc);
	}
	// 
	// Loop virtual channels
	for( size_t j= 0; j< this->m_virtual_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_virtual_channel_array[ j];
		board_channel->DrawSamples( scope_index, dc);
	}
}

bool GenericBoard::ToggleRecordStatus( const wxString &path, const wxString &file_name, const wxString &timestamp, bool start, bool use_max_buffer, int max_buffer)
{
	bool ret= true;
	//
	// Append board id
	wxString new_file_name= wxString::Format( _T("%sB%02d"), file_name.c_str(), this->m_board_index);
	// 
	// Loop channels
	for( size_t j= 0; j< this->m_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_channel_array[ j];
		if( !board_channel->ToggleRecordStatus(  path, new_file_name, timestamp, start))
			ret= false;
		board_channel->m_p_record_ch_control->Enable( !start);
	}
	// 
	// Loop Virtual channels
	for( size_t j= 0; j< this->m_virtual_channel_array.GetCount(); j++)
	{
		GenericBoardChannel *board_channel= ( GenericBoardChannel *)this->m_virtual_channel_array[ j];
		if( !board_channel->ToggleRecordStatus(  path, new_file_name, timestamp, start))
			ret= false;
		board_channel->m_p_record_ch_control->Enable( !start);
	}

	this->m_record_max_buffers= max_buffer;
	this->m_record_use_max_buffers= use_max_buffer;

	this->m_is_recording= start;

	return ret;
}

bool GenericBoard::IsRunning( void)
{
    wxMutexLocker lock( this->m_p_app_settings->m_mutex);
    return this->m_is_running;
}

void GenericBoard::SetRunning( bool value)
{
    wxMutexLocker lock( this->m_p_app_settings->m_mutex);
    this->m_is_running= value;
}
GenericBoardChannel* GenericBoard::CreateVirtualChannel( int ch_index, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex)
{
	return new VirtualBoardChannel( this, ch_index, this->m_p_data, scope_refresh, p_data_mutex, this->m_p_app_settings);
}

bool GenericBoard::GetPhysicalChannelValue( int ch_index, int sample_index, double &result)
{
	result= 0;
	if( ch_index>= (int)this->m_channel_array.GetCount())
		return false;
	if( sample_index>= (int)((GenericBoardChannel*)this->m_channel_array[ ch_index])->GetBufferCount())
		return false;
	result= ((GenericBoardChannel*)this->m_channel_array[ ch_index])->GetSample( sample_index);
	return true;
}
bool GenericBoard::GetPhysicalChannelValueVolt( int ch_index, int sample_index, double &result)
{
	result= 0;
	if( ch_index>= (int)this->m_channel_array.GetCount())
		return false;
	if( sample_index>= (int)((GenericBoardChannel*)this->m_channel_array[ ch_index])->GetBufferCount())
		return false;
	result= ((GenericBoardChannel*)this->m_channel_array[ ch_index])->GetSampleVolt( sample_index);
	return true;
}

bool GenericBoard::GetPhysicalChannelBufferCount( int ch_index, UINT32 &result)
{
	result= 0;
	if( ch_index>= (int)this->m_channel_array.GetCount())
		return false;
	result= ((GenericBoardChannel*)this->m_channel_array[ ch_index])->GetBufferCount();
	return true;
}




