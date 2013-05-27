/////////////////////////////////////////////////////////////////////////////
// Name:        generic_board_channel.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////


#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "generic_board_channel.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <wx/filename.h>


#include "generic_board_channel.h"
#include "common_ch_control_base.h"
#include "record_ch_control.h"
#include "cursor_ch_control.h"
#include "appsettings.h"
#include "drawing_panel.h"
#include "generic_board.h"

GenericBoardChannel::GenericBoardChannel( GenericBoard* parent, int ch_index, cvt_board_data* p_data, void ( *scope_refresh)( int, bool), wxMutex* p_data_mutex, AppSettings *p_app_settings):
		ScopeRefresh( scope_refresh), m_p_data_mutex( p_data_mutex),
		m_p_data( p_data), m_ch_index( ch_index), m_p_app_settings( p_app_settings), m_p_record_file( NULL),
        m_samples_mutex( wxMUTEX_RECURSIVE), m_record_mutex( wxMUTEX_RECURSIVE), m_p_common_ch_control( NULL)
{

	this->m_parent= parent;
	this->m_is_recording= false;

	this->m_medium_value= 0;
	this->m_overload_up= false;
	this->m_overload_down= false;
	for( int i= 0; i< SCOPE_NUM_PANELS; i++)
	{
		this->m_line_pen[ i]= NULL;
		this->m_trigger_pen[ i]= NULL;
		this->m_trigger_brush[ i]= NULL;
		this->m_volt_2_div[ i]= 1.0;

		this->m_offset_y[ i]= 0;
		this->m_volt_2_pix[ i]= 0;
		this->m_div_2_pix_X[ i]= 0;
		this->m_div_2_pix_Y[ i]= 0;
		this->m_pix_Y[ i]= 0;
		this->m_pix_X[ i]= 0;
		this->m_left_div_2_pix_Y[ i]= 0;
		this->m_left_pix_Y[ i]= 0;
		this->m_left_pix_X[ i]= 0;
		for( int cursor_index= 0; cursor_index< SCOPE_NUM_CURSORS; cursor_index++)
		{
			this->m_cursor_position[ i][ cursor_index]= 0;
		}
		this->m_cursor_enabled[ i]= false;
	}
	//
	// Get volt_2_bit
	this->m_volt_2_bit= this->m_parent->GetVolt2Bit();
	if( this->m_volt_2_bit== 0)
		this->m_volt_2_bit= 1.0;
	this->m_bit_2_volt= 1/ this->m_volt_2_bit;

	this->m_sample_shift = 16- this->m_parent->GetSampleBit();
}

GenericBoardChannel::~GenericBoardChannel(void)
{
	for( int i= 0; i< SCOPE_NUM_PANELS; i++)
	{
		if( this->m_line_pen[ i]!= NULL)
		{
			delete this->m_line_pen[ i];
			this->m_line_pen[ i]= NULL;
		}

		if( this->m_trigger_pen[ i]!= NULL)
		{
			delete this->m_trigger_pen[ i];
			this->m_trigger_pen[ i]= NULL;
		}
		if( this->m_trigger_brush[ i]!= NULL)
		{
			delete this->m_trigger_brush[ i];
			this->m_trigger_brush[ i]= NULL;
		}
	}
	if( this->m_p_record_file)
	{
		delete this->m_p_record_file;
		this->m_p_record_file= NULL;
	}
}

bool GenericBoardChannel::LoadConfig( wxConfigBase* p_config, const wxString& base_section)
{
	/*
		Application setting channel parameters' file structure

          |- ENABLED= 1
          |- SCOPE_VIEW_ENABLED_0= 1       // Enable channel view in scope 1
          |- SCOPE_VIEW_ENABLED_1= 1       // Enable channel view in scope 2
          |- SCOPE_VIEW_ENABLED_2= 1       // Enable channel view in scope 3
          |- SCOPE_VIEW_ENABLED_3= 1       // Enable channel view in scope 4
          |- LINE_COLOR_0= 0xaaff00        // RGB color Scope 1
          |- LINE_WIDTH_0= 1               // Pixels Scope 1
          |- OFFSET_VOLT_0= 0.0            // Volts Scope 1
          |- VOLT_2_DIV_0= 4               // Div/ Volts conversion factor ( div_val= VOLT_2_DIV* volt_val) Scope 1
          |- LINE_COLOR_1= 0xaaff00        // RGB color Scope 2
          |- LINE_WIDTH_1= 1               // Pixels Scope 2
          |- OFFSET_VOLT_1= 0.0            // Volts Scope 2
          |- VOLT_2_DIV_1= 4               // Div/ Volts conversion factor ( div_val= VOLT_2_DIV* volt_val) Scope 2
          |- LINE_COLOR_2= 0xaaff00        // RGB color Scope 3
          |- LINE_WIDTH_2= 1               // Pixels Scope 3
          |- OFFSET_VOLT_2= 0.0            // Volts Scope 3
          |- VOLT_2_DIV_2= 4               // Div/ Volts conversion factor ( div_val= VOLT_2_DIV* volt_val) Scope 3
          |- LINE_COLOR_3= 0xaaff00        // RGB color Scope 4
          |- LINE_WIDTH_3= 1               // Pixels Scope 4
          |- OFFSET_VOLT_3= 0.0            // Volts Scope 4
          |- VOLT_2_DIV_3= 4               // Div/ Volts conversion factor ( div_val= VOLT_2_DIV* volt_val) Scope 4
          |- RECORD_RATE_DIVIDER= 1        // Samples' recording rate divider
          |- RECORD_ENABLED= 1             // Samples' recording enabled
          |- RECORD_FORMAT= 0              // Record save format 0: hex 1: ASCII decimal 2: ASCII hexdecimal
	*/

	//
	// Get channel enable bit
	this->m_enabled= FALSE;
	p_config->Read( base_section+ _("ENABLED"), &this->m_enabled, 0);
	// Check if channel supported by the board
	if( m_enabled) {
		m_enabled= ( m_parent->GetChEnableMsk()& ( 1<< m_ch_index))!= 0; 
	}
	//
	// Get Enable channel view in scope #
	for( int scope_index= 0; scope_index< SCOPE_NUM_PANELS; scope_index++)
	{
		wxString scope_index_string= wxString::Format( _T("_%d"), scope_index);

		this->m_scope_view_enabled[ scope_index]= FALSE;
		p_config->Read( base_section+ _("SCOPE_VIEW_ENABLED")+ scope_index_string, &this->m_scope_view_enabled[ scope_index], 0);
	}

	for( int scope_index= 0; scope_index< SCOPE_NUM_PANELS; scope_index++)
	{
		wxString scope_index_string= wxString::Format( _T("_%d"), scope_index);
		//
		// Get line color
		wxString line_color_rgb_string= _("");
		p_config->Read( base_section+ _("LINE_COLOR")+ scope_index_string , &line_color_rgb_string, _("0xffffff"));
		unsigned long line_color_rgb;
		wxString hex_part;
		if( line_color_rgb_string.Upper().StartsWith(_("0X"), &hex_part))
		{
			// Hex format
			if( !hex_part.Trim().ToULong( &line_color_rgb, 16))
			{
				line_color_rgb= 0x00ffffff;
			}
		}
		else
		{
			// Decimal format
			if( !line_color_rgb_string.Trim().ToULong( &line_color_rgb, 10))
			{
				line_color_rgb= 0x00ffffff;
			}
		}
		this->m_line_color[ scope_index].Set( (line_color_rgb>> 16)& 0xff, (line_color_rgb>> 8)& 0xff, line_color_rgb& 0xff);
		//
		// Get line width
		this->m_line_width[ scope_index]= 1;
		p_config->Read( base_section+ _("LINE_WIDTH")+ scope_index_string , &this->m_line_width[ scope_index], 1);
		//
		// Get offset_volt
		this->m_offset_y[ scope_index]= 0;
		p_config->Read( base_section+ _("OFFSET_Y")+ scope_index_string , &this->m_offset_y[ scope_index], 0.0);
		//
		// Get div_2_volt
		double value= 1.0;
		p_config->Read( base_section+ _("VOLT_2_DIV")+ scope_index_string , &value, 4.0);
		this->SetVolt2Div( scope_index, value);
	}

	//
	// Get record rate divider
	this->m_record_rate_divider= 1;
	p_config->Read( base_section+ _("RECORD_RATE_DIVIDER"), &this->m_record_rate_divider, 1);
	if( this->m_record_rate_divider<= 0)
	{
		this->m_record_rate_divider= 1;
	}
	//
	// Get record enable bit
	int dummy= 0;
	p_config->Read( base_section+ _("RECORD_ENABLED"), &dummy, 0);
	this->m_record_enabled= dummy!= 0;

	//
	// Get record format type
	int record_format_type;
	p_config->Read( base_section+ _("RECORD_FORMAT"), &record_format_type, (int)GenericBoardChannel::HEX);
	this->m_record_format_type= (GenericBoardChannel::RECORD_FORMAT_TYPE)record_format_type;

	return true;

}
bool GenericBoardChannel::SaveConfig( wxConfigBase* p_config, const wxString& base_section)
{

	//
	// Set channel enable bit
	if( !p_config->Write( base_section+ _("ENABLED"), this->m_enabled? 1: 0))
		return false;

	//
	// Set Enable channel view in scope #
	for( int scope_index= 0; scope_index< SCOPE_NUM_PANELS; scope_index++)
	{
		wxString scope_index_string= wxString::Format( _T("_%d"), scope_index);

		if( !p_config->Write( base_section+ _("SCOPE_VIEW_ENABLED")+ scope_index_string, this->m_scope_view_enabled[ scope_index]? 1: 0))
			return false;
	}

	for( int scope_index= 0; scope_index< SCOPE_NUM_PANELS; scope_index++)
	{
		wxString scope_index_string= wxString::Format( _T("_%d"), scope_index);
		//
		// Set line color
		wxString line_color_rgb_string= wxString::Format( _T("0x%02x%02x%02x"), this->m_line_color[ scope_index].Red(), this->m_line_color[ scope_index].Green(), this->m_line_color[ scope_index].Blue());
		if( !p_config->Write( base_section+ _("LINE_COLOR")+ scope_index_string, line_color_rgb_string))
			return false;
		//
		// Set line width
		if( !p_config->Write( base_section+ _("LINE_WIDTH")+ scope_index_string, this->m_line_width[ scope_index]))
			return false;
		//
		// Set offset_volt
		if( !p_config->Write( base_section+ _("OFFSET_Y")+ scope_index_string, this->m_offset_y[ scope_index]))
			return false;
		//
		// Set volt_2_div
		if( !p_config->Write( base_section+ _("VOLT_2_DIV")+ scope_index_string, this->m_volt_2_div[ scope_index]))
			return false;
	}

	//
	// Set record rate divider
	if( this->m_record_rate_divider<= 0)
	{
		this->m_record_rate_divider= 1;
	}
	if( !p_config->Write( base_section+ _("RECORD_RATE_DIVIDER"), this->m_record_rate_divider))
		return false;
	//
	// Set record enable bit
	if( !p_config->Write( base_section+ _("RECORD_ENABLED"), this->m_record_enabled? 1: 0))
		return false;

	//
	// Set record format type
	if( !p_config->Write( base_section+ _("RECORD_FORMAT"), (int)this->m_record_format_type))
		return false;

	return true;
}

bool GenericBoardChannel::SetLinePen( int scope_index, const wxPen* line_pen, const wxPen* trigger_pen)
{
	if( this->m_line_pen[ scope_index]!= NULL)
	{
		delete this->m_line_pen[ scope_index];
		this->m_line_pen[ scope_index]= NULL;
	}
	this->m_line_pen[ scope_index]= ( line_pen== NULL)? NULL: new wxPen( *line_pen);

	if( this->m_trigger_pen[ scope_index]!= NULL)
	{
		delete this->m_trigger_pen[ scope_index];
		this->m_trigger_pen[ scope_index]= NULL;
	}
	if( this->m_trigger_brush[ scope_index]!= NULL)
	{
		delete this->m_trigger_brush[ scope_index];
		this->m_trigger_brush[ scope_index]= NULL;
	}
	if( trigger_pen== NULL)
	{
		this->m_trigger_pen[ scope_index]= ( line_pen== NULL)? NULL: new wxPen( *line_pen);
		this->m_trigger_brush[ scope_index]= new wxBrush( line_pen->GetColour());
	}
	else
	{
		this->m_trigger_pen[ scope_index]= new wxPen( *trigger_pen);
		this->m_trigger_brush[ scope_index]= new wxBrush( line_pen->GetColour());
	}

	if( this->ScopeRefresh!= NULL)
		(this->ScopeRefresh)( scope_index, false);
	return true;
}
void GenericBoardChannel::DrawPosition( int scope_index, wxDC &dc)
{
	wxMutexLocker lock( this->m_p_app_settings->m_mutex);

	const int MARKER_SIZE_PIX_Y= 2;
	const int CANVAS_SIZE_PIX_X= 17;
	const int MARKER_ARROW_PIX_X= 5;
	
	static wxPoint marker[ ] =
	{
		wxPoint( 2, -MARKER_SIZE_PIX_Y),
		wxPoint( CANVAS_SIZE_PIX_X- MARKER_ARROW_PIX_X, -MARKER_SIZE_PIX_Y),
		wxPoint( CANVAS_SIZE_PIX_X, 0),
		wxPoint( CANVAS_SIZE_PIX_X- MARKER_ARROW_PIX_X, +MARKER_SIZE_PIX_Y),
		wxPoint( 2, +MARKER_SIZE_PIX_Y),
	};
	const int marker_points= sizeof( marker)/ sizeof( marker[0]);

	if( !( this->m_enabled&& this->m_scope_view_enabled[ scope_index])|| 
		( this->m_trigger_pen== NULL)||
		( this->m_trigger_brush== NULL))
		return;
	double offset_y= this->m_left_div_2_pix_Y[ scope_index]*( (double)( DrawingCanvas::NUM_DIV_PER_SCREEN>> 1)+ this->m_offset_y[ scope_index] );

	if( this->m_trigger_brush[ scope_index])
		dc.SetBrush( *this->m_trigger_brush[ scope_index]);
	if( this->m_trigger_pen[ scope_index])
		dc.SetPen( *this->m_trigger_pen[ scope_index]);
	dc.DrawPolygon( marker_points, marker, 0, (int)(double)( this->m_left_pix_Y[ scope_index]- offset_y), wxODDEVEN_RULE);
	dc.SetPen( wxNullPen);
	dc.SetBrush( wxNullBrush);
}

void GenericBoardChannel::DrawCursor( int scope_index, wxDC &dc)
{
	wxMutexLocker lock( this->m_p_app_settings->m_mutex);
	if( !( this->m_enabled&& this->m_scope_view_enabled[ scope_index])|| 
		!m_cursor_enabled[ scope_index]||
		( this->m_trigger_pen[ scope_index]== NULL))
		return;
	if( this->m_trigger_pen[ scope_index])
	{
		dc.SetPen( *this->m_trigger_pen[ scope_index]);
	}

	for( int cursor_index= 0; cursor_index< SCOPE_NUM_CURSORS; cursor_index++)
	{
		// TODO MOD 
		int offset_x= this->Sec2Pix( scope_index, this->Sample2Sec( this->m_p_app_settings->m_offsetSample[ scope_index]+ this->m_cursor_position[ scope_index][cursor_index]));
		dc.DrawLine( offset_x, 0, offset_x, this->m_pix_Y[ scope_index]);
	}	
	// Restore original pen
	dc.SetPen( wxNullPen);
}

void GenericBoardChannel::DrawSamples( int scope_index, wxDC &dc)
{
	#define OVERLOAD_UP		(0x7fc0)
	#define OVERLOAD_DW		(-0x7fc0)
	wxMutexLocker lock( this->m_p_app_settings->m_mutex);
#ifdef SAMPLE_LOCK
	wxMutexLocker sample_lock( this->m_samples_mutex);
#endif
	if( !( this->m_enabled&& this->m_scope_view_enabled[ scope_index]))
		return;
	UINT32 buffer_count= this->GetBufferCount();
	if( !buffer_count)
		return;

	double cursor_value[ SCOPE_NUM_CURSORS];
	int sample_bit;
	int cursor_pos_x[ SCOPE_NUM_CURSORS];
	memcpy( cursor_pos_x, m_cursor_position[scope_index], sizeof( cursor_pos_x[0])*SCOPE_NUM_CURSORS);

	if( this->m_line_pen[ scope_index])
		dc.SetPen( *this->m_line_pen[ scope_index]);
	double offset_x= this->m_p_app_settings->m_offsetSample[ scope_index];

	//double offset_y= this->m_offset_volt;
	double offset_y= this->m_div_2_pix_Y[ scope_index]*( (double)(int)( DrawingCanvas::NUM_DIV_PER_SCREEN>> 1)+ this->m_offset_y[ scope_index]);

	int x0, y0, x1, y1;
	int i= this->Sec2Sample( this->Pix2Sec( scope_index, 0))- offset_x;
	if( i< 0)
	{
		i= 0;
	}
	else if(( (UINT32)i>= buffer_count)&& ( i>= this->m_p_app_settings->m_max_log_X))
	{
		i= ( (int)buffer_count> this->m_p_app_settings->m_max_log_X)? this->m_p_app_settings->m_max_log_X: buffer_count;
	}
	double sample_volt= this->GetSampleVolt( i);
	sample_bit= this->GetSample(i);
	x0= Sec2Pix( scope_index, this->Sample2Sec( offset_x+ i));
	//y0= this->PixY2Dc( this->Volt2Pix( offset_y+ sample_volt));
	y0= this->PixY2Dc( scope_index, (int)(double)( offset_y+ (double)this->Volt2Pix( scope_index, sample_volt)));
	bool overload_down= false;
	bool overload_up= false;
    int medium_value_count= 1;
	this->m_medium_value= sample_volt;
	if( sample_bit>= OVERLOAD_UP)
	{
		overload_up= true;
	}
	else if( sample_bit<= OVERLOAD_DW)
	{
		overload_down= true;
	}
	if( this->m_cursor_enabled[ scope_index])
	{
		for( int cursor_index= 0; cursor_index< SCOPE_NUM_CURSORS; cursor_index++)
		{
			if( cursor_pos_x[scope_index]== 0)
			{
				cursor_value[cursor_index]= sample_volt* 1000;
			}
			else
			{
				cursor_value[cursor_index]= 0;
			}
		}
	}
	int step= this->Sec2Sample( this->Pix2Sec( scope_index, 1));
	if( step== 0)
		step= 1;
	i+= step;
	for( ; ( (UINT32)i< buffer_count)&& ( i< this->m_p_app_settings->m_max_log_X); i+= step)
	{
		sample_volt= this->GetSampleVolt( i);
		sample_bit= this->GetSample(i);
		if( sample_bit>= OVERLOAD_UP)
		{
			overload_up= true;
		}
		else if( sample_bit<= OVERLOAD_DW)
		{
			overload_down= true;
		}
		this->m_medium_value+= sample_volt;
        ++medium_value_count;
		x1= this->Sec2Pix( scope_index, this->Sample2Sec( offset_x+ i));
		y1= this->PixY2Dc( scope_index, (int)(double)(offset_y+ (double)this->Volt2Pix( scope_index, sample_volt)));

		if( this->m_cursor_enabled[ scope_index])
		{
			for( int cursor_index= 0; cursor_index< SCOPE_NUM_CURSORS; cursor_index++)
			{
				if(( cursor_pos_x[cursor_index]>= i)&&
					( cursor_pos_x[cursor_index]< i+ step))
				{
					cursor_value[cursor_index]= sample_volt* 1000;
				}
			}
		}
		if( x0== x1)
			continue;
		if( x0> this->m_pix_X[ scope_index]+ 10)
			break;
		if( x1>= -10)
			dc.DrawLine( x0, y0, x1, y1);
		x0= x1;
		y0= y1;
	}
	dc.SetPen( wxNullPen);
	this->m_medium_value/= medium_value_count;

	// Update controls here
	this->m_p_common_ch_control->SetMediumLabel( this->m_medium_value* 1000);
	if( ( overload_down^ this->m_overload_down) || ( overload_up^ this->m_overload_up))
	{
		this->m_p_common_ch_control->SetOverloadBackground( ( overload_down|| overload_up)? wxColour(255, 0, 0): wxColour(0, 255, 0));
		this->m_overload_down= overload_down;
		this->m_overload_up= overload_up;
	}

	if( this->m_cursor_enabled[ scope_index])
	{
		// Lock and check again
		wxMutexLocker lock( this->m_p_app_settings->m_mutex);
		if( this->m_cursor_enabled[ scope_index])
		{
			this->m_p_cursor_ch_control[ scope_index]->SetCursorValues( cursor_value);
		}
	}
}
void GenericBoardChannel::SetVolt2Div( int scope_index, double volt_2_div)
{
	if( volt_2_div< 0.0000001)
		volt_2_div= 0.0000001;
	this->m_volt_2_div[ scope_index]= volt_2_div;
	//this->m_div_2_volt= 1/ volt_2_div;

	this->m_volt_2_pix[ scope_index]= this->m_volt_2_div[ scope_index]* this->m_div_2_pix_Y[ scope_index];
}
int GenericBoardChannel::Sec2Pix( int scope_index, double value)
{ 
	return (int)(double)( this->m_p_app_settings->m_sec_2_pix[ scope_index]* value);
}
double GenericBoardChannel::Sample2Sec( int value)
{ 
	return this->m_p_app_settings->m_sample_2_sec* (double)value;
}
double GenericBoardChannel::Pix2Sec( int scope_index, int value)
{ 
	return (double)( value)/ this->m_p_app_settings->m_sec_2_pix[ scope_index];
}
int GenericBoardChannel::Sec2Sample( double value)
{ 
	return (int)(double)( (double)value/ this->m_p_app_settings->m_sample_2_sec);
}
void GenericBoardChannel::SetDiv2Pix( int scope_index, double div_2_pix_Y)
{
	wxMutexLocker lock( this->m_p_app_settings->m_mutex);

	this->m_div_2_pix_Y[ scope_index]= div_2_pix_Y;
	this->m_volt_2_pix[ scope_index]= this->m_volt_2_div[ scope_index]* this->m_div_2_pix_Y[ scope_index];	
}
void GenericBoardChannel::SetLeftDiv2Pix( int scope_index, double div_2_pix_Y)
{
	wxMutexLocker lock( this->m_p_app_settings->m_mutex);

	this->m_left_div_2_pix_Y[ scope_index]= div_2_pix_Y;
	//this->m_volt_2_pix= this->m_volt_2_div* this->m_div_2_pix_Y;	
}
wxString GenericBoardChannel::GetRecordChannelNumber( void)
{
	return wxString::Format( _T("C%02d"), this->m_ch_index);
}
bool GenericBoardChannel::ToggleRecordStatus( const wxString &path, const wxString &file_name, const wxString &timestamp, bool start)
{
	wxMutexLocker lock( this->m_record_mutex);
	if( start)
	{
		// Start recording request
		if( this->m_is_recording)
			// Already recording
			return true;
		if( !this->m_record_enabled)
			return true;
		// Create recording file
		if( this->m_p_record_file)
		{
			delete this->m_p_record_file;
			this->m_p_record_file= NULL;
		}
		wxString file_ext= _("hex");
		switch( this->m_record_format_type)
		{
		case ASCII_DEC:
			file_ext= _("adc");
			break;
		case ASCII_HEX:
			file_ext= _("ahx");
			break;
		case HEX:
		default:
			this->m_record_format_type= HEX;
			file_ext= _("bhx");
			break;
		}
		this->m_record_sample_counter= 0;
		// Append channel id & timestamp
		wxString new_file_name( wxString::Format( wxT("%s%s_%s"), (const wxChar *)file_name.c_str(), (const wxChar *)this->GetRecordChannelNumber( ), (const wxChar *)timestamp.c_str()));
		wxFileName filename( path, new_file_name, file_ext);
		filename.Normalize();
		this->m_p_record_file= new wxFile( filename.GetFullPath(), wxFile::write_append);
		if( !this->m_p_record_file->IsOpened())
		{
			delete this->m_p_record_file;
			this->m_p_record_file= NULL;
			return false;
		}
	}
	else
	{
		// Stop recording request
		if( !this->m_is_recording)
			// Nothing to do
			return true;

		// Close recording buffer
		if( this->m_p_record_file)
		{
			this->m_p_record_file->Close();
			delete this->m_p_record_file;
			this->m_p_record_file= NULL;
		}
	}
	this->m_is_recording= start;
	return true;
}
bool GenericBoardChannel::RecordSamples( void)
{
	wxMutexLocker lock( this->m_record_mutex);
	if( !this->m_record_enabled)
		return true;
	if( !this->m_p_record_file)
		return false;

	// Do Save to file ...
	switch( this->m_record_format_type)
	{
	case ASCII_DEC:
		{
			// Text dec format
			wxString line;
			for( UINT32 i= 0; i< this->GetBufferCount(); i++)
			{
				if( !this->m_record_sample_counter)
				{
					// record converted data
					line= wxString::Format( _T("%d\r\n"), this->GetSampleRaw( i));
					this->m_p_record_file->Write( line);
				}
				if( ++this->m_record_sample_counter>= (UINT32)this->m_record_rate_divider)
				{
					this->m_record_sample_counter= 0;
				}
			}
		}
		break;
	case ASCII_HEX:
		{
			// Text hex format
			wxString line;
			for( UINT32 i= 0; i< this->GetBufferCount(); i++)
			{
				if( !this->m_record_sample_counter)
				{
					// record raw data
					line= wxString::Format( _T("%08X\r\n"), this->GetSampleRaw( i));
					this->m_p_record_file->Write( line);
				}
				if( ++this->m_record_sample_counter>= (UINT32)this->m_record_rate_divider)
				{
					this->m_record_sample_counter= 0;
				}
			}
		}
		break;
	case HEX:
	default:
		{
			// Binary hex format
			INT32 sample;
			for( UINT32 i= 0; i< this->GetBufferCount(); i++)
			{
				if( !this->m_record_sample_counter)
				{
					// record raw data
					sample= this->GetSampleRaw( i);
					this->m_p_record_file->Write( &sample, sizeof( sample));
				}
				if( ++this->m_record_sample_counter>= (UINT32)this->m_record_rate_divider)
				{
					this->m_record_sample_counter= 0;
				}
			}
		}
		break;
	}
	return true;
}
void GenericBoardChannel::SetEnable( bool enable, bool disable_all)
{
	if( this->m_p_common_ch_control)
		this->m_p_common_ch_control->SetEnable( enable, disable_all);
}
