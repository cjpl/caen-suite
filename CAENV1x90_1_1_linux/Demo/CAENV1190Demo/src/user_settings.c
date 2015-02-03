/////////////////////////////////////////////////////////////////////////////
// Name:        user_settings.c
// Purpose:     user setting loading and storing
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
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "common_defs.h"
#include "user_settings.h"

////////////////////////////////////////////
// File local defines
////////////////////////////////////////////
#define DEF_RAW_OUTPUT_FILENAME				"raw_values.dat"						/*!< Raw board values default filename */
#define DEF_PARSED_OUTPUT_FILENAME			"parsed_values.dat"						/*!< Parsed board values default filename */

#define MAX_FILENAME_LENGHT					255										/*!< Maximum filenam length */

#define DEF_NUM_EVENTS						-1										/*!< Default number of events */
#define DEF_BASE_ADDRESS					0x3210									/*!< Default boards' base address */
#define DEF_BOARD_TYPE_STR					"V1190A"								/*!< Default V1190's type string */
#define DEF_V1190_TYPE						CVT_V1190_TYPE_A						/*!< Default V1190's type */
#define DEF_TDC_COUNT						CVT_V1190_NUM_TDC_A						/*!< Default V1190 number of TDCs */
#define DEF_ACQUISITION_MODE				AM_TRIGGER_MATCH						/*!< Default acquisition mode */
#define DEF_ACQUISITION_MODE_PARAMS			"1,1,0,-1,-1,-1,-1,1,0"					/*!< Default acquisition mode params */

////////////////////////////////////////////
// File local variables declaration
////////////////////////////////////////////

////////////////////////////////////////////
// File local methods declaration
////////////////////////////////////////////
static BOOL parse_continuous_param( const char* line, continuous_mode_param *target);
static BOOL parse_trigger_matching_param( const char* line, trigger_matching_mode_param *target);

////////////////////////////////////////////
// Global visible variables declaration
////////////////////////////////////////////

/**************************************************
**************************************************/
BOOL user_settings_open( user_setting_data* p_data)
{
	// module variable init
	p_data->m_raw_output_filename= (char*)malloc( MAX_FILENAME_LENGHT);
	p_data->m_parsed_output_filename= (char*)malloc( MAX_FILENAME_LENGHT);

	// setting default values ...
	if( p_data->m_raw_output_filename== NULL)
		TRACE("user setting module: insufficient memory !\n");
	else
		strcpy( p_data->m_raw_output_filename, DEF_RAW_OUTPUT_FILENAME);

	if( p_data->m_parsed_output_filename== NULL)
		TRACE("user setting module: insufficient memory !\n");
	else
		strcpy( p_data->m_parsed_output_filename, DEF_PARSED_OUTPUT_FILENAME);

	p_data->m_num_events= DEF_NUM_EVENTS;
	p_data->m_base_address= DEF_BASE_ADDRESS;
	p_data->m_V1190_type= DEF_V1190_TYPE;
	p_data->m_tdc_count= DEF_TDC_COUNT;

	p_data->m_acquisition_mode.m_mode= DEF_ACQUISITION_MODE;
	switch( p_data->m_acquisition_mode.m_mode)
	{
	case AM_CONTINUOUS:
		parse_continuous_param( DEF_ACQUISITION_MODE_PARAMS, &p_data->m_acquisition_mode.m_params.m_continuos);
		break;
	case AM_TRIGGER_MATCH:
		parse_trigger_matching_param( DEF_ACQUISITION_MODE_PARAMS, &p_data->m_acquisition_mode.m_params.m_trigger_matching);
		break;
	case AM_NONE:
		break;
	}
	return TRUE;
}
/**************************************************
**************************************************/
BOOL user_settings_close( user_setting_data* p_data)
{
	// module variable free
	if( p_data->m_raw_output_filename)
		free( p_data->m_raw_output_filename);
	if( p_data->m_parsed_output_filename)
		free( p_data->m_parsed_output_filename);

	// setting invalid values ...
	p_data->m_raw_output_filename= NULL;
	p_data->m_parsed_output_filename= NULL;

	return TRUE;
}

/**************************************************
**************************************************/
BOOL user_settings_parse_input_param( user_setting_data* p_data, int argc, char* argv[])
{
	BOOL ret_val= TRUE;
	BOOL help_to_show= FALSE;
	BOOL some_error_to_ack= FALSE;
	int i;
	for( i= 1; i< argc; i++)
	{
		if( !stricmp( argv[i], "-h"))
		{
			help_to_show= TRUE;
		} 
		else if( !strnicmp( argv[i], "-a", 2))
		{
			// The board's base address
			if( !strnicmp( argv[i]+ 2, "0x", 2))
			{
				// hex format
				int address= 0;
				sscanf( argv[i]+ 4, "%x", &address);
				p_data->m_base_address= (UINT16)address;
			}
			else
			{
				// decimal format
				p_data->m_base_address= atoi( argv[i]+ 2);
			}
		}
		else if( !strnicmp( argv[i], "-p", 2))
		{
			// parsed output filename
			strcpy( p_data->m_parsed_output_filename, argv[i]+ 2);
		}
		else if( !strnicmp( argv[i], "-r", 2))
		{
			// raw output filename
			strcpy( p_data->m_raw_output_filename, argv[i]+ 2);
		}
		else if( !strnicmp( argv[i], "-e", 2))
		{
			// Number of samples to acquire
			p_data->m_num_events= atol( argv[i]+ 2);
		}
		else if( !strnicmp( argv[i], "-t", 2))
		{
			// Board type
			if( !stricmp( argv[i]+ 2, "v1190a"))
			{
				p_data->m_V1190_type= CVT_V1190_TYPE_A;
				p_data->m_tdc_count= CVT_V1190_NUM_TDC_A;
			}
			else if( !stricmp( argv[i]+ 2, "v1190b"))
			{
				p_data->m_V1190_type= CVT_V1190_TYPE_B;
				p_data->m_tdc_count= CVT_V1190_NUM_TDC_B;
			}
			else if( !stricmp( argv[i]+ 2, "v1290a"))
			{
				p_data->m_V1190_type= CVT_V1290_TYPE_A;
				p_data->m_tdc_count= CVT_V1290_NUM_TDC_A;
			}
			else if( !stricmp( argv[i]+ 2, "v1290n"))
			{
				p_data->m_V1190_type= CVT_V1290_TYPE_N;
				p_data->m_tdc_count= CVT_V1290_NUM_TDC_N;
			}
			else
			{
				// Bad parameter
				TRACE1("\nuser settings: bad V1190 type '%s'", argv[i]+ 2);
				TRACE("\n  restart with -h flag for help on usage\n");
				some_error_to_ack= TRUE;
			}
		}
		else if( !strnicmp( argv[i], "-c", 2))
		{
			// continuous acquisition mode
			if( !parse_continuous_param( argv[i]+ 2, &p_data->m_acquisition_mode.m_params.m_continuos))
			{
				TRACE1("\nerror parsing continuous mode parameters '%s'\n", argv[i]+ 2);
				TRACE("\n  restart with -h flag for help on usage\n");
				some_error_to_ack= TRUE;
			}
			else
			{
				p_data->m_acquisition_mode.m_mode= AM_CONTINUOUS;
			}
		}
		else if( !strnicmp( argv[i], "-m", 2))
		{
			// trigger matching acquisition mode
			if( !parse_trigger_matching_param( argv[i]+ 2, &p_data->m_acquisition_mode.m_params.m_trigger_matching))
			{
				TRACE1("\nerror parsing trigger matching mode parameters '%s'\n", argv[i]+ 2);
				TRACE("\n  restart with -h flag for help on usage\n");
				some_error_to_ack= TRUE;
			}
			else
			{
				p_data->m_acquisition_mode.m_mode= AM_TRIGGER_MATCH;
			}
		}
		else
		{
			// Unknown parameter
			TRACE1("\nuser settings: ignored command line parameter '%s'", argv[i]);
			TRACE("\n  restart with -h flag for help on usage\n");
			some_error_to_ack= TRUE;
		}
	}
	if( some_error_to_ack)
	{
		TRACE ( "Hit a key to continue ... \n");
		while( !con_kbhit());
	}
	
	if( help_to_show|| some_error_to_ack)
	{
		clrscr();
		// show help screen
		//       01234567890123456789012345678901234567890123456789012345678901234567890123456789
		TRACE ( "\n");
		TRACE ( "V1190Demo usage:    V1190Demo {params_list}\n");
		TRACE ( "params_list:\n");
		TRACE ( "-pfilename | -Pfilename\n");
		TRACE ( "      filename= parsed output filename.\n");
		TRACE1( "                If not specified '%s' will be assumed.\n", DEF_PARSED_OUTPUT_FILENAME);
		TRACE ( "           example: V1190Demo -p\"parsed data out.dat\"\n");
		TRACE ( "                    V1190Demo -Pparsed_data_out.dat\n");
		TRACE ( "-rfilename | -Rfilename\n");
		TRACE ( "      filename= raw output filename.\n");
		TRACE1( "                If not specified '%s' will be assumed.\n", DEF_RAW_OUTPUT_FILENAME);
		TRACE ( "           example: V1190Demo -r\"raw data out.dat\"\n");
		TRACE ( "                    V1190Demo -Rraw_data_out.dat\n");
		TRACE ( "-abase_address | -Abase_address\n");
		TRACE ( "      base_address= the board's base address (16 bit MSW), expressed in decimal\n"); 
		TRACE ( "                    or hexdecimal format. \n");
		TRACE1( "                    If not specified '0x%04x' will be assumed.\n", DEF_BASE_ADDRESS);
		TRACE ( "           example: V1190Demo -a4660\n");
		TRACE ( "                    V1190Demo -A0x1234\n");
		TRACE ( "-enum_events | -Enum_events\n");
		TRACE ( "      num_events= number of events to acquire.\n");
		TRACE1( "                  If not specified '%i' will be assumed.\n", DEF_NUM_EVENTS);
		TRACE ( "                  A non positive number means don't care (i.e. acquire until key pressed)\n");
		TRACE ( "           example: V1190Demo -e1024\n");
		TRACE ( "                    V1190Demo -E32768\n");
		
		TRACE ( "Hit a key to continue ... \n");
		while( !con_kbhit());
		clrscr();

		TRACE ( "-c\"params\" | -C\"params\"\n");
		TRACE ( "      \"params\"= continuos acquisition mode parameters.\n");
		TRACE1( "                  If not specified '%s' will be assumed.\n", DEF_ACQUISITION_MODE_PARAMS);
		TRACE ( "           The parameter string format is: \n");
		TRACE1( "                  \"edge_detection, m_res_width, enable_msk[0..%i] \n", MAX_V1190_TDC_COUNT-1);
		TRACE ( "           where : \n");
		TRACE ( "                  edge_detection  : The edge detection type numeric value\n");
		TRACE ( "                                    (see CVT_V1190_EDGE_DETECTION_ENUM)\n");
		TRACE ( "                  res_width       : The resolution width numeric value\n");
		TRACE ( "                                    (see CVT_V1190_PAIR_RES_WIDTH_ENUM)\n");
		TRACE1( "                  enable_msk[0..%i]       : The channel enable pattern buffer\n", MAX_CH_ENABLE_WORD- 1);
		TRACE ( "                                            (hex or dec value). You must provide\n");
		TRACE ( "                                            the number of required words depending on the board\n");
		TRACE1( "                                            type (up to %i words). \n", MAX_CH_ENABLE_WORD);
		TRACE ( "                                            If some words are missing, the corresponding channels will be disabled.\n");
		TRACE ( "           example: V1190Demo -c\" 2, 0, 0xffff, 0xffff, 0xffff, 0xffff\"\n");
		TRACE ( "-m\"params\" | -M\"params\"\n");
		TRACE ( "      \"params\"= trigger matching mode parameters.\n");
		TRACE ( "                  If not specified continuous acquisition mode will be assumed.\n");
		TRACE ( "           The parameter string format is:\n");
		TRACE1( "           \"header_trailer_enable, empty_event_enable, trigger_time_tag_enable, window_width, window_offset, extra_search_margin, reject_margin, edge_detection, m_res_width, enable_msk[0..%i] \n", MAX_V1190_TDC_COUNT- 1);
		TRACE ( "           where : \n");
		TRACE ( "                  header_trailer_enable  : Enable(1)/disable(0) header and\n");
		TRACE ( "                                           trailer\n");
		TRACE ( "                  empty_event_enable     : Enable(1)/disable(0) empty event\n");
		TRACE ( "                                           storage\n");
		TRACE ( "                  trigger_time_tag_enable: Enable(1)/disable(0) trigger time\n");
		TRACE ( "                                           tag\n");
		
		TRACE ( "Hit a key to continue ... \n");
		while( !con_kbhit());
		clrscr();

		TRACE ( "                  window_width           : Sets the width of the match window\n");
		TRACE ( "                  window_offset          : Sets the offset of the match window\n");
		TRACE ( "                                           with respect to the trigger itself\n");
		TRACE ( "                  extra_search_margin    : Sets the extra search field of the\n");
		TRACE ( "                                           match window\n");
		TRACE ( "                  reject_margin          : Sets the reject margin, expressed in\n");
		TRACE ( "                                           clock cycles\n");
		TRACE ( "                  edge_detection         : The edge detection type numeric value\n");
		TRACE ( "                                           (see CVT_V1190_EDGE_DETECTION_ENUM)\n");
		TRACE ( "                  res_width              : The resolution width numeric value\n");
		TRACE ( "                                           (see CVT_V1190_PAIR_RES_WIDTH_ENUM)\n");
		TRACE1( "                  enable_msk[0..%i]       : The channel enable pattern buffer\n", MAX_CH_ENABLE_WORD- 1);
		TRACE ( "                                            (hex or dec value). You must provide\n");
		TRACE ( "                                            the number of required words depending on the board\n");
		TRACE1( "                                            type (up to %i words). \n", MAX_CH_ENABLE_WORD);
		TRACE ( "                                            If some words are missing, the corresponding channels will be disabled.\n");
		TRACE ( "           example: V1190Demo -m\" 1, 1, 1, 200, 0, 0, 0, 2, 0, 0xffff, 0xffff, 0xffff, 0xffff\"\n");
		TRACE ( "-tv1190_type | -Tv1190_type\n");
		TRACE ( "      v1190_type= the V1190's type.\n");
		TRACE ( "                  Valid values are: V1190A, V1190B, V1290A, V1290N\n");
		TRACE1( "                    If not specified '%s' will be assumed.\n", DEF_BOARD_TYPE_STR);
		TRACE ( "           example: V1190Demo -tV1190A\n");
		TRACE ( "                    V1190Demo -TV1290N\n");
		TRACE ( "-h | -H\n");
		TRACE ( "      Show this help screen\n");
		TRACE ( "           example: V1190Demo -h\n");
		TRACE ( "\n");
		TRACE ( "Hit a key to continue ... \n");
		while( !con_kbhit());
		
		ret_val= FALSE;
	}
	return ret_val;
}


BOOL parse_continuous_param( const char* line, continuous_mode_param *target)
{
	int i;
	const char* tok;
	char buff[ 300];
	
	strncpy( buff, line, 300);

	tok= strtok( buff, ", ");
	if( !tok)
		return FALSE;
	target->m_edge_detection= atoi( tok);

	tok= strtok( NULL, ", ");
	if( !tok)
		return FALSE;
	target->m_res_width= atoi( tok);

	memset( &target->m_enable_msk[ 0], 0, MAX_CH_ENABLE_WORD* sizeof( target->m_enable_msk[ 0]));
	for( i= 0; i< MAX_CH_ENABLE_WORD; i++)
	{
		int tmp= 0;
		tok= strtok( NULL, ", ");
		if( !tok)
			break;
		if( !strnicmp( tok, "0x", 2))
		{
			// hex format
			sscanf( tok+ 2, "%x", &tmp);
		}
		else
		{
			// decimal format
			tmp= atoi( tok);
		}
		target->m_enable_msk[ i]= (UINT16)tmp;
	}
	return TRUE;
}
BOOL parse_trigger_matching_param( const char* line, trigger_matching_mode_param *target)
{
	int i;
	const char* tok;
	char buff[ 300];
	
	strncpy( buff, line, 300);

	tok= strtok( buff, ", ");
	if( !tok)
		return FALSE;
	target->m_header_trailer_enable= atoi( tok)? TRUE: FALSE;

	tok= strtok( NULL, ", ");
	if( !tok)
		return FALSE;
	target->m_empty_event_enable= atoi( tok)? TRUE: FALSE;

	tok= strtok( NULL, ", ");
	if( !tok)
		return FALSE;
	target->m_trigger_time_tag_enable= atoi( tok)? TRUE: FALSE;

	tok= strtok( NULL, ", ");
	if( !tok)
		return FALSE;
	target->m_window_width= atoi( tok);

	tok= strtok( NULL, ", ");
	if( !tok)
		return FALSE;
	target->m_window_offset= atoi( tok);

	tok= strtok( NULL, ", ");
	if( !tok)
		return FALSE;
	target->m_extra_search_margin= atoi( tok);

	tok= strtok( NULL, ", ");
	if( !tok)
		return FALSE;
	target->m_reject_margin= atoi( tok);

	tok= strtok( NULL, ", ");
	if( !tok)
		return FALSE;
	target->m_edge_detection= atoi( tok);

	tok= strtok( NULL, ", ");
	if( !tok)
		return FALSE;
	target->m_res_width= atoi( tok);

	memset( &target->m_enable_msk[ 0], 0, MAX_CH_ENABLE_WORD* sizeof( target->m_enable_msk[ 0]));
	for( i= 0; i< MAX_CH_ENABLE_WORD; i++)
	{
		int tmp= 0;
		tok= strtok( NULL, ", ");
		if( !tok)
			break;
		if( !strnicmp( tok, "0x", 2))
		{
			// hex format
			sscanf( tok+ 2, "%x", &tmp);
		}
		else
		{
			// decimal format
			tmp= atoi( tok);
		}
		target->m_enable_msk[ i]= (UINT16)tmp;
	}
	return TRUE;
}
