/////////////////////////////////////////////////////////////////////////////
// Name:        V17XX_board_channel.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////

//#define __TEST__

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "V17XX_board_channel.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "appsettings.h"
#include "V17XX_board_channel.h"
extern "C" 
{
	#include "cvt_V1724.h"
}


V17XXBoardChannel::V17XXBoardChannel( GenericBoard* parent, int ch_index, cvt_board_data* p_data, void ( *scope_refresh)( int, bool), wxMutex* p_data_mutex, AppSettings *p_app_settings):
									PhysicalBoardChannel( parent, ch_index, p_data, scope_refresh, p_data_mutex, p_app_settings)
{
}

V17XXBoardChannel::~V17XXBoardChannel( void)
{
}

#ifdef SAMPLE_LOCK
bool V17XXBoardChannel:: ReadSamplesCache( UINT32 num_samples)
{
	bool ret= false;
	int max_log_X;
	{
		wxMutexLocker lock( *this->m_p_data_mutex);
		max_log_X= num_samples;
	}

	if( !this->m_enabled)
	{
		wxMutexLocker lock( this->m_samples_mutex);
		this->m_sample_buffer_count= 0;
		return false;
	}
	// Check if enough storage
	if( max_log_X> (int)this->m_tmp_sample_buffer_size)
	{
		delete this->m_p_tmp_sample_buffer;
		this->m_tmp_sample_buffer_size= max_log_X;
		this->m_p_tmp_sample_buffer= new UINT16[ this->m_tmp_sample_buffer_size];
	}
	// Set the number of requested samples
	this->m_tmp_sample_buffer_count= max_log_X;

#ifdef __TEST__
	static double phase= 0;
	for( unsigned int i= 0; i< this->m_sample_buffer_count; i++)
	{
		this->m_p_tmp_sample_buffer[i]= 0x8000+ (int)(double)( 1000.0* sin( phase+ 6.28*i*10.0/( this->m_tmp_sample_buffer_count)));
		//this->m_p_sample_buffer[i]= 0;
	}
	++phase;

    {
        //
        // Copy to final buffer
        wxMutexLocker lock( this->m_samples_mutex);
        if( max_log_X> (int)this->m_sample_buffer_size)
        {
            delete this->m_p_sample_buffer;
            this->m_sample_buffer_size= max_log_X;
            this->m_p_sample_buffer= new UINT16[ this->m_sample_buffer_size];
        }
        // Set the number of requested samples
        this->m_sample_buffer_count= this->m_tmp_sample_buffer_count;
        memcpy( this->m_p_sample_buffer, this->m_p_tmp_sample_buffer, this->m_sample_buffer_count<< 1);

    }
	ret= true;

#else
	{
		UINT32 read= this->m_tmp_sample_buffer_count;
		UINT8 board_id;
		UINT32 trigger_time_tag, event_counter;
		if( cvt_V1724_get_buffer_cache( ( cvt_V1724_data*)this->m_p_data, 0, this->m_ch_index, this->m_p_tmp_sample_buffer, &read, &board_id, &trigger_time_tag, &event_counter)== FALSE)
			return false;
		if( read)
		{

			//
			// Copy to final buffer
			wxMutexLocker lock( this->m_samples_mutex);
			if( max_log_X> (int)this->m_sample_buffer_size)
			{
				delete this->m_p_sample_buffer;
				this->m_sample_buffer_size= max_log_X;
				this->m_p_sample_buffer= new UINT16[ this->m_sample_buffer_size];
			}
			// Set the number of requested samples
			memcpy( this->m_p_sample_buffer, this->m_p_tmp_sample_buffer, read<< 1);

			this->m_sample_buffer_count= read;
			ret= true;
		}
	}
#endif
	return ret;

}
#else

bool V17XXBoardChannel:: ReadSamplesCache( UINT32 num_samples)
{

	bool ret= false;
	wxMutexLocker lock( *this->m_p_data_mutex);
	if( !this->m_enabled)
	{
		this->m_sample_buffer_count= 0;
		return false;
	}
	// Check if enough storage
	if( num_samples> (int)this->m_sample_buffer_size)
	{
		delete this->m_p_sample_buffer;
		this->m_sample_buffer_size= num_samples;
		this->m_p_sample_buffer= new UINT16[ this->m_sample_buffer_size];
	}
	// Set the number of requested samples
	this->m_sample_buffer_count= num_samples;

#ifdef __TEST__
	static double phase= 0;
	for( unsigned int i= 0; i< this->m_sample_buffer_count; i++)
	{
		this->m_p_sample_buffer[i]= 0x8000+ (int)(double)( 1000.0* sin( phase+ 6.28*i*10.0/( this->m_sample_buffer_count)));
		//this->m_p_sample_buffer[i]= 0;
	}
	++phase;
	ret= true;
#else
	{
		UINT32 read= this->m_sample_buffer_count;
		if( cvt_V1724_get_buffer_cache( ( cvt_V1724_data*)this->m_p_data, this->m_ch_index, this->m_p_sample_buffer, &read)== FALSE)
			return false;
		if( read)
		{
			this->m_sample_buffer_count= read;
			ret= true;
		}
	}
#endif
	return ret;

}
#endif

bool V17XXBoardChannel:: WriteDACOffset( void)
{
	// board offset
	int dac_offset= (int)(double)( -this->m_DAC_offset_bit* this->m_parent->GetDACUpdateFactor());
	if( dac_offset> 0x7fff)
	{
		dac_offset= 0x7fff;
	}
	else if( dac_offset< -0x8000)
	{
		dac_offset= -0x8000;
	}
	dac_offset+= 0x8000;
	return cvt_V1724_set_channel_offset( ( cvt_V1724_data*) this->m_p_data, 1<< this->m_ch_index, dac_offset)!= FALSE;
}

bool V17XXBoardChannel:: WriteChannelTrigger( void)
{
	// channel trigger settings
	// bool is_out_enabled= this->m_enabled&& ( this->m_trigger_edge_type!= GenericBoardChannel::TRIGGER_EDGE_TYPE::NO_TRIGGER);
	// bool is_in_enabled= this->m_enabled;
	// return cvt_V1724_set_channel_trigger( ( cvt_V1724_data*) this->m_p_data, 1<< this->m_ch_index, this->m_trigger_edge_type== GenericBoardChannel::TRIGGER_EDGE_TYPE::FALLING_EDGE, trigger_threshold, this->m_trigger_thr_sample)!= FALSE;

	// !!! WARNING !!! this->m_volt_2_bit refers to 16 bit data so scale it to the proper board resolution
	double scale_factor= (double)( 1<< this->m_parent->GetSampleBit())/ (double)( 1<< 16);
	int trigger_threshold= (int)( double)( this->m_trigger_threshold_volt* this->m_volt_2_bit* scale_factor);
	int min, max, mid;
	min= -( 1<< ( this->m_parent->GetSampleBit()- 1));
	max= -min- 1;
	mid= -min;

	if( trigger_threshold> max)
	{
		trigger_threshold= max;
	}
	else if( trigger_threshold< min)
	{
		trigger_threshold= min;
	}
	trigger_threshold+= mid;
#ifndef SIMUL
	return cvt_V1724_set_channel_trigger( ( cvt_V1724_data*) this->m_p_data, 1<< this->m_ch_index, trigger_threshold, this->m_trigger_thr_sample)!= FALSE;
#else
	return true;
#endif
}
