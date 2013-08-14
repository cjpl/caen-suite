/////////////////////////////////////////////////////////////////////////////
// Name:        caenscope.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 13:09:06
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _CAENSCOPE_H_
#define _CAENSCOPE_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "caenscope.h"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "mainframe.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * CAENScopeApp class declaration
 */

class CAENScopeApp: public wxApp
{    
    DECLARE_CLASS( CAENScopeApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    CAENScopeApp();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin CAENScopeApp event handler declarations

////@end CAENScopeApp event handler declarations

////@begin CAENScopeApp member function declarations

////@end CAENScopeApp member function declarations

////@begin CAENScopeApp member variables
////@end CAENScopeApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(CAENScopeApp)
////@end declare app

#endif
    // _CAENSCOPE_H_
