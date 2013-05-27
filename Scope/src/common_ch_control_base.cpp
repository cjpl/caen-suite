/////////////////////////////////////////////////////////////////////////////
// Name:        common_ch_control_base.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     11/01/2007 15:09:37
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "common_ch_control_base.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
// #include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "common_ch_control_base.h"

/*!
 * CommonChControlBase type definition
 */

 IMPLEMENT_DYNAMIC_CLASS( CommonChControlBase, wxPanel )

/*!
 * CommonChControlBase event table definition
 */

/*!
 * CommonChControlBase constructors
 */

CommonChControlBase::CommonChControlBase( )
{
}

CommonChControlBase::CommonChControlBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
}

void CommonChControlBase::SetMediumLabel( double value)
{
}
void CommonChControlBase::SetOverloadBackground( const wxColor& color)
{
}
void CommonChControlBase::SetEnable( bool enable, bool disable_all)
{
}

