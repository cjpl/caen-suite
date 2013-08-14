/////////////////////////////////////////////////////////////////////////////
// Name:        V17XX_board.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 14:18:40
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _V17XX_board_H_
#define _V17XX_board_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "V17XX_board.h"
#endif

/*!
 * Includes
 */

extern "C" 
{
	#include "cvt_V1724.h"
}
#include "generic_board.h"

class AppSettings;

// SDK extension to support Desktop and NIM ADC
typedef enum
{
	CVT_V17XX_RCFG_BOARD_ID_DT5724=	0x00020000| 5724,		/*!< \brief The board is DT5724*/
	CVT_V17XX_RCFG_BOARD_ID_N6724=	0x00030000| 6724,		/*!< \brief The board is N6724  */

	CVT_V17XX_RCFG_BOARD_ID_DT5721=	0x00020000| 5721,		/*!< \brief The board is DT5721 */
	CVT_V17XX_RCFG_BOARD_ID_N6721=	0x00030000| 6721,		/*!< \brief The board is N6721  */

	CVT_V17XX_RCFG_BOARD_ID_DT5731=	0x00020000| 5731,		/*!< \brief The board is DT5731 */
	CVT_V17XX_RCFG_BOARD_ID_N6731=	0x00030000| 6731,		/*!< \brief The board is N6731  */

	CVT_V17XX_RCFG_BOARD_ID_DT5720=	0x00020000| 5720,		/*!< \brief The board is DT5720 */
	CVT_V17XX_RCFG_BOARD_ID_N6720=	0x00030000| 6720,		/*!< \brief The board is N6720  */

	CVT_V17XX_RCFG_BOARD_ID_DT5740=	0x00020000| 5740,		/*!< \brief The board is DT5740 */
	CVT_V17XX_RCFG_BOARD_ID_N6740=	0x00030000| 6740,		/*!< \brief The board is N6740  */

	CVT_V17XX_RCFG_BOARD_ID_DT5751=	0x00020000| 5751,		/*!< \brief The board is DT5751 */
	CVT_V17XX_RCFG_BOARD_ID_N6751=	0x00030000| 6751,		/*!< \brief The board is N6751  */

} CVT_V17XX_TYPES_EXT;


class V17XXBoard :	public GenericBoard
{
public:
	typedef enum  
	{
		BV_VME= 0,		// Vme
		BV_DESKTOP,		// Desktop
		BV_NIM,			// Nim
	} BOARD_VARIANT;

	V17XXBoard( int board_index, void (* scope_refresh)( int, bool), void (*update_samples_ready_led)( bool), wxMutex *p_data_mutex, AppSettings* p_app_settings, BOARD_VARIANT board_variant);
	~V17XXBoard( void);

	//
	// Pure virtual implememtation
	bool Open( long vme_handle);
	GenericBoardChannel* CreateChannel( int ch_index, void (* scope_refresh)( int, bool), wxMutex *p_data_mutex);
	bool WriteSampleBufferSize( void);
	bool WriteTriggerMode( bool started);
	bool WriteSoftwareTrigger( void);
	bool SetFrontPanelIO( bool use_TTL);
	bool ReadBoardData( UINT32 *p_max_num_samples, UINT32* p_num_events);
	bool DoStartAcquisition( void);
	bool DoStopAcquisition( void);
	static bool GetBoardId( cvt_board_data data, int &board_id);
	static bool v1724_get_system_info_wrapper( cvt_V1724_data* p_data, UINT16 *p_firmware_rev, CVT_V1724_ROM_CONFIG *p_rom_config, BOOL *p_is_board_type_correct, BOOL *p_is_firmware_rev_correct);
	bool Init( long vme_handle);
	virtual int GetPostTriggerDivider() const = 0;
protected:
	BOARD_VARIANT m_board_variant;

};


#endif	// _V17XX_board_H_

