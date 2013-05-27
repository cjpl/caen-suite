/////////////////////////////////////////////////////////////////////////////
// Name:        physical_board_channel.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     10/01/07 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////


#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "physical_board_channel.h"
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


#include "physical_board_channel.h"
#include "appsettings.h"
#include "drawing_panel.h"

PhysicalBoardChannel::PhysicalBoardChannel( GenericBoard* parent, int ch_index, cvt_board_data* p_data, void ( *scope_refresh)( int, bool), wxMutex* p_data_mutex, AppSettings *p_app_settings):
		GenericBoardChannel( parent, ch_index, p_data, scope_refresh, p_data_mutex, p_app_settings)
{
	this->m_sample_buffer_size= 2* 1024* 1024;
	this->m_p_sample_buffer= new UINT16[ this->m_sample_buffer_size];
	this->m_sample_buffer_count= 0;

	this->m_tmp_sample_buffer_size= 2* 1024* 1024;
	this->m_p_tmp_sample_buffer= new UINT16[ this->m_tmp_sample_buffer_size];
	this->m_tmp_sample_buffer_count= 0;

}

PhysicalBoardChannel::~PhysicalBoardChannel(void)
{
	if( this->m_p_sample_buffer)
	{
		delete this->m_p_sample_buffer;
		this->m_p_sample_buffer= NULL;
		this->m_sample_buffer_count= 0;
	}
	if( this->m_p_tmp_sample_buffer)
	{
		delete this->m_p_tmp_sample_buffer;
		this->m_p_tmp_sample_buffer= NULL;
		this->m_tmp_sample_buffer_count= 0;
	}
}

bool PhysicalBoardChannel::LoadConfig( wxConfigBase* p_config, const wxString& base_section)
{
	GenericBoardChannel::LoadConfig( p_config, base_section);
	/*
		Application setting physical channel parameters' file structure

          |- DAC_VOLT_2_BIT=26214.4        // DAC Bits/ Volt conversion factor ( bit_val= DAC_VOLT_2_BIT* volt_val) (2^16/2.500)
          |- DAC_OFFSET_BIT=0              // DAC Offset Bit
          |- TRIGGER_ENABLED= 1            // Trigger enabled
          |- TRIGGER_THRESHOLD_VOLT= 1.25  // Trigger Threshold (Volts)
          |- TRIGGER_THR_SAMPLE= 100       // Number of samples after trigger threshold
	*/

	//
	// Get DAC offset volt
	this->m_DAC_offset_bit= 0x8000;
	p_config->Read( base_section+ _("DAC_OFFSET_BIT"), &this->m_DAC_offset_bit, 0x8000);

	//
	// Get DAC bit 2 volt
	this->m_DAC_volt_2_bit= 26214.4;
	p_config->Read( base_section+ _("DAC_VOLT_2_BIT"), &this->m_DAC_volt_2_bit, 26214.4);

	//
	// Get trigger enable bit
	int dummy= 1;
	p_config->Read( base_section+ _("TRIGGER_ENABLED"), &dummy, 1);
	this->m_trigger_enabled= dummy!= 0;

	//
	// Get trigger threshold
	this->m_trigger_threshold_volt= 0;
	p_config->Read( base_section+ _("TRIGGER_THRESHOLD_VOLT"), &this->m_trigger_threshold_volt, 0.0);

	//
	// Get trigger threshold samples
	this->m_trigger_thr_sample= 0;
	p_config->Read( base_section+ _("TRIGGER_THR_SAMPLE"), &this->m_trigger_thr_sample, 0);

	return true;

}
bool PhysicalBoardChannel::SaveConfig( wxConfigBase* p_config, const wxString& base_section)
{
	if( !GenericBoardChannel::SaveConfig( p_config, base_section))
		return false;

	//
	// Set DAC offset volt
	if( !p_config->Write( base_section+ _("DAC_OFFSET_BIT"), this->m_DAC_offset_bit))
		return false;

	//
	// Set DAC bit 2 volt
	if( !p_config->Write( base_section+ _("DAC_VOLT_2_BIT"), this->m_DAC_volt_2_bit))
		return false;

	//
	// Set record enable bit
	if( !p_config->Write( base_section+ _("TRIGGER_ENABLED"), this->m_trigger_enabled? 1: 0))
		return false;

	//
	// Set trigger threshold
	if( !p_config->Write( base_section+ _("TRIGGER_THRESHOLD_VOLT"), this->m_trigger_threshold_volt))
		return false;
	//
	// Set trigger threshold samples
	if( !p_config->Write( base_section+ _("TRIGGER_THR_SAMPLE"), this->m_trigger_thr_sample))
		return false;

	return true;
}
void PhysicalBoardChannel::DrawTrigger( int scope_index, wxDC &dc)
{
	wxMutexLocker lock( this->m_p_app_settings->m_mutex);

	const int TRIGGER_SIZE_PIX_X= 5;
	const int TRIGGER_SIZE_PIX_Y= 3;
	static wxPoint rising_trigger[ ] =
	{
		wxPoint( -TRIGGER_SIZE_PIX_X, +TRIGGER_SIZE_PIX_Y),
		wxPoint( 0, +TRIGGER_SIZE_PIX_Y),
		wxPoint( 0, -TRIGGER_SIZE_PIX_Y),
		wxPoint( +TRIGGER_SIZE_PIX_X, -TRIGGER_SIZE_PIX_Y)
	};
	static wxPoint falling_trigger[ ] =
	{
		wxPoint( -TRIGGER_SIZE_PIX_X, -TRIGGER_SIZE_PIX_Y),
		wxPoint( 0, -TRIGGER_SIZE_PIX_Y),
		wxPoint( 0, +TRIGGER_SIZE_PIX_Y),
		wxPoint( +TRIGGER_SIZE_PIX_X, +TRIGGER_SIZE_PIX_Y)
	};

	if( !( this->m_enabled&& this->m_scope_view_enabled[ scope_index])|| 
		( this->m_trigger_pen[ scope_index]== NULL))
		return;

	if( this->m_trigger_pen[ scope_index])
		dc.SetPen( *this->m_trigger_pen[ scope_index]);

	double offset_x= this->Sample2Sec( this->m_p_app_settings->m_max_log_X- ( this->m_p_app_settings->m_post_trigger+ this->m_trigger_thr_sample)+ this->m_p_app_settings->m_offsetSample[ scope_index]);

	//double offset_y= this->m_offset_volt/*+ this->m_trigger_threshold*/;
	double offset_y= this->m_div_2_pix_Y[ scope_index]*( (double)( DrawingCanvas::NUM_DIV_PER_SCREEN>> 1)+ this->m_offset_y[ scope_index]);
	switch( this->m_p_app_settings->m_trigger_edge_type)
	{
	case AppSettings::FALLING_EDGE:
		//dc.DrawLines( 4, falling_trigger, this->Sec2Pix( offset_x), this->PixY2Dc( this->Volt2Pix( offset_y)));
		dc.DrawLines( 4, falling_trigger, this->Sec2Pix( scope_index, offset_x), this->PixY2Dc( scope_index, (int)offset_y));
		break;
	case AppSettings::RISING_EDGE:
		//dc.DrawLines( 4, rising_trigger, this->Sec2Pix( offset_x), this->PixY2Dc( this->Volt2Pix( offset_y)));
		dc.DrawLines( 4, rising_trigger, this->Sec2Pix( scope_index, offset_x), this->PixY2Dc( scope_index, (int)offset_y));
		break;
	default:
		break;
	}
	dc.SetPen( wxNullPen);
}
