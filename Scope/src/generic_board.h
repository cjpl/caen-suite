/////////////////////////////////////////////////////////////////////////////
// Name:        generic_board.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_BOARD_H_
#define _GENERIC_BOARD_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "generic_board.h"
#endif

/*!
 * Includes
 */
#include <wx/arrimpl.cpp> 
extern "C" 
{
	#include "cvt_board_commons.h"
	#include "cvt_V1724.h"
}
#include "generic_board_channel.h"
#include "virtual_board_channel.h"

class BoardWorkerThread;
class AppSettings;

class GenericBoard
{
public:
	GenericBoard( int board_index, void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings *p_app_settings);
	virtual ~GenericBoard(void);

	//
	// Properties
	wxArrayPtrVoid m_channel_array;
	wxArrayPtrVoid m_virtual_channel_array;
	wxMutex *m_p_data_mutex;
	void (* ScopeRefresh)( int, bool);
	void (* UpdateSamplesReadyLed)( bool);	

	//
	// Methods
	virtual bool LoadConfig( wxConfigBase* p_config, const wxString& base_section);
	virtual bool SaveConfig( wxConfigBase* p_config, const wxString& base_section);
	virtual GenericBoardChannel* CreateVirtualChannel( int ch_index, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex);
	virtual bool GetPhysicalChannelValue( int ch_index, int sample_index, double &result);
	virtual bool GetPhysicalChannelValueVolt( int ch_index, int sample_index, double &result);
	virtual bool GetPhysicalChannelBufferCount( int ch_index, UINT32 &result);
	virtual double GetDACUpdateFactor( void){ return 1.0;};
	void SetBaseAddress( UINT16 base_address) 
	{
		if( !m_p_data) return;
		m_p_data->m_base_address= base_address;
	}
	UINT16 GetBaseAddress ( ) const
	{
		if( !m_p_data) return 0;
		return m_p_data->m_base_address;
	}
	const wxString &GetROCFwRev ( ) const {return m_roc_fw;}
	const wxString &GetAMCFwRev ( ) const {return m_amc_fw;}

	// 
	// Pure virtual methods
	virtual UINT8 GetChEnableMsk() const = 0;
	virtual wxString GetTypeString()= 0;
	virtual CVT_V17XX_TYPES GetType()= 0;
	virtual double GetClockMHz() const = 0;
	virtual int GetSampleBit() const = 0; 
	virtual double GetVolt2Bit() const = 0;
	virtual bool Open( long vme_handle)= 0;
	virtual GenericBoardChannel* CreateChannel( int ch_index, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex)= 0;
	virtual bool WriteSampleBufferSize( void) = 0;
	virtual bool WriteTriggerMode( bool started) = 0;
	virtual bool WriteSoftwareTrigger( void) = 0;
	virtual bool SetFrontPanelIO( bool use_TTL)= 0;
	virtual bool ReadBoardData( UINT32 *p_max_num_samples, UINT32* p_num_events)= 0;
	virtual bool DoStartAcquisition( void)= 0;
	virtual bool DoStopAcquisition( void)= 0;
	virtual bool GetBoardMemory( UINT32 &num_ksamples_per_channel)= 0;

	virtual bool Init( long /* vme_handle*/){ return true;};

	void DrawTrigger( int scope_index, wxDC &dc);
	void DrawCursor( int scope_index, wxDC &dc);
	void DrawSamples( int scope_index, wxDC &dc);
	void SetDiv2Pix( int scope_index, double div_2_pix_Y);
	void SetLeftDiv2Pix( int scope_index, double div_2_pix_Y);
	void SetSec2Div( int scope_index, double sec_2_div);
	void SetPix( int scope_index, int pix_X, int pix_Y);
	void SetLeftPix( int scope_index, int pix_X, int pix_Y);
	void DrawPosition( int scope_index, wxDC &dc);

	bool DoStartRunning( void);
	void DoStopRunning( void);
	bool ToggleRecordStatus( const wxString &path, const wxString &file_name, const wxString &timestamp, bool start, bool use_max_buffer, int max_buffer);
	bool IsRunning( void);
    void SetRunning( bool value);
//    bool m_thread_exited;
	bool IsDPP( ) const { return m_isDPP;}
protected:
	cvt_board_data* m_p_data;
	BoardWorkerThread *m_p_worker_thread;
	bool m_is_running;
	AppSettings *m_p_app_settings;
	int m_board_index;
	bool m_is_recording;
	int m_record_max_buffers;
	bool m_record_use_max_buffers;
	wxString m_roc_fw;
	wxString m_amc_fw;
	bool m_isDPP;
friend class BoardWorkerThread;
};


#endif		// _GENERIC_BOARD_H_

