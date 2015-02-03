////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file    cvt_board_commons.h
*   \brief   VME Board common features definitions
*   \author  NDA
*   \version 1.0
*   \date    03/2006
*            
*            VME boards common APIs: typically level 0 APIs
*            These APIs provide features common to every VME board.
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CVT_BOARD_COMMONS_H
#define __CVT_BOARD_COMMONS_H

////////////////////////////////////////////////////////////////////////////////////////////////
// File includes
////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#include "cvt_common_defs.h"
#include "CAENVMElib.h"
#include "CAENVMEoslib.h"
#include "CAENVMEtypes.h"

////////////////////////////////////////////////////////////////////////////////////////////////
// Global defines
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \struct  cvt_reg_table
*   \brief   Board register table entry
*            
*            This is a struct holding boards specif register table entries
*            Each board must declare a register table in order to get register address, address modifier and data size 
*            for vme operation
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	UINT16	m_address;			//!< Register address
	UINT16	m_am;				//!< Register address modifier
	UINT16	m_data_size;		//!< Register data size
} cvt_reg_table;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum    MCST_CBLT_board_pos
*   \brief   Board position in MCST/CBLT chain
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MCST_CBLT_board_pos_first= 0,		//!< First board in MCST CBLT chain
	MCST_CBLT_board_pos_mid,			//!< Middle board in MCST CBLT chain
	MCST_CBLT_board_pos_last,			//!< Last board in MCST CBLT chain
	MCST_CBLT_board_disabled,			//!< Board is inactive in MCST CBLT chain
} MCST_CBLT_board_pos;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \struct  cvt_board_data
*   \brief   Data common to every board
*            
*            This is the basic structure for every board specific data. 
*            This struct MUST be the first data of any other specific board data.
*   \todo    Add a board specific semaphore foreach API level [0..2]
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	UINT16	m_base_address;						//!< Base address
	long	m_vme_handle;						//!< VME handle
	const cvt_reg_table* m_p_reg_table;			//!< Pointer to board specif register table
	BOOL (*set_MCST_CBLT)( void* /*p_data*/, UINT8 /*address*/, MCST_CBLT_board_pos /*MCST_CBLT position*/ );		//!< Pointer to board specif set_MCST_CBLT method
} cvt_board_data;

////////////////////////////////////////////////////////////////////////////////////////////////
// Global variables declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// Global methods declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      UINT8 cvt_ror_bits( UINT8 data, int num_bits)
*   \brief   Perfoms a num_bits bitwise right rotation of data byte 
*            
*   \param   data The source byte to rotate
*   \param   num_bits The number of bits to rotate
*   \return  Converted data
*/
////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 cvt_ror_bits( UINT8 data, int num_bits);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      UINT8 cvt_swap_bits( UINT8 data)
*   \brief   Swaps the bits of the source byte
*            
*   \param   data The source byte to swap
*   \return  Converted data
*/
////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 cvt_swap_bits( UINT8 data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      void cvt_delay(int msec)
*   \brief   Waits for specified time
*            
*   \param   msec The time delay to wait (msec)
*/
////////////////////////////////////////////////////////////////////////////////////////////////
void cvt_delay(int msec);

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     B O A R D S   H A N D L I N G
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_board_open( cvt_board_data* p_data, UINT16 base_address, long vme_handle, const cvt_reg_table* p_reg_table);
*   \brief   Basic board open
*            
*            Provides basic handling for board opening, common to all the boards.
*   \param   p_data Pointer to board data
*   \param   base_address The board base address (MSW)
*   \param   vme_handle The VME handle
*   \param   p_reg_table The board specific register table pointer
*   \return  TRUE: board successfully opened
*   \note    This API if typically called by derived boards during open procedure.
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_board_open( cvt_board_data* p_data, UINT16 base_address, long vme_handle, const cvt_reg_table* p_reg_table);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_board_close( cvt_board_data* p_data);
*   \brief   Basic board close
*            
*            Provides basic handling for board closing, common to all the boards.
*   \param   p_data Pointer to board data
*   \return  TRUE: board successfully closed
*   \note    This API if typically called by derived boards during close procedure.
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_board_close( cvt_board_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     L E V E L   0   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_write( cvt_board_data* p_data, UINT16 address, const void* p_value, CVAddressModifier am, CVDataWidth data_size);
*   \brief   Writes a register onto VME board
*            
*            Writes a value at relative address, with specific address modifier and data size
*   \param   p_data Pointer to board data
*   \param   address  The register's board relative address
*   \param   p_value The pointer to the value to write
*   \param   am The address modifier
*   \param   data_size The data size
*   \return  TRUE  write procedure ok
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_write( cvt_board_data* p_data, UINT16 address, const void* p_value, CVAddressModifier am, CVDataWidth data_size);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_read( cvt_board_data* p_data, UINT16 address, void* p_value, CVAddressModifier am, CVDataWidth data_size);
*   \brief   Reads a register from VME board
*            
*            Reads a value at relative address, with specific address modifier and data size
*   \param   p_data Pointer to board data
*   \param   address  The register's board relative address
*   \param   p_value The pointer to the value read
*   \param   am The address modifier
*   \param   data_size The data size
*   \return  TRUE  read procedure ok
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_read( cvt_board_data* p_data, UINT16 address, void* p_value, CVAddressModifier am, CVDataWidth data_size);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_set_bitmask( cvt_board_data* p_data, UINT16 address, void *p_value, CVAddressModifier am, CVDataWidth data_size);
*   \brief   Sets bitmask onto VME board register
*            
*            Reads the actual register value, ORs it with the bitmask and write back to the register.
*   \param   p_data Pointer to board data
*   \param   address  The register's board relative address
*   \param   p_value The pointer to the mask to set
*   \param   am The address modifier
*   \param   data_size The data size
*   \return  TRUE  write procedure ok
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_set_bitmask( cvt_board_data* p_data, UINT16 address, void *p_value, CVAddressModifier am, CVDataWidth data_size);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_clear_bitmask( cvt_board_data* p_data, UINT16 address, void *p_value, CVAddressModifier am, CVDataWidth data_size);
*   \brief   Clears bitmask onto VME board register
*            
*            Reads the actual register value, ANDs it with the complementary bitmask and write back to the register.
*   \param   p_data Pointer to board data
*   \param   address  The register's board relative address
*   \param   p_value The pointer to the mask to clear
*   \param   am The address modifier
*   \param   data_size The data size
*   \return  TRUE  write procedure ok
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_clear_bitmask( cvt_board_data* p_data, UINT16 address, void *p_value, CVAddressModifier am, CVDataWidth data_size);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_FIFO_BLT_read( cvt_board_data* p_data, UINT16 address, void* p_buffer, UINT32 buffer_size, UINT32 *p_read_bytes, CVAddressModifier am, CVDataWidth data_size, BOOL *p_is_berr);
*   \brief   Performs a FIFO BLT read from VME board
*            
*            Reads a buffer of value at relative address, with specific address modifier and data size in FIFO BLT mode
*   \param   p_data Pointer to board data
*   \param   address  The register's board relative address
*   \param   p_buffer The pointer to target buffer
*   \param   buffer_size The target buffer size (bytes)
*   \param   p_read_bytes The number of bytes really read
*   \param   am The address modifier
*   \param   data_size The data size
*   \param   p_is_berr Returns TRUE if the Bus Error bit was setted
*   \return  TRUE  read procedure ok
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_FIFO_BLT_read( cvt_board_data* p_data, UINT16 address, void* p_buffer, UINT32 buffer_size, UINT32 *p_read_bytes, CVAddressModifier am, CVDataWidth data_size, BOOL *p_is_berr);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_write_reg( cvt_board_data* p_data, UINT16 reg_index, const void* p_value);
*   \brief   Writes a register onto VME board
*            
*            Writes a value to a register specified by register index. 
*            Register address, address modifier and data size will setted according to the specific board register table
*   \param   p_data Pointer to board data
*   \param   reg_index The register's board index : it must be a valid CVT_VXXXX_REG_INDEX
*   \param   p_value The pointer to the value to write
*   \return  TRUE  write procedure ok
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_write_reg( cvt_board_data* p_data, UINT16 reg_index, const void* p_value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_read_reg( cvt_board_data* p_data, UINT16 reg_index, void* p_value);
*   \brief   Reads a register from VME board
*            
*            Reads a value a register specified by register index. 
*            Register address, address modifier and data size will setted according to the specific board register table
*   \param   p_data Pointer to board data
*   \param   reg_index The register's board index : it must be a valid CVT_VXXXX_REG_INDEX
*   \param   p_value The pointer to the value read
*   \return  TRUE  read procedure ok
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_read_reg( cvt_board_data* p_data, UINT16 reg_index, void* p_value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_set_bitmask_reg( cvt_board_data* p_data, UINT16 reg_index, void *p_value);
*   \brief   Sets bitmask onto VME board register
*            
*            Reads the actual register value, ORs it with the bitmask and write back to the register.
*            Register address, address modifier and data size will setted according to the specific board register table
*   \param   reg_index The register's board index : it must be a valid CVT_VXXXX_REG_INDEX
*   \param   p_data Pointer to board data
*   \param   p_value The pointer to the mask to set
*   \return  TRUE  write procedure ok
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_set_bitmask_reg( cvt_board_data* p_data, UINT16 reg_index, void *p_value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_clear_bitmask_reg( cvt_board_data* p_data, UINT16 reg_index, void *p_value);
*   \brief   Clears bitmask onto VME board register
*            
*            Reads the actual register value, ANDs it with the complementary bitmask and write back to the register.
*            Register address, address modifier and data size will setted according to the specific board register table
*   \param   p_data Pointer to board data
*   \param   reg_index The register's board index : it must be a valid CVT_VXXXX_REG_INDEX
*   \param   p_value The pointer to the mask to clear
*   \return  TRUE  write procedure ok
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_clear_bitmask_reg( cvt_board_data* p_data, UINT16 reg_index, void *p_value);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_FIFO_BLT_read_reg( cvt_board_data* p_data, UINT16 reg_index, void* p_buffer, UINT32 buffer_size, UINT32 *p_read_bytes, BOOL *p_is_berr);
*   \brief   Performs a FIFO BLT read from VME board
*            
*            Reads a buffer of register values specified by register index.
*            Register address, address modifier and data size will setted according to the specific board register table
*   \param   p_data Pointer to board data
*   \param   reg_index The register's board index : it must be a valid CVT_VXXXX_REG_INDEX
*   \param   p_buffer The pointer to target buffer
*   \param   buffer_size The target buffer size (bytes)
*   \param   p_read_bytes The number of bytes really read
*   \param   p_is_berr Returns TRUE if the Bus Error bit was setted
*   \return  TRUE  read procedure ok
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_FIFO_BLT_read_reg( cvt_board_data* p_data, UINT16 reg_index, void* p_buffer, UINT32 buffer_size, UINT32 *p_read_bytes, BOOL *p_is_berr);

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     G L O B A L   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL cvt_set_MCST_CBLT( UINT8 address, cvt_board_data** board_array, UINT16 board_array_len);
*   \brief   Setups MCST/CBLT parameters for a group of boards.
*            
*            Setups the relevant parameters for MCST/CBLT usage for a collection of boards.
*   \param   address The MCST/CBLT address common to each board of the group
*   \param   board_array The collection of boards to setup. The first board in the chain is board_array[0], and the last one is board_array[ board_array_len-1]
*   \param   board_array_len The number of boards into board_array buffer.
*   \return  TRUE: Procedure successfully executed
*/
////////////////////////////////////////////////////////////////////////////////////////////////
CVT_DLL_API BOOL cvt_set_MCST_CBLT( UINT8 address, cvt_board_data** board_array, UINT16 board_array_len);

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     M I S C E L L A N E O U S   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

#endif			// __CVT_BOARD_COMMONS_H
