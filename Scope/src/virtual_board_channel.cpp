/////////////////////////////////////////////////////////////////////////////
// Name:        virtual_board_channel.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     10/01/07 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////

//#define __TEST__

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "virtual_board_channel.h"
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
#include "virtual_board_channel.h"
#include "rpn_handler.h"


extern "C" 
{
	#include "cvt_V1724.h"
}


VirtualBoardChannel::VirtualBoardChannel( GenericBoard* parent, int ch_index, cvt_board_data* p_data, void ( *scope_refresh)( int, bool), wxMutex* p_data_mutex, AppSettings *p_app_settings):
									GenericBoardChannel( parent, ch_index, p_data, scope_refresh, p_data_mutex, p_app_settings)
{
	this->m_p_rpn_handler= NULL;
}

VirtualBoardChannel::~VirtualBoardChannel( void)
{
	if( this->m_p_rpn_handler)
		delete this->m_p_rpn_handler;
}
double VirtualBoardChannel::GetSampleVolt( int i)
{
	// evaluate expression and return the value
	this->m_sample_index= i;
	double result= 0;
	if( !this->m_p_rpn_handler)
		return 0;
	if( !this->m_p_rpn_handler->Eval( result))
		return 0;
	return result;
}
int VirtualBoardChannel::GetSample( int i)
{
	return (int)(double)( this->GetSampleVolt( i)* this->m_volt_2_bit);
}
int VirtualBoardChannel::GetSampleRaw( int i)
{
	return ( GetSample( i)+ 0x8000)>> this->m_sample_shift;
}
wxString VirtualBoardChannel::GetRecordChannelNumber( void)
{
	return wxString::Format( _T("V%02d"), this->m_ch_index);
}
UINT32 VirtualBoardChannel::GetBufferCount( void)
{
	if( !this->m_p_rpn_handler)
		return 0;
	return this->m_p_rpn_handler->GetBufferCount();
}
void VirtualBoardChannel::DrawTrigger( int /*scope_index*/, wxDC &/*dc*/)
{
	// Do nothing
}

bool VirtualBoardChannel::LoadConfig( wxConfigBase* p_config, const wxString& base_section)
{
	GenericBoardChannel::LoadConfig( p_config, base_section);
	/*
		Application setting physical channel parameters' file structure

          |- VIRTUAL_CHANNEL_DEF=CH1,CH2,ADD        // Virtual channel RPN definition
	*/

	//
	// Get RPN definition
	wxString tmp_string= _("");
	p_config->Read( base_section+ _("VIRTUAL_CHANNEL_DEF"), &tmp_string, _(""));
	this->m_p_rpn_handler= new RpnHandler( this, tmp_string.ToAscii());

	return true;

}
bool VirtualBoardChannel::SaveConfig( wxConfigBase* p_config, const wxString& base_section)
{
	if( !GenericBoardChannel::SaveConfig( p_config, base_section))
		return false;

	//
	// Set RPN definition
	if( this->m_p_rpn_handler)
	{
		wxString tmp_string((const wxChar*) this->m_p_rpn_handler->Format());
		if( !p_config->Write( base_section+ _("VIRTUAL_CHANNEL_DEF"), tmp_string))
			return false;
	}
	else
	{
		if( !p_config->Write( base_section+ _("VIRTUAL_CHANNEL_DEF"), ""))
			return false;
	}
	return true;
}
bool VirtualBoardChannel::GetChannelValue( int channel_id, double& result)
{
	return this->m_parent->GetPhysicalChannelValue( channel_id, this->m_sample_index, result);
}
bool VirtualBoardChannel::GetChannelValueVolt( int channel_id, double& result)
{
	return this->m_parent->GetPhysicalChannelValueVolt( channel_id, this->m_sample_index, result);
}
bool VirtualBoardChannel::GetChannelBufferCount( int channel_id, UINT32& result)
{
	return this->m_parent->GetPhysicalChannelBufferCount( channel_id, result);
}
const char* VirtualBoardChannel::GetExpressionDef( void)
{
	if( !this->m_p_rpn_handler)
		return "";
	return this->m_p_rpn_handler->Format();
}
void VirtualBoardChannel::SetExpressionDef( const char* expression_def)
{
	if( !this->m_p_rpn_handler)
	{
		this->m_p_rpn_handler= new RpnHandler( this, expression_def);
		return;
	}
	this->m_p_rpn_handler->Parse( expression_def);
}
