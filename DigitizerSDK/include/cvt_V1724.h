////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file    cvt_V1724.h
*   \brief   V1724 VME board definitions
*   \author  NDA
*   \version 1.0
*   \date    10/2006
*            
*            Provides methods, properties and defines to handle V1724 VME boards
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CVT_V1724_DEF_H
#define __CVT_V1724_DEF_H

////////////////////////////////////////////////////////////////////////////////////////////////
// File includes
////////////////////////////////////////////////////////////////////////////////////////////////
#include "cvt_common_defs.h"
#include "cvt_board_commons.h"
////////////////////////////////////////////////////////////////////////////////////////////////
// Global defines
////////////////////////////////////////////////////////////////////////////////////////////////

#define CVT_V1724_THRESHOLD_NUM			8			/*!< \brief Number of threshold registers */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V17XX_TYPES
*   \brief   The V17XX board type
*            
*            Provides an entry for each board type
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724= 0,						/*!< \brief The board is V1724 */
	CVT_V1721,							/*!< \brief The board is V1721 */
	CVT_V1731,							/*!< \brief The board is V1731 */
	CVT_V1720,							/*!< \brief The board is V1720 */
	CVT_V1740,							/*!< \brief The board is V1740 */
	CVT_V1751,							/*!< \brief The board is V1751 */
} CVT_V17XX_TYPES;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \struct  cvt_V1724_data
*   \brief   V1724 board data structure
*            
*            This structure stores any board data, common and specific ones. 
*            It must be passed to each V1724's API 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	cvt_board_data	m_common_data;				/*!< Boards common data structure: always let at offset 0 */
	//
	// Board specific data
	CVT_V17XX_TYPES m_type;						/*!< The V17XX board type (either V1724, V1721, V1731, V1720, V1740) */

	UINT32 *m_cache_sample_buffer;				/*!< Builtin samples' cache buffer */
	UINT32 m_cache_sample_buffer_size;			/*!< Builtin samples' cache buffer size ( BYTES) */
	UINT32 m_cache_sample_buffer_read_bytes;	/*!< Builtin number of samples stored ( BYTES) */
	BOOL m_is_des_mode;							/*!< Des mode setted (V1731 only) */
} cvt_V1724_data;

////////////////////////////////////////////////////////////////////////////////////////////////
// Registers address
////////////////////////////////////////////////////////////////////////////////////////////////
//
// Readout Buffer
#define CVT_V1724_OUT_BUFFER_ADD					0x0000				/*!< \brief Output buffer relative address */
//
// Channel broadcast registers
#define CVT_V1724_BROAD_CH_CTRL_ADD					0x8000				/*!< \brief Control channel broadcast register relative address (Write only)*/
#define CVT_V1724_BROAD_CH_SET_CTRL_ADD				0x8004				/*!< \brief Set control channel broadcast register relative address (Write only)*/
#define CVT_V1724_BROAD_CH_CLEAR_CTRL_ADD			0x8008				/*!< \brief Clear control channel broadcast register relative address (Write only)*/
#define CVT_V1724_BROAD_NUM_BLOCK_ADD				0x800C				/*!< \brief Number of blocks broadcast register relative address (Write only)*/
#define CVT_V1724_BROAD_CH_BUFF_FLUSH_ADD			0x8010				/*!< \brief Number of buffers to be removed channel broadcast register relative address (Write only)*/
#define CVT_V1724_BROAD_CH_RND_ACC_ADD				0x8014				/*!< \brief Read random Access channel broadcast register relative address (Write only)*/
#define CVT_V1724_BROAD_CH_CUSSIZE_ADD  			0x8020				/*!< \brief CustomSize channel broadcast register relative address (Write only)*/
#define CVT_V1724_BROAD_CH_ZSTH_ADD					0x8024				/*!< \brief Zero suppression threshold channel broadcast register relative address (Write only)*/
#define CVT_V1724_BROAD_ADC_CONF_ADD				0x809c				/*!< \brief ADC configuration broadcast register relative address (Write only)*/

//
// VME registers
#define CVT_V1724_ACQ_CONTROL_ADD					0x8100				/*!< \brief Acquisiton Control register relative address */
#define CVT_V1724_ACQ_STATUS_ADD					0x8104				/*!< \brief Acquisiton Status register relative address */
#define CVT_V1724_SW_TRIGGER_ADD					0x8108				/*!< \brief Software trigger register relative address */
#define CVT_V1724_TRIGGER_SRC_ENABLE_ADD			0x810C				/*!< \brief Trigger source enable register relative address */
#define CVT_V1724_FP_TRIGGER_OUT_ENABLE_ADD			0x8110				/*!< \brief Front panel trigger out enable mask register relative address */
#define CVT_V1724_POST_TRIG_ADD						0x8114				/*!< \brief Post trigger register relative address */
#define CVT_V1724_FRONT_PANEL_IO_ADD				0x8118				/*!< \brief Front panel IO register relative address */
#define CVT_V1724_FRONT_PANEL_IO_CTRL_ADD			0x811C				/*!< \brief Front panel IO Control register relative address */
#define CVT_V1724_CH_ENABLE_ADD						0x8120				/*!< \brief Channel enable mask register relative address */
#define CVT_V1724_FW_REV_ADD						0x8124				/*!< \brief Firmware Revision register relative address */
#define CVT_V1724_DOWNSAMPLE_FACT_ADD				0x8128				/*!< \brief DownSample factor register relative address */
#define CVT_V1724_EVENT_STORED_ADD					0x812C				/*!< \brief Event stored register relative address */
#define CVT_V1724_MON_SET_ADD						0x8138				/*!< \brief Monitor output set register relative address */
#define CVT_V1724_SW_SYNC_ADD						0x813C				/*!< \brief Sw sync register relative address */
#define CVT_V1724_BOARD_INFO_ADD					0x8140				/*!< \brief Board's information register relative address */
#define CVT_V1724_MON_MODE_ADD						0x8144				/*!< \brief Monitor output mode register relative address */
#define CVT_V1724_TEST_IO_ADD						0x8168				/*!< \brief I/O Test register relative address */

#define CVT_V1724_VME_CONTROL_ADD					0xEF00				/*!< \brief VME Control register relative address */
#define CVT_V1724_VME_STATUS_ADD					0xEF04				/*!< \brief VME Status register relative address */
#define CVT_V1724_BOARD_ID_ADD						0xEF08				/*!< \brief Geo Address register relative address */
#define CVT_V1724_MCST_CBLT_ADD_CTRL_ADD			0xEF0C				/*!< \brief MCST/CBLT Address and control register relative address */
#define CVT_V1724_RELOCATION_ADDRESS_ADD			0xEF10				/*!< \brief Relocation address register relative address */
#define CVT_V1724_INT_STATUS_ID_ADD					0xEF14				/*!< \brief Interrupt status id register relative address */
#define CVT_V1724_INT_EVENT_NUM_ADD					0xEF18				/*!< \brief Interrupt event number register relative address */
#define CVT_V1724_BLT_EVENT_NUM_ADD					0xEF1C				/*!< \brief BLT event number register relative address */
#define CVT_V1724_SCRATCH_ADD						0xEF20				/*!< \brief Scratch register relative address */
#define CVT_V1724_SW_RESET_ADD						0xEF24				/*!< \brief Software reset register relative address */
#define CVT_V1724_SW_CLEAR_ADD						0xEF28				/*!< \brief Software clear register relative address */
#define CVT_V1724_FLASH_EN_ADD						0xEF2C				/*!< \brief Flash enable relative address */
#define CVT_V1724_FLASH_DATA_ADD					0xEF30				/*!< \brief Flash data relative address */
#define CVT_V1724_RELOAD_CONFIG_ADD					0xEF34				/*!< \brief Configuration Reload relative address */
#define CVT_V1724_BASE_ADDRESS_ADD					0xEF38				/*!< \brief Base Address relative address */
#define CVT_V1724_ROM_CHKSUM_ADD					0xF000				/*!< \brief Configuration ROM checksum relative address */
#define CVT_V1724_ROM_CHKSUM_LEN_2_ADD				0xF004				/*!< \brief Configuration ROM checksum length (MSB) relative address */
#define CVT_V1724_ROM_CHKSUM_LEN_1_ADD				0xF008				/*!< \brief Configuration ROM checksum length relative address */
#define CVT_V1724_ROM_CHKSUM_LEN_0_ADD				0xF00C				/*!< \brief Configuration ROM checksum length (LSB) relative address */
#define CVT_V1724_ROM_CONST_2_ADD					0xF010				/*!< \brief Configuration ROM constant (MSB) relative address */
#define CVT_V1724_ROM_CONST_1_ADD					0xF014				/*!< \brief Configuration ROM constant relative address */
#define CVT_V1724_ROM_CONST_0_ADD					0xF018				/*!< \brief Configuration ROM constant (LSB) relative address */
#define CVT_V1724_ROM_C_CODE_ADD					0xF01C				/*!< \brief Configuration ROM c_code relative address */
#define CVT_V1724_ROM_R_CODE_ADD					0xF020				/*!< \brief Configuration ROM r_code relative address */
#define CVT_V1724_ROM_OUI_2_ADD						0xF024				/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) (MSB) relative address */
#define CVT_V1724_ROM_OUI_1_ADD						0xF028				/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) relative address */
#define CVT_V1724_ROM_OUI_0_ADD						0xF02C				/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) (LSB) relative address */
#define CVT_V1724_ROM_VERSION_ADD					0xF030				/*!< \brief Configuration ROM Purchased version of the Mod.V1724 relative address */
#define CVT_V1724_ROM_BOARD_ID_2_ADD				0xF034				/*!< \brief Configuration ROM Board identifier (MSB) relative address */
#define CVT_V1724_ROM_BOARD_ID_1_ADD				0xF038				/*!< \brief Configuration ROM Board identifier relative address */
#define CVT_V1724_ROM_BOARD_ID_0_ADD				0xF03C				/*!< \brief Configuration ROM Board identifier (LSB) relative address */
#define CVT_V1724_ROM_REVISION_3_ADD				0xF040				/*!< \brief Configuration ROM Hardware revision identifier relative address */
#define CVT_V1724_ROM_REVISION_2_ADD				0xF044				/*!< \brief Configuration ROM Hardware revision identifier relative address */
#define CVT_V1724_ROM_REVISION_1_ADD				0xF048				/*!< \brief Configuration ROM Hardware revision identifier relative address */
#define CVT_V1724_ROM_REVISION_0_ADD				0xF04C				/*!< \brief Configuration ROM Hardware revision identifier relative address */
#define CVT_V1724_ROM_SERIAL_1_ADD					0xF080				/*!< \brief Configuration ROM Serial number (MSB) relative address */
#define CVT_V1724_ROM_SERIAL_0_ADD					0xF084				/*!< \brief Configuration ROM Serial number (LSB) relative address */
#define CVT_V1724_ROM_VCXO_TYPE_ADD					0xF088				/*!< \brief Configuration ROM VCXO type relative address */

//
// CH 0
#define CVT_V1724_CH0_RESERVED_RND_ACC_ADD			0x1014				/*!< \brief CH 0 Read Block channel broadcast reserved register relative address */
#define CVT_V1724_CH0_ZSTH_ADD						0x1024				/*!< \brief CH 0 Zero suppression threshold register relative address */
#define CVT_V1724_CH0_THRESHOLD_ADD					0x1080				/*!< \brief CH 0 Threshold register relative address */
#define CVT_V1724_CH0_TIME_OVER_UNDER_THR_ADD		0x1084				/*!< \brief CH 0 Over/Under Threshold Samples register relative address */
#define CVT_V1724_CH0_STATUS_ADD					0x1088				/*!< \brief CH 0 status register relative address */
#define CVT_V1724_CH0_FW_REV_ADD					0x108C				/*!< \brief CH 0 firmware revision register relative address */
#define CVT_V1724_CH0_BUFF_OCCUPANCY_ADD			0x1094				/*!< \brief CH 0 Number of Buffers Filled register relative address */
#define CVT_V1724_CH0_DAC_CONF_ADD					0x1098				/*!< \brief CH 0 DAC Data Configuration register relative address */
#define CVT_V1724_CH0_ADC_CONF_ADD					0x109C				/*!< \brief CH 0 Configuration register relative address */
#define CVT_V1724_CH0_RESERVED_ADC_DEBUG_ADD		0x10A0				/*!< \brief CH 0 ADC Debug Reserved register relative address */
#define CVT_V1724_CH0_RESERVED_MEM_DATA_ADD			0x10A4				/*!< \brief CH 0 Memory test data Reserved register relative address */
#define CVT_V1724_CH0_RESERVED_MEM_ADDRESS_ADD		0x10A8				/*!< \brief CH 0 Memory test address Reserved register relative address */
//
// CH 1
#define CVT_V1724_CH1_RESERVED_RND_ACC_ADD			0x1114				/*!< \brief CH 1 Read Block channel broadcast reserved register relative address */
#define CVT_V1724_CH1_ZSTH_ADD						0x1124				/*!< \brief CH 1 Zero suppression threshold register relative address */
#define CVT_V1724_CH1_THRESHOLD_ADD					0x1180				/*!< \brief CH 1 Threshold register relative address */
#define CVT_V1724_CH1_TIME_OVER_UNDER_THR_ADD		0x1184				/*!< \brief CH 1 Over/Under Threshold Samples register relative address */
#define CVT_V1724_CH1_STATUS_ADD					0x1188				/*!< \brief CH 1 status register relative address */
#define CVT_V1724_CH1_FW_REV_ADD					0x118C				/*!< \brief CH 1 firmware revision register relative address */
#define CVT_V1724_CH1_BUFF_OCCUPANCY_ADD			0x1194				/*!< \brief CH 1 Number of Buffers Filled register relative address */
#define CVT_V1724_CH1_DAC_CONF_ADD					0x1198				/*!< \brief CH 1 DAC Data Configuration register relative address */
#define CVT_V1724_CH1_ADC_CONF_ADD					0x119C				/*!< \brief CH 1 Configuration register relative address */
#define CVT_V1724_CH1_RESERVED_ADC_DEBUG_ADD		0x11A0				/*!< \brief CH 1 ADC Debug Reserved register relative address */
#define CVT_V1724_CH1_RESERVED_MEM_DATA_ADD			0x11A4				/*!< \brief CH 1 Memory test data Reserved register relative address */
#define CVT_V1724_CH1_RESERVED_MEM_ADDRESS_ADD		0x11A8				/*!< \brief CH 1 Memory test address Reserved register relative address */
//
// CH 2
#define CVT_V1724_CH2_RESERVED_RND_ACC_ADD			0x1214				/*!< \brief CH 2 Read Block channel broadcast reserved register relative address */
#define CVT_V1724_CH2_ZSTH_ADD						0x1224				/*!< \brief CH 2 Zero suppression threshold register relative address */
#define CVT_V1724_CH2_THRESHOLD_ADD					0x1280				/*!< \brief CH 2 Threshold register relative address */
#define CVT_V1724_CH2_TIME_OVER_UNDER_THR_ADD		0x1284				/*!< \brief CH 2 Over/Under Threshold Samples register relative address */
#define CVT_V1724_CH2_STATUS_ADD					0x1288				/*!< \brief CH 2 status register relative address */
#define CVT_V1724_CH2_FW_REV_ADD					0x128C				/*!< \brief CH 2 firmware revision register relative address */
#define CVT_V1724_CH2_BUFF_OCCUPANCY_ADD			0x1294				/*!< \brief CH 2 Number of Buffers Filled register relative address */
#define CVT_V1724_CH2_DAC_CONF_ADD					0x1298				/*!< \brief CH 2 DAC Data Configuration register relative address */
#define CVT_V1724_CH2_ADC_CONF_ADD					0x129C				/*!< \brief CH 2 Configuration register relative address */
#define CVT_V1724_CH2_RESERVED_ADC_DEBUG_ADD		0x12A0				/*!< \brief CH 2 ADC Debug Reserved register relative address */
#define CVT_V1724_CH2_RESERVED_MEM_DATA_ADD			0x12A4				/*!< \brief CH 2 Memory test data Reserved register relative address */
#define CVT_V1724_CH2_RESERVED_MEM_ADDRESS_ADD		0x12A8				/*!< \brief CH 2 Memory test address Reserved register relative address */
//
// CH 3
#define CVT_V1724_CH3_RESERVED_RND_ACC_ADD			0x1314				/*!< \brief CH 3 Read Block channel broadcast reserved register relative address */
#define CVT_V1724_CH3_ZSTH_ADD						0x1324				/*!< \brief CH 3 Zero suppression threshold register relative address */
#define CVT_V1724_CH3_THRESHOLD_ADD					0x1380				/*!< \brief CH 3 Threshold register relative address */
#define CVT_V1724_CH3_TIME_OVER_UNDER_THR_ADD		0x1384				/*!< \brief CH 3 Over/Under Threshold Samples register relative address */
#define CVT_V1724_CH3_STATUS_ADD					0x1388				/*!< \brief CH 3 status register relative address */
#define CVT_V1724_CH3_FW_REV_ADD					0x138C				/*!< \brief CH 3 firmware revision register relative address */
#define CVT_V1724_CH3_BUFF_OCCUPANCY_ADD			0x1394				/*!< \brief CH 3 Number of Buffers Filled register relative address */
#define CVT_V1724_CH3_DAC_CONF_ADD					0x1398				/*!< \brief CH 3 DAC Data Configuration register relative address */
#define CVT_V1724_CH3_ADC_CONF_ADD					0x139C				/*!< \brief CH 3 Configuration register relative address */
#define CVT_V1724_CH3_RESERVED_ADC_DEBUG_ADD		0x13A0				/*!< \brief CH 3 ADC Debug Reserved register relative address */
#define CVT_V1724_CH3_RESERVED_MEM_DATA_ADD			0x13A4				/*!< \brief CH 3 Memory test data Reserved register relative address */
#define CVT_V1724_CH3_RESERVED_MEM_ADDRESS_ADD		0x13A8				/*!< \brief CH 3 Memory test address Reserved register relative address */
//
// CH 4
#define CVT_V1724_CH4_RESERVED_RND_ACC_ADD			0x1414				/*!< \brief CH 4 Read Block channel broadcast reserved register relative address */
#define CVT_V1724_CH4_ZSTH_ADD						0x1424				/*!< \brief CH 4 Zero suppression threshold register relative address */
#define CVT_V1724_CH4_THRESHOLD_ADD					0x1480				/*!< \brief CH 4 Threshold register relative address */
#define CVT_V1724_CH4_TIME_OVER_UNDER_THR_ADD		0x1484				/*!< \brief CH 4 Over/Under Threshold Samples register relative address */
#define CVT_V1724_CH4_STATUS_ADD					0x1488				/*!< \brief CH 4 status register relative address */
#define CVT_V1724_CH4_FW_REV_ADD					0x148C				/*!< \brief CH 4 firmware revision register relative address */
#define CVT_V1724_CH4_BUFF_OCCUPANCY_ADD			0x1494				/*!< \brief CH 4 Number of Buffers Filled register relative address */
#define CVT_V1724_CH4_DAC_CONF_ADD					0x1498				/*!< \brief CH 4 DAC Data Configuration register relative address */
#define CVT_V1724_CH4_ADC_CONF_ADD					0x149C				/*!< \brief CH 4 Configuration register relative address */
#define CVT_V1724_CH4_RESERVED_ADC_DEBUG_ADD		0x14A0				/*!< \brief CH 4 ADC Debug Reserved register relative address */
#define CVT_V1724_CH4_RESERVED_MEM_DATA_ADD			0x14A4				/*!< \brief CH 4 Memory test data Reserved register relative address */
#define CVT_V1724_CH4_RESERVED_MEM_ADDRESS_ADD		0x14A8				/*!< \brief CH 4 Memory test address Reserved register relative address */
//
// CH 5
#define CVT_V1724_CH5_RESERVED_RND_ACC_ADD			0x1514				/*!< \brief CH 5 Read Block channel broadcast reserved register relative address */
#define CVT_V1724_CH5_ZSTH_ADD						0x1524				/*!< \brief CH 5 Zero suppression threshold register relative address */
#define CVT_V1724_CH5_THRESHOLD_ADD					0x1580				/*!< \brief CH 5 Threshold register relative address */
#define CVT_V1724_CH5_TIME_OVER_UNDER_THR_ADD		0x1584				/*!< \brief CH 5 Over/Under Threshold Samples register relative address */
#define CVT_V1724_CH5_STATUS_ADD					0x1588				/*!< \brief CH 5 status register relative address */
#define CVT_V1724_CH5_FW_REV_ADD					0x158C				/*!< \brief CH 5 firmware revision register relative address */
#define CVT_V1724_CH5_BUFF_OCCUPANCY_ADD			0x1594				/*!< \brief CH 5 Number of Buffers Filled register relative address */
#define CVT_V1724_CH5_DAC_CONF_ADD					0x1598				/*!< \brief CH 5 DAC Data Configuration register relative address */
#define CVT_V1724_CH5_ADC_CONF_ADD					0x159C				/*!< \brief CH 5 Configuration register relative address */
#define CVT_V1724_CH5_RESERVED_ADC_DEBUG_ADD		0x15A0				/*!< \brief CH 5 ADC Debug Reserved register relative address */
#define CVT_V1724_CH5_RESERVED_MEM_DATA_ADD			0x15A4				/*!< \brief CH 5 Memory test data Reserved register relative address */
#define CVT_V1724_CH5_RESERVED_MEM_ADDRESS_ADD		0x15A8				/*!< \brief CH 5 Memory test address Reserved register relative address */
//
// CH 6
#define CVT_V1724_CH6_RESERVED_RND_ACC_ADD			0x1614				/*!< \brief CH 6 Read Block channel broadcast reserved register relative address */
#define CVT_V1724_CH6_ZSTH_ADD						0x1624				/*!< \brief CH 6 Zero suppression threshold register relative address */
#define CVT_V1724_CH6_THRESHOLD_ADD					0x1680				/*!< \brief CH 6 Threshold register relative address */
#define CVT_V1724_CH6_TIME_OVER_UNDER_THR_ADD		0x1684				/*!< \brief CH 6 Over/Under Threshold Samples register relative address */
#define CVT_V1724_CH6_STATUS_ADD					0x1688				/*!< \brief CH 6 status register relative address */
#define CVT_V1724_CH6_FW_REV_ADD					0x168C				/*!< \brief CH 6 firmware revision register relative address */
#define CVT_V1724_CH6_BUFF_OCCUPANCY_ADD			0x1694				/*!< \brief CH 6 Number of Buffers Filled register relative address */
#define CVT_V1724_CH6_DAC_CONF_ADD					0x1698				/*!< \brief CH 6 DAC Data Configuration register relative address */
#define CVT_V1724_CH6_ADC_CONF_ADD					0x169C				/*!< \brief CH 6 Configuration register relative address */
#define CVT_V1724_CH6_RESERVED_ADC_DEBUG_ADD		0x16A0				/*!< \brief CH 6 ADC Debug Reserved register relative address */
#define CVT_V1724_CH6_RESERVED_MEM_DATA_ADD			0x16A4				/*!< \brief CH 6 Memory test data Reserved register relative address */
#define CVT_V1724_CH6_RESERVED_MEM_ADDRESS_ADD		0x16A8				/*!< \brief CH 6 Memory test address Reserved register relative address */
//
// CH 7
#define CVT_V1724_CH7_RESERVED_RND_ACC_ADD			0x1714				/*!< \brief CH 7 Read Block channel broadcast reserved register relative address */
#define CVT_V1724_CH7_ZSTH_ADD						0x1724				/*!< \brief CH 7 Zero suppression threshold register relative address */
#define CVT_V1724_CH7_THRESHOLD_ADD					0x1780				/*!< \brief CH 7 Threshold register relative address */
#define CVT_V1724_CH7_TIME_OVER_UNDER_THR_ADD		0x1784				/*!< \brief CH 7 Over/Under Threshold Samples register relative address */
#define CVT_V1724_CH7_STATUS_ADD					0x1788				/*!< \brief CH 7 status register relative address */
#define CVT_V1724_CH7_FW_REV_ADD					0x178C				/*!< \brief CH 7 firmware revision register relative address */
#define CVT_V1724_CH7_BUFF_OCCUPANCY_ADD			0x1794				/*!< \brief CH 7 Number of Buffers Filled register relative address */
#define CVT_V1724_CH7_DAC_CONF_ADD					0x1798				/*!< \brief CH 7 DAC Data Configuration register relative address */
#define CVT_V1724_CH7_ADC_CONF_ADD					0x179C				/*!< \brief CH 7 Configuration register relative address */
#define CVT_V1724_CH7_RESERVED_ADC_DEBUG_ADD		0x17A0				/*!< \brief CH 7 ADC Debug Reserved register relative address */
#define CVT_V1724_CH7_RESERVED_MEM_DATA_ADD			0x17A4				/*!< \brief CH 7 Memory test data Reserved register relative address */
#define CVT_V1724_CH7_RESERVED_MEM_ADDRESS_ADD		0x17A8				/*!< \brief CH 7 Memory test address Reserved register relative address */

////////////////////////////////////////////////////////////////////////////////////////////////
// Registers data size
////////////////////////////////////////////////////////////////////////////////////////////////
//
// Readout Buffer
#define CVT_V1724_OUT_BUFFER_DATA_SIZE				cvD64				/*!< \brief Output buffer data buffer */

//
// Channel broadcast registers
#define CVT_V1724_BROAD_CH_CTRL_DATA_SIZE			cvD32				/*!< \brief Control channel broadcast register data size (Write only)*/
#define CVT_V1724_BROAD_CH_SET_CTRL_DATA_SIZE		cvD32				/*!< \brief Set control channel broadcast register data size (Write only)*/
#define CVT_V1724_BROAD_CH_CLEAR_CTRL_DATA_SIZE		cvD32				/*!< \brief Clear control channel broadcast register data size (Write only)*/
#define CVT_V1724_BROAD_NUM_BLOCK_DATA_SIZE			cvD32				/*!< \brief Number of blocks broadcast register data size(Write only)*/
#define CVT_V1724_BROAD_CH_BUFF_FLUSH_DATA_SIZE		cvD32				/*!< \brief Number of buffers to be removed channel broadcast register data size(Write only)*/
#define CVT_V1724_BROAD_CH_RND_ACC_DATA_SIZE		cvD32				/*!< \brief Parameters to Random access  channel broadcast register data size (Write only)*/
#define CVT_V1724_BROAD_CH_CUSSIZE_DATA_SIZE		cvD32				/*!< \brief Custom Size channel broadcast register data size (Write only)*/
#define CVT_V1724_BROAD_CH_ZSTH_DATA_SIZE			cvD32				/*!< \brief Zero suppression threshold channel broadcast register data size (Write only)*/
#define CVT_V1724_BROAD_ADC_CONF_DATA_SIZE			cvD32				/*!< \brief ADC configuration broadcast register data size (Write only)*/
//
// VME registers
#define CVT_V1724_ACQ_CONTROL_DATA_SIZE				cvD32				/*!< \brief Acquisiton Control register data size */
#define CVT_V1724_ACQ_STATUS_DATA_SIZE				cvD32				/*!< \brief Acquisiton Status register data size */
#define CVT_V1724_SW_TRIGGER_DATA_SIZE				cvD32				/*!< \brief Software trigger register data size */
#define CVT_V1724_TRIGGER_SRC_ENABLE_DATA_SIZE		cvD32				/*!< \brief Trigger source enable register data size */
#define CVT_V1724_FP_TRIGGER_OUT_ENABLE_DATA_SIZE	cvD32				/*!< \brief Front panel trigger out enable mask register data size */
#define CVT_V1724_POST_TRIG_DATA_SIZE				cvD32				/*!< \brief Post trigger register data size */
#define CVT_V1724_FRONT_PANEL_IO_DATA_SIZE			cvD32				/*!< \brief Front panel IO register data size */
#define CVT_V1724_FRONT_PANEL_IO_CTRL_DATA_SIZE		cvD32				/*!< \brief Front panel IO Control register data size */
#define CVT_V1724_CH_ENABLE_DATA_SIZE				cvD32				/*!< \brief Channel enable mask register data size */
#define CVT_V1724_FW_REV_DATA_SIZE					cvD32				/*!< \brief Firmware Revision register data size */
#define CVT_V1724_DOWNSAMPLE_FACT_DATA_SIZE			cvD32				/*!< \brief DownSample factor register data size */
#define CVT_V1724_EVENT_STORED_DATA_SIZE			cvD32				/*!< \brief Event stored register data size */
#define CVT_V1724_MON_SET_DATA_SIZE					cvD32				/*!< \brief Monitor output set register data size */
#define CVT_V1724_SW_SYNC_DATA_SIZE					cvD32				/*!< \brief Sw sync register data size */
#define CVT_V1724_BOARD_INFO_DATA_SIZE				cvD32				/*!< \brief Board's information register data size */
#define CVT_V1724_MON_MODE_DATA_SIZE				cvD32				/*!< \brief Monitor output mode register data size */
#define CVT_V1724_TEST_IO_DATA_SIZE				    cvD32				/*!< \brief I/O Test register data size */

#define CVT_V1724_VME_CONTROL_DATA_SIZE				cvD32				/*!< \brief VME Control register data size */
#define CVT_V1724_VME_STATUS_DATA_SIZE				cvD32				/*!< \brief VME Status register data size */
#define CVT_V1724_BOARD_ID_DATA_SIZE				cvD32				/*!< \brief Geo Address register data size */
#define CVT_V1724_MCST_CBLT_ADD_CTRL_DATA_SIZE		cvD32				/*!< \brief MCST/CBLT Address and control register data size */
#define CVT_V1724_RELOCATION_ADDRESS_DATA_SIZE		cvD32				/*!< \brief Relocation address register data size */
#define CVT_V1724_INT_STATUS_ID_DATA_SIZE			cvD32				/*!< \brief Interrupt status id register data size */
#define CVT_V1724_INT_EVENT_NUM_DATA_SIZE			cvD32				/*!< \brief Interrupt event number register data size */
#define CVT_V1724_BLT_EVENT_NUM_DATA_SIZE			cvD32				/*!< \brief BLT event number register data size */
#define CVT_V1724_SCRATCH_DATA_SIZE					cvD32				/*!< \brief Scratch register data size */
#define CVT_V1724_SW_RESET_DATA_SIZE				cvD32				/*!< \brief Software reset register data size */
#define CVT_V1724_SW_CLEAR_DATA_SIZE				cvD32				/*!< \brief Software clear register data size */
#define CVT_V1724_FLASH_EN_DATA_SIZE				cvD32				/*!< \brief Flash enable data size */
#define CVT_V1724_FLASH_DATA_DATA_SIZE				cvD32				/*!< \brief Flash data data size */
#define CVT_V1724_RELOAD_CONFIG_DATA_SIZE			cvD32				/*!< \brief Configuration Reload data size */
#define CVT_V1724_BASE_ADDRESS_DATA_SIZE			cvD32				/*!< \brief Base Address data size */
#define CVT_V1724_ROM_CHKSUM_DATA_SIZE				cvD32				/*!< \brief Configuration ROM checksum data size */
#define CVT_V1724_ROM_CHKSUM_LEN_2_DATA_SIZE		cvD32				/*!< \brief Configuration ROM checksum length (MSB) data size */
#define CVT_V1724_ROM_CHKSUM_LEN_1_DATA_SIZE		cvD32				/*!< \brief Configuration ROM checksum length data size */
#define CVT_V1724_ROM_CHKSUM_LEN_0_DATA_SIZE		cvD32				/*!< \brief Configuration ROM checksum length (LSB) data size */
#define CVT_V1724_ROM_CONST_2_DATA_SIZE				cvD32				/*!< \brief Configuration ROM constant (MSB) data size */
#define CVT_V1724_ROM_CONST_1_DATA_SIZE				cvD32				/*!< \brief Configuration ROM constant data size */
#define CVT_V1724_ROM_CONST_0_DATA_SIZE				cvD32				/*!< \brief Configuration ROM constant (LSB) data size */
#define CVT_V1724_ROM_C_CODE_DATA_SIZE				cvD32				/*!< \brief Configuration ROM c_code data size */
#define CVT_V1724_ROM_R_CODE_DATA_SIZE				cvD32				/*!< \brief Configuration ROM r_code data size */
#define CVT_V1724_ROM_OUI_2_DATA_SIZE				cvD32				/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) (MSB) data size */
#define CVT_V1724_ROM_OUI_1_DATA_SIZE				cvD32				/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) data size */
#define CVT_V1724_ROM_OUI_0_DATA_SIZE				cvD32				/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) (LSB) data size */
#define CVT_V1724_ROM_VERSION_DATA_SIZE				cvD32				/*!< \brief Configuration ROM Purchased version of the Mod.V1724 data size */
#define CVT_V1724_ROM_BOARD_ID_2_DATA_SIZE			cvD32				/*!< \brief Configuration ROM Board identifier (MSB) data size */
#define CVT_V1724_ROM_BOARD_ID_1_DATA_SIZE			cvD32				/*!< \brief Configuration ROM Board identifier data size */
#define CVT_V1724_ROM_BOARD_ID_0_DATA_SIZE			cvD32				/*!< \brief Configuration ROM Board identifier (LSB) data size */
#define CVT_V1724_ROM_REVISION_3_DATA_SIZE			cvD32				/*!< \brief Configuration ROM Hardware revision identifier data size */
#define CVT_V1724_ROM_REVISION_2_DATA_SIZE			cvD32				/*!< \brief Configuration ROM Hardware revision identifier data size */
#define CVT_V1724_ROM_REVISION_1_DATA_SIZE			cvD32				/*!< \brief Configuration ROM Hardware revision identifier data size */
#define CVT_V1724_ROM_REVISION_0_DATA_SIZE			cvD32				/*!< \brief Configuration ROM Hardware revision identifier data size */
#define CVT_V1724_ROM_SERIAL_1_DATA_SIZE			cvD32				/*!< \brief Configuration ROM Serial number (MSB) data size */
#define CVT_V1724_ROM_SERIAL_0_DATA_SIZE			cvD32				/*!< \brief Configuration ROM Serial number (LSB) data size */
#define CVT_V1724_ROM_VCXO_TYPE_DATA_SIZE			cvD32				/*!< \brief Configuration ROM VCXO type data size */

//
// CH 0
#define CVT_V1724_CH0_RESERVED_RND_ACC_DATA_SIZE		cvD32				/*!< \brief CH 0 Read Block channel broadcast reserved register data size */
#define CVT_V1724_CH0_ZSTH_DATA_SIZE					cvD32				/*!< \brief Ch 0 Zero suppression threshold register data size)*/
#define CVT_V1724_CH0_THRESHOLD_DATA_SIZE				cvD32				/*!< \brief CH 0 Threshold register data size */
#define CVT_V1724_CH0_TIME_OVER_UNDER_THR_DATA_SIZE		cvD32				/*!< \brief CH 0 Over/Under Threshold Samples register data size */
#define CVT_V1724_CH0_STATUS_DATA_SIZE					cvD32				/*!< \brief CH 0 status register data size */
#define CVT_V1724_CH0_FW_REV_DATA_SIZE					cvD32				/*!< \brief CH 0 firmware revision register data size */
#define CVT_V1724_CH0_BUFF_OCCUPANCY_DATA_SIZE			cvD32				/*!< \brief CH 0 Number of Buffers Filled register data size */
#define CVT_V1724_CH0_DAC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 0 DAC Data Configuration register data size */
#define CVT_V1724_CH0_ADC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 0 Configuration register data size */
#define CVT_V1724_CH0_RESERVED_ADC_DEBUG_DATA_SIZE		cvD32				/*!< \brief CH 0 ADC Debug Reserved register data size */
#define CVT_V1724_CH0_RESERVED_MEM_DATA_DATA_SIZE		cvD32				/*!< \brief CH 0 Memory test data Reserved register data size */
#define CVT_V1724_CH0_RESERVED_MEM_ADDRESS_DATA_SIZE	cvD32				/*!< \brief CH 0 Memory test address Reserved register data size */

//
// CH 1
#define CVT_V1724_CH1_RESERVED_RND_ACC_DATA_SIZE		cvD32				/*!< \brief CH 1 Read Block channel broadcast reserved register data size */
#define CVT_V1724_CH1_ZSTH_DATA_SIZE					cvD32				/*!< \brief Ch 1 Zero suppression threshold register data size)*/
#define CVT_V1724_CH1_THRESHOLD_DATA_SIZE				cvD32				/*!< \brief CH 1 Threshold register data size */
#define CVT_V1724_CH1_TIME_OVER_UNDER_THR_DATA_SIZE		cvD32				/*!< \brief CH 1 Over/Under Threshold Samples register data size */
#define CVT_V1724_CH1_STATUS_DATA_SIZE					cvD32				/*!< \brief CH 1 status register data size */
#define CVT_V1724_CH1_FW_REV_DATA_SIZE					cvD32				/*!< \brief CH 1 firmware revision register data size */
#define CVT_V1724_CH1_BUFF_OCCUPANCY_DATA_SIZE			cvD32				/*!< \brief CH 1 Number of Buffers Filled register data size */
#define CVT_V1724_CH1_DAC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 1 DAC Data Configuration register data size */
#define CVT_V1724_CH1_ADC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 1 Configuration register data size */
#define CVT_V1724_CH1_RESERVED_ADC_DEBUG_DATA_SIZE		cvD32				/*!< \brief CH 1 ADC Debug Reserved register data size */
#define CVT_V1724_CH1_RESERVED_MEM_DATA_DATA_SIZE		cvD32				/*!< \brief CH 1 Memory test data Reserved register data size */
#define CVT_V1724_CH1_RESERVED_MEM_ADDRESS_DATA_SIZE	cvD32				/*!< \brief CH 1 Memory test address Reserved register data size */

//
// CH 2
#define CVT_V1724_CH2_RESERVED_RND_ACC_DATA_SIZE		cvD32				/*!< \brief CH 2 Read Block channel broadcast reserved register data size */
#define CVT_V1724_CH2_ZSTH_DATA_SIZE					cvD32				/*!< \brief Ch 2 Zero suppression threshold register data size)*/
#define CVT_V1724_CH2_THRESHOLD_DATA_SIZE				cvD32				/*!< \brief CH 2 Threshold register data size */
#define CVT_V1724_CH2_TIME_OVER_UNDER_THR_DATA_SIZE		cvD32				/*!< \brief CH 2 Over/Under Threshold Samples register data size */
#define CVT_V1724_CH2_STATUS_DATA_SIZE					cvD32				/*!< \brief CH 2 status register data size */
#define CVT_V1724_CH2_FW_REV_DATA_SIZE					cvD32				/*!< \brief CH 2 firmware revision register data size */
#define CVT_V1724_CH2_BUFF_OCCUPANCY_DATA_SIZE			cvD32				/*!< \brief CH 2 Number of Buffers Filled register data size */
#define CVT_V1724_CH2_DAC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 2 DAC Data Configuration register data size */
#define CVT_V1724_CH2_ADC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 2 Configuration register data size */
#define CVT_V1724_CH2_RESERVED_ADC_DEBUG_DATA_SIZE		cvD32				/*!< \brief CH 2 ADC Debug Reserved register data size */
#define CVT_V1724_CH2_RESERVED_MEM_DATA_DATA_SIZE		cvD32				/*!< \brief CH 2 Memory test data Reserved register data size */
#define CVT_V1724_CH2_RESERVED_MEM_ADDRESS_DATA_SIZE	cvD32				/*!< \brief CH 2 Memory test address Reserved register data size */

//
// CH 3
#define CVT_V1724_CH3_RESERVED_RND_ACC_DATA_SIZE		cvD32				/*!< \brief CH 3 Read Block channel broadcast reserved register data size */
#define CVT_V1724_CH3_ZSTH_DATA_SIZE					cvD32				/*!< \brief Ch 3 Zero suppression threshold register data size)*/
#define CVT_V1724_CH3_THRESHOLD_DATA_SIZE				cvD32				/*!< \brief CH 3 Threshold register data size */
#define CVT_V1724_CH3_TIME_OVER_UNDER_THR_DATA_SIZE		cvD32				/*!< \brief CH 3 Over/Under Threshold Samples register data size */
#define CVT_V1724_CH3_STATUS_DATA_SIZE					cvD32				/*!< \brief CH 3 status register data size */
#define CVT_V1724_CH3_FW_REV_DATA_SIZE					cvD32				/*!< \brief CH 3 firmware revision register data size */
#define CVT_V1724_CH3_BUFF_OCCUPANCY_DATA_SIZE			cvD32				/*!< \brief CH 3 Number of Buffers Filled register data size */
#define CVT_V1724_CH3_DAC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 3 DAC Data Configuration register data size */
#define CVT_V1724_CH3_ADC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 3 Configuration register data size */
#define CVT_V1724_CH3_RESERVED_ADC_DEBUG_DATA_SIZE		cvD32				/*!< \brief CH 3 ADC Debug Reserved register data size */
#define CVT_V1724_CH3_RESERVED_MEM_DATA_DATA_SIZE		cvD32				/*!< \brief CH 3 Memory test data Reserved register data size */
#define CVT_V1724_CH3_RESERVED_MEM_ADDRESS_DATA_SIZE	cvD32				/*!< \brief CH 3 Memory test address Reserved register data size */

//
// CH 4
#define CVT_V1724_CH4_RESERVED_RND_ACC_DATA_SIZE		cvD32				/*!< \brief CH 4 Read Block channel broadcast reserved register data size */
#define CVT_V1724_CH4_ZSTH_DATA_SIZE					cvD32				/*!< \brief Ch 4 Zero suppression threshold register data size)*/
#define CVT_V1724_CH4_THRESHOLD_DATA_SIZE				cvD32				/*!< \brief CH 4 Threshold register data size */
#define CVT_V1724_CH4_TIME_OVER_UNDER_THR_DATA_SIZE		cvD32				/*!< \brief CH 4 Over/Under Threshold Samples register data size */
#define CVT_V1724_CH4_STATUS_DATA_SIZE					cvD32				/*!< \brief CH 4 status register data size */
#define CVT_V1724_CH4_FW_REV_DATA_SIZE					cvD32				/*!< \brief CH 4 firmware revision register data size */
#define CVT_V1724_CH4_BUFF_OCCUPANCY_DATA_SIZE			cvD32				/*!< \brief CH 4 Number of Buffers Filled register data size */
#define CVT_V1724_CH4_DAC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 4 DAC Data Configuration register data size */
#define CVT_V1724_CH4_ADC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 4 Configuration register data size */
#define CVT_V1724_CH4_RESERVED_ADC_DEBUG_DATA_SIZE		cvD32				/*!< \brief CH 4 ADC Debug Reserved register data size */
#define CVT_V1724_CH4_RESERVED_MEM_DATA_DATA_SIZE		cvD32				/*!< \brief CH 4 Memory test data Reserved register data size */
#define CVT_V1724_CH4_RESERVED_MEM_ADDRESS_DATA_SIZE	cvD32				/*!< \brief CH 4 Memory test address Reserved register data size */

//
// CH 5
#define CVT_V1724_CH5_RESERVED_RND_ACC_DATA_SIZE		cvD32				/*!< \brief CH 5 Read Block channel broadcast reserved register data size */
#define CVT_V1724_CH5_ZSTH_DATA_SIZE					cvD32				/*!< \brief Ch 5 Zero suppression threshold register data size)*/
#define CVT_V1724_CH5_THRESHOLD_DATA_SIZE				cvD32				/*!< \brief CH 5 Threshold register data size */
#define CVT_V1724_CH5_TIME_OVER_UNDER_THR_DATA_SIZE		cvD32				/*!< \brief CH 5 Over/Under Threshold Samples register data size */
#define CVT_V1724_CH5_STATUS_DATA_SIZE					cvD32				/*!< \brief CH 5 status register data size */
#define CVT_V1724_CH5_FW_REV_DATA_SIZE					cvD32				/*!< \brief CH 5 firmware revision register data size */
#define CVT_V1724_CH5_BUFF_OCCUPANCY_DATA_SIZE			cvD32				/*!< \brief CH 5 Number of Buffers Filled register data size */
#define CVT_V1724_CH5_DAC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 5 DAC Data Configuration register data size */
#define CVT_V1724_CH5_ADC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 5 Configuration register data size */
#define CVT_V1724_CH5_RESERVED_ADC_DEBUG_DATA_SIZE		cvD32				/*!< \brief CH 5 ADC Debug Reserved register data size */
#define CVT_V1724_CH5_RESERVED_MEM_DATA_DATA_SIZE		cvD32				/*!< \brief CH 5 Memory test data Reserved register data size */
#define CVT_V1724_CH5_RESERVED_MEM_ADDRESS_DATA_SIZE	cvD32				/*!< \brief CH 5 Memory test address Reserved register data size */

//
// CH 6
#define CVT_V1724_CH6_RESERVED_RND_ACC_DATA_SIZE		cvD32				/*!< \brief CH 6 Read Block channel broadcast reserved register data size */
#define CVT_V1724_CH6_ZSTH_DATA_SIZE					cvD32				/*!< \brief Ch 6 Zero suppression threshold register data size)*/
#define CVT_V1724_CH6_THRESHOLD_DATA_SIZE				cvD32				/*!< \brief CH 6 Threshold register data size */
#define CVT_V1724_CH6_TIME_OVER_UNDER_THR_DATA_SIZE		cvD32				/*!< \brief CH 6 Over/Under Threshold Samples register data size */
#define CVT_V1724_CH6_STATUS_DATA_SIZE					cvD32				/*!< \brief CH 6 status register data size */
#define CVT_V1724_CH6_FW_REV_DATA_SIZE					cvD32				/*!< \brief CH 6 firmware revision register data size */
#define CVT_V1724_CH6_BUFF_OCCUPANCY_DATA_SIZE			cvD32				/*!< \brief CH 6 Number of Buffers Filled register data size */
#define CVT_V1724_CH6_DAC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 6 DAC Data Configuration register data size */
#define CVT_V1724_CH6_ADC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 6 Configuration register data size */
#define CVT_V1724_CH6_RESERVED_ADC_DEBUG_DATA_SIZE		cvD32				/*!< \brief CH 6 ADC Debug Reserved register data size */
#define CVT_V1724_CH6_RESERVED_MEM_DATA_DATA_SIZE		cvD32				/*!< \brief CH 6 Memory test data Reserved register data size */
#define CVT_V1724_CH6_RESERVED_MEM_ADDRESS_DATA_SIZE	cvD32				/*!< \brief CH 6 Memory test address Reserved register data size */

//
// CH 7
#define CVT_V1724_CH7_RESERVED_RND_ACC_DATA_SIZE		cvD32				/*!< \brief CH 7 Read Block channel broadcast reserved register data size */
#define CVT_V1724_CH7_ZSTH_DATA_SIZE					cvD32				/*!< \brief Ch 7 Zero suppression threshold register data size)*/
#define CVT_V1724_CH7_THRESHOLD_DATA_SIZE				cvD32				/*!< \brief CH 7 Threshold register data size */
#define CVT_V1724_CH7_TIME_OVER_UNDER_THR_DATA_SIZE		cvD32				/*!< \brief CH 7 Over/Under Threshold Samples register data size */
#define CVT_V1724_CH7_STATUS_DATA_SIZE					cvD32				/*!< \brief CH 7 status register data size */
#define CVT_V1724_CH7_FW_REV_DATA_SIZE					cvD32				/*!< \brief CH 7 firmware revision register data size */
#define CVT_V1724_CH7_BUFF_OCCUPANCY_DATA_SIZE			cvD32				/*!< \brief CH 7 Number of Buffers Filled register data size */
#define CVT_V1724_CH7_DAC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 7 DAC Data Configuration register data size */
#define CVT_V1724_CH7_ADC_CONF_DATA_SIZE				cvD32				/*!< \brief CH 7 Configuration register data size */
#define CVT_V1724_CH7_RESERVED_ADC_DEBUG_DATA_SIZE		cvD32				/*!< \brief CH 7 ADC Debug Reserved register data size */
#define CVT_V1724_CH7_RESERVED_MEM_DATA_DATA_SIZE		cvD32				/*!< \brief CH 7 Memory test data Reserved register data size */
#define CVT_V1724_CH7_RESERVED_MEM_ADDRESS_DATA_SIZE	cvD32				/*!< \brief CH 7 Memory test address Reserved register data size */



////////////////////////////////////////////////////////////////////////////////////////////////
// Registers address modifiers
////////////////////////////////////////////////////////////////////////////////////////////////
//
// Readout Buffer
#define CVT_V1724_OUT_BUFFER_AM						cvA32_S_MBLT				/*!< \brief Output buffer data buffer address modifier */


//
// Channel broadcast registers
#define CVT_V1724_BROAD_CH_CTRL_AM					cvA32_S_DATA				/*!< \brief Control channel broadcast register address modifier (Write only)*/
#define CVT_V1724_BROAD_CH_SET_CTRL_AM				cvA32_S_DATA				/*!< \brief Set control channel broadcast register address modifier (Write only)*/
#define CVT_V1724_BROAD_CH_CLEAR_CTRL_AM			cvA32_S_DATA				/*!< \brief Clear control channel broadcast register address modifier (Write only)*/
#define CVT_V1724_BROAD_NUM_BLOCK_AM				cvA32_S_DATA				/*!< \brief Number of blocks broadcast register address modifiere(Write only)*/
#define CVT_V1724_BROAD_CH_BUFF_FLUSH_AM			cvA32_S_DATA				/*!< \brief Number of buffers to be removed channel broadcast register address modifiere(Write only)*/
#define CVT_V1724_BROAD_CH_RND_ACC_AM				cvA32_S_DATA				/*!< \brief Parameters to Random access  channel broadcast register address modifier (Write only)*/
#define CVT_V1724_BROAD_CH_CUSSIZE_AM				cvA32_S_DATA				/*!< \brief Custom Size register channel broadcast address modifier (Write only)*/
#define CVT_V1724_BROAD_CH_ZSTH_AM					cvA32_S_DATA				/*!< \brief Zero suppression threshold register channel broadcast address modifier (Write only)*/
#define CVT_V1724_BROAD_ADC_CONF_AM					cvA32_S_DATA				/*!< \brief ADC configuration broadcast register address modifier (Write only)*/

//
// VME registers
#define CVT_V1724_ACQ_CONTROL_AM					cvA32_S_DATA				/*!< \brief Acquisiton Control register address modifier */
#define CVT_V1724_ACQ_STATUS_AM						cvA32_S_DATA				/*!< \brief Acquisiton Status register address modifier */
#define CVT_V1724_SW_TRIGGER_AM						cvA32_S_DATA				/*!< \brief Software trigger register address modifier */
#define CVT_V1724_TRIGGER_SRC_ENABLE_AM				cvA32_S_DATA				/*!< \brief Trigger source enable register address modifier */
#define CVT_V1724_FP_TRIGGER_OUT_ENABLE_AM			cvA32_S_DATA				/*!< \brief Front panel trigger out enable mask register address modifier */
#define CVT_V1724_POST_TRIG_AM						cvA32_S_DATA				/*!< \brief Post trigger register address modifier */
#define CVT_V1724_FRONT_PANEL_IO_AM					cvA32_S_DATA				/*!< \brief Front panel IO register address modifier */
#define CVT_V1724_FRONT_PANEL_IO_CTRL_AM			cvA32_S_DATA				/*!< \brief Front panel IO Control register address modifier */
#define CVT_V1724_CH_ENABLE_AM						cvA32_S_DATA				/*!< \brief Channel enable mask register address modifier */
#define CVT_V1724_FW_REV_AM							cvA32_S_DATA				/*!< \brief Firmware Revision register address modifier */
#define CVT_V1724_DOWNSAMPLE_FACT_AM				cvA32_S_DATA				/*!< \brief DownSample factor register address modifier */
#define CVT_V1724_EVENT_STORED_AM					cvA32_S_DATA				/*!< \brief Event stored register address modifier */
#define CVT_V1724_MON_SET_AM						cvA32_S_DATA				/*!< \brief Monitor output set register address modifier */
#define CVT_V1724_SW_SYNC_AM						cvA32_S_DATA				/*!< \brief Sw sync register address modifier */
#define CVT_V1724_BOARD_INFO_AM						cvA32_S_DATA				/*!< \brief Board's information register address modifier */
#define CVT_V1724_MON_MODE_AM						cvA32_S_DATA				/*!< \brief Monitor output mode register address modifier */
#define CVT_V1724_TEST_IO_AM						cvA32_S_DATA				/*!< \brief I/O Test register address modifier */

#define CVT_V1724_VME_CONTROL_AM					cvA32_S_DATA				/*!< \brief VME Control register address modifier */
#define CVT_V1724_VME_STATUS_AM						cvA32_S_DATA				/*!< \brief VME Status register address modifier */
#define CVT_V1724_BOARD_ID_AM						cvA32_S_DATA				/*!< \brief Geo Address register address modifier */
#define CVT_V1724_MCST_CBLT_ADD_CTRL_AM				cvA32_S_DATA				/*!< \brief MCST/CBLT Address and control register address modifier */
#define CVT_V1724_RELOCATION_ADDRESS_AM				cvA32_S_DATA				/*!< \brief Relocation address register address modifier */
#define CVT_V1724_INT_STATUS_ID_AM					cvA32_S_DATA				/*!< \brief Interrupt status id register address modifier */
#define CVT_V1724_INT_EVENT_NUM_AM					cvA32_S_DATA				/*!< \brief Interrupt event number register address modifier */
#define CVT_V1724_BLT_EVENT_NUM_AM					cvA32_S_DATA				/*!< \brief BLT event number register address modifier */
#define CVT_V1724_SCRATCH_AM						cvA32_S_DATA				/*!< \brief Scratch register address modifier */
#define CVT_V1724_SW_RESET_AM						cvA32_S_DATA				/*!< \brief Software reset register address modifier */
#define CVT_V1724_SW_CLEAR_AM						cvA32_S_DATA				/*!< \brief Software clear register address modifier */
#define CVT_V1724_FLASH_EN_AM						cvA32_S_DATA				/*!< \brief Flash enable address modifier */
#define CVT_V1724_FLASH_DATA_AM						cvA32_S_DATA				/*!< \brief Flash data address modifier */
#define CVT_V1724_RELOAD_CONFIG_AM					cvA32_S_DATA				/*!< \brief Configuration Reload address modifier */
#define CVT_V1724_BASE_ADDRESS_AM					cvA32_S_DATA				/*!< \brief Base Address address modifier */
#define CVT_V1724_ROM_CHKSUM_AM						cvA32_S_DATA				/*!< \brief Configuration ROM checksum address modifier */
#define CVT_V1724_ROM_CHKSUM_LEN_2_AM				cvA32_S_DATA				/*!< \brief Configuration ROM checksum length (MSB) address modifier */
#define CVT_V1724_ROM_CHKSUM_LEN_1_AM				cvA32_S_DATA				/*!< \brief Configuration ROM checksum length address modifier */
#define CVT_V1724_ROM_CHKSUM_LEN_0_AM				cvA32_S_DATA				/*!< \brief Configuration ROM checksum length (LSB) address modifier */
#define CVT_V1724_ROM_CONST_2_AM					cvA32_S_DATA				/*!< \brief Configuration ROM constant (MSB) address modifier */
#define CVT_V1724_ROM_CONST_1_AM					cvA32_S_DATA				/*!< \brief Configuration ROM constant address modifier */
#define CVT_V1724_ROM_CONST_0_AM					cvA32_S_DATA				/*!< \brief Configuration ROM constant (LSB) address modifier */
#define CVT_V1724_ROM_C_CODE_AM						cvA32_S_DATA				/*!< \brief Configuration ROM c_code address modifier */
#define CVT_V1724_ROM_R_CODE_AM						cvA32_S_DATA				/*!< \brief Configuration ROM r_code address modifier */
#define CVT_V1724_ROM_OUI_2_AM						cvA32_S_DATA				/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) (MSB) address modifier */
#define CVT_V1724_ROM_OUI_1_AM						cvA32_S_DATA				/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) address modifier */
#define CVT_V1724_ROM_OUI_0_AM						cvA32_S_DATA				/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) (LSB) address modifier */
#define CVT_V1724_ROM_VERSION_AM					cvA32_S_DATA				/*!< \brief Configuration ROM Purchased version of the Mod.V1724 address modifier */
#define CVT_V1724_ROM_BOARD_ID_2_AM					cvA32_S_DATA				/*!< \brief Configuration ROM Board identifier (MSB) address modifier */
#define CVT_V1724_ROM_BOARD_ID_1_AM					cvA32_S_DATA				/*!< \brief Configuration ROM Board identifier address modifier */
#define CVT_V1724_ROM_BOARD_ID_0_AM					cvA32_S_DATA				/*!< \brief Configuration ROM Board identifier (LSB) address modifier */
#define CVT_V1724_ROM_REVISION_3_AM					cvA32_S_DATA				/*!< \brief Configuration ROM Hardware revision identifier address modifier */
#define CVT_V1724_ROM_REVISION_2_AM					cvA32_S_DATA				/*!< \brief Configuration ROM Hardware revision identifier address modifier */
#define CVT_V1724_ROM_REVISION_1_AM					cvA32_S_DATA				/*!< \brief Configuration ROM Hardware revision identifier address modifier */
#define CVT_V1724_ROM_REVISION_0_AM					cvA32_S_DATA				/*!< \brief Configuration ROM Hardware revision identifier address modifier */
#define CVT_V1724_ROM_SERIAL_1_AM					cvA32_S_DATA				/*!< \brief Configuration ROM Serial number (MSB) address modifier */
#define CVT_V1724_ROM_SERIAL_0_AM					cvA32_S_DATA				/*!< \brief Configuration ROM Serial number (LSB) address modifier */
#define CVT_V1724_ROM_VCXO_TYPE_AM					cvA32_S_DATA				/*!< \brief Configuration ROM VCXO type address modifier */

//
// CH 0
#define CVT_V1724_CH0_RESERVED_RND_ACC_AM			cvA32_S_DATA				/*!< \brief CH 0 Read Block channel broadcast reserved register address modifier */
#define CVT_V1724_CH0_ZSTH_AM						cvA32_S_DATA				/*!< \brief CH 0 Zero suppression threshold register address modifier */
#define CVT_V1724_CH0_THRESHOLD_AM					cvA32_S_DATA				/*!< \brief CH 0 Threshold register address modifier */
#define CVT_V1724_CH0_TIME_OVER_UNDER_THR_AM		cvA32_S_DATA				/*!< \brief CH 0 Over/Under Threshold Samples register address modifier */
#define CVT_V1724_CH0_STATUS_AM						cvA32_S_DATA				/*!< \brief CH 0 status register address modifier */
#define CVT_V1724_CH0_FW_REV_AM						cvA32_S_DATA				/*!< \brief CH 0 firmware revision register address modifier */
#define CVT_V1724_CH0_BUFF_OCCUPANCY_AM				cvA32_S_DATA				/*!< \brief CH 0 Number of Buffers Filled register address modifier */
#define CVT_V1724_CH0_DAC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 0 DAC Data Configuration register address modifier */
#define CVT_V1724_CH0_ADC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 0 Configuration register address modifier */
#define CVT_V1724_CH0_RESERVED_ADC_DEBUG_AM			cvA32_S_DATA				/*!< \brief CH 0 ADC Debug Reserved register address modifier */
#define CVT_V1724_CH0_RESERVED_MEM_DATA_AM			cvA32_S_DATA				/*!< \brief CH 0 Memory test data Reserved register address modifier */
#define CVT_V1724_CH0_RESERVED_MEM_ADDRESS_AM		cvA32_S_DATA				/*!< \brief CH 0 Memory test address Reserved register address modifier */

//
// CH 1
#define CVT_V1724_CH1_RESERVED_RND_ACC_AM			cvA32_S_DATA				/*!< \brief CH 1 Read Block channel broadcast reserved register address modifier */
#define CVT_V1724_CH1_ZSTH_AM						cvA32_S_DATA				/*!< \brief CH 1 Zero suppression threshold register address modifier */
#define CVT_V1724_CH1_THRESHOLD_AM					cvA32_S_DATA				/*!< \brief CH 1 Threshold register address modifier */
#define CVT_V1724_CH1_TIME_OVER_UNDER_THR_AM		cvA32_S_DATA				/*!< \brief CH 1 Over/Under Threshold Samples register address modifier */
#define CVT_V1724_CH1_STATUS_AM						cvA32_S_DATA				/*!< \brief CH 1 status register address modifier */
#define CVT_V1724_CH1_FW_REV_AM						cvA32_S_DATA				/*!< \brief CH 1 firmware revision register address modifier */
#define CVT_V1724_CH1_BUFF_OCCUPANCY_AM				cvA32_S_DATA				/*!< \brief CH 1 Number of Buffers Filled register address modifier */
#define CVT_V1724_CH1_DAC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 1 DAC Data Configuration register address modifier */
#define CVT_V1724_CH1_ADC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 1 Configuration register address modifier */
#define CVT_V1724_CH1_RESERVED_ADC_DEBUG_AM			cvA32_S_DATA				/*!< \brief CH 1 ADC Debug Reserved register address modifier */
#define CVT_V1724_CH1_RESERVED_MEM_DATA_AM			cvA32_S_DATA				/*!< \brief CH 1 Memory test data Reserved register address modifier */
#define CVT_V1724_CH1_RESERVED_MEM_ADDRESS_AM		cvA32_S_DATA				/*!< \brief CH 1 Memory test address Reserved register address modifier */

//
// CH 2
#define CVT_V1724_CH2_RESERVED_RND_ACC_AM			cvA32_S_DATA				/*!< \brief CH 2 Read Block channel broadcast reserved register address modifier */
#define CVT_V1724_CH2_ZSTH_AM						cvA32_S_DATA				/*!< \brief CH 2 Zero suppression threshold register address modifier */
#define CVT_V1724_CH2_THRESHOLD_AM					cvA32_S_DATA				/*!< \brief CH 2 Threshold register address modifier */
#define CVT_V1724_CH2_TIME_OVER_UNDER_THR_AM		cvA32_S_DATA				/*!< \brief CH 2 Over/Under Threshold Samples register address modifier */
#define CVT_V1724_CH2_STATUS_AM						cvA32_S_DATA				/*!< \brief CH 2 status register address modifier */
#define CVT_V1724_CH2_FW_REV_AM						cvA32_S_DATA				/*!< \brief CH 2 firmware revision register address modifier */
#define CVT_V1724_CH2_BUFF_OCCUPANCY_AM				cvA32_S_DATA				/*!< \brief CH 2 Number of Buffers Filled register address modifier */
#define CVT_V1724_CH2_DAC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 2 DAC Data Configuration register address modifier */
#define CVT_V1724_CH2_ADC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 2 Configuration register address modifier */
#define CVT_V1724_CH2_RESERVED_ADC_DEBUG_AM			cvA32_S_DATA				/*!< \brief CH 2 ADC Debug Reserved register address modifier */
#define CVT_V1724_CH2_RESERVED_MEM_DATA_AM			cvA32_S_DATA				/*!< \brief CH 2 Memory test data Reserved register address modifier */
#define CVT_V1724_CH2_RESERVED_MEM_ADDRESS_AM		cvA32_S_DATA				/*!< \brief CH 2 Memory test address Reserved register address modifier */

//
// CH 3
#define CVT_V1724_CH3_RESERVED_RND_ACC_AM			cvA32_S_DATA				/*!< \brief CH 3 Read Block channel broadcast reserved register address modifier */
#define CVT_V1724_CH3_ZSTH_AM						cvA32_S_DATA				/*!< \brief CH 3 Zero suppression threshold register address modifier */
#define CVT_V1724_CH3_THRESHOLD_AM					cvA32_S_DATA				/*!< \brief CH 3 Threshold register address modifier */
#define CVT_V1724_CH3_TIME_OVER_UNDER_THR_AM		cvA32_S_DATA				/*!< \brief CH 3 Over/Under Threshold Samples register address modifier */
#define CVT_V1724_CH3_STATUS_AM						cvA32_S_DATA				/*!< \brief CH 3 status register address modifier */
#define CVT_V1724_CH3_FW_REV_AM						cvA32_S_DATA				/*!< \brief CH 3 firmware revision register address modifier */
#define CVT_V1724_CH3_BUFF_OCCUPANCY_AM				cvA32_S_DATA				/*!< \brief CH 3 Number of Buffers Filled register address modifier */
#define CVT_V1724_CH3_DAC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 3 DAC Data Configuration register address modifier */
#define CVT_V1724_CH3_ADC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 3 Configuration register address modifier */
#define CVT_V1724_CH3_RESERVED_ADC_DEBUG_AM			cvA32_S_DATA				/*!< \brief CH 3 ADC Debug Reserved register address modifier */
#define CVT_V1724_CH3_RESERVED_MEM_DATA_AM			cvA32_S_DATA				/*!< \brief CH 3 Memory test data Reserved register address modifier */
#define CVT_V1724_CH3_RESERVED_MEM_ADDRESS_AM		cvA32_S_DATA				/*!< \brief CH 3 Memory test address Reserved register address modifier */

//
// CH 4
#define CVT_V1724_CH4_RESERVED_RND_ACC_AM			cvA32_S_DATA				/*!< \brief CH 4 Read Block channel broadcast reserved register address modifier */
#define CVT_V1724_CH4_ZSTH_AM						cvA32_S_DATA				/*!< \brief CH 4 Zero suppression threshold register address modifier */
#define CVT_V1724_CH4_THRESHOLD_AM					cvA32_S_DATA				/*!< \brief CH 4 Threshold register address modifier */
#define CVT_V1724_CH4_TIME_OVER_UNDER_THR_AM		cvA32_S_DATA				/*!< \brief CH 4 Over/Under Threshold Samples register address modifier */
#define CVT_V1724_CH4_STATUS_AM						cvA32_S_DATA				/*!< \brief CH 4 status register address modifier */
#define CVT_V1724_CH4_FW_REV_AM						cvA32_S_DATA				/*!< \brief CH 4 firmware revision register address modifier */
#define CVT_V1724_CH4_BUFF_OCCUPANCY_AM				cvA32_S_DATA				/*!< \brief CH 4 Number of Buffers Filled register address modifier */
#define CVT_V1724_CH4_DAC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 4 DAC Data Configuration register address modifier */
#define CVT_V1724_CH4_ADC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 4 Configuration register address modifier */
#define CVT_V1724_CH4_RESERVED_ADC_DEBUG_AM			cvA32_S_DATA				/*!< \brief CH 4 ADC Debug Reserved register address modifier */
#define CVT_V1724_CH4_RESERVED_MEM_DATA_AM			cvA32_S_DATA				/*!< \brief CH 4 Memory test data Reserved register address modifier */
#define CVT_V1724_CH4_RESERVED_MEM_ADDRESS_AM		cvA32_S_DATA				/*!< \brief CH 4 Memory test address Reserved register address modifier */

//
// CH 5
#define CVT_V1724_CH5_RESERVED_RND_ACC_AM			cvA32_S_DATA				/*!< \brief CH 5 Read Block channel broadcast reserved register address modifier */
#define CVT_V1724_CH5_ZSTH_AM						cvA32_S_DATA				/*!< \brief CH 5 Zero suppression threshold register address modifier */
#define CVT_V1724_CH5_THRESHOLD_AM					cvA32_S_DATA				/*!< \brief CH 5 Threshold register address modifier */
#define CVT_V1724_CH5_TIME_OVER_UNDER_THR_AM		cvA32_S_DATA				/*!< \brief CH 5 Over/Under Threshold Samples register address modifier */
#define CVT_V1724_CH5_STATUS_AM						cvA32_S_DATA				/*!< \brief CH 5 status register address modifier */
#define CVT_V1724_CH5_FW_REV_AM						cvA32_S_DATA				/*!< \brief CH 5 firmware revision register address modifier */
#define CVT_V1724_CH5_BUFF_OCCUPANCY_AM				cvA32_S_DATA				/*!< \brief CH 5 Number of Buffers Filled register address modifier */
#define CVT_V1724_CH5_DAC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 5 DAC Data Configuration register address modifier */
#define CVT_V1724_CH5_ADC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 5 Configuration register address modifier */
#define CVT_V1724_CH5_RESERVED_ADC_DEBUG_AM			cvA32_S_DATA				/*!< \brief CH 5 ADC Debug Reserved register address modifier */
#define CVT_V1724_CH5_RESERVED_MEM_DATA_AM			cvA32_S_DATA				/*!< \brief CH 5 Memory test data Reserved register address modifier */
#define CVT_V1724_CH5_RESERVED_MEM_ADDRESS_AM		cvA32_S_DATA				/*!< \brief CH 5 Memory test address Reserved register address modifier */

//
// CH 6
#define CVT_V1724_CH6_RESERVED_RND_ACC_AM			cvA32_S_DATA				/*!< \brief CH 6 Read Block channel broadcast reserved register address modifier */
#define CVT_V1724_CH6_ZSTH_AM						cvA32_S_DATA				/*!< \brief CH 6 Zero suppression threshold register address modifier */
#define CVT_V1724_CH6_THRESHOLD_AM					cvA32_S_DATA				/*!< \brief CH 6 Threshold register address modifier */
#define CVT_V1724_CH6_TIME_OVER_UNDER_THR_AM		cvA32_S_DATA				/*!< \brief CH 6 Over/Under Threshold Samples register address modifier */
#define CVT_V1724_CH6_STATUS_AM						cvA32_S_DATA				/*!< \brief CH 6 status register address modifier */
#define CVT_V1724_CH6_FW_REV_AM						cvA32_S_DATA				/*!< \brief CH 6 firmware revision register address modifier */
#define CVT_V1724_CH6_BUFF_OCCUPANCY_AM				cvA32_S_DATA				/*!< \brief CH 6 Number of Buffers Filled register address modifier */
#define CVT_V1724_CH6_DAC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 6 DAC Data Configuration register address modifier */
#define CVT_V1724_CH6_ADC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 6 Configuration register address modifier */
#define CVT_V1724_CH6_RESERVED_ADC_DEBUG_AM			cvA32_S_DATA				/*!< \brief CH 6 ADC Debug Reserved register address modifier */
#define CVT_V1724_CH6_RESERVED_MEM_DATA_AM			cvA32_S_DATA				/*!< \brief CH 6 Memory test data Reserved register address modifier */
#define CVT_V1724_CH6_RESERVED_MEM_ADDRESS_AM		cvA32_S_DATA				/*!< \brief CH 6 Memory test address Reserved register address modifier */

//
// CH 7
#define CVT_V1724_CH7_RESERVED_RND_ACC_AM			cvA32_S_DATA				/*!< \brief CH 7 Read Block channel broadcast reserved register address modifier */
#define CVT_V1724_CH7_ZSTH_AM						cvA32_S_DATA				/*!< \brief CH 7 Zero suppression threshold register address modifier */
#define CVT_V1724_CH7_THRESHOLD_AM					cvA32_S_DATA				/*!< \brief CH 7 Threshold register address modifier */
#define CVT_V1724_CH7_TIME_OVER_UNDER_THR_AM		cvA32_S_DATA				/*!< \brief CH 7 Over/Under Threshold Samples register address modifier */
#define CVT_V1724_CH7_STATUS_AM						cvA32_S_DATA				/*!< \brief CH 7 status register address modifier */
#define CVT_V1724_CH7_FW_REV_AM						cvA32_S_DATA				/*!< \brief CH 7 firmware revision register address modifier */
#define CVT_V1724_CH7_BUFF_OCCUPANCY_AM				cvA32_S_DATA				/*!< \brief CH 7 Number of Buffers Filled register address modifier */
#define CVT_V1724_CH7_DAC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 7 DAC Data Configuration register address modifier */
#define CVT_V1724_CH7_ADC_CONF_AM					cvA32_S_DATA				/*!< \brief CH 7 Configuration register address modifier */
#define CVT_V1724_CH7_RESERVED_ADC_DEBUG_AM			cvA32_S_DATA				/*!< \brief CH 7 ADC Debug Reserved register address modifier */
#define CVT_V1724_CH7_RESERVED_MEM_DATA_AM			cvA32_S_DATA				/*!< \brief CH 7 Memory test data Reserved register address modifier */
#define CVT_V1724_CH7_RESERVED_MEM_ADDRESS_AM		cvA32_S_DATA				/*!< \brief CH 7 Memory test address Reserved register address modifier */


////////////////////////////////////////////////////////////////////////////////////////////////
// Registers indexes
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_REG_INDEX
*   \brief   The registers indexes
*            
*            Provides an entry for each register: This is the index into the CVT_V1724_REG_TABLE board table
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
//
// Readout Buffer
	CVT_V1724_OUT_BUFFER_INDEX,						/*!< \brief Output buffer data buffer index */

//
// Channel broadcast registers
	CVT_V1724_BROAD_CH_CTRL_INDEX,					/*!< \brief Control channel broadcast register index */
	CVT_V1724_BROAD_CH_SET_CTRL_INDEX,				/*!< \brief Set control channel broadcast register index */
	CVT_V1724_BROAD_CH_CLEAR_CTRL_INDEX,			/*!< \brief Clear control channel broadcast register index */
	CVT_V1724_BROAD_NUM_BLOCK_INDEX,				/*!< \brief Number of blocks broadcast register index */
	CVT_V1724_BROAD_CH_BUFF_FLUSH_INDEX,			/*!< \brief Number of buffers to be removed channel broadcast register index */
	CVT_V1724_BROAD_CH_RND_ACC_INDEX,				/*!< \brief Parameters to Random access  channel broadcast register index */
	CVT_V1724_BROAD_CH_CUSSIZE_INDEX,				/*!< \brief Custom Size threshold channel broadcast register index*/
	CVT_V1724_BROAD_CH_ZSTH_INDEX,					/*!< \brief Zero suppression threshold channel broadcast register index*/
	CVT_V1724_BROAD_ADC_CONF_INDEX,					/*!< \brief ADC configuration broadcast register register index (Write only)*/
//
// VME registers
	CVT_V1724_ACQ_CONTROL_INDEX,					/*!< \brief Acquisiton Control register index */
	CVT_V1724_ACQ_STATUS_INDEX,						/*!< \brief Acquisiton Status register index */
	CVT_V1724_SW_TRIGGER_INDEX,						/*!< \brief Software trigger register index */
	CVT_V1724_TRIGGER_SRC_ENABLE_INDEX,				/*!< \brief Trigger source enable register index */
	CVT_V1724_FP_TRIGGER_OUT_ENABLE_INDEX,			/*!< \brief Front panel trigger out enable mask register index */
	CVT_V1724_POST_TRIG_INDEX,						/*!< \brief Post trigger register index */
	CVT_V1724_FRONT_PANEL_IO_INDEX,					/*!< \brief Front panel IO register index */
	CVT_V1724_FRONT_PANEL_IO_CTRL_INDEX,			/*!< \brief Front panel IO Control register index */
	CVT_V1724_CH_ENABLE_INDEX,						/*!< \brief Channel enable mask register index */
	CVT_V1724_FW_REV_INDEX,							/*!< \brief Firmware Revision register index */
	CVT_V1724_DOWNSAMPLE_FACT_INDEX,				/*!< \brief DownSample factor register index */
	CVT_V1724_EVENT_STORED_INDEX,					/*!< \brief Event stored register index */
	CVT_V1724_MON_SET_INDEX,						/*!< \brief Monitor output set register index*/
	CVT_V1724_SW_SYNC_INDEX,						/*!< \brief Sw sync register index */
	CVT_V1724_BOARD_INFO_INDEX,						/*!< \brief Board's information register index */
	CVT_V1724_MON_MODE_INDEX,						/*!< \brief Monitor output mode register index*/
	CVT_V1724_TEST_IO_INDEX,					    /*!< \brief Test Register for IO verification index */

	CVT_V1724_VME_CONTROL_INDEX,					/*!< \brief VME Control register index */
	CVT_V1724_VME_STATUS_INDEX,						/*!< \brief VME Status register index */
	CVT_V1724_BOARD_ID_INDEX,						/*!< \brief Geo Address register index */
	CVT_V1724_MCST_CBLT_ADD_CTRL_INDEX,				/*!< \brief MCST/CBLT Address and control register index */
	CVT_V1724_RELOCATION_ADDRESS_INDEX,				/*!< \brief Relocation address register index */
	CVT_V1724_INT_STATUS_ID_INDEX,					/*!< \brief Interrupt status id register index */
	CVT_V1724_INT_EVENT_NUM_INDEX,					/*!< \brief Interrupt event number register index */
	CVT_V1724_BLT_EVENT_NUM_INDEX,					/*!< \brief BLT event number register index */
	CVT_V1724_SCRATCH_INDEX,						/*!< \brief Scratch register index */
	CVT_V1724_SW_RESET_INDEX,						/*!< \brief Software reset register index */
	CVT_V1724_SW_CLEAR_INDEX,						/*!< \brief Software clear register index */
	CVT_V1724_FLASH_EN_INDEX,						/*!< \brief Flash enable index */
	CVT_V1724_FLASH_DATA_INDEX,						/*!< \brief Flash data index */
	CVT_V1724_RELOAD_CONFIG_INDEX,					/*!< \brief Configuration Reload index */
	CVT_V1724_BASE_ADDRESS_INDEX,					/*!< \brief Base Address index */
	CVT_V1724_ROM_CHKSUM_INDEX,						/*!< \brief Configuration ROM checksum index */
	CVT_V1724_ROM_CHKSUM_LEN_2_INDEX,				/*!< \brief Configuration ROM checksum length (MSB) index */
	CVT_V1724_ROM_CHKSUM_LEN_1_INDEX,				/*!< \brief Configuration ROM checksum length index */
	CVT_V1724_ROM_CHKSUM_LEN_0_INDEX,				/*!< \brief Configuration ROM checksum length (LSB) index */
	CVT_V1724_ROM_CONST_2_INDEX,					/*!< \brief Configuration ROM constant (MSB) index */
	CVT_V1724_ROM_CONST_1_INDEX,					/*!< \brief Configuration ROM constant index */
	CVT_V1724_ROM_CONST_0_INDEX,					/*!< \brief Configuration ROM constant (LSB) index */
	CVT_V1724_ROM_C_CODE_INDEX,						/*!< \brief Configuration ROM c_code index */
	CVT_V1724_ROM_R_CODE_INDEX,						/*!< \brief Configuration ROM r_code index */
	CVT_V1724_ROM_OUI_2_INDEX,						/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) (MSB) index */
	CVT_V1724_ROM_OUI_1_INDEX,						/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) index */
	CVT_V1724_ROM_OUI_0_INDEX,						/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) (LSB) index */
	CVT_V1724_ROM_VERSION_INDEX,					/*!< \brief Configuration ROM Purchased version of the Mod.V1724 index */
	CVT_V1724_ROM_BOARD_ID_2_INDEX,					/*!< \brief Configuration ROM Board identifier (MSB) index */
	CVT_V1724_ROM_BOARD_ID_1_INDEX,					/*!< \brief Configuration ROM Board identifier index */
	CVT_V1724_ROM_BOARD_ID_0_INDEX,					/*!< \brief Configuration ROM Board identifier (LSB) index */
	CVT_V1724_ROM_REVISION_3_INDEX,					/*!< \brief Configuration ROM Hardware revision identifier index */
	CVT_V1724_ROM_REVISION_2_INDEX,					/*!< \brief Configuration ROM Hardware revision identifier index */
	CVT_V1724_ROM_REVISION_1_INDEX,					/*!< \brief Configuration ROM Hardware revision identifier index */
	CVT_V1724_ROM_REVISION_0_INDEX,					/*!< \brief Configuration ROM Hardware revision identifier index */
	CVT_V1724_ROM_SERIAL_1_INDEX,					/*!< \brief Configuration ROM Serial number (MSB) index */
	CVT_V1724_ROM_SERIAL_0_INDEX,					/*!< \brief Configuration ROM Serial number (LSB) index */
	CVT_V1724_ROM_VCXO_TYPE_INDEX,					/*!< \brief Configuration ROM VCXO type index */

//
// CH 0
	CVT_V1724_CH0_RESERVED_RND_ACC_INDEX,			/*!< \brief CH 0 Read Block channel broadcast reserved register index */
	CVT_V1724_CH0_ZSTH_INDEX,						/*!< \brief CH 0 Zero suppression threshold channel broadcast register index*/
	CVT_V1724_CH0_THRESHOLD_INDEX,					/*!< \brief CH 0 Threshold register index */
	CVT_V1724_CH0_TIME_OVER_UNDER_THR_INDEX,		/*!< \brief CH 0 Over/Under Threshold Samples register index */
	CVT_V1724_CH0_STATUS_INDEX,						/*!< \brief CH 0 status register index */
	CVT_V1724_CH0_FW_REV_INDEX,						/*!< \brief CH 0 firmware revision register index */
	CVT_V1724_CH0_BUFF_OCCUPANCY_INDEX,				/*!< \brief CH 0 Number of Buffers Filled register index */
	CVT_V1724_CH0_DAC_CONF_INDEX,					/*!< \brief CH 0 DAC Data Configuration register index */
	CVT_V1724_CH0_ADC_CONF_INDEX,					/*!< \brief CH 0 Configuration register index */
	CVT_V1724_CH0_RESERVED_ADC_DEBUG_INDEX,			/*!< \brief CH 0 ADC Debug Reserved register index */
	CVT_V1724_CH0_RESERVED_MEM_DATA_INDEX,			/*!< \brief CH 0 Memory test data Reserved register index */
	CVT_V1724_CH0_RESERVED_MEM_ADDRESS_INDEX,		/*!< \brief CH 0 Memory test address Reserved register index */

//
// CH 1
	CVT_V1724_CH1_RESERVED_RND_ACC_INDEX,			/*!< \brief CH 1 Read Block channel broadcast reserved register index */
	CVT_V1724_CH1_ZSTH_INDEX,						/*!< \brief CH 1 Zero suppression threshold channel broadcast register index*/
	CVT_V1724_CH1_THRESHOLD_INDEX,					/*!< \brief CH 1 Threshold register index */
	CVT_V1724_CH1_TIME_OVER_UNDER_THR_INDEX,		/*!< \brief CH 1 Over/Under Threshold Samples register index */
	CVT_V1724_CH1_STATUS_INDEX,						/*!< \brief CH 1 status register index */
	CVT_V1724_CH1_FW_REV_INDEX,						/*!< \brief CH 1 firmware revision register index */
	CVT_V1724_CH1_BUFF_OCCUPANCY_INDEX,				/*!< \brief CH 1 Number of Buffers Filled register index */
	CVT_V1724_CH1_DAC_CONF_INDEX,					/*!< \brief CH 1 DAC Data Configuration register index */
	CVT_V1724_CH1_ADC_CONF_INDEX,					/*!< \brief CH 1 Configuration register index */
	CVT_V1724_CH1_RESERVED_ADC_DEBUG_INDEX,			/*!< \brief CH 1 ADC Debug Reserved register index */
	CVT_V1724_CH1_RESERVED_MEM_DATA_INDEX,			/*!< \brief CH 1 Memory test data Reserved register index */
	CVT_V1724_CH1_RESERVED_MEM_ADDRESS_INDEX,		/*!< \brief CH 1 Memory test address Reserved register index */

//
// CH 2
	CVT_V1724_CH2_RESERVED_RND_ACC_INDEX,			/*!< \brief CH 2 Read Block channel broadcast reserved register index */
	CVT_V1724_CH2_ZSTH_INDEX,						/*!< \brief CH 2 Zero suppression threshold channel broadcast register index*/
	CVT_V1724_CH2_THRESHOLD_INDEX,					/*!< \brief CH 2 Threshold register index */
	CVT_V1724_CH2_TIME_OVER_UNDER_THR_INDEX,		/*!< \brief CH 2 Over/Under Threshold Samples register index */
	CVT_V1724_CH2_STATUS_INDEX,						/*!< \brief CH 2 status register index */
	CVT_V1724_CH2_FW_REV_INDEX,						/*!< \brief CH 2 firmware revision register index */
	CVT_V1724_CH2_BUFF_OCCUPANCY_INDEX,				/*!< \brief CH 2 Number of Buffers Filled register index */
	CVT_V1724_CH2_DAC_CONF_INDEX,					/*!< \brief CH 2 DAC Data Configuration register index */
	CVT_V1724_CH2_ADC_CONF_INDEX,					/*!< \brief CH 2 Configuration register index */
	CVT_V1724_CH2_RESERVED_ADC_DEBUG_INDEX,			/*!< \brief CH 2 ADC Debug Reserved register index */
	CVT_V1724_CH2_RESERVED_MEM_DATA_INDEX,			/*!< \brief CH 2 Memory test data Reserved register index */
	CVT_V1724_CH2_RESERVED_MEM_ADDRESS_INDEX,		/*!< \brief CH 2 Memory test address Reserved register index */

//
// CH 3
	CVT_V1724_CH3_RESERVED_RND_ACC_INDEX,			/*!< \brief CH 3 Read Block channel broadcast reserved register index */
	CVT_V1724_CH3_ZSTH_INDEX,						/*!< \brief CH 3 Zero suppression threshold channel broadcast register index*/
	CVT_V1724_CH3_THRESHOLD_INDEX,					/*!< \brief CH 3 Threshold register index */
	CVT_V1724_CH3_TIME_OVER_UNDER_THR_INDEX,		/*!< \brief CH 3 Over/Under Threshold Samples register index */
	CVT_V1724_CH3_STATUS_INDEX,						/*!< \brief CH 3 status register index */
	CVT_V1724_CH3_FW_REV_INDEX,						/*!< \brief CH 3 firmware revision register index */
	CVT_V1724_CH3_BUFF_OCCUPANCY_INDEX,				/*!< \brief CH 3 Number of Buffers Filled register index */
	CVT_V1724_CH3_DAC_CONF_INDEX,					/*!< \brief CH 3 DAC Data Configuration register index */
	CVT_V1724_CH3_ADC_CONF_INDEX,					/*!< \brief CH 3 Configuration register index */
	CVT_V1724_CH3_RESERVED_ADC_DEBUG_INDEX,			/*!< \brief CH 3 ADC Debug Reserved register index */
	CVT_V1724_CH3_RESERVED_MEM_DATA_INDEX,			/*!< \brief CH 3 Memory test data Reserved register index */
	CVT_V1724_CH3_RESERVED_MEM_ADDRESS_INDEX,		/*!< \brief CH 3 Memory test address Reserved register index */

//
// CH 4
	CVT_V1724_CH4_RESERVED_RND_ACC_INDEX,			/*!< \brief CH 4 Read Block channel broadcast reserved register index */
	CVT_V1724_CH4_ZSTH_INDEX,						/*!< \brief CH 4 Zero suppression threshold channel broadcast register index*/
	CVT_V1724_CH4_THRESHOLD_INDEX,					/*!< \brief CH 4 Threshold register index */
	CVT_V1724_CH4_TIME_OVER_UNDER_THR_INDEX,		/*!< \brief CH 4 Over/Under Threshold Samples register index */
	CVT_V1724_CH4_STATUS_INDEX,						/*!< \brief CH 4 status register index */
	CVT_V1724_CH4_FW_REV_INDEX,						/*!< \brief CH 4 firmware revision register index */
	CVT_V1724_CH4_BUFF_OCCUPANCY_INDEX,				/*!< \brief CH 4 Number of Buffers Filled register index */
	CVT_V1724_CH4_DAC_CONF_INDEX,					/*!< \brief CH 4 DAC Data Configuration register index */
	CVT_V1724_CH4_ADC_CONF_INDEX,					/*!< \brief CH 4 Configuration register index */
	CVT_V1724_CH4_RESERVED_ADC_DEBUG_INDEX,			/*!< \brief CH 4 ADC Debug Reserved register index */
	CVT_V1724_CH4_RESERVED_MEM_DATA_INDEX,			/*!< \brief CH 4 Memory test data Reserved register index */
	CVT_V1724_CH4_RESERVED_MEM_ADDRESS_INDEX,		/*!< \brief CH 4 Memory test address Reserved register index */

//
// CH 5
	CVT_V1724_CH5_RESERVED_RND_ACC_INDEX,			/*!< \brief CH 5 Read Block channel broadcast reserved register index */
	CVT_V1724_CH5_ZSTH_INDEX,						/*!< \brief CH 5 Zero suppression threshold channel broadcast register index*/
	CVT_V1724_CH5_THRESHOLD_INDEX,					/*!< \brief CH 5 Threshold register index */
	CVT_V1724_CH5_TIME_OVER_UNDER_THR_INDEX,		/*!< \brief CH 5 Over/Under Threshold Samples register index */
	CVT_V1724_CH5_STATUS_INDEX,						/*!< \brief CH 5 status register index */
	CVT_V1724_CH5_FW_REV_INDEX,						/*!< \brief CH 5 firmware revision register index */
	CVT_V1724_CH5_BUFF_OCCUPANCY_INDEX,				/*!< \brief CH 5 Number of Buffers Filled register index */
	CVT_V1724_CH5_DAC_CONF_INDEX,					/*!< \brief CH 5 DAC Data Configuration register index */
	CVT_V1724_CH5_ADC_CONF_INDEX,					/*!< \brief CH 5 Configuration register index */
	CVT_V1724_CH5_RESERVED_ADC_DEBUG_INDEX,			/*!< \brief CH 5 ADC Debug Reserved register index */
	CVT_V1724_CH5_RESERVED_MEM_DATA_INDEX,			/*!< \brief CH 5 Memory test data Reserved register index */
	CVT_V1724_CH5_RESERVED_MEM_ADDRESS_INDEX,		/*!< \brief CH 5 Memory test address Reserved register index */

//
// CH 6
	CVT_V1724_CH6_RESERVED_RND_ACC_INDEX,			/*!< \brief CH 6 Read Block channel broadcast reserved register index */
	CVT_V1724_CH6_ZSTH_INDEX,						/*!< \brief CH 6 Zero suppression threshold channel broadcast register index*/
	CVT_V1724_CH6_THRESHOLD_INDEX,					/*!< \brief CH 6 Threshold register index */
	CVT_V1724_CH6_TIME_OVER_UNDER_THR_INDEX,		/*!< \brief CH 6 Over/Under Threshold Samples register index */
	CVT_V1724_CH6_STATUS_INDEX,						/*!< \brief CH 6 status register index */
	CVT_V1724_CH6_FW_REV_INDEX,						/*!< \brief CH 6 firmware revision register index */
	CVT_V1724_CH6_BUFF_OCCUPANCY_INDEX,				/*!< \brief CH 6 Number of Buffers Filled register index */
	CVT_V1724_CH6_DAC_CONF_INDEX,					/*!< \brief CH 6 DAC Data Configuration register index */
	CVT_V1724_CH6_ADC_CONF_INDEX,					/*!< \brief CH 6 Configuration register index */
	CVT_V1724_CH6_RESERVED_ADC_DEBUG_INDEX,			/*!< \brief CH 6 ADC Debug Reserved register index */
	CVT_V1724_CH6_RESERVED_MEM_DATA_INDEX,			/*!< \brief CH 6 Memory test data Reserved register index */
	CVT_V1724_CH6_RESERVED_MEM_ADDRESS_INDEX,		/*!< \brief CH 6 Memory test address Reserved register index */

//
// CH 7
	CVT_V1724_CH7_RESERVED_RND_ACC_INDEX,			/*!< \brief CH 7 Read Block channel broadcast reserved register index */
	CVT_V1724_CH7_ZSTH_INDEX,						/*!< \brief CH 7 Zero suppression threshold channel broadcast register index*/
	CVT_V1724_CH7_THRESHOLD_INDEX,					/*!< \brief CH 7 Threshold register index */
	CVT_V1724_CH7_TIME_OVER_UNDER_THR_INDEX,		/*!< \brief CH 7 Over/Under Threshold Samples register index */
	CVT_V1724_CH7_STATUS_INDEX,						/*!< \brief CH 7 status register index */
	CVT_V1724_CH7_FW_REV_INDEX,						/*!< \brief CH 7 firmware revision register index */
	CVT_V1724_CH7_BUFF_OCCUPANCY_INDEX,				/*!< \brief CH 7 Number of Buffers Filled register index */
	CVT_V1724_CH7_DAC_CONF_INDEX,					/*!< \brief CH 7 DAC Data Configuration register index */
	CVT_V1724_CH7_ADC_CONF_INDEX,					/*!< \brief CH 7 Configuration register index */
	CVT_V1724_CH7_RESERVED_ADC_DEBUG_INDEX,			/*!< \brief CH 7 ADC Debug Reserved register index */
	CVT_V1724_CH7_RESERVED_MEM_DATA_INDEX,			/*!< \brief CH 7 Memory test data Reserved register index */
	CVT_V1724_CH7_RESERVED_MEM_ADDRESS_INDEX,		/*!< \brief CH 7 Memory test address Reserved register index */

//
//
	CVT_V1724_LAST_INDEX,							/*!< \brief Tag : just to get table index size */

} CVT_V1724_REG_INDEX;
												
#define CVT_V1724_MAX_CHANNEL			8			/*!< \brief The number of channels */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_VME_CONTROL_MSK
*   \brief   Control register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_VME_CTRL_INT_LEVEL_MSK		= 0x0007,		/*!< Interrupt level bit masks */
	CVT_V1724_VME_CTRL_BERR_ENABLE_MSK		= 0x0010,		/*!< Bus error enable bit */
	CVT_V1724_VME_CTRL_ALIGN64_MSK			= 0x0020,		/*!< Align 64 enable bit */
	CVT_V1724_VME_CTRL_RELOC_MSK			= 0x0040,		/*!< Reloc bit */
} CVT_V1724_VME_CONTROL_MSK;

#define CVT_V1724_GET_INT_LEVEL( reg)			(((UINT32)reg)& CVT_V1724_VME_CTRL_INT_LEVEL_MSK)																		/*!< \brief Extract the interrupt level from UINT32 value */
#define CVT_V1724_SET_INT_LEVEL( reg, value)	reg= (((UINT32)reg)& ~CVT_V1724_VME_CTRL_INT_LEVEL_MSK)| ((UINT32)value& CVT_V1724_VME_CTRL_INT_LEVEL_MSK)				/*!< \brief Sets the interrupt level value into UINT32 value */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_VME_STATUS_MSK
*   \brief   Status register bitmasks
*   \todo    To be defined
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_VME_STS_DATA_READY_MSK		= 0x0001,		/*!< Data ready bit */
	CVT_V1724_VME_STS_FULL_MSK				= 0x0002,		/*!< Full bit */
	CVT_V1724_VME_STS_BERR_FLAG_MSK			= 0x0004,		/*!< Berr flag bit */
	CVT_V1724_VME_STS_PURGED_MSK			= 0x0008,		/*!< Purged bit */
} CVT_V1724_VME_STATUS_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_TRIGGER_SRC_ENABLE_MSK
*   \brief   Trigger enable bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_TRGEN_CH0_MSK				= 0x00000001,		/*!< Enable CH 0 trigger bit */
	CVT_V1724_TRGEN_CH1_MSK				= 0x00000002,		/*!< Enable CH 1 trigger bit */
	CVT_V1724_TRGEN_CH2_MSK				= 0x00000004,		/*!< Enable CH 2 trigger bit */
	CVT_V1724_TRGEN_CH3_MSK				= 0x00000008,		/*!< Enable CH 3 trigger bit */
	CVT_V1724_TRGEN_CH4_MSK				= 0x00000010,		/*!< Enable CH 4 trigger bit */
	CVT_V1724_TRGEN_CH5_MSK				= 0x00000020,		/*!< Enable CH 5 trigger bit */
	CVT_V1724_TRGEN_CH6_MSK				= 0x00000040,		/*!< Enable CH 6 trigger bit */
	CVT_V1724_TRGEN_CH7_MSK				= 0x00000080,		/*!< Enable CH 7 trigger bit */
	CVT_V1724_TRGEN_EXT_MSK				= 0x40000000,		/*!< External trigger enable bit */
	CVT_V1724_TRGEN_SW_MSK				= 0x80000000,		/*!< Software trigger enable bit */
} CVT_V1724_TRIGGER_SRC_ENABLE_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_FP_TRIGGER_OUT_ENABLE_MSK
*   \brief   Front Panel Trigger Out enable bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_FPTRGEN_CH0_MSK			= 0x00000001,		/*!< Enable CH 0 trigger bit */
	CVT_V1724_FPTRGEN_CH1_MSK			= 0x00000002,		/*!< Enable CH 1 trigger bit */
	CVT_V1724_FPTRGEN_CH2_MSK			= 0x00000004,		/*!< Enable CH 2 trigger bit */
	CVT_V1724_FPTRGEN_CH3_MSK			= 0x00000008,		/*!< Enable CH 3 trigger bit */
	CVT_V1724_FPTRGEN_CH4_MSK			= 0x00000010,		/*!< Enable CH 4 trigger bit */
	CVT_V1724_FPTRGEN_CH5_MSK			= 0x00000020,		/*!< Enable CH 5 trigger bit */
	CVT_V1724_FPTRGEN_CH6_MSK			= 0x00000040,		/*!< Enable CH 6 trigger bit */
	CVT_V1724_FPTRGEN_CH7_MSK			= 0x00000080,		/*!< Enable CH 7 trigger bit */
	CVT_V1724_FPTRGEN_EXT_MSK			= 0x40000000,		/*!< External trigger enable bit */
	CVT_V1724_FPTRGEN_SW_MSK			= 0x80000000,		/*!< Software trigger enable bit */
} CVT_V1724_FP_TRIGGER_OUT_ENABLE_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_BROAD_CH_CONTROL_MSK
*   \brief   CVT_V1724_BROAD_CH_CTRL: Control register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_BROAD_CHCTRL_GATE_MODE_MSK			= 0x00000001,	/*!< Gate mode bit ( 0 --> Window mode, 1 --> Single mode ) */
	CVT_V1724_BROAD_CHCTRL_TRG_OVERLAP_MSK			= 0x00000002,	/*!< Trigger Overlapping enable bit */
	CVT_V1724_BROAD_CHCTRL_MEM_TEST_ENABLE_MSK		= 0x00000008,	/*!< Memory test enabled bit */
	CVT_V1724_BROAD_CHCTRL_MEM_ACC_MODE_MSK			= 0x00000010,	/*!< Memory Access mode bit ( 0 --> random access mode, 1--> sequential access mode) */
	CVT_V1724_BROAD_CHCTRL_TRG_OUT_THR_MSK			= 0x00000040,	/*!< Trigger Output Threshold mode bit ( 0 --> Over, 1 --> Under) */
	CVT_V1724_BROAD_CHCTRL_DES_MODE_MSK				= 0x00001000,	/*!< Switch to des mode (4 channel mode) ( 0 --> Normal mode , 1 --> Des mode) (V1731 only) */
} CVT_V1724_BROAD_CH_CONTROL_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_BROAD_CH_RND_ACC_MSK
*   \brief   CVT_V1724_BROAD_CH_RND_ACC register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_BROAD_CHRNDACC_BLOCK_ADD_MSK		= 0x000003FF,	/*!< Address of Block to be read bits */
	CVT_V1724_BROAD_CHRNDACC_SAMPLE_NUM_MSK		= 0x003FFC00,	/*!< Number of samples to be read bits */
	CVT_V1724_BROAD_CHRNDACC_OFFSET_MSK			= 0xFFC00000,	/*!< Offset of Address Data to be read bits */
} CVT_V1724_BROAD_CH_RND_ACC_MSK;

#define CVT_V1724_GET_CH_RND_ACC_BLOCK_ADD( reg)			(((UINT32)reg)& CVT_V1724_BROAD_CHRNDACC_BLOCK_ADD_MSK)																				/*!< \brief Extract the Address of Block to be read from UINT32 value */
#define CVT_V1724_SET_CH_RND_ACC_BLOCK_ADD( reg, value)		reg= (((UINT32)reg)& ~CVT_V1724_BROAD_CHRNDACC_BLOCK_ADD_MSK)| ((UINT32)value& CVT_V1724_BROAD_CHRNDACC_BLOCK_ADD_MSK)				/*!< \brief Sets the Address of Block to be read into UINT32 value */

#define CVT_V1724_GET_CH_RND_ACC_SAMPLE_NUM( reg)			((((UINT32)reg)& CVT_V1724_BROAD_CHRNDACC_SAMPLE_NUM_MSK)>> 10)																		/*!< \brief Extract the Number of samples to be read from UINT32 value */
#define CVT_V1724_SET_CH_RND_ACC_SAMPLE_NUM( reg, value)	reg= (((UINT32)reg)& ~CVT_V1724_BROAD_CHRNDACC_SAMPLE_NUM_MSK)| ((((UINT32)value)<< 10)& CVT_V1724_BROAD_CHRNDACC_SAMPLE_NUM_MSK)	/*!< \brief Sets the Number of samples to be read into UINT32 value */

#define CVT_V1724_GET_CH_RND_ACC_OFFSET( reg)				((((UINT32)reg)& CVT_V1724_BROAD_CHRNDACC_OFFSET_MSK)>> 22)																			/*!< \brief Extract the Offset of Address Data  from UINT32 value */
#define CVT_V1724_SET_CH_RND_ACC_OFFSET( reg, value)		reg= (((UINT32)reg)& ~CVT_V1724_BROAD_CHRNDACC_OFFSET_MSK)| ((((UINT32)value)<< 22)& CVT_V1724_BROAD_CHRNDACC_OFFSET_MSK)			/*!< \brief Sets the Offset of Address Data into UINT32 value */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_BOARD_INFO_MSK
*   \brief   CVT_V1724_BOARD_INFO register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_BRDINF_ID_MSK					= 0x000000ff,	/*!< Board info ID bits \ref CVT_V17XX_TYPES */
	CVT_V1724_BRDINF_CH_BLOCK_SIZE_MUL_MSK	= 0x0000ff00,	/*!< Channel block size multiplier bits (as multiple of 256K WORD 32)*/
} CVT_V1724_BOARD_INFO_MSK;

#define CVT_V1724_GET_BRDINF_ID( reg)						(((UINT32)reg)& CVT_V1724_BRDINF_ID_MSK)															/*!< \brief Extract the Board info ID from UINT32 value */
#define CVT_V1724_GET_BRDINF_BLOCK_SIZE_MUL( reg)			((((UINT32)reg)& CVT_V1724_BRDINF_CH_BLOCK_SIZE_MUL_MSK)>> 8)										/*!< \brief Extract the channel block size multiplier from UINT32 value */
#define CVT_V1724_GET_BRDINF_BLOCK_SIZE_KW( reg)			(((UINT32)reg)& CVT_V1724_BRDINF_CH_BLOCK_SIZE_MUL_MSK)												/*!< \brief Extract the channel block size (as number of KWORD 32) from UINT32 value */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_ACQ_CONTROL_MSK
*   \brief   CVT_V1724_ACQ_CONTROL register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_ACQCTRL_ACQ_MODE_MSK			= 0x00000003,	/*!< Acqisition mode msk */
	CVT_V1724_ACQCTRL_START_MSK				= 0x00000004,	/*!< 0--> Stop acquisition 1--> Start acquisition */
	CVT_V1724_ACQCTRL_EVENT_COUNTER_ALL_MSK	= 0x00000008,	/*!< 0--> Event counter counts only generated and accepted triggers 1--> Event counter counts all generated triggers */
	CVT_V1724_ACQCTRL_DOWNSAMPLE_MSK		= 0x00000010,	/*!< Downsample enable bit */
} CVT_V1724_ACQ_CONTROL_MSK;

#define CVT_V1724_GET_ACQCTRL_ACQ_MODE( reg)			(((UINT32)reg)& CVT_V1724_ACQCTRL_ACQ_MODE_MSK)																		/*!< \brief Extract the acquisition mode value from UINT32 value */
#define CVT_V1724_SET_ACQCTRL_ACQ_MODE( reg, value)		reg= (((UINT32)reg)& ~CVT_V1724_ACQCTRL_ACQ_MODE_MSK)| ((UINT32)value& CVT_V1724_ACQCTRL_ACQ_MODE_MSK)				/*!< \brief Sets the acquisition mode value into UINT32 value */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_ACQ_CONTROL_ACQ_MODES
*   \brief   CVT_V1724_ACQ_CONTROL_MSK acquisition modes
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_ACQCTRL_ACQ_MODE_REGISTER_CTRL		= 0,	/*!< Register controlled acquisition mode */
	CVT_V1724_ACQCTRL_ACQ_MODE_S_IN_CTRL			= 1,	/*!< S-IN controlled acquisition mode */
	CVT_V1724_ACQCTRL_ACQ_MODE_S_IN_GATE			= 2,	/*!< S-IN gate acquisition mode */
	CVT_V1724_ACQCTRL_ACQ_MODE_MULTIBOARD_SYNC		= 3,	/*!< Multiboard sync acquisition mode */
} CVT_V1724_ACQ_CONTROL_ACQ_MODES;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_ACQ_STATUS_MSK
*   \brief   CVT_V1724_ACQ_STATUS register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_ACQSTS_MEB_NOT_EMPTY_MSK		= 0x00000001,	/*!< MEB not empty bit */
	CVT_V1724_ACQSTS_MEB_FULL_MSK			= 0x00000002,	/*!< MEB full bit */
	CVT_V1724_ACQSTS_RUN_MSK				= 0x00000004,	/*!< Run status bit */
	CVT_V1724_ACQSTS_EVENT_RDY_MSK			= 0x00000008,	/*!< Event ready bit */
	CVT_V1724_ACQSTS_EVENT_FULL_MSK			= 0x00000010,	/*!< Event full bit */
	CVT_V1724_ACQSTS_CLKEXT_MSK				= 0x00000020,	/*!< External clock bit */
	CVT_V1724_ACQSTS_PLL_BYPASS_MSK			= 0x00000040,	/*!< PLL Bypass bit */
	CVT_V1724_ACQSTS_PLL_STATUS_MSK			= 0x00000080,	/*!< PLL Status bit */
	CVT_V1724_ACQSTS_S_IN_MSK				= 0x00008000,	/*!< S-IN status bit */
} CVT_V1724_ACQ_STATUS_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_CH_ENABLE_MSK
*   \brief   CVT_V1724_CH_ENABLE register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_CHEN_CH0_MSK				= 0x0001,		/*!< Enable CH 0 bit */
	CVT_V1724_CHEN_CH1_MSK				= 0x0002,		/*!< Enable CH 1 bit */
	CVT_V1724_CHEN_CH2_MSK				= 0x0004,		/*!< Enable CH 2 bit */
	CVT_V1724_CHEN_CH3_MSK				= 0x0008,		/*!< Enable CH 3 bit */
	CVT_V1724_CHEN_CH4_MSK				= 0x0010,		/*!< Enable CH 4 bit */
	CVT_V1724_CHEN_CH5_MSK				= 0x0020,		/*!< Enable CH 5 bit */
	CVT_V1724_CHEN_CH6_MSK				= 0x0040,		/*!< Enable CH 6 bit */
	CVT_V1724_CHEN_CH7_MSK				= 0x0080,		/*!< Enable CH 7 bit */
} CVT_V1724_CH_ENABLE_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_CH_ADC_CONF_MSK
*   \brief   ADC CH Configuration register bitmasks for V1724/V1720 only
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_CHADCCONF_DITHER_MSK			= 0x00000001,	/*!< CH ADC Dither bit */
	CVT_V1724_CHADCCONF_CLK_DUTY_STAB_MSK	= 0x00000002,	/*!< CH ADC Clock Duty cycle stabilizer bit */
	CVT_V1724_CHADCCONF_RND_MSK				= 0x00000004,	/*!< CH ADC Output Randomize bit */
} CVT_V1724_CH_ADC_CONF_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_CH_ADC_CONF_MSK_2
*   \brief   ADC CH Configuration register bitmasks for V1731/V1721 only
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_CHADCCONF_CAL_MSK_2			= 0x00000002,	/*!< CH ADC calibration bit */
} CVT_V1724_CH_ADC_CONF_MSK_2;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_FRONT_PANEL_IO_MSK
*   \brief   Front Panel IO data register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_FPIO_MSK			= 0x0000FFFF,			/*!< IO data value */
} CVT_V1724_FRONT_PANEL_IO_MSK;

#define CVT_V1724_GET_FRONT_PANEL_IO( reg)			(((UINT32)reg)& CVT_V1724_FPIO_MSK)													/*!< \brief Extract front panel data from UINT32 value */
#define CVT_V1724_SET_FRONT_PANEL_IO( reg, value)	reg= (((UINT32)reg)& ~CVT_V1724_FPIO_MSK)| ((UINT32)value& CVT_V1724_FPIO_MSK)		/*!< \brief Sets front panel data into UINT32 value */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_FRONT_PANEL_IO_CTRL_MSK
*   \brief   Front Panel IO control register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_FPIO_CTRL_TTL_MSK			= 0x00000001,	/*!< TTL/NIM external signal bit */
	CVT_V1724_FPIO_CTRL_OUT_DIS_MSK		= 0x00000002,	/*!< Output disable bit */
	CVT_V1724_FPIO_CTRL_DIR_MSK			= 0x0000003C,	/*!< Direction msk  */
	CVT_V1724_FPIO_CTRL_MODE_MSK		= 0x000000C0,	/*!< Mode msk ( bit 0x00000100 is don't care ) */
} CVT_V1724_FRONT_PANEL_IO_CTRL_MSK;

#define CVT_V1724_GET_FPIO_CTRL_DIR( reg)			((((UINT32)reg)& CVT_V1724_FPIO_CTRL_DIR_MSK)>> 2)															/*!< \brief Extract the Front panel IO direction from UINT32 value */
#define CVT_V1724_SET_FPIO_CTRL_DIR( reg, value)	reg= (((UINT32)reg)& ~CVT_V1724_FPIO_CTRL_DIR_MSK)| ((((UINT32)value)<< 2)& CVT_V1724_FPIO_CTRL_DIR_MSK)	/*!< \brief Sets the Front panel IO direction into UINT32 value */

#define CVT_V1724_GET_FPIO_CTRL_MODE( reg)			((((UINT32)reg)& CVT_V1724_FPIO_CTRL_MODE_MSK)>> 6)															/*!< \brief Extract the Front panel IO mode from UINT32 value */
#define CVT_V1724_SET_FPIO_CTRL_MODE( reg, value)	reg= (((UINT32)reg)& ~CVT_V1724_FPIO_CTRL_MODE_MSK)| ((((UINT32)value)<< 6)& CVT_V1724_FPIO_CTRL_MODE_MSK)	/*!< \brief Sets the Front panel IO mode into UINT32 value */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_FRONT_PANEL_IO_MODES
*   \brief   Front Panel IO modes
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_FPIO_MODES_GPIO			= 0,			/*!< General purpose IO */
	CVT_V1724_FPIO_MODES_PROGIO			= 1,			/*!< Programmed IO */
	CVT_V1724_FPIO_MODES_PATTERN		= 2,			/*!< Pattern mode */
} CVT_V1724_FRONT_PANEL_IO_MODES;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_DAC_CONF_MSK
*   \brief   CH DAC data configuration register bitmasks
*   \todo    Bits to define
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_CHDAC_DATA_MSK			= 0x0000FFFF,	/*!< DAC data bits */
	CVT_V1724_CHDAC_SET_A_MSK			= 0x00100000,	/*!< Set data for DAC A */
	CVT_V1724_CHDAC_SET_B_MSK			= 0x00240000,	/*!< Set data for DAC B */
} CVT_V1724_DAC_CONF_MSK;

#define CVT_V1724_GET_CH_DAC_CONF( reg)			(((UINT32)reg)& CVT_V1724_CHDAC_DATA_MSK)																/*!< \brief Extract DAC's data from UINT32 value */
#define CVT_V1724_SET_CH_DAC_CONF( reg, value)	reg= (((UINT32)reg)& ~CVT_V1724_CHDAC_DATA_MSK)| ((UINT32)value& CVT_V1724_CHDAC_DATA_MSK)				/*!< \brief Sets DAC's data into UINT32 value */
  
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_CH_STATUS_MSK
*   \brief   CH status register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_CHSTS_FIFO_FULL_MSK		= 0x00000001,	/*!< CH Descriptor FIFO full Status bit */
	CVT_V1724_CHSTS_FIFO_EMPTY_MSK		= 0x00000002,	/*!< CH Descriptor FIFO empty Status bit */
	CVT_V1724_CHSTS_DAC_BUSY_MSK		= 0x00000004,	/*!< CH DAC Busy Status bit */
	CVT_V1724_CHSTS_BIST_END_MSK		= 0x00000008,	/*!< CH BIST end Status bit */
	CVT_V1724_CHSTS_BIST_OK_MSK			= 0x00000010,	/*!< CH BIST result bit */
	CVT_V1724_CHSTS_BLOCK_REM_OK_MSK	= 0x00000020,	/*!< CH Block Remove result bit */
	CVT_V1724_CHSTS_CAL_RUN_MSK			= 0x00000040,	/*!< CH calibration run bit ( 1 = calibration completed ) (V1731/V1721 only) */
} CVT_V1724_CH_STATUS_MSK;
  
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_NUM_BLOCKS
*   \brief   The number for blocks 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_NBLK_1= 0,			/*!<    1 block  */
	CVT_V1724_NBLK_2,				/*!<    2 blocks */
	CVT_V1724_NBLK_4,				/*!<    4 blocks */
	CVT_V1724_NBLK_8,				/*!<    8 blocks */
	CVT_V1724_NBLK_16,				/*!<   16 blocks */
	CVT_V1724_NBLK_32,				/*!<   32 blocks */
	CVT_V1724_NBLK_64,				/*!<   64 blocks */
	CVT_V1724_NBLK_128,				/*!<  128 blocks */
	CVT_V1724_NBLK_256,				/*!<  256 blocks */
	CVT_V1724_NBLK_512,				/*!<  512 blocks */
	CVT_V1724_NBLK_1024,			/*!< 1024 blocks */
} CVT_V1724_NUM_BLOCKS;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_EXTCLOCK
*   \brief   External clock allowed values
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_EXTCLK_10000KHz= 0,		/*!< 10   MHz */
	CVT_V1724_EXTCLK_40000KHz,			/*!< 40   MHz */
	CVT_V1724_EXTCLK_50000KHz,			/*!< 50   MHz */
	CVT_V1724_EXTCLK_62500KHz,			/*!< 62.5 MHz */
} CVT_V1724_EXTCLOCK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*!          CVT_V1724_EXTCLOCK_KHZ
*   \brief   External clock allowed values (KHz)
*/
////////////////////////////////////////////////////////////////////////////////////////////////
static const UINT32 CVT_V1724_EXTCLOCK_KHZ[]=
{
	10000,							/*!< 10   MHz */
	40000,							/*!< 40   MHz */
	50000,							/*!< 50   MHz */
	62500,							/*!< 62.5 MHz */
};

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V17XX_BOARD_CLOCK_INDEX
*   \brief   Boards internal clock indexer for CVT_V17XX_BOARD_CLOCK_KHZ[]
*   \sa      CVT_V17XX_BOARD_CLOCK_KHZ[]
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_BOARD_CLOCK_INDEX= 0,		/*!< V1724          : 100   MHz */
	CVT_V1721_BOARD_CLOCK_INDEX,		/*!< V1721          : 500   MHz */
	CVT_V1731_BOARD_CLOCK_INDEX,		/*!< V1731          : 500   MHz */
	CVT_V1731_DES_BOARD_CLOCK_INDEX,	/*!< V1731 Des mode :1000   MHz */
	CVT_V1720_BOARD_CLOCK_INDEX,		/*!< V1720          : 250   MHz */
	CVT_V1740_BOARD_CLOCK_INDEX,		/*!< V1740          :  62.5 MHz */
	CVT_V1751_BOARD_CLOCK_INDEX,		/*!< V1751          : 1000  MHz */
	CVT_V1751_DES_BOARD_CLOCK_INDEX,	/*!< V1751 Des mode : 2000  MHz */
} CVT_V17XX_BOARD_CLOCK_INDEX;

////////////////////////////////////////////////////////////////////////////////////////////////
/*!          CVT_V17XX_BOARD_CLOCK_KHZ
*   \brief   Boards internal clock values (KHz): use \ref CVT_V17XX_BOARD_CLOCK_INDEX enumeration as indexer
*   \sa      CVT_V17XX_BOARD_CLOCK_INDEX
*/
////////////////////////////////////////////////////////////////////////////////////////////////
static const UINT32 CVT_V17XX_BOARD_CLOCK_KHZ[]=
{
	100000,							/*!< V1724          : 100   MHz */
	500000,							/*!< V1721          : 500   MHz */
	500000,							/*!< V1731          : 500   MHz */
	1000000,						/*!< V1731 Des mode :1000   MHz */
	250000,							/*!< V1720          : 250   MHz */
	 62500,							/*!< V1740          :  62.5 MHz */
	1000000,						/*!< V1751          :1000   MHz */
	2000000,						/*!< V1751 Des mode :2000   MHz */
};

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_MCST_CBLT_ADD_CTRL_MSK
*   \brief   V1724 MCST-CBLT Address/Control register bit masks
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_MCST_CBLT_ADD_MSK			= 0x000000FF,		/*!< Address bits mask */
	CVT_V1724_MCST_CBLT_CTRL_MSK		= 0x00000300,		/*!< Control bits mask */
} CVT_V1724_MCST_CBLT_ADD_CTRL_MSK;

#define CVT_V1724_GET_MCST_CBLT_ADD( reg)			(((UINT32)reg)& CVT_V1724_MCST_CBLT_ADD_MSK)																		/*!< \brief Extract the Base Address of from UINT32 value */
#define CVT_V1724_SET_MCST_CBLT_ADD( reg, value)	reg= (((UINT32)reg)& ~CVT_V1724_MCST_CBLT_ADD_MSK)| ((UINT32)value& CVT_V1724_MCST_CBLT_ADD_MSK)					/*!< \brief Sets the Base Address into UINT32 value */

#define CVT_V1724_GET_MCST_CBLT_CTRL( reg)			((((UINT32)reg)& CVT_V1724_MCST_CBLT_CTRL_MSK)>> 8)																	/*!< \brief Extract the MCST-CBLT Control from UINT32 value */
#define CVT_V1724_SET_MCST_CBLT_CTRL( reg, value)	reg= (((UINT32)reg)& ~CVT_V1724_MCST_CBLT_CTRL_MSK)| ((((UINT32)value)<< 8)& CVT_V1724_MCST_CBLT_CTRL_MSK)			/*!< \brief Sets MCST-CBLT Control into UINT32 value */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_MCST_CBLT_CTRL_BOARDS
*   \brief   V1724 MCST-CBLT control boards
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_MCST_CBLT_CTRL_DISABLED_BOARD			= 0,		/*!< Disabled Board */
	CVT_V1724_MCST_CBLT_CTRL_LAST_BOARD				= 1,		/*!< Last Board */
	CVT_V1724_MCST_CBLT_CTRL_FIRST_BOARD			= 2,		/*!< First Board */
	CVT_V1724_MCST_CBLT_CTRL_MID_BOARD				= 3,		/*!< Middle Board */
} CVT_V1724_MCST_CBLT_CTRL_BOARDS;

////////////////////////////////////////////////////////////////////////////////////////////////
/*!          V1724 Flash programming
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#define V1724_FLASH_PAGE_SIZE					264				/*!< V1724 flash page size */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_FLASH_OPCODES
*   \brief   V1724 Flash register opcodes
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_FOP_PAGE_ERASE					= 0x0081,		/*!< V1724 flash page erase */
	CVT_V1724_FOP_PAGE_PROG_TH_BUF1				= 0x0082,		/*!< V1724 flash page write */
	CVT_V1724_FOP_PAGE_READ						= 0x00D2,		/*!< V1724 flash page read  */
} CVT_V1724_FLASH_OPCODES;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_FLASH_BANK
*   \brief   V1724 Flash banks
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_ROM_FLASH_PAGE					= 0,			/*!< V1724 ROM flash bank */
	CVT_V1724_PLL_FLASH_PAGE					= 1,			/*!< V1724 PLL flash bank */
	CVT_V1724_FB_STANDARD						= 48,			/*!< V1724 firmware standard flash bank */
	CVT_V1724_FB_BACKUP							= 2072,			/*!< V1724 firmware backup flash bank   */
} CVT_V1724_FLASH_BANK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_FLASH_EN_MSK
*   \brief   Flash enable register bitmasks
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_FLEN_EN_MSK				= 0x00000001,	/*!< Flash enable bit */
} CVT_V1724_FLASH_EN_MSK;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V1724_MON_MODES
*   \brief   V1724 Output monitor mode
*            
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V1724_MONMODE_TRIGGER_MAJ			= 0,			/*!< V1724 channel trigger majority mode */
	CVT_V1724_MONMODE_TEST					= 1,			/*!< V1724 channel test mode */
	CVT_V1724_MONMODE_MONITOR				= 2,			/*!< V1724 channel ADC monitor mode */
	CVT_V1724_MONMODE_OCCUPANCY				= 3,			/*!< V1724 channel buffer occupancy mode */
	CVT_V1724_MONMODE_SW_CTRL				= 4,			/*!< V1724 channel direct software monitor control mode */
} CVT_V1724_MON_MODES;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \struct  CVT_V1724_ROM_CONFIG
*   \brief   V1724 board ROM configuration
*            
*            This structure stores the ROM configuration values
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	UINT8 m_chksum;							/*!< \brief Configuration ROM checksum */
	UINT32 m_chksum_len;					/*!< \brief Configuration ROM checksum length */
	UINT32 m_const;							/*!< \brief Configuration ROM constant */
	UINT8 m_c_code;							/*!< \brief Configuration ROM c_code */
	UINT8 m_r_code;							/*!< \brief Configuration ROM r_code */
	UINT32 m_OUI;							/*!< \brief Configuration ROM Manufacturer identifier (IEEE OUI) */
	UINT8 m_version;						/*!< \brief Configuration ROM Purchased version of the Mod.V1724 */
	UINT32 m_board_id;						/*!< \brief Configuration ROM Board identifier \ref CVT_V17XX_ROM_CFG_BOARD_ID */
	UINT32 m_revision;						/*!< \brief Configuration ROM Hardware revision identifier */
	UINT16 m_serial;						/*!< \brief Configuration ROM Serial number */
	UINT8 m_VCXO_type;						/*!< \brief Configuration ROM VCXO type */
} CVT_V1724_ROM_CONFIG;


////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V17XX_ROM_CFG_VCXO_TYPE
*   \brief   Configurazion ROM VCXO types
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V17XX_RCFG_VCXO_500	= 1,		//  VCXO  500 MHz
	CVT_V17XX_RCFG_VCXO_1000= 0,		//  VCXO 1000 MHz
} CVT_V17XX_ROM_CFG_VCXO_TYPE;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    CVT_V17XX_ROM_CFG_BOARD_ID
*   \brief   Configurazion ROM board IDs
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	CVT_V17XX_RCFG_BOARD_ID_V1724	= 0x00000000| 1724,		//  V1724
	CVT_V17XX_RCFG_BOARD_ID_VX1724	= 0x00010000| 1724,		// VX1724
	CVT_V17XX_RCFG_BOARD_ID_V1721	= 0x00000000| 1721,		//  V1721
	CVT_V17XX_RCFG_BOARD_ID_VX1721	= 0x00010000| 1721,		// VX1721
	CVT_V17XX_RCFG_BOARD_ID_V1731	= 0x00000000| 1731,		//  V1731
	CVT_V17XX_RCFG_BOARD_ID_VX1731	= 0x00010000| 1731,		// VX1731
	CVT_V17XX_RCFG_BOARD_ID_V1720	= 0x00000000| 1720,		//  V1720
	CVT_V17XX_RCFG_BOARD_ID_VX1720	= 0x00010000| 1720,		// VX1720
	CVT_V17XX_RCFG_BOARD_ID_V1740	= 0x00000000| 1740,		//  V1740
	CVT_V17XX_RCFG_BOARD_ID_VX1740	= 0x00010000| 1740,		// VX1740
	CVT_V17XX_RCFG_BOARD_ID_V1751	= 0x00000000| 1751,		//  V1751
	CVT_V17XX_RCFG_BOARD_ID_VX1751	= 0x00010000| 1751,		// VX1751
} CVT_V17XX_ROM_CFG_BOARD_ID;

// HACK V1740 TBC

#define CVT_V1724_MIN_FIRMARE_REV	0x0002		/*!< Minimum firmware revision supported by this tool version */


////////////////////////////////////////////////////////////////////////////////////////////////
// Output buffer macros
////////////////////////////////////////////////////////////////////////////////////////////////

#define V1724_HEADER_TAG_MSK							0xA0000000													/*!< \brief The V1724 Header tag msk */

#define CVT_V1724_IS_HEADER_TAG(data_0)					((data_0& 0xF0000000)== V1724_HEADER_TAG_MSK)				/*!< \brief Checks if type is header tag */

#define CVT_V1724_GET_EVENT_TAG(data_0)					((UINT32)((((UINT32)data_0)>>28)& 0x0000000f))				/*!< \brief Gets the tag of this event */
#define CVT_V1724_GET_EVENT_SIZE(data_0)				((UINT32)(((UINT32)data_0)& 0x0fffffff))					/*!< \brief Gets the size of this event */

#define CVT_V1724_GET_EVENT_ACTIVE_CHANNELS(data_1)		((UINT32)(((UINT32)data_1)& 0x000000ff))					/*!< \brief Gets the active channel mask of this event */
#define CVT_V1724_GET_EVENT_BOARD_ID(data_1)			((UINT32)((((UINT32)data_1)>>27)& 0x0000001f))				/*!< \brief Gets the board id of this event */

#define CVT_V1724_GET_EVENT_COUNT(data_2)				((UINT32)(((UINT32)data_2)& 0x00ffffff))					/*!< \brief Gets the counter of this event */

#define CVT_V1724_GET_EVENT_TRIGGER_TIME_TAG(data_3)	((UINT32)(((UINT32)data_3)& 0xffffffff))					/*!< \brief Gets the Trigger time tag of this event */


#if defined (__GNUC__)
	#define		PACKED_1		__attribute__ ((packed, aligned(1)))
	#define		_INLINE_		__inline__ 
#else
	#define		PACKED_1
	#define		_INLINE_		
#endif
#if defined(WIN32)|| defined(_WIN32_WCE)
	#pragma pack(push)
	#pragma pack(1)
#endif


#define CVT_V1724_MAX_BLT_EVENT_NUM		4		/*!< \brief The maximum number of blt_event per readout cycle */

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \union   CVT_V1724_HEADER
*   \brief   V1724 board event header
*            
*            This structure stores the readout event's header struct
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef union PACKED_1
{
	struct										
	{
		union
		{
			struct
			{
				UINT32 m_event_size: 28 ;		/* Event size */		
				UINT32 m_header_tag: 4 ;		/* Header tag */		
			} m_fields ;
			UINT32 m_DWORD;
		} m_HEADER_0;
		union
		{
			struct
			{
				UINT32 m_active_channel_msk: 8 ;	/* Active channels msk */		
				UINT32 m_reserved: 19 ;				/* reserved */		
				UINT32 m_board_id: 5 ;				/* Board Id */		
			} m_fields ;
			UINT32 m_DWORD;
		} m_HEADER_1;
		union
		{
			struct
			{
				UINT32 m_event_counter: 24 ;		/* Event counter */		
				UINT32	: 8;						/* undefined */		
			} m_fields ;
			UINT32 m_DWORD;
		} m_HEADER_2;
		union
		{
			struct
			{
				UINT32 m_trigger_time_tag: 32;		/* Timestamp */		
			} m_fields ;
			UINT32 m_DWORD;
		} m_HEADER_3;
	} m_fields;
	UINT32 m_DWORD[ 4];
} CVT_V1724_HEADER;

#if defined(WIN32)|| defined(_WIN32_WCE)
	#pragma pack(pop)
#endif


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
/*! \fn      BOOL cvt_V1724_open( cvt_V1724_data* p_data, UINT16 base_address, long vme_handle, CVT_V17XX_TYPES type);
*   \brief   V1724 VME boards data initialization
*            
*            Provides specific handling for V1724 boards opening.
*   \param   p_data Pointer to board data
*   \param   base_address The board base address (MSW)
*   \param   vme_handle The VME handle
*   \param   type The board type : it must be a \ref CVT_V17XX_TYPES value
*   \return  TRUE: board successfully opened
*   \note    Must be called before any other board specific API.
*   \sa      CVT_V17XX_TYPES 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_open( cvt_V1724_data* p_data, UINT16 base_address, long vme_handle, CVT_V17XX_TYPES type);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_close( cvt_V1724_data* p_data);
*   \brief   V1724 VME boards closing and resource free
*            
*            Provides specific handling for V1724 boards closing.
*   \param   p_data Pointer to board data
*   \return  TRUE: board successfully closed
*   \note    Must be called when done with any other board specific API.
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_close( cvt_V1724_data* p_data);

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
/*! \fn      cvt_V1724_read_data( cvt_V1724_data* p_data, UINT32* p_ch_max_samples, UINT32* p_num_events);
*   \brief   Reads data from the board's channels and stores to user buffer
*            
*            Calling cvt_V1724_read_data will cache the channels' data into internal buffer
*            Then call \ref cvt_V1724_get_buffer_cache to get cached data
*   \param   p_data Pointer to board data
*   \param   p_ch_max_samples returns the maximum number of samples per channel read for each event
*   \param   p_num_events returns the number of events read
*   \return  TRUE: Procedure successfully executed
*   \sa      cvt_V1724_get_buffer_cache
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_read_data( cvt_V1724_data* p_data, UINT32* p_ch_max_samples, UINT32* p_num_events);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_buffer_cache( cvt_V1724_data* p_data, UINT16 event_index, UINT8 ch_index, UINT16* p_buff, UINT32* p_buff_size, UINT8 *p_board_id, UINT32* p_trigger_time_tag, UINT32* p_event_counter)
*   \brief   Reads data cache from previous cvt_V1724_read_data data call.
*            
*            Call cvt_FIFO_BLT_read for Multiple Event Buffer and stores data into user buffer.
*            If the returned data is just a V1724 not valid datum, this is discarded.
*   \param   p_data Pointer to board data
*   \param   event_index The event index from which retrive data 
*   \param   ch_index The channel index 
*   \param   p_buff The target buffer: caller allocated
*   \param   p_buff_size The buffer size (16 bit word). On exit will holds the number of words really read.
*   \param   p_board_id The board id stored into event
*   \param   p_trigger_time_tag The trigger time tag stored into event
*   \param   p_event_counter The counter stored into event
*   \return  TRUE: Procedure successfully executed, FALSE elsewhere (e.g. event or channel index not found)
*   \sa      cvt_V1724_read_data
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_buffer_cache( cvt_V1724_data* p_data, UINT16 event_index, UINT8 ch_index, UINT16* p_buff, UINT32* p_buff_size, UINT8 *p_board_id, UINT32* p_trigger_time_tag, UINT32* p_event_counter);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_trigger_mode( cvt_V1724_data* p_data, BOOL falling_edge_enable, BOOL ext_trigger_enable, BOOL sw_trigger_enable, UINT8 ch_trigger_enable_msk, BOOL trigger_overlap_enable, UINT32 post_trigger);
*   \brief   Setups the triggering parameters.
*            
*            Setups the relevant parameters for the triggering mode.
*   \param   p_data Pointer to board data
*   \param   falling_edge_enable Enable/Disable triggering on falling edge
*   \param   ext_trigger_enable Enable/Disable the external trigger.
*   \param   sw_trigger_enable Enable/Disable the software trigger.
*   \param   ch_trigger_enable_msk Enable/Disable trigger from channels thresholds comparison. If bit i of the mask is setted, the channel i feature is setted.
*   \param   trigger_overlap_enable Enable/Disable the trigger overlap feature.
*   \param   post_trigger The amount of post trigger samples
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_trigger_mode( cvt_V1724_data* p_data, BOOL falling_edge_enable, BOOL ext_trigger_enable, BOOL sw_trigger_enable, UINT8 ch_trigger_enable_msk, BOOL trigger_overlap_enable, UINT32 post_trigger);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_trigger_mode( cvt_V1724_data* p_data, BOOL *p_falling_edge_enable, BOOL *p_ext_trigger_enable, BOOL *p_sw_trigger_enable, UINT8 *p_ch_trigger_enable_msk, BOOL *p_trigger_overlap_enable, UINT32 *p_post_trigger);
*   \brief   Gets the trigger out settings
*            
*            Retrives the relevant parameters setting for the triggering mode.
*   \param   p_data Pointer to board data
*   \param   p_falling_edge_enable Triggering on falling edge status
*   \param   p_ext_trigger_enable External trigger status.
*   \param   p_sw_trigger_enable Software trigger status.
*   \param   p_ch_trigger_enable_msk Trigger from channels thresholds comparison status. If bit i of the mask is setted, the channel i feature is setted.
*   \param   p_trigger_overlap_enable Trigger overlap feature status.
*   \param   p_post_trigger Amount of post trigger samples status
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_trigger_mode( cvt_V1724_data* p_data, BOOL *p_falling_edge_enable, BOOL *p_ext_trigger_enable, BOOL *p_sw_trigger_enable, UINT8 *p_ch_trigger_enable_msk, BOOL *p_trigger_overlap_enable, UINT32 *p_post_trigger);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_fp_trigger_out( cvt_V1724_data* p_data, BOOL *p_ext_trigger_enable, BOOL *p_sw_trigger_enable, UINT8 *p_ch_trigger_enable_msk);
*   \brief   Gets the front panel trigger output settings
*            
*            Retrives the relevant parameters setting for the front panel triggering mode.
*   \param   p_data Pointer to board data
*   \param   p_ext_trigger_enable External trigger status output enable.
*   \param   p_sw_trigger_enable Software trigger status output enable.
*   \param   p_ch_trigger_enable_msk Trigger output from channels thresholds comparison status.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_fp_trigger_out( cvt_V1724_data* p_data, BOOL *p_ext_trigger_enable, BOOL *p_sw_trigger_enable, UINT8 *p_ch_trigger_enable_msk);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_fp_trigger_out( cvt_V1724_data* p_data, BOOL ext_trigger_enable, BOOL sw_trigger_enable, UINT8 ch_trigger_enable_msk);
*   \brief   Setups the front panel triggering output parameters.
*            
*            Setups the relevant parameters for the front panel triggering mode.
*   \param   p_data Pointer to board data
*   \param   ext_trigger_enable Enable/Disable the external trigger output.
*   \param   sw_trigger_enable Enable/Disable the software trigger output.
*   \param   ch_trigger_enable_msk Enable/Disable trigger output from channels thresholds comparison
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_fp_trigger_out( cvt_V1724_data* p_data, BOOL ext_trigger_enable, BOOL sw_trigger_enable, UINT8 ch_trigger_enable_msk);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_start_acquisition( cvt_V1724_data* p_data, UINT8 ch_msk);
*   \brief   Starts the acquisition for the spcified channel mask
*            
*   \param   p_data Pointer to board data
*   \param   ch_msk The mask of enabled channels 
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_start_acquisition( cvt_V1724_data* p_data, UINT8 ch_msk);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_stop_acquisition( cvt_V1724_data* p_data);
*   \brief   Stops the acquisition
*            
*   \param   p_data Pointer to board data
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_stop_acquisition( cvt_V1724_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_acquisition_mode( cvt_V1724_data* p_data, BOOL sample_enable, CVT_V1724_NUM_BLOCKS block_size, CVT_V1724_ACQ_CONTROL_ACQ_MODES acquisition_mode, BOOL count_all_trigger, UINT32 downsample_factor);
*   \brief   Setups the acquisition mode parameters.
*            
*            Setups the relevant parameters for the acquisition mode.
*   \param   p_data Pointer to board data
*   \param   sample_enable Enable/Disable the sample acquisition mode: if disabled the acquisition mode is windowed
*   \param   block_size Setup the samples' number per block size foreach channel: it must be a valid \ref CVT_V1724_NUM_BLOCKS identifier.
*   \param   acquisition_mode Setups the acquisition mode
*   \param   count_all_trigger Set to TRUE if you want to count all triggers (accepted and not)
*   \param   downsample_factor If != 0 the download factor will be setted and enabled , disabled otherwise
*   \return  TRUE: Procedure successfully executed
*   \sa      CVT_V1724_NUM_BLOCKS
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_acquisition_mode( cvt_V1724_data* p_data, BOOL sample_enable, CVT_V1724_NUM_BLOCKS block_size, CVT_V1724_ACQ_CONTROL_ACQ_MODES acquisition_mode, BOOL count_all_trigger, UINT32 downsample_factor);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_acquisition_mode( cvt_V1724_data* p_data, BOOL *p_sample_enable, CVT_V1724_NUM_BLOCKS *p_block_size);
*   \brief   Gets the acquisition mode parameters.
*            
*            Retrives the relevant parameters settings for the acquisition mode.
*   \param   p_data Pointer to board data
*   \param   p_sample_enable Sample acquisition mode: if disabled the acquisition mode is windowed
*   \param   p_block_size Samples' number per block size foreach channel: it must be a valid \ref CVT_V1724_NUM_BLOCKS identifier.
*   \return  TRUE: Procedure successfully executed
*   \sa      CVT_V1724_NUM_BLOCKS
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_acquisition_mode( cvt_V1724_data* p_data, BOOL *p_sample_enable, CVT_V1724_NUM_BLOCKS *p_block_size);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_acquisition_status( cvt_V1724_data* p_data, BOOL *p_is_MEB_not_empty, BOOL *p_is_MEB_full, BOOL *p_is_running, BOOL *p_some_event_ready, BOOL *p_event_full, BOOL *p_s_in);
*   \brief   Gets the acquisition status parameters.
*            
*            Retrives the relevant parameters for the acquisition status.
*   \param   p_data Pointer to board data
*   \param   p_is_MEB_not_empty This flag is set if MEB is not empty
*   \param   p_is_MEB_full This flag is set if MEB is full
*   \param   p_is_running This flag is set if acquisition is running
*   \param   p_some_event_ready This flag is set if some event is ready
*   \param   p_event_full This flag is set if event memory is full
*   \param   p_s_in This flag shows the front panel' S-IN signal logical state
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_acquisition_status( cvt_V1724_data* p_data, BOOL *p_is_MEB_not_empty, BOOL *p_is_MEB_full, BOOL *p_is_running, BOOL *p_some_event_ready, BOOL *p_event_full, BOOL *p_s_in);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_buffer_samples( cvt_V1724_data* p_data, UINT16 *p_num_k_samples, CVT_V1724_NUM_BLOCKS *p_num_block_read);
*   \brief   Returns the maximum number of samples per events for each channel
*            
*   \param   p_data Pointer to board data
*   \param   p_num_k_samples The number of samples (as K blocks) per channel or per group in case of CVT_V1740 
*   \param   p_num_block_read The num block register value read ( \ref CVT_V1724_NUM_BLOCKS )
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_buffer_samples( cvt_V1724_data* p_data, UINT16 *p_num_k_samples, CVT_V1724_NUM_BLOCKS *p_num_block_read);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_buffer_samples( cvt_V1724_data* p_data, UINT16 num_k_samples, CVT_V1724_NUM_BLOCKS *p_num_block_written);
*   \brief   Sets the maximum number of samples per events for each channel
*            
*   \param   p_data Pointer to board data
*   \param   num_k_samples The number of samples (as K blocks: valid values are power of 2 multiples) per channel or per group in case of CVT_V1740 
*   \param   p_num_block_written The num block register value written ( \ref CVT_V1724_NUM_BLOCKS )
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_buffer_samples( cvt_V1724_data* p_data, UINT16 num_k_samples, CVT_V1724_NUM_BLOCKS *p_num_block_written);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_dither_enable( cvt_V1724_data* p_data, UINT8 ch_msk, BOOL dither_value);
*   \brief   Setups the channels' dithering feature ( V1724/V1720 only).
*            
*            Enables/Disables the dither feature for each channel specified with ch_msk.
*   \param   p_data Pointer to board data
*   \param   ch_msk The channel mask 
*   \param   dither_value Set to TRUE to enable the dither channels in the mask, FALSE to disable
*   \return  TRUE: Procedure successfully executed
*   \deprecated Use \ref cvt_V1724_set_adc_conf
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_dither_enable( cvt_V1724_data* p_data, UINT8 ch_msk, BOOL dither_value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_dither_enable( cvt_V1724_data* p_data, UINT8 ch_index, BOOL *p_dither_value);
*   \brief   Gets the specified channel' dithering feature status ( V1724/V1720 only).
*            
*            Gets the dither feature status for the specified channel.
*   \param   p_data Pointer to board data
*   \param   ch_index The channel index
*   \param   p_dither_value If TRUE the dither feature is enabled, disable otherwise
*   \return  TRUE: Procedure successfully executed
*   \deprecated Use \ref cvt_V1724_get_adc_conf
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_dither_enable( cvt_V1724_data* p_data, UINT8 ch_index, BOOL *p_dither_value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_adc_conf( cvt_V1724_data* p_data, UINT8 ch_msk, BOOL dither_value, BOOL clk_duty_stab_value, BOOL randomize_value);
*   \brief   Setups the channels' adc configuration ( V1724/V1720 only).
*            
*            Enables/Disables the dither, clock duty cycle stabilizer and output randomize features for each channel specified with ch_msk.
*   \param   p_data Pointer to board data
*   \param   ch_msk The channel mask 
*   \param   dither_value Set to TRUE to enable the dither channels in the mask, FALSE to disable
*   \param   clk_duty_stab_value Set to TRUE to enable the clock duty cycle stabilizer feature, FALSE to disable
*   \param   randomize_value Set to TRUE to enable the output randomized feature, FALSE to disable
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_adc_conf( cvt_V1724_data* p_data, UINT8 ch_msk, BOOL dither_value, BOOL clk_duty_stab_value, BOOL randomize_value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_adc_conf( cvt_V1724_data* p_data, UINT8 ch_index, BOOL *p_dither_value, BOOL *p_clk_duty_stab_value, BOOL *p_randomize_value);
*   \brief   Gets the specified channel' adc configuration ( V1724/V1720 only).
*            
*            Gets the dither, clock duty cycle stabilizer and output randomize features status for the specified channel.
*   \param   p_data Pointer to board data
*   \param   ch_index The channel index
*   \param   p_dither_value If TRUE the dither feature is enabled, disable otherwise
*   \param   p_clk_duty_stab_value If TRUE the clock duty cycle stabilizer feature is enabled, disable otherwise
*   \param   p_randomize_value If TRUE the output randomized feature is enabled, disable otherwise
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_adc_conf( cvt_V1724_data* p_data, UINT8 ch_index, BOOL *p_dither_value, BOOL *p_clk_duty_stab_value, BOOL *p_randomize_value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_adc_calib( cvt_V1724_data* p_data, UINT8 ch_msk);
*   \brief   Performs the specified ADCs' channels calibration ( V1731/V1721 only).
*            
*   \param   p_data Pointer to board data
*   \param   ch_msk The channel mask to calibrate
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_adc_calib( cvt_V1724_data* p_data, UINT8 ch_msk);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_adc_temp( cvt_V1724_data* p_data, UINT8 ch_msk, UINT32* tempadc);
*   \brief   Reads the specified ADCs' channels temperature ( V1751 only).
*            
*   \param   p_data Pointer to board data
*   \param   ch_msk The channel mask read temperature from
*   \param   tampadc The caller allocated storage to hold channels' temperatures: 
*				it must be a CVT_V1724_MAX_CHANNEL UINT32 data array
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_adc_temp( cvt_V1724_data* p_data, UINT8 ch_msk, UINT32* tempadc);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_des_mode( cvt_V1724_data* p_data, BOOL is_des_mode);
*   \brief   Switchs to DES mode or normal mode ( V1731 only).
*            
*            Performs the correct procedure to switch to DES mode ( 4 channels) or normal (8 channels) mode
*   \param   p_data Pointer to board data
*   \param   is_des_mode If TRUE the des mode is setted
*   \return  TRUE: Procedure successfully executed
*   \remark  !!! WARNING !!! Odd channel's input signal must be disconnected and acquisition setting will be modified
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_des_mode( cvt_V1724_data* p_data, BOOL is_des_mode);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_interrupt( cvt_V1724_data* p_data, UINT8 level, UINT32 status_id, UINT16 event_number);
*   \brief   Setups interrupt parameters.
*            
*            Setups the relevant parameters for interrupt usage.
*   \param   p_data Pointer to board data
*   \param   level The interrupt level.
*   \param   status_id The interrupt status id (interrupt vector).
*   \param   event_number The number of events to get an interrupt (setting 0 interrupt feature is disabled).
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_interrupt( cvt_V1724_data* p_data, UINT8 level, UINT32 status_id, UINT16 event_number);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_interrupt( cvt_V1724_data* p_data, UINT8 *p_level, UINT32 *p_status_id, UINT16 *p_event_number);
*   \brief   Gets interrupt parameters.
*            
*            Retrives the relevant parameters settings for interrupt usage.
*   \param   p_data Pointer to board data
*   \param   p_level The interrupt level.
*   \param   p_status_id The interrupt stayus id (interupt vector).
*   \param   p_event_number The number of events to get an interrupt (if 0 interrupt feature is disabled).
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_interrupt( cvt_V1724_data* p_data, UINT8 *p_level, UINT32 *p_status_id, UINT16 *p_event_number);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_readout_mode( cvt_V1724_data* p_data, BOOL enable_bus_error, UINT32 BLT_event_number);
*   \brief   Setups data readout mode parameters.
*            
*            Setups the relevant parameters for data readout.
*   \param   p_data Pointer to board data
*   \param   enable_bus_error Enable bus error: the module is enabled to generate a Bus error to finish a block transfer. 
*   \param   BLT_event_number The number of events to readout foreach BLT cycle.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_readout_mode( cvt_V1724_data* p_data, BOOL enable_bus_error, UINT32 BLT_event_number);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_readout_mode( cvt_V1724_data* p_data, BOOL *p_enable_bus_error, UINT32 *p_BLT_event_number);
*   \brief   Gets data readout mode parameters.
*            
*            Retrives the relevant parameters settings for data readout.
*   \param   p_data Pointer to board data
*   \param   *p_enable_bus_error Bus error status: if TRUE the module is enabled to generate a Bus error to finish a block transfer. 
*   \param   *p_BLT_event_number The number of events to readout foreach BLT cycle.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_readout_mode( cvt_V1724_data* p_data, BOOL *p_enable_bus_error, UINT32 *p_BLT_event_number);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_software_reset( cvt_V1724_data* p_data);
*   \brief   Performs a software reset.
*            
*            Writes a dummy value into SW_RESET_REGISTER register.
*   \param   p_data Pointer to board data
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_software_reset( cvt_V1724_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_data_clear( cvt_V1724_data* p_data);
*   \brief   Performs a data clear.
*            
*            Writes a dummy value into SW_CLEAR_REGISTER register.
*   \param   p_data Pointer to board data
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_data_clear( cvt_V1724_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_channel_offset( cvt_V1724_data* p_data, UINT8 ch_msk, UINT16 offset_value);
*   \brief   Sets channels' offset.
*            
*            Sets the offset value for each channel specified with ch_msk.
*   \param   p_data Pointer to board data
*   \param   ch_msk The channel mask 
*   \param   offset_value The offset value to be applied to specified channels.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_channel_offset( cvt_V1724_data* p_data, UINT8 ch_msk, UINT16 offset_value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_channel_offset( cvt_V1724_data* p_data, UINT8 ch_index, UINT16 *p_offset_value);
*   \brief   Sets specified channel' offset.
*            
*            Retrives the offset value for the specified channel.
*   \param   p_data Pointer to board data
*   \param   ch_index The channel index
*   \param   p_offset_value The channel' offset value.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_channel_offset( cvt_V1724_data* p_data, UINT8 ch_index, UINT16 *p_offset_value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_channel_trigger( cvt_V1724_data* p_data, UINT8 ch_msk, UINT32 trigger_threshold, UINT32 threshold_samples);
*   \brief   Sets channels' trigger parameters.
*            
*            Sets the relevant trigger parameters for each channel specified with ch_msk.
*   \param   p_data Pointer to board data
*   \param   ch_msk The channel mask 
*   \param   trigger_threshold The value of the trigger threshold
*   \param   threshold_samples The hysteresis on threshold comparison 
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_channel_trigger( cvt_V1724_data* p_data, UINT8 ch_msk, UINT32 trigger_threshold, UINT32 threshold_samples);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_channel_trigger( cvt_V1724_data* p_data, UINT8 ch_index, UINT32 *p_trigger_threshold, UINT32 *p_threshold_samples);
*   \brief   Gets the specified channel' trigger parameters.
*            
*            Retrives the relevant trigger parameters for the specified channel.
*   \param   p_data Pointer to board data
*   \param   ch_index The channel index
*   \param   p_trigger_threshold The value of the trigger threshold
*   \param   p_threshold_samples The hysteresis on threshold comparison 
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_channel_trigger( cvt_V1724_data* p_data, UINT8 ch_index, UINT32 *p_trigger_threshold, UINT32 *p_threshold_samples);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_front_panel_IO( cvt_V1724_data* p_data, BOOL use_TTL, BOOL out_en, UINT8 dir_msk, CVT_V1724_FRONT_PANEL_IO_MODES mode);
*   \brief   Sets front panel's IO.
*            
*            Sets the relevant parameters for the front panel's IO.
*   \param   p_data Pointer to board data
*   \param   use_TTL If set, the external signals standard is TTL type, elsewhere NIM type is assumed
*   \param   out_en If setted enables the trigger output
*   \param   dir_msk Set direction mask
*   \param   mode Set the operational mode
*   \return  TRUE: Procedure successfully executed
*   \sa      CVT_V1724_FRONT_PANEL_IO_MODES
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_front_panel_IO( cvt_V1724_data* p_data, BOOL use_TTL, BOOL out_en, UINT8 dir_msk, CVT_V1724_FRONT_PANEL_IO_MODES mode);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_front_panel_IO( cvt_V1724_data* p_data, BOOL *p_use_TTL, BOOL *p_is_out_en, UINT8 *p_dir_msk, CVT_V1724_FRONT_PANEL_IO_MODES *p_mode);
*   \brief   Gets front panel's IO.
*            
*            Retrives the relevant parameters for the front panel's IO.
*   \param   p_data Pointer to board data
*   \param   p_use_TTL True if the external signals standard is TTL type
*   \param   p_is_out_en True if the trigger output is enabled
*   \param   p_dir_msk Gets the direction mask
*   \param   p_mode Gets the operational mode
*   \return  TRUE: Procedure successfully executed
*   \sa      CVT_V1724_FRONT_PANEL_IO_MODES
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_front_panel_IO( cvt_V1724_data* p_data, BOOL *p_use_TTL, BOOL *p_is_out_en, UINT8 *p_dir_msk, CVT_V1724_FRONT_PANEL_IO_MODES *p_mode);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_software_trigger( cvt_V1724_data* p_data);
*   \brief   Performs a software trigger.
*            
*            Sends a software trigger. Software triggers must be enabled
*   \param   p_data Pointer to board data
*   \return  TRUE: Procedure successfully executed
*   \sa      cvt_V1724_set_trigger_mode
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_software_trigger( cvt_V1724_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_channel_status( cvt_V1724_data* p_data, UINT8 ch_index, BOOL *p_is_dac_busy, BOOL *p_is_fifo_full, BOOL *p_is_fifo_empty, BOOL *p_is_block_remove_ok);
*   \brief   Gets information about board status.
*            
*   \param   p_data Pointer to board data.
*   \param   ch_index The index of the channel to test.
*   \param   p_is_dac_busy Returns the channel's DAC_BUSY flag status. 
*   \param   p_is_fifo_full Returns the channel's FIFO_FULL flag status. 
*   \param   p_is_fifo_empty Returns the channel's FIFO_EMPTY flag status. 
*   \param   p_is_block_remove_ok Returns the channel's BLOCK_REM_OK flag status. 
*   \return  TRUE: Procedure successfully executed.
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_channel_status( cvt_V1724_data* p_data, UINT8 ch_index, BOOL *p_is_dac_busy, BOOL *p_is_fifo_full, BOOL *p_is_fifo_almost_full, BOOL *p_is_block_remove_ok);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_system_info( cvt_V1724_data* p_data, UINT16 *p_firmware_rev, CVT_V1724_ROM_CONFIG *p_rom_config, BOOL *p_is_board_type_correct, BOOL *p_is_firmware_rev_correct);
*   \brief   Gets board's system information.
*            
*            Reads the firmware revision register and the serial number.
*   \param   p_data Pointer to board data
*   \param   p_firmware_rev The firmare release (MSB major release, LSB minor release).
*   \param   p_rom_config The ROM configuration.
*   \param   p_is_board_type_correct Return TRUE if the cvt_V1724_data::m_type matches the CVT_V1724_ROM_CONFIG::m_board_id type
*   \param   p_is_firmware_rev_correct Return TRUE if the CVT_V1724_FW_REV register value is greater or equal then minimum requested level for this tool's version \ref CVT_V1724_MIN_FIRMARE_REV
*   \return  TRUE: Procedure successfully executed
*   \sa      CVT_V1724_MIN_FIRMARE_REV
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_system_info( cvt_V1724_data* p_data, UINT16 *p_firmware_rev, CVT_V1724_ROM_CONFIG *p_rom_config, BOOL *p_is_board_type_correct, BOOL *p_is_firmware_rev_correct);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_channel_info( cvt_V1724_data* p_data, UINT8 ch_index, UINT16 *p_firmware_rev);
*   \brief   Gets board's system information.
*            
*            Reads the firmware revision register and the serial number.
*   \param   p_data Pointer to board data
*   \param   ch_index The index of the channel to test.
*   \param   p_firmware_rev The channel's firmare release (MSB major release, LSB minor release).
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_channel_info( cvt_V1724_data* p_data, UINT8 ch_index, UINT16 *p_firmware_rev);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_set_MCST_CBLT( cvt_V1724_data* p_data, UINT8 address, MCST_CBLT_board_pos pos);
*   \brief   Setups MCST/CBLT parameters for this board.
*            
*            Setups the relevant parameters for MCST/CBLT usage.
*   \param   p_data Pointer to board data.
*   \param   address The MCST/CBLT address.
*   \param   pos The board position into the MCST / CBLT chain: it must be a \ref MCST_CBLT_board_pos identifier
*   \return  TRUE: Procedure successfully executed
*   \sa      MCST_CBLT_board_pos
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_set_MCST_CBLT( cvt_V1724_data* p_data, UINT8 address, MCST_CBLT_board_pos pos);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_get_MCST_CBLT( cvt_V1724_data* p_data, UINT8 *p_address, MCST_CBLT_board_pos *p_pos);
*   \brief   Gets MCST/CBLT parameters from board.
*            
*            Retrives the relevant parameters for MCST/CBLT usage.
*   \param   p_data Pointer to board data.
*   \param   p_address The MCST/CBLT address.
*   \param   p_pos The board position into the MCST / CBLT chain: it must be a \ref MCST_CBLT_board_pos identifier
*   \return  TRUE: Procedure successfully executed
*   \sa      MCST_CBLT_board_pos
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_get_MCST_CBLT( cvt_V1724_data* p_data, UINT8 *p_address, MCST_CBLT_board_pos *p_pos);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_write_flash_page( cvt_V1724_data* p_data, const UINT8* page_buff, UINT32 page_index);
*   \brief   Writes a page into board's flash.
*            
*   \param   p_data Pointer to board data.
*   \param   page_buff The source page buffer: page_buff size must be \ref V1724_FLASH_PAGE_SIZE bytes
*   \param   page_index The page index (0 based index) to be written
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_write_flash_page( cvt_V1724_data* p_data, const UINT8* page_buff, UINT32 page_index);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_read_flash_page( cvt_V1724_data* p_data, UINT8* page_buff, UINT32 page_index);
*   \brief   Reads a page from board's flash.
*            
*   \param   p_data Pointer to board data.
*   \param   page_buff The target page buffer: page_buff size must be \ref V1724_FLASH_PAGE_SIZE and allocated by the caller
*   \param   page_index The page index (0 based index) to be read
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_read_flash_page( cvt_V1724_data* p_data, UINT8* page_buff, UINT32 page_index);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_erase_flash_page( cvt_V1724_data* p_data, UINT32 page_index);
*   \brief   Erases a board's flash page.
*            
*   \param   p_data Pointer to board data.
*   \param   page_index The page index (0 based index) to be erased
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_erase_flash_page( cvt_V1724_data* p_data, UINT32 page_index);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_fw_upgrade( cvt_V1724_data* p_data, const UINT8* data_buff, UINT32 data_size, CVT_V1724_FLASH_BANK flash_bank, BOOL (* call_back)(UINT32 written_bytes));
*   \brief   Performs a full flash upgrade onto specific bank (standard or backup).
*            
*   \param   p_data Pointer to board data.
*   \param   data_buff The source data buffer
*   \param   data_size The data_buff size (bytes)
*   \param   flash_bank The flash bank to upgrade: must be a \ref CVT_V1724_FLASH_BANK valid one
*   \param   call_back End user call back function, called for each new page transferred: may be NULL: you can return FALSE to abort procedure
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_fw_upgrade( cvt_V1724_data* p_data, const UINT8* data_buff, UINT32 data_size, CVT_V1724_FLASH_BANK flash_bank, BOOL (* call_back)(UINT32 written_bytes) );

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_V1724_pll_upgrade( cvt_V1724_data* p_data, const char* filename);
*   \brief   Loads PLL from file and stores into flash
*            
*   \param   p_data Pointer to board data.
*   \param   filename The source file
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_V1724_pll_upgrade( cvt_V1724_data* p_data, const char* filename);

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     M I S C E L L A N E O U S   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      const char* cvt_V1724_SW_rev( void);
*   \brief   Returns the SDK software release
*            
*   \return  const char*: The SDK revision string
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API const char* cvt_V1724_SW_rev( void);

#endif  // __CVT_V1724_DEF_H
