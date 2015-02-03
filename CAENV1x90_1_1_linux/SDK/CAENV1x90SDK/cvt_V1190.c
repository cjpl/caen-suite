////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file    cvt_V1190.c
*   \brief   V1190 VME board implementation
*   \author  NDA
*   \version 1.0
*   \date    03/2006
*            
*            Provides methods, properties and defines to handle V1190 VME boards
*/
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// File includes
////////////////////////////////////////////////////////////////////////////////////////////////
#include <memory.h>
#include <string.h>
#include "cvt_V1190.h"

////////////////////////////////////////////////////////////////////////////////////////////////
// File local defines
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// Static variables declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \var     static const cvt_reg_table CVT_V1190_REG_TABLE[]
*   \brief   The board registers table
*            
*            Provides an entry for each declared register: keep synched with \ref CVT_V1190_REG_INDEX
*/
////////////////////////////////////////////////////////////////////////////////////////////////
static const cvt_reg_table CVT_V1190_REG_TABLE[]=
{
	{CVT_V1190_OUT_BUFFER_ADD,			CVT_V1190_OUT_BUFFER_AM,		CVT_V1190_OUT_BUFFER_DATA_SIZE},				/*!< \brief Output buffer */
	{CVT_V1190_CONTROL_ADD,				CVT_V1190_CONTROL_AM,			CVT_V1190_CONTROL_DATA_SIZE},					/*!< \brief Control register */
	{CVT_V1190_STATUS_ADD,				CVT_V1190_STATUS_AM,			CVT_V1190_STATUS_DATA_SIZE},					/*!< \brief Status register */
	{CVT_V1190_INT_LEVEL_ADD,			CVT_V1190_INT_LEVEL_AM,			CVT_V1190_INT_LEVEL_DATA_SIZE},					/*!< \brief Interrupt level register */
	{CVT_V1190_INT_VECTOR_ADD,			CVT_V1190_INT_VECTOR_AM,		CVT_V1190_INT_VECTOR_DATA_SIZE},				/*!< \brief Interrupt vector register */
	{CVT_V1190_GEO_ADDRESS_ADD,			CVT_V1190_GEO_ADDRESS_AM,		CVT_V1190_GEO_ADDRESS_DATA_SIZE},				/*!< \brief Geo Address register */
	{CVT_V1190_MCST_CBLT_ADDRESS_ADD,	CVT_V1190_MCST_CBLT_ADDRESS_AM,	CVT_V1190_MCST_CBLT_ADDRESS_DATA_SIZE},			/*!< \brief MCST Base Address register */
	{CVT_V1190_MCST_CBLT_CTRL_ADD,		CVT_V1190_MCST_CBLT_CTRL_AM,	CVT_V1190_MCST_CBLT_CTRL_DATA_SIZE},			/*!< \brief MCST/CBLT Control register */
	{CVT_V1190_MOD_RESET_ADD,			CVT_V1190_MOD_RESET_AM,			CVT_V1190_MOD_RESET_DATA_SIZE},					/*!< \brief Module reset register */
	{CVT_V1190_SW_CLEAR_ADD,			CVT_V1190_SW_CLEAR_AM,			CVT_V1190_SW_CLEAR_DATA_SIZE},					/*!< \brief Software clear register */
	{CVT_V1190_SW_EVENT_RESET_ADD,		CVT_V1190_SW_EVENT_RESET_AM,	CVT_V1190_SW_EVENT_RESET_DATA_SIZE},			/*!< \brief Software event reset register */
	{CVT_V1190_SW_TRIGGER_ADD,			CVT_V1190_SW_TRIGGER_AM,		CVT_V1190_SW_TRIGGER_DATA_SIZE},				/*!< \brief Software trigger register */
	{CVT_V1190_EVENT_COUNTER_ADD,		CVT_V1190_EVENT_COUNTER_AM,		CVT_V1190_EVENT_COUNTER_DATA_SIZE},				/*!< \brief Event counter register */
	{CVT_V1190_EVENT_STORED_ADD,		CVT_V1190_EVENT_STORED_AM,		CVT_V1190_EVENT_STORED_DATA_SIZE},				/*!< \brief Event stored register */
	{CVT_V1190_ALMOST_FULL_LVL_ADD,		CVT_V1190_ALMOST_FULL_LVL_AM,	CVT_V1190_ALMOST_FULL_LVL_DATA_SIZE},			/*!< \brief Almost full level register */
	{CVT_V1190_BLT_EVENT_NUM_ADD,		CVT_V1190_BLT_EVENT_NUM_AM,		CVT_V1190_BLT_EVENT_NUM_DATA_SIZE},				/*!< \brief BLT event number register */
	{CVT_V1190_FW_REV_ADD,				CVT_V1190_FW_REV_AM,			CVT_V1190_FW_REV_DATA_SIZE},					/*!< \brief Firmware revision register */
	{CVT_V1190_TESTREG_ADD,				CVT_V1190_TESTREG_AM,			CVT_V1190_TESTREG_DATA_SIZE},					/*!< \brief Testreg register */
	{CVT_V1190_OUT_PROG_CTRL_ADD,		CVT_V1190_OUT_PROG_CTRL_AM,		CVT_V1190_OUT_PROG_CTRL_DATA_SIZE},				/*!< \brief Output prog control register */
	{CVT_V1190_MICRO_ADD,				CVT_V1190_MICRO_AM,				CVT_V1190_MICRO_DATA_SIZE},						/*!< \brief Micro register */
	{CVT_V1190_MICRO_HND_ADD,			CVT_V1190_MICRO_HND_AM,			CVT_V1190_MICRO_HND_DATA_SIZE},					/*!< \brief Micro handshake register */
	{CVT_V1190_SEL_FLASH_ADD,			CVT_V1190_SEL_FLASH_AM,			CVT_V1190_SEL_FLASH_DATA_SIZE},					/*!< \brief Select Flash register */
	{CVT_V1190_FLASH_ADD,				CVT_V1190_FLASH_AM,				CVT_V1190_FLASH_DATA_SIZE},						/*!< \brief Flash register */
	{CVT_V1190_COMP_SRAM_PAGE_ADD,		CVT_V1190_COMP_SRAM_PAGE_AM,	CVT_V1190_COMP_SRAM_PAGE_DATA_SIZE},			/*!< \brief Compensation SRAM Page register */
	{CVT_V1190_EVENT_FIFO_ADD,			CVT_V1190_EVENT_FIFO_AM,		CVT_V1190_EVENT_FIFO_DATA_SIZE},				/*!< \brief Event FIFO register */
	{CVT_V1190_EVENT_FIFO_STORED_ADD,	CVT_V1190_EVENT_FIFO_STORED_AM,	CVT_V1190_EVENT_FIFO_STORED_DATA_SIZE},			/*!< \brief Event FIFO stored register */
	{CVT_V1190_EVENT_FIFO_STATUS_ADD,	CVT_V1190_EVENT_FIFO_STATUS_AM,	CVT_V1190_EVENT_FIFO_STATUS_DATA_SIZE},			/*!< \brief Event FIFO status register */
	{CVT_V1190_DUMMY32_ADD,				CVT_V1190_DUMMY32_AM,			CVT_V1190_DUMMY32_DATA_SIZE},					/*!< \brief Dummy 32 register */
	{CVT_V1190_DUMMY16_ADD,				CVT_V1190_DUMMY16_AM,			CVT_V1190_DUMMY16_DATA_SIZE},					/*!< \brief Dummy 16 register */
	{CVT_V1190_ROM_OUI_2_ADD,			CVT_V1190_ROM_OUI_2_AM,		CVT_V1190_ROM_OUI_2_DATA_SIZE},				/*!< \brief Manufacturer identifier (IEEE OUI) (MSB) register */
	{CVT_V1190_ROM_OUI_1_ADD,				CVT_V1190_ROM_OUI_1_AM,			CVT_V1190_ROM_OUI_1_DATA_SIZE},					/*!< \brief Manufacturer identifier (IEEE OUI) register */
	{CVT_V1190_ROM_OUI_0_ADD,			CVT_V1190_ROM_OUI_0_AM,		CVT_V1190_ROM_OUI_0_DATA_SIZE},				/*!< \brief Manufacturer identifier (IEEE OUI) (LSB) register */
	{CVT_V1190_ROM_VERSION_ADD,			CVT_V1190_ROM_VERSION_AM,		CVT_V1190_ROM_VERSION_DATA_SIZE},				/*!< \brief Purchased version of the Mod.V1190 register */
	{CVT_V1190_ROM_BOARD_ID_2_ADD,	CVT_V1190_ROM_BOARD_ID_2_AM,	CVT_V1190_ROM_BOARD_ID_2_DATA_SIZE},			/*!< \brief Board identifier (MSB) register */
	{CVT_V1190_ROM_BOARD_ID_1_ADD,		CVT_V1190_ROM_BOARD_ID_1_AM,		CVT_V1190_ROM_BOARD_ID_1_DATA_SIZE},				/*!< \brief Board identifier register */
	{CVT_V1190_ROM_BOARD_ID_0_ADD,	CVT_V1190_ROM_BOARD_ID_0_AM,	CVT_V1190_ROM_BOARD_ID_0_DATA_SIZE},			/*!< \brief Board identifier (LSB) register */
	{CVT_V1190_ROM_REVISION_3_ADD,		CVT_V1190_ROM_REVISION_3_AM,	CVT_V1190_ROM_REVISION_3_DATA_SIZE},			/*!< \brief Hardware revision identifier register */
	{CVT_V1190_ROM_REVISION_2_ADD,		CVT_V1190_ROM_REVISION_2_AM,	CVT_V1190_ROM_REVISION_2_DATA_SIZE},			/*!< \brief Hardware revision identifier register */
	{CVT_V1190_ROM_REVISION_1_ADD,		CVT_V1190_ROM_REVISION_1_AM,	CVT_V1190_ROM_REVISION_1_DATA_SIZE},			/*!< \brief Hardware revision identifier register */
	{CVT_V1190_ROM_REVISION_0_ADD,		CVT_V1190_ROM_REVISION_0_AM,	CVT_V1190_ROM_REVISION_0_DATA_SIZE},			/*!< \brief Hardware revision identifier register */
	{CVT_V1190_ROM_SERIAL_1_ADD,		CVT_V1190_ROM_SERIAL_1_AM,	CVT_V1190_ROM_SERIAL_1_DATA_SIZE},			/*!< \brief Serial number (MSB) register */
	{CVT_V1190_ROM_SERIAL_0_ADD,		CVT_V1190_ROM_SERIAL_0_AM,	CVT_V1190_ROM_SERIAL_0_DATA_SIZE},			/*!< \brief Serial number (LSB) register */
};
////////////////////////////////////////////////////////////////////////////////////////////////
// Static methods declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// Global visible variables declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     B O A R D S   H A N D L I N G
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_open( cvt_V1190_data* p_data, UINT16 base_address, long vme_handle, CVT_V1X90_TYPES type)
{
	memset( p_data, 0, sizeof( cvt_V1190_data));
	// Check board type
	switch( type)
	{
	case CVT_V1190_TYPE_A:						/*!< The board is V1190A */
	case CVT_V1190_TYPE_B:						/*!< The board is V1190B */
	case CVT_V1290_TYPE_A:						/*!< The board is V1290A */
	case CVT_V1290_TYPE_N:						/*!< The board is V1290N */
		break;
	default:
		TRACE1( "cvt_V1190_open: bad board type: %d\n", type);
		return FALSE;
	}
	// basic data initialization
	if( !cvt_board_open( &p_data->m_common_data, base_address, vme_handle, CVT_V1190_REG_TABLE))
		return FALSE;
	// board specific data initialization
	p_data->m_common_data.set_MCST_CBLT= ( BOOL (*)( void*, UINT8, MCST_CBLT_board_pos))cvt_V1190_set_MCST_CBLT;
	p_data->m_type= type;

#ifdef CVT_V1190_USE_DATA_QUEUE
	p_data->m_queue= malloc( CVT_V1190_QUEUE_SIZE_DWORD* sizeof( UINT32));	
	if( p_data->m_queue== NULL)
	{
		TRACE( "cvt_V1190_open: cannot allocate queue buffer\n");
		return FALSE;
	}
	memset( p_data->m_queue, 0, CVT_V1190_QUEUE_SIZE_DWORD* sizeof( UINT32));
#endif
	
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_close( cvt_V1190_data* p_data)
{
#ifdef CVT_V1190_USE_DATA_QUEUE
	if( p_data->m_queue!= NULL)
	{
		free( p_data->m_queue);
	}
#endif
	if( !cvt_board_close( &p_data->m_common_data))
		return FALSE;
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
//     L E V E L   0   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     L E V E L   1   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_write_2_micro( cvt_V1190_data* p_data, UINT16 ope_code, const UINT16* p_params, int num_params)
{
	UINT16 micro_hnd= 0;
	// wait for micro register write ok
	do
	{
		if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_MICRO_HND_INDEX, &micro_hnd))
		{
			return FALSE;
		}
	} while( !(micro_hnd& CVT_V1190_MICRO_HND_WRITEOK_MSK));
	// write opcode to micro register
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_MICRO_INDEX, &ope_code))
	{
		return FALSE;
	}
	// write ope cod
	while( num_params--)
	{
		// wait for micro register write ok
		do
		{
			if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_MICRO_HND_INDEX, &micro_hnd))
			{
				return FALSE;
			}
		} while( !(micro_hnd& CVT_V1190_MICRO_HND_WRITEOK_MSK));
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_MICRO_INDEX, p_params++))
		{
			return FALSE;
		}
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_read_from_micro( cvt_V1190_data* p_data, UINT16 ope_code, UINT16* p_params, int num_params)
{
	UINT16 micro_hnd= 0;
	// wait for micro register write ok
	do
	{
		if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_MICRO_HND_INDEX, &micro_hnd))
		{
			return FALSE;
		}
	} while( !(micro_hnd& CVT_V1190_MICRO_HND_WRITEOK_MSK));
	// write opcode to micro register
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_MICRO_INDEX, &ope_code))
	{
		return FALSE;
	}
	// read ope code 
	while( num_params--)
	{
		// wait for micro register read ok
		do
		{
			if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_MICRO_HND_INDEX, &micro_hnd))
			{
				return FALSE;
			}
		} while( !(micro_hnd& CVT_V1190_MICRO_HND_READOK_MSK));
		if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_MICRO_INDEX, p_params++))
		{
			return FALSE;
		}
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_bitmask_control( cvt_V1190_data* p_data, CVT_V1190_CONTROL_MSK value)
{
	UINT16 reg_value= value;
	// set bitmask to register
	if( !cvt_set_bitmask( &p_data->m_common_data, CVT_V1190_CONTROL_ADD, &reg_value, CVT_V1190_CONTROL_AM, CVT_V1190_CONTROL_DATA_SIZE))
	{
		TRACE( "V1190 CVT_V1190_CONTROL_SET failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_clear_bitmask_control( cvt_V1190_data* p_data, CVT_V1190_CONTROL_MSK value)
{
	UINT16 reg_value= value;
	// set bitmask to register
	if( !cvt_clear_bitmask( &p_data->m_common_data, CVT_V1190_CONTROL_ADD, &reg_value, CVT_V1190_CONTROL_AM, CVT_V1190_CONTROL_DATA_SIZE))
	{
		TRACE( "V1190 CVT_V1190_CONTROL_CLEAR failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     L E V E L   2   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_windows_width( cvt_V1190_data* p_data, UINT16 value)
{
	UINT16 reg_value= (UINT16)value;
	if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_SET_WIN_WIDTH_OPCODE, &reg_value, 1))
	{
		TRACE( "V1190 WND_WIDTH write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_windows_offset( cvt_V1190_data* p_data, UINT16 value)
{
	UINT16 reg_value= (UINT16)value;
	if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_SET_WIN_OFFSET_OPCODE, &reg_value, 1))
	{
		TRACE( "V1190 WND_OFFSET write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_get_channel_enable( cvt_V1190_data* p_data, UINT16 *p_enable_msk)
{
	int num_ch= 0;

	switch( p_data->m_type)
	{
	case CVT_V1190_TYPE_A:						/*!< The board is V1190A */
		num_ch= CVT_V1190_NUM_TDC_A* CVT_V1190_CH_PER_TDC;
		break;
	case CVT_V1190_TYPE_B:						/*!< The board is V1190B */
		num_ch= CVT_V1190_NUM_TDC_B* CVT_V1190_CH_PER_TDC;
		break;
	case CVT_V1290_TYPE_A:						/*!< The board is V1290A */
		num_ch= CVT_V1290_NUM_TDC_A* CVT_V1290_CH_PER_TDC;
		break;
	case CVT_V1290_TYPE_N:						/*!< The board is V1290N */
		num_ch= CVT_V1290_NUM_TDC_N* CVT_V1290_CH_PER_TDC;
		break;
	default:
		TRACE1( "cvt_V1190_get_channel_enable: bad board type: %d\n", p_data->m_type);
		return FALSE;
	}
	//
	// read channel enable pattern
	if( !cvt_V1190_read_from_micro( p_data, CVT_V1190_READ_EN_PATTERN_OPCODE, p_enable_msk, num_ch>> 4))
	{
		TRACE( "V1190 EN_CHANNEL_MSK write failed !\n");
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_trigger_match( cvt_V1190_data* p_data)
{
	if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_TRG_MATCH_OPCODE, NULL, 0))
	{
		TRACE( "V1190 TRG_MATCH write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_head_trail_enable( cvt_V1190_data* p_data)
{
	if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_EN_HEAD_TRAILER_OPCODE, 0, 0))
	{
		TRACE( "V1190 TDC_HEAD_TRAIL_ENABLE write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_head_trail_disable( cvt_V1190_data* p_data)
{
	if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_DIS_HEAD_TRAILER_OPCODE, 0, 0))
	{
		TRACE( "V1190 TDC_HEAD_TRAIL_DISABLE write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_read_MEB( cvt_V1190_data* p_data, void* p_buff, UINT32* p_buff_size)
{
	BOOL is_berr= FALSE;
	if( !cvt_FIFO_BLT_read( &p_data->m_common_data, CVT_V1190_OUT_BUFFER_ADD, p_buff, *p_buff_size, p_buff_size, CVT_V1190_OUT_BUFFER_AM, CVT_V1190_OUT_BUFFER_DATA_SIZE, &is_berr))
	{
		return FALSE;
	}
	// V1190 return a filler if output buffer empty, so discard it
	if( *p_buff_size== sizeof( UINT32))
	{
		if( CVT_V1190_IS_FILLER( *((UINT32*)p_buff)))
			*p_buff_size= 0;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_continuous_acquisition_mode( cvt_V1190_data* p_data, CVT_V1190_EDGE_DETECTION_ENUM edge_detection, CVT_V1190_PAIR_RES_WIDTH_ENUM res_width, const UINT16 *p_enable_msk)
{
	UINT16 reg_value;
	//
	// write continuous storage mode opcode
	if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_CONT_STORE_OPCODE, NULL, 0))
	{
		TRACE( "V1190 CVT_V1190_CONT_STORE_OPCODE write failed !\n");
		return FALSE;
	}

	//
	// Edge detection
	switch( edge_detection)
	{
	case CVT_V1190_ED_PAIR_MODE:			/*!< Pair mode. */
		switch( p_data->m_type)
		{
		case CVT_V1190_TYPE_A:						/*!< The board is V1190A */
		case CVT_V1190_TYPE_B:						/*!< The board is V1190B */
			break;
		case CVT_V1290_TYPE_A:						/*!< The board is V1290A */
		case CVT_V1290_TYPE_N:						/*!< The board is V1290N */
			// Pair Mode is not valid for V1290X 
			TRACE1( "V1190 cvt_V1190_set_continuous_acquisition_mode bad edge detection type '%d' for V1290X !\n", edge_detection);
			return FALSE;
		}
	case CVT_V1190_ED_TRAILING_ONLY:		/*!< Trailing only. */
	case CVT_V1190_ED_LEADING_ONLY:			/*!< Leading only. */
	case CVT_V1190_ED_TRAILING_AND_LEADING:	/*!< Trailing and Leading. */
		break;
	default:
		TRACE1( "V1190 cvt_V1190_set_continuous_acquisition_mode bad edge detection type '%d' !\n", edge_detection);
		return FALSE;
	}
	reg_value= edge_detection;	
	if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_SET_DETECTION_OPCODE, &reg_value, 1))
	{
		TRACE( "V1190 CVT_V1190_SET_DETECTION_OPCODE write failed !\n");
		return FALSE;
	}

	// 
	// Resolution width
	switch( p_data->m_type)
	{
	case CVT_V1190_TYPE_A:						/*!< The board is V1190A */
	case CVT_V1190_TYPE_B:						/*!< The board is V1190B */
		{
			switch( res_width)
			{
			case CVT_V1190_PRW_100PS:			/*!< 100 ps. */
			case CVT_V1190_PRW_200PS:			/*!< 200 ps. */
			case CVT_V1190_PRW_400PS:			/*!< 400 ps. */
			case CVT_V1190_PRW_800PS:			/*!< 800 ps. */
			case CVT_V1190_PRW_1_6NS:			/*!< 1.6 ns. */
			case CVT_V1190_PRW_3_12NS:			/*!< 3.12 ns. */
			case CVT_V1190_PRW_6_25NS:			/*!< 6.25 ns. */
			case CVT_V1190_PRW_12_5NS:			/*!< 12.5 ns. */
			case CVT_V1190_PRW_25NS:			/*!< 25 ns. */
			case CVT_V1190_PRW_50NS:			/*!< 50 ns. */
			case CVT_V1190_PRW_100NS:			/*!< 100 ns. */
			case CVT_V1190_PRW_200NS:			/*!< 200 ns. */
			case CVT_V1190_PRW_400NS:			/*!< 400 ns. */
			case CVT_V1190_PRW_800NS:			/*!< 800 ns. */
				break;
			default:
				TRACE1( "V1190 cvt_V1190_set_continuous_acquisition_mode bad resolution width '%d' !\n", res_width);
				return FALSE;
			}
			reg_value= 0;
			CVT_V1190_SET_PAIR_RES_WITH( reg_value, res_width);
			if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_SET_PAIR_RES_OPCODE, &reg_value, 1))
			{
				TRACE( "V1190 CVT_V1190_SET_PAIR_RES_OPCODE write failed !\n");
				return FALSE;
			}
		}
	case CVT_V1290_TYPE_A:						/*!< The board is V1290A */
	case CVT_V1290_TYPE_N:						/*!< The board is V1290N */
		break;	
	}
	//
	// Channel enable mask
	if( p_enable_msk)
	{
		if( !cvt_V1190_set_channel_enable( p_data, p_enable_msk))
		{
			return FALSE;
		}
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_trigger_matching_acquisition_mode( cvt_V1190_data* p_data, INT16 window_width, INT16 window_offset, INT16 extra_search_margin, INT16 reject_margin, CVT_V1190_EDGE_DETECTION_ENUM edge_detection, CVT_V1190_PAIR_RES_WIDTH_ENUM res_width, const UINT16 *p_enable_msk, BOOL header_trailer_enable, BOOL empty_event_enable, BOOL trigger_time_tag_enable)
{
	UINT16 reg_value;
	UINT16 set_msk= 0;
	UINT16 clear_msk= 0;
	//
	// set trigger matching mode
	if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_TRG_MATCH_OPCODE, NULL, 0))
	{
		TRACE( "V1190 CVT_V1190_TRG_MATCH_OPCODE write failed !\n");
		return FALSE;
	}
	//
	// Set window width
	if( window_width>= 0)
	{
		if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_SET_WIN_WIDTH_OPCODE, ( UINT16*)&window_width, 1))
		{
			TRACE( "V1190 CVT_V1190_SET_WIN_WIDTH_OPCODE write failed !\n");
			return FALSE;
		}
	}
	//
	// Set window offset
	if( window_offset>= 0)
	{
		if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_SET_WIN_OFFSET_OPCODE, ( UINT16*)&window_offset, 1))
		{
			TRACE( "V1190 CVT_V1190_SET_WIN_OFFSET_OPCODE write failed !\n");
			return FALSE;
		}
	}
	//
	// Set extra search margin micro opcode
	if( extra_search_margin>= 0)
	{
		if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_SET_SW_MARGIN_OPCODE, ( UINT16*)&extra_search_margin, 1))
		{
			TRACE( "V1190 CVT_V1190_SET_SW_MARGIN_OPCODE write failed !\n");
			return FALSE;
		}
	}
	//
	// Set reject margin micro opcode 
	if( reject_margin>= 0)
	{
		if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_SET_REJ_MARGIN_OPCODE, ( UINT16*)&reject_margin, 1))
		{
			TRACE( "V1190 CVT_V1190_SET_REJ_MARGIN_OPCODE write failed !\n");
			return FALSE;
		}
	}
	//
	// Edge detection
	switch( edge_detection)
	{
	case CVT_V1190_ED_PAIR_MODE:			/*!< Pair mode. */
		switch( p_data->m_type)
		{
		case CVT_V1190_TYPE_A:						/*!< The board is V1190A */
		case CVT_V1190_TYPE_B:						/*!< The board is V1190B */
			break;
		case CVT_V1290_TYPE_A:						/*!< The board is V1290A */
		case CVT_V1290_TYPE_N:						/*!< The board is V1290N */
			// Pair Mode is not valid for V1290X 
			TRACE1( "V1190 cvt_V1190_set_trigger_matching_acquisition_mode bad edge detection type '%d' for V1290X !\n", edge_detection);
			return FALSE;
		}
	case CVT_V1190_ED_TRAILING_ONLY:		/*!< Trailing only. */
	case CVT_V1190_ED_LEADING_ONLY:			/*!< Leading only. */
	case CVT_V1190_ED_TRAILING_AND_LEADING:	/*!< Trailing and Leading. */
		break;
	default:
		TRACE1( "V1190 cvt_V1190_set_trigger_matching_acquisition_mode bad edge detection type '%d' !\n", edge_detection);
		return FALSE;
	}
	reg_value= edge_detection;	
	if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_SET_DETECTION_OPCODE, &reg_value, 1))
	{
		TRACE( "V1190 CVT_V1190_SET_DETECTION_OPCODE write failed !\n");
		return FALSE;
	}
	// 
	// Resolution width
	switch( p_data->m_type)
	{
	case CVT_V1190_TYPE_A:						/*!< The board is V1190A */
	case CVT_V1190_TYPE_B:						/*!< The board is V1190B */
		{
			switch( res_width)
			{
			case CVT_V1190_PRW_100PS:			/*!< 100 ps. */
			case CVT_V1190_PRW_200PS:			/*!< 200 ps. */
			case CVT_V1190_PRW_400PS:			/*!< 400 ps. */
			case CVT_V1190_PRW_800PS:			/*!< 800 ps. */
			case CVT_V1190_PRW_1_6NS:			/*!< 1.6 ns. */
			case CVT_V1190_PRW_3_12NS:			/*!< 3.12 ns. */
			case CVT_V1190_PRW_6_25NS:			/*!< 6.25 ns. */
			case CVT_V1190_PRW_12_5NS:			/*!< 12.5 ns. */
			case CVT_V1190_PRW_25NS:			/*!< 25 ns. */
			case CVT_V1190_PRW_50NS:			/*!< 50 ns. */
			case CVT_V1190_PRW_100NS:			/*!< 100 ns. */
			case CVT_V1190_PRW_200NS:			/*!< 200 ns. */
			case CVT_V1190_PRW_400NS:			/*!< 400 ns. */
			case CVT_V1190_PRW_800NS:			/*!< 800 ns. */
				break;
			default:
				TRACE1( "V1190 cvt_V1190_set_trigger_matching_acquisition_mode bad resolution width '%d' !\n", res_width);
				return FALSE;
			}
			reg_value= 0;
			CVT_V1190_SET_PAIR_RES_WITH( reg_value, res_width);
			if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_SET_PAIR_RES_OPCODE, &reg_value, 1))
			{
				TRACE( "V1190 CVT_V1190_SET_PAIR_RES_OPCODE write failed !\n");
				return FALSE;
			}
		}
	case CVT_V1290_TYPE_A:						/*!< The board is V1290A */
	case CVT_V1290_TYPE_N:						/*!< The board is V1290N */
		break;	
	}

	//
	// Channel enable pattern
	//
	// Channel enable mask
	if( p_enable_msk)
	{
		if( !cvt_V1190_set_channel_enable( p_data, p_enable_msk))
		{
			return FALSE;
		}
	}
	//
	// enable/disable header trailer
	if( header_trailer_enable)
	{
		if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_EN_HEAD_TRAILER_OPCODE, NULL, 0))
		{
			TRACE( "V1190 CVT_V1190_EN_HEAD_TRAILER_OPCODE write failed !\n");
			return FALSE;
		}
	}
	else
	{
		if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_DIS_HEAD_TRAILER_OPCODE, NULL, 0))
		{
			TRACE( "V1190 CVT_V1190_DIS_HEAD_TRAILER_OPCODE write failed !\n");
			return FALSE;
		}
	}

	//
	// Empty event enable
	set_msk|= ( empty_event_enable)? CVT_V1190_CTRL_EMPTY_EVENT_MSK: 0;
	clear_msk|= ( empty_event_enable)? 0: CVT_V1190_CTRL_EMPTY_EVENT_MSK;
	//
	// Trigger time tag enable
	set_msk|= ( trigger_time_tag_enable)? CVT_V1190_CTRL_TRIGGER_TIME_TAG_ENABLE_MSK: 0;
	clear_msk|= ( trigger_time_tag_enable)? 0: CVT_V1190_CTRL_TRIGGER_TIME_TAG_ENABLE_MSK;

	if( set_msk)
	{
		if( !cvt_set_bitmask_reg( &p_data->m_common_data, CVT_V1190_CONTROL_INDEX, &set_msk))
		{
			TRACE( "V1190 CVT_V1190_CONTROL bitmask set failed !\n");
			return FALSE;
		}
	}
	if( clear_msk)
	{
		if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CVT_V1190_CONTROL_INDEX, &clear_msk))
		{
			TRACE( "V1190 CVT_V1190_CONTROL bitmask clear failed !\n");
			return FALSE;
		}
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_interrupt( cvt_V1190_data* p_data, UINT8 level, UINT8 vector)
{
	UINT16 reg_value;
	//
	// interrupt level
	reg_value= level& 0x07;
	if( level!= reg_value)
	{
		TRACE( "V1190 bad interrupt level !\n");
		return FALSE;
	}
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_INT_LEVEL_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_INT_LEVEL write failed !\n");
		return FALSE;
	}
	//
	// interrupt vector
	reg_value= vector;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_INT_VECTOR_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_INT_VECTOR write failed !\n");
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_readout_mode( cvt_V1190_data* p_data, BOOL bus_error_enable, BOOL align64_enable, UINT8 blt_event_number)
{
	UINT16 reg_value;
	UINT16 set_msk= 0;
	UINT16 clear_msk= 0;
	
	//
	// Bus error
	set_msk|= ( bus_error_enable)? CVT_V1190_CTRL_BERR_ENABLE_MSK: 0;
	clear_msk|= ( bus_error_enable)? 0: CVT_V1190_CTRL_BERR_ENABLE_MSK;
	//
	// Align 64
	set_msk|= ( align64_enable)? CVT_V1190_CTRL_ALIGN64_MSK: 0;
	clear_msk|= ( align64_enable)? 0: CVT_V1190_CTRL_ALIGN64_MSK;
	
	//
	// bitmask set
	if( set_msk)
	{
		if( !cvt_set_bitmask_reg( &p_data->m_common_data, CVT_V1190_CONTROL_INDEX, &set_msk))
		{
			TRACE( "V1190 CVT_V1190_CONTROL write failed !\n");
			return FALSE;
		}
	}
	//
	// bitmask clear
	if( clear_msk)
	{
		// clear the enable bit
		if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CVT_V1190_CONTROL_INDEX, &clear_msk))
		{
			TRACE( "V1190 CVT_V1190_CONTROL write failed !\n");
			return FALSE;
		}
	}

	//
	// BLT event number
	reg_value= blt_event_number;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_BLT_EVENT_NUM_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_BLT_EVENT_NUM write failed !\n");
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_get_status( cvt_V1190_data* p_data, BOOL *p_is_data_ready, BOOL *p_is_term_on, BOOL *p_is_buffer_full, BOOL *p_is_buffer_almost_full, CVT_V1190_STATUS_RES* p_resolution, UINT8* p_error_bitmask)
{
	UINT16 reg_value= 0;
	//
	// read status register
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_STATUS_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_STATUS read failed !\n");
		return FALSE;
	}
	*p_is_data_ready= ( reg_value& CVT_V1190_STS_DREADY_MSK)? TRUE: FALSE;
	*p_is_term_on= ( reg_value& CVT_V1190_STS_TERM_ON_MSK)? TRUE: FALSE;
	*p_is_buffer_full= ( reg_value& CVT_V1190_STS_FULL_MSK)? TRUE: FALSE;
	*p_is_buffer_almost_full= ( reg_value& CVT_V1190_STS_ALMOST_FULL_MSK)? TRUE: FALSE;

	*p_resolution= CVT_V1190_GET_STATUS_RES( reg_value);
	*p_error_bitmask= CVT_V1190_GET_STATUS_ERROR( reg_value);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_get_event_counter( cvt_V1190_data* p_data, UINT32* p_counter)
{
	UINT32 reg_value;
	*p_counter= 0;
	// Event Counter
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_EVENT_COUNTER_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_EVENT_COUNTER read failed !\n");
		return FALSE;
	}
	*p_counter= reg_value;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_get_event_stored( cvt_V1190_data* p_data, UINT16* p_counter)
{
	UINT16 reg_value;
	*p_counter= 0;
	// Event stored
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_EVENT_STORED_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_EVENT_STORED read failed !\n");
		return FALSE;
	}
	*p_counter= reg_value;

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_get_system_info( cvt_V1190_data* p_data, UINT16 *p_firmware_rev, UINT32 *p_tdc_id_buff, UINT16 *p_micro_firmware_rev, UINT16 *p_serial_number)
{
	UINT16 reg_value= 0;
	UINT32 reg_value32= 0;
	int num_tdc= 0;

	switch( p_data->m_type)
	{
	case CVT_V1190_TYPE_A:						/*!< The board is V1190A */
		num_tdc= CVT_V1190_NUM_TDC_A;
		break;
	case CVT_V1190_TYPE_B:						/*!< The board is V1190B */
		num_tdc= CVT_V1190_NUM_TDC_B;
		break;
	case CVT_V1290_TYPE_A:						/*!< The board is V1290A */
		num_tdc= CVT_V1290_NUM_TDC_A;
		break;
	case CVT_V1290_TYPE_N:						/*!< The board is V1290N */
		num_tdc= CVT_V1290_NUM_TDC_N;
		break;
	default:
		TRACE1( "cvt_V1190_get_system_info: bad board type: %d\n", p_data->m_type);
		return FALSE;
	}
	//
	// Firmware revision register
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_FW_REV_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_FW_REV read failed !\n");
		return FALSE;
	}
	*p_firmware_rev= (( reg_value& 0x00f0)<< 4)|( reg_value& 0x000f);
	//
	// TDC IDs
	while( num_tdc--)
	{
		if( !cvt_V1190_read_from_micro( p_data, CVT_V1190_READ_TDC_ID_OPCODE+ num_tdc, (UINT16*)&reg_value32, 2))
		{
			TRACE( "V1190 CVT_V1190_READ_TDC_ID_OPCODE opcode read failed !\n");
			return FALSE;
		}
		p_tdc_id_buff[ num_tdc]= reg_value32;
		// (( reg_value& 0x00f0)<< 4)|( reg_value& 0x000f);
	}
	//
	// Microcontroller firmware revision
	if( !cvt_V1190_read_from_micro( p_data, CVT_V1190_READ_MICRO_REV_OPCODE, &reg_value, 1))
	{
		TRACE( "V1190 CVT_V1190_READ_MICRO_REV_OPCODE opcode read failed !\n");
		return FALSE;
	}
	*p_micro_firmware_rev= (( reg_value& 0x00f0)<< 4)|( reg_value& 0x000f);
	//
	// Serial number
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_ROM_SERIAL_0_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_ROM_SERIAL_LSB read failed !\n");
		return FALSE;
	}
	*p_serial_number= reg_value& 0x00ff;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1190_ROM_SERIAL_1_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_ROM_SERIAL_MSB read failed !\n");
		return FALSE;
	}
	*p_serial_number|= (reg_value& 0x00ff)<< 8;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_data_clear( cvt_V1190_data* p_data)
{
	UINT16 reg_value= 0;
	// force software clear
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_SW_CLEAR_INDEX, &reg_value))
	{
		TRACE( "V1190 SW_CLEAR write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_module_reset( cvt_V1190_data* p_data)
{
	UINT16 reg_value= 0;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_MOD_RESET_INDEX, &reg_value))
	{
		TRACE( "V1190 MOD_RESET write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_channel_enable( cvt_V1190_data* p_data, const UINT16* p_enable_msk)
{
	int num_ch= 0;

	switch( p_data->m_type)
	{
	case CVT_V1190_TYPE_A:						/*!< The board is V1190A */
		num_ch= CVT_V1190_NUM_TDC_A* CVT_V1190_CH_PER_TDC;
		break;
	case CVT_V1190_TYPE_B:						/*!< The board is V1190B */
		num_ch= CVT_V1190_NUM_TDC_B* CVT_V1190_CH_PER_TDC;
		break;
	case CVT_V1290_TYPE_A:						/*!< The board is V1290A */
		num_ch= CVT_V1290_NUM_TDC_A* CVT_V1290_CH_PER_TDC;
		break;
	case CVT_V1290_TYPE_N:						/*!< The board is V1290A */
		num_ch= CVT_V1290_NUM_TDC_N* CVT_V1290_CH_PER_TDC;
		break;
	default:
		TRACE1( "cvt_V1190_set_channel_enable: bad board type: %d\n", p_data->m_type);
		return FALSE;
	}

	//
	// write channel enable pattern
	if( !cvt_V1190_write_2_micro( p_data, CVT_V1190_WRITE_EN_PATTERN_OPCODE, p_enable_msk, num_ch>> 4))
	{
		TRACE( "V1190 EN_CHANNEL_MSK write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_almost_full( cvt_V1190_data* p_data, UINT16 almost_full_value)
{
	UINT16 reg_value= 0;
	//
	// write the almost full register
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_ALMOST_FULL_LVL_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_ALMOST_FULL_LVL write failed !\n");
		return FALSE;
	}
	return TRUE;
}



////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_peek_event( cvt_V1190_data *p_data, UINT32 *out_buff, long *p_out_buff_size, UINT32 *p_event_count)
{
	long in_org_pos= p_data->m_queue_ini;
	int step= 0;
	UINT32 data;
	long queue_ptr= in_org_pos;
	long out_buff_size= *p_out_buff_size;
	long num_word_to_read= 0;

	// scan input stream
	while( queue_ptr!= p_data->m_queue_end)
	{
		data= p_data->m_queue[ queue_ptr];
		if( ++queue_ptr>= CVT_V1190_QUEUE_SIZE_DWORD)
		{
			queue_ptr= 0;
		}
		switch( step)
		{
			case 0:
				//
				// wait for header
				if( !CVT_V1190_IS_GLOBAL_HEADER( data))
				{
					// misplaced data ?!?!?
					// skip it
					cvt_V1190_dequeue( p_data, NULL, 1);
					in_org_pos= queue_ptr;
					break;
				}
				// Global Header found:
				// EOB found
				// check event count
				*p_event_count= CVT_V1190_GET_GLB_HDR_EVENT_COUNT( data);

				num_word_to_read= 1;
				++step;
				break;
			case 1:
				//
				// wait for EOB
				++num_word_to_read;
				// check if EOB
				if( !CVT_V1190_IS_GLOBAL_TRAILER( data))
				{
					// channels data
					break;
				}
				if( out_buff_size< num_word_to_read)
				{
					*p_out_buff_size= 0;
					return FALSE;
				}
				// event count matching
				if( queue_ptr>= in_org_pos)
				{
					memcpy( out_buff, p_data->m_queue+ in_org_pos, num_word_to_read*sizeof( UINT32));
				}
				else
				{
					// HACK: debug < or <= condition
					long first_block_word= CVT_V1190_QUEUE_SIZE_DWORD- in_org_pos;
					long second_block_word= num_word_to_read- first_block_word;
					memcpy( out_buff, p_data->m_queue+ in_org_pos, first_block_word* sizeof(UINT32));
					memcpy( out_buff+ first_block_word, p_data->m_queue, second_block_word* sizeof(UINT32));
				}
				*p_out_buff_size= num_word_to_read;
				// done
				return TRUE;
		}
	}
	*p_out_buff_size= 0;
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_inqueue( cvt_V1190_data* p_data, const UINT32* in_buff, UINT32 in_buff_size)
{
	if( !in_buff_size)
		return TRUE;
	if( cvt_V1190_get_queue_free( p_data)< (long)in_buff_size)
	{
		// No enough free space
		return FALSE;
	}
	if( p_data->m_queue_end+ in_buff_size< CVT_V1190_QUEUE_SIZE_DWORD)
	{
		memcpy( p_data->m_queue+ p_data->m_queue_end, in_buff, in_buff_size*sizeof( UINT32));
		p_data->m_queue_end+= in_buff_size;
	}
	else
	{
		long first_block_word= CVT_V1190_QUEUE_SIZE_DWORD- p_data->m_queue_end;
		long second_block_word= in_buff_size- first_block_word;
		memcpy( p_data->m_queue+ p_data->m_queue_end, in_buff, first_block_word* sizeof(UINT32));
		memcpy( p_data->m_queue, in_buff+ first_block_word, second_block_word* sizeof(UINT32));
		p_data->m_queue_end= second_block_word;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_dequeue( cvt_V1190_data* p_data, UINT32 *out_buff, UINT32 out_buff_size)
{
	if( !out_buff_size)
		return TRUE;
	if( cvt_V1190_get_queue_length( p_data)< (long)out_buff_size)
	{
		// No enough data
		return FALSE;
	}
	if( p_data->m_queue_ini+ out_buff_size< CVT_V1190_QUEUE_SIZE_DWORD)
	{
		if( out_buff)
		{
			memcpy( out_buff, p_data->m_queue+ p_data->m_queue_ini, out_buff_size*sizeof( UINT32));
		}
		p_data->m_queue_ini+= out_buff_size;
	}
	else
	{
		long first_block_word= CVT_V1190_QUEUE_SIZE_DWORD- p_data->m_queue_ini;
		long second_block_word= out_buff_size- first_block_word;
		if( out_buff)
		{
			memcpy( out_buff, p_data->m_queue+ p_data->m_queue_ini, first_block_word* sizeof(UINT32));
			memcpy( out_buff+ first_block_word, p_data->m_queue, second_block_word* sizeof(UINT32));
		}
		p_data->m_queue_ini= second_block_word;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
long cvt_V1190_get_queue_free( cvt_V1190_data* p_data)
{
	return (long)CVT_V1190_QUEUE_SIZE_DWORD- (( p_data->m_queue_end- p_data->m_queue_ini+ CVT_V1190_QUEUE_SIZE_DWORD)%CVT_V1190_QUEUE_SIZE_DWORD);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
long cvt_V1190_get_queue_length( cvt_V1190_data* p_data)
{
	return (long)(( p_data->m_queue_end- p_data->m_queue_ini+ CVT_V1190_QUEUE_SIZE_DWORD)%CVT_V1190_QUEUE_SIZE_DWORD);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1190_set_MCST_CBLT( cvt_V1190_data* p_data, UINT8 address, MCST_CBLT_board_pos pos)
{
	UINT16 reg_value;
	//
	// MCST/CBLT address
	reg_value= address;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_MCST_CBLT_ADDRESS_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_MCST_CBLT_ADDRESS write failed !\n");
		return FALSE;
	}
	//
	// MCST/CBLT control
	switch( pos)
	{
	case MCST_CBLT_board_pos_first:
		reg_value= CVT_V1190_MCCTRL_FIRST_BOARD_MSK;
		break;
	case MCST_CBLT_board_pos_mid:
		reg_value= CVT_V1190_MCCTRL_MID_BOARD_MSK;
		break;
	case MCST_CBLT_board_pos_last:
		reg_value= CVT_V1190_MCCTRL_LAST_BOARD_MSK;
		break;
	case MCST_CBLT_board_disabled:
		reg_value= CVT_V1190_MCCTRL_DISABLED_BOARD_MSK;
		break;
	default:
		TRACE1( "V1190 cvt_V1190_set_MCST_CBLT bad position indentifier '%d'!\n", pos);
		return FALSE;
	}
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1190_MCST_CBLT_CTRL_INDEX, &reg_value))
	{
		TRACE( "V1190 CVT_V1190_MCST_CBLT_CTRL write failed !\n");
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     M I S C E L L A N E O U S   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
const char* cvt_V1190_SW_rev( void)
{
	return "CAEN1x90SDK Rev. 1.1";
}
