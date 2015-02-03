/////////////////////////////////////////////////////////////////////////////
// Name:        main.c
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     10/04/07
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////
// File includes
////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#if defined (LINUX)
	#include <memory.h>
	#include <ctype.h>
#endif
#include "common_defs.h"
#include "cvt_board_commons.h"
#include "cvt_common_defs.h"
#include "cvt_V1190.h"
#include "user_settings.h"
#include "console.h"


////////////////////////////////////////////
// File local defines
////////////////////////////////////////////
#define GLB_HDR_STR		"GLB_HDR   - EVT COUNT   : %08x GEO      : %08x \n"
#define GLB_TRL_STR		"GLB_TRL   - STATUS      : %08x WCOUNT   : %08x GEO     : %08x \n"
#define TDC_HDR_STR		" TDC_HDR  - TDC         : %08x EVT ID   : %08x BUNCH ID: %08x \n"
#define TDC_MSR_STR		"  TDC_MSR - TRAILING    : %08x CH       : %08x MEASURE : %08x \n"
#define TDC_ERR_STR		"  TDC_ERR - TDC         : %08x ERR FLAGS: %08x \n"
#define TDC_TRL_STR		" TDC_TRL  - TDC         : %08x EVT ID   : %08x WCOUNT  : %08x \n"
#define TDC_TRG_STR		"  TDC_TRG - TRG TIME TAG: %08x \n"
#define FILLER_STR		"  FILLER  - \n"
#define UNKNOWN_STR		"\n??? UNKNOWN TAG ??? -          READ WORD: %08x \n\n"

////////////////////////////////////////////
// File local variables declaration
////////////////////////////////////////////

////////////////////////////////////////////
// Global visible variables declaration
////////////////////////////////////////////

////////////////////////////////////////////
// File local methods declaration
////////////////////////////////////////////



/**************************************************
**************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      int main(int argc, char **argv) 
*   \brief   CAENVMETool demo usage for the V1190 board
*            
*            Setups a V1190 board, reads some events and stores into output file
*   \param   argc number of command line arguments
*   \param   *argv[] command line arguments' list 
*   \return  = 0 procedure completed correctly: < 0 some error occurred
*/
////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) 

{
	int ret_val= 0;									// procedure exit value
	cvt_V1190_data board_data;						// board data
	user_setting_data user_setting;					// user settings
	FILE* parsed_out_file= NULL;					// parsed output file
	FILE* raw_out_file= NULL;						// raw output file
	UINT8 *data_buff= NULL;							// read data buffer
	UINT32 data_size;
	int32_t vme_handle= -1;							// The CAENVMELib handle
	long read_events= 0;
	const int DATA_BUFF_SIZE= 1024*1024;			// The data buffer size

	/////////////////////////////////////////
	// Demo application specific
	/////////////////////////////////////////

	memset( &user_setting, 0, sizeof( user_setting));
	memset( &board_data, 0, sizeof( board_data));

	//
	// init the console module
	con_init( );

	//
	// print header
	con_printf( "\n");
	con_printf( "-------------------------------------------------------\n");
	con_printf( "-           C A E N    V 1 1 9 0    D E M O           -\n");
	con_printf( "-                                                     -\n");
	con_printf( "-   www.caen.it                             rev.01.00 -\n");
	con_printf( "-------------------------------------------------------\n");
	con_printf( "\n");

	//
	// init user setting module
	if( !user_settings_open( &user_setting))
	{
		ret_val= -1;
		goto exit_point;
	}

	//
	// input parameter check
	if( !user_settings_parse_input_param( &user_setting, argc, (char**)argv))
	{
		ret_val= -2;
		goto exit_point;
	}
	//
	// Vme handle initialization
	while( TRUE)
	{
		if( CAENVME_Init( cvV1718, 0, 0, &vme_handle)== cvSuccess)
		{
			user_setting.m_board_type= cvV1718;
			user_setting.m_board_number= 0;
			user_setting.m_link_number= 0;
			break;
		}
		if( CAENVME_Init( cvV2718, 0, 0, &vme_handle)== cvSuccess)
		{
			user_setting.m_board_type= cvV2718;
			user_setting.m_board_number= 0;
			user_setting.m_link_number= 0;
			break;
		}
		TRACE("VME INIT ERROR :  press 'Q' to quit or any other key to retry\n");
		if( toupper( con_getch()) == 'Q')
		{
			ret_val= -3;
			goto exit_point;
		}
	}

	/////////////////////////////////////////
	// Library specific
	/////////////////////////////////////////

	//
	// init V1190 board data
	TRACE(  " Initializing V1190 board data ... ");
	if( !cvt_V1190_open( &board_data, user_setting.m_base_address, vme_handle, user_setting.m_V1190_type))
	{	
		TRACE( "\nError executing cvt_V1190_open \n");
		ret_val= -4;
		goto exit_point;
	}
	TRACE(  " Ok \n");

	//
	// Get system informations
	{
		UINT32 tdc_id_buff[ MAX_V1190_TDC_COUNT];
		UINT16 firmware_rev;
		UINT16 micro_firmware_rev;
		UINT16 serial_number;
		int i; 

		TRACE(  " Getting system informations ... ");
		if( !cvt_V1190_get_system_info( &board_data, &firmware_rev, tdc_id_buff, &micro_firmware_rev, &serial_number))
		{
			TRACE( "\nError executing cvt_V1190_get_system_info \n");
			ret_val= -5;
			goto exit_point;
		}
		TRACE(  " Ok \n\n");

		// Show system infos
		TRACE1( "   Firmware Rev.       : %04x\n", firmware_rev);
		TRACE1( "   Micro Firmware Rev. : %04x\n", micro_firmware_rev);
		TRACE1( "   Serial Number       : %04x\n", serial_number);
		for( i= 0; i< user_setting.m_tdc_count; i++)
		{
			TRACE2( "   TDC %d               : %08x\n", i, tdc_id_buff[ i]);
		}
	}
	//
	// data clear
	TRACE(  " Sending data clear ... ");
	if( !cvt_V1190_data_clear( &board_data))	
	{	
		TRACE( "\nError executing cvt_V1190_data_clear \n");
		ret_val= -5;
		goto exit_point;
	}
	TRACE(  " Ok \n");

	//
	// Acquisition mode
	TRACE(  " Setting acquisition mode ... ");
	switch( user_setting.m_acquisition_mode.m_mode)
	{
	case AM_CONTINUOUS:
		if( !cvt_V1190_set_continuous_acquisition_mode( &board_data, 
														user_setting.m_acquisition_mode.m_params.m_continuos.m_edge_detection,
														user_setting.m_acquisition_mode.m_params.m_continuos.m_res_width,
														&user_setting.m_acquisition_mode.m_params.m_continuos.m_enable_msk[0]))
		{	
			TRACE( "Error executing cvt_V1190_set_continuous_acquisition_mode \n");
			ret_val= -5;
			goto exit_point;
		}
		break;
	case AM_TRIGGER_MATCH:
		if( !cvt_V1190_set_trigger_matching_acquisition_mode(	&board_data, 
																user_setting.m_acquisition_mode.m_params.m_trigger_matching.m_window_width,
																user_setting.m_acquisition_mode.m_params.m_trigger_matching.m_window_offset,
																user_setting.m_acquisition_mode.m_params.m_trigger_matching.m_extra_search_margin,
																user_setting.m_acquisition_mode.m_params.m_trigger_matching.m_reject_margin,
																user_setting.m_acquisition_mode.m_params.m_trigger_matching.m_edge_detection,
																user_setting.m_acquisition_mode.m_params.m_trigger_matching.m_res_width,
																&user_setting.m_acquisition_mode.m_params.m_trigger_matching.m_enable_msk[0],
																user_setting.m_acquisition_mode.m_params.m_trigger_matching.m_header_trailer_enable,
																user_setting.m_acquisition_mode.m_params.m_trigger_matching.m_empty_event_enable,
																user_setting.m_acquisition_mode.m_params.m_trigger_matching.m_trigger_time_tag_enable))
		{	
			TRACE( "Error executing cvt_V1190_set_trigger_matching_acquisition_mode \n");
			ret_val= -5;
			goto exit_point;
		}
		break;
	case AM_NONE:
		break;
	}
	TRACE(  " Ok\n");

	//
	// readout mode
	TRACE(  " Setting readout mode ...");
	if( !cvt_V1190_set_readout_mode( &board_data, TRUE, TRUE, 1))
	{	
		TRACE( "Error executing cvt_V1190_set_readout_mode \n");
		ret_val= -5;
		goto exit_point;
	}
	TRACE(  " Ok\n");

	// Allocate buffer storage
	data_buff= malloc( DATA_BUFF_SIZE);
	if( data_buff== NULL)
	{
		// Insufficient memory
		TRACE1( "Error allocating events' buffer (%li bytes)", DATA_BUFF_SIZE);
		ret_val= -5;
		goto exit_point;
	}

	// Create output files
	if( ( parsed_out_file= fopen( user_setting.m_parsed_output_filename, "wt"))== NULL)
	{
		TRACE1( "Error creating parsed output file '%s'", user_setting.m_parsed_output_filename);
		ret_val= -5;
		goto exit_point;
	}
	if( ( raw_out_file= fopen( user_setting.m_raw_output_filename, "w+b"))== NULL)
	{
		TRACE1( "Error creating raw output file '%s' \n", user_setting.m_raw_output_filename);
		ret_val= -5;
		goto exit_point;
	}

	//
	// Start acquisition 
	TRACE(  " Getting events: hit any key to abort ...\n");
	TRACE(  "\n");

	while((( read_events< user_setting.m_num_events)|| (user_setting.m_num_events<= 0))&&
			!con_kbhit())
	{
		static long last_read_bytes= 0;
		static long read_bytes= 0;
		data_size= DATA_BUFF_SIZE;
		//
		// Read from MEB .....
		if( !cvt_V1190_read_MEB( &board_data, data_buff, &data_size))
		{
			TRACE( " \nError executing cvt_V1190_read_MEB \n");
			ret_val= -5;
			goto exit_point;
		}
		if( !data_size)
			continue;
		//
		// .... and store raw data into file
		if( fwrite( data_buff, 1, data_size, raw_out_file)!= data_size)
		{
			TRACE( " \nError writing raw data file \n");
			ret_val= -5;
			goto exit_point;
		}
		read_bytes+= data_size;
		if( ( read_bytes>> 10)!= ( last_read_bytes>> 10))
		{
			// 
			// Give user a feedback every 1KB data
			TRACE( ".");
		}
		last_read_bytes= read_bytes;
	}
	TRACE(  "\n Done \n");
	TRACE(  " Parsing events and writing to output file ... ");

	//
	// Post process data : parse raw data and store events in clear text
	if( fflush( raw_out_file))
	{
		TRACE1( "\nError flushing raw output file '%s' \n", user_setting.m_raw_output_filename);
		ret_val= -5;
		goto exit_point;
	}
	if( fseek( raw_out_file, 0, SEEK_SET))
	{
		TRACE1( "\nError flushing raw output file '%s' \n", user_setting.m_raw_output_filename);
		ret_val= -5;
		goto exit_point;
	}

	while( ( data_size= ( UINT32)fread( data_buff, 4, DATA_BUFF_SIZE>> 2, raw_out_file)))
	{
		UINT32 *tmp_buff= (UINT32*)data_buff;
		char line[ 400];
		size_t str_len;

		while( data_size-- > 0)
		{
			UINT32 data= *(tmp_buff++);
			*line= '\0';
			switch( data& CVT_V1190_DATA_TYPE_MSK)
			{
			case CVT_V1190_GLOBAL_HEADER:
				{
					// Global header
					UINT32 event_count= CVT_V1190_GET_GLB_HDR_EVENT_COUNT( data);
					UINT32 geo= CVT_V1190_GET_GLB_HDR_GEO( data);

					sprintf( line, GLB_HDR_STR, event_count, geo);
				}
				break;
			case CVT_V1190_GLOBAL_TRAILER:
				{
					// Global trailer
					UINT32 status= CVT_V1190_GET_GLB_TRL_STATUS( data);
					UINT32 wcount= CVT_V1190_GET_GLB_TRL_WCOUNT( data);
					UINT32 geo= CVT_V1190_GET_GLB_TRL_GEO( data);

					sprintf( line, GLB_TRL_STR, status, wcount, geo);
				}
				break;
			case CVT_V1190_TDC_HEADER:
				{
					// TDC header
					UINT32 tdc= CVT_V1190_GET_TDC_HDR_TDC( data);
					UINT32 event_id= CVT_V1190_GET_TDC_HDR_EVENT_ID( data);
					UINT32 bunch_id= CVT_V1190_GET_TDC_HDR_BUNCH_ID( data);

					sprintf( line, TDC_HDR_STR, tdc, event_id, bunch_id);
				}
				break;
			case CVT_V1190_TDC_MEASURE:
				{
					// TDC measure
					UINT32 trailing= CVT_V1190_GET_TDC_MSR_TRAILING( data);
					UINT32 channel= CVT_V1190_GET_TDC_MSR_CHANNEL( data);
					UINT32 measure= CVT_V1190_GET_TDC_HDR_MEASURE( data);
					//fix July 2013
					if (user_setting.m_V1190_type ==  CVT_V1190_TYPE_A || user_setting.m_V1190_type == CVT_V1190_TYPE_B) {
						channel= CVT_V1190_GET_TDC_MSR_CHANNEL( data);
						measure= CVT_V1190_GET_TDC_HDR_MEASURE( data);
					}
					else {
						channel= CVT_V1290_GET_TDC_MSR_CHANNEL( data);
						measure= CVT_V1290_GET_TDC_HDR_MEASURE( data);
					}

					sprintf( line, TDC_MSR_STR, trailing, channel, measure);
				}
				break;
			case CVT_V1190_TDC_ERROR:
				{
					UINT32 tdc= CVT_V1190_GET_TDC_ERR_TDC( data);
					UINT32 err_flags= CVT_V1190_GET_TDC_ERR_ERR_FLAGS( data);

					sprintf( line, TDC_ERR_STR, tdc, err_flags);
				}
				break;
			case CVT_V1190_TDC_TRAILER:
				{
					UINT32 tdc= CVT_V1190_GET_TDC_TRL_TDC( data);
					UINT32 event_id= CVT_V1190_GET_TDC_TRL_EVENT_ID( data);
					UINT32 wcount= CVT_V1190_GET_TDC_TRL_WCOUNT( data);

					sprintf( line, TDC_TRL_STR, tdc, event_id, wcount);
				}
				break;
			case CVT_V1190_GLOBAL_TRIGGER_TIME:
				{
					UINT32 trg_time_tag= CVT_V1190_GET_GLB_TRG_TIME_TAG( data);

					sprintf( line, TDC_TRG_STR, trg_time_tag);
				}
				break;
			case CVT_V1190_FILLER:
				{
					sprintf( line, FILLER_STR);
				}
				break;
			default:
				{
					sprintf( line, UNKNOWN_STR, data);
				}
				break;
			}
			if( (str_len= strlen( line))> 0)
			{
				if( fwrite( line, 1, str_len, parsed_out_file)!= str_len)
				{
					// error writing file
					TRACE1( "\nError writing parsed output file '%s' \n", user_setting.m_parsed_output_filename);
					ret_val= -5;
					goto exit_point;
				}
			}
		}
	}	
	TRACE(  " Ok\n");

exit_point:	
	/////////////////////////////////////////
	// Library specific
	/////////////////////////////////////////
	
	//
	// Release board resources
	if( !cvt_V1190_close( &board_data))
	{	
		TRACE( "\nError executing cvt_V1190_close\n");
	}

	/////////////////////////////////////////
	// Demo application specific
	/////////////////////////////////////////

	if( raw_out_file!= NULL)
	{
		fclose( raw_out_file);
	}
	if( parsed_out_file!= NULL)
	{
		fclose( parsed_out_file);
	}
	if( data_buff!= NULL)
	{
		free( data_buff);
	}

	// close modules
	user_settings_close( &user_setting);

	TRACE( "Hit a key to exit ...");
	con_getch();
	//
	// close the console module
	con_end( );

	return ret_val;
}

