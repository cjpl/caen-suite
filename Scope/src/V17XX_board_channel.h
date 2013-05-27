/////////////////////////////////////////////////////////////////////////////
// Name:        V17XX_board_channel.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _V17XX_board_CHANNEL_H_
#define _V17XX_board_CHANNEL_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "V17XX_board_channel.h"
#endif

/*!
 * Includes
 */

#include "physical_board_channel.h"

class AppSettings;

class V17XXBoardChannel: public PhysicalBoardChannel
{
public:
	V17XXBoardChannel( GenericBoard* parent, int ch_index, cvt_board_data* p_data, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex, AppSettings* p_app_settings);
	~V17XXBoardChannel(void);
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


#endif	// _V17XX_board_CHANNEL_H_
