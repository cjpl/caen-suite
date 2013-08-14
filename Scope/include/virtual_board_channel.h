/////////////////////////////////////////////////////////////////////////////
// Name:        virtual_board_channel.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     10/01/07 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _VIRTUAL_BOARD_CHANNEL_H_
#define _VIRTUAL_BOARD_CHANNEL_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "virtual_board_channel.h"
#endif

/*!
 * Includes
 */
#include "generic_board_channel.h"

class RpnHandler;
class AppSettings;

class VirtualBoardChannel: public GenericBoardChannel
{
public:
	VirtualBoardChannel( GenericBoard* parent, int ch_index, cvt_board_data* p_data, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex, AppSettings* p_app_settings);
	~VirtualBoardChannel(void);
	//
	// Properties

	//
	// Methods

	// Pure virtual implementation
	virtual inline int GetSample( int i);
	virtual inline int GetSampleRaw( int i);
	virtual inline double GetSampleVolt( int i);
	
	virtual inline UINT32 GetBufferCount( void);
	virtual void DrawTrigger( int scope_index, wxDC &dc);

	// Virtual override
	bool LoadConfig( wxConfigBase* p_config, const wxString& base_section);
	bool SaveConfig( wxConfigBase* p_config, const wxString& base_section);
	wxString GetRecordChannelNumber( void);

	const char* GetExpressionDef( void);
	void SetExpressionDef( const char* expression_def);

protected:

	RpnHandler *m_p_rpn_handler;
	bool GetChannelValue( int channel_id, double& result);
	bool GetChannelValueVolt( int channel_id, double& result);
	bool GetChannelBufferCount( int channel_id, UINT32& result);
	int m_sample_index;

	friend class RpnHandler;
};


#endif	// _VIRTUAL_BOARD_CHANNEL_H_
