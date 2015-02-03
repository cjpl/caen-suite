////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file    cvt_common_defs.h
*   \brief   Common definitions
*   \author  NDA
*   \version 1.0
*   \date    03/2006
*            
*            Provides common data types, APIs and utility.
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CVT_COMMON_DEFS_DEF_H
#define __CVT_COMMON_DEFS_DEF_H

////////////////////////////////////////////////////////////////////////////////////////////////
// File includes
////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////////////////////
// Global defines
////////////////////////////////////////////////////////////////////////////////////////////////

//
// Data tyes
#if !defined BOOL
	typedef int BOOL;						//!< Boolean type
#endif
#if !defined TRUE
	#define		TRUE	-1					//!< Boolean TRUE value
#endif
#if !defined FALSE
	#define		FALSE	0					//!< Boolean TRUE value
#endif

#if !defined UINT8
	typedef unsigned char      UINT8;		//!< Unsigned 8 bit word
#endif
#if !defined UINT16
	typedef unsigned short     UINT16;		//!< Unsigned 16 bit word
#endif
#if !defined UINT32
	typedef unsigned int       UINT32;		//!< Unsigned 32 bit word
#endif
#ifndef WIN32
	#if !defined UINT64
		typedef unsigned long long UINT64;	//!< Unsigned 64 bit word (Non Windows systems)
	#endif
#endif
#if !defined INT8
	typedef signed   char      INT8;		//!< Signed 8 bit word
#endif
#if !defined INT16
	typedef          short     INT16;		//!< Signed 16 bit word
#endif
#if !defined INT32
	typedef          int       INT32;		//!< Signed 32 bit word
#endif
#ifndef WIN32
	#if !defined INT64
		typedef          long long INT64;	//!< Signed 64 bit word (Non Windows systems)
	#endif
#endif
#if !defined PCSTR
	typedef const char*    PCSTR;			//!< Constant pointer to char
#endif

#if defined (WIN32)
	#if defined( CVT_EXPORTS)
		#define CVT_DLL_API   __declspec( dllexport )
	#else
		#define CVT_DLL_API   __declspec( dllimport )
	#endif
#elif defined (LINUX)
	#define CVT_DLL_API
#endif


//
// Debugging macros
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \def    TRACE( format)
*   \brief  Traces a message to stdout
*   \param  format The message string
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined TRACE
    #ifdef DEBUG
	#define TRACE( format)								printf( format)
    #else
        #define TRACE( format)
    #endif
#endif
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \def    TRACE1( format, p1)
*   \brief  Traces a message to stdout
*   \param  format The message format string 
*   \param  p1 The format string parameter 1 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined TRACE1
    #ifdef DEBUG
	#define TRACE1( format, p1)							printf( format, p1)
    #else
        #define TRACE1( format, p1)
    #endif
#endif
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \def    TRACE2( format, p1, p2)
*   \brief  Traces a message to stdout
*   \param  format The message format string 
*   \param  p1 The format string parameter 1 
*   \param  p2 The format string parameter 2 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined TRACE2
    #ifdef DEBUG
	#define TRACE2( format, p1, p2)						printf( format, p1, p2)
    #else
        #define TRACE2( format, p1, p2)
    #endif
#endif
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \def    TRACE3( format, p1, p2, p3)
*   \brief  Traces a message to stdout
*   \param  format The message format string 
*   \param  p1 The format string parameter 1 
*   \param  p2 The format string parameter 2 
*   \param  p3 The format string parameter 3 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined TRACE3
    #ifdef DEBUG
	#define TRACE3( format, p1, p2, p3)					printf( format, p1, p2, p3)
    #else
        #define TRACE3( format, p1, p2, p3)
    #endif
#endif
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \def    TRACE4( format, p1, p2, p3, p4)
*   \brief  Traces a message to stdout
*   \param  format The message format string 
*   \param  p1 The format string parameter 1 
*   \param  p2 The format string parameter 2 
*   \param  p3 The format string parameter 3 
*   \param  p4 The format string parameter 4 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined TRACE4
    #ifdef DEBUG
	#define TRACE4( format, p1, p2, p3, p4)				printf( format, p1, p2, p3, p4)
    #else
        #define TRACE4( format, p1, p2, p3, p4)
    #endif
#endif
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \def    TRACE5( format, p1, p2, p3, p4, p5)
*   \brief  Traces a message to stdout
*   \param  format The message format string 
*   \param  p1 The format string parameter 1 
*   \param  p2 The format string parameter 2 
*   \param  p3 The format string parameter 3 
*   \param  p4 The format string parameter 4 
*   \param  p5 The format string parameter 5 
*/
////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined TRACE5
    #ifdef DEBUG
	#define TRACE5( format, p1, p2, p3, p4, p5)			printf( format, p1, p2, p3, p4, p5)
    #else
    	#define TRACE5( format, p1, p2, p3, p4, p5)			
    #endif
#endif

//
// Helper functions
#ifndef WIN32
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \def    stricmp( str1, str2)
*   \brief  Case insensitive string compare
*   \param  str1 First string to compare
*   \param  str2 Second string to compare
*
*           Provides a wrapper to strcasecmp, for multiplatform issue.
*   \note   Non Windows systems only
*/
////////////////////////////////////////////////////////////////////////////////////////////////
	#define stricmp( str1, str2)		strcasecmp( str1, str2)
////////////////////////////////////////////////////////////////////////////////////////////////
/*! \def    strnicmp( str1, str2, n)
*   \brief  Case insensitive string compare up to n characters
*   \param  str1 First string to compare
*   \param  str2 Second string to compare
*   \param  n Maximun mumber of characters to compare
*
*           Provides a wrapper to strncasecmp, for multiplatform issue.
*   \note   Non Windows systems only
*/
////////////////////////////////////////////////////////////////////////////////////////////////
	#define strnicmp( str1, str2, n)	strncasecmp( str1, str2, n)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////
// Global variables declaration
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// Global methods declaration
////////////////////////////////////////////////////////////////////////////////////////////////




#endif 
