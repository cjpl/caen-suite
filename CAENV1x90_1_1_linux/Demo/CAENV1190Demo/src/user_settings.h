/////////////////////////////////////////////////////////////////////////////
// Name:        user_settings.h
// Purpose:     user settng definitions
// Author:      NDA
// Modified by: 
// Created:     10/04/07
// RCS-ID:      
// Copyright:   CAEN S.p.A. All rights reserved
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#ifndef __USER_SETTINGS_DEF_H
#define __USER_SETTINGS_DEF_H

////////////////////////////////////////////
// File includes
////////////////////////////////////////////
#include "common_defs.h"
#include "cvt_board_commons.h"
#include "cvt_common_defs.h"
#include "cvt_V1190.h"

////////////////////////////////////////////
// Global defines
////////////////////////////////////////////
#define MAX_V1190_TDC_COUNT					CVT_V1190_NUM_TDC_A			/*!< Maximun number of V1190's TDCs */
#define MAX_V1190_CH_PER_TDC_COUNT			CVT_V1190_CH_PER_TDC		/*!< Maximun number of V1190's channels per TDC */
#define MAX_CH_ENABLE_WORD					((MAX_V1190_TDC_COUNT* MAX_V1190_CH_PER_TDC_COUNT)>> 4)
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \struct  trigger_matching_mode_param
*   \brief   Trigger matching acquisition mode parameters
*            
*            This structure stores the relevant parameter for the trigger matching acquisition mode
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	BOOL m_header_trailer_enable;						/*!< Enable/disable header and trailer. */
	BOOL m_empty_event_enable;							/*!< Enable/disable empty event storage. */
	BOOL m_trigger_time_tag_enable;						/*!< Enable/disable the trigger time tag. */
	UINT16 m_window_width;								/*!< Sets the width of the match window. */
	UINT16 m_window_offset;								/*!< Sets the offset of the match window with respect to the trigger itself */
	UINT16 m_extra_search_margin;						/*!< Sets the extra search field of the match window. */
	UINT16 m_reject_margin;								/*!< Sets the reject margin, expressed in clock cycles. */
	CVT_V1190_EDGE_DETECTION_ENUM m_edge_detection;		/*!< The edge detection type. */
	CVT_V1190_PAIR_RES_WIDTH_ENUM m_res_width;			/*!< The resolution width. */
	UINT16 m_enable_msk[ MAX_CH_ENABLE_WORD];			/*!< The channel enable pattern buffer. */
} trigger_matching_mode_param;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \struct  continuous_mode_param
*   \brief   Continuous acquisition mode parameters
*            
*            This structure stores the relevant parameter for the continuous acquisition mode
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	CVT_V1190_EDGE_DETECTION_ENUM m_edge_detection;		/*!< The edge detection type. */
	CVT_V1190_PAIR_RES_WIDTH_ENUM m_res_width;			/*!< The resolution width. */
	UINT16 m_enable_msk[ MAX_CH_ENABLE_WORD];			/*!< The channel enable pattern buffer. */
} continuous_mode_param;


////////////////////////////////////////////////////////////////////////////////////////////////
/*! \enum  ACQUISITION_MODES
*   \brief The acquisition mode enumeration
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	AM_NONE,											/*!< No settings for acquisition mode. */
	AM_CONTINUOUS,										/*!< Continuous acquisition mode. */
	AM_TRIGGER_MATCH									/*!< Trigger match acquisition mode. */
} ACQUISITION_MODES;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \struct  acquisition_mode
*   \brief   The acquisition mode parameters
*            
*            This structure stores the relevant parameter for the selected acquisition mode
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	ACQUISITION_MODES m_mode;							/*!< Selected acquisition mode */
	union
	{
		continuous_mode_param m_continuos;
		trigger_matching_mode_param m_trigger_matching;
	} m_params;
} acquisition_mode;

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \struct  user_setting_data
*   \brief   User settings data structure
*            
*            This structure stores user defined application settings 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	//
	// parameters passed through command line
	char* m_parsed_output_filename;			/*!< The name for parsed data output data file */
	char* m_raw_output_filename;			/*!< The name for raw output data file */
	UINT16 m_base_address;					/*!< The board base address */
	long m_num_events;						/*!< Number of events to acquire */
	CVT_V1X90_TYPES m_V1190_type;			/*!< The V1190 type */
	acquisition_mode m_acquisition_mode;	/*!< The acquisition mode settings */
	//
	// parameters NOT parsed from command line: just for application wide visibility
	int m_tdc_count;						/*!< the V1190 number of TDCs */
	CVBoardTypes m_board_type;				/*!< board Type */
	int m_board_number;						/*!< board number */
	int m_link_number;						/*!< link number */
} user_setting_data;

////////////////////////////////////////////
// Global variables declaration
////////////////////////////////////////////

////////////////////////////////////////////
// Global methods declaration
////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL user_settings_open( user_setting_data* p_data)
*   \brief   init user setting module
*            
*   \param   *p_data data buffer pointer
*   \return  TRUE procedure completed correctly
*   \note    call before any other methods
*/
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL user_settings_open( user_setting_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL user_settings_close( user_setting_data* p_data)
*   \brief   closes user setting module (frees allocated resources)
*            
*   \param   *p_data data buffer pointer
*   \return  TRUE procedure completed correctly
*   \note    call after any other methods
*/
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL user_settings_close( user_setting_data* p_data);

////////////////////////////////////////////////////////////////////////////////////////////////
/*! \fn      BOOL user_settings_parse_input_param( user_setting_data* p_data, int argc, char* argv[])
*   \brief   Scan<s user input parameters
*            
*   \param   *p_data data buffer pointer
*   \param   argc number of input parameters
*   \param   *argv[] string parameters list
*   \return  TRUE procedure completed correctly
*/
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL user_settings_parse_input_param( user_setting_data* p_data, int argc, char* argv[]);

#endif 
