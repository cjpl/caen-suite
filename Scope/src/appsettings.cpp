// Name:        appsettings.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     11/23/05 16:17:15
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////


#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "appsettings.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <wx/arrimpl.cpp> 
#include <wx/config.h>			
#include <wx/confbase.h>		
#include <wx/fileconf.h>		
#include <wx/dir.h>


#include "appsettings.h"
#include "V1724_board.h"
#include "V1721_board.h"
#include "V1720_board.h"
#include "V1731_board.h"
#include "V1740_board.h"
#include "V1751_board.h"
#include "rpn_handler.h"
#include "mainframe.h"


#ifndef CAEN_VME_INVALID_HANDLE
	#define CAEN_VME_INVALID_HANDLE			-1
#endif

AppSettings::AppSettings( void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool)): m_link_num(0), m_node_num(0), m_vme_handle( CAEN_VME_INVALID_HANDLE),
								ScopeRefresh( scope_refresh), UpdateSamplesReadyLed( update_samples_ready_led), m_mutex( wxMUTEX_RECURSIVE)
{
	wxString setting_filename;
	setting_filename= AppSettings::get_settings_path()+ _("settings.txt");
	if( wxTheApp->argc>= 2) {
		wxFileName tmpname= wxFileName( wxTheApp->argv[ 1]);
		if( tmpname.IsRelative()) {
			setting_filename= wxGetCwd()+ wxFileName::GetPathSeparator()+ tmpname.GetFullPath();
		}
	}
	if (!wxFile::Exists(setting_filename)) {
		 wxLogError(_T("Unable to find the settings file ")+ setting_filename);
		return;
	}
	wxConfigBase::Set( new wxFileConfig( wxEmptyString, wxEmptyString, setting_filename, setting_filename, wxCONFIG_USE_LOCAL_FILE ));
	for( int i= 0; i< SCOPE_NUM_PANELS; i++)
	{
		m_grid_pen[ i]= NULL;
		m_mid_grid_pen[ i]= NULL;
		m_back_brush[ i]= NULL;
	}
}

AppSettings::~AppSettings(void)
{
	delete wxConfigBase::Set((wxConfigBase *) NULL);

	// Delete channel list
	for( size_t i= 0; i< this->m_board_array.GetCount(); i++)
	{
		delete (GenericBoard*)this->m_board_array[i];
	}
	this->m_board_array.Clear();

	// Close VME handling
	this->EndVME();

	for( int i= 0; i< SCOPE_NUM_PANELS; i++)
	{
		if( this->m_grid_pen[ i]!= NULL)
		{
			delete this->m_grid_pen[ i];
			this->m_grid_pen[ i]= NULL;
		}
		if( this->m_mid_grid_pen[ i]!= NULL)
		{
			delete this->m_mid_grid_pen[ i];
			this->m_mid_grid_pen[ i]= NULL;
		}
		if( this->m_back_brush[ i]!= NULL)
		{	
			delete this->m_back_brush[ i];
			this->m_back_brush[ i]= NULL;
		}
	}
}
/*!
* Load data
*/
bool AppSettings::Load( void)
{
	/*
	Application setting file structure
	[RECORD]
	|
	|- RECORD_FOLDER= ./record/           // The folder where to store record files
	[TRIGGER]
	|
	|- TRIGGER_MSK= 0                     // Bitmask : 0x0001: external 0x0002: Channels 0x0004: autoretrig 
	|- POST_TRIGGER= 0       
	|- TRIGGER_POSITION_KEEP= 0       
	|- SAMPLE_BLOCK_SIZE= 0                    
    |- TRIGGER_EDGE= 0               // 0: No Trigger  1: Rising edge  2: Falling edge
	[MISC]
	|
	|- LINK_TYPE=USB
	|- LINK_NUM=0
	|- NODE_NUM=0
	|- ADDRESS=0x3210								// Hex board base address
	|- STARTED=0									// Get acquisition status upon loading
	|- SHOW_LEFT_PANE= 0							// Get the left pane show status upon loading
	|- SHOW_BOTTOM_PANE= 0							// Get the bottom pane show status upon loading
	|- SHOW_SCOPE_0_PANE= 0							// Get the scope 0 pane show status upon loading
	|- SHOW_SCOPE_1_PANE= 0							// Get the scope 1 pane show status upon loading
	|- SHOW_SCOPE_2_PANE= 0							// Get the scope 2 pane show status upon loading
	|- SHOW_SCOPE_3_PANE= 0							// Get the scope 3 pane show status upon loading
	|- GRID_LINE_COLOR_0= 0xffffff					// RGB grid color for scope 0
	|- GRID_LINE_COLOR_1= 0xffffff					// RGB grid color for scope 1
	|- GRID_LINE_COLOR_2= 0xffffff					// RGB grid color for scope 2
	|- GRID_LINE_COLOR_3= 0xffffff					// RGB grid color for scope 3
	|- GRID_LINE_TYPE_0= 0							// Grid line type for scope 0
	|- GRID_LINE_TYPE_1= 0							// Grid line type for scope 1
	|- GRID_LINE_TYPE_2= 0							// Grid line type for scope 2
	|- GRID_LINE_TYPE_3= 0							// Grid line type for scope 3
	|- GRID_LINE_WIDTH_0= 1							// Grid line width for scope 0
	|- GRID_LINE_WIDTH_1= 1							// Grid line width for scope 1
	|- GRID_LINE_WIDTH_2= 1							// Grid line width for scope 2
	|- GRID_LINE_WIDTH_3= 1							// Grid line width for scope 3
	|- OFFSET_SAMPLE_0= 0							// Horizontal offset (samples) for scope 0
	|- OFFSET_SAMPLE_1= 0							// Horizontal offset (samples) for scope 1
	|- OFFSET_SAMPLE_2= 0							// Horizontal offset (samples) for scope 2
	|- OFFSET_SAMPLE_3= 0							// Horizontal offset (samples) for scope 3
	|- SEC_2_DIV_0= 1000							// Div/ Sec conversion factor ( div_val= SEC_2_DIV* sec_val) for scope 0
	|- SEC_2_DIV_1= 1000							// Div/ Sec conversion factor ( div_val= SEC_2_DIV* sec_val) for scope 1
	|- SEC_2_DIV_2= 1000							// Div/ Sec conversion factor ( div_val= SEC_2_DIV* sec_val) for scope 2
	|- SEC_2_DIV_3= 1000							// Div/ Sec conversion factor ( div_val= SEC_2_DIV* sec_val) for scope 3
	|- BACKGROUND_COLOR_0= 0x000000					// RGB color background color for scope 0
	|- BACKGROUND_COLOR_1= 0x000000					// RGB color background color for scope 1
	|- BACKGROUND_COLOR_2= 0x000000					// RGB color background color for scope 2
	|- BACKGROUND_COLOR_3= 0x000000					// RGB color background color for scope 3
	|- EXT_RATE_MHZ= 100							// external sample rate (MHz)
	|- INT_RATE_MHZ= 10								// internal sample rate (MHz)
	|- USE_EXT_CLOCK= 0								// use external clock
	|- USE_TTL= 0									// use TTL/NIM external signals
	|- MAX_LOG_X= 1000
	|- ACQ_BOARD_NUM= N
	[ACQ_BOARDS]
	|
	|- [0]
	|   |
	|   |- BOARD_TYPE= V1724
	|   |- { OTHER BOARD DATA}
	|   ...
	|- [N- 1]
	|   |
	|   |- BOARD_TYPE= V1724
	|   |- { OTHER BOARD DATA}
	*/
	unsigned int i;
	// Delete previously stored boards
	this->m_board_array.Clear();
	wxConfigBase* config= wxConfigBase::Get( false);
	if( !config)
	{
		wxLogError( _("Cannot get configuration file\n"));
		return false;
	}

	wxMutexLocker lock( this->m_mutex);
	
	//
	// Get Record Folder
	config->Read(  _("/RECORD/RECORD_FOLDER"), &this->m_record_folder, _T("./"));
	// Sanity checks
	if( !wxDir::Exists( this->m_record_folder))
	{
		// Set to current directory
		this->m_record_folder= _T("./");
	}

	//
	// Get Trigger msk
	int trigger_msk= 0;
	config->Read( _("/TRIGGER/TRIGGER_MSK"), &trigger_msk, 0);
	this->m_trigger_msk= (AppSettings::TRIGGER_MSK)trigger_msk;

	//
	// Get Post Trigger
	this->m_post_trigger= 0;
	config->Read( _("/TRIGGER/POST_TRIGGER"), &this->m_post_trigger, 0);

	//
	// Get Keep trigger position flags
	int tmp;
	config->Read( _("/TRIGGER/TRIGGER_POSITION_KEEP"), &tmp, 0);
	this->m_trigger_position_keep= tmp? true: false;


	//
	// Get trigger edge type
	int edge_type;
	config->Read( _("/TRIGGER/TRIGGER_EDGE"), &edge_type, (int)NO_TRIGGER);
	this->m_trigger_edge_type= (TRIGGER_EDGE_TYPE)edge_type;

	//
	// Get the number of sample per channel
	this->m_num_sample= 0;
	config->Read( _("/TRIGGER/NUM_SAMPLE"), &this->m_num_sample, 0);

	//
	// Get the link type
	config->Read( _("/MISC/LINK_TYPE"), &this->m_link_type_string, _("USB"));
	//
	// Get link number
	config->Read( _("/MISC/LINK_NUM"), &this->m_link_num, 0);
	//
	// Get node number
	config->Read( _("/MISC/NODE_NUM"), &this->m_node_num, 0);
	//
	// Get the base address
	wxString base_add_string= _("");
	config->Read( _("/MISC/ADDRESS"), &base_add_string, _("0"));
	unsigned long base_add= 0x3210;
	wxString hex_part;
	if( base_add_string.Upper().StartsWith(_("0X"), &hex_part))
	{
		// Hex format
		if( !hex_part.Trim().ToULong( &base_add, 16))
		{
			base_add= 0x3210;
		}
	}
	else
	{
		// Decimal format
		if( base_add_string.Trim().ToULong( &base_add, 10))
		{
			base_add= 0x3210;
		}
	}
	m_base_address= (int)base_add;

	//
	// Get acquisition status upon loading
	config->Read( _("/MISC/STARTED"), &tmp, 0);
	this->m_started= tmp? true: false;

	//
	// Get show left pane status upon loading
	config->Read( _("/MISC/SHOW_LEFT_PANE"), &tmp, 0);
	this->m_show_left_pane= tmp? true: false;

	//
	// Get show bottom pane status upon loading
	config->Read( _("/MISC/SHOW_BOTTOM_PANE"), &tmp, 0);
	this->m_show_bottom_pane= tmp? true: false;

	//
	// Get Show scope left top pane upon loading
	config->Read( _("/MISC/SHOW_SCOPE_0_PANE"), &tmp, 0);
	this->m_show_scope_left_top_pane= tmp? true: false;

	//
	// Get Show scope right top pane upon loading
	config->Read( _("/MISC/SHOW_SCOPE_1_PANE"), &tmp, 0);
	this->m_show_scope_right_top_pane= tmp? true: false;

	//
	// Get Show scope left bottom pane upon loading
	config->Read( _("/MISC/SHOW_SCOPE_2_PANE"), &tmp, 0);
	this->m_show_scope_left_bottom_pane= tmp? true: false;

	//
	// Get Show scope right bottom pane upon loading
	config->Read( _("/MISC/SHOW_SCOPE_3_PANE"), &tmp, 0);
	this->m_show_scope_right_bottom_pane= tmp? true: false;

	for( int scope_index= 0; scope_index< SCOPE_NUM_PANELS; scope_index++)
	{
		wxString scope_index_string= wxString::Format( _T("_%d"), scope_index);
		//
		// Get grid line color
		wxString grid_line_color_rgb_string= _("");
		config->Read( _("/MISC/GRID_LINE_COLOR")+ scope_index_string, &grid_line_color_rgb_string, _("0xffffff"));
		unsigned long grid_line_color_rgb;
		wxString hex_part;
		if( grid_line_color_rgb_string.Upper().StartsWith(_("0X"), &hex_part))
		{
			// Hex format
			if( !hex_part.Trim().ToULong( &grid_line_color_rgb, 16))
			{
				grid_line_color_rgb= 0x00ffffff;
			}
		}
		else
		{
			// Decimal format
			if( !grid_line_color_rgb_string.Trim().ToULong( &grid_line_color_rgb, 10))
			{
				grid_line_color_rgb= 0x00ffffff;
			}
		}
		this->m_grid_line_color[ scope_index].Set( (grid_line_color_rgb>> 16)& 0xff, (grid_line_color_rgb>> 8)& 0xff, grid_line_color_rgb& 0xff);

		//
		// Get line type
		int grid_line_type;
		config->Read( _("/MISC/GRID_LINE_TYPE")+ scope_index_string, &grid_line_type, 1);
		this->m_grid_line_type[ scope_index]= (GRID_LINE_TYPE)grid_line_type;

		//
		// Get line width
		config->Read( _("/MISC/GRID_LINE_WIDTH")+ scope_index_string, &this->m_grid_line_width[ scope_index], 1);

		//
		// Get horizontal offset (sec)
		config->Read( _("/MISC/OFFSET_SAMPLE")+ scope_index_string, &this->m_offsetSample[ scope_index], 0);

		//
		// Get Div/ Sec conversion factor
		config->Read( _("/MISC/SEC_2_DIV")+ scope_index_string, &this->m_sec_2_div[ scope_index], 1000.0);
		this->SetSec2Div( scope_index, this->m_sec_2_div[ scope_index]);

		//
		// Get background color
		wxString back_color_rgb_string= _("");
		config->Read( _("/MISC/BACKGROUND_COLOR")+ scope_index_string, &back_color_rgb_string, _("0x000000"));
		unsigned long back_color_rgb;
		if( back_color_rgb_string.Upper().StartsWith(_("0X"), &hex_part))
		{
			// Hex format
			if( !hex_part.Trim().ToULong( &back_color_rgb, 16))
			{
				back_color_rgb= 0x00ffffff;
			}
		}
		else
		{
			// Decimal format
			if( !back_color_rgb_string.Trim().ToULong( &back_color_rgb, 10))
			{
				back_color_rgb= 0x00ffffff;
			}
		}
		this->m_background_color[ scope_index].Set( (back_color_rgb>> 16)& 0xff, (back_color_rgb>> 8)& 0xff, back_color_rgb& 0xff);
	}
	//
	// Get external sample rate (MHz)
	config->Read( _("/MISC/EXT_RATE_MHZ"), &this->m_ext_rate_MHz, 10);
	//
	// Get clock type usage (internal or external)
	config->Read( _("/MISC/USE_EXT_CLOCK"), &tmp, 0);
	this->m_use_ext_clock= tmp? true: false;
	
	this->SetClock( this->m_use_ext_clock, this->m_ext_rate_MHz);

	//
	// Get clock type usage (internal or external)
	config->Read( _("/MISC/USE_TTL"), &tmp, 0);
	this->m_use_TTL= tmp? true: false;
	
	//
	// Get maximum logical value X
	config->Read( _("/MISC/MAX_LOG_X"), &this->m_max_log_X, 1024);

	int acq_board_num= 0;
	config->Read( _("/MISC/ACQ_BOARD_NUM"), &acq_board_num, 0);

	//
	// Boards loop
	wxString board_base_string= _("/ACQ_BOARDS/");

	m_board_types.Clear();
	//
	// Boards loop
	for( i= 0; i< (unsigned int)acq_board_num; i++)
	{
		wxString board_string= wxString::Format( _T("%s%i/"), board_base_string.c_str(), i);

		//
		// Get the board type
		wxString board_type= _("");
		config->Read( board_string+ _("BOARD_TYPE"), &board_type, _("V1724"));
		m_board_types.Add(board_type);
	}

	// Simulate a connection to have a board_array defined for compatibility with software previous version
	// board handling
	Connect( true);

	return true;
}

/*!
* Connect to boards
*/
bool AppSettings::Connect( bool simulate)
{	
	if(( this->m_vme_handle== CAEN_VME_INVALID_HANDLE)&& !simulate)
	{
		return false;
	}
	wxConfigBase* config= wxConfigBase::Get( false);
	if( !config)
	{
		wxLogError( _("Cannot get configuration file\n"));
		return false;
	}
	this->m_board_array.Clear();

	//
	// Boards loop
	for( int i= 0; i< (int)m_board_types.Count(); i++)
	{
		wxString board_base_string= _("/ACQ_BOARDS/");
		wxString board_string= wxString::Format( _T("%s%i/"), board_base_string.c_str(), i);

		GenericBoard *board= ( GenericBoard *)0;
		//
		// Get the board type
		wxString board_type= m_board_types[i];
		if( !board_type.Trim().CmpNoCase( _("")))
		{
			// No board specified: detect it from registers
			
			// HACK: the following code assumes a V17XX ADC board type is connected so we loose
			// in generality about board types (i.e. it must be hacked to be able to connect to boards
			// other than V17XX ones.)

			// DbGOnLY
			//int board_id= CVT_V17XX_RCFG_BOARD_ID_V1724;
			//const char *def_board_string= "V1724";
			int board_id= CVT_V17XX_RCFG_BOARD_ID_V1740;
			const char *def_board_string= "V1740";

			if( !simulate)
			{
				// Create a temporary generic board object to get the board type
				cvt_board_data tmp_data;
				memset( &tmp_data, 0, sizeof( tmp_data));
				tmp_data.m_base_address= (UINT16)m_base_address;
				tmp_data.m_vme_handle= this->m_vme_handle;
				// 
				// read the board id
				if( !V17XXBoard::GetBoardId( tmp_data, board_id))
				{
					wxLogError( wxString::Format( _T("Cannot read BOARD INFO : defaulting to '%s'\n"), def_board_string));
					board_id= CVT_V17XX_RCFG_BOARD_ID_V1724;
				}
			}
			switch( board_id)
			{
					// 24 Series
				case CVT_V17XX_RCFG_BOARD_ID_V1724:			//  V1724
				case CVT_V17XX_RCFG_BOARD_ID_VX1724:		// VX1724
					board= new V1724Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME);
					break;
				case CVT_V17XX_RCFG_BOARD_ID_DT5724:		// DT5724
					board= new V1724Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP);
					break;
				case CVT_V17XX_RCFG_BOARD_ID_N6724:			//  N6724
					board= new V1724Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM);
					break;

					// 21 Series
				case CVT_V17XX_RCFG_BOARD_ID_V1721:			//  V1721
				case CVT_V17XX_RCFG_BOARD_ID_VX1721:		// VX1721
					board= new V1721Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME);
					break;
				case CVT_V17XX_RCFG_BOARD_ID_DT5721:		// DT5721
					board= new V1721Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP);
					break;
				case CVT_V17XX_RCFG_BOARD_ID_N6721:			//  N6721
					board= new V1721Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM);
					break;

					// 31 Series
				case CVT_V17XX_RCFG_BOARD_ID_V1731:			//  V1731
				case CVT_V17XX_RCFG_BOARD_ID_VX1731:		// VX1731
					{
						bool des_mode= false;
						if( !simulate)
						{
							if( wxMessageDialog(NULL, _("CAENScope has detected a V1731 adc board.\nDo yuo want to set the DES mode ?"), _("CAENScope"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION).ShowModal()== wxID_YES){
								des_mode= true;
							}
						}
						board= new V1731Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME, des_mode);
					}
					break;
				case CVT_V17XX_RCFG_BOARD_ID_DT5731:		// DT5731
					{
						bool des_mode= false;
						if( !simulate)
						{
							if( wxMessageDialog(NULL, _("CAENScope has detected a DT5731 adc board.\nDo yuo want to set the DES mode ?"), _("CAENScope"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION).ShowModal()== wxID_YES){
								des_mode= true;
							}
						}
						board= new V1731Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP, des_mode);
					}
					break;
				case CVT_V17XX_RCFG_BOARD_ID_N6731:			//  N6731
					{
						bool des_mode= false;
						if( !simulate)
						{
							if( wxMessageDialog(NULL, _("CAENScope has detected a N6731 adc board.\nDo yuo want to set the DES mode ?"), _("CAENScope"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION).ShowModal()== wxID_YES){
								des_mode= true;
							}
						}
						board= new V1731Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM, des_mode);
					}
					break;

					// 20 Series
				case CVT_V17XX_RCFG_BOARD_ID_V1720:			//  V1720
				case CVT_V17XX_RCFG_BOARD_ID_VX1720:		// VX1720
					board= new V1720Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME);
					break;
				case CVT_V17XX_RCFG_BOARD_ID_DT5720:		// DT5720
					board= new V1720Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP);
					break;
				case CVT_V17XX_RCFG_BOARD_ID_N6720:			//  N6720
					board= new V1720Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM);
					break;

					// 40 Series
				case CVT_V17XX_RCFG_BOARD_ID_V1740:			//  V1740
				case CVT_V17XX_RCFG_BOARD_ID_VX1740:		// VX1740
					board= new V1740Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME);
					if( !simulate) 
					{
						(( V1740Board*)board)->m_channel_group= GetChannelGroup( _("V1740"), 8, (( V1740Board*)board)->m_channel_group);
					}
					break;
				case CVT_V17XX_RCFG_BOARD_ID_DT5740:		// DT5740
					board= new V1740Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP);
					if( !simulate) 
					{
						(( V1740Board*)board)->m_channel_group= GetChannelGroup( _("DT5740"), 4, (( V1740Board*)board)->m_channel_group);
					}
					break;
				case CVT_V17XX_RCFG_BOARD_ID_N6740:			//  N6740
					board= new V1740Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM);
					if( !simulate) 
					{
						(( V1740Board*)board)->m_channel_group= GetChannelGroup( _("N6740"), 8, (( V1740Board*)board)->m_channel_group);
					}
					break;

					// 51 Series
				case CVT_V17XX_RCFG_BOARD_ID_V1751:			//  V1751
				case CVT_V17XX_RCFG_BOARD_ID_VX1751:		// VX1751
					{
						bool des_mode= false;
						if( !simulate)
						{
							if( wxMessageDialog(NULL, _("CAENScope has detected a V1751 adc board.\nDo yuo want to set the DES mode ?"), _("CAENScope"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION).ShowModal()== wxID_YES){
								des_mode= true;
							}
						}
						board= new V1751Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME, des_mode);
					}
					break;
				case CVT_V17XX_RCFG_BOARD_ID_DT5751:		// DT5751
					{
						bool des_mode= false;
						if( !simulate)
						{
							if( wxMessageDialog(NULL, _("CAENScope has detected a DT5751 adc board.\nDo yuo want to set the DES mode ?"), _("CAENScope"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION).ShowModal()== wxID_YES){
								des_mode= true;
							}
						}
						board= new V1751Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP, des_mode);
					}
					break;
				case CVT_V17XX_RCFG_BOARD_ID_N6751:			//  N6751
					{
						bool des_mode= false;
						if( !simulate)
						{
							if( wxMessageDialog(NULL, _("CAENScope has detected a V1751 adc board.\nDo yuo want to set the DES mode ?"), _("CAENScope"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION).ShowModal()== wxID_YES){
								des_mode= true;
							}
						}
						board= new V1751Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM, des_mode);
					}
					break;

				default:
					// Unknown board type
					wxLogError( wxString::Format( _T("Unknown board id '0x%08X'\n"), board_id));
					break;
			}
		}
		else
		{
			// A board was specified : create a board of proper type

			// VME
			if( !board_type.Trim().CmpNoCase( _("V1724")))
			{
				// V1724
				board= new V1724Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME);
			}
			else if( !board_type.Trim().CmpNoCase( _("V1721")))
			{
				// V1721
				board= new V1721Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME);
			}
			else if( !board_type.Trim().CmpNoCase( _("V1720")))
			{
				// V1720
				board= new V1720Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME);
			}
			else if( !board_type.Trim().CmpNoCase( _("V1731")))
			{
				// V1731 Not DES mode
				board= new V1731Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME, false);
			}
			else if( !board_type.Trim().CmpNoCase( _("V1731_DES")))
			{ 
				// V1731 DES mode 
				board= new V1731Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME, true);
			}
			else if( !board_type.Trim().CmpNoCase( _("V1740")))
			{
				// V1740
				board= new V1740Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME);
				if( !simulate) 
				{
					(( V1740Board*)board)->m_channel_group= GetChannelGroup( _("V1740"), 8, (( V1740Board*)board)->m_channel_group);
				}
			}

			// DESKTOP
			else if( !board_type.Trim().CmpNoCase( _("DT5724")))
			{
				// V1724
				board= new V1724Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP);
			}
			else if( !board_type.Trim().CmpNoCase( _("DT5721")))
			{
				// V1721
				board= new V1721Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP);
			}
			else if( !board_type.Trim().CmpNoCase( _("DT5720")))
			{
				// V1720
				board= new V1720Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP);
			}
			else if( !board_type.Trim().CmpNoCase( _("DT5731")))
			{
				// V1731 Not DES mode
				board= new V1731Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP, false);
			}
			else if( !board_type.Trim().CmpNoCase( _("DT5731_DES")))
			{ 
				// V1731 DES mode 
				board= new V1731Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP, true);
			}
			else if( !board_type.Trim().CmpNoCase( _("DT5740")))
			{
				// V1740
				board= new V1740Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP);
				if( !simulate) 
				{
					(( V1740Board*)board)->m_channel_group= GetChannelGroup( _("DT5740"), 4, (( V1740Board*)board)->m_channel_group);
				}
			}
			else if( !board_type.Trim().CmpNoCase( _("V1751")))
			{
				// V1751 Not DES mode
				board= new V1751Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME, false);
			}
			else if( !board_type.Trim().CmpNoCase( _("V1751_DES")))
			{ 
				// V1751 DES mode 
				board= new V1751Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_VME, true);
			}
			else if( !board_type.Trim().CmpNoCase( _("DT5751")))
			{
				// V1731 Not DES mode
				board= new V1751Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP, false);
			}
			else if( !board_type.Trim().CmpNoCase( _("DT5751_DES")))
			{ 
				// V1751 DES mode 
				board= new V1751Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_DESKTOP, true);
			}

			// NIM
			else if( !board_type.Trim().CmpNoCase( _("N6724")))
			{
				// V1724
				board= new V1724Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM);
			}
			else if( !board_type.Trim().CmpNoCase( _("N6721")))
			{
				// V1721
				board= new V1721Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM);
			}
			else if( !board_type.Trim().CmpNoCase( _("N6720")))
			{
				// V1720
				board= new V1720Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM);
			}
			else if( !board_type.Trim().CmpNoCase( _("N6731")))
			{
				// V1731 Not DES mode
				board= new V1731Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM, false);
			}
			else if( !board_type.Trim().CmpNoCase( _("N6731_DES")))
			{ 
				// V1731 DES mode 
				board= new V1731Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM, true);
			}
			else if( !board_type.Trim().CmpNoCase( _("N6740")))
			{
				// V1740
				board= new V1740Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM);
				if( !simulate) 
				{
					(( V1740Board*)board)->m_channel_group= GetChannelGroup( _("N6740"), 8, (( V1740Board*)board)->m_channel_group);
				}
			}
			else if( !board_type.Trim().CmpNoCase( _("N6751")))
			{
				// V1751 Not DES mode
				board= new V1751Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM, false);
			}
			else if( !board_type.Trim().CmpNoCase( _("N6751_DES")))
			{ 
				// V1751 DES mode 
				board= new V1751Board( i, this->ScopeRefresh, this->UpdateSamplesReadyLed, &this->m_mutex, this, V17XXBoard::BV_NIM, true);
			}
			else
			{
				// Unknown board type
				wxLogError( wxString::Format( _T("Unknown board type '%s'\n"), board_type.c_str()));
				// return false;
			}
		}
		if( !board)
		{
			continue;
		}
		this->m_board_array.Add( board);
		this->m_int_rate_MHz= board->GetClockMHz();
		this->SetClock( false, 0);

		// Open board handlers
		if( !((GenericBoard*)this->m_board_array[i])->Open( this->m_vme_handle ))
		{
			wxLogError( _("Board open failure\n"));
			//return false;
		}
		// Set base address
		((GenericBoard*)this->m_board_array[i])->SetBaseAddress( (UINT16)m_base_address);
		// Load board section
		if( !((GenericBoard*)this->m_board_array[i])->LoadConfig( config, board_string))
		{
			wxLogError( _("Error loading board settings\n"));
			//return false;
		}
		if( !simulate)
		{
			// Init board section
			if( !((GenericBoard*)this->m_board_array[i])->Init( this->m_vme_handle))
			{
				wxLogError( _("Board init failure\n"));
				//return false;
			}
			// Check if DPP
			if( ((GenericBoard*)this->m_board_array[i])->IsDPP()) 
			{
				wxLogError( _("DPP mode not supported !\nPlease check the board firmware"));
				return false;
			}
		}
	}

	return true;
}
int AppSettings::GetChannelGroup( const wxString &boardLabel, int numGroups, int defGroup) 
{
	wxArrayString choices;
	for( int i= 0; i< numGroups; i++) 
	{
		choices.Add( wxString::Format( _("Group %d"), i));
	}						
	wxSingleChoiceDialog dlg( NULL, wxString::Format( _("CAENScope has detected a %s adc board.\nSelect the channel group."), boardLabel.wx_str()),_("CAENScope"), choices);
	dlg.SetSelection( defGroup);
	dlg.ShowModal();
	return dlg.GetSelection( );
}
/*!
* save data
*/
bool AppSettings::Save( void)
{
	wxConfigBase* config= wxConfigBase::Get( false);
	if( !config)
		return false;
	wxMutexLocker lock( this->m_mutex);

	//
	// Delete groups
	wxString group_id;
	long group_index;
	while( config->GetFirstGroup( group_id, group_index))
	{
		config->DeleteGroup( group_id);
	}
	//
	// Set Record Folder
	if( !config->Write( _("/RECORD/RECORD_FOLDER"), this->m_record_folder))
		return false;

	//
	// Set Trigger msk
	if( !config->Write( _("/TRIGGER/TRIGGER_MSK"), (int)this->m_trigger_msk))
		return false;

	//
	// Set Post Trigger
	if( !config->Write( _("/TRIGGER/POST_TRIGGER"), this->m_post_trigger))
		return false;

	//
	// Set Keep trigger position flags
	config->Write( _("/TRIGGER/TRIGGER_POSITION_KEEP"), this->m_trigger_position_keep? 1: 0);

	//
	// Set trigger edge type
	if( !config->Write( _("/TRIGGER/TRIGGER_EDGE"), (int)this->m_trigger_edge_type))
		return false;

	//
	// Set the number of sample per channel
	if( !config->Write( _("/TRIGGER/NUM_SAMPLE"), this->m_num_sample))
		return false;

	//
	// Set the link type
	if( !config->Write( _("/MISC/LINK_TYPE"), this->m_link_type_string))
		return false;
	//
	// Set the link number 
	if( !config->Write( _("/MISC/LINK_NUM"), this->m_link_num))
		return false;
	//
	// Set the node number
	if( !config->Write( _("/MISC/NODE_NUM"), this->m_node_num))
		return false;
	//
	// Set the board address
	wxString base_add_string= wxString::Format( _T("0x%04x"), m_base_address);
	if( !config->Write( _("/MISC/ADDRESS"), base_add_string))
		return false;

	//
	// Set acquisition status upon loading
	config->Write( _("/MISC/STARTED"), this->m_started? 1: 0);

	//
	// Set show left pane status upon loading
	config->Write( _("/MISC/SHOW_LEFT_PANE"), this->m_show_left_pane? 1: 0);

	//
	// Set show bottom pane status upon loading
	config->Write( _("/MISC/SHOW_BOTTOM_PANE"), this->m_show_bottom_pane? 1: 0);

	//
	// Get Show scope left top pane upon loading
	config->Write( _("/MISC/SHOW_SCOPE_0_PANE"), m_show_scope_left_top_pane? 1: 0);

	//
	// Get Show scope right top pane upon loading
	config->Write( _("/MISC/SHOW_SCOPE_1_PANE"), m_show_scope_right_top_pane? 1: 0);

	//
	// Get Show scope left bottom pane upon loading
	config->Write( _("/MISC/SHOW_SCOPE_2_PANE"), m_show_scope_left_bottom_pane? 1: 0);

	//
	// Get Show scope right bottom pane upon loading
	config->Write( _("/MISC/SHOW_SCOPE_3_PANE"), m_show_scope_right_bottom_pane? 1: 0);

	for( int scope_index= 0; scope_index< SCOPE_NUM_PANELS; scope_index++)
	{
		wxString scope_index_string= wxString::Format( _T("_%d"), scope_index);

		//
		// Set grid line color
		wxString grid_line_color_rgb_string= wxString::Format( _T("0x%02x%02x%02x"), this->m_grid_line_color[ scope_index].Red(), this->m_grid_line_color[ scope_index].Green(), this->m_grid_line_color[ scope_index].Blue());
		if( !config->Write( _("/MISC/GRID_LINE_COLOR")+ scope_index_string, grid_line_color_rgb_string))
			return false;

		//
		// Set line type
		if( !config->Write( _("/MISC/GRID_LINE_TYPE")+ scope_index_string, (int)this->m_grid_line_type[ scope_index]))
			return false;

		//
		// Set line width
		if( !config->Write( _("/MISC/GRID_LINE_WIDTH")+ scope_index_string, this->m_grid_line_width[ scope_index]))
			return false;

		//
		// Set horizontal offset (sec)
		if( !config->Write( _("/MISC/OFFSET_SAMPLE")+ scope_index_string, this->m_offsetSample[ scope_index]))
			return false;
	
		//
		// Set Div/ Sec conversion factor
		if( !config->Write( _("/MISC/SEC_2_DIV")+ scope_index_string, this->m_sec_2_div[ scope_index]))
			return false;

		//
		// Set grid line color
		wxString back_color_rgb_string= wxString::Format( _T("0x%02x%02x%02x"), this->m_background_color[ scope_index].Red(), this->m_background_color[ scope_index].Green(), this->m_background_color[ scope_index].Blue());
		if( !config->Write( _("/MISC/BACKGROUND_COLOR")+ scope_index_string, back_color_rgb_string))
			return false;
	}

	//
	// Set external sample rate (MHz)
	if( !config->Write( _("/MISC/EXT_RATE_MHZ"), this->m_ext_rate_MHz))
		return false;
	//
	// Set clock type usage (internal or external)
	if( !config->Write( _("/MISC/USE_EXT_CLOCK"), this->m_use_ext_clock? 1: 0))
		return false;

	//
	// Set external signals standard: TTL/NIM
	if( !config->Write( _("/MISC/USE_TTL"), this->m_use_TTL? 1: 0))
		return false;

	//
	// Set maximum logical value X
	if( !config->Write( _("/MISC/MAX_LOG_X"), this->m_max_log_X))
		return false;

	//
	// Set board number
	if( !config->Write( _("/MISC/ACQ_BOARD_NUM"), (int)this->m_board_array.GetCount()))
		return false;

	wxString board_base_string= _("/ACQ_BOARDS/");
	//
	// Boards loop
	for( size_t i= 0; i< this->m_board_array.GetCount(); i++)
	{
		wxString board_string= wxString::Format( _T("%s%i/"), board_base_string.c_str(), i);
		//
		// Set the board type
		//if( !config->Write( board_string+ _("BOARD_TYPE"), ((GenericBoard*)this->m_board_array[i])->GetTypeString()))
		//	return false;
		if( !config->Write( board_string+ _("BOARD_TYPE"), this->m_board_types[ i]))
			return false;

		// Save board section
		if( !((GenericBoard*)this->m_board_array[i])->SaveConfig( config, board_string))
			return false;
	}
	if( !config->Flush())
		return false;
	return true;
}
bool AppSettings::InitVME( void)
{
	// Init CAEN VME handle
	if( !this->m_link_type_string.CmpNoCase(_("USB"))||
		!this->m_link_type_string.CmpNoCase(_("V1718")))
	{
		CVErrorCodes cv_error_code;
		if( ( cv_error_code= CAENVME_Init( cvV1718, this->m_link_num, this->m_node_num, &this->m_vme_handle))!= cvSuccess)
		{
			wxLogError( wxString::Format( _("Link init failure: Link type= %s link number= %i node number = %i error= %s"), this->m_link_type_string.c_str(), this->m_link_num, this->m_node_num, CAENVME_DecodeError( cv_error_code) ));
			return false;
		}
	}
	else if( !this->m_link_type_string.CmpNoCase(_("OPTICAL"))||
			 !this->m_link_type_string.CmpNoCase(_("V2718")))
	{
		CVErrorCodes cv_error_code;
		if( ( cv_error_code= CAENVME_Init( cvV2718, this->m_link_num, this->m_node_num, &this->m_vme_handle))!= cvSuccess)
		{
			wxLogError( wxString::Format( _("Link init failure: Link type= %s link number= %i node number = %i error= %s"), this->m_link_type_string.c_str(), this->m_link_num, this->m_node_num, CAENVME_DecodeError( cv_error_code) ));
			return false;
		}
	}
	else
	{
		// Automatically check board type
		CVErrorCodes cv_error_code;
		// try V1718
		if( ( cv_error_code= CAENVME_Init( cvV1718, this->m_link_num, this->m_node_num, &this->m_vme_handle))== cvSuccess)
		{
			return true;
		}
		// try V2718
		if( ( cv_error_code= CAENVME_Init( cvV2718, this->m_link_num, this->m_node_num, &this->m_vme_handle))== cvSuccess)
		{
			return true;
		}
		wxLogError( wxString::Format( _("Cannot find any available link (USB, OPTICAL, V1718 or V2718) on link number '%d' and node number '%d'"), this->m_link_num, this->m_node_num));
		return false;
	}
	return true;
}
bool AppSettings::EndVME( void)
{
	if( this->m_vme_handle== CAEN_VME_INVALID_HANDLE)
	{
		return true;
	}
	CVErrorCodes cv_error_code;
	if( ( cv_error_code= CAENVME_End( this->m_vme_handle))!= cvSuccess)
	{
		wxLogError( wxString::Format( _("Link close failure: Link type= %s link number= %d node number= %d error= %s\n"), this->m_link_type_string.c_str(), this->m_link_num, this->m_node_num, CAENVME_DecodeError( cv_error_code)));
		return false;
	}		
	this->m_vme_handle= CAEN_VME_INVALID_HANDLE;
	return true;
}

bool AppSettings::SetGridPen( int scope_index, const wxPen* grid_pen, const wxPen* mid_grid_pen)
{
	if( this->m_grid_pen[ scope_index]!= NULL)
	{
		delete this->m_grid_pen[ scope_index];
		this->m_grid_pen[ scope_index]= NULL;
	}
	this->m_grid_pen[ scope_index]= ( grid_pen== NULL)? NULL: new wxPen( *grid_pen);

	if( this->m_mid_grid_pen[ scope_index]!= NULL)
	{
		delete this->m_mid_grid_pen[ scope_index];
		this->m_mid_grid_pen[ scope_index]= NULL;
	}
	if( mid_grid_pen== NULL)
	{
		this->m_mid_grid_pen[ scope_index]= ( grid_pen== NULL)? NULL: new wxPen( *grid_pen);
	}
	else
	{
		this->m_mid_grid_pen[ scope_index]= new wxPen( *mid_grid_pen);
	}
	return true;
}

bool AppSettings::SetBackBrush( int scope_index, const wxBrush* back_brush)
{
	if( this->m_back_brush[ scope_index]!= NULL)
	{	
		delete this->m_back_brush[ scope_index];
		this->m_back_brush[ scope_index]= NULL;
	}
	this->m_back_brush[ scope_index]= ( back_brush== NULL)? NULL: new wxBrush( *back_brush);
	return true;
}

void AppSettings::SetDiv2Pix( int scope_index, double div_2_pix_X)
{
	wxMutexLocker lock( this->m_mutex);

	this->m_div_2_pix_X[ scope_index]= div_2_pix_X;
	this->m_sec_2_pix[ scope_index]= this->m_sec_2_div[ scope_index]* this->m_div_2_pix_X[ scope_index];
}

void AppSettings::SetSec2Div( int scope_index, double sec_2_div)
{
	if( sec_2_div< 0.0000000001)
		sec_2_div= 0.0000000001;
	this->m_sec_2_div[ scope_index]= sec_2_div;

	this->m_sec_2_pix[ scope_index]= this->m_sec_2_div[ scope_index]* this->m_div_2_pix_X[ scope_index];
}

void AppSettings::SetSec2Sample( double sec_2_sample)
{
	if( sec_2_sample< 0.0000000001)
		sec_2_sample= 0.0000000001;
	this->m_sec_2_sample= sec_2_sample;

	this->m_sample_2_sec= 1/ this->m_sec_2_sample;
}
void AppSettings::SetClock( bool use_ext_clock, double ext_rate_MHz)
{
	if( ext_rate_MHz< 1)
		ext_rate_MHz= 1;
	else if( ext_rate_MHz> 1000)
		ext_rate_MHz= 1000;
	this->m_ext_rate_MHz= ext_rate_MHz;

	this->m_use_ext_clock= use_ext_clock;

	this->SetSec2Sample( this->m_use_ext_clock? (ext_rate_MHz)* 1000000.0: (this->m_int_rate_MHz)* 1000000.0);
}

const wxString AppSettings::get_settings_path() { // by Giovanni Bianchi: the settings file is written in the default application data dir under Windows to avoid problems with Vista/7's UAC
#ifdef WIN32
	wxStandardPaths std_path;
	return std_path.GetUserDataDir() + wxFileName::GetPathSeparator();
#else
	return _("/etc/CAENScope/");
#endif
}

const wxString AppSettings::get_default_path() {
#ifdef WIN32
	return GetExecutablePath()+ wxFileName::GetPathSeparator();
#else
	return _("/etc/CAENScope/");	
	//wxStandardPaths std_path;
	//		return std_path.GetLocalDataDir()+ wxFileName::GetPathSeparator();
#endif
}

const wxString AppSettings::GetExecutablePath()
{
    static bool found = false;
    static wxString path;

    if (found)
        return path;
    else
    {
#ifdef __WXMSW__

        char buf[512];
        *buf = '\0';
        GetModuleFileName(NULL, buf, 511);
        path = buf;

#elif defined(__WXMAC__)

        ProcessInfoRec processinfo;
        ProcessSerialNumber procno ;
        FSSpec fsSpec;

        procno.highLongOfPSN = NULL ;
        procno.lowLongOfPSN = kCurrentProcess ;
        processinfo.processInfoLength = sizeof(ProcessInfoRec);
        processinfo.processName = NULL;
        processinfo.processAppSpec = &fsSpec;

        GetProcessInformation( &procno , &processinfo ) ;
        path = wxMacFSSpec2MacFilename(&fsSpec);
#else
        wxString argv0 = wxTheApp->argv[0];

        if (wxIsAbsolutePath(argv0))
            path = argv0;
        else
        {
            wxPathList pathlist;
            pathlist.AddEnvList(wxT("PATH"));
            path = pathlist.FindAbsoluteValidPath(argv0);
        }

        wxFileName filename(path);
        filename.Normalize();
        path = filename.GetFullPath();
#endif
        found = true;
		wxFileName fn( path);
		path= fn.GetPath();
        return path;
    }
}
