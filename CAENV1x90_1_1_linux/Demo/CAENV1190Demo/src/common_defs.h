/***********************************************************************************************
* MODULE:     common_defs.h
* PURPOSE:    common definitions
* WRITTEN BY: NDA
* COPYRIGHT:  CAEN S.p.A. all rights reserved
* USAGE:      compiled with gcc ?!?!
************************************************************************************************/
#ifndef __COMMON_DEFS_DEF_H
#define __COMMON_DEFS_DEF_H

////////////////////////////////////////////
// File includes
////////////////////////////////////////////
#include <stdio.h>
#include "console.h"


////////////////////////////////////////////
// Global defines
////////////////////////////////////////////

//
// Data tyes
/*
typedef int BOOL;
#define TRUE	-1
#define FALSE	0


typedef unsigned char      UINT8;
typedef unsigned short     UINT16;
typedef unsigned int       UINT32;
typedef unsigned long long UINT64;
typedef          char      INT8;
typedef          short     INT16;
typedef          int       INT32;
typedef          long long INT64;

typedef const char*    PCSTR;

*/
//
// Debugging macros
#define TRACE( format)								con_printf( format)
#define TRACE1( format, p1)							con_printf( format, p1)
#define TRACE2( format, p1, p2)						con_printf( format, p1, p2)
#define TRACE3( format, p1, p2, p3)					con_printf( format, p1, p2, p3)
#define TRACE4( format, p1, p2, p3, p4)				con_printf( format, p1, p2, p3, p4)
#define TRACE5( format, p1, p2, p3, p4, p5)			con_printf( format, p1, p2, p3, p4, p5)


//
// Helper functions
#ifdef LINUX
	#define stricmp( str1, str2)		strcasecmp( str1, str2)
	#define strnicmp( str1, str2, n)	strncasecmp( str1, str2, n)
#endif
////////////////////////////////////////////
// Global variables declaration
////////////////////////////////////////////

////////////////////////////////////////////
// Global methods declaration
////////////////////////////////////////////




#endif 
