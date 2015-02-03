////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file    cvt_V1190.h
*   \brief   V1190 VME board definitions
*   \author  NDA 
*   \version 1.0
*   \date    03/2006
*            
*            Provides methods, properties and defines to handle V1190 VME boards
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CVT_V1190_DEF_H
#define __CVT_V1190_DEF_H

////////////////////////////////////////////////////////////////////////////////////////////////
// File includes
////////////////////////////////////////////////////////////////////////////////////////////////
#include "cvt_common_defs.h"
#include "cvt_board_commons.h"
////////////////////////////////////////////////////////////////////////////////////////////////
// Global defines
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \def     CVT_V1190_USE_DATA_QUEUE
*   \brief   Enable/ disable V1190 builtin data queue
*            
*            Define this to enable V1190 builtin data queue; comment out to disable this feature
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#define CVT_V1190_USE_DATA_QUEUE	1

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \def     CVT_V1190_QUEUE_SIZE_DWORD
*   \brief   V1190 data queue size 
*            
*            This is the number of UINT32 words storage into the V1190 builtin data queue
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#define CVT_V1190_QUEUE_SIZE_DWORD	(1024*1024)	

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1X90_TYPES
*   \brief   The V1190/V1290 board type
*            
*            Provides an entry for each board type
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_TYPE_A,							/*!< \brief The board is V1190A */
	CVT_V1190_TYPE_B,							/*!< \brief The board is V1190B */
	CVT_V1290_TYPE_A,							/*!< \brief The board is V1290A */
	CVT_V1290_TYPE_N,							/*!< \brief The board is V1290N */
} CVT_V1X90_TYPES;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1X90_CH_PER_TDC
*   \brief   The V1X90 number of channel per TDC
*            
*            Provides an entry for each board type
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_CH_PER_TDC= 32,			/*!< \brief The V1190X's channel number per TDC */
	CVT_V1290_CH_PER_TDC= 8,			/*!< \brief The V1290X's channel number per TDC */
} CVT_V1X90_CH_PER_TDC;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \struct  cvt_V1190_data
*   \brief   V1190 board data structure
*            
*            This structure stores any board data, common and specific ones. 
*            It must be passed to each V1190's API 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	cvt_board_data	m_common_data;				/*!< Boards common data structure: always let at offset 0 */
	//
	// Board specific data
	CVT_V1X90_TYPES m_type;						/*!< The V1X90 board type (either V1190A, V1190B, V1290A, V1290N) */
#ifdef CVT_V1190_USE_DATA_QUEUE
	UINT32 *m_queue;							/*!< Builtin read data queue: only if CVT_V1190_USE_DATA_QUEUE is defined */
	long m_queue_ini;							/*!< Builtin read data queue bottom offset: valid data can be peeked from queue_ini to queue_end. (only if CVT_V1190_USE_DATA_QUEUE is defined) */
	long m_queue_end;							/*!< Builtin read data queue top offset: new data can be stored from queue_end to queue_ini (only if CVT_V1190_USE_DATA_QUEUE is defined) */
#endif
} cvt_V1190_data;


#define CVT_V1190_NUM_TDC_A		4				/*!< \brief TDCs number for V1190A */
#define CVT_V1190_NUM_TDC_B		2				/*!< \brief TDCs number for V1190B */
#define CVT_V1290_NUM_TDC_A		4				/*!< \brief TDCs number for V1290A */
#define CVT_V1290_NUM_TDC_N		2				/*!< \brief TDCs number for V1290N */

////////////////////////////////////////////////////////////////////////////////////////////////
// Registers address
////////////////////////////////////////////////////////////////////////////////////////////////
#define CVT_V1190_OUT_BUFFER_ADD				0x0000			/*!< \brief Output buffer relative address */
#define CVT_V1190_CONTROL_ADD					0x1000			/*!< \brief Control register relative address */
#define CVT_V1190_STATUS_ADD					0x1002			/*!< \brief Status register relative address */
#define CVT_V1190_INT_LEVEL_ADD					0x100A			/*!< \brief Interrupt level register relative address */
#define CVT_V1190_INT_VECTOR_ADD				0x100C			/*!< \brief Interrupt vector register relative address */
#define CVT_V1190_GEO_ADDRESS_ADD				0x100E			/*!< \brief Geo Address register relative address */
#define CVT_V1190_MCST_CBLT_ADDRESS_ADD			0x1010			/*!< \brief MCST/CBLT Base Address register relative address */
#define CVT_V1190_MCST_CBLT_CTRL_ADD			0x1012			/*!< \brief MCST/CBLT Control register relative address */
#define CVT_V1190_MOD_RESET_ADD					0x1014			/*!< \brief Module reset register relative address */
#define CVT_V1190_SW_CLEAR_ADD					0x1016			/*!< \brief Software clear register relative address */
#define CVT_V1190_SW_EVENT_RESET_ADD			0x1018			/*!< \brief Software event reset register relative address */
#define CVT_V1190_SW_TRIGGER_ADD				0x101A			/*!< \brief Software trigger register relative address */
#define CVT_V1190_EVENT_COUNTER_ADD				0x101C			/*!< \brief Event counter register relative address */
#define CVT_V1190_EVENT_STORED_ADD				0x1020			/*!< \brief Event stored register relative address */
#define CVT_V1190_ALMOST_FULL_LVL_ADD			0x1022			/*!< \brief Almost full level register relative address */
#define CVT_V1190_BLT_EVENT_NUM_ADD				0x1024			/*!< \brief BLT event number register relative address */
#define CVT_V1190_FW_REV_ADD					0x1026			/*!< \brief Firmware revision register relative address */
#define CVT_V1190_TESTREG_ADD					0x1028			/*!< \brief Testreg register relative address */
#define CVT_V1190_OUT_PROG_CTRL_ADD				0x102C			/*!< \brief Output prog control register relative address */
#define CVT_V1190_MICRO_ADD						0x102E			/*!< \brief Micro register relative address */
#define CVT_V1190_MICRO_HND_ADD					0x1030			/*!< \brief Micro handshake register relative address */
#define CVT_V1190_SEL_FLASH_ADD					0x1032			/*!< \brief Select Flash register relative address */
#define CVT_V1190_FLASH_ADD						0x1034			/*!< \brief Flash register relative address */
#define CVT_V1190_COMP_SRAM_PAGE_ADD			0x1036			/*!< \brief Compensation SRAM Page register relative address */
#define CVT_V1190_EVENT_FIFO_ADD				0x1038			/*!< \brief Event FIFO register relative address */
#define CVT_V1190_EVENT_FIFO_STORED_ADD			0x103C			/*!< \brief Event FIFO stored register relative address */
#define CVT_V1190_EVENT_FIFO_STATUS_ADD			0x103E			/*!< \brief Event FIFO status register relative address */
#define CVT_V1190_DUMMY32_ADD					0x1200			/*!< \brief Dummy 32 register relative address */
#define CVT_V1190_DUMMY16_ADD					0x1204			/*!< \brief Dummy 16 register relative address */
#define CVT_V1190_ROM_OUI_2_ADD					0x4024			/*!< \brief Manufacturer identifier (IEEE OUI) (MSB) relative address */
#define CVT_V1190_ROM_OUI_1_ADD					0x4028			/*!< \brief Manufacturer identifier (IEEE OUI) relative address */
#define CVT_V1190_ROM_OUI_0_ADD					0x402C			/*!< \brief Manufacturer identifier (IEEE OUI) (LSB) relative address */
#define CVT_V1190_ROM_VERSION_ADD				0x4030			/*!< \brief Purchased version of the Mod.V1190 relative address */
#define CVT_V1190_ROM_BOARD_ID_2_ADD			0x4034			/*!< \brief Board identifier (MSB) relative address */
#define CVT_V1190_ROM_BOARD_ID_1_ADD			0x4038			/*!< \brief Board identifier relative address */
#define CVT_V1190_ROM_BOARD_ID_0_ADD			0x403C			/*!< \brief Board identifier (LSB) relative address */
#define CVT_V1190_ROM_REVISION_3_ADD			0x4040			/*!< \brief Hardware revision identifier relative address */
#define CVT_V1190_ROM_REVISION_2_ADD			0x4044			/*!< \brief Hardware revision identifier relative address */
#define CVT_V1190_ROM_REVISION_1_ADD			0x4048			/*!< \brief Hardware revision identifier relative address */
#define CVT_V1190_ROM_REVISION_0_ADD			0x404C			/*!< \brief Hardware revision identifier relative address */
#define CVT_V1190_ROM_SERIAL_1_ADD				0x4080			/*!< \brief Serial number (MSB) relative address */
#define CVT_V1190_ROM_SERIAL_0_ADD				0x4084			/*!< \brief Serial number (LSB) relative address */

////////////////////////////////////////////////////////////////////////////////////////////////
// Registers data size
////////////////////////////////////////////////////////////////////////////////////////////////
#define CVT_V1190_OUT_BUFFER_DATA_SIZE			cvD64			/*!< \brief Output buffer data size */
#define CVT_V1190_CONTROL_DATA_SIZE				cvD16			/*!< \brief Control register data size */
#define CVT_V1190_STATUS_DATA_SIZE				cvD16			/*!< \brief Status register data size */
#define CVT_V1190_INT_LEVEL_DATA_SIZE			cvD16			/*!< \brief Interrupt level register data size */
#define CVT_V1190_INT_VECTOR_DATA_SIZE			cvD16			/*!< \brief Interrupt vector register data size */
#define CVT_V1190_GEO_ADDRESS_DATA_SIZE			cvD16			/*!< \brief Geo Address register data size */
#define CVT_V1190_MCST_CBLT_ADDRESS_DATA_SIZE	cvD16			/*!< \brief MCST/CBLT Base Address register data size */
#define CVT_V1190_MCST_CBLT_CTRL_DATA_SIZE		cvD16			/*!< \brief MCST/CBLT Control register data size */
#define CVT_V1190_MOD_RESET_DATA_SIZE			cvD16			/*!< \brief Module reset register data size */
#define CVT_V1190_SW_CLEAR_DATA_SIZE			cvD16			/*!< \brief Software clear register data size */
#define CVT_V1190_SW_EVENT_RESET_DATA_SIZE		cvD16			/*!< \brief Software event reset register data size */
#define CVT_V1190_SW_TRIGGER_DATA_SIZE			cvD16			/*!< \brief Software trigger register data size */
#define CVT_V1190_EVENT_COUNTER_DATA_SIZE		cvD32			/*!< \brief Event counter register data size */
#define CVT_V1190_EVENT_STORED_DATA_SIZE		cvD16			/*!< \brief Event stored register data size */
#define CVT_V1190_ALMOST_FULL_LVL_DATA_SIZE		cvD16			/*!< \brief Almost full level register data size */
#define CVT_V1190_BLT_EVENT_NUM_DATA_SIZE		cvD16			/*!< \brief BLT event number register data size */
#define CVT_V1190_FW_REV_DATA_SIZE				cvD16			/*!< \brief Firmware revision register data size */
#define CVT_V1190_TESTREG_DATA_SIZE				cvD32			/*!< \brief Testreg register data size */
#define CVT_V1190_OUT_PROG_CTRL_DATA_SIZE		cvD16			/*!< \brief Output prog control register data size */
#define CVT_V1190_MICRO_DATA_SIZE				cvD16			/*!< \brief Micro register data size */
#define CVT_V1190_MICRO_HND_DATA_SIZE			cvD16			/*!< \brief Micro handshake register data size */
#define CVT_V1190_SEL_FLASH_DATA_SIZE			cvD16			/*!< \brief Select Flash register data size */
#define CVT_V1190_FLASH_DATA_SIZE				cvD16			/*!< \brief Flash register data size */
#define CVT_V1190_COMP_SRAM_PAGE_DATA_SIZE		cvD16			/*!< \brief Compensation SRAM Page register data size */
#define CVT_V1190_EVENT_FIFO_DATA_SIZE			cvD32			/*!< \brief Event FIFO register data size */
#define CVT_V1190_EVENT_FIFO_STORED_DATA_SIZE	cvD16			/*!< \brief Event FIFO stored register data size */
#define CVT_V1190_EVENT_FIFO_STATUS_DATA_SIZE	cvD16			/*!< \brief Event FIFO status register data size */
#define CVT_V1190_DUMMY32_DATA_SIZE				cvD32			/*!< \brief Dummy 32 register data size */
#define CVT_V1190_DUMMY16_DATA_SIZE				cvD16			/*!< \brief Dummy 16 register data size */
#define CVT_V1190_ROM_OUI_2_DATA_SIZE			cvD16			/*!< \brief Manufacturer identifier (IEEE OUI) (MSB) data size */
#define CVT_V1190_ROM_OUI_1_DATA_SIZE			cvD16			/*!< \brief Manufacturer identifier (IEEE OUI) data size */
#define CVT_V1190_ROM_OUI_0_DATA_SIZE			cvD16			/*!< \brief Manufacturer identifier (IEEE OUI) (LSB) data size */
#define CVT_V1190_ROM_VERSION_DATA_SIZE			cvD16			/*!< \brief Purchased version of the Mod.V1190 data size */
#define CVT_V1190_ROM_BOARD_ID_2_DATA_SIZE		cvD16			/*!< \brief Board identifier (MSB) data size */
#define CVT_V1190_ROM_BOARD_ID_1_DATA_SIZE		cvD16			/*!< \brief Board identifier data size */
#define CVT_V1190_ROM_BOARD_ID_0_DATA_SIZE		cvD16			/*!< \brief Board identifier (LSB) data size */
#define CVT_V1190_ROM_REVISION_3_DATA_SIZE		cvD16			/*!< \brief Hardware revision identifier data size */
#define CVT_V1190_ROM_REVISION_2_DATA_SIZE		cvD16			/*!< \brief Hardware revision identifier data size */
#define CVT_V1190_ROM_REVISION_1_DATA_SIZE		cvD16			/*!< \brief Hardware revision identifier data size */
#define CVT_V1190_ROM_REVISION_0_DATA_SIZE		cvD16			/*!< \brief Hardware revision identifier data size */
#define CVT_V1190_ROM_SERIAL_1_DATA_SIZE		cvD16			/*!< \brief Serial number (MSB) data size */
#define CVT_V1190_ROM_SERIAL_0_DATA_SIZE		cvD16			/*!< \brief Serial number (LSB) data size */

////////////////////////////////////////////////////////////////////////////////////////////////
// Registers address modifiers
////////////////////////////////////////////////////////////////////////////////////////////////
#define CVT_V1190_OUT_BUFFER_AM					cvA32_S_MBLT	/*!< \brief Output buffer address modifier */
#define CVT_V1190_CONTROL_AM					cvA32_S_DATA	/*!< \brief Control register address modifier */
#define CVT_V1190_STATUS_AM						cvA32_S_DATA	/*!< \brief Status register address modifier */
#define CVT_V1190_INT_LEVEL_AM					cvA32_S_DATA	/*!< \brief Interrupt level register data size */
#define CVT_V1190_INT_VECTOR_AM					cvA32_S_DATA	/*!< \brief Interrupt vector register data size */
#define CVT_V1190_GEO_ADDRESS_AM				cvA32_S_DATA	/*!< \brief Geo Address register data size */
#define CVT_V1190_MCST_CBLT_ADDRESS_AM			cvA32_S_DATA	/*!< \brief MCST/CBLT Base Address register data size */
#define CVT_V1190_MCST_CBLT_CTRL_AM				cvA32_S_DATA	/*!< \brief MCST/CBLT Control register data size */
#define CVT_V1190_MOD_RESET_AM					cvA32_S_DATA	/*!< \brief Module reset register address modifier */
#define CVT_V1190_SW_CLEAR_AM					cvA32_S_DATA	/*!< \brief Software clear register address modifier */
#define CVT_V1190_SW_EVENT_RESET_AM				cvA32_S_DATA	/*!< \brief Software event reset register address modifier */
#define CVT_V1190_SW_TRIGGER_AM					cvA32_S_DATA	/*!< \brief Software trigger register address modifier */
#define CVT_V1190_EVENT_COUNTER_AM				cvA32_S_DATA	/*!< \brief Event counter register address modifier */
#define CVT_V1190_EVENT_STORED_AM				cvA32_S_DATA	/*!< \brief Event stored register address modifier */
#define CVT_V1190_ALMOST_FULL_LVL_AM			cvA32_S_DATA	/*!< \brief Almost full level register address modifier */
#define CVT_V1190_BLT_EVENT_NUM_AM				cvA32_S_DATA	/*!< \brief BLT event number register address modifier */
#define CVT_V1190_FW_REV_AM						cvA32_S_DATA	/*!< \brief Firmware revision register address modifier */
#define CVT_V1190_TESTREG_AM					cvA32_S_DATA	/*!< \brief Testreg register address modifier */
#define CVT_V1190_OUT_PROG_CTRL_AM				cvA32_S_DATA	/*!< \brief Output prog control register address modifier */
#define CVT_V1190_MICRO_AM						cvA32_S_DATA	/*!< \brief Micro register address modifier */
#define CVT_V1190_MICRO_HND_AM					cvA32_S_DATA	/*!< \brief Micro handshake register address modifier */
#define CVT_V1190_SEL_FLASH_AM					cvA32_S_DATA	/*!< \brief Select Flash register address modifier */
#define CVT_V1190_FLASH_AM						cvA32_S_DATA	/*!< \brief Flash register address modifier */
#define CVT_V1190_COMP_SRAM_PAGE_AM				cvA32_S_DATA	/*!< \brief Compensation SRAM Page register address modifier */
#define CVT_V1190_EVENT_FIFO_AM					cvA32_S_DATA	/*!< \brief Event FIFO register address modifier */
#define CVT_V1190_EVENT_FIFO_STORED_AM			cvA32_S_DATA	/*!< \brief Event FIFO stored register address modifier */
#define CVT_V1190_EVENT_FIFO_STATUS_AM			cvA32_S_DATA	/*!< \brief Event FIFO status register address modifier */
#define CVT_V1190_DUMMY32_AM					cvA32_S_DATA	/*!< \brief Dummy 32 register address modifier */
#define CVT_V1190_DUMMY16_AM					cvA32_S_DATA	/*!< \brief Dummy 16 register address modifier */
#define CVT_V1190_ROM_OUI_2_AM					cvA32_S_DATA	/*!< \brief Manufacturer identifier (IEEE OUI) (MSB) address modifier */
#define CVT_V1190_ROM_OUI_1_AM					cvA32_S_DATA	/*!< \brief Manufacturer identifier (IEEE OUI) address modifier */
#define CVT_V1190_ROM_OUI_0_AM					cvA32_S_DATA	/*!< \brief Manufacturer identifier (IEEE OUI) (LSB) address modifier */
#define CVT_V1190_ROM_VERSION_AM				cvA32_S_DATA	/*!< \brief Purchased version of the Mod.V1190 address modifier */
#define CVT_V1190_ROM_BOARD_ID_2_AM				cvA32_S_DATA	/*!< \brief Board identifier (MSB) address modifier */
#define CVT_V1190_ROM_BOARD_ID_1_AM				cvA32_S_DATA	/*!< \brief Board identifier address modifier */
#define CVT_V1190_ROM_BOARD_ID_0_AM				cvA32_S_DATA	/*!< \brief Board identifier (LSB) address modifier */
#define CVT_V1190_ROM_REVISION_3_AM				cvA32_S_DATA	/*!< \brief Hardware revision identifier address modifier */
#define CVT_V1190_ROM_REVISION_2_AM				cvA32_S_DATA	/*!< \brief Hardware revision identifier address modifier */
#define CVT_V1190_ROM_REVISION_1_AM				cvA32_S_DATA	/*!< \brief Hardware revision identifier address modifier */
#define CVT_V1190_ROM_REVISION_0_AM				cvA32_S_DATA	/*!< \brief Hardware revision identifier address modifier */
#define CVT_V1190_ROM_SERIAL_1_AM				cvA32_S_DATA	/*!< \brief Serial number (MSB) address modifier */
#define CVT_V1190_ROM_SERIAL_0_AM				cvA32_S_DATA	/*!< \brief Serial number (LSB) address modifier */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_REG_INDEX
*   \brief   The registers indexes
*            
*            Provides an entry for each register: This is the index into the CVT_V1190_REG_TABLE board table
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_OUT_BUFFER_INDEX,					/*!< \brief Output buffer index */
	CVT_V1190_CONTROL_INDEX,					/*!< \brief Control register index */
	CVT_V1190_STATUS_INDEX,						/*!< \brief Status register index */
	CVT_V1190_INT_LEVEL_INDEX,					/*!< \brief Interrupt level register index */
	CVT_V1190_INT_VECTOR_INDEX,					/*!< \brief Interrupt vector register index */
	CVT_V1190_GEO_ADDRESS_INDEX,				/*!< \brief Geo Address register index */
	CVT_V1190_MCST_CBLT_ADDRESS_INDEX,			/*!< \brief MCST/CBLT Base Address register index */
	CVT_V1190_MCST_CBLT_CTRL_INDEX,				/*!< \brief MCST/CBLT Control register index */
	CVT_V1190_MOD_RESET_INDEX,					/*!< \brief Module reset register index */
	CVT_V1190_SW_CLEAR_INDEX,					/*!< \brief Software clear register index */
	CVT_V1190_SW_EVENT_RESET_INDEX,				/*!< \brief Software event reset register index */
	CVT_V1190_SW_TRIGGER_INDEX,					/*!< \brief Software trigger register index */
	CVT_V1190_EVENT_COUNTER_INDEX,				/*!< \brief Event counter register index */
	CVT_V1190_EVENT_STORED_INDEX,				/*!< \brief Event stored register index */
	CVT_V1190_ALMOST_FULL_LVL_INDEX,			/*!< \brief Almost full level register index */
	CVT_V1190_BLT_EVENT_NUM_INDEX,				/*!< \brief BLT event number register index */
	CVT_V1190_FW_REV_INDEX,						/*!< \brief Firmware revision register index */
	CVT_V1190_TESTREG_INDEX,					/*!< \brief Testreg register index */
	CVT_V1190_OUT_PROG_CTRL_INDEX,				/*!< \brief Output prog control register index */
	CVT_V1190_MICRO_INDEX,						/*!< \brief Micro register index */
	CVT_V1190_MICRO_HND_INDEX,					/*!< \brief Micro handshake register index */
	CVT_V1190_SEL_FLASH_INDEX,					/*!< \brief Select Flash register index */
	CVT_V1190_FLASH_INDEX,						/*!< \brief Flash register index */
	CVT_V1190_COMP_SRAM_PAGE_INDEX,				/*!< \brief Compensation SRAM Page register index */
	CVT_V1190_EVENT_FIFO_INDEX,					/*!< \brief Event FIFO register index */
	CVT_V1190_EVENT_FIFO_STORED_INDEX,			/*!< \brief Event FIFO stored register index */
	CVT_V1190_EVENT_FIFO_STATUS_INDEX,			/*!< \brief Event FIFO status register index */
	CVT_V1190_DUMMY32_INDEX,					/*!< \brief Dummy 32 register index */
	CVT_V1190_DUMMY16_INDEX,					/*!< \brief Dummy 16 register index */
	CVT_V1190_ROM_OUI_2_INDEX,					/*!< \brief Manufacturer identifier (IEEE OUI) (MSB) index */
	CVT_V1190_ROM_OUI_1_INDEX,					/*!< \brief Manufacturer identifier (IEEE OUI) index */
	CVT_V1190_ROM_OUI_0_INDEX,					/*!< \brief Manufacturer identifier (IEEE OUI) (LSB) index */
	CVT_V1190_ROM_VERSION_INDEX,				/*!< \brief Purchased version of the Mod.V1190 index */
	CVT_V1190_ROM_BOARD_ID_2_INDEX,				/*!< \brief Board identifier (MSB) index */
	CVT_V1190_ROM_BOARD_ID_1_INDEX,				/*!< \brief Board identifier index */
	CVT_V1190_ROM_BOARD_ID_0_INDEX,				/*!< \brief Board identifier (LSB) index */
	CVT_V1190_ROM_REVISION_3_INDEX,				/*!< \brief Hardware revision identifier index */
	CVT_V1190_ROM_REVISION_2_INDEX,				/*!< \brief Hardware revision identifier index */
	CVT_V1190_ROM_REVISION_1_INDEX,				/*!< \brief Hardware revision identifier index */
	CVT_V1190_ROM_REVISION_0_INDEX,				/*!< \brief Hardware revision identifier index */
	CVT_V1190_ROM_SERIAL_1_INDEX,				/*!< \brief Serial number (MSB) index */
	CVT_V1190_ROM_SERIAL_0_INDEX,				/*!< \brief Serial number (LSB) index */
} CVT_V1190_REG_INDEX;

////////////////////////////////////////////////////////////////////////////////////////////////
// Micro register opcodes
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_MICRO_OPCODES
*   \brief   Micro opcodes
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Micro register opcodes: ACQUISITION MODE
	////////////////////////////////////////////////////////////////////////////////////////////////
	CVT_V1190_TRG_MATCH_OPCODE					= 0x0000,		/*!< \brief Trigger matching mode micro opcode */
	CVT_V1190_CONT_STORE_OPCODE					= 0x0100,		/*!< \brief Continuos storage micro opcode */
	CVT_V1190_READ_ACQ_MOD_OPCODE				= 0x0200,		/*!< \brief Read acquisition mode micro opcode */
	CVT_V1190_SET_KEEP_TOKEN_OPCODE				= 0x0300,		/*!< \brief Set keep_token micro opcode */
	CVT_V1190_CLEAR_KEEP_TOKEN_OPCODE			= 0x0400,		/*!< \brief Clear keep_token micro opcode */
	CVT_V1190_LOAD_DEF_CONFIG_OPCODE			= 0x0500,		/*!< \brief Load default configuration micro opcode */
	CVT_V1190_SAVE_USER_CONFIG_OPCODE			= 0x0600,		/*!< \brief Save User configuration micro opcode */
	CVT_V1190_LOAD_USER_CONFIG_OPCODE			= 0x0700,		/*!< \brief Load User configuration micro opcode */
	CVT_V1190_AUTOLOAD_USER_CONFIG_OPCODE		= 0x0800,		/*!< \brief Set auto load User configuration micro opcode */
	CVT_V1190_AUTOLOAD_DEF_CONFIG_OPCODE		= 0x0900,		/*!< \brief Set auto load default configuration micro opcode */

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Micro register opcodes: TRIGGER
	////////////////////////////////////////////////////////////////////////////////////////////////
	CVT_V1190_SET_WIN_WIDTH_OPCODE				= 0x1000,		/*!< \brief Set window width micro opcode */
	CVT_V1190_SET_WIN_OFFSET_OPCODE				= 0x1100,		/*!< \brief Set window offset micro opcode */
	CVT_V1190_SET_SW_MARGIN_OPCODE				= 0x1200,		/*!< \brief Set extra search margin micro opcode */
	CVT_V1190_SET_REJ_MARGIN_OPCODE				= 0x1300,		/*!< \brief Set reject margin micro opcode */
	CVT_V1190_EN_SUB_TRG_OPCODE					= 0x1400,		/*!< \brief Enable subtraction of trigger time micro opcode */
	CVT_V1190_DIS_SUB_TRG_OPCODE				= 0x1500,		/*!< \brief Disable subtraction of trigger time micro opcode */
	CVT_V1190_READ_TRG_CONF_OPCODE				= 0x1600,		/*!< \brief Read trigger configuration micro opcode */

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Micro register opcodes: TDC EDGE DETECTION & RESOLUTION
	////////////////////////////////////////////////////////////////////////////////////////////////
	CVT_V1190_SET_DETECTION_OPCODE				= 0x2200,		/*!< \brief Enable paired meas. leading/ trailing edge micro opcode */
	CVT_V1190_READ_DETECTION_OPCODE				= 0x2300,		/*!< \brief Read edge detection configuration micro opcode */
	CVT_V1190_SET_TR_LEAD_LSB_OPCODE			= 0x2400,		/*!< \brief Set LSB of leading/trailing edge micro opcode */
	CVT_V1190_SET_PAIR_RES_OPCODE				= 0x2500,		/*!< \brief Set leading time and width res. when pair micro opcode */
	CVT_V1190_READ_RES_OPCODE					= 0x2600,		/*!< \brief Read resolution micro opcode */
	CVT_V1190_SET_DEAD_TIME_OPCODE				= 0x2800,		/*!< \brief Set channel dead time between hits micro opcode */
	CVT_V1190_READ_DEAD_TIME_OPCODE				= 0x2900,		/*!< \brief Read channel dead time between hits micro opcode */

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Micro register opcodes: TDC READOUT
	////////////////////////////////////////////////////////////////////////////////////////////////
	CVT_V1190_EN_HEAD_TRAILER_OPCODE			= 0x3000,		/*!< \brief Enable TDC header and trailer micro opcode */
	CVT_V1190_DIS_HEAD_TRAILER_OPCODE			= 0x3100,		/*!< \brief Disable TDC header and trailer micro opcode */
	CVT_V1190_READ_HEAD_TRAILER_OPCODE			= 0x3200,		/*!< \brief Read status TDC header and trailer micro opcode */
	CVT_V1190_SET_EVENT_SIZE_OPCODE				= 0x3300,		/*!< \brief Set maximum number of hits per event micro opcode */
	CVT_V1190_READ_EVENT_SIZE_OPCODE			= 0x3400,		/*!< \brief Read maximum number of hits per event micro opcode */
	CVT_V1190_EN_ERROR_MARK_OPCODE				= 0x3500,		/*!< \brief Enable TDC error mark micro opcode */
	CVT_V1190_DIS_ERROR_MARK_OPCODE				= 0x3600,		/*!< \brief Disable TDC error mark micro opcode */
	CVT_V1190_EN_ERROR_BYPASS_OPCODE			= 0x3700,		/*!< \brief Enable bypass TDC if error micro opcode */
	CVT_V1190_DIS_ERROR_BYPASS_OPCODE			= 0x3800,		/*!< \brief Disable bypass TDC if error micro opcode */
	CVT_V1190_SET_ERROR_TYPES_OPCODE			= 0x3900,		/*!< \brief Set TDC internal error type micro opcode */
	CVT_V1190_READ_ERROR_TYPES_OPCODE			= 0x3A00,		/*!< \brief Read TDC internal error type micro opcode */
	CVT_V1190_SET_FIFO_SIZE_OPCODE				= 0x3B00,		/*!< \brief Set effective size of readout FIFO micro opcode */
	CVT_V1190_READ_FIFO_SIZE_OPCODE				= 0x3C00,		/*!< \brief Read effective size of readout FIFO micro opcode */

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Micro register opcodes: CHANNEL ENABLE
	////////////////////////////////////////////////////////////////////////////////////////////////
	CVT_V1190_EN_CHANNEL_OPCODE					= 0x4000,		/*!< \brief Enable channel nn micro opcode */
	CVT_V1190_DIS_CHANNEL_OPCODE				= 0x4100,		/*!< \brief Disable channel nn micro opcode */
	CVT_V1190_EN_ALL_CH_OPCODE					= 0x4200,		/*!< \brief Enable all channels micro opcode */
	CVT_V1190_DIS_ALL_CH_OPCODE					= 0x4300,		/*!< \brief Disable all channels micro opcode */
	CVT_V1190_WRITE_EN_PATTERN_OPCODE			= 0x4400,		/*!< \brief Write enable pattern for channels micro opcode */
	CVT_V1190_READ_EN_PATTERN_OPCODE			= 0x4500,		/*!< \brief Read enable pattern for channels micro opcode */
	CVT_V1190_WRITE_EN_PATTERN32_OPCODE			= 0x4600,		/*!< \brief Write 32 bit enable pattern for channels micro opcode */
	CVT_V1190_READ_EN_PATTERN32_OPCODE			= 0x4700,		/*!< \brief Read 32 bit enable pattern for channels micro opcode */

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Micro register opcodes: ADJUST
	////////////////////////////////////////////////////////////////////////////////////////////////
	CVT_V1190_SET_GLOB_OFFSET_OPCODE			= 0x5000,		/*!< \brief Set global offset micro opcode */
	CVT_V1190_READ_GLOB_OFFSET_OPCODE			= 0x5100,		/*!< \brief Read global offset micro opcode */
	CVT_V1190_SET_ADJUST_CH_OPCODE				= 0x5200,		/*!< \brief Set channel nn adjust micro opcode */
	CVT_V1190_READ_ADJUST_CH_OPCODE				= 0x5300,		/*!< \brief Read channel nn adjust micro opcode */
	CVT_V1190_SET_RC_ADJ_OPCODE					= 0x5400,		/*!< \brief Set RC adjust of tdc 0n micro opcode */
	CVT_V1190_READ_RC_ADJ_OPCODE				= 0x5500,		/*!< \brief Read RC adjust of tdc 0n micro opcode */
	CVT_V1190_SAVE_RC_ADJ_OPCODE				= 0x5600,		/*!< \brief Save RC adjust on EEPROM micro opcode */

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Micro register opcodes: MISCELLANEOUS
	////////////////////////////////////////////////////////////////////////////////////////////////
	CVT_V1190_READ_TDC_ID_OPCODE				= 0x6000,		/*!< \brief Read programmed ID of TDC 0n micro opcode */
	CVT_V1190_READ_MICRO_REV_OPCODE				= 0x6100,		/*!< \brief Read firmware revision of microcontroller micro opcode */
	CVT_V1190_RESET_DLL_PLL_OPCODE				= 0x6200,		/*!< \brief Reset DLL and PLL micro opcode */

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Micro register opcodes: ADVANCED
	////////////////////////////////////////////////////////////////////////////////////////////////
	CVT_V1190_WRITE_SETUP_REG_OPCODE			= 0x7000,		/*!< \brief Write word nn into the scan path setup micro opcode */
	CVT_V1190_READ_SETUP_REG_OPCODE				= 0x7100,		/*!< \brief Read word nn into the scan path setup micro opcode */
	CVT_V1190_UPDATE_SETUP_REG_OPCODE			= 0x7200,		/*!< \brief Load the scan path setup micro opcode */
	CVT_V1190_DEFAULT_SETUP_REG_OPCODE			= 0x7300,		/*!< \brief Reload the default scan path setup micro opcode */
	CVT_V1190_READ_ERROR_STATUS_OPCODE			= 0x7400,		/*!< \brief Read errors in the TDC 0n status micro opcode */
	CVT_V1190_READ_DLL_LOCK_OPCODE				= 0x7500,		/*!< \brief Read the DLL LOCK bit of the TDC 0n micro opcode */
	CVT_V1190_READ_STATUS_STREAM_OPCODE			= 0x7600,		/*!< \brief Read the TDC 0n status micro opcode */
	CVT_V1190_UPDATE_SETUP_TDC_OPCODE			= 0x7700,		/*!< \brief Load the scan path setup on TDC nn micro opcode */

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Micro register opcodes: DEBUG AND TEST
	////////////////////////////////////////////////////////////////////////////////////////////////
	CVT_V1190_WRITE_EEPROM_OPCODE				= 0xC000,		/*!< \brief Write 1 byte into the EEPROM micro opcode */
	CVT_V1190_READ_EEPROM_OPCODE				= 0xC100,		/*!< \brief Read 1 byte from the EEPROM micro opcode */
	CVT_V1190_MICROCONTROLLER_FW_OPCODE			= 0xC200,		/*!< \brief Read the µcontroller firmware revision/date micro opcode */
	CVT_V1190_WRITE_SPARE_OPCODE				= 0xC300,		/*!< \brief Write a 16 bit spare variable micro opcode */
	CVT_V1190_READ_SPARE_OPCODE					= 0xC400,		/*!< \brief Read a 16 bit spare variable micro opcode */
	CVT_V1190_EN_TEST_MODE_OPCODE				= 0xC500,		/*!< \brief Enable TDC test mode micro opcode */
	CVT_V1190_DIS_TEST_MODE_OPCODE				= 0xC600,		/*!< \brief Disable TDC test mode micro opcode */
	CVT_V1190_SET_TDC_TEST_OUTPUT_OPCODE		= 0xC700,		/*!< \brief Set TDC 0n signal test output micro opcode */
	CVT_V1190_SET_DLL_CLOCK_OPCODE				= 0xC800,		/*!< \brief Set DLL clock source micro opcode */
	CVT_V1190_READ_TDC_SETUP_SCAN_PATH_OPCODE	= 0xC800,		/*!< \brief Read all Setup Scan Path on TDC 0n micro opcode */

} CVT_V1190_MICRO_OPCODES;

////////////////////////////////////////////////////////////////////////////////////////////////
// Micro Handshake bitmasks
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_MICRO_HND_BIT_MSK
*   \brief   Micro Handshake register bitmasks
*            
*            Provides a bitmask for any relevant bit of the Micro Handshake register
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_MICRO_HND_WRITEOK_MSK					= 0x0001,		/*!< \brief Micro write ok mask */
	CVT_V1190_MICRO_HND_READOK_MSK					= 0x0002,		/*!< \brief Micro read ok mask */	
} CVT_V1190_MICRO_HND_BIT_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_CONTROL_MSK
*   \brief   V1190 Control register masks
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_CTRL_BERR_ENABLE_MSK					= 0x0001,		/*!< Set Bus error enable bit. */
	CVT_V1190_CTRL_TERM_MSK							= 0x0002,		/*!< Set the software termination status. */
	CVT_V1190_CTRL_TERM_SW_MSK						= 0x0004,		/*!< Allows to select the termination mode. */
	CVT_V1190_CTRL_EMPTY_EVENT_MSK					= 0x0008,		/*!< Allows to choose if writing the Global Header and the Global Trailer when there are no data from the TDCs. */
	CVT_V1190_CTRL_ALIGN64_MSK						= 0x0010,		/*!< Align 64 bit */
	CVT_V1190_CTRL_COMPENSATION_ENABLE_MSK			= 0x0020,		/*!< Compensation of the INL enable bit. */
	CVT_V1190_CTRL_TEST_FIFO_ENABLE_MSK				= 0x0040,		/*!< Output Buffer test mode enable bit. */
	CVT_V1190_CTRL_READ_COMPENSATION_SRAM_ENABLE_MSK= 0x0080,		/*!< Enable reoadout for the sram where the compensation table is written. */
	CVT_V1190_CTRL_EVENT_FIFO_ENABLE_MSK			= 0x0100,		/*!< Event FIFO enable bit. */
	CVT_V1190_CTRL_TRIGGER_TIME_TAG_ENABLE_MSK		= 0x0200,		/*!< Trigger Time Tag Writing on event enable bit. */
} CVT_V1190_CONTROL_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_STATUS_MSK
*   \brief   V1190 status register masks
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_STS_DREADY_MSK					= 0x0001,		/*!< Event Ready or Data Ready. */
	CVT_V1190_STS_ALMOST_FULL_MSK				= 0x0002,		/*!< There are at least Almost Full Level words in the Output Buffer. */
	CVT_V1190_STS_FULL_MSK						= 0x0004,		/*!< The Output Buffer is FULL. */
	CVT_V1190_STS_TRG_MATCH_MSK					= 0x0008,		/*!< Indicates the selected operating mode. */
	CVT_V1190_STS_HEADER_EN_MSK					= 0x0010,		/*!< TDCs’ Header and TRAILER enabled. */
	CVT_V1190_STS_TERM_ON_MSK					= 0x0020,		/*!< All Control Bus Terminations are ON. */
	CVT_V1190_STS_ERROR_0_MSK					= 0x0040,		/*!< TDC 0 error has occurred. */
	CVT_V1190_STS_ERROR_1_MSK					= 0x0080,		/*!< TDC 1 error has occurred. */
	CVT_V1190_STS_ERROR_2_MSK					= 0x0100,		/*!< TDC 2 error has occurred. */
	CVT_V1190_STS_ERROR_3_MSK					= 0x0200,		/*!< TDC 3 error has occurred. */
	CVT_V1190_STS_BERR_FLAG_MSK					= 0x0400,		/*!< a Bus Error has occurred. */
	CVT_V1190_STS_PURGED_MSK					= 0x0800,		/*!< Board purged. */
	CVT_V1190_STS_RES_0_MSK						= 0x1000,		/*!< Resolution bit 0. */
	CVT_V1190_STS_RES_1_MSK						= 0x2000,		/*!< Resolution bit 1. */
	CVT_V1190_STS_PAIR_MODE_MSK					= 0x4000,		/*!< Module in pair mode */
	CVT_V1190_STS_TRIGGER_LOST_MSK				= 0x8000,		/*!< One trigger at least was not sent to the TDCs */
} CVT_V1190_STATUS_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_STATUS_RES
*   \brief   V1190 status register resolution
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_STS_RES_800PS						= 0x0000,		/*!< 800 ps. (V1190 Only) */
	CVT_V1190_STS_RES_200PS						= 0x0001,		/*!< 200 ps. (V1190 Only) */
	CVT_V1190_STS_RES_100PS						= 0x0002,		/*!< 100 ps. (V1190 Only) */
	CVT_V1190_STS_RES_25PS						= 0x0003,		/*!<  25 ps. (V1290 Only) */
} CVT_V1190_STATUS_RES;

#define CVT_V1190_STS_RES_MSK					0x3000																							/*!< CVT_V1190_STATUS register resolution bitmask. */
#define CVT_V1190_GET_STATUS_RES( reg)			((((UINT16)reg)& CVT_V1190_STS_RES_MSK)>> 12)													/*!< \brief Extract the resolution from UINT16 value */
#define CVT_V1190_SET_STATUS_RES( reg, value)	reg= (((UINT16)reg)& ~CVT_V1190_STS_RES_MSK)| ((((UINT16)value)<< 12)&CVT_V1190_STS_RES_MSK)	/*!< \brief Sets the resolution into UINT16 value */

#define CVT_V1190_STS_ERROR_MSK					0x03C0																							/*!< CVT_V1190_STATUS register error bitmask. */
#define CVT_V1190_GET_STATUS_ERROR( reg)		((((UINT16)reg)& CVT_V1190_STS_ERROR_MSK)>> 6)													/*!< \brief Extract the error bitmask from UINT16 value */
#define CVT_V1190_SET_STATUS_ERROR( reg, value)	reg= (((UINT16)reg)& ~CVT_V1190_STS_ERROR_MSK)| ((((UINT16)value)<< 6)& CVT_V1190_STS_ERROR_MSK)/*!< \brief Sets the error bitmask into UINT16 value */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_EDGE_DETECTION_ENUM
*   \brief   V1190 edge detection mode enumeration
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_ED_PAIR_MODE						= 0,			/*!< Pair mode. (V1190 Only)*/
	CVT_V1190_ED_TRAILING_ONLY					= 1,			/*!< Trailing only. */
	CVT_V1190_ED_LEADING_ONLY					= 2,			/*!< Leading only. */
	CVT_V1190_ED_TRAILING_AND_LEADING			= 3,			/*!< Trailing and Leading. */
} CVT_V1190_EDGE_DETECTION_ENUM;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_TR_LEAD_LSB_ENUM
*   \brief   V1190 edge detection mode enumeration
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_TLL_800PS							= 0,			/*!< 800 ps. (V1190 Only) */
	CVT_V1190_TLL_200PS							= 1,			/*!< 200 ps. (V1190 Only) */
	CVT_V1190_TLL_100PS							= 2,			/*!< 100 ps. (V1190 Only) */
	CVT_V1190_TLL_25PS							= 3,			/*!<  25 ps. (V1290 Only) */
} CVT_V1190_TR_LEAD_LSB_ENUM;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_PAIR_RES_LEADING_TIME_ENUM
*   \brief   V1190 Set/read leading time resolution when pair enumeration
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_PRLT_100PS						= 0x0000,		/*!< 100 ps. */
	CVT_V1190_PRLT_200PS						= 0x0001,		/*!< 200 ps. */
	CVT_V1190_PRLT_400PS						= 0x0002,		/*!< 400 ps. */
	CVT_V1190_PRLT_800PS						= 0x0003,		/*!< 800 ps. */
	CVT_V1190_PRLT_1_6NS						= 0x0004,		/*!< 1.6 ns. */
	CVT_V1190_PRLT_3_12NS						= 0x0005,		/*!< 3.12 ns. */
	CVT_V1190_PRLT_6_25NS						= 0x0006,		/*!< 6.25 ns. */
	CVT_V1190_PRLT_12_5NS						= 0x0007,		/*!< 12.5 ns. */
} CVT_V1190_PAIR_RES_LEADING_TIME_ENUM;

#define CVT_V1190_PRLT_MSK										0x0007																			/*!< CVT_V1190_PAIR_RES register leading time significant bitmask */
#define CVT_V1190_GET_PAIR_RES_LEADING_TIME( reg)				((UINT8)(((UINT16)reg)& CVT_V1190_PRLT_MSK))									/*!< \brief Extract the leading time from UINT16 value */
#define CVT_V1190_SET_PAIR_RES_LEADING_TIME( reg, value)		reg= (((UINT16)reg)& ~CVT_V1190_PRLT_MSK)| ((UINT16)value& CVT_V1190_PRLT_MSK)	/*!< \brief Sets the leading time into UINT16 value */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_PAIR_RES_WIDTH_ENUM
*   \brief   V1190 Set/read width resolution (when edge detection is pair) enumeration
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_PRW_100PS							= 0x0000,		/*!< 100 ps. */
	CVT_V1190_PRW_200PS							= 0x0001,		/*!< 200 ps. */
	CVT_V1190_PRW_400PS							= 0x0002,		/*!< 400 ps. */
	CVT_V1190_PRW_800PS							= 0x0003,		/*!< 800 ps. */
	CVT_V1190_PRW_1_6NS							= 0x0004,		/*!< 1.6 ns. */
	CVT_V1190_PRW_3_12NS						= 0x0005,		/*!< 3.12 ns. */
	CVT_V1190_PRW_6_25NS						= 0x0006,		/*!< 6.25 ns. */
	CVT_V1190_PRW_12_5NS						= 0x0007,		/*!< 12.5 ns. */
	CVT_V1190_PRW_25NS							= 0x0008,		/*!< 25 ns. */
	CVT_V1190_PRW_50NS							= 0x0009,		/*!< 50 ns. */
	CVT_V1190_PRW_100NS							= 0x000A,		/*!< 100 ns. */
	CVT_V1190_PRW_200NS							= 0x000B,		/*!< 200 ns. */
	CVT_V1190_PRW_400NS							= 0x000C,		/*!< 400 ns. */
	CVT_V1190_PRW_800NS							= 0x000D,		/*!< 800 ns. */
} CVT_V1190_PAIR_RES_WIDTH_ENUM;

#define CVT_V1190_PRW_MSK						  0x0F00		/*!< CVT_V1190_PAIR_RES register resolution significant bitmask */
#define CVT_V1190_GET_PAIR_RES_WITH( reg)		  ((UINT8)((((UINT16)reg)& CVT_V1190_PRW_MSK)>> 8))				/*!< \brief Extract the resolution from UINT16 value */
#define CVT_V1190_SET_PAIR_RES_WITH( reg, value)  reg= (((UINT16)reg)& ~CVT_V1190_PRW_MSK)| (((UINT16)value)<< 8)	/*!< \brief Sets the resolution into UINT16 value */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_DEAD_TIME_ENUM
*   \brief   V1190 Set/read dead time enumeration
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_DT_5NS							= 0,			/*!< 5 ns. */
	CVT_V1190_DT_10NS							= 1,			/*!< 10 ns. */
	CVT_V1190_DT_30NS							= 2,			/*!< 30 ns. */
	CVT_V1190_DT_100NS							= 3,			/*!< 100 ns. */
} CVT_V1190_DEAD_TIME_ENUM;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_EVENT_SIZE_ENUM
*   \brief   V1190 Set/read the maximun number of hits per event enumeration
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_ES_0								= 0,			/*!< 0 hits per event. */
	CVT_V1190_ES_1								= 1,			/*!< 1 hits per event. */
	CVT_V1190_ES_2								= 2,			/*!< 2 hits per event. */
	CVT_V1190_ES_4								= 3,			/*!< 4 hits per event. */
	CVT_V1190_ES_8								= 4,			/*!< 8 hits per event. */
	CVT_V1190_ES_16								= 5,			/*!< 16 hits per event. */
	CVT_V1190_ES_32								= 6,			/*!< 32 hits per event. */
	CVT_V1190_ES_64								= 7,			/*!< 64 hits per event. */
	CVT_V1190_ES_128							= 8,			/*!< 128 hits per event. */
	CVT_V1190_ES_NO_LIMIT						= 9,			/*!< no limits to hits per event. */
} CVT_V1190_EVENT_SIZE_ENUM;

////////////////////////////////////////////////////////////////////////////////////////////////
// Output buffer macros
////////////////////////////////////////////////////////////////////////////////////////////////
#define CVT_V1190_DATA_TYPE_MSK				0xf8000000		/*!< \brief Data type bit masks */

#define CVT_V1190_GLOBAL_HEADER				0x40000000		/*!< \brief Global header data type */
#define CVT_V1190_GLOBAL_TRAILER			0x80000000		/*!< \brief Global trailer data type */
#define CVT_V1190_TDC_HEADER				0x08000000		/*!< \brief TDC header data type */
#define CVT_V1190_TDC_MEASURE				0x00000000		/*!< \brief TDC measure data type */
#define CVT_V1190_TDC_ERROR					0x20000000		/*!< \brief TDC error data type */
#define CVT_V1190_TDC_TRAILER				0x18000000		/*!< \brief TDC trailer data type */
#define CVT_V1190_GLOBAL_TRIGGER_TIME		0x88000000		/*!< \brief Global trigger tag time data type */
#define CVT_V1190_FILLER					0xc0000000		/*!< \brief Filler data type */

#define CVT_V1190_GLB_HDR_MAX_EVENT_COUNT	(0x003fffff+ 1)	/*!< \brief Max Event count */
#define CVT_V1190_GLB_HDR_EVENT_COUNT_MSK	0x07ffffe0		/*!< \brief Global header event count msk */
#define CVT_V1190_GLB_HDR_GEO_MSK			0x0000001f		/*!< \brief Global header GEO msk */
#define CVT_V1190_GLB_TRG_TIME_TAG_MSK		0x07ffffff		/*!< \brief Global EXTENDED TRIGGER TIME TAG msk */
#define CVT_V1190_GLB_TRL_STATUS_MSK		0x07000000		/*!< \brief Global trailer STATUS msk */
#define CVT_V1190_GLB_TRL_WCOUNT_MSK		0x001fffe0		/*!< \brief Global trailer Word count  msk */
#define CVT_V1190_GLB_TRL_GEO_MSK			0x0000001f		/*!< \brief Global trailer GEO msk */

#define CVT_V1190_TDC_HDR_TDC_MSK			0x03000000		/*!< \brief TDC event header TDC msk */
#define CVT_V1190_TDC_HDR_EVENT_ID_MSK		0x00fff000		/*!< \brief TDC event header EVENT ID msk */
#define CVT_V1190_TDC_HDR_BUNCH_ID_MSK		0x00000fff		/*!< \brief TDC event header BUNCH ID msk */
#define CVT_V1190_TDC_MSR_TRAILING_MSK		0x04000000		/*!< \brief TDC measurement TRAILING msk */
#define CVT_V1190_TDC_MSR_CHANNEL_MSK		0x03f80000		/*!< \brief TDC measurement CHANNEL msk (for V1190) */
#define CVT_V1190_TDC_MSR_MEASURE_MSK		0x0007ffff		/*!< \brief TDC measurement MEASURE msk (for V1190) */
#define CVT_V1290_TDC_MSR_CHANNEL_MSK		0x03e00000		/*!< \brief TDC measurement CHANNEL msk (for V1290) */
#define CVT_V1290_TDC_MSR_MEASURE_MSK		0x001fffff		/*!< \brief TDC measurement MEASURE msk (for V1290) */
#define CVT_V1190_TDC_TRL_TDC_MSK			0x03000000		/*!< \brief TDC event trailer TDC msk */
#define CVT_V1190_TDC_TRL_EVENT_ID_MSK		0x00fff000		/*!< \brief TDC event trailer TDC msk */
#define CVT_V1190_TDC_TRL_WCOUNT_MSK		0x00000fff		/*!< \brief TDC event trailer WORD COUNT msk */
#define CVT_V1190_TDC_ERR_TDC_MSK			0x03000000		/*!< \brief TDC error TDC msk */
#define CVT_V1190_TDC_ERR_ERR_FLAGS_MSK		0x00003fff		/*!< \brief TDC error ERROR FLAGS msk */

#define CVT_V1190_IS_GLOBAL_HEADER(data)		((data& CVT_V1190_DATA_TYPE_MSK)== CVT_V1190_GLOBAL_HEADER)			/*!< \brief Checks if data type is global header */
#define CVT_V1190_IS_GLOBAL_TRAILER(data)		((data& CVT_V1190_DATA_TYPE_MSK)== CVT_V1190_GLOBAL_TRAILER)		/*!< \brief Checks if data type is global trailer */
#define CVT_V1190_IS_TDC_HEADER(data)			((data& CVT_V1190_DATA_TYPE_MSK)== CVT_V1190_TDC_HEADER)			/*!< \brief Checks if data type is TDC header */
#define CVT_V1190_IS_TDC_MEASURE(data)			((data& CVT_V1190_DATA_TYPE_MSK)== CVT_V1190_TDC_MEASURE)			/*!< \brief Checks if data type is TDC measure */
#define CVT_V1190_IS_TDC_ERROR(data)			((data& CVT_V1190_DATA_TYPE_MSK)== CVT_V1190_TDC_ERROR)				/*!< \brief Checks if data type is TDC error */
#define CVT_V1190_IS_TDC_TRAILER(data)			((data& CVT_V1190_DATA_TYPE_MSK)== CVT_V1190_TDC_TRAILER)			/*!< \brief Checks if data type is TDC trailer */
#define CVT_V1190_IS_GLOBAL_TRIGGER_TIME(data)	((data& CVT_V1190_DATA_TYPE_MSK)== CVT_V1190_GLOBAL_TRIGGER_TIME)	/*!< \brief Checks if data type is global trigger time */
#define CVT_V1190_IS_FILLER(data)				((data& CVT_V1190_DATA_TYPE_MSK)== CVT_V1190_FILLER)				/*!< \brief Checks if data type is filler */

#define CVT_V1190_GET_GLB_HDR_EVENT_COUNT(data)	((UINT32)((((UINT32)data)& CVT_V1190_GLB_HDR_EVENT_COUNT_MSK)>>5))		/*!< \brief Gets the global header event counter of this event */
#define CVT_V1190_GET_GLB_HDR_GEO(data)			((UINT32)(((UINT32)data)& CVT_V1190_GLB_HDR_GEO_MSK))					/*!< \brief Gets the global header GEO address of this event */

#define CVT_V1190_GET_GLB_TRG_TIME_TAG(data)	((UINT32)(((UINT32)data)& CVT_V1190_GLB_TRG_TIME_TAG_MSK))				/*!< \brief Gets the global trigger time tag */

#define CVT_V1190_GET_GLB_TRL_STATUS(data)		((UINT32)((((UINT32)data)& CVT_V1190_GLB_TRL_STATUS_MSK)>>24))			/*!< \brief Gets the global trailer status */
#define CVT_V1190_GET_GLB_TRL_WCOUNT(data)		((UINT32)((((UINT32)data)& CVT_V1190_GLB_TRL_WCOUNT_MSK)>>5))			/*!< \brief Gets the global trailer word counter counter */
#define CVT_V1190_GET_GLB_TRL_GEO(data)			((UINT32)(((UINT32)data)& CVT_V1190_GLB_TRL_GEO_MSK))					/*!< \brief Gets the global trailer GEO address */

#define CVT_V1190_GET_TDC_HDR_TDC(data)			((UINT32)((((UINT32)data)& CVT_V1190_TDC_HDR_TDC_MSK)>>24))				/*!< \brief Gets the TDC header TDC number */
#define CVT_V1190_GET_TDC_HDR_EVENT_ID(data)	((UINT32)((((UINT32)data)& CVT_V1190_TDC_HDR_EVENT_ID_MSK)>>12))		/*!< \brief Gets the TDC header event id */
#define CVT_V1190_GET_TDC_HDR_BUNCH_ID(data)	((UINT32)(((UINT32)data)& CVT_V1190_TDC_HDR_BUNCH_ID_MSK))				/*!< \brief Gets the TDC header bunch id */

#define CVT_V1190_GET_TDC_MSR_TRAILING(data)	((UINT32)((((UINT32)data)& CVT_V1190_TDC_MSR_TRAILING_MSK)>>26))		/*!< \brief Gets the TDC measurement TRAILING bit */
#define CVT_V1190_GET_TDC_MSR_CHANNEL(data)		((UINT32)((((UINT32)data)& CVT_V1190_TDC_MSR_CHANNEL_MSK)>>19))			/*!< \brief Gets the TDC measurement CHANNEL number (for V1190) */
#define CVT_V1190_GET_TDC_HDR_MEASURE(data)		((UINT32)(((UINT32)data)& CVT_V1190_TDC_MSR_MEASURE_MSK))				/*!< \brief Gets the TDC measurement measure value (for V1190) */
#define CVT_V1290_GET_TDC_MSR_CHANNEL(data)		((UINT32)((((UINT32)data)& CVT_V1290_TDC_MSR_CHANNEL_MSK)>>21))			/*!< \brief Gets the TDC measurement CHANNEL number (for V1290) */
#define CVT_V1290_GET_TDC_HDR_MEASURE(data)		((UINT32)(((UINT32)data)& CVT_V1290_TDC_MSR_MEASURE_MSK))				/*!< \brief Gets the TDC measurement measure value (for V1290) */

#define CVT_V1190_GET_TDC_TRL_TDC(data)			((UINT32)((((UINT32)data)& CVT_V1190_TDC_TRL_TDC_MSK)>>24))				/*!< \brief Gets the TDC trailer TDC */
#define CVT_V1190_GET_TDC_TRL_EVENT_ID(data)	((UINT32)((((UINT32)data)& CVT_V1190_TDC_TRL_EVENT_ID_MSK)>>12))		/*!< \brief Gets the TDC trailer event id */
#define CVT_V1190_GET_TDC_TRL_WCOUNT(data)		((UINT32)(((UINT32)data)& CVT_V1190_TDC_TRL_WCOUNT_MSK))				/*!< \brief Gets the TDC trailer word count */

#define CVT_V1190_GET_TDC_ERR_TDC(data)			((UINT32)((((UINT32)data)& CVT_V1190_TDC_ERR_TDC_MSK)>>24))				/*!< \brief Gets the TDC error TDC */
#define CVT_V1190_GET_TDC_ERR_ERR_FLAGS(data)	((UINT32)(((UINT32)data)& CVT_V1190_TDC_ERR_ERR_FLAGS_MSK))				/*!< \brief Gets the TDC error error flags */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_ERROR_TYPES_MSK
*   \brief   TDC internal error type bitmasks
*            
*            Provides a bitmask for any relevant error bit of the TDC
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_ET_VERNIER_ERROR_MSK					= 0x0001,		/*!< \brief Vernier error (DLL unlocked or excessive jitter) */
	CVT_V1190_ET_COARSE_ERROR_MSK					= 0x0002,		/*!< \brief Coarse error (parity error on coarse count) */
	CVT_V1190_ET_CHANNEL_SELECT_ERROR_MSK			= 0x0004,		/*!< \brief Channel select error (synchronisation error) */
	CVT_V1190_ET_L1_BUFFER_PARITY_ERROR_MSK			= 0x0008,		/*!< \brief L1 buffer parity error */
	CVT_V1190_ET_TRIGGER_FIFO_PARITY_ERROR_MSK		= 0x0010,		/*!< \brief Trigger fifo parity error */
	CVT_V1190_ET_TRIGGER_MATCHING_ERROR_MSK			= 0x0020,		/*!< \brief Trigger matching error (state error) */
	CVT_V1190_ET_READOUT_FIFO_PARITY_ERROR_MSK		= 0x0040,		/*!< \brief Readout fifo parity error */
	CVT_V1190_ET_READOUT_STATE_ERROR_MSK			= 0x0080,		/*!< \brief Readout state error */
	CVT_V1190_ET_SETUP_PARITY_ERROR_MSK				= 0x0100,		/*!< \brief Set up parity error */
	CVT_V1190_ET_CONTROL_PARITY_ERROR_MSK			= 0x0200,		/*!< \brief Control parity error */
	CVT_V1190_ET_JTAG_INSTRUCTION_PARITY_ERROR_MSK	= 0x0400,		/*!< \brief Jtag instruction parity error */
} CVT_V1190_ERROR_TYPES_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_FIFO_SIZE_ENUM
*   \brief   V1190 Set/read effective size of readout FIFO enumeration
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_FS_2								= 0,			/*!< 2 words. */
	CVT_V1190_FS_4								= 1,			/*!< 4 words. */
	CVT_V1190_FS_8								= 2,			/*!< 8 words. */
	CVT_V1190_FS_16								= 3,			/*!< 16 words. */
	CVT_V1190_FS_32								= 4,			/*!< 32 words. */
	CVT_V1190_FS_64								= 5,			/*!< 64 words. */
	CVT_V1190_FS_128							= 6,			/*!< 128 words. */
	CVT_V1190_FS_256							= 7,			/*!< 256 words. */
} CVT_V1190_FIFO_SIZE_ENUM;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_DLL_CLOCK_ENUM
*   \brief   V1190 Set/read DLL clock enumeration
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_DC_40MHZ							= 0,			/*!< direct 40 MHz clock (low resolution). */
	CVT_V1190_DC_PLL40MHZ						= 1,			/*!< from PLL 40 MHz clock (low resolution). */
	CVT_V1190_DC_PLL160MHZ						= 2,			/*!< from PLL 160 MHz clock (medium resolution). */
	CVT_V1190_DC_PLL320MHZ						= 3,			/*!< from PLL 320 MHz clock (high resolution). */
} CVT_V1190_DLL_CLOCK_ENUM;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1190_MCST_CBLT_CTRL_MSK
*   \brief   V1190 CVT_V1190/MCST Control register bit masks
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1190_MCCTRL_DISABLED_BOARD_MSK			= 0x0000,		/*!< Disabled Board mask */
	CVT_V1190_MCCTRL_LAST_BOARD_MSK				= 0x0001,		/*!< Last Board mask */
	CVT_V1190_MCCTRL_FIRST_BOARD_MSK			= 0x0002,		/*!< First Board mask */
	CVT_V1190_MCCTRL_MID_BOARD_MSK				= 0x0003,		/*!< Middle Board mask */
} CVT_V1190_MCST_CBLT_CTRL_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
// Global variables declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// Global methods declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     B O A R D S   H A N D L I N G
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_open( cvt_V1190_data* p_data, UINT16 base_address, long vme_handle, CVT_V1X90_TYPES type);
*   \brief   V1494 VME boards data initialization
*            
*            Provides specific handling for V495 boards opening.
*   \param   p_data Pointer to board data
*   \param   base_address The board base address (MSW)
*   \param   vme_handle The VME handle
*   \param   type The board type : it must be a \ref CVT_V1X90_TYPES value
*   \return  TRUE: board successfully opened
*   \note    Must be called before any other board specific API.
*   \sa      CVT_V1X90_TYPES 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_open( cvt_V1190_data* p_data, UINT16 base_address, long vme_handle, CVT_V1X90_TYPES type);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_close( cvt_V1190_data* p_data);
*   \brief   V1190 VME boards closing and resource free
*            
*            Provides specific handling for V1190 boards closing.
*   \param   p_data Pointer to board data
*   \return  TRUE: board successfully closed
*   \note    Must be called when done with any other board specific API.
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_close( cvt_V1190_data* p_data);

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
/*! \fn      BOOL cvt_V1190_write_2_micro( cvt_V1190_data* p_data, UINT16 ope_code, const UINT16* p_params, int num_params);
*   \brief   Writes an opcode to V1190 micro register.
*            
*            Writes an opcode to V1190 micro register and the specified number of parameters. 
*            Handles all the necessary handshake with micro to get the job done.
*   \param   p_data Pointer to board data
*   \param   ope_code The ope code to write 
*   \param   p_params Pointer to parameter buffer (caller allocated). May be NULL if num_params== 0
*   \param   num_params The number of parameters to write
*   \return  TRUE: Opcode write successfull
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_write_2_micro( cvt_V1190_data* p_data, UINT16 ope_code, const UINT16* p_params, int num_params);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_read_from_micro( cvt_V1190_data* p_data, UINT16 ope_code, UINT16* p_params, int num_params);
*   \brief   Reads an opcode from V1190 micro register.
*            
*            Reads an opcode to V1190 micro register and the specified number of parameters. 
*            Handles all the necessary handshake with micro to get the job done.
*   \param   p_data Pointer to board data
*   \param   ope_code The ope code to read
*   \param   p_params Pointer to parameter buffer (caller allocated). May be NULL if num_params== 0
*   \param   num_params The number of parameters to read
*   \return  TRUE: Opcode read successfull
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_read_from_micro( cvt_V1190_data* p_data, UINT16 ope_code, UINT16* p_params, int num_params);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_bitmask_control( cvt_V1190_data* p_data, CVT_V1190_CONTROL_MSK value);
*   \brief   Set a bitmask to control register.
*            
*            Sets the bits of the bitmask into the register. The bitmask is ORed to the actual regiter content
*   \param   p_data Pointer to board data
*   \param   value The bitmask to set : may be a combination of \ref CVT_V1190_CONTROL_MSK bitmask
*   \return  TRUE: Procedure successfully executed
*   \sa      CVT_V1190_CONTROL_MSK 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_bitmask_control( cvt_V1190_data* p_data, CVT_V1190_CONTROL_MSK value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_clear_bitmask_control( cvt_V1190_data* p_data, CVT_V1190_CONTROL_MSK value);
*   \brief   Clear a bitmask to control 1 register.
*            
*            Clears the bits of the bitmask into the register. The inverted bitmask is ANDed to the actual regiter content
*   \param   p_data Pointer to board data
*   \param   value The bitmask to clear: may be a combination of \ref CVT_V1190_CONTROL_MSK bitmask
*   \return  TRUE: Procedure successfully executed
*   \sa      CVT_V1190_CONTROL_MSK
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_clear_bitmask_control( cvt_V1190_data* p_data, CVT_V1190_CONTROL_MSK value);

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     L E V E L   2   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_windows_width( cvt_V1190_data* p_data, UINT16 value);
*   \brief   Set the window width.
*            
*            Writes the specified value through micro register opcode.
*   \param   p_data Pointer to board data
*   \param   value The value to set
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_windows_width( cvt_V1190_data* p_data, UINT16 value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_windows_offset( cvt_V1190_data* p_data, UINT16 value);
*   \brief   Set the window offset.
*            
*            Writes the specified value through micro register opcode.
*   \param   p_data Pointer to board data
*   \param   value The value to set
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_windows_offset( cvt_V1190_data* p_data, UINT16 value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_get_channel_enable( cvt_V1190_data* p_data, UINT16 *p_enable_msk);
*   \brief   Get the channel enable pattern.
*            
*            Reads the specified channel enable pattern through micro register opcode.
*   \param   p_data Pointer to board data
*   \param   p_enable_msk The channel enable pattern buffer. 
*            This is a user allocated buffer, providing storage for 
*            CVT_V1190_NUM_TDC_A*2, CVT_V1190_NUM_TDC_B*2, CVT_V1290_NUM_TDC_A/2, CVT_V1290_NUM_TDC_N/2 according to  board type ( \ref CVT_V1X90_TYPES)
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_get_channel_enable( cvt_V1190_data* p_data, UINT16 *p_enable_msk);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_trigger_match( cvt_V1190_data* p_data);
*   \brief   Set the trigger matching mode.
*            
*            Writes dummy value through micro register opcode to set the trigger matching mode.
*   \param   p_data Pointer to board data
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_trigger_match( cvt_V1190_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_head_trail_enable( cvt_V1190_data* p_data);
*   \brief   Enable TDC Header and Trailer in readout
*            
*            Writes through micro register opcode to enable TDC Header and Trailer in readout.
*   \param   p_data Pointer to board data
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_head_trail_enable( cvt_V1190_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_head_trail_disable( cvt_V1190_data* p_data);
*   \brief   Disable TDC Header and Trailer in readout
*            
*            Writes through micro register opcode to disable TDC Header and Trailer in readout.
*   \param   p_data Pointer to board data
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_head_trail_disable( cvt_V1190_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_read_MEB( cvt_V1190_data* p_data, void* p_buff, UINT32* p_buff_size);
*   \brief   Reads data from the Multiple event buffer and stores to user buffer
*            
*            Call cvt_FIFO_BLT_read for Multiple event buffer and stores data into user buffer.
*            If the returned data is just a V1190 filler, this is discarded.
*   \param   p_data Pointer to board data
*   \param   p_buff The target buffer: caller allocated
*   \param   p_buff_size The buffer size (bytes). On exit will holds the number of bytes really read.
*                         If just a filler data will be read this will be discarded
*   \return  TRUE: Procedure successfully executed
*   \sa      cvt_FIFO_BLT_read
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_read_MEB( cvt_V1190_data* p_data, void* p_buff, UINT32* p_buff_size);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_continuous_acquisition_mode( cvt_V1190_data* p_data, CVT_V1190_EDGE_DETECTION_ENUM edge_detection, CVT_V1190_PAIR_RES_WIDTH_ENUM res_width, const UINT16 *p_enable_msk);
*   \brief   Enable and setups the continuous acquisition mode
*            
*            Setups the relevant parameters for continuous acquisition mode.
*   \param   p_data Pointer to board data
*   \param   edge_detection The edge detection type. Must be a valid \ref CVT_V1190_EDGE_DETECTION_ENUM
*   \param   res_width The resolution width. Must be a valid \ref CVT_V1190_PAIR_RES_WIDTH_ENUM 
*                      This parameter is ignored for V1290X boards
*   \param   p_enable_msk The channel enable pattern buffer. 
*            This is a user allocated buffer, providing storage for 
*            CVT_V1190_NUM_TDC_A*2, CVT_V1190_NUM_TDC_B*2, CVT_V1290_NUM_TDC_A/2, CVT_V1290_NUM_TDC_N/2 according to  board type ( \ref CVT_V1X90_TYPES)
*            It may be NULL (i.e. if you don't need to setup channel enable patterns). 
*   \return  TRUE: Procedure successfully executed
*   \sa      CVT_V1190_EDGE_DETECTION_ENUM
*   \sa      CVT_V1190_PAIR_RES_WIDTH_ENUM 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_continuous_acquisition_mode( cvt_V1190_data* p_data, CVT_V1190_EDGE_DETECTION_ENUM edge_detection, CVT_V1190_PAIR_RES_WIDTH_ENUM res_width, const UINT16 *p_enable_msk);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_trigger_matching_acquisition_mode( cvt_V1190_data* p_data, INT16 window_width, INT16 window_offset, INT16 extra_search_margin, INT16 reject_margin, CVT_V1190_EDGE_DETECTION_ENUM edge_detection, CVT_V1190_PAIR_RES_WIDTH_ENUM res_width, const UINT16 *p_enable_msk, BOOL header_trailer_enable, BOOL empty_event_enable, BOOL trigger_time_tag_enable);
*   \brief   Enable and setups the trigger matching mode
*            
*            Setups the relevant parameters for trigger matching mode usage.
*   \param   p_data Pointer to board data
*   \param   window_width Sets the width of the match window (a negative value means don't change).
*   \param   window_offset Sets the offset of the match window with respect to the trigger itself (a negative value means don't change)
*   \param   extra_search_margin Sets the extra search field of the match window (a negative value means don't change).
*   \param   reject_margin Sets the reject margin, expressed in clock cycles (a negative value means don't change).
*   \param   edge_detection The edge detection type. Must be a valid \ref CVT_V1190_EDGE_DETECTION_ENUM
*   \param   res_width The resolution width. Must be a valid \ref CVT_V1190_PAIR_RES_WIDTH_ENUM 
*                      This parameter is ignored for V1290X boards
*   \param   p_enable_msk The channel enable pattern buffer. 
*            This is a user allocated buffer, providing storage for 
*            CVT_V1190_NUM_TDC_A*2, CVT_V1190_NUM_TDC_B*2, CVT_V1290_NUM_TDC_A/2, CVT_V1290_NUM_TDC_N/2 according to  board type ( \ref CVT_V1X90_TYPES)
*            It may be NULL (i.e. if you don't need to setup channel enable patterns). 
*   \param   header_trailer_enable Enable/disable header and trailer.
*   \param   empty_event_enable Enable/disable empty event storage.
*   \param   trigger_time_tag_enable Enable/disable the trigger time tag.
*   \return  TRUE: Procedure successfully executed 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_trigger_matching_acquisition_mode( cvt_V1190_data* p_data, INT16 window_width, INT16 window_offset, INT16 extra_search_margin, INT16 reject_margin, CVT_V1190_EDGE_DETECTION_ENUM edge_detection, CVT_V1190_PAIR_RES_WIDTH_ENUM res_width, const UINT16 *p_enable_msk, BOOL header_trailer_enable, BOOL empty_event_enable, BOOL trigger_time_tag_enable);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_interrupt( cvt_V1190_data* p_data, UINT8 level, UINT8 vector);
*   \brief   Setups interrupt parameters.
*            
*            Setups the relevant parameters for interrupt usage.
*   \param   p_data Pointer to board data
*   \param   level The interrupt level.
*   \param   vector The interrupt vector.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_interrupt( cvt_V1190_data* p_data, UINT8 level, UINT8 vector);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_readout_mode( cvt_V1190_data* p_data, BOOL bus_error_enable, BOOL align64_enable, UINT8 blt_event_number);
*   \brief   Setups data readout mode parameters.
*            
*            Setups the relevant parameters for data readout.
*   \param   p_data Pointer to board data
*   \param   bus_error_enable Enable bus error: the module is enabled to generate a Bus error to finish a block transfer. 
*   \param   align64_enable Enable align 64: the module is enabled to add dummy word when the number of words is odd.
*   \param   blt_event_number The number of complete events to transfer via BLT
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_readout_mode( cvt_V1190_data* p_data, BOOL bus_error_enable, BOOL align64_enable, UINT8 blt_event_number);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_get_status( cvt_V1190_data* p_data, BOOL *p_is_data_ready, BOOL *p_is_term_on, BOOL *p_is_buffer_full, BOOL *p_is_buffer_almost_full, CVT_V1190_STATUS_RES* p_resolution, UINT8* p_error_bitmask);
*   \brief   Gets information about board status.
*            
*   \param   p_data Pointer to board data
*   \param   p_is_data_ready Returns TRUE if data is ready. 
*   \param   p_is_term_on Returns TRUE if term bit is on. 
*   \param   p_is_buffer_full Returns TRUE if buffer is full. 
*   \param   p_is_buffer_almost_full Returns TRUE if buffer is almost full. 
*   \param   p_resolution Returns the resolution 
*   \param   p_error_bitmask Returns the TDC bitmask error: if bit i is 1 then the TDCi is on error
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_get_status( cvt_V1190_data* p_data, BOOL *p_is_data_ready, BOOL *p_is_term_on, BOOL *p_is_buffer_full, BOOL *p_is_buffer_almost_full, CVT_V1190_STATUS_RES* p_resolution, UINT8* p_error_bitmask);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_get_event_counter( cvt_V1190_data* p_data, UINT32* p_counter);
*   \brief   Gets the event counter value.
*            
*            Gets the event counter actual value.
*   \param   p_data Pointer to board data
*   \param   p_counter Pointer to the counter value.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_get_event_counter( cvt_V1190_data* p_data, UINT32* p_counter);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_get_event_stored( cvt_V1190_data* p_data, UINT16* p_counter);
*   \brief   Gets the event stored value.
*            
*            Gets the event stored actual value.
*   \param   p_data Pointer to board data
*   \param   p_counter Pointer to the counter value.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_get_event_stored( cvt_V1190_data* p_data, UINT16* p_counter);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_get_system_info( cvt_V1190_data* p_data, UINT16 *p_firmware_rev, UINT32 *p_tdc_id_buff, UINT16 *p_micro_firmware_rev, UINT16 *p_serial_number);
*   \brief   Gets board's system information.
*            
*            Reads the firmware revision register, TDC revs etc.
*   \param   p_data Pointer to board data
*   \param   p_firmware_rev The firmware release (MSB major release, LSB minor release).
*   \param   p_tdc_id_buff The TDC IDs buffer This is a user allocated buffer, providing storage for CVT_V1190_NUM_TDC_# words according to the board type (\ref CVT_V1X90_TYPES). p_tdc_id_buff[#] format is: MSB major release, LSB minor release.
*   \param   p_micro_firmware_rev The micro firmware release (MSB major release, LSB minor release).
*   \param   p_serial_number The serial number.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_get_system_info( cvt_V1190_data* p_data, UINT16 *p_firmware_rev, UINT32 *p_tdc_id_buff, UINT16 *p_micro_firmware_rev, UINT16 *p_serial_number);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_data_clear( cvt_V1190_data* p_data);
*   \brief   Performs the data clear.
*            
*            Writes a dummy value to the software clear register.
*   \param   p_data Pointer to board data
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_data_clear( cvt_V1190_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_module_reset( cvt_V1190_data* p_data);
*   \brief   Performs the module reset.
*            
*            Writes a dummy value to the module reset register.
*   \param   p_data Pointer to board data
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_module_reset( cvt_V1190_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_channel_enable( cvt_V1190_data* p_data, const UINT16* p_enable_msk);
*   \brief   Set the channel enable mask.
*            
*            Writes the specified channel enable pattern through micro register opcode.
*   \param   p_data Pointer to board data
*   \param   p_enable_msk The enable masks' array. This is a user allocated buffer, providing storage for 
*                    CVT_V1190_NUM_TDC_A*2, CVT_V1190_NUM_TDC_B*2, CVT_V1290_NUM_TDC_A/2, CVT_V1290_NUM_TDC_N/2 according to  board type ( \ref CVT_V1X90_TYPES)
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_channel_enable( cvt_V1190_data* p_data, const UINT16* p_enable_msk);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_almost_full( cvt_V1190_data* p_data, UINT16 almost_full_value);
*   \brief   Sets the almost full level register.
*            
*            Writes the specified value into the almost full level register. 
*            This Register allows the User to set the Almost Full Level of the Output Buffer. 
*            When the Output Buffer contains a number of words at least equal to the Almost Full Level, then an
*            Interrupt Request (IRQ) is generated (if enabled) and the related bit in the Status Register is set.
*   \param   p_data Pointer to board data
*   \param   almost_full_value The almost full level value.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_almost_full( cvt_V1190_data* p_data, UINT16 almost_full_value);

#ifdef CVT_V1190_USE_DATA_QUEUE

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_peek_event( cvt_V1190_data *p_data, UINT32 *out_buff, long *p_out_buff_size, UINT32 *p_event_count);
*   \brief   Tries to peek (i.e. copy but not removing) an event from queue and save data to output buffer
*            
*            Scans the queue beginning from m_queue_ini, searching for an event block, and stores data output stream. 
*   \param   p_data Pointer to board data
*   \param   out_buff Pointer to output buffer
*   \param   p_out_buff_size  Size of out_buff (UINT32). The number of data written into out_buff (UINT32) on exit.
*   \param   p_event_count The found event count
*   \return  TRUE: some event found, FALSE elsewhere
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_peek_event( cvt_V1190_data *p_data, UINT32 *out_buff, long *p_out_buff_size, UINT32 *p_event_count);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_inqueue( cvt_V1190_data* p_data, const UINT32* in_buff, UINT32 in_buff_size);
*   \brief   Tries to put in_buff_size data word to queue
*            
*            Checks for the queue available free words and stores data beginning from m_queue_end. 
*            m_queue_end will be update
*   \param   p_data Pointer to board data
*   \param   in_buff Pointer to input buffer
*   \param   in_buff_size  Size of in_buff (UINT32)
*   \return  TRUE: data stored correctly FALSE elsewhere (e.g. queue overflow)
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_inqueue( cvt_V1190_data* p_data, const UINT32* in_buff, UINT32 in_buff_size);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_dequeue( cvt_V1190_data* p_data, UINT32 *out_buff, UINT32 out_buff_size);
*   \brief   Tries to get out_buff_size data word from the queue
*            
*            Checks for queue available data words and gets data beginning from m_queue_ini. 
*            m_queue_ini will be update: if out_buff!= NULL the data will be stored into it.
*   \param   p_data Pointer to board data
*   \param   out_buff Pointer to output buffer (may be NULL)
*   \param   out_buff_size  Size of out_buff (UINT32)
*   \return  TRUE: data removed correctly, FALSE elsewhere (e.g. queue underflow)
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_dequeue( cvt_V1190_data* p_data, UINT32 *out_buff, UINT32 out_buff_size);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      long cvt_V1190_get_queue_free( cvt_V1190_data* p_data);
*   \brief   Gets the number of free queue space (words)
*            
*   \param   p_data Pointer to board data
*   \return  The number of free queue space (UINT32 words)
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API long cvt_V1190_get_queue_free( cvt_V1190_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      long cvt_V1190_get_queue_length( cvt_V1190_data* p_data);
*   \brief   Gets the queue length
*            
*   \param   p_data Pointer to board data
*   \return  The queue length (UINT32 words)
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API long cvt_V1190_get_queue_length( cvt_V1190_data* p_data);

#endif  // CVT_V1190_USE_DATA_QUEUE

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1190_set_MCST_CBLT( cvt_V1190_data* p_data, UINT8 address, MCST_CBLT_board_pos pos);
*   \brief   Setups MCST/CBLT parameters this board.
*            
*            Setups the relevant parameters for MCST/CBLT usage.
*   \param   p_data Pointer to board data.
*   \param   address The MCST/CBLT address.
*   \param   pos The board position into the MCST / CBLT chain: it must be a \ref MCST_CBLT_board_pos identifier
*   \return  TRUE: Procedure successfully executed
*   \sa      MCST_CBLT_board_pos
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1190_set_MCST_CBLT( cvt_V1190_data* p_data, UINT8 address, MCST_CBLT_board_pos pos);

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     M I S C E L L A N E O U S   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      const char* cvt_V1190_SW_rev( void);
*   \brief   Returns the SDK software release
*            
*   \return  const char*: The SDK revision string
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API const char* cvt_V1190_SW_rev( void);

#endif  // __CVT_V1190_DEF_H
