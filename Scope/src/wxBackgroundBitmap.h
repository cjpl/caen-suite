/////////////////////////////////////////////////////////////////////////////
// Name:        wxBackgroundBitmap.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     03/01/2007 12:54:22
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////


#ifndef _WXBACKGROUNDBITMAP_H_
#define _WXBACKGROUNDBITMAP_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "wxBackgroundBitmap.h"
#endif
#include <wx/wx.h>

class wxBackgroundBitmap : public wxEvtHandler {
    typedef wxEvtHandler Inherited;
public:
    wxBackgroundBitmap(const wxBitmap &B, const wxWindow *parent) : m_bitmap( B), m_p_parent( parent), wxEvtHandler() { }
    virtual bool        ProcessEvent(wxEvent &Event);
protected:
    wxBitmap m_bitmap;
    const wxWindow *m_p_parent;

};

#endif
