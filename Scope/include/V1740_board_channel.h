/////////////////////////////////////////////////////////////////////////////
// Name:        V1740_board_channel.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _V1740_board_CHANNEL_H_
#define _V1740_board_CHANNEL_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "V1740_board_channel.h"
#endif

/*!
 * Includes
 */

#include "physical_board_channel.h"

class AppSettings;

class V1740BoardChannel: public PhysicalBoardChannel
{
public:
	V1740BoardChannel( GenericBoard* parent, int ch_index, cvt_board_data* p_data, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex, AppSettings* p_app_settings);
	~V1740BoardChannel(void);
	//
	// Properties

	//
	// Methods

	// Pure virtual 
	bool ReadSamplesCache( UINT32 num_samples);
	bool WriteDACOffset( void);
	bool WriteChannelTrigger( void);

protected:

};


#endif	// _V1740_board_CHANNEL_H_
