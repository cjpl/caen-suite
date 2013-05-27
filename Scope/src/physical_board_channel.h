/////////////////////////////////////////////////////////////////////////////
// Name:        physical_board_channel.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     10/01/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICAL_BOARD_CHANNEL_H_
#define _PHYSICAL_BOARD_CHANNEL_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "physical_board_channel.h"
#endif

/*!
 * Includes
 */

#include "generic_board_channel.h"

extern "C" 
{
	#include "cvt_board_commons.h"
}

//#include "appsettings.h"

class PhysicalBoardChannel: public GenericBoardChannel
{
public:
	PhysicalBoardChannel( GenericBoard* parent, int ch_index, cvt_board_data* p_data, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex, AppSettings *p_app_settings);
	virtual ~PhysicalBoardChannel(void);
	//
	// Properties
	int m_DAC_offset_bit;
	double m_DAC_bit_2_volt, m_DAC_volt_2_bit;
	double m_trigger_threshold_volt;
	int m_trigger_thr_sample;
	bool m_trigger_enabled;

	//
	// Methods
	virtual bool LoadConfig( wxConfigBase* p_config, const wxString& base_section);
	virtual bool SaveConfig( wxConfigBase* p_config, const wxString& base_section);

	// Pure virtual implementation
	inline double GetSampleVolt( int i){ return (double)( this->GetSample( i))* this->m_bit_2_volt;};
	inline int GetSample( int i){ return (int)((( int)this->m_p_sample_buffer[i])<< this->m_sample_shift)- 0x8000;};
	inline int GetSampleRaw( int i){ return this->m_p_sample_buffer[i];};
	inline UINT32 GetBufferCount( void){ return this->m_sample_buffer_count;}
	void DrawTrigger( int scope_index, wxDC &dc);

	// Pure virtual 
	virtual bool ReadSamplesCache( UINT32 num_samples)= 0;
	virtual bool WriteDACOffset( void)= 0;
	virtual bool WriteChannelTrigger( void)= 0;

protected:
#ifdef SAMPLE_LOCK
	wxMutex m_samples_mutex;
#endif
	UINT16 *m_p_sample_buffer;
	UINT32 m_sample_buffer_size, m_sample_buffer_count;
	UINT16 *m_p_tmp_sample_buffer;
	UINT32 m_tmp_sample_buffer_size, m_tmp_sample_buffer_count, m_tmp_record_sample_counter;
};


#endif	// _PHYSICAL_BOARD_CHANNEL_H_

