/////////////////////////////////////////////////////////////////////////////
// Name:        common_ch_control_base.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     11/01/2007 15:09:38
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _COMMON_CH_CONTROL_BASE_H_
#define _COMMON_CH_CONTROL_BASE_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "common_ch_control_base.h"
#endif

/*!
 * Includes
 */

/*!
 * Forward declarations
 */

/*!
 * Control identifiers
 */


/*!
 * CommonChControlBase class declaration
 */

class CommonChControlBase: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( CommonChControlBase )
public:
    /// Constructors
    CommonChControlBase( );
    CommonChControlBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);

	virtual void SetMediumLabel( double value);
	virtual void SetOverloadBackground( const wxColor& color);
	virtual void SetEnable( bool enable, bool disable_all);
};

#endif
    // _COMMON_CH_CONTROL_BASE_H_
