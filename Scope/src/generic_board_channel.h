/////////////////////////////////////////////////////////////////////////////
// Name:        generic_board_channel.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_BOARD_CHANNEL_H_
#define _GENERIC_BOARD_CHANNEL_H_

#define SAMPLE_LOCK

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "generic_board_channel.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

/*!
 * Includes
 */
#include <wx/colour.h>
#include <wx/config.h>			
#include <wx/confbase.h>		
#include <wx/fileconf.h>		
#include <wx/file.h>		

#include "common_defs.h"

extern "C" 
{
	#include "cvt_board_commons.h"
}

//#include "appsettings.h"
class AppSettings;
class RecordChControl;
class CommonChControlBase;
class CursorChControl;
class GenericBoard;

class GenericBoardChannel
{
public:
	typedef enum
	{
		HEX= 0,
		ASCII_DEC,
		ASCII_HEX,
	} RECORD_FORMAT_TYPE;
public:
	GenericBoardChannel( GenericBoard* parent, int ch_index, cvt_board_data* p_data, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex, AppSettings *p_app_settings);
	virtual ~GenericBoardChannel( void);
	//
	// Properties
	bool m_enabled;
	bool m_scope_view_enabled[ SCOPE_NUM_PANELS];
	wxColour m_line_color[ SCOPE_NUM_PANELS];
	int m_line_width[ SCOPE_NUM_PANELS];
	int m_record_rate_divider;
	bool m_record_enabled;
	RECORD_FORMAT_TYPE m_record_format_type;

	double m_offset_y[ SCOPE_NUM_PANELS];
	double m_volt_2_bit, m_bit_2_volt;

	double m_volt_2_div[ SCOPE_NUM_PANELS], m_volt_2_pix[ SCOPE_NUM_PANELS];
	double m_div_2_pix_X[ SCOPE_NUM_PANELS], m_div_2_pix_Y[ SCOPE_NUM_PANELS];
	int m_pix_Y[ SCOPE_NUM_PANELS], m_pix_X[ SCOPE_NUM_PANELS];
	double m_left_div_2_pix_Y[ SCOPE_NUM_PANELS];
	int m_left_pix_Y[ SCOPE_NUM_PANELS], m_left_pix_X[ SCOPE_NUM_PANELS];
	int m_cursor_position[ SCOPE_NUM_PANELS][SCOPE_NUM_CURSORS];
	bool m_cursor_enabled[ SCOPE_NUM_PANELS];

	double m_medium_value;
	bool m_overload_up, m_overload_down;
	int m_sample_shift;

	wxPen *m_line_pen[ SCOPE_NUM_PANELS];
	wxPen *m_trigger_pen[ SCOPE_NUM_PANELS];
	wxBrush *m_trigger_brush[ SCOPE_NUM_PANELS];

	RecordChControl* m_p_record_ch_control;
	CommonChControlBase* m_p_common_ch_control;
	CursorChControl* m_p_cursor_ch_control[ SCOPE_NUM_PANELS];
	virtual void SetEnable( bool enable, bool disable_all);
	void (* ScopeRefresh)( int, bool);
	bool SetLinePen( int scope_index, const wxPen* line_pen, const wxPen* trigger_pen= NULL);

	//
	// Methods
	virtual bool LoadConfig( wxConfigBase* p_config, const wxString& base_section);
	virtual bool SaveConfig( wxConfigBase* p_config, const wxString& base_section);

	void SetSec2Pix( int scope_index, double sec_per_div);

	inline int Volt2Pix( int scope_index, double value){ return (int)(double)( this->m_volt_2_pix[ scope_index] * value);};
	inline int PixY2Dc( int scope_index, int value){ return this->m_pix_Y[ scope_index]- value;};

	void SetDiv2Pix( int scope_index, double div_2_pix_Y);
	void SetLeftDiv2Pix( int scope_index, double div_2_pix_Y);

	int Sec2Pix( int scope_index, double value);
	double Sample2Sec( int value);
	double Pix2Sec( int scope_index, int value);
	int Sec2Sample( double value);

	void SetVolt2Div( int scope_index, double volt_2_div);
	void SetVolt2Pix( int scope_index, double volt_2_pix);
	void SetPix( int scope_index, int pix_X, int pix_Y){ this->m_pix_X[ scope_index] = pix_X; this->m_pix_Y[ scope_index]= pix_Y;};
	void SetLeftPix( int scope_index, int pix_X, int pix_Y){ this->m_left_pix_X[ scope_index]= pix_X; this->m_left_pix_Y[ scope_index]= pix_Y;};
	void DrawCursor( int scope_index, wxDC &dc);
	void DrawSamples( int scope_index, wxDC &dc);
	void DrawPosition( int scope_index, wxDC &dc);

	bool ToggleRecordStatus( const wxString &path, const wxString &file_name, const wxString &timestamp, bool start);
	virtual bool RecordSamples( void);
	virtual wxString GetRecordChannelNumber( void);

	// Pure virtual 
	virtual double GetSampleVolt( int i) = 0;
	virtual int GetSample( int i)= 0;
	virtual inline int GetSampleRaw( int i)= 0;
	virtual UINT32 GetBufferCount( void)= 0;
	virtual void DrawTrigger( int scope_index, wxDC &dc)= 0;

	GenericBoard* GetParent( ){ return this->m_parent;};
protected:
	GenericBoard* m_parent;
	bool m_is_recording;
	wxFile *m_p_record_file;

	wxMutex	*m_p_data_mutex;
#ifdef SAMPLE_LOCK
	wxMutex m_samples_mutex;
#endif
	cvt_board_data* m_p_data;
	int m_ch_index;
	UINT32 m_record_sample_counter;
	AppSettings *m_p_app_settings;
	wxMutex m_record_mutex;

};


#endif	// _GENERIC_BOARD_CHANNEL_H_

