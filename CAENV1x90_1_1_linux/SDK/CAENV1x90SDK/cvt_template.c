////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file    cvt_board_commons.c
*   \brief   VME Board common features implementation
*   \author  NDA
*   \version 1.0
*   \date    03/2006
*            
*            VME boards common APIs: These APIs provide features common to every VME board.
*/
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
// File includes
////////////////////////////////////////////////////////////////////////////////////////////////
#include <memory.h>
#include <string.h>

#ifdef LINUX
	#include <unistd.h>
#endif

#include "cvt_board_commons.h"

////////////////////////////////////////////////////////////////////////////////////////////////
// File local defines
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// Static variables declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// Static methods declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 cvt_ror_bits( UINT8 data, int num_bits)
{
	while( num_bits--)
	{
		data= ( data& 0x01)? (data>> 1)|0x80: (data>> 1);
	}
	return data;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 cvt_swap_bits( UINT8 data)
{
	UINT8 tmp= 0x00;
	UINT8 msk_l, msk_r;
	for( msk_l= 0x80, msk_r= 0x01; msk_l; msk_l>>= 1, msk_r<<= 1)
	{
		tmp|= (data& msk_l)? msk_r: 0x00;
	}
	return tmp;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
void cvt_delay(int msec)
{
#ifdef LINUX
  usleep( msec* 1000); 
#else
  Sleep( msec);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Global visible variables declaration
////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
/*
        -----------------------------------------------------------------------------

        DllMain
        Entry point della libreria (inizializzare qui i dati globali)

        -----------------------------------------------------------------------------
*/
BOOL WINAPI DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
    static int m_num_instances= 0;

        switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
                {
					if( !m_num_instances)
					{
					}

					++m_num_instances;
                }
                break;
        case DLL_PROCESS_DETACH:
				--m_num_instances;
				break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
                break;
        }
        return TRUE;
}

#else   //Linux
/*
        -----------------------------------------------------------------------------

        _init
        Library entry point

        -----------------------------------------------------------------------------
*/
void _init( void )
{
}

/*
        -----------------------------------------------------------------------------

        _fini
        Library exit point

        -----------------------------------------------------------------------------
*/
void _fini( void )
{
}

#endif // WIN32

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     B O A R D S   H A N D L I N G
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_board_open( cvt_board_data* p_data, UINT16 base_address, long vme_handle, const cvt_reg_table *p_reg_table)
{
	memset( p_data, 0, sizeof( cvt_board_data));

	// init fields
	p_data->m_base_address= base_address;
	p_data->m_vme_handle= vme_handle;
	p_data->m_p_reg_table= p_reg_table;
	
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_board_close( cvt_board_data* p_data)
{
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     L E V E L   0   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_write( cvt_board_data* p_data, UINT16 address, const void* p_value, CVAddressModifier am, CVDataWidth data_size)
{
	CVErrorCodes err_code;
	if( ( err_code= CAENVME_WriteCycle( p_data->m_vme_handle, (((UINT32)p_data->m_base_address)<< 16)| address, (void*)p_value, am, data_size))!= cvSuccess)
	{
		TRACE( "CAENVME_WriteCycle: ");
		TRACE( CAENVME_DecodeError( err_code));
		TRACE( "\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_read( cvt_board_data* p_data, UINT16 address, void* p_value, CVAddressModifier am, CVDataWidth data_size)
{
	CVErrorCodes err_code;
	if( ( err_code= CAENVME_ReadCycle( p_data->m_vme_handle, (((UINT32)p_data->m_base_address)<< 16)| address, (void*)p_value, am, data_size))!= cvSuccess)
	{
		TRACE( "CAENVME_ReadCycle: ");
		TRACE( CAENVME_DecodeError( err_code));
		TRACE( "\n");
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_set_bitmask( cvt_board_data* p_data, UINT16 address, void *p_value, CVAddressModifier am, CVDataWidth data_size)
{
	switch( data_size) 
	{
	case cvD8:
		{
			UINT8 reg_value= 0;
			if( !cvt_read( p_data, address, &reg_value, am, data_size))
				return FALSE;
			reg_value|= *(UINT8*)p_value;
			if( !cvt_write( p_data, address, &reg_value, am, data_size))
				return FALSE;
		}
		break;
	case cvD16:
	case cvD16_swapped:
		{
			UINT16 reg_value= 0;
			if( !cvt_read( p_data, address, &reg_value, am, data_size))
				return FALSE;
			reg_value|= *(UINT16*)p_value;
			if( !cvt_write( p_data, address, &reg_value, am, data_size))
				return FALSE;
		}
		break;
	case cvD32:
	case cvD32_swapped:
		{
			UINT32 reg_value= 0;
			if( !cvt_read( p_data, address, &reg_value, am, data_size))
				return FALSE;
			reg_value|= *(UINT32*)p_value;
			if( !cvt_write( p_data, address, &reg_value, am, data_size))
				return FALSE;
		}
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_clear_bitmask( cvt_board_data* p_data, UINT16 address, void* p_value, CVAddressModifier am, CVDataWidth data_size)
{
	switch( data_size) 
	{
	case cvD8:
		{
			UINT8 reg_value= 0;
			if( !cvt_read( p_data, address, &reg_value, am, data_size))
				return FALSE;
			reg_value&= ~*(UINT8*)p_value;
			if( !cvt_write( p_data, address, &reg_value, am, data_size))
				return FALSE;
		}
		break;
	case cvD16:
	case cvD16_swapped:
		{
			UINT16 reg_value= 0;
			if( !cvt_read( p_data, address, &reg_value, am, data_size))
				return FALSE;
			reg_value&= ~*(UINT16*)p_value;
			if( !cvt_write( p_data, address, &reg_value, am, data_size))
				return FALSE;
		}
		break;
	case cvD32:
	case cvD32_swapped:
		{
			UINT32 reg_value= 0;
			if( !cvt_read( p_data, address, &reg_value, am, data_size))
				return FALSE;
			reg_value&= ~*(UINT32*)p_value;
			if( !cvt_write( p_data, address, &reg_value, am, data_size))
				return FALSE;
		}
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_FIFO_BLT_read( cvt_board_data* p_data, UINT16 address, void* p_buffer, UINT32 buffer_size, UINT32 *p_read_bytes, CVAddressModifier am, CVDataWidth data_size, BOOL *p_is_berr)
{
	// Avoid CAENVMELib Linux Driver limits to 16 MB
	const UINT32 MAX_BLT_SIZE= 8*1024*1024;
	int read_bytes= 0;
	UINT32 bytes_to_read= 0;
	CVErrorCodes err_code;

	*p_read_bytes= 0;
	while( *p_read_bytes< buffer_size)
	{
		bytes_to_read= (( buffer_size- *p_read_bytes)>  MAX_BLT_SIZE)? MAX_BLT_SIZE: buffer_size- *p_read_bytes;
		*p_is_berr= FALSE;
		switch( err_code= CAENVME_FIFOBLTReadCycle( p_data->m_vme_handle, (((UINT32)p_data->m_base_address)<< 16)| address, (void*)((UINT8*)p_buffer+ *p_read_bytes), bytes_to_read, am, data_size, &read_bytes))
		{
		case cvBusError:
			*p_is_berr= TRUE;
		case cvSuccess:
			break;
		default:
			TRACE( "CAENVME_FIFOBLTReadCycle: ");
			TRACE( CAENVME_DecodeError( err_code));
			TRACE( "\n");
			return FALSE;
		}
		(*p_read_bytes)+= read_bytes;
		if( bytes_to_read!= read_bytes)
			break;

	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_write_reg( cvt_board_data* p_data, UINT16 reg_index, const void* p_value)
{
	return cvt_write( p_data, p_data->m_p_reg_table[ reg_index].m_address, p_value, p_data->m_p_reg_table[ reg_index].m_am, p_data->m_p_reg_table[ reg_index].m_data_size);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_read_reg( cvt_board_data* p_data, UINT16 reg_index, void* p_value)
{
	return cvt_read( p_data, p_data->m_p_reg_table[ reg_index].m_address, p_value, p_data->m_p_reg_table[ reg_index].m_am, p_data->m_p_reg_table[ reg_index].m_data_size);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_set_bitmask_reg( cvt_board_data* p_data, UINT16 reg_index, void *p_value)
{
	return cvt_set_bitmask( p_data, p_data->m_p_reg_table[ reg_index].m_address, p_value, p_data->m_p_reg_table[ reg_index].m_am, p_data->m_p_reg_table[ reg_index].m_data_size);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_clear_bitmask_reg( cvt_board_data* p_data, UINT16 reg_index, void* p_value)
{
	return cvt_clear_bitmask( p_data, p_data->m_p_reg_table[ reg_index].m_address, p_value, p_data->m_p_reg_table[ reg_index].m_am, p_data->m_p_reg_table[ reg_index].m_data_size);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_FIFO_BLT_read_reg( cvt_board_data* p_data, UINT16 reg_index, void* p_buffer, UINT32 buffer_size, UINT32 *p_read_bytes, BOOL *p_is_berr)
{
	return cvt_FIFO_BLT_read( p_data, p_data->m_p_reg_table[ reg_index].m_address, p_buffer, buffer_size, p_read_bytes, p_data->m_p_reg_table[ reg_index].m_am, p_data->m_p_reg_table[ reg_index].m_data_size, p_is_berr);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//     G L O B A L   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL cvt_set_MCST_CBLT( UINT8 address, cvt_board_data** board_array, UINT16 board_array_len)
{
	MCST_CBLT_board_pos pos= MCST_CBLT_board_pos_last;
	while( board_array_len--)
	{
		if( !board_array[ board_array_len]->set_MCST_CBLT)
		{
			TRACE1("cvt_set_MCST_CBLT: no set_MCST_CBLT method setted for board 0x%8p\n", board_array[ board_array_len]);
			return FALSE;
		}
		if( !(board_array[ board_array_len]->set_MCST_CBLT)( board_array[ board_array_len], address, pos))
		{
			TRACE1("cvt_set_MCST_CBLT: set_MCST_CBLT method failure for board 0x%8p\n", board_array[ board_array_len]);
			return FALSE;
		}
		pos= ( board_array_len- 1)? MCST_CBLT_board_pos_mid: MCST_CBLT_board_pos_first;
	}
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//
//     M I S C E L L A N E O U S   A P I s
//
////////////////////////////////////////////////////////////////////////////////////////////////
