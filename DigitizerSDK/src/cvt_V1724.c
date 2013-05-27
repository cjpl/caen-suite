////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file    cvt_V1724.c
*   \brief   V1724 VME board implementation
*   \author  NDA
*   \version 1.0
*   \date    10/2006
*            
*            Provides methods, properties and defines to handle V1724 VME boards
*/
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// File includes
////////////////////////////////////////////////////////////////////////////////////////////////
#include <memory.h>
#include <string.h>
#include "cvt_V1724.h"


////////////////////////////////////////////////////////////////////////////////////////////////
// File local defines
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
// Static variables declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \var     static const cvt_reg_table CVT_V1724_REG_TABLE[]
*   \brief   The board registers table
*            
*            Provides an entry for each declared register: keep synched with \ref CVT_V792_REG_INDEX
*/
////////////////////////////////////////////////////////////////////////////////////////////////
static const cvt_reg_table CVT_V1724_REG_TABLE[ CVT_V1724_LAST_INDEX]=
{
//
// Readout Buffer
	{CVT_V1724_OUT_BUFFER_ADD,				CVT_V1724_OUT_BUFFER_AM,				CVT_V1724_OUT_BUFFER_DATA_SIZE},					/*!< \brief Output buffer register */

//
// Channel broadcast registers
	{CVT_V1724_BROAD_CH_CTRL_ADD,			CVT_V1724_BROAD_CH_CTRL_AM,				CVT_V1724_BROAD_CH_CTRL_DATA_SIZE},					/*!< \brief Control channel broadcast register */
	{CVT_V1724_BROAD_CH_SET_CTRL_ADD,		CVT_V1724_BROAD_CH_SET_CTRL_AM,			CVT_V1724_BROAD_CH_SET_CTRL_DATA_SIZE},				/*!< \brief Set control channel broadcast register */
	{CVT_V1724_BROAD_CH_CLEAR_CTRL_ADD,		CVT_V1724_BROAD_CH_CLEAR_CTRL_AM,		CVT_V1724_BROAD_CH_CLEAR_CTRL_DATA_SIZE},			/*!< \brief Clear control channel broadcast register */
	{CVT_V1724_BROAD_NUM_BLOCK_ADD,			CVT_V1724_BROAD_NUM_BLOCK_AM,			CVT_V1724_BROAD_NUM_BLOCK_DATA_SIZE},				/*!< \brief Number of blocks broadcast register */
	{CVT_V1724_BROAD_CH_BUFF_FLUSH_ADD,		CVT_V1724_BROAD_CH_BUFF_FLUSH_AM,		CVT_V1724_BROAD_CH_BUFF_FLUSH_DATA_SIZE},			/*!< \brief Number of buffers to be removed channel broadcast register */
	{CVT_V1724_BROAD_CH_RND_ACC_ADD,		CVT_V1724_BROAD_CH_RND_ACC_AM,			CVT_V1724_BROAD_CH_RND_ACC_DATA_SIZE},				/*!< \brief Parameters to Random access  channel broadcast register */
	{CVT_V1724_BROAD_CH_CUSSIZE_ADD,		CVT_V1724_BROAD_CH_CUSSIZE_AM,			CVT_V1724_BROAD_CH_CUSSIZE_DATA_SIZE},				/*!< \brief Zero suppression threshold channel broadcast register */
	{CVT_V1724_BROAD_CH_ZSTH_ADD,			CVT_V1724_BROAD_CH_ZSTH_AM,				CVT_V1724_BROAD_CH_ZSTH_DATA_SIZE},					/*!< \brief Zero suppression threshold channel broadcast register */
	{CVT_V1724_BROAD_ADC_CONF_ADD,			CVT_V1724_BROAD_ADC_CONF_AM,			CVT_V1724_BROAD_ADC_CONF_DATA_SIZE},				/*!< \brief ADC configuration broadcast register (Write only)*/

//
// VME registers
	{CVT_V1724_ACQ_CONTROL_ADD,				CVT_V1724_ACQ_CONTROL_AM,				CVT_V1724_ACQ_CONTROL_DATA_SIZE},					/*!< \brief Acquisiton Control register */
	{CVT_V1724_ACQ_STATUS_ADD,				CVT_V1724_ACQ_STATUS_AM,				CVT_V1724_ACQ_STATUS_DATA_SIZE},					/*!< \brief Acquisiton Status register */
	{CVT_V1724_SW_TRIGGER_ADD,				CVT_V1724_SW_TRIGGER_AM,				CVT_V1724_SW_TRIGGER_DATA_SIZE},					/*!< \brief Software trigger register */
	{CVT_V1724_TRIGGER_SRC_ENABLE_ADD,		CVT_V1724_TRIGGER_SRC_ENABLE_AM,		CVT_V1724_TRIGGER_SRC_ENABLE_DATA_SIZE},			/*!< \brief Trigger source enable register */
	{CVT_V1724_FP_TRIGGER_OUT_ENABLE_ADD,	CVT_V1724_FP_TRIGGER_OUT_ENABLE_AM,		CVT_V1724_FP_TRIGGER_OUT_ENABLE_DATA_SIZE},			/*!< \brief Front panel trigger out enable mask register */
	{CVT_V1724_POST_TRIG_ADD,				CVT_V1724_POST_TRIG_AM,					CVT_V1724_POST_TRIG_DATA_SIZE},						/*!< \brief Post trigger register */
	{CVT_V1724_FRONT_PANEL_IO_ADD,			CVT_V1724_FRONT_PANEL_IO_AM,			CVT_V1724_FRONT_PANEL_IO_DATA_SIZE},				/*!< \brief Front panel IO register */
	{CVT_V1724_FRONT_PANEL_IO_CTRL_ADD,		CVT_V1724_FRONT_PANEL_IO_CTRL_AM,		CVT_V1724_FRONT_PANEL_IO_CTRL_DATA_SIZE},			/*!< \brief Front panel IO Control register */
	{CVT_V1724_CH_ENABLE_ADD,				CVT_V1724_CH_ENABLE_AM,					CVT_V1724_CH_ENABLE_DATA_SIZE},						/*!< \brief Channel enable mask register */
	{CVT_V1724_FW_REV_ADD,					CVT_V1724_FW_REV_AM,					CVT_V1724_FW_REV_DATA_SIZE},						/*!< \brief Firmware Revision register */
	{CVT_V1724_DOWNSAMPLE_FACT_ADD,			CVT_V1724_DOWNSAMPLE_FACT_AM,			CVT_V1724_DOWNSAMPLE_FACT_DATA_SIZE},				/*!< \brief DownSample factor register */
	{CVT_V1724_EVENT_STORED_ADD,			CVT_V1724_EVENT_STORED_AM,				CVT_V1724_EVENT_STORED_DATA_SIZE},					/*!< \brief Event stored register */
	{CVT_V1724_MON_SET_ADD,					CVT_V1724_MON_SET_AM,					CVT_V1724_MON_SET_DATA_SIZE},						/*!< \brief Monitor output set register */
	{CVT_V1724_SW_SYNC_ADD,					CVT_V1724_SW_SYNC_AM,					CVT_V1724_SW_SYNC_DATA_SIZE},						/*!< \brief Sw sync register */
	{CVT_V1724_BOARD_INFO_ADD,				CVT_V1724_BOARD_INFO_AM,				CVT_V1724_BOARD_INFO_DATA_SIZE},					/*!< \brief Board's information register */
	{CVT_V1724_MON_MODE_ADD,				CVT_V1724_MON_MODE_AM,					CVT_V1724_MON_MODE_DATA_SIZE},						/*!< \brief Monitor output mode register */
	{CVT_V1724_TEST_IO_ADD,				    CVT_V1724_TEST_IO_AM,					CVT_V1724_TEST_IO_DATA_SIZE},						/*!< \brief Monitor output mode register */

	{CVT_V1724_VME_CONTROL_ADD,				CVT_V1724_VME_CONTROL_AM,				CVT_V1724_VME_CONTROL_DATA_SIZE},					/*!< \brief VME Control register */
	{CVT_V1724_VME_STATUS_ADD,				CVT_V1724_VME_STATUS_AM,				CVT_V1724_VME_STATUS_DATA_SIZE},					/*!< \brief VME Status register */
	{CVT_V1724_BOARD_ID_ADD,				CVT_V1724_BOARD_ID_AM,					CVT_V1724_BOARD_ID_DATA_SIZE},						/*!< \brief Geo Address register */
	{CVT_V1724_MCST_CBLT_ADD_CTRL_ADD,		CVT_V1724_MCST_CBLT_ADD_CTRL_AM,		CVT_V1724_MCST_CBLT_ADD_CTRL_DATA_SIZE},			/*!< \brief MCST/CBLT Address and control register */
	{CVT_V1724_RELOCATION_ADDRESS_ADD,		CVT_V1724_RELOCATION_ADDRESS_AM,		CVT_V1724_RELOCATION_ADDRESS_DATA_SIZE},			/*!< \brief Relocation address register */
	{CVT_V1724_INT_STATUS_ID_ADD,			CVT_V1724_INT_STATUS_ID_AM,				CVT_V1724_INT_STATUS_ID_DATA_SIZE},					/*!< \brief Interrupt status id register */
	{CVT_V1724_INT_EVENT_NUM_ADD,			CVT_V1724_INT_EVENT_NUM_AM,				CVT_V1724_INT_EVENT_NUM_DATA_SIZE},					/*!< \brief Interrupt event number register */
	{CVT_V1724_BLT_EVENT_NUM_ADD,			CVT_V1724_BLT_EVENT_NUM_AM,				CVT_V1724_BLT_EVENT_NUM_DATA_SIZE},					/*!< \brief BLT event number register */
	{CVT_V1724_SCRATCH_ADD,					CVT_V1724_SCRATCH_AM,					CVT_V1724_SCRATCH_DATA_SIZE},						/*!< \brief Scratch register */
	{CVT_V1724_SW_RESET_ADD,				CVT_V1724_SW_RESET_AM,					CVT_V1724_SW_RESET_DATA_SIZE},						/*!< \brief Software reset register */
	{CVT_V1724_SW_CLEAR_ADD,				CVT_V1724_SW_CLEAR_AM,					CVT_V1724_SW_CLEAR_DATA_SIZE},						/*!< \brief Software clear register */
	{CVT_V1724_FLASH_EN_ADD,				CVT_V1724_FLASH_EN_AM,					CVT_V1724_FLASH_EN_DATA_SIZE},						/*!< \brief Flash enable */
	{CVT_V1724_FLASH_DATA_ADD,				CVT_V1724_FLASH_DATA_AM,				CVT_V1724_FLASH_DATA_DATA_SIZE},					/*!< \brief Flash data */
	{CVT_V1724_RELOAD_CONFIG_ADD,			CVT_V1724_RELOAD_CONFIG_AM,				CVT_V1724_RELOAD_CONFIG_DATA_SIZE},					/*!< \brief Configuration Reload address modifier */
	{CVT_V1724_BASE_ADDRESS_ADD,			CVT_V1724_BASE_ADDRESS_AM,				CVT_V1724_BASE_ADDRESS_DATA_SIZE},					/*!< \brief Base Address address modifier */
	{CVT_V1724_ROM_CHKSUM_ADD,				CVT_V1724_ROM_CHKSUM_AM,				CVT_V1724_ROM_CHKSUM_DATA_SIZE},					/*!< \brief Configuration ROM checksum data size */
	{CVT_V1724_ROM_CHKSUM_LEN_2_ADD,		CVT_V1724_ROM_CHKSUM_LEN_2_AM,			CVT_V1724_ROM_CHKSUM_LEN_2_DATA_SIZE},				/*!< \brief Configuration ROM checksum length (MSB) data size */
	{CVT_V1724_ROM_CHKSUM_LEN_1_ADD,		CVT_V1724_ROM_CHKSUM_LEN_1_AM,			CVT_V1724_ROM_CHKSUM_LEN_1_DATA_SIZE},				/*!< \brief Configuration ROM checksum length data size */
	{CVT_V1724_ROM_CHKSUM_LEN_0_ADD,		CVT_V1724_ROM_CHKSUM_LEN_0_AM,			CVT_V1724_ROM_CHKSUM_LEN_0_DATA_SIZE},				/*!< \brief Configuration ROM checksum length (LSB) data size */
	{CVT_V1724_ROM_CONST_2_ADD,				CVT_V1724_ROM_CONST_2_AM,				CVT_V1724_ROM_CONST_2_DATA_SIZE},					/*!< \brief Configuration ROM constant (MSB) data size */
	{CVT_V1724_ROM_CONST_1_ADD,				CVT_V1724_ROM_CONST_1_AM,				CVT_V1724_ROM_CONST_1_DATA_SIZE},					/*!< \brief Configuration ROM constant data size */
	{CVT_V1724_ROM_CONST_0_ADD,				CVT_V1724_ROM_CONST_0_AM,				CVT_V1724_ROM_CONST_0_DATA_SIZE},					/*!< \brief Configuration ROM constant (LSB) data size */
	{CVT_V1724_ROM_C_CODE_ADD,				CVT_V1724_ROM_C_CODE_AM,				CVT_V1724_ROM_C_CODE_DATA_SIZE},					/*!< \brief Configuration ROM c_code data size */
	{CVT_V1724_ROM_R_CODE_ADD,				CVT_V1724_ROM_R_CODE_AM,				CVT_V1724_ROM_R_CODE_DATA_SIZE},					/*!< \brief Configuration ROM r_code data size */
	{CVT_V1724_ROM_OUI_2_ADD,				CVT_V1724_ROM_OUI_2_AM,					CVT_V1724_ROM_OUI_2_DATA_SIZE},						/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) (MSB) data size */
	{CVT_V1724_ROM_OUI_1_ADD,				CVT_V1724_ROM_OUI_1_AM,					CVT_V1724_ROM_OUI_1_DATA_SIZE},						/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) data size */
	{CVT_V1724_ROM_OUI_0_ADD,				CVT_V1724_ROM_OUI_0_AM,					CVT_V1724_ROM_OUI_0_DATA_SIZE},						/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) (LSB) data size */
	{CVT_V1724_ROM_VERSION_ADD,				CVT_V1724_ROM_VERSION_AM,				CVT_V1724_ROM_VERSION_DATA_SIZE},					/*!< \brief Configuration ROM Purchased version of the Mod.V1724 data size */
	{CVT_V1724_ROM_BOARD_ID_2_ADD,			CVT_V1724_ROM_BOARD_ID_2_AM,			CVT_V1724_ROM_BOARD_ID_2_DATA_SIZE},				/*!< \brief Configuration ROM Board identifier (MSB) data size */
	{CVT_V1724_ROM_BOARD_ID_1_ADD,			CVT_V1724_ROM_BOARD_ID_1_AM,			CVT_V1724_ROM_BOARD_ID_1_DATA_SIZE},				/*!< \brief Configuration ROM Board identifier data size */
	{CVT_V1724_ROM_BOARD_ID_0_ADD,			CVT_V1724_ROM_BOARD_ID_0_AM,			CVT_V1724_ROM_BOARD_ID_0_DATA_SIZE},				/*!< \brief Configuration ROM Board identifier (LSB) data size */
	{CVT_V1724_ROM_REVISION_3_ADD,			CVT_V1724_ROM_REVISION_3_AM,			CVT_V1724_ROM_REVISION_3_DATA_SIZE},				/*!< \brief Configuration ROM Hardware revision identifier data size */
	{CVT_V1724_ROM_REVISION_2_ADD,			CVT_V1724_ROM_REVISION_2_AM,			CVT_V1724_ROM_REVISION_2_DATA_SIZE},				/*!< \brief Configuration ROM Hardware revision identifier data size */
	{CVT_V1724_ROM_REVISION_1_ADD,			CVT_V1724_ROM_REVISION_1_AM,			CVT_V1724_ROM_REVISION_1_DATA_SIZE},				/*!< \brief Configuration ROM Hardware revision identifier data size */
	{CVT_V1724_ROM_REVISION_0_ADD,			CVT_V1724_ROM_REVISION_0_AM,			CVT_V1724_ROM_REVISION_0_DATA_SIZE},				/*!< \brief Configuration ROM Hardware revision identifier data size */
	{CVT_V1724_ROM_SERIAL_1_ADD,			CVT_V1724_ROM_SERIAL_1_AM,				CVT_V1724_ROM_SERIAL_1_DATA_SIZE},					/*!< \brief Configuration ROM Serial number (MSB) data size */
	{CVT_V1724_ROM_SERIAL_0_ADD,			CVT_V1724_ROM_SERIAL_0_AM,				CVT_V1724_ROM_SERIAL_0_DATA_SIZE},					/*!< \brief Configuration ROM Serial number (LSB) data size */
	{CVT_V1724_ROM_VCXO_TYPE_ADD,			CVT_V1724_ROM_VCXO_TYPE_AM,				CVT_V1724_ROM_VCXO_TYPE_DATA_SIZE},					/*!< \brief Configuration ROM Serial VCXO type data size */

//
// CH 0
	{CVT_V1724_CH0_RESERVED_RND_ACC_ADD,	CVT_V1724_CH0_RESERVED_RND_ACC_AM,		CVT_V1724_CH0_RESERVED_RND_ACC_DATA_SIZE},			/*!< \brief CH 0 Read Block channel broadcast reserved register */
	{CVT_V1724_CH0_ZSTH_ADD,				CVT_V1724_CH0_ZSTH_AM,					CVT_V1724_CH0_ZSTH_DATA_SIZE},						/*!< \brief CH 0 Zero suppression threshold register */
	{CVT_V1724_CH0_THRESHOLD_ADD,			CVT_V1724_CH0_THRESHOLD_AM,				CVT_V1724_CH0_THRESHOLD_DATA_SIZE},					/*!< \brief CH 0 Threshold register */
	{CVT_V1724_CH0_TIME_OVER_UNDER_THR_ADD,	CVT_V1724_CH0_TIME_OVER_UNDER_THR_AM,	CVT_V1724_CH0_TIME_OVER_UNDER_THR_DATA_SIZE},		/*!< \brief CH 0 Over/Under Threshold Samples register */
	{CVT_V1724_CH0_STATUS_ADD,				CVT_V1724_CH0_STATUS_AM,				CVT_V1724_CH0_STATUS_DATA_SIZE},					/*!< \brief CH 0 status register */
	{CVT_V1724_CH0_FW_REV_ADD,				CVT_V1724_CH0_FW_REV_AM,				CVT_V1724_CH0_FW_REV_DATA_SIZE},					/*!< \brief CH 0 firmware revision register */
	{CVT_V1724_CH0_BUFF_OCCUPANCY_ADD,		CVT_V1724_CH0_BUFF_OCCUPANCY_AM,		CVT_V1724_CH0_BUFF_OCCUPANCY_DATA_SIZE},			/*!< \brief CH 0 Number of Buffers Filled register */
	{CVT_V1724_CH0_DAC_CONF_ADD,			CVT_V1724_CH0_DAC_CONF_AM,				CVT_V1724_CH0_DAC_CONF_DATA_SIZE},					/*!< \brief CH 0 DAC Data Configuration register */
	{CVT_V1724_CH0_ADC_CONF_ADD,			CVT_V1724_CH0_ADC_CONF_AM,				CVT_V1724_CH0_ADC_CONF_DATA_SIZE},					/*!< \brief CH 0 Configuration register */
	{CVT_V1724_CH0_RESERVED_ADC_DEBUG_ADD,	CVT_V1724_CH0_RESERVED_ADC_DEBUG_AM,	CVT_V1724_CH0_RESERVED_ADC_DEBUG_DATA_SIZE},		/*!< \brief CH 0 ADC Debug Reserved register */
	{CVT_V1724_CH0_RESERVED_MEM_DATA_ADD,	CVT_V1724_CH0_RESERVED_MEM_DATA_AM,		CVT_V1724_CH0_RESERVED_MEM_DATA_DATA_SIZE},			/*!< \brief CH 0 Memory test data Reserved register */
	{CVT_V1724_CH0_RESERVED_MEM_ADDRESS_ADD,CVT_V1724_CH0_RESERVED_MEM_ADDRESS_AM,	CVT_V1724_CH0_RESERVED_MEM_ADDRESS_DATA_SIZE},		/*!< \brief CH 0 Memory test address Reserved register */

//
// CH 1
	{CVT_V1724_CH1_RESERVED_RND_ACC_ADD,	CVT_V1724_CH1_RESERVED_RND_ACC_AM,		CVT_V1724_CH1_RESERVED_RND_ACC_DATA_SIZE},			/*!< \brief CH 1 Read Block channel broadcast reserved register */
	{CVT_V1724_CH1_ZSTH_ADD,				CVT_V1724_CH1_ZSTH_AM,					CVT_V1724_CH1_ZSTH_DATA_SIZE},						/*!< \brief CH 1 Zero suppression threshold register */
	{CVT_V1724_CH1_THRESHOLD_ADD,			CVT_V1724_CH1_THRESHOLD_AM,				CVT_V1724_CH1_THRESHOLD_DATA_SIZE},					/*!< \brief CH 1 Threshold register */
	{CVT_V1724_CH1_TIME_OVER_UNDER_THR_ADD,	CVT_V1724_CH1_TIME_OVER_UNDER_THR_AM,	CVT_V1724_CH1_TIME_OVER_UNDER_THR_DATA_SIZE},		/*!< \brief CH 1 Over/Under Threshold Samples register */
	{CVT_V1724_CH1_STATUS_ADD,				CVT_V1724_CH1_STATUS_AM,				CVT_V1724_CH1_STATUS_DATA_SIZE},					/*!< \brief CH 1 status register */
	{CVT_V1724_CH1_FW_REV_ADD,				CVT_V1724_CH1_FW_REV_AM,				CVT_V1724_CH1_FW_REV_DATA_SIZE},					/*!< \brief CH 1 firmware revision register */
	{CVT_V1724_CH1_BUFF_OCCUPANCY_ADD,		CVT_V1724_CH1_BUFF_OCCUPANCY_AM,		CVT_V1724_CH1_BUFF_OCCUPANCY_DATA_SIZE},			/*!< \brief CH 1 Number of Buffers Filled register */
	{CVT_V1724_CH1_DAC_CONF_ADD,			CVT_V1724_CH1_DAC_CONF_AM,				CVT_V1724_CH1_DAC_CONF_DATA_SIZE},					/*!< \brief CH 1 DAC Data Configuration register */
	{CVT_V1724_CH1_ADC_CONF_ADD,			CVT_V1724_CH1_ADC_CONF_AM,				CVT_V1724_CH1_ADC_CONF_DATA_SIZE},					/*!< \brief CH 1 Configuration register */
	{CVT_V1724_CH1_RESERVED_ADC_DEBUG_ADD,	CVT_V1724_CH1_RESERVED_ADC_DEBUG_AM,	CVT_V1724_CH1_RESERVED_ADC_DEBUG_DATA_SIZE},		/*!< \brief CH 1 ADC Debug Reserved register */
	{CVT_V1724_CH1_RESERVED_MEM_DATA_ADD,	CVT_V1724_CH1_RESERVED_MEM_DATA_AM,		CVT_V1724_CH1_RESERVED_MEM_DATA_DATA_SIZE},			/*!< \brief CH 1 Memory test data Reserved register */
	{CVT_V1724_CH1_RESERVED_MEM_ADDRESS_ADD,CVT_V1724_CH1_RESERVED_MEM_ADDRESS_AM,	CVT_V1724_CH1_RESERVED_MEM_ADDRESS_DATA_SIZE},		/*!< \brief CH 1 Memory test address Reserved register */

//
// CH 2
	{CVT_V1724_CH2_RESERVED_RND_ACC_ADD,	CVT_V1724_CH2_RESERVED_RND_ACC_AM,		CVT_V1724_CH2_RESERVED_RND_ACC_DATA_SIZE},			/*!< \brief CH 2 Read Block channel broadcast reserved register */
	{CVT_V1724_CH2_ZSTH_ADD,				CVT_V1724_CH2_ZSTH_AM,					CVT_V1724_CH2_ZSTH_DATA_SIZE},						/*!< \brief CH 2 Zero suppression threshold register */
	{CVT_V1724_CH2_THRESHOLD_ADD,			CVT_V1724_CH2_THRESHOLD_AM,				CVT_V1724_CH2_THRESHOLD_DATA_SIZE},					/*!< \brief CH 2 Threshold register */
	{CVT_V1724_CH2_TIME_OVER_UNDER_THR_ADD,	CVT_V1724_CH2_TIME_OVER_UNDER_THR_AM,	CVT_V1724_CH2_TIME_OVER_UNDER_THR_DATA_SIZE},		/*!< \brief CH 2 Over/Under Threshold Samples register */
	{CVT_V1724_CH2_STATUS_ADD,				CVT_V1724_CH2_STATUS_AM,				CVT_V1724_CH2_STATUS_DATA_SIZE},					/*!< \brief CH 2 status register */
	{CVT_V1724_CH2_FW_REV_ADD,				CVT_V1724_CH2_FW_REV_AM,				CVT_V1724_CH2_FW_REV_DATA_SIZE},					/*!< \brief CH 2 firmware revision register */
	{CVT_V1724_CH2_BUFF_OCCUPANCY_ADD,		CVT_V1724_CH2_BUFF_OCCUPANCY_AM,		CVT_V1724_CH2_BUFF_OCCUPANCY_DATA_SIZE},			/*!< \brief CH 2 Number of Buffers Filled register */
	{CVT_V1724_CH2_DAC_CONF_ADD,			CVT_V1724_CH2_DAC_CONF_AM,				CVT_V1724_CH2_DAC_CONF_DATA_SIZE},					/*!< \brief CH 2 DAC Data Configuration register */
	{CVT_V1724_CH2_ADC_CONF_ADD,			CVT_V1724_CH2_ADC_CONF_AM,				CVT_V1724_CH2_ADC_CONF_DATA_SIZE},					/*!< \brief CH 2 Configuration register */
	{CVT_V1724_CH2_RESERVED_ADC_DEBUG_ADD,	CVT_V1724_CH2_RESERVED_ADC_DEBUG_AM,	CVT_V1724_CH2_RESERVED_ADC_DEBUG_DATA_SIZE},		/*!< \brief CH 2 ADC Debug Reserved register */
	{CVT_V1724_CH2_RESERVED_MEM_DATA_ADD,	CVT_V1724_CH2_RESERVED_MEM_DATA_AM,		CVT_V1724_CH2_RESERVED_MEM_DATA_DATA_SIZE},			/*!< \brief CH 2 Memory test data Reserved register */
	{CVT_V1724_CH2_RESERVED_MEM_ADDRESS_ADD,CVT_V1724_CH2_RESERVED_MEM_ADDRESS_AM,	CVT_V1724_CH2_RESERVED_MEM_ADDRESS_DATA_SIZE},		/*!< \brief CH 2 Memory test address Reserved register */

//
// CH 3
	{CVT_V1724_CH3_RESERVED_RND_ACC_ADD,	CVT_V1724_CH3_RESERVED_RND_ACC_AM,		CVT_V1724_CH3_RESERVED_RND_ACC_DATA_SIZE},			/*!< \brief CH 3 Read Block channel broadcast reserved register */
	{CVT_V1724_CH3_ZSTH_ADD,				CVT_V1724_CH3_ZSTH_AM,					CVT_V1724_CH3_ZSTH_DATA_SIZE},						/*!< \brief CH 3 Zero suppression threshold register */
	{CVT_V1724_CH3_THRESHOLD_ADD,			CVT_V1724_CH3_THRESHOLD_AM,				CVT_V1724_CH3_THRESHOLD_DATA_SIZE},					/*!< \brief CH 3 Threshold register */
	{CVT_V1724_CH3_TIME_OVER_UNDER_THR_ADD,	CVT_V1724_CH3_TIME_OVER_UNDER_THR_AM,	CVT_V1724_CH3_TIME_OVER_UNDER_THR_DATA_SIZE},		/*!< \brief CH 3 Over/Under Threshold Samples register */
	{CVT_V1724_CH3_STATUS_ADD,				CVT_V1724_CH3_STATUS_AM,				CVT_V1724_CH3_STATUS_DATA_SIZE},					/*!< \brief CH 3 status register */
	{CVT_V1724_CH3_FW_REV_ADD,				CVT_V1724_CH3_FW_REV_AM,				CVT_V1724_CH3_FW_REV_DATA_SIZE},					/*!< \brief CH 3 firmware revision register */
	{CVT_V1724_CH3_BUFF_OCCUPANCY_ADD,		CVT_V1724_CH3_BUFF_OCCUPANCY_AM,		CVT_V1724_CH3_BUFF_OCCUPANCY_DATA_SIZE},			/*!< \brief CH 3 Number of Buffers Filled register */
	{CVT_V1724_CH3_DAC_CONF_ADD,			CVT_V1724_CH3_DAC_CONF_AM,				CVT_V1724_CH3_DAC_CONF_DATA_SIZE},					/*!< \brief CH 3 DAC Data Configuration register */
	{CVT_V1724_CH3_ADC_CONF_ADD,			CVT_V1724_CH3_ADC_CONF_AM,				CVT_V1724_CH3_ADC_CONF_DATA_SIZE},					/*!< \brief CH 3 Configuration register */
	{CVT_V1724_CH3_RESERVED_ADC_DEBUG_ADD,	CVT_V1724_CH3_RESERVED_ADC_DEBUG_AM,	CVT_V1724_CH3_RESERVED_ADC_DEBUG_DATA_SIZE},		/*!< \brief CH 3 ADC Debug Reserved register */
	{CVT_V1724_CH3_RESERVED_MEM_DATA_ADD,	CVT_V1724_CH3_RESERVED_MEM_DATA_AM,		CVT_V1724_CH3_RESERVED_MEM_DATA_DATA_SIZE},			/*!< \brief CH 3 Memory test data Reserved register */
	{CVT_V1724_CH3_RESERVED_MEM_ADDRESS_ADD,CVT_V1724_CH3_RESERVED_MEM_ADDRESS_AM,	CVT_V1724_CH3_RESERVED_MEM_ADDRESS_DATA_SIZE},		/*!< \brief CH 3 Memory test address Reserved register */

//
// CH 4
	{CVT_V1724_CH4_RESERVED_RND_ACC_ADD,	CVT_V1724_CH4_RESERVED_RND_ACC_AM,		CVT_V1724_CH4_RESERVED_RND_ACC_DATA_SIZE},			/*!< \brief CH 4 Read Block channel broadcast reserved register */
	{CVT_V1724_CH4_ZSTH_ADD,				CVT_V1724_CH4_ZSTH_AM,					CVT_V1724_CH4_ZSTH_DATA_SIZE},						/*!< \brief CH 4 Zero suppression threshold register */
	{CVT_V1724_CH4_THRESHOLD_ADD,			CVT_V1724_CH4_THRESHOLD_AM,				CVT_V1724_CH4_THRESHOLD_DATA_SIZE},					/*!< \brief CH 4 Threshold register */
	{CVT_V1724_CH4_TIME_OVER_UNDER_THR_ADD,	CVT_V1724_CH4_TIME_OVER_UNDER_THR_AM,	CVT_V1724_CH4_TIME_OVER_UNDER_THR_DATA_SIZE},		/*!< \brief CH 4 Over/Under Threshold Samples register */
	{CVT_V1724_CH4_STATUS_ADD,				CVT_V1724_CH4_STATUS_AM,				CVT_V1724_CH4_STATUS_DATA_SIZE},					/*!< \brief CH 4 status register */
	{CVT_V1724_CH4_FW_REV_ADD,				CVT_V1724_CH4_FW_REV_AM,				CVT_V1724_CH4_FW_REV_DATA_SIZE},					/*!< \brief CH 4 firmware revision register */
	{CVT_V1724_CH4_BUFF_OCCUPANCY_ADD,		CVT_V1724_CH4_BUFF_OCCUPANCY_AM,		CVT_V1724_CH4_BUFF_OCCUPANCY_DATA_SIZE},			/*!< \brief CH 4 Number of Buffers Filled register */
	{CVT_V1724_CH4_DAC_CONF_ADD,			CVT_V1724_CH4_DAC_CONF_AM,				CVT_V1724_CH4_DAC_CONF_DATA_SIZE},					/*!< \brief CH 4 DAC Data Configuration register */
	{CVT_V1724_CH4_ADC_CONF_ADD,			CVT_V1724_CH4_ADC_CONF_AM,				CVT_V1724_CH4_ADC_CONF_DATA_SIZE},					/*!< \brief CH 4 Configuration register */
	{CVT_V1724_CH4_RESERVED_ADC_DEBUG_ADD,	CVT_V1724_CH4_RESERVED_ADC_DEBUG_AM,	CVT_V1724_CH4_RESERVED_ADC_DEBUG_DATA_SIZE},		/*!< \brief CH 4 ADC Debug Reserved register */
	{CVT_V1724_CH4_RESERVED_MEM_DATA_ADD,	CVT_V1724_CH4_RESERVED_MEM_DATA_AM,		CVT_V1724_CH4_RESERVED_MEM_DATA_DATA_SIZE},			/*!< \brief CH 4 Memory test data Reserved register */
	{CVT_V1724_CH4_RESERVED_MEM_ADDRESS_ADD,CVT_V1724_CH4_RESERVED_MEM_ADDRESS_AM,	CVT_V1724_CH4_RESERVED_MEM_ADDRESS_DATA_SIZE},		/*!< \brief CH 4 Memory test address Reserved register */

//
// CH 5
	{CVT_V1724_CH5_RESERVED_RND_ACC_ADD,	CVT_V1724_CH5_RESERVED_RND_ACC_AM,		CVT_V1724_CH5_RESERVED_RND_ACC_DATA_SIZE},			/*!< \brief CH 5 Read Block channel broadcast reserved register */
	{CVT_V1724_CH5_ZSTH_ADD,				CVT_V1724_CH5_ZSTH_AM,					CVT_V1724_CH5_ZSTH_DATA_SIZE},						/*!< \brief CH 5 Zero suppression threshold register */
	{CVT_V1724_CH5_THRESHOLD_ADD,			CVT_V1724_CH5_THRESHOLD_AM,				CVT_V1724_CH5_THRESHOLD_DATA_SIZE},					/*!< \brief CH 5 Threshold register */
	{CVT_V1724_CH5_TIME_OVER_UNDER_THR_ADD,	CVT_V1724_CH5_TIME_OVER_UNDER_THR_AM,	CVT_V1724_CH5_TIME_OVER_UNDER_THR_DATA_SIZE},		/*!< \brief CH 5 Over/Under Threshold Samples register */
	{CVT_V1724_CH5_STATUS_ADD,				CVT_V1724_CH5_STATUS_AM,				CVT_V1724_CH5_STATUS_DATA_SIZE},					/*!< \brief CH 5 status register */
	{CVT_V1724_CH5_FW_REV_ADD,				CVT_V1724_CH5_FW_REV_AM,				CVT_V1724_CH5_FW_REV_DATA_SIZE},					/*!< \brief CH 5 firmware revision register */
	{CVT_V1724_CH5_BUFF_OCCUPANCY_ADD,		CVT_V1724_CH5_BUFF_OCCUPANCY_AM,		CVT_V1724_CH5_BUFF_OCCUPANCY_DATA_SIZE},			/*!< \brief CH 5 Number of Buffers Filled register */
	{CVT_V1724_CH5_DAC_CONF_ADD,			CVT_V1724_CH5_DAC_CONF_AM,				CVT_V1724_CH5_DAC_CONF_DATA_SIZE},					/*!< \brief CH 5 DAC Data Configuration register */
	{CVT_V1724_CH5_ADC_CONF_ADD,			CVT_V1724_CH5_ADC_CONF_AM,				CVT_V1724_CH5_ADC_CONF_DATA_SIZE},					/*!< \brief CH 5 Configuration register */
	{CVT_V1724_CH5_RESERVED_ADC_DEBUG_ADD,	CVT_V1724_CH5_RESERVED_ADC_DEBUG_AM,	CVT_V1724_CH5_RESERVED_ADC_DEBUG_DATA_SIZE},		/*!< \brief CH 5 ADC Debug Reserved register */
	{CVT_V1724_CH5_RESERVED_MEM_DATA_ADD,	CVT_V1724_CH5_RESERVED_MEM_DATA_AM,		CVT_V1724_CH5_RESERVED_MEM_DATA_DATA_SIZE},			/*!< \brief CH 5 Memory test data Reserved register */
	{CVT_V1724_CH5_RESERVED_MEM_ADDRESS_ADD,CVT_V1724_CH5_RESERVED_MEM_ADDRESS_AM,	CVT_V1724_CH5_RESERVED_MEM_ADDRESS_DATA_SIZE},		/*!< \brief CH 5 Memory test address Reserved register */

//
// CH 6
	{CVT_V1724_CH6_RESERVED_RND_ACC_ADD,	CVT_V1724_CH6_RESERVED_RND_ACC_AM,		CVT_V1724_CH6_RESERVED_RND_ACC_DATA_SIZE},			/*!< \brief CH 6 Read Block channel broadcast reserved register */
	{CVT_V1724_CH6_ZSTH_ADD,				CVT_V1724_CH6_ZSTH_AM,					CVT_V1724_CH6_ZSTH_DATA_SIZE},						/*!< \brief CH 6 Zero suppression threshold register */
	{CVT_V1724_CH6_THRESHOLD_ADD,			CVT_V1724_CH6_THRESHOLD_AM,				CVT_V1724_CH6_THRESHOLD_DATA_SIZE},					/*!< \brief CH 6 Threshold register */
	{CVT_V1724_CH6_TIME_OVER_UNDER_THR_ADD,	CVT_V1724_CH6_TIME_OVER_UNDER_THR_AM,	CVT_V1724_CH6_TIME_OVER_UNDER_THR_DATA_SIZE},		/*!< \brief CH 6 Over/Under Threshold Samples register */
	{CVT_V1724_CH6_STATUS_ADD,				CVT_V1724_CH6_STATUS_AM,				CVT_V1724_CH6_STATUS_DATA_SIZE},					/*!< \brief CH 6 status register */
	{CVT_V1724_CH6_FW_REV_ADD,				CVT_V1724_CH6_FW_REV_AM,				CVT_V1724_CH6_FW_REV_DATA_SIZE},					/*!< \brief CH 6 firmware revision register */
	{CVT_V1724_CH6_BUFF_OCCUPANCY_ADD,		CVT_V1724_CH6_BUFF_OCCUPANCY_AM,		CVT_V1724_CH6_BUFF_OCCUPANCY_DATA_SIZE},			/*!< \brief CH 6 Number of Buffers Filled register */
	{CVT_V1724_CH6_DAC_CONF_ADD,			CVT_V1724_CH6_DAC_CONF_AM,				CVT_V1724_CH6_DAC_CONF_DATA_SIZE},					/*!< \brief CH 6 DAC Data Configuration register */
	{CVT_V1724_CH6_ADC_CONF_ADD,			CVT_V1724_CH6_ADC_CONF_AM,				CVT_V1724_CH6_ADC_CONF_DATA_SIZE},					/*!< \brief CH 6 Configuration register */
	{CVT_V1724_CH6_RESERVED_ADC_DEBUG_ADD,	CVT_V1724_CH6_RESERVED_ADC_DEBUG_AM,	CVT_V1724_CH6_RESERVED_ADC_DEBUG_DATA_SIZE},		/*!< \brief CH 6 ADC Debug Reserved register */
	{CVT_V1724_CH6_RESERVED_MEM_DATA_ADD,	CVT_V1724_CH6_RESERVED_MEM_DATA_AM,		CVT_V1724_CH6_RESERVED_MEM_DATA_DATA_SIZE},			/*!< \brief CH 6 Memory test data Reserved register */
	{CVT_V1724_CH6_RESERVED_MEM_ADDRESS_ADD,CVT_V1724_CH6_RESERVED_MEM_ADDRESS_AM,	CVT_V1724_CH6_RESERVED_MEM_ADDRESS_DATA_SIZE},		/*!< \brief CH 6 Memory test address Reserved register */

//
// CH 7
	{CVT_V1724_CH7_RESERVED_RND_ACC_ADD,	CVT_V1724_CH7_RESERVED_RND_ACC_AM,		CVT_V1724_CH7_RESERVED_RND_ACC_DATA_SIZE},			/*!< \brief CH 7 Read Block channel broadcast reserved register */
	{CVT_V1724_CH7_ZSTH_ADD,				CVT_V1724_CH7_ZSTH_AM,					CVT_V1724_CH7_ZSTH_DATA_SIZE},						/*!< \brief CH 7 Zero suppression threshold register */
	{CVT_V1724_CH7_THRESHOLD_ADD,			CVT_V1724_CH7_THRESHOLD_AM,				CVT_V1724_CH7_THRESHOLD_DATA_SIZE},					/*!< \brief CH 7 Threshold register */
	{CVT_V1724_CH7_TIME_OVER_UNDER_THR_ADD,	CVT_V1724_CH7_TIME_OVER_UNDER_THR_AM,	CVT_V1724_CH7_TIME_OVER_UNDER_THR_DATA_SIZE},		/*!< \brief CH 7 Over/Under Threshold Samples register */
	{CVT_V1724_CH7_STATUS_ADD,				CVT_V1724_CH7_STATUS_AM,				CVT_V1724_CH7_STATUS_DATA_SIZE},					/*!< \brief CH 7 status register */
	{CVT_V1724_CH7_FW_REV_ADD,				CVT_V1724_CH7_FW_REV_AM,				CVT_V1724_CH7_FW_REV_DATA_SIZE},					/*!< \brief CH 7 firmware revision register */
	{CVT_V1724_CH7_BUFF_OCCUPANCY_ADD,		CVT_V1724_CH7_BUFF_OCCUPANCY_AM,		CVT_V1724_CH7_BUFF_OCCUPANCY_DATA_SIZE},			/*!< \brief CH 7 Number of Buffers Filled register */
	{CVT_V1724_CH7_DAC_CONF_ADD,			CVT_V1724_CH7_DAC_CONF_AM,				CVT_V1724_CH7_DAC_CONF_DATA_SIZE},					/*!< \brief CH 7 DAC Data Configuration register */
	{CVT_V1724_CH7_ADC_CONF_ADD,			CVT_V1724_CH7_ADC_CONF_AM,				CVT_V1724_CH7_ADC_CONF_DATA_SIZE},					/*!< \brief CH 7 Configuration register */
	{CVT_V1724_CH7_RESERVED_ADC_DEBUG_ADD,	CVT_V1724_CH7_RESERVED_ADC_DEBUG_AM,	CVT_V1724_CH7_RESERVED_ADC_DEBUG_DATA_SIZE},		/*!< \brief CH 7 ADC Debug Reserved register */
	{CVT_V1724_CH7_RESERVED_MEM_DATA_ADD,	CVT_V1724_CH7_RESERVED_MEM_DATA_AM,		CVT_V1724_CH7_RESERVED_MEM_DATA_DATA_SIZE},			/*!< \brief CH 7 Memory test data Reserved register */
	{CVT_V1724_CH7_RESERVED_MEM_ADDRESS_ADD,CVT_V1724_CH7_RESERVED_MEM_ADDRESS_AM,	CVT_V1724_CH7_RESERVED_MEM_ADDRESS_DATA_SIZE},		/*!< \brief CH 7 Memory test address Reserved register */

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
BOOL cvt_V1724_open( cvt_V1724_data* p_data, UINT16 base_address, long vme_handle, CVT_V17XX_TYPES type)
{
	UINT32 reg_value32= 0;
	UINT32 num_kwords= 0;
	memset( p_data, 0, sizeof( cvt_V1724_data));
	// Check board type
	switch( type)
	{
	case CVT_V1724:							/*!< \brief The board is V1724 */
	case CVT_V1721:							/*!< \brief The board is V1721 */
	case CVT_V1731:							/*!< \brief The board is V1731 */
	case CVT_V1720:							/*!< \brief The board is V1720 */
	case CVT_V1740:							/*!< \brief The board is V1740 */
	case CVT_V1751:							/*!< \brief The board is V1751 */
		break;
	default:
		TRACE1( "cvt_V1724_open: bad board type: %d\n", type);
		return FALSE;
	}
	
	// basic data initialization
	if( !cvt_board_open( &p_data->m_common_data, base_address, vme_handle, CVT_V1724_REG_TABLE))
		return FALSE;
	// board specific data initialization
	// TODO: verify type matches BOARD_INFO BOARD_ID value
	p_data->m_type= type;
	p_data->m_common_data.set_MCST_CBLT= ( BOOL (*)( void*, UINT8, MCST_CBLT_board_pos))cvt_V1724_set_MCST_CBLT;

	// preallocate a suitable memory chunck for sample cache storage

	// 
	// read the effective number of KWords per channel
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_BOARD_INFO_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_BOARD_INFO read failed !\n");
		return FALSE;
	}
	// Get the number of WORDS
	// reg_value32= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)<< 10;
	switch( type)
	{
	case CVT_V1724:							/*!< \brief The board is V1724 */
	case CVT_V1720:							/*!< \brief The board is V1720 */
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)<< 1;
		break;
	case CVT_V1740:							/*!< \brief The board is V1740 */
		// For V1740 BOARD_INFO contains the number of words 36 bits words per group
		// so to get the number of samples we have to calculate the number of nibbles 
		// and to divide for the number of nibble per sample (3)
		num_kwords= ( CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)* 36 /* bits per word*/)/4 /* bits per nibble */ / 3 /* bits per sample */;
		break;
	case CVT_V1721:							/*!< \brief The board is V1721 */
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)<< 2;
		break;
	case CVT_V1731:							/*!< \brief The board is V1731 */
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)<< 2;
		if( p_data->m_is_des_mode)
			num_kwords<<= 1;
		break;
	case CVT_V1751:							/*!< \brief The board is V1751 */
        // num_kwords indica le locazioni di memoria 
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)>> 1;
		if( p_data->m_is_des_mode)
			num_kwords<<= 1;
		num_kwords=(num_kwords*1024*7)/3; //numero di locazioni di memoria
		num_kwords++;
		break;
	default:
		TRACE1( "cvt_V1724_get_buffer_samples: bad board type: %d\n", type);
		return FALSE;
	}

	//p_data->m_cache_sample_buffer_size= (reg_value32<< 2)* CVT_V1724_MAX_CHANNEL+ sizeof( CVT_V1724_HEADER)* ( CVT_V1724_NBLK_1024+ 1);
	
	if (type== CVT_V1751)
	{	  
	  p_data->m_cache_sample_buffer_size= (num_kwords<<2)* CVT_V1724_MAX_CHANNEL+ sizeof( CVT_V1724_HEADER)* (1024+ 1);
	}
	else
	{
	  p_data->m_cache_sample_buffer_size= ( num_kwords<< 11)* CVT_V1724_MAX_CHANNEL+ sizeof( CVT_V1724_HEADER)* ( CVT_V1724_NBLK_1024+ 1);
	}
	p_data->m_cache_sample_buffer= malloc( p_data->m_cache_sample_buffer_size);
	p_data->m_cache_sample_buffer_read_bytes= 0;

	switch( type)
	{
	case CVT_V1731:							/*!< \brief The board is V1731 */
	case CVT_V1751:							/*!< \brief The board is V1751 */
		// Check if DES mode setted
		if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_CTRL_INDEX, &reg_value32))
		{
			TRACE( "V1724 CVT_V1724_BROAD_CH_CTRL read failed !\n");
			return FALSE;
		}
		p_data->m_is_des_mode= ( reg_value32& CVT_V1724_BROAD_CHCTRL_DES_MODE_MSK)? TRUE: FALSE;
		break;
	default:
		break;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_close( cvt_V1724_data* p_data)
{
	if( p_data->m_cache_sample_buffer)
	{
		free( p_data->m_cache_sample_buffer);
		p_data->m_cache_sample_buffer= NULL;
		p_data->m_cache_sample_buffer_size= 0;
		p_data->m_cache_sample_buffer_read_bytes= 0;
	}
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
//     L E V E L   2   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_read_data( cvt_V1724_data* p_data, UINT32* p_ch_max_samples, UINT32* p_num_events)
{
	UINT32 BLT_event_number= 0;
	CVT_V1724_HEADER* p_header;
	BOOL is_berr= FALSE;

	*p_ch_max_samples= 0;
	*p_num_events= 0;

	// 
	// Get BLT event number
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_EVENT_STORED_INDEX, &BLT_event_number))
	{
		TRACE( "CVT_V1724_EVENT_STORED read failed !\n");
		return FALSE;
	}
	if( BLT_event_number> CVT_V1724_MAX_BLT_EVENT_NUM)
		BLT_event_number= CVT_V1724_MAX_BLT_EVENT_NUM;

	p_data->m_cache_sample_buffer_read_bytes= 0;

	// memset( p_data->m_cache_sample_buffer, 0, p_data->m_cache_sample_buffer_size);
	// Read from buffer
	if( !cvt_FIFO_BLT_read( &p_data->m_common_data, CVT_V1724_OUT_BUFFER_ADD, p_data->m_cache_sample_buffer, p_data->m_cache_sample_buffer_size, &p_data->m_cache_sample_buffer_read_bytes, CVT_V1724_OUT_BUFFER_AM, CVT_V1724_OUT_BUFFER_DATA_SIZE, &is_berr))
	{
		p_data->m_cache_sample_buffer_read_bytes= 0;
		return FALSE;
	}
	if( p_data->m_cache_sample_buffer_read_bytes< sizeof( CVT_V1724_HEADER))
	{
		p_data->m_cache_sample_buffer_read_bytes= 0;
		return FALSE;
	}

	// Parse the buffer for validity
	{
		UINT32 offset= 0;
		UINT8 ch_msk;
		int num_channels;
		UINT32 samples;

		while( offset< (p_data->m_cache_sample_buffer_read_bytes-4))
		{
			p_header= (CVT_V1724_HEADER*)(( UINT8*)p_data->m_cache_sample_buffer+ offset);
			if( !CVT_V1724_IS_HEADER_TAG( p_header->m_fields.m_HEADER_0.m_DWORD))
			{
				// Not an header
				p_data->m_cache_sample_buffer_read_bytes= 0;
				*p_ch_max_samples= 0;
				*p_num_events= 0;
				return FALSE;
			}
			++(*p_num_events);
			// Get the number of channels (groups for V1740)
			for( ch_msk= p_header->m_fields.m_HEADER_1.m_fields.m_active_channel_msk, num_channels= 0; ch_msk; ch_msk>>= 1)
			{
				if( ch_msk& 0x01)
					++num_channels;
			}
			if( !num_channels)
			{
				return TRUE;
			}

			switch( p_data->m_type)
			{
			case CVT_V1724:							/*!< \brief The board is V1724 */
			case CVT_V1720:							/*!< \brief The board is V1720 */
				samples= ((( p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2)- sizeof( CVT_V1724_HEADER))/ num_channels)>> 1;
				break;
			case CVT_V1721:							/*!< \brief The board is V1721 */
			case CVT_V1731:							/*!< \brief The board is V1731 */
				samples= ((( p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2)- sizeof( CVT_V1724_HEADER))/ num_channels);
				break;
			case CVT_V1740:							/*!< \brief The board is V1740 */
				{
					const int DELTA_NIBBLE= 3;
					// NumChannels is the number of 8 channels group
					samples= (((( p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2)- sizeof( CVT_V1724_HEADER))<< 1) / ( DELTA_NIBBLE* ( num_channels<< 3)));
				}
				break;
			case CVT_V1751:							/*!< \brief The board is V1751 */
				samples= ((( p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2)- sizeof( CVT_V1724_HEADER))/ num_channels)>>2;
				samples *=3;
				break;
			default:
				TRACE1( "cvt_V1724_read_data: bad board type: %d\n", p_data->m_type);
				return FALSE;
			}
			if( *p_ch_max_samples< samples)
			{
				*p_ch_max_samples= samples;
			}
			offset+= p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2;
		}
	}
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_buffer_cache( cvt_V1724_data* p_data, UINT16 event_index, UINT8 ch_index, UINT16* p_buff, UINT32* p_buff_size, UINT8 *p_board_id, UINT32* p_trigger_time_tag, UINT32* p_event_counter)
{
	CVT_V1724_HEADER *p_header;
	UINT32 offset= 0;
	UINT32 req_buff_size= *p_buff_size;
	int current_event= event_index;

	*p_buff_size= 0;
	*p_board_id= 0;
	*p_trigger_time_tag= 0;
	*p_event_counter= 0;

	// Parse the buffer
	do
	{
		p_header= (CVT_V1724_HEADER*)(( UINT8*)p_data->m_cache_sample_buffer+ offset);
		if( !current_event)
		{
			UINT8 ch_msk;
			int num_channels;
			int index;
			UINT32 i;
			UINT32 samples;

			switch( p_data->m_type)
			{
			case CVT_V1724:							/*!< \brief The board is V1724 */
			case CVT_V1720:							/*!< \brief The board is V1720 */
				// Event found
				if( !( p_header->m_fields.m_HEADER_1.m_fields.m_active_channel_msk& (1<< ch_index)))
				{
					// Channel not found
					return FALSE;
				}
				// Get the number of channels
				for( ch_msk= 0x01, index= -1, i= 0, num_channels= 0; i< CVT_V1724_MAX_CHANNEL; ch_msk<<= 1, i++)
				{
					if( p_header->m_fields.m_HEADER_1.m_fields.m_active_channel_msk& ch_msk)
					{
						if( ch_index== i)
						{
							// Channel found: store the index
							index= num_channels;
						}
						++num_channels;
					}
				}
				if( index< 0)
				{
					return FALSE;
				}
				samples= ((( p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2)- sizeof( CVT_V1724_HEADER))/ num_channels)>> 1;
				// Get data as 14/12 bit values: 2 samples/DWORD
				for( i= 0 ; ( i< samples)&& ( i< req_buff_size); i++)
				{
					p_buff[ i]= ((UINT16*)(( UINT8*)p_data->m_cache_sample_buffer+ offset+ sizeof( CVT_V1724_HEADER)))[ index* samples+ i];
				}
				break;
			case CVT_V1721:							/*!< \brief The board is V1721 */
			case CVT_V1731:							/*!< \brief The board is V1731 */
				// Event found
				if( !( p_header->m_fields.m_HEADER_1.m_fields.m_active_channel_msk& (1<< ch_index)))
				{
					// Channel not found
					return FALSE;
				}
				// Get the number of channels
				for( ch_msk= 0x01, index= -1, i= 0, num_channels= 0; i< CVT_V1724_MAX_CHANNEL; ch_msk<<= 1, i++)
				{
					if( p_header->m_fields.m_HEADER_1.m_fields.m_active_channel_msk& ch_msk)
					{
						if( ch_index== i)
						{
							// Channel found: store the index
							index= num_channels;
						}
						++num_channels;
					}
				}
				if( index< 0)
				{
					return FALSE;
				}
				samples= ((( p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2)- sizeof( CVT_V1724_HEADER))/ num_channels);
				// Get data as 14/12 bit values: 2 samples/DWORD
				for( i= 0 ; ( i< samples)&& ( i< req_buff_size); i++)
				{
					p_buff[ i]= ((UINT8*)(( UINT8*)p_data->m_cache_sample_buffer+ offset+ sizeof( CVT_V1724_HEADER)))[ index* samples+ i];
				}
				break;
			case CVT_V1740:							/*!< \brief The board is V1740 */
				{
					int grp_index= ch_index>> 3;
					// Event found
					// p_header->m_fields.m_HEADER_1.m_fields.m_active_channel_msk is the mask of groups enabled 
					if( !( p_header->m_fields.m_HEADER_1.m_fields.m_active_channel_msk& (1<< grp_index)))
					{
						// Channel not found
						return FALSE;
					}
					// Get the number of groups 
					for( ch_msk= 0x01, index= -1, i= 0, num_channels= 0; i< CVT_V1724_MAX_CHANNEL; ch_msk<<= 1, i++)
					{
						if( p_header->m_fields.m_HEADER_1.m_fields.m_active_channel_msk& ch_msk)
						{
							if( grp_index== i)
							{
								// Channel found: store the index
								index= num_channels;
							}
							++num_channels;
						}
					}
					if( index< 0)
					{
						return FALSE;
					}
					// Get data as 12 bit values: 3 nibbles per sample packed as 3 joined channel's samples
					{
						const int DELTA_NIBBLE= 3;
						const int PACKED_SAMPLE= 3;
						int nibble_offset= ( ch_index% 8)* PACKED_SAMPLE* DELTA_NIBBLE;
						int byte_offset;
						UINT8 *ptr;
						int group_offset= ((( p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2)- sizeof( CVT_V1724_HEADER))* index) / num_channels;

						// NumChannels is the number of 8 channels group
						samples= (((( p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2)- sizeof( CVT_V1724_HEADER))<< 1) / ( DELTA_NIBBLE* ( num_channels<< 3)));

						for( i= 0 ; ( i+ 2< samples)&& ( i+ 2< req_buff_size); i+= PACKED_SAMPLE, nibble_offset+= (( DELTA_NIBBLE* PACKED_SAMPLE)<< 3))
						{
							offset= nibble_offset>> 1;
							byte_offset= nibble_offset- ( offset<< 1);
							ptr= ( UINT8*)p_data->m_cache_sample_buffer+ offset+ sizeof( CVT_V1724_HEADER)+ group_offset;
							switch( byte_offset) {
								case 0:
									// sample 0
									p_buff[ i]= *ptr;
									p_buff[ i]|= ((*( ptr+ 1))<< 8)& 0x0f00;
									// sample 1
									p_buff[ i+ 1]= ((*( ptr+ 1))>> 4)& 0x000f;
									p_buff[ i+ 1]|= (*( ptr+ 2))<< 4;
									// sample 2
									p_buff[ i+ 2]= *( ptr+ 3);
									p_buff[ i+ 2]|= ((*( ptr+ 4))<< 8)& 0x0f00;
									break;
								case 1:
									// sample 0
									p_buff[ i]= ((*ptr)>> 4)& 0x000f;
									p_buff[ i]|= (*( ptr+ 1))<< 4;
									// sample 1
									p_buff[ i+ 1]= *( ptr+ 2);
									p_buff[ i+ 1]|= ((*( ptr+ 3))<< 8)& 0x0f00;
									// sample 2
									p_buff[ i+ 2]= ((*( ptr+ 3))>> 4)& 0x000f;
									p_buff[ i+ 2]|= (*( ptr+ 4))<< 4;
									break;
							}

						}
					}
				}
				break;
			case CVT_V1751:							/*!< \brief The board is V1751 */
				
                // Event found
				if( !( p_header->m_fields.m_HEADER_1.m_fields.m_active_channel_msk& (1<< ch_index)))
				{
					// Channel not found
					return FALSE;
				}
				// Get the number of channels
				for( ch_msk= 0x01, index= -1, i= 0, num_channels= 0; i< CVT_V1724_MAX_CHANNEL; ch_msk<<= 1, i++)
				{
					if( p_header->m_fields.m_HEADER_1.m_fields.m_active_channel_msk& ch_msk)
					{
						if( ch_index== i)
						{
							// Channel found: store the index
							index= num_channels;
						}
						++num_channels;
					}
				}
				if( index< 0)
				{
					return FALSE;
				}
				samples= ((( p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2)- sizeof( CVT_V1724_HEADER))/ num_channels)>> 2;
				// in realtà in questo caso samples è il numero di word: samples= 3*word
				{ 
				UINT32 *ptr,app;
				UINT8 ns;
                for( i= 0 ; ( i< samples)&& ( i< req_buff_size); i++)
				{
					ptr = ( UINT32*)p_data->m_cache_sample_buffer+ (( offset+ sizeof( CVT_V1724_HEADER))>>2)+ (index*samples+ i);
					if( (char*)ptr>= (char*)p_data->m_cache_sample_buffer+ p_data->m_cache_sample_buffer_size) {
						// Bad samples' number ?
						return FALSE;
					}
  				    app= *ptr;
					p_buff[ 3*i]= *ptr & 0x03FF;
					p_buff[ 3*i+1]= (*ptr>> 10) & 0x3ff;
					p_buff[ 3*i+2]= (*ptr>> 20) & 0x03FF;
					ns=(*ptr>>30) & 0x03;
					if (ns!= 3)
						ns=ns;
				}
				i= (samples-1)*3+ns;
				}
				break;
			default:
				TRACE1( "cvt_V1724_get_buffer_cache: bad board type: %d\n", p_data->m_type);
				return FALSE;
			}

			*p_buff_size= i;
			return TRUE;
		}
		offset+= p_header->m_fields.m_HEADER_0.m_fields.m_event_size<< 2;
	}
	
	while(( offset< p_data->m_cache_sample_buffer_read_bytes)&& (( --current_event)>= 0 ));

	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////

BOOL cvt_V1724_set_trigger_mode( cvt_V1724_data* p_data, BOOL falling_edge_enable, BOOL ext_trigger_enable, BOOL sw_trigger_enable, UINT8 ch_trigger_enable_msk, BOOL trigger_overlap_enable, UINT32 post_trigger)
{
	static const UINT32 CH_TRIGGER_MSK[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_TRGEN_CH0_MSK,		/*!< Enable CH 0 trigger bit */
		CVT_V1724_TRGEN_CH1_MSK,		/*!< Enable CH 1 trigger bit */
		CVT_V1724_TRGEN_CH2_MSK,		/*!< Enable CH 2 trigger bit */
		CVT_V1724_TRGEN_CH3_MSK,		/*!< Enable CH 3 trigger bit */
		CVT_V1724_TRGEN_CH4_MSK,		/*!< Enable CH 4 trigger bit */
		CVT_V1724_TRGEN_CH5_MSK,		/*!< Enable CH 5 trigger bit */
		CVT_V1724_TRGEN_CH6_MSK,		/*!< Enable CH 6 trigger bit */
		CVT_V1724_TRGEN_CH7_MSK,		/*!< Enable CH 7 trigger bit */
	};

	UINT32 set_msk32= 0;
	UINT32 clear_msk32= 0;

	// HACK 
	// This operation should be avoided if acquisition is running:
	// We could provide a check here (depending on firmware capabilities)

	//
	// falling/rising edge enable ( Over/Under threshold)
	set_msk32|= ( !falling_edge_enable)? 0: CVT_V1724_BROAD_CHCTRL_TRG_OUT_THR_MSK;
	clear_msk32|= ( !falling_edge_enable)? CVT_V1724_BROAD_CHCTRL_TRG_OUT_THR_MSK: 0;

	// 
	// Trigger Overlap
	set_msk32|= ( trigger_overlap_enable)? CVT_V1724_BROAD_CHCTRL_TRG_OVERLAP_MSK: 0;
	clear_msk32|= ( trigger_overlap_enable)? 0: CVT_V1724_BROAD_CHCTRL_TRG_OVERLAP_MSK;
	
	//
	// setup each channel
	if( set_msk32)
	{
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_SET_CTRL_INDEX, &set_msk32))
		{
			TRACE( "V1724 BROADCAST CH CTRL write failed !\n");
			return FALSE;
		}
	}
	if( clear_msk32)
	{
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_CLEAR_CTRL_INDEX, &clear_msk32))
		{
			TRACE( "V1724 BROADCAST CH CTRL write failed !\n");
			return FALSE;
		}
	}

	set_msk32= 0;
	clear_msk32= 0;

	//
	// External trigger
	set_msk32|= ( ext_trigger_enable)? CVT_V1724_TRGEN_EXT_MSK: 0;
	clear_msk32|= ( ext_trigger_enable)? 0: CVT_V1724_TRGEN_EXT_MSK;
	//
	// Software trigger
	set_msk32|= ( sw_trigger_enable)? CVT_V1724_TRGEN_SW_MSK: 0;
	clear_msk32|= ( sw_trigger_enable)? 0: CVT_V1724_TRGEN_SW_MSK;

	//
	// Channels' trigger
	{
		int i;
		for( i= 0; i< CVT_V1724_MAX_CHANNEL ; i++, ch_trigger_enable_msk>>= 1)
		{
			if( ch_trigger_enable_msk& 0x01)
			{
				set_msk32|= CH_TRIGGER_MSK[ i];
			}
			else
			{
				clear_msk32|= CH_TRIGGER_MSK[ i];
			}
		}
	}
	//
	// bitmask set
	if( set_msk32)
	{
		if( !cvt_set_bitmask_reg( &p_data->m_common_data, CVT_V1724_TRIGGER_SRC_ENABLE_INDEX, &set_msk32))
		{
			TRACE( "V1724 CVT_V1724_TRIGGER_SRC_ENABLE write failed !\n");
			return FALSE;
		}
	}
	//
	// bitmask clear
	if( clear_msk32)
	{
		// clear the enable bit
		if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CVT_V1724_TRIGGER_SRC_ENABLE_INDEX, &clear_msk32))
		{
			TRACE( "V1724 CVT_V1724_TRIGGER_SRC_ENABLE write failed !\n");
			return FALSE;
		}
	}

	//
	// Post Trigger
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_POST_TRIG_INDEX, &post_trigger))
	{
		TRACE( "V1724 CVT_V1724_POST_TRIG write failed !\n");
		return FALSE;
	}
	
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_trigger_mode( cvt_V1724_data* p_data, BOOL *p_falling_edge_enable, BOOL *p_ext_trigger_enable, BOOL *p_sw_trigger_enable, UINT8 *p_ch_trigger_enable_msk, BOOL *p_trigger_overlap_enable, UINT32 *p_post_trigger)
{
	static const UINT32 CH_TRIGGER_MSK[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_TRGEN_CH0_MSK,		/*!< Enable CH 0 trigger bit */
		CVT_V1724_TRGEN_CH1_MSK,		/*!< Enable CH 1 trigger bit */
		CVT_V1724_TRGEN_CH2_MSK,		/*!< Enable CH 2 trigger bit */
		CVT_V1724_TRGEN_CH3_MSK,		/*!< Enable CH 3 trigger bit */
		CVT_V1724_TRGEN_CH4_MSK,		/*!< Enable CH 4 trigger bit */
		CVT_V1724_TRGEN_CH5_MSK,		/*!< Enable CH 5 trigger bit */
		CVT_V1724_TRGEN_CH6_MSK,		/*!< Enable CH 6 trigger bit */
		CVT_V1724_TRGEN_CH7_MSK,		/*!< Enable CH 7 trigger bit */
	};

	UINT32 reg_value32= 0;

	//
	// get CVT_V1724_BROAD_CH_CTRL register status
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_CTRL_INDEX, &reg_value32))
	{
		TRACE( "V1724 BROADCAST CH CTRL read failed !\n");
		return FALSE;
	}
	//
	// falling/rising edge enable ( Over/Under threshold)
	*p_falling_edge_enable= ( reg_value32& CVT_V1724_BROAD_CHCTRL_TRG_OUT_THR_MSK) ? TRUE: FALSE;
	// 
	// Trigger Overlap
	*p_trigger_overlap_enable= ( reg_value32& CVT_V1724_BROAD_CHCTRL_TRG_OVERLAP_MSK) ? TRUE: FALSE;
	
	//
	// get CVT_V1724_TRIGGER_SRC_ENABLE register status
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_TRIGGER_SRC_ENABLE_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_TRIGGER_SRC_ENABLE read failed !\n");
		return FALSE;
	}
	//
	// External trigger
	*p_ext_trigger_enable= ( reg_value32& CVT_V1724_TRGEN_EXT_MSK) ? TRUE: FALSE;
	//
	// Software trigger
	*p_sw_trigger_enable= ( reg_value32& CVT_V1724_TRGEN_SW_MSK) ? TRUE: FALSE;
	//
	// Channels' trigger
	{
		int i;
		int msk= 0x01;
		*p_ch_trigger_enable_msk= 0;
		for( i= 0; i< CVT_V1724_MAX_CHANNEL ; i++, msk<<= 1)
		{
			*p_ch_trigger_enable_msk|= ( reg_value32& CH_TRIGGER_MSK[ i])? msk: 0;
		}
	}

	//
	// Get Post Trigger
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_POST_TRIG_INDEX, p_post_trigger))
	{
		TRACE( "V1724 CVT_V1724_POST_TRIG read failed !\n");
		return FALSE;
	}
	
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_start_acquisition( cvt_V1724_data* p_data, UINT8 ch_msk)
{
	UINT32 set_msk= 0;
	UINT32 reg_value32= 0;

	// HACK 
	// Channel mask setting should be avoided if acquisition is running:
	// We could provide a check here (depending on firmware capabilities)

	//
	// Enabled Channel mask
	switch( p_data->m_type)
	{
	case CVT_V1724:							/*!< \brief The board is V1724 */
	case CVT_V1720:							/*!< \brief The board is V1720 */
	case CVT_V1721:							/*!< \brief The board is V1721 */
	case CVT_V1740:							/*!< \brief The board is V1740 */   
		break;
	case CVT_V1731:							/*!< \brief The board is V1721 */
		// For V1731 in des mode channels are coupled and enabled with a single bit (only even channel)
		if(( p_data->m_is_des_mode)&& ( ch_msk& 0xaa))
		{
			TRACE( "cvt_V1724_start_acquisition: Cannot enable odd channels in des mode \n");
			return FALSE;
		}
		break;
	case CVT_V1751:							/*!< \brief The board is V1751 */
		// For V1751 in des mode channels are coupled and enabled with a single bit (only odd channel)
		if(( p_data->m_is_des_mode)&& ( ch_msk& 0x55))
		{
			TRACE( "cvt_V1724_start_acquisition: Cannot enable even channels in des mode \n");
			return FALSE;
		}
		break;
	default:
		TRACE1( "cvt_V1724_start_acquisition: bad board type: %d\n", p_data->m_type);
		return FALSE;
	}
	reg_value32= ch_msk;

	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_CH_ENABLE_INDEX, &reg_value32))
	{
		TRACE( "V1724 CHANNEL ENABLE write failed !\n");
		return FALSE;
	}

	// Start acquisition
	set_msk|= CVT_V1724_ACQCTRL_START_MSK;

	if( !cvt_set_bitmask_reg( &p_data->m_common_data, CVT_V1724_ACQ_CONTROL_INDEX, &set_msk))
	{
		TRACE( "V1724 ACQUISITION CONTROL write failed !\n");
		return FALSE;
	}
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_stop_acquisition( cvt_V1724_data* p_data)
{
	UINT32 clear_msk= 0;

	// Stop acquisition
	clear_msk|= CVT_V1724_ACQCTRL_START_MSK;

	if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CVT_V1724_ACQ_CONTROL_INDEX, &clear_msk))
	{
		TRACE( "V1724 ACQUISITION CONTROL write failed !\n");
		return FALSE;
	}		
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_acquisition_mode( cvt_V1724_data* p_data, BOOL sample_enable, CVT_V1724_NUM_BLOCKS block_size, CVT_V1724_ACQ_CONTROL_ACQ_MODES acquisition_mode, BOOL count_all_trigger, UINT32 downsample_factor)
{
	UINT32 set_msk= 0;
	UINT32 clear_msk= 0;
	UINT32 reg_value32;

	//
	// parameter checking
	switch( block_size)
	{
	case CVT_V1724_NBLK_1024:			/*!< 1024 blocks */
	case CVT_V1724_NBLK_512:			/*!<  512 blocks */
	case CVT_V1724_NBLK_256:			/*!<  256 blocks */
	case CVT_V1724_NBLK_128:			/*!<  128 blocks */
	case CVT_V1724_NBLK_64:				/*!<   64 blocks */
	case CVT_V1724_NBLK_32:				/*!<   32 blocks */
	case CVT_V1724_NBLK_16:				/*!<   16 blocks */
	case CVT_V1724_NBLK_8:				/*!<    8 blocks */
	case CVT_V1724_NBLK_4:				/*!<    4 blocks */
	case CVT_V1724_NBLK_2:				/*!<    2 blocks */
	case CVT_V1724_NBLK_1:				/*!<    1 block  */
		break;
	default:
		TRACE1( "V1724 Bad block size '%d'!\n", block_size);
		return FALSE;
	}
	//
	// Sample enable
	set_msk|= ( sample_enable)? CVT_V1724_BROAD_CHCTRL_GATE_MODE_MSK: 0;
	clear_msk|= ( sample_enable)? 0: CVT_V1724_BROAD_CHCTRL_GATE_MODE_MSK;
	
	//
	// setup each channel
	if( set_msk)
	{
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_SET_CTRL_INDEX, &set_msk))
		{
			TRACE( "V1724 CH SET CONTROL write failed !\n");
			return FALSE;
		}
	}
	if( clear_msk)
	{
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_CLEAR_CTRL_INDEX, &clear_msk))
		{
			TRACE( "V1724 CH CLEAR CONTROL write failed !\n");
			return FALSE;
		}		
	}
	//
	// Block size	
	reg_value32= block_size;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_NUM_BLOCK_INDEX, &reg_value32))
	{
		TRACE( "V1724 CH BLOCK SIZE write failed !\n");
		return FALSE;
	}

	reg_value32= 0;
	set_msk= 0;
	clear_msk= 0;
	// Acquisition mode
	CVT_V1724_SET_ACQCTRL_ACQ_MODE( reg_value32, acquisition_mode);
	set_msk|= ( reg_value32& CVT_V1724_ACQCTRL_ACQ_MODE_MSK);
	clear_msk|= (( ~reg_value32)& CVT_V1724_ACQCTRL_ACQ_MODE_MSK);

	// Event counter
	set_msk|= ( count_all_trigger)? CVT_V1724_ACQCTRL_EVENT_COUNTER_ALL_MSK: 0;
	clear_msk|= ( count_all_trigger)? 0: CVT_V1724_ACQCTRL_EVENT_COUNTER_ALL_MSK;

	// Down sample
	set_msk|= ( downsample_factor)? CVT_V1724_ACQCTRL_DOWNSAMPLE_MSK: 0;
	clear_msk|= ( downsample_factor)? 0: CVT_V1724_ACQCTRL_DOWNSAMPLE_MSK;

	if( set_msk)
	{
		if( !cvt_set_bitmask_reg( &p_data->m_common_data, CVT_V1724_ACQ_CONTROL_INDEX, &set_msk))
		{
			TRACE( "V1724 ACQUISITION CONTROL write failed !\n");
			return FALSE;
		}
	}
	if( clear_msk)
	{
		if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CVT_V1724_ACQ_CONTROL_INDEX, &clear_msk))
		{
			TRACE( "V1724 ACQUISITION CONTROL write failed !\n");
			return FALSE;
		}		
	}

	if( downsample_factor)
	{
		reg_value32= downsample_factor;
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_DOWNSAMPLE_FACT_INDEX, &reg_value32))
		{
			TRACE( "V1724 DOWNSAMPLE FACTOR write failed !\n");
			return FALSE;
		}		
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_acquisition_mode( cvt_V1724_data* p_data, BOOL *p_sample_enable, CVT_V1724_NUM_BLOCKS *p_block_size)
{
	UINT32 reg_value32= 0;

	//
	// Get CVT_V1724_BROAD_CH_CTRL register value
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_CTRL_INDEX, &reg_value32))
	{
		TRACE( "CVT_V1724_BROAD_CH_CTRL read failed !\n");
		return FALSE;
	}
	//
	// Sample enable
	*p_sample_enable= ( reg_value32& CVT_V1724_BROAD_CHCTRL_GATE_MODE_MSK)? TRUE: FALSE;
	
	//
	// Get Block size	
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_BROAD_NUM_BLOCK_INDEX, &reg_value32))
	{
		TRACE( "CVT_V1724_BROAD_NUM_BLOCK read failed !\n");
		return FALSE;
	}
	*p_block_size= reg_value32;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_acquisition_status( cvt_V1724_data* p_data, BOOL *p_is_MEB_not_empty, BOOL *p_is_MEB_full, BOOL *p_is_running, BOOL *p_some_event_ready, BOOL *p_event_full, BOOL *p_s_in)
{
	UINT32 reg_value32= 0;

	//
	// Get CVT_V1724_ACQ_STATUS register value
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ACQ_STATUS_INDEX, &reg_value32))
	{
		TRACE( "V1724 ACQUISITION STATUS read failed !\n");
		return FALSE;
	}

	//
	// MEB not empty bit
	*p_is_MEB_not_empty= ( reg_value32& CVT_V1724_ACQSTS_MEB_NOT_EMPTY_MSK)? TRUE: FALSE;

	//
	// MEB full bit
	*p_is_MEB_full= ( reg_value32& CVT_V1724_ACQSTS_MEB_FULL_MSK)? TRUE: FALSE;

	//
	// Run status bit
	*p_is_running= ( reg_value32& CVT_V1724_ACQSTS_RUN_MSK)? TRUE: FALSE;

	//
	// Event ready bit
	*p_some_event_ready= ( reg_value32& CVT_V1724_ACQSTS_EVENT_RDY_MSK)? TRUE: FALSE;

	//
	// Event full bit
	*p_event_full= ( reg_value32& CVT_V1724_ACQSTS_EVENT_FULL_MSK)? TRUE: FALSE;

	//
	// S-IN status bit
	*p_s_in= ( reg_value32& CVT_V1724_ACQSTS_S_IN_MSK)? TRUE: FALSE;
			
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_buffer_samples( cvt_V1724_data* p_data, UINT16 *p_num_k_samples, CVT_V1724_NUM_BLOCKS *p_num_block_read)
{
	UINT32 reg_value32;
	UINT32 num_kwords;
	UINT32 num_blocks;

	// Get the number of words per channel
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_BOARD_INFO_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_BOARD_INFO read failed !\n");
		return FALSE;
	}


	// Convert to num samples
	switch( p_data->m_type)
	{
	case CVT_V1724:							/*!< \brief The board is V1724 */
	case CVT_V1720:							/*!< \brief The board is V1720 */
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)<< 1;
		break;
	case CVT_V1740:							/*!< \brief The board is V1740 */
		// For V1740 BOARD_INFO contains the number of words 36 bits words per group
		// so to get the number of samples we have to calculate the number of nibbles 
		// and to divide for the number of nibble per sample (3)
		num_kwords= ( CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)* 36 /* bits per word*/)/4 /* bits per nibble */ / 3 /* bits per sample */;
		break;
	case CVT_V1721:							/*!< \brief The board is V1721 */
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)<< 2;
		break;
	case CVT_V1731:							/*!< \brief The board is V1731 */
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)<< 2;
		if( p_data->m_is_des_mode)
			num_kwords<<= 1;
		break;
	case CVT_V1751:							/*!< \brief The board is V1731 */
		num_kwords= (CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)>>1)*7;
		if( p_data->m_is_des_mode)
			num_kwords<<= 1;
		break;
	default:
        // HACK LCOL 20/07/2009: commentata la linea seguente => non è definito type!!
		//TRACE1( "cvt_V1724_get_buffer_samples: bad board type: %d\n", type);
		return FALSE;
	}

	// Get actual block size
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_BROAD_NUM_BLOCK_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_BROAD_NUM_BLOCK read failed !\n");
		return FALSE;
	}
	*p_num_block_read= reg_value32;

	num_blocks= 1<< ( reg_value32);

	*p_num_k_samples= ( UINT16)( UINT32)( num_kwords/ num_blocks);

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_buffer_samples( cvt_V1724_data* p_data, UINT16 num_k_samples, CVT_V1724_NUM_BLOCKS *p_num_block_written)
{
	UINT32 reg_value32;
	UINT32 num_kwords;
	UINT32 num_blocks;

	if( num_k_samples== 0)
	{
		TRACE( "V1724 bad num_k_samples !\n");
		return FALSE;
	}

	// Get the number of words per channel
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_BOARD_INFO_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_BOARD_INFO read failed !\n");
		return FALSE;
	}
	// Convert to num samples
	switch( p_data->m_type)
	{
	case CVT_V1724:							/*!< \brief The board is V1724 */
	case CVT_V1720:							/*!< \brief The board is V1720 */
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)<< 1;
		break;
	case CVT_V1740:							/*!< \brief The board is V1740 */
		// For V1740 BOARD_INFO contains the number of words 36 bits words per group
		// so to get the number of samples we have to calculate the number of nibbles 
		// and to divide for the number of nibble per sample (3)
		num_kwords= ( CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)* 36 /* bits per word*/)/4 /* bits per nibble */ / 3 /* bits per sample */;
		break;
	case CVT_V1721:							/*!< \brief The board is V1721 */
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)<< 2;
		break;
	case CVT_V1731:							/*!< \brief The board is V1731 */
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)<< 2;
		if( p_data->m_is_des_mode)
			num_kwords<<= 1;
		break;
	case CVT_V1751:							/*!< \brief The board is V1751 */
		num_kwords= CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg_value32)*3;
		if( p_data->m_is_des_mode)
			num_kwords<<= 1;
		break;
	default:
        // HACK LCOL 20/07/2009: commentata la linea seguente => non è definito type!!
		//TRACE1( "cvt_V1724_get_buffer_samples: bad board type: %d\n", type);
		return FALSE;
	}

	// Get the number of blocks requested
	reg_value32= (( UINT32)( num_kwords/ ( UINT32)num_k_samples));
	num_blocks= 0;
	while( reg_value32> (UINT32)( 1<< num_blocks))
	{
		++num_blocks;
	}

	if( num_blocks> CVT_V1724_NBLK_1024)
	{
		TRACE( "V1724 bad num_k_samples: too many blocks requested !\n");
		return FALSE;
	}

	// Set Block num	
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_NUM_BLOCK_INDEX, &num_blocks))
	{
		TRACE( "V1724 CVT_V1724_BROAD_NUM_BLOCK write failed !\n");
		return FALSE;
	}
	*p_num_block_written= num_blocks;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_fp_trigger_out( cvt_V1724_data* p_data, BOOL ext_trigger_enable, BOOL sw_trigger_enable, UINT8 ch_trigger_enable_msk)
{
	static const UINT32 CH_TRIGGER_MSK[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_FPTRGEN_CH0_MSK,		/*!< Enable CH 0 trigger bit */
		CVT_V1724_FPTRGEN_CH1_MSK,		/*!< Enable CH 1 trigger bit */
		CVT_V1724_FPTRGEN_CH2_MSK,		/*!< Enable CH 2 trigger bit */
		CVT_V1724_FPTRGEN_CH3_MSK,		/*!< Enable CH 3 trigger bit */
		CVT_V1724_FPTRGEN_CH4_MSK,		/*!< Enable CH 4 trigger bit */
		CVT_V1724_FPTRGEN_CH5_MSK,		/*!< Enable CH 5 trigger bit */
		CVT_V1724_FPTRGEN_CH6_MSK,		/*!< Enable CH 6 trigger bit */
		CVT_V1724_FPTRGEN_CH7_MSK,		/*!< Enable CH 7 trigger bit */
	};

	UINT32 set_msk32= 0;
	UINT32 clear_msk32= 0;

	//
	// External trigger
	set_msk32|= ( ext_trigger_enable)? CVT_V1724_FPTRGEN_EXT_MSK: 0;
	clear_msk32|= ( ext_trigger_enable)? 0: CVT_V1724_FPTRGEN_EXT_MSK;
	//
	// Software trigger
	set_msk32|= ( sw_trigger_enable)? CVT_V1724_FPTRGEN_SW_MSK: 0;
	clear_msk32|= ( sw_trigger_enable)? 0: CVT_V1724_FPTRGEN_SW_MSK;

	//
	// Channels' trigger
	{
		int i;
		for( i= 0; i< CVT_V1724_MAX_CHANNEL ; i++, ch_trigger_enable_msk>>= 1)
		{
			if( ch_trigger_enable_msk& 0x01)
			{
				set_msk32|= CH_TRIGGER_MSK[ i];
			}
			else
			{
				clear_msk32|= CH_TRIGGER_MSK[ i];
			}
		}
	}
	//
	// bitmask set
	if( set_msk32)
	{
		if( !cvt_set_bitmask_reg( &p_data->m_common_data, CVT_V1724_FP_TRIGGER_OUT_ENABLE_INDEX, &set_msk32))
		{
			TRACE( "V1724 CVT_V1724_TRIGGER_SRC_ENABLE write failed !\n");
			return FALSE;
		}
	}
	//
	// bitmask clear
	if( clear_msk32)
	{
		// clear the enable bit
		if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CVT_V1724_FP_TRIGGER_OUT_ENABLE_INDEX, &clear_msk32))
		{
			TRACE( "V1724 CVT_V1724_TRIGGER_SRC_ENABLE write failed !\n");
			return FALSE;
		}
	}

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_fp_trigger_out( cvt_V1724_data* p_data, BOOL *p_ext_trigger_enable, BOOL *p_sw_trigger_enable, UINT8 *p_ch_trigger_enable_msk)
{
	static const UINT32 CH_TRIGGER_MSK[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_FPTRGEN_CH0_MSK,		/*!< Enable CH 0 trigger bit */
		CVT_V1724_FPTRGEN_CH1_MSK,		/*!< Enable CH 1 trigger bit */
		CVT_V1724_FPTRGEN_CH2_MSK,		/*!< Enable CH 2 trigger bit */
		CVT_V1724_FPTRGEN_CH3_MSK,		/*!< Enable CH 3 trigger bit */
		CVT_V1724_FPTRGEN_CH4_MSK,		/*!< Enable CH 4 trigger bit */
		CVT_V1724_FPTRGEN_CH5_MSK,		/*!< Enable CH 5 trigger bit */
		CVT_V1724_FPTRGEN_CH6_MSK,		/*!< Enable CH 6 trigger bit */
		CVT_V1724_FPTRGEN_CH7_MSK,		/*!< Enable CH 7 trigger bit */
	};

	UINT32 reg_value32= 0;
	
	//
	// get CVT_V1724_TRIGGER_SRC_ENABLE register status
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_FP_TRIGGER_OUT_ENABLE_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_FP_TRIGGER_OUT_ENABLE read failed !\n");
		return FALSE;
	}
	//
	// External trigger
	*p_ext_trigger_enable= ( reg_value32& CVT_V1724_FPTRGEN_EXT_MSK) ? TRUE: FALSE;
	//
	// Software trigger
	*p_sw_trigger_enable= ( reg_value32& CVT_V1724_FPTRGEN_SW_MSK) ? TRUE: FALSE;
	//
	// Channels' trigger
	{
		int i;
		int msk= 0x01;
		*p_ch_trigger_enable_msk= 0;
		for( i= 0; i< CVT_V1724_MAX_CHANNEL ; i++, msk<<= 1)
		{
			*p_ch_trigger_enable_msk|= ( reg_value32& CH_TRIGGER_MSK[ i])? msk: 0;
		}
	}
	
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_dither_enable( cvt_V1724_data* p_data, UINT8 ch_msk, BOOL dither_value)
{
	static const UINT16 CH_CONF[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_ADC_CONF_INDEX,			/*!< \brief CH 0 Configuration register index */
		CVT_V1724_CH1_ADC_CONF_INDEX,			/*!< \brief CH 1 Configuration register index */
		CVT_V1724_CH2_ADC_CONF_INDEX,			/*!< \brief CH 2 Configuration register index */
		CVT_V1724_CH3_ADC_CONF_INDEX,			/*!< \brief CH 3 Configuration register index */
		CVT_V1724_CH4_ADC_CONF_INDEX,			/*!< \brief CH 4 Configuration register index */
		CVT_V1724_CH5_ADC_CONF_INDEX,			/*!< \brief CH 5 Configuration register index */
		CVT_V1724_CH6_ADC_CONF_INDEX,			/*!< \brief CH 6 Configuration register index */
		CVT_V1724_CH7_ADC_CONF_INDEX,			/*!< \brief CH 7 Configuration register index */
	};
	UINT32 set_msk= 0;

	//
	// Board type verify
	switch( p_data->m_type)
	{
	case CVT_V1724:
	case CVT_V1720:
// HACK V1740 TBD
	case CVT_V1740:
		break;
	default:
		TRACE( "V1724 cvt_V1724_set_dither_enable bad board type !\n");
		return FALSE;
	}

	//
	// Dither enable
	set_msk|= CVT_V1724_CHADCCONF_DITHER_MSK;

	if( dither_value)
	{
		int i;
		for( i= 0; (i< CVT_V1724_MAX_CHANNEL )&& ch_msk; i++, ch_msk>>= 1)
		{
			if( !(ch_msk& 0x01))
				continue;
			if( !cvt_set_bitmask_reg( &p_data->m_common_data, CH_CONF[ i], &set_msk))
			{
				TRACE( "V1724 CH CONF write failed !\n");
				return FALSE;
			}
		}
	}
	else
	{
		int i;
		for( i= 0; (i< CVT_V1724_MAX_CHANNEL )&& ch_msk; i++, ch_msk>>= 1)
		{
			if( !(ch_msk& 0x01))
				continue;
			if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CH_CONF[ i], &set_msk))
			{
				TRACE( "V1724 CH CONF write failed !\n");
				return FALSE;
			}
		}
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_dither_enable( cvt_V1724_data* p_data, UINT8 ch_index, BOOL *p_dither_value)
{
	static const UINT16 CH_CONF[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_ADC_CONF_INDEX,			/*!< \brief CH 0 Configuration register index */
		CVT_V1724_CH1_ADC_CONF_INDEX,			/*!< \brief CH 1 Configuration register index */
		CVT_V1724_CH2_ADC_CONF_INDEX,			/*!< \brief CH 2 Configuration register index */
		CVT_V1724_CH3_ADC_CONF_INDEX,			/*!< \brief CH 3 Configuration register index */
		CVT_V1724_CH4_ADC_CONF_INDEX,			/*!< \brief CH 4 Configuration register index */
		CVT_V1724_CH5_ADC_CONF_INDEX,			/*!< \brief CH 5 Configuration register index */
		CVT_V1724_CH6_ADC_CONF_INDEX,			/*!< \brief CH 6 Configuration register index */
		CVT_V1724_CH7_ADC_CONF_INDEX,			/*!< \brief CH 7 Configuration register index */
	};
	UINT32 reg_value32= 0;

	//
	// Board type verify
	switch( p_data->m_type)
	{
	case CVT_V1724:
	case CVT_V1720:
// HACK V1740 TBD
	case CVT_V1740:	
		break;
	default:
		TRACE( "V1724 cvt_V1724_set_dither_enable bad board type !\n");
		return FALSE;
	}

	//
	// input param check
	if( ch_index>= CVT_V1724_MAX_CHANNEL)
	{
		TRACE1( "V1724 cvt_V1724_get_dither_enable bad channel '%d'!\n", ch_index);
		return FALSE;
	}

	//
	// Gets the CVT_V1724_CH#_CONF register value
	if( !cvt_read_reg( &p_data->m_common_data, CH_CONF[ ch_index], &reg_value32))
	{
		TRACE( "V1724 CH CONF read failed !\n");
		return FALSE;
	}

	//
	// Dither
	*p_dither_value= ( reg_value32& CVT_V1724_CHADCCONF_DITHER_MSK)? TRUE: FALSE;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_adc_conf( cvt_V1724_data* p_data, UINT8 ch_msk, BOOL dither_value, BOOL clk_duty_stab_value, BOOL randomize_value)
{
	static const UINT16 CH_CONF[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_ADC_CONF_INDEX,			/*!< \brief CH 0 Configuration register index */
		CVT_V1724_CH1_ADC_CONF_INDEX,			/*!< \brief CH 1 Configuration register index */
		CVT_V1724_CH2_ADC_CONF_INDEX,			/*!< \brief CH 2 Configuration register index */
		CVT_V1724_CH3_ADC_CONF_INDEX,			/*!< \brief CH 3 Configuration register index */
		CVT_V1724_CH4_ADC_CONF_INDEX,			/*!< \brief CH 4 Configuration register index */
		CVT_V1724_CH5_ADC_CONF_INDEX,			/*!< \brief CH 5 Configuration register index */
		CVT_V1724_CH6_ADC_CONF_INDEX,			/*!< \brief CH 6 Configuration register index */
		CVT_V1724_CH7_ADC_CONF_INDEX,			/*!< \brief CH 7 Configuration register index */
	};
	UINT32 set_msk32= 0;
	UINT32 clear_msk32= 0;

	//
	// Board type verify
	switch( p_data->m_type)
	{
	case CVT_V1724:
	case CVT_V1720:
// HACK V1740 TBD
	case CVT_V1740:	
		break;
	default:
		TRACE( "V1724 cvt_V1724_set_adc_conf bad board type !\n");
		return FALSE;
	}

	//
	// Dither enable
	set_msk32|= ( dither_value)? CVT_V1724_CHADCCONF_DITHER_MSK: 0;
	clear_msk32|= ( dither_value)? 0: CVT_V1724_CHADCCONF_DITHER_MSK;
	//
	// Clock duty cycle stabilizer
	set_msk32|= ( clk_duty_stab_value)? CVT_V1724_CHADCCONF_CLK_DUTY_STAB_MSK: 0;
	clear_msk32|= ( clk_duty_stab_value)? 0: CVT_V1724_CHADCCONF_CLK_DUTY_STAB_MSK;
	//
	// Output randomizer
	set_msk32|= ( randomize_value)? CVT_V1724_CHADCCONF_RND_MSK: 0;
	clear_msk32|= ( randomize_value)? 0: CVT_V1724_CHADCCONF_RND_MSK;

	//
	// bitmask set
	if( set_msk32)
	{
		int i;
		UINT8 act_ch_msk= ch_msk;
		for( i= 0; (i< CVT_V1724_MAX_CHANNEL )&& act_ch_msk; i++, act_ch_msk>>= 1)
		{
			if( !( act_ch_msk& 0x01))
				continue;
			if( !cvt_set_bitmask_reg( &p_data->m_common_data, CH_CONF[ i], &set_msk32))
			{
				TRACE( "V1724 CH CONF write failed !\n");
				return FALSE;
			}
		}
	}
	//
	// bitmask clear
	if( clear_msk32)
	{
		int i;
		UINT8 act_ch_msk= ch_msk;
		for( i= 0; (i< CVT_V1724_MAX_CHANNEL )&& act_ch_msk; i++, act_ch_msk>>= 1)
		{
			if( !( act_ch_msk& 0x01))
				continue;
			if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CH_CONF[ i], &clear_msk32))
			{
				TRACE( "V1724 CH CONF write failed !\n");
				return FALSE;
			}
		}
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_adc_conf( cvt_V1724_data* p_data, UINT8 ch_index, BOOL *p_dither_value, BOOL *p_clk_duty_stab_value, BOOL *p_randomize_value)
{
	static const UINT16 CH_CONF[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_ADC_CONF_INDEX,			/*!< \brief CH 0 Configuration register index */
		CVT_V1724_CH1_ADC_CONF_INDEX,			/*!< \brief CH 1 Configuration register index */
		CVT_V1724_CH2_ADC_CONF_INDEX,			/*!< \brief CH 2 Configuration register index */
		CVT_V1724_CH3_ADC_CONF_INDEX,			/*!< \brief CH 3 Configuration register index */
		CVT_V1724_CH4_ADC_CONF_INDEX,			/*!< \brief CH 4 Configuration register index */
		CVT_V1724_CH5_ADC_CONF_INDEX,			/*!< \brief CH 5 Configuration register index */
		CVT_V1724_CH6_ADC_CONF_INDEX,			/*!< \brief CH 6 Configuration register index */
		CVT_V1724_CH7_ADC_CONF_INDEX,			/*!< \brief CH 7 Configuration register index */
	};
	UINT32 reg_value32= 0;

	//
	// Board type verify
	switch( p_data->m_type)
	{
	case CVT_V1724:
	case CVT_V1720:
// HACK V1740 TBD
	case CVT_V1740:	
		break;
	default:
		TRACE( "V1724 cvt_V1724_set_adc_conf bad board type !\n");
		return FALSE;
	}

	//
	// input param check
	if( ch_index>= CVT_V1724_MAX_CHANNEL)
	{
		TRACE1( "V1724 cvt_V1724_set_adc_conf bad channel '%d'!\n", ch_index);
		return FALSE;
	}

	//
	// Gets the CVT_V1724_CH#_CONF register value
	if( !cvt_read_reg( &p_data->m_common_data, CH_CONF[ ch_index], &reg_value32))
	{
		TRACE( "V1724 CH CONF read failed !\n");
		return FALSE;
	}

	//
	// Dither
	*p_dither_value= ( reg_value32& CVT_V1724_CHADCCONF_DITHER_MSK)? TRUE: FALSE;
	//
	// Clock duty stabilizer
	*p_clk_duty_stab_value= ( reg_value32& CVT_V1724_CHADCCONF_CLK_DUTY_STAB_MSK)? TRUE: FALSE;
	//
	// Output Randomize 
	*p_randomize_value= ( reg_value32& CVT_V1724_CHADCCONF_RND_MSK)? TRUE: FALSE;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_adc_calib( cvt_V1724_data* p_data, UINT8 ch_msk)
{
	static const UINT16 CH_CONF[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_ADC_CONF_INDEX,			/*!< \brief CH 0 Configuration register index */
		CVT_V1724_CH1_ADC_CONF_INDEX,			/*!< \brief CH 1 Configuration register index */
		CVT_V1724_CH2_ADC_CONF_INDEX,			/*!< \brief CH 2 Configuration register index */
		CVT_V1724_CH3_ADC_CONF_INDEX,			/*!< \brief CH 3 Configuration register index */
		CVT_V1724_CH4_ADC_CONF_INDEX,			/*!< \brief CH 4 Configuration register index */
		CVT_V1724_CH5_ADC_CONF_INDEX,			/*!< \brief CH 5 Configuration register index */
		CVT_V1724_CH6_ADC_CONF_INDEX,			/*!< \brief CH 6 Configuration register index */
		CVT_V1724_CH7_ADC_CONF_INDEX,			/*!< \brief CH 7 Configuration register index */
	};
	static const UINT16 CH_STATUS[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_STATUS_INDEX,						/*!< \brief CH 0 status register relative address */
		CVT_V1724_CH1_STATUS_INDEX,						/*!< \brief CH 1 status register relative address */
		CVT_V1724_CH2_STATUS_INDEX,						/*!< \brief CH 2 status register relative address */
		CVT_V1724_CH3_STATUS_INDEX,						/*!< \brief CH 3 status register relative address */
		CVT_V1724_CH4_STATUS_INDEX,						/*!< \brief CH 4 status register relative address */
		CVT_V1724_CH5_STATUS_INDEX,						/*!< \brief CH 5 status register relative address */
		CVT_V1724_CH6_STATUS_INDEX,						/*!< \brief CH 6 status register relative address */
		CVT_V1724_CH7_STATUS_INDEX,						/*!< \brief CH 7 status register relative address */
	};
	UINT32 reg_value= 0;
	UINT32 msk32= 0;
	int i;
	UINT8 act_ch_msk;
	BOOL is_des_mode= FALSE;

	//
	// Board type verify
	switch( p_data->m_type)
	{
	case CVT_V1751:
	case CVT_V1731:
	case CVT_V1721:
		break;
	default:
		TRACE( "V1724 cvt_V1724_adc_calib bad board type !\n");
		return FALSE;
	}

	if( p_data->m_type!= CVT_V1751)
	{
		// Check if des mode
		if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_CTRL_INDEX, &reg_value))
		{
			TRACE( "V1724 CVT_V1724_BROAD_CH_CTRL read failed !\n");
			return FALSE;
		}
		is_des_mode= reg_value& CVT_V1724_BROAD_CHCTRL_DES_MODE_MSK;
		
		if( is_des_mode)
		{
			return cvt_V1724_set_des_mode( p_data, TRUE);
		}
		// calibration bit
		msk32|= CVT_V1724_CHADCCONF_CAL_MSK_2;

		// Set calibration bit
		act_ch_msk= ch_msk;
		for( i= 0; (i< CVT_V1724_MAX_CHANNEL )&& act_ch_msk; i++, act_ch_msk>>= 1)
		{
			if( !( act_ch_msk& 0x01))
				continue;
			if( !cvt_set_bitmask_reg( &p_data->m_common_data, CH_CONF[ i], &msk32))
			{
				TRACE( "V1724 ADC calib write failed !\n");
				return FALSE;
			}
		}
		cvt_delay( 1);

		// Reset calibration bit
		act_ch_msk= ch_msk;
		for( i= 0; (i< CVT_V1724_MAX_CHANNEL )&& act_ch_msk; i++, act_ch_msk>>= 1)
		{
			if( !( act_ch_msk& 0x01))
				continue;
			if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CH_CONF[ i], &msk32))
			{
				TRACE( "V1724 ADC calib write failed !\n");
				return FALSE;
			}
		}
	}
	else
	{
		// calibration bit
		msk32|= CVT_V1724_CHADCCONF_CAL_MSK_2;

		// Set calibration bit
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_ADC_CONF_INDEX, &msk32))
		{
			TRACE( "V1724 ADC calib write failed !\n");
			return FALSE;
		}
		cvt_delay( 20);

		// Reset calibration bit
		msk32= 0;
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_ADC_CONF_INDEX, &msk32))
		{
			TRACE( "V1724 ADC calib write failed !\n");
			return FALSE;
		}
	}
	cvt_delay( 20);

	// verify calibration 
	act_ch_msk= ch_msk;
	for( i= 0; (i< CVT_V1724_MAX_CHANNEL )&& act_ch_msk; i++, act_ch_msk>>= 1)
	{
		if( !( act_ch_msk& 0x01))
			continue;
		// read channel status register 1
		if( !cvt_read_reg( &p_data->m_common_data, CH_STATUS[ i], &reg_value))
		{
			TRACE1( "V1724 CH_STATUS[%d] read failed !\n", i);
			return FALSE;
		}
		if( !( reg_value& CVT_V1724_CHSTS_CAL_RUN_MSK))
		{
			TRACE1( "V1724 CH_STATUS[%d] calibration failed !\n", i);
			return FALSE;
		}
	}

	// Clear data
	if( !cvt_V1724_data_clear( p_data))
	{
		return FALSE;
	}

	// Resynch
	reg_value= 0;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_SW_SYNC_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_SW_SYNC write failed !\n");
		return FALSE;
	}

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_adc_temp( cvt_V1724_data* p_data, UINT8 ch_msk, UINT32* tempadc)
{
	UINT32 reg_value= 0;
	UINT32 msk32= 0;
	int i;
	UINT8 act_ch_msk;

	static const UINT16 ADC_TEMP[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_RESERVED_MEM_ADDRESS_INDEX,			/*!< \brief CH 0 Configuration register index */
		CVT_V1724_CH1_RESERVED_MEM_ADDRESS_INDEX,			/*!< \brief CH 1 Configuration register index */
		CVT_V1724_CH2_RESERVED_MEM_ADDRESS_INDEX,			/*!< \brief CH 2 Configuration register index */
		CVT_V1724_CH3_RESERVED_MEM_ADDRESS_INDEX,			/*!< \brief CH 3 Configuration register index */
		CVT_V1724_CH4_RESERVED_MEM_ADDRESS_INDEX,			/*!< \brief CH 4 Configuration register index */
		CVT_V1724_CH5_RESERVED_MEM_ADDRESS_INDEX,			/*!< \brief CH 5 Configuration register index */
		CVT_V1724_CH6_RESERVED_MEM_ADDRESS_INDEX,			/*!< \brief CH 6 Configuration register index */
		CVT_V1724_CH7_RESERVED_MEM_ADDRESS_INDEX,			/*!< \brief CH 7 Configuration register index */
	};

	//
	// Board type verify
	switch( p_data->m_type)
	{
	case CVT_V1751:
		break;
	default:
		TRACE( "V1724 cvt_V1724_adc_temp bad board type !\n");
		return FALSE;
	}


	// verify calibration 
	act_ch_msk= ch_msk &0xAA;
	for( i= 0; (i< CVT_V1724_MAX_CHANNEL )&& act_ch_msk; i++, act_ch_msk>>= 1)
	{
		if( !( act_ch_msk& 0x01))
			continue;
		// read channel status register 1
		if( !cvt_read_reg( &p_data->m_common_data, ADC_TEMP[i] , &reg_value))
		{
			TRACE1( "V1724 TEMP_ADC[%d] read failed !\n", i);
			return FALSE;
		}
		else
		tempadc[i]=reg_value;

	}
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_des_mode( cvt_V1724_data* p_data, BOOL is_des_mode)
{
	UINT8 reg_value8;
	UINT32 reg_value;
	UINT8 ch_msk;

	//
	// Board type verify
	switch( p_data->m_type)
	{
	case CVT_V1731:
	case CVT_V1751:
		break;
	default:
		TRACE( "V1724 cvt_V1724_set_des_mode bad board type !\n");
		return FALSE;
	}

	if( is_des_mode)
	{
		// 
		// Switch to des mode

		UINT16 dac_delta;
		UINT32 max_dac_steps;
		UINT16 dac_value[ CVT_V1724_MAX_CHANNEL];
		int i;
		CVT_V1724_NUM_BLOCKS num_blocks= CVT_V1724_NBLK_1024;
		UINT32 samples_read, num_events;
		// int num_samples= 4096;
		UINT8 ch_ok_msk= 0;
		UINT16 *p_buff= 0;
		const UINT32 DEF_BUFF_SIZE= 1024;
		UINT32 buff_size= DEF_BUFF_SIZE;
		double mid_scale_value; 
		double mid_scale_tolerance; 
		BOOL ret_val= TRUE;
		BOOL running= FALSE;

		//
		// Board type verify
		switch( p_data->m_type)
		{
		case CVT_V1731:
			mid_scale_value= 127.5;
			mid_scale_tolerance= 1.0;
			dac_delta= 100;
			break;
		case CVT_V1751:
			mid_scale_value= 512;
			mid_scale_tolerance= 1.0;
			dac_delta= 100;
			break;
		default:
			return FALSE;
		}
		max_dac_steps= (0xffff/ dac_delta)* 2;

		if(p_data->m_type == CVT_V1751){
			running= TRUE;
			goto exit_point;
		}

		// 
		// Switch back from des mode

		// Reset des mode bit 
		reg_value= CVT_V1724_BROAD_CHCTRL_DES_MODE_MSK;
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_CLEAR_CTRL_INDEX, &reg_value))
		{
			TRACE( "V1724 CVT_V1724_BROAD_CH_CLEAR_CTRL write failed !\n");
			ret_val= FALSE;
			goto exit_point;
		}
		p_data->m_is_des_mode= FALSE;

		if(( p_buff= ( UINT16*)malloc( buff_size* sizeof( UINT16)))== NULL)
		{
			TRACE( "V1724 error allocating samples' buffer !\n");
			ret_val= FALSE;
			goto exit_point;
		}

		// Perform channels calibration
		ch_msk= 0xff;

		if( !cvt_V1724_adc_calib( p_data, ch_msk))
		{
			ret_val= FALSE;
			goto exit_point;
		}

		// Init DAC values
		for( i= 0; i< CVT_V1724_MAX_CHANNEL; i++)
		{
			dac_value[ i]= 0x8000;
		}
		ch_msk= 0xff;
		if( !cvt_V1724_set_channel_offset( p_data, ch_msk, dac_value[ 0]))
		{
			ret_val= FALSE;
			goto exit_point;
		}
		// Wait DAC settling time
		cvt_delay( 1000);

		// Set acquisition parameters

		// Set acquisition mode
		if( !cvt_V1724_set_acquisition_mode( p_data, FALSE, num_blocks, CVT_V1724_ACQCTRL_ACQ_MODE_REGISTER_CTRL, FALSE, 0))
		{
			ret_val= FALSE;
			goto exit_point;
		}

		// Set channel trigger
		ch_msk= 0xff;
		if( !cvt_V1724_set_channel_trigger( p_data, ch_msk, 0x8000, 100))
		{
			ret_val= FALSE;
			goto exit_point;
		}

		// Set trigger mode
		if( !cvt_V1724_set_trigger_mode( p_data, FALSE, FALSE, TRUE, 0x00, FALSE, 10))
		{
			ret_val= FALSE;
			goto exit_point;
		}

		// Set VME read out mode
		if( !cvt_V1724_set_readout_mode( p_data, TRUE, 1))
		{
			ret_val= FALSE;
			goto exit_point;
		}

		// For each odd channel set DAC value to get a medium ADC value close to mid scale value
		// !!! WARNING !!! Odd channel's input signal must be disconnected

		ch_msk= 0xaa;
		// Start acquisition mode
		if( !cvt_V1724_start_acquisition( p_data, ch_msk))
		{
			ret_val= FALSE;
			goto exit_point;
		}
		running= TRUE;

		// Send data clear
		if( !cvt_V1724_data_clear( p_data))
		{
			ret_val= FALSE;
			goto exit_point;
		}
		while(( ch_ok_msk!= ch_msk)&& --max_dac_steps)
		{

			// Wait a while to have data buffer surely filled
			cvt_delay( 10);

			// Send software trigger
			if( !cvt_V1724_software_trigger( p_data))
			{
				ret_val= FALSE;
				goto exit_point;
			}

			// Get events : Just one for board will be enough
			samples_read= num_events= 0;
			if( !cvt_V1724_read_data( p_data, &samples_read, &num_events))
			{
				ret_val= FALSE;
				goto exit_point;
			}

			if( !(num_events&& samples_read))
				continue;

			// Get samples
			for( i= 0; i< CVT_V1724_MAX_CHANNEL; i++)
			{
				double mean= 0;
				int new_dac_value= 0;
				if( !( ch_msk& ( 1<< i)))
					continue;
				buff_size= DEF_BUFF_SIZE;
				if( !cvt_V1724_get_buffer_cache( p_data, 0, i, p_buff, &buff_size, &reg_value8, &reg_value, &reg_value))
				{
					ret_val= FALSE;
					goto exit_point;
				}
				if( !buff_size)
					continue;
				reg_value= buff_size;
				while( (int)(--buff_size)>= 0)
				{
					mean+= (double)p_buff[ buff_size];
				}
				mean= (double)mean/(double)reg_value;

				if( ( mean>= mid_scale_value- mid_scale_tolerance)&&
					( mean<= mid_scale_value+ mid_scale_tolerance))
				{
					// Done
					ch_ok_msk|= 1<< i;
				}
				else
				{
					new_dac_value= dac_value[ i]+ (( mean< mid_scale_value)? -dac_delta: dac_delta);
					if( ( new_dac_value< 0xffff)&&
						( new_dac_value> 0))
					{
						dac_value[ i]= ( UINT16)new_dac_value;
						// Update value
						if( !cvt_V1724_set_channel_offset( p_data, (1<< i), dac_value[ i]))
						{
							ret_val= FALSE;
							goto exit_point;
						}
					}
				}
			}
			// Wait DAC settling time
			cvt_delay( 50);
		}
		if( ch_ok_msk!= ch_msk)
		{
			TRACE( "V1724 cvt_V1724_set_des_mode procedure failed !\n");
			ret_val= FALSE;
			goto exit_point;
		}
exit_point:
		if( running)
		{
			//
			// Stop acquisition
			if( !cvt_V1724_stop_acquisition( p_data))
			{
				ret_val= FALSE;
				goto exit_point;
			}
			if( ret_val)
			{
				// Set des mode bit 
				reg_value= CVT_V1724_BROAD_CHCTRL_DES_MODE_MSK;
				if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_SET_CTRL_INDEX, &reg_value))
				{
					TRACE( "V1724 CVT_V1724_BROAD_CH_SET_CTRL write failed !\n");
					ret_val= FALSE;
					goto exit_point;
				}
				p_data->m_is_des_mode= TRUE;
			}
		}

		if( p_buff)
			free( p_buff);
		if( !ret_val)
			return FALSE;
	}
	else
	{
		// 
		// Switch back from des mode

		// Reset des mode bit 
		reg_value= CVT_V1724_BROAD_CHCTRL_DES_MODE_MSK;
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BROAD_CH_CLEAR_CTRL_INDEX, &reg_value))
		{
			TRACE( "V1724 CVT_V1724_BROAD_CH_CLEAR_CTRL write failed !\n");
			return FALSE;
		}
		p_data->m_is_des_mode= FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_interrupt( cvt_V1724_data* p_data, UINT8 level, UINT32 status_id, UINT16 event_number)
{
	UINT32 reg_value;
	//
	// interrupt level
	reg_value= level& 0x07;
	if( level!= reg_value)
	{
		TRACE( "V1724 bad interrupt level !\n");
		return FALSE;
	}
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_VME_CONTROL_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_VME_CONTROL read failed !\n");
		return FALSE;
	}
	CVT_V1724_SET_INT_LEVEL( reg_value, level);
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_VME_CONTROL_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_VME_CONTROL write failed !\n");
		return FALSE;
	}

	//
	// event number
	reg_value= event_number& 0x03ff;
	if( event_number!= reg_value)
	{
		TRACE( "V1724 bad event number !\n");
		return FALSE;
	}
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_INT_EVENT_NUM_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_INT_EVENT_NUM write failed !\n");
		return FALSE;
	}
	//
	// interrupt status id (vector)
	reg_value= status_id;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_INT_STATUS_ID_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_INT_STATUS_ID write failed !\n");
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_interrupt( cvt_V1724_data* p_data, UINT8 *p_level, UINT32 *p_status_id, UINT16 *p_event_number)
{
	UINT32 reg_value32;
	//
	// Get CVT_V1724_INT_LEVEL register value
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_VME_CONTROL_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_VME_CONTROL read failed !\n");
		return FALSE;
	}
	//
	// interrupt level
	*p_level= CVT_V1724_GET_INT_LEVEL( reg_value32);

	//
	// event number
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_INT_EVENT_NUM_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_INT_EVENT_NUM read failed !\n");
		return FALSE;
	}
	*p_event_number= reg_value32& 0x03ff;
	
	//
	// Get CVT_V1724_INT_STATUS_ID register value
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_INT_STATUS_ID_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_INT_STATUS_ID read failed !\n");
		return FALSE;
	}
	//
	// interrupt status_id
	*p_status_id= ( UINT8)reg_value32;
	
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_readout_mode( cvt_V1724_data* p_data, BOOL enable_bus_error, UINT32 BLT_event_number)
{
	UINT32 set_msk= 0;
	UINT32 clear_msk= 0;
	
	//
	// Bus error
	set_msk|= ( enable_bus_error)? CVT_V1724_VME_CTRL_BERR_ENABLE_MSK: 0;
	clear_msk|= ( enable_bus_error)? 0: CVT_V1724_VME_CTRL_BERR_ENABLE_MSK;
	
	//
	// bitmask set
	if( set_msk)
	{
		if( !cvt_set_bitmask_reg( &p_data->m_common_data, CVT_V1724_VME_CONTROL_INDEX, &set_msk))
		{
			TRACE( "V1724 CVT_V1724_VME_CONTROL write failed !\n");
			return FALSE;
		}
	}
	//
	// bitmask clear
	if( clear_msk)
	{
		// clear the enable bit
		if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CVT_V1724_VME_CONTROL_INDEX, &clear_msk))
		{
			TRACE( "V1724 CVT_V1724_CONTROL write failed !\n");
			return FALSE;
		}
	}

	// 
	// BLT event number
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_BLT_EVENT_NUM_INDEX, &BLT_event_number))
	{
		TRACE( "V1724 CVT_V1724_BLT_EVENT_NUM write failed !\n");
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_readout_mode( cvt_V1724_data* p_data, BOOL *p_enable_bus_error, UINT32 *p_BLT_event_number)
{
	UINT32 reg_value32= 0;

	//
	// Gets the CVT_V1724_CONTROL parameter 
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_VME_CONTROL_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_VME_CONTROL read failed !\n");
		return FALSE;
	}
	//
	// Bus error
	*p_enable_bus_error= ( reg_value32&  CVT_V1724_VME_CTRL_BERR_ENABLE_MSK)? TRUE: FALSE;

	// 
	// Get BLT event number
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_BLT_EVENT_NUM_INDEX, p_BLT_event_number))
	{
		TRACE( "V1724 CVT_V1724_BLT_EVENT_NUM read failed !\n");
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_software_reset( cvt_V1724_data* p_data)
{
	//
	// Write CVT_V1724_SW_RESET register
	UINT32 reg_value= 0;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_SW_RESET_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_SW_RESET write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_data_clear( cvt_V1724_data* p_data)
{
	//
	// Write CVT_V1724_SW_RESET register
	UINT32 reg_value= 0;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_SW_CLEAR_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_CLEAR_RESET write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_channel_offset( cvt_V1724_data* p_data, UINT8 ch_msk, UINT16 offset_value)
{
	static const UINT16 CH_DAC_CONF[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_DAC_CONF_INDEX,		/*!< \brief CH 0 DAC Data Configuration register index */
		CVT_V1724_CH1_DAC_CONF_INDEX,		/*!< \brief CH 1 DAC Data Configuration register index */
		CVT_V1724_CH2_DAC_CONF_INDEX,		/*!< \brief CH 2 DAC Data Configuration register index */
		CVT_V1724_CH3_DAC_CONF_INDEX,		/*!< \brief CH 3 DAC Data Configuration register index */
		CVT_V1724_CH4_DAC_CONF_INDEX,		/*!< \brief CH 4 DAC Data Configuration register index */
		CVT_V1724_CH5_DAC_CONF_INDEX,		/*!< \brief CH 5 DAC Data Configuration register index */
		CVT_V1724_CH6_DAC_CONF_INDEX,		/*!< \brief CH 6 DAC Data Configuration register index */
		CVT_V1724_CH7_DAC_CONF_INDEX,		/*!< \brief CH 7 DAC Data Configuration register index */
	};
	UINT32 reg_value_A= 0, reg_value_B= 0;
	//
	// Channel offset

	//
	// Data for DAC A ( even channels)
	CVT_V1724_SET_CH_DAC_CONF( reg_value_A, offset_value);
	reg_value_A|= CVT_V1724_CHDAC_SET_A_MSK;
	//
	// Data for DAC B ( odd channels)
	CVT_V1724_SET_CH_DAC_CONF( reg_value_B, offset_value);
	reg_value_B|= CVT_V1724_CHDAC_SET_B_MSK;


	//if( p_data->m_type== CVT_V1740) {
	//	// Grp. Grp. DAC
	//	//  0    1    0
	//	//  2    3    2
	//	//  4    5    4
	//	//  6    7    6
	//	UINT8 tmp_msk= ch_msk;
	//	ch_msk= 0;
	//	ch_msk|= ( tmp_msk& (0x03))? 0x01: 0x00;
	//	ch_msk|= ( tmp_msk& (0x0C))? 0x04: 0x00;
	//	ch_msk|= ( tmp_msk& (0x30))? 0x10: 0x00;
	//	ch_msk|= ( tmp_msk& (0xC0))? 0x40: 0x00;
	//}
	//
	// setup each channel
	{
		int i;
		for( i= 0; (i< CVT_V1724_MAX_CHANNEL )&& ch_msk; i++, ch_msk>>= 1)
		{
			if( ch_msk& 0x01)
			{
				//
				// Wait for DAC !busy
				BOOL trash;
				BOOL is_dac_busy= TRUE;
				while( is_dac_busy)
				{
					// HACK insert timeout here

					if( !cvt_V1724_get_channel_status( p_data, i, &is_dac_busy, &trash, &trash, &trash))
					{
						TRACE( "V1724 set channel offset failed !\n");
						return FALSE;
					}
				}
				if( !cvt_write_reg( &p_data->m_common_data, CH_DAC_CONF[ i], ( i& 0x01)? &reg_value_B: &reg_value_A))
				{
					TRACE( "V1724 CH DAC CONF write failed !\n");
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_channel_offset( cvt_V1724_data* p_data, UINT8 ch_index, UINT16 *p_offset_value)
{
	static const UINT16 CH_DAC_CONF[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_DAC_CONF_INDEX,		/*!< \brief CH 0 DAC Data Configuration register index */
		CVT_V1724_CH1_DAC_CONF_INDEX,		/*!< \brief CH 1 DAC Data Configuration register index */
		CVT_V1724_CH2_DAC_CONF_INDEX,		/*!< \brief CH 2 DAC Data Configuration register index */
		CVT_V1724_CH3_DAC_CONF_INDEX,		/*!< \brief CH 3 DAC Data Configuration register index */
		CVT_V1724_CH4_DAC_CONF_INDEX,		/*!< \brief CH 4 DAC Data Configuration register index */
		CVT_V1724_CH5_DAC_CONF_INDEX,		/*!< \brief CH 5 DAC Data Configuration register index */
		CVT_V1724_CH6_DAC_CONF_INDEX,		/*!< \brief CH 6 DAC Data Configuration register index */
		CVT_V1724_CH7_DAC_CONF_INDEX,		/*!< \brief CH 7 DAC Data Configuration register index */
	};
	UINT32 reg_value32= 0;
	BOOL trash;
	BOOL is_dac_busy= TRUE;

	//
	// input param check
	if( ch_index>= CVT_V1724_MAX_CHANNEL)
	{
		TRACE1( "V1724 cvt_V1724_get_channel_offset bad channel '%d'!\n", ch_index);
		return FALSE;
	}


	//if( p_data->m_type== CVT_V1740) {
	//	// Grp. Grp. DAC
	//	//  0    1    0
	//	//  2    3    2
	//	//  4    5    4
	//	//  6    7    6
	//	ch_index&= ~0x01;
	//}

	//
	// Wait for DAC !busy
	while( is_dac_busy)
	{
		// HACK insert timeout here
		if( !cvt_V1724_get_channel_status( p_data, ch_index, &is_dac_busy, &trash, &trash, &trash))
		{
			TRACE( "V1724 set channel offset failed !\n");
			return FALSE;
		}
	}
	//
	// Get CVT_V1724_CH#_DAC_CONF register value
	if( !cvt_read_reg( &p_data->m_common_data, CH_DAC_CONF[ ch_index], &reg_value32))
	{
		TRACE( "V1724 CH DAC CONF read failed !\n");
		return FALSE;
	}
	//
	// Channel offset
	*p_offset_value= CVT_V1724_GET_CH_DAC_CONF( reg_value32);

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_channel_trigger( cvt_V1724_data* p_data, UINT8 ch_msk, UINT32 trigger_threshold, UINT32 threshold_samples)
{
	static const UINT16 CH_TRG_THR[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_THRESHOLD_INDEX,					/*!< \brief CH 0 Threshold register index */
		CVT_V1724_CH1_THRESHOLD_INDEX,					/*!< \brief CH 1 Threshold register index */
		CVT_V1724_CH2_THRESHOLD_INDEX,					/*!< \brief CH 2 Threshold register index */
		CVT_V1724_CH3_THRESHOLD_INDEX,					/*!< \brief CH 3 Threshold register index */
		CVT_V1724_CH4_THRESHOLD_INDEX,					/*!< \brief CH 4 Threshold register index */
		CVT_V1724_CH5_THRESHOLD_INDEX,					/*!< \brief CH 5 Threshold register index */
		CVT_V1724_CH6_THRESHOLD_INDEX,					/*!< \brief CH 6 Threshold register index */
		CVT_V1724_CH7_THRESHOLD_INDEX,					/*!< \brief CH 7 Threshold register index */
	};

	static const UINT16 CH_TRG_THR_SAMPLE[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 0 Over/Under Threshold Samples register index */
		CVT_V1724_CH1_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 1 Over/Under Threshold Samples register index */
		CVT_V1724_CH2_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 2 Over/Under Threshold Samples register index */
		CVT_V1724_CH3_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 3 Over/Under Threshold Samples register index */
		CVT_V1724_CH4_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 4 Over/Under Threshold Samples register index */
		CVT_V1724_CH5_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 5 Over/Under Threshold Samples register index */
		CVT_V1724_CH6_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 6 Over/Under Threshold Samples register index */
		CVT_V1724_CH7_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 7 Over/Under Threshold Samples register index */
	};

	//
	// trigger threshold
	{
		int i;
		UINT8 tmp_msk= ch_msk;
		UINT32 reg_value= trigger_threshold;
		for( i= 0; (i< CVT_V1724_MAX_CHANNEL )&& tmp_msk; i++, tmp_msk>>= 1)
		{
			if( tmp_msk& 0x01)
			{
				if( !cvt_write_reg( &p_data->m_common_data, CH_TRG_THR[ i], &reg_value))
				{
					TRACE( "V1724 CH TRIGGER THRESHOLD write failed !\n");
					return FALSE;
				}
			}
		}
	}

	//
	// trigger threshold samples
	{
		int i;
		UINT8 tmp_msk= ch_msk;
		UINT32 reg_value= threshold_samples;
		for( i= 0; (i< CVT_V1724_MAX_CHANNEL)&& tmp_msk; i++, tmp_msk>>= 1)
		{
			if( tmp_msk& 0x01)
			{
				if( !cvt_write_reg( &p_data->m_common_data, CH_TRG_THR_SAMPLE[ i], &reg_value))
				{
					TRACE( "V1724 CH TRIGGER THRESHOLD SAMPLES write failed !\n");
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_channel_trigger( cvt_V1724_data* p_data, UINT8 ch_index, UINT32 *p_trigger_threshold, UINT32 *p_threshold_samples)
{
	static const UINT16 CH_TRG_THR[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_THRESHOLD_INDEX,					/*!< \brief CH 0 Threshold register index */
		CVT_V1724_CH1_THRESHOLD_INDEX,					/*!< \brief CH 1 Threshold register index */
		CVT_V1724_CH2_THRESHOLD_INDEX,					/*!< \brief CH 2 Threshold register index */
		CVT_V1724_CH3_THRESHOLD_INDEX,					/*!< \brief CH 3 Threshold register index */
		CVT_V1724_CH4_THRESHOLD_INDEX,					/*!< \brief CH 4 Threshold register index */
		CVT_V1724_CH5_THRESHOLD_INDEX,					/*!< \brief CH 5 Threshold register index */
		CVT_V1724_CH6_THRESHOLD_INDEX,					/*!< \brief CH 6 Threshold register index */
		CVT_V1724_CH7_THRESHOLD_INDEX,					/*!< \brief CH 7 Threshold register index */
	};

	static const UINT16 CH_TRG_THR_SAMPLE[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 0 Over/Under Threshold Samples register index */
		CVT_V1724_CH1_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 1 Over/Under Threshold Samples register index */
		CVT_V1724_CH2_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 2 Over/Under Threshold Samples register index */
		CVT_V1724_CH3_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 3 Over/Under Threshold Samples register index */
		CVT_V1724_CH4_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 4 Over/Under Threshold Samples register index */
		CVT_V1724_CH5_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 5 Over/Under Threshold Samples register index */
		CVT_V1724_CH6_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 6 Over/Under Threshold Samples register index */
		CVT_V1724_CH7_TIME_OVER_UNDER_THR_INDEX,				/*!< \brief CH 7 Over/Under Threshold Samples register index */
	};

	//
	// input param check
	if( ch_index>= CVT_V1724_MAX_CHANNEL)
	{
		TRACE1( "V1724 cvt_V1724_get_channel_trigger bad channel '%d'!\n", ch_index);
		return FALSE;
	}

	//
	// trigger threshold
	if( !cvt_read_reg( &p_data->m_common_data, CH_TRG_THR[ ch_index], p_trigger_threshold))
	{
		TRACE( "V1724 CH TRIGGER THRESHOLD read failed !\n");
		return FALSE;
	}

	//
	// trigger threshold samples
	if( !cvt_read_reg( &p_data->m_common_data, CH_TRG_THR_SAMPLE[ ch_index], p_threshold_samples))
	{
		TRACE( "V1724 CH TRIGGER THRESHOLD SAMPLES read failed !\n");
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_front_panel_IO( cvt_V1724_data* p_data, BOOL use_TTL, BOOL out_en, UINT8 dir_msk, CVT_V1724_FRONT_PANEL_IO_MODES mode)
{
	UINT32 reg_value32= 0;
	
	//
	// Validity check
	switch( mode)
	{
		case CVT_V1724_FPIO_MODES_GPIO:			/*!< General purpose IO */
		case CVT_V1724_FPIO_MODES_PROGIO:		/*!< Programmed IO */
		case CVT_V1724_FPIO_MODES_PATTERN:		/*!< Pattern mode */
			break;
		default:
			TRACE( "V1724 CVT_V1724_FRONT_PANEL_IO_CTRL bad mode !\n");
			return FALSE;			
	}

	//
	// Ttl/Nim
	reg_value32|= ( use_TTL)? CVT_V1724_FPIO_CTRL_TTL_MSK: 0;

	//
	// Output enable
	reg_value32|= ( out_en)? 0: CVT_V1724_FPIO_CTRL_OUT_DIS_MSK;

	//
	// Direction
	CVT_V1724_SET_FPIO_CTRL_DIR( reg_value32, dir_msk);

	//
	// Operational mode
	CVT_V1724_SET_FPIO_CTRL_MODE( reg_value32, mode);

	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FRONT_PANEL_IO_CTRL_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_FRONT_PANEL_IO_CTRL write failed !\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_front_panel_IO( cvt_V1724_data* p_data, BOOL *p_use_TTL, BOOL *p_is_out_en, UINT8 *p_dir_msk, CVT_V1724_FRONT_PANEL_IO_MODES *p_mode)
{
	UINT32 reg_value32= 0;
	
	//
	// Get the CVT_V1724_FRONT_PANEL_IO_CTRL register value
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_FRONT_PANEL_IO_CTRL_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_FRONT_PANEL_IO_CTRL read failed !\n");
		return FALSE;
	}
	//
	// Ttl / Nim
	*p_use_TTL= ( reg_value32& CVT_V1724_FPIO_CTRL_TTL_MSK)? TRUE: FALSE;


	//
	// Output enable
	*p_is_out_en= ( reg_value32& CVT_V1724_FPIO_CTRL_OUT_DIS_MSK)? FALSE: TRUE;

	//
	// Direction
	*p_dir_msk= CVT_V1724_GET_FPIO_CTRL_DIR( reg_value32);

	//
	// Operational mode
	*p_mode= CVT_V1724_GET_FPIO_CTRL_MODE( reg_value32);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_software_trigger( cvt_V1724_data* p_data)
{
	UINT32 reg_value;
	//
	// software trigger
	reg_value= 1;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_SW_TRIGGER_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_SW_TRIGGER write failed !\n");
		return FALSE;
	}
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_channel_status( cvt_V1724_data* p_data, UINT8 ch_index, BOOL *p_is_dac_busy, BOOL *p_is_fifo_full, BOOL *p_is_fifo_empty, BOOL *p_is_block_remove_ok)
{
	static const UINT16 CH_STATUS[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_STATUS_INDEX,						/*!< \brief CH 0 status register relative address */
		CVT_V1724_CH1_STATUS_INDEX,						/*!< \brief CH 1 status register relative address */
		CVT_V1724_CH2_STATUS_INDEX,						/*!< \brief CH 2 status register relative address */
		CVT_V1724_CH3_STATUS_INDEX,						/*!< \brief CH 3 status register relative address */
		CVT_V1724_CH4_STATUS_INDEX,						/*!< \brief CH 4 status register relative address */
		CVT_V1724_CH5_STATUS_INDEX,						/*!< \brief CH 5 status register relative address */
		CVT_V1724_CH6_STATUS_INDEX,						/*!< \brief CH 6 status register relative address */
		CVT_V1724_CH7_STATUS_INDEX,						/*!< \brief CH 7 status register relative address */
	};

	UINT32 reg_value= 0;

	//
	// input param check
	if( ch_index>= CVT_V1724_MAX_CHANNEL)
	{
		TRACE1( "V1724 cvt_V1724_get_channel_status bad channel '%d'!\n", ch_index);
		return FALSE;
	}
	//
	// read channel status register 1
	if( !cvt_read_reg( &p_data->m_common_data, CH_STATUS[ ch_index], &reg_value))
	{
		TRACE1( "V1724 CH_STATUS[%d] read failed !\n", ch_index);
		return FALSE;
	}
	*p_is_dac_busy= ( reg_value& CVT_V1724_CHSTS_DAC_BUSY_MSK)? TRUE: FALSE;
	*p_is_fifo_full= ( reg_value& CVT_V1724_CHSTS_FIFO_FULL_MSK)? TRUE: FALSE;
	*p_is_fifo_empty= ( reg_value& CVT_V1724_CHSTS_FIFO_EMPTY_MSK)? TRUE: FALSE;
	*p_is_block_remove_ok= ( reg_value& CVT_V1724_CHSTS_BLOCK_REM_OK_MSK)? TRUE: FALSE;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_system_info( cvt_V1724_data* p_data, UINT16 *p_firmware_rev, CVT_V1724_ROM_CONFIG *p_rom_config, BOOL *p_is_board_type_correct, BOOL *p_is_firmware_rev_correct)
{
	UINT32 reg_value= 0;
	*p_is_board_type_correct= FALSE;
	*p_is_firmware_rev_correct= FALSE;

	//
	// Firmware revision register
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_FW_REV_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FW_REV read failed !\n");
		return FALSE;
	}
	*p_firmware_rev= reg_value& 0x0000ffff;
	if( *p_firmware_rev>= CVT_V1724_MIN_FIRMARE_REV)
		*p_is_firmware_rev_correct= TRUE;

	//
	// Chksum
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_CHKSUM_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_CHKSUM_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_chksum= reg_value& 0x000000ff;

	//
	// Chksum Len
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_CHKSUM_LEN_0_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_CHKSUM_LEN_0_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_chksum_len= reg_value& 0x000000ff;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_CHKSUM_LEN_1_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_CHKSUM_LEN_1_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_chksum_len|= (reg_value& 0x000000ff)<< 8;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_CHKSUM_LEN_2_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_CHKSUM_LEN_2_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_chksum_len|= (reg_value& 0x000000ff)<< 16;

	//
	// Const
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_CONST_0_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_CONST_0_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_const= reg_value& 0x000000ff;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_CONST_1_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_CONST_1_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_const|= (reg_value& 0x000000ff)<< 8;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_CONST_2_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_CONST_2_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_const|= (reg_value& 0x000000ff)<< 16;

	//
	// c_code
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_C_CODE_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_C_CODE_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_c_code= reg_value& 0x000000ff;

	//
	// r_code
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_R_CODE_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_R_CODE_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_r_code= reg_value& 0x000000ff;

	//
	// OUI
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_OUI_0_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_OUI_0_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_OUI= reg_value& 0x000000ff;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_OUI_1_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_OUI_1_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_OUI|= (reg_value& 0x000000ff)<< 8;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_OUI_2_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_OUI_2_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_OUI|= (reg_value& 0x000000ff)<< 16;

	//
	// version
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_VERSION_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_VERSION_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_version= reg_value& 0x000000ff;

	//
	// Board id
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_BOARD_ID_0_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_BOARD_ID_0_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_board_id= reg_value& 0x000000ff;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_BOARD_ID_1_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_BOARD_ID_1_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_board_id|= (reg_value& 0x000000ff)<< 8;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_BOARD_ID_2_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_BOARD_ID_2_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_board_id|= (reg_value& 0x000000ff)<< 16;

	switch( p_rom_config->m_board_id)
	{
	case CVT_V17XX_RCFG_BOARD_ID_V1724:			//  V1724
	case CVT_V17XX_RCFG_BOARD_ID_VX1724:		// VX1724
		if( p_data->m_type== CVT_V1724)
			*p_is_board_type_correct= TRUE;
		break;
	case CVT_V17XX_RCFG_BOARD_ID_V1721:			//  V1721
	case CVT_V17XX_RCFG_BOARD_ID_VX1721:		// VX1721
		if( p_data->m_type== CVT_V1721)
			*p_is_board_type_correct= TRUE;
		break;
	case CVT_V17XX_RCFG_BOARD_ID_V1731:			//  V1731
	case CVT_V17XX_RCFG_BOARD_ID_VX1731:		// VX1731
		if( p_data->m_type== CVT_V1731)
			*p_is_board_type_correct= TRUE;
		break;
	case CVT_V17XX_RCFG_BOARD_ID_V1720:			//  V1720
	case CVT_V17XX_RCFG_BOARD_ID_VX1720:		// VX1720
		if( p_data->m_type== CVT_V1720)
			*p_is_board_type_correct= TRUE;
		break;
	case CVT_V17XX_RCFG_BOARD_ID_V1740:			//  V1740
	case CVT_V17XX_RCFG_BOARD_ID_VX1740:		// VX1740
		if( p_data->m_type== CVT_V1740)
			*p_is_board_type_correct= TRUE;
		break;
	case CVT_V17XX_RCFG_BOARD_ID_V1751:			//  V1751
	case CVT_V17XX_RCFG_BOARD_ID_VX1751:		// VX1751
		if( p_data->m_type== CVT_V1751)
			*p_is_board_type_correct= TRUE;
		break;
	}

	//
	// Revision
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_REVISION_0_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_REVISION_0_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_revision= reg_value& 0x000000ff;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_REVISION_1_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_REVISION_1_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_revision|= (reg_value& 0x000000ff)<< 8;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_REVISION_2_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_REVISION_2_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_revision|= (reg_value& 0x000000ff)<< 16;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_REVISION_3_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_REVISION_3_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_revision|= (reg_value& 0x000000ff)<< 24;

	//
	// Serial number
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_SERIAL_0_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_SERIAL_LSB read failed !\n");
		return FALSE;
	}
	p_rom_config->m_serial= reg_value& 0x00ff;
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_SERIAL_1_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_SERIAL_MSB read failed !\n");
		return FALSE;
	}
	p_rom_config->m_serial|= (reg_value& 0x00ff)<< 8;

	//
	// VCXO type
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_ROM_VCXO_TYPE_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_ROM_VCXO_TYPE_INDEX read failed !\n");
		return FALSE;
	}
	p_rom_config->m_VCXO_type= reg_value& 0x000000ff;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_channel_info( cvt_V1724_data* p_data, UINT8 ch_index, UINT16 *p_firmware_rev)
{
	static const UINT16 CH_FW_REV[ CVT_V1724_MAX_CHANNEL]=
	{
		CVT_V1724_CH0_FW_REV_INDEX,						/*!< \brief CH 0 firmware revision register relative index */
		CVT_V1724_CH1_FW_REV_INDEX,						/*!< \brief CH 1 firmware revision register relative index */
		CVT_V1724_CH2_FW_REV_INDEX,						/*!< \brief CH 2 firmware revision register relative index */
		CVT_V1724_CH3_FW_REV_INDEX,						/*!< \brief CH 3 firmware revision register relative index */
		CVT_V1724_CH4_FW_REV_INDEX,						/*!< \brief CH 4 firmware revision register relative index */
		CVT_V1724_CH5_FW_REV_INDEX,						/*!< \brief CH 5 firmware revision register relative index */
		CVT_V1724_CH6_FW_REV_INDEX,						/*!< \brief CH 6 firmware revision register relative index */
		CVT_V1724_CH7_FW_REV_INDEX,						/*!< \brief CH 7 firmware revision register relative index */
	};

	UINT32 reg_value= 0;

	//
	// input param check
	if( ch_index>= CVT_V1724_MAX_CHANNEL)
	{
		TRACE1( "V1724 cvt_V1724_get_channel_info bad channel '%d'!\n", ch_index);
		return FALSE;
	}

	//
	// read channel Fw rev register 1
	if( !cvt_read_reg( &p_data->m_common_data, CH_FW_REV[ ch_index], &reg_value))
	{
		TRACE1( "V1724 CH_FW_REV[%d] read failed !\n", ch_index);
		return FALSE;
	}
	*p_firmware_rev= reg_value& 0x0000ffff;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_set_MCST_CBLT( cvt_V1724_data* p_data, UINT8 address, MCST_CBLT_board_pos pos)
{
	UINT32 reg_value= 0;
	//
	// MCST/CBLT address register
	CVT_V1724_SET_MCST_CBLT_ADD( reg_value, address);
	//
	// MCST/CBLT control register
	switch( pos)
	{
	case MCST_CBLT_board_pos_first:
		CVT_V1724_SET_MCST_CBLT_CTRL( reg_value, CVT_V1724_MCST_CBLT_CTRL_FIRST_BOARD);
		break;
	case MCST_CBLT_board_pos_mid:
		CVT_V1724_SET_MCST_CBLT_CTRL( reg_value, CVT_V1724_MCST_CBLT_CTRL_MID_BOARD);
		break;
	case MCST_CBLT_board_pos_last:
		CVT_V1724_SET_MCST_CBLT_CTRL( reg_value, CVT_V1724_MCST_CBLT_CTRL_LAST_BOARD);
		break;
	case MCST_CBLT_board_disabled:
		CVT_V1724_SET_MCST_CBLT_CTRL( reg_value, CVT_V1724_MCST_CBLT_CTRL_DISABLED_BOARD);
		break;
	default:
		TRACE1( "V1724 cvt_V1724_set_MCST_CBLT bad position indentifier '%d'!\n", pos);
		return FALSE;
	}

	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_MCST_CBLT_ADD_CTRL_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_MCST_CBLT_ADD_CTRL write failed !\n");
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_get_MCST_CBLT( cvt_V1724_data* p_data, UINT8 *p_address, MCST_CBLT_board_pos *p_pos)
{
	UINT32 reg_value32;
	//
	// Get MCST/CBLT address register
	if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_MCST_CBLT_ADD_CTRL_INDEX, &reg_value32))
	{
		TRACE( "V1724 CVT_V1724_MCST_CBLT_ADD_CTRL read failed !\n");
		return FALSE;
	}
	*p_address= CVT_V1724_GET_MCST_CBLT_ADD( reg_value32);

	switch( CVT_V1724_GET_MCST_CBLT_CTRL( reg_value32))
	{
	case CVT_V1724_MCST_CBLT_CTRL_FIRST_BOARD:
		*p_pos= MCST_CBLT_board_pos_first;
		break;
	case CVT_V1724_MCST_CBLT_CTRL_MID_BOARD:
		*p_pos= MCST_CBLT_board_pos_mid;
		break;
	case CVT_V1724_MCST_CBLT_CTRL_LAST_BOARD:
		*p_pos= MCST_CBLT_board_pos_last;
		break;
	case CVT_V1724_MCST_CBLT_CTRL_DISABLED_BOARD:
		*p_pos= MCST_CBLT_board_disabled;
		break;
	default:
		TRACE1( "V1724 cvt_V1724_get_MCST_CBLT bad position indentifier '%d'!\n", reg_value32);
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_write_flash_page( cvt_V1724_data* p_data, const UINT8* page_buff, UINT32 page_index)
{
	int i;
	UINT32 reg_value;
	UINT32 flash_addr;
	BOOL ret_val= TRUE;

	flash_addr= page_index << 9;

	//
	// enable flash
	reg_value= CVT_V1724_FLEN_EN_MSK;
	if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CVT_V1724_FLASH_EN_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH_EN write failed !\n");
		return FALSE;
	}

	// write opcode
	reg_value= CVT_V1724_FOP_PAGE_PROG_TH_BUF1;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
	// write address
	reg_value= (unsigned char)( flash_addr>> 16);
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
	reg_value= (unsigned char)( flash_addr>> 8);
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
	reg_value= (unsigned char) flash_addr;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
	// write flash page
	for (i= 0; i< V1724_FLASH_PAGE_SIZE; i++)
	{
		reg_value= page_buff[ i];
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
		{
			TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
			ret_val= FALSE;
			goto exit_point;
		}
	}

exit_point:
	// disable flash
	reg_value= CVT_V1724_FLEN_EN_MSK;
	if( !cvt_set_bitmask_reg( &p_data->m_common_data, CVT_V1724_FLASH_EN_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH_EN write failed !\n");
		ret_val= FALSE;
	}

	// wait 50ms
	cvt_delay( 50);
	return ret_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_read_flash_page( cvt_V1724_data* p_data, UINT8* page_buff, UINT32 page_index)
{
	int i;
	UINT32 reg_value;
	UINT32 flash_addr;
	BOOL ret_val= TRUE;

	flash_addr= page_index<< 9;

	// enable flash (NCS = 0)
	reg_value= CVT_V1724_FLEN_EN_MSK;
	if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CVT_V1724_FLASH_EN_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH_EN write failed !\n");
		return FALSE;
	}

	// write opcode
	reg_value= CVT_V1724_FOP_PAGE_READ;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
	// write address
	reg_value= (unsigned char)( flash_addr>> 16);
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
	reg_value= (unsigned char)( flash_addr>> 8);
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
	reg_value= (unsigned char) flash_addr;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}


	// additional don't care bytes
	for( i=0; i<4; i++)
	{
		reg_value= 0;
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
		{
			TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
			ret_val= FALSE;
			goto exit_point;
		}
	}

	// read flash page
	for (i= 0; i< V1724_FLASH_PAGE_SIZE; i++)
	{
		if( !cvt_read_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
		{
			TRACE( "V1724 CVT_V1724_FLASH read failed !\n");
			ret_val= FALSE;
			goto exit_point;
		}
		page_buff[ i]= ( UINT8)reg_value;
	}

exit_point:
	// disable flash (NCS = 1)
	reg_value= CVT_V1724_FLEN_EN_MSK;
	if( !cvt_set_bitmask_reg( &p_data->m_common_data, CVT_V1724_FLASH_EN_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH_EN write failed !\n");
		ret_val= FALSE;
	}

	return ret_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_erase_flash_page( cvt_V1724_data* p_data, UINT32 page_index)
{
	UINT32 reg_value;
	UINT32 flash_addr;
	BOOL ret_val= TRUE;

	flash_addr= page_index<< 9;

	// enable flash (NCS = 0)
	reg_value= CVT_V1724_FLEN_EN_MSK;
	if( !cvt_clear_bitmask_reg( &p_data->m_common_data, CVT_V1724_FLASH_EN_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH_EN write failed !\n");
		return FALSE;
	}

	// write opcode
	reg_value= CVT_V1724_FOP_PAGE_ERASE;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
	// write address
	reg_value= (unsigned char)( flash_addr>> 16);
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
	reg_value= (unsigned char)( flash_addr>> 8);
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
	reg_value= (unsigned char) flash_addr;
	if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_FLASH_DATA_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
		ret_val= FALSE;
		goto exit_point;
	}
exit_point:
	// disable flash (NCS = 1)
	reg_value= CVT_V1724_FLEN_EN_MSK;
	if( !cvt_set_bitmask_reg( &p_data->m_common_data, CVT_V1724_FLASH_EN_INDEX, &reg_value))
	{
		TRACE( "V1724 CVT_V1724_FLASH_EN write failed !\n");
		ret_val= FALSE;
	}

	return ret_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_fw_upgrade( cvt_V1724_data* p_data, const UINT8* data_buff, UINT32 data_size, CVT_V1724_FLASH_BANK flash_bank, BOOL (* call_back)(UINT32 written_bytes))
{
	// HACK to be rewritten with block trasfer mode
	UINT32 tot_bytes= 0;
	UINT8 tmp_page_w[ V1724_FLASH_PAGE_SIZE], tmp_page_r[ V1724_FLASH_PAGE_SIZE];

	switch( flash_bank)
	{
	case CVT_V1724_FB_STANDARD:		// Standard (boot) flash page
	case CVT_V1724_FB_BACKUP:		// Backup flash page
		break;
	default:
		TRACE( "V1724 cvt_V1724_fw_upgrade Invalid flash bank!\n");
		return FALSE;
	}

	// Swap bits into data bytes
	while( tot_bytes< data_size)
	{
		int i;
		// pepare temporary page to write
		for( i= 0; ( i< V1724_FLASH_PAGE_SIZE)&& ( tot_bytes< data_size); i++)
		{
			// bitwise byte rotation
			tmp_page_w[ i]= cvt_swap_bits( data_buff[ tot_bytes++]);
		}
		// write page to flash
		if( !cvt_V1724_write_flash_page( p_data, tmp_page_w, flash_bank))
		{
			TRACE( "V1724 CVT_V1724_FLASH write failed !\n");
			return FALSE;
		}
		// read page from flash
		if( !cvt_V1724_read_flash_page( p_data, tmp_page_r, flash_bank))
		{
			TRACE( "V1724 CVT_V1724_FLASH read failed !\n");
			return FALSE;
		}
		// verify pages
		if( memcmp( tmp_page_r, tmp_page_w, V1724_FLASH_PAGE_SIZE))
		{
			// read page differs from page written 
			TRACE( "V1724 cvt_V1724_fw_upgrade page verify failure!\n");
			return FALSE;
		}
		++flash_bank;
		if( call_back)
		{
			if( !(*call_back)( tot_bytes))
				return FALSE;
		}
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_V1724_pll_upgrade( cvt_V1724_data* p_data, const char* filename)
{
	BOOL ret= TRUE;
	UINT8 page[ V1724_FLASH_PAGE_SIZE];
	char file_line[300];
	// int org_line= 15;
	int i;
	int data_size;
	FILE *from;

	if( ( from= fopen( filename, "rt"))== NULL)
	{
		TRACE( "V1724 cvt_V1724_pll_upgrade file open failure!\n");
		return FALSE;
	}
	// Strip header lines
	for( i= 0; i< 4; i++)
	{
		if( fgets( file_line, 300, from)== NULL)
		{
			TRACE( "V1724 cvt_V1724_pll_upgrade bad file format !\n");
			ret= FALSE;
			goto exit_point;						
		}
	}
	data_size= 0;
	// Get data lines
	while( TRUE)
	{
		char *token;
		char *trash;
		int value;
		if( fgets( file_line, 300, from)== NULL)
		{
			if( !feof( from))
			{
				TRACE( "V1724 cvt_V1724_pll_upgrade file read error !\n");
				ret= FALSE;
				goto exit_point;
			}
			break;
		}
		if( data_size>= V1724_FLASH_PAGE_SIZE)
		{
			TRACE( "V1724 cvt_V1724_pll_upgrade file too large for flash page size !\n");
			ret= FALSE;
			goto exit_point;
		}
		// Get Address
		token= strtok( file_line, ",");
		// Skip a value
		trash= strtok( NULL, ",");

		if( ( token== 0)|| (trash== 0))
			break;
		if( !strcmp( token, "\"\""))
			break;
		sscanf( token, "\"%x\"", &value);
		page[ data_size++]= value& 0xff;

		// Get value
		token= strtok( NULL, ",");
		sscanf( token, "\"%x\"", &value);
		page[ data_size++]= value& 0xff;
	}

	if( !cvt_V1724_write_flash_page( p_data, page, CVT_V1724_PLL_FLASH_PAGE))
	{
		TRACE( "V1724 cvt_V1724_pll_upgrade flash write failed !\n");
		ret= FALSE;
		goto exit_point;
	}

	//
	// Reload configuration
	{
		UINT32 reg_value32= 0;
		if( !cvt_write_reg( &p_data->m_common_data, CVT_V1724_RELOAD_CONFIG_INDEX, &reg_value32))
		{
			TRACE( "V1724 CVT_V1724_RELOAD_CONFIG_INDEX write failed !\n");
			ret= FALSE;
			goto exit_point;
		}
	}
exit_point:
	if( from)
	{
		fclose( from);
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     M I S C E L L A N E O U S   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
const char* cvt_V1724_SW_rev( void)
{
	return "CAENdigitizerSDK Rev. 1.3";
}
