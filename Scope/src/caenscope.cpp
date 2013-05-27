/////////////////////////////////////////////////////////////////////////////
// Name:        caenscope.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     04/03/06 13:09:06
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "caenscope.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "caenscope.h"

////@begin XPM images
////@end XPM images

/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( CAENScopeApp )
////@end implement app

/*!
 * CAENScopeApp type definition
 */

IMPLEMENT_CLASS( CAENScopeApp, wxApp )

/*!
 * CAENScopeApp event table definition
 */

BEGIN_EVENT_TABLE( CAENScopeApp, wxApp )

////@begin CAENScopeApp event table entries
////@end CAENScopeApp event table entries

END_EVENT_TABLE()

/*!
 * Constructor for CAENScopeApp
 */

CAENScopeApp::CAENScopeApp()
{
////@begin CAENScopeApp member initialisation
////@end CAENScopeApp member initialisation
}

/*!
 * Initialisation for CAENScopeApp
 */

bool CAENScopeApp::OnInit()
{    
////@begin CAENScopeApp initialisation
    // Remove the comment markers above and below this block
    // to make permanent changes to the code.

#if wxUSE_XPM
    wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
    MainFrame* mainWindow = new MainFrame( NULL, ID_MAIN_FRAME );
    mainWindow->Show(true);
////@end CAENScopeApp initialisation

    return true;
}

/*!
 * Cleanup for CAENScopeApp
 */
int CAENScopeApp::OnExit()
{    
////@begin CAENScopeApp cleanup
    return wxApp::OnExit();
////@end CAENScopeApp cleanup
}

