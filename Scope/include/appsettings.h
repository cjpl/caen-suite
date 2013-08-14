/////////////////////////////////////////////////////////////////////////////
// Name:        appsettings.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     11/23/05 16:17:15
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _APPSETTINGS_H_
#define _APPSETTINGS_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "appsettings.h"
#endif

#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/thread.h>
#include <wx/arrstr.h>

#include "generic_board.h"

class wxMutex;

WX_DEFINE_ARRAY_INT(int, IntArray);

class AppSettings
{
public:
	typedef enum
	{
		EXT_TRIGGER_MSK=		0x0001,				// external trigger
		CHANNEL_TRIGGER_MSK=	0x0002,				// Channels trigger
		SW_AUTO_TRIGGER_MSK=	0x0004,				// Software auto retrigger
	} TRIGGER_MSK;
	typedef enum
	{
		NO_TRIGGER= 0,
		RISING_EDGE,
		FALLING_EDGE,
	} TRIGGER_EDGE_TYPE;
	typedef enum
	{
		NO_LINE= 0,
		SOLID,
		DASHED,
		DASH_DOT,
		DOTTED,
	} GRID_LINE_TYPE;

public:
	//
	// Methods
	AppSettings( void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool));
	~AppSettings( void);
	bool Load( void);
	bool Save( void);
	bool SetGridPen( int scope_index, const wxPen* grid_pen, const wxPen* mid_grid_pen= NULL);
	bool SetBackBrush( int scope_index, const wxBrush* back_brush);
	bool Connect( bool simulate= false);
	bool EndVME( void);
	bool InitVME( void);

	void (* ScopeRefresh)( int, bool);
	void (* UpdateSamplesReadyLed)( bool);
	void SetDiv2Pix( int scope_index, double div_2_pix_X);
	void SetSec2Div( int scope_index, double sec_2_div);
	void SetSec2Sample( double sec_2_sample);
	void SetClock( bool use_ext_clock, double ext_rate_MHz);

	inline UINT32 Sec2Pix( int scope_index, double value){ return (UINT32)(double)( this->m_sec_2_pix[ scope_index]* value);};
	inline double Sample2Sec( int value){ return this->m_sample_2_sec* (double)value;};

	//
	// Common lock
	wxMutex m_mutex;
	//
	// Properties
	TRIGGER_MSK m_trigger_msk;					// Trigger type masks
	int m_post_trigger;							// Number of post trigger samples ( < 0 means pretrigger)
	int m_num_sample;							// The number of setted saples per channel
	wxArrayPtrVoid m_board_array;				// Boards array
	wxColor m_grid_line_color[ SCOPE_NUM_PANELS];		// The grid color
	GRID_LINE_TYPE m_grid_line_type[ SCOPE_NUM_PANELS];	// The grid line type
	int m_grid_line_width[ SCOPE_NUM_PANELS];			// The grid line width
	wxColor m_background_color[ SCOPE_NUM_PANELS];		// The background color
	wxString m_record_folder;					// The folder where to store recorded files
	TRIGGER_EDGE_TYPE m_trigger_edge_type;		// Trigger edge type

	wxPen *m_grid_pen[ SCOPE_NUM_PANELS];
	wxPen *m_mid_grid_pen[ SCOPE_NUM_PANELS];
	wxBrush *m_back_brush[ SCOPE_NUM_PANELS];
	int m_max_log_X;							// maximum logical unit X
	int m_offsetSample[ SCOPE_NUM_PANELS];		// Horizontal offset (samples)
	double m_sec_2_sample;						// Samples/ Sec conversion factor	
	double m_sec_2_div[ SCOPE_NUM_PANELS];		// Div/ Sec conversion factor
	double m_sample_2_sec;						// Sec/ Sample conversion factor	

	double m_int_rate_MHz;						// Internal clock (MHz)
	double m_ext_rate_MHz;						// External clock (MHz)
	bool m_use_ext_clock;						// External/ Internal clock usage
	bool m_use_TTL;								// Use TTL/NIM external signals 
	bool m_trigger_position_keep;				// Keep trigger position on screen
	bool m_started;								// Start acquiring upon loading
	bool m_show_left_pane;						// Show left pane upon loading
	bool m_show_bottom_pane;					// Show bottom pane upon loading
	bool m_show_scope_left_top_pane;			// Show scope left top pane upon loading
	bool m_show_scope_right_top_pane;			// Show scope right top pane upon loading
	bool m_show_scope_left_bottom_pane;			// Show scope left bottom pane upon loading
	bool m_show_scope_right_bottom_pane;		// Show scope right bottom pane upon loading

	wxArrayString m_board_types;

	double m_sec_2_pix[ SCOPE_NUM_PANELS];
	double m_div_2_pix_X[ SCOPE_NUM_PANELS], m_div_2_pix_Y[ SCOPE_NUM_PANELS];
	int m_pix_Y[ SCOPE_NUM_PANELS], m_pix_X[ SCOPE_NUM_PANELS];
	static const wxString get_default_path();
	static const wxString GetExecutablePath();
	static const wxString get_settings_path();

	wxString m_link_type_string;
	int m_link_num;
	int m_node_num;
	int m_base_address;
protected:
	int GetChannelGroup( const wxString &boardLabel, int numGroups, int defGroup);

	int32_t m_vme_handle;
};


#endif


