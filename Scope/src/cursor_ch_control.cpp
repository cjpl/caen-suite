/////////////////////////////////////////////////////////////////////////////
// Name:        cursor_ch_control.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     12/10/2006 10:56:03
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 12/10/2006 10:56:03

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "cursor_ch_control.h"
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

#include "cursor_ch_control.h"

////@begin XPM images
////@end XPM images

/*!
 * CursorChControl type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CursorChControl, wxPanel )

/*!
 * CursorChControl event table definition
 */

BEGIN_EVENT_TABLE( CursorChControl, wxPanel )

////@begin CursorChControl event table entries
    EVT_TOGGLEBUTTON( ID_CURSOR_TOGGLEBUTTON, CursorChControl::OnCursorTogglebuttonClick )

    EVT_CHOICE( ID_CHANNEL_CHOICE, CursorChControl::OnChannelChoiceSelected )

    EVT_BUTTON( ID_CURSOR_0_RESET_BUTTON, CursorChControl::OnCursor0ResetButtonClick )

    EVT_SPIN( ID_CURSOR_0_POSITION_SPINBUTTON, CursorChControl::OnCursor0PositionSpinbuttonUpdated )

    EVT_CHOICE( ID_CURSOR_0_POS_MULTIPLIER_CHOICE, CursorChControl::OnCursor0PosMultiplierChoiceSelected )

    EVT_BUTTON( ID_CURSOR_1_RESET_BUTTON, CursorChControl::OnCursor1ResetButtonClick )

    EVT_SPIN( ID_CURSOR_1_POSITION_SPINBUTTON, CursorChControl::OnCursor1PositionSpinbuttonUpdated )

    EVT_CHOICE( ID_CURSOR_1_POS_MULTIPLIER_CHOICE, CursorChControl::OnCursor1PosMultiplierChoiceSelected )

////@end CursorChControl event table entries

END_EVENT_TABLE()

/*!
 * CursorChControl constructors
 */

 CursorChControl::CursorChControl( )
{
	wxASSERT( SCOPE_NUM_CURSORS== 2);
	for( int cursor_index= 0; cursor_index< SCOPE_NUM_CURSORS; cursor_index++)
	{
		m_last_cursor_pos[cursor_index]= 0;
	}
}

CursorChControl::CursorChControl( int scope_index, wxMutex *mutex, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
								: m_scope_index(-1), m_p_board_channel(NULL), m_mutex( mutex)
{
	wxASSERT( SCOPE_NUM_CURSORS== 2);
	for( int cursor_index= 0; cursor_index< SCOPE_NUM_CURSORS; cursor_index++)
	{
		m_last_cursor_pos[cursor_index]= 0;
	}
    Create(parent, id, pos, size, style);
	m_scope_index= scope_index;

}

/*!
 * CursorChControl creator
 */

bool CursorChControl::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CursorChControl member initialisation
    m_cursor_enable_control = NULL;
    m_channel_control = NULL;
    m_ch_cursor_0_reset_control = NULL;
    m_set_cursor_0_position_control = NULL;
    m_cursor_0_pos_multiplier_control = NULL;
    m_cursor_0_position_control = NULL;
    m_cursor_0_value_control = NULL;
    m_ch_cursor_1_reset_control = NULL;
    m_set_cursor_1_position_control = NULL;
    m_cursor_1_pos_multiplier_control = NULL;
    m_cursor_1_position_control = NULL;
    m_cursor_1_value_control = NULL;
    m_delta_position_control = NULL;
    m_delta_value_control = NULL;
////@end CursorChControl member initialisation

////@begin CursorChControl creation
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CursorChControl creation
    return true;
}

/*!
 * Control creation for CursorChControl
 */

void CursorChControl::CreateControls()
{    
////@begin CursorChControl content construction
    // Generated by DialogBlocks, 30/11/2010 08:21:32 (unregistered)

    CursorChControl* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer4, 0, wxALIGN_TOP|wxALL, 5);

    m_cursor_enable_control = new wxToggleButton( itemPanel1, ID_CURSOR_TOGGLEBUTTON, _("???"), wxDefaultPosition, wxSize(60, -1), 0 );
    m_cursor_enable_control->SetValue(true);
    m_cursor_enable_control->SetHelpText(_("Enable/Disable cursors"));
    if (ShowToolTips())
        m_cursor_enable_control->SetToolTip(_("Enable/Disable cursors"));
    m_cursor_enable_control->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false, _T("Verdana")));
    itemBoxSizer4->Add(m_cursor_enable_control, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 6);

    wxString* m_channel_controlStrings = NULL;
    m_channel_control = new wxChoice( itemPanel1, ID_CHANNEL_CHOICE, wxDefaultPosition, wxSize(100, -1), 0, m_channel_controlStrings, 0 );
    m_channel_control->SetHelpText(_("Set the cursor's channel"));
    if (ShowToolTips())
        m_channel_control->SetToolTip(_("Set the cursor's channel"));
    itemBoxSizer4->Add(m_channel_control, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer7->Add(itemBoxSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer9Static = new wxStaticBox(itemPanel1, wxID_ANY, _T(""));
    wxStaticBoxSizer* itemStaticBoxSizer9 = new wxStaticBoxSizer(itemStaticBoxSizer9Static, wxVERTICAL);
    itemBoxSizer8->Add(itemStaticBoxSizer9, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 3);

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer9->Add(itemBoxSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_ch_cursor_0_reset_control = new wxButton( itemPanel1, ID_CURSOR_0_RESET_BUTTON, _("0"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    m_ch_cursor_0_reset_control->SetHelpText(_("Reset cursor position"));
    if (ShowToolTips())
        m_ch_cursor_0_reset_control->SetToolTip(_("Reset cursor position"));
    m_ch_cursor_0_reset_control->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false, _T("Tahoma")));
    itemBoxSizer10->Add(m_ch_cursor_0_reset_control, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2);

    m_set_cursor_0_position_control = new wxSpinButton( itemPanel1, ID_CURSOR_0_POSITION_SPINBUTTON, wxDefaultPosition, wxDefaultSize, wxSP_HORIZONTAL );
    m_set_cursor_0_position_control->SetHelpText(_("Set cursor position"));
    if (ShowToolTips())
        m_set_cursor_0_position_control->SetToolTip(_("Set cursor position"));
    itemBoxSizer10->Add(m_set_cursor_0_position_control, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 2);

    wxString* m_cursor_0_pos_multiplier_controlStrings = NULL;
    m_cursor_0_pos_multiplier_control = new wxChoice( itemPanel1, ID_CURSOR_0_POS_MULTIPLIER_CHOICE, wxDefaultPosition, wxSize(70, -1), 0, m_cursor_0_pos_multiplier_controlStrings, 0 );
    m_cursor_0_pos_multiplier_control->SetHelpText(_("Set cursor position multiplier factor"));
    if (ShowToolTips())
        m_cursor_0_pos_multiplier_control->SetToolTip(_("Set cursor position multiplier factor"));
    itemStaticBoxSizer9->Add(m_cursor_0_pos_multiplier_control, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer8->Add(itemBoxSizer14, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5);

    wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer14->Add(itemBoxSizer15, 0, wxALIGN_RIGHT|wxALL, 0);

    wxStaticText* itemStaticText16 = new wxStaticText( itemPanel1, wxID_STATIC, _("T1 : "), wxDefaultPosition, wxSize(60, -1), wxALIGN_RIGHT );
    itemBoxSizer15->Add(itemStaticText16, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    m_cursor_0_position_control = new wxStaticText( itemPanel1, wxID_STATIC, _("0"), wxDefaultPosition, wxSize(70, -1), 0 );
    m_cursor_0_position_control->SetHelpText(_("Cursor position (uSec)"));
    if (ShowToolTips())
        m_cursor_0_position_control->SetToolTip(_("Cursor position (uSec)"));
    m_cursor_0_position_control->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false, _T("Tahoma")));
    itemBoxSizer15->Add(m_cursor_0_position_control, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxStaticText* itemStaticText18 = new wxStaticText( itemPanel1, wxID_STATIC, _("uS"), wxDefaultPosition, wxSize(20, -1), 0 );
    itemBoxSizer15->Add(itemStaticText18, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer14->Add(itemBoxSizer19, 0, wxALIGN_RIGHT|wxALL, 0);

    wxStaticText* itemStaticText20 = new wxStaticText( itemPanel1, wxID_STATIC, _("V1 : "), wxDefaultPosition, wxSize(60, -1), wxALIGN_RIGHT );
    itemBoxSizer19->Add(itemStaticText20, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    m_cursor_0_value_control = new wxStaticText( itemPanel1, wxID_STATIC, _("0"), wxDefaultPosition, wxSize(70, -1), 0 );
    m_cursor_0_value_control->SetHelpText(_("Signal value at cursor position (mV)"));
    if (ShowToolTips())
        m_cursor_0_value_control->SetToolTip(_("Signal value at cursor position (mV)"));
    m_cursor_0_value_control->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false, _T("Tahoma")));
    itemBoxSizer19->Add(m_cursor_0_value_control, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxStaticText* itemStaticText22 = new wxStaticText( itemPanel1, wxID_STATIC, _("mV"), wxDefaultPosition, wxSize(20, -1), 0 );
    itemBoxSizer19->Add(itemStaticText22, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxBoxSizer* itemBoxSizer23 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer7->Add(itemBoxSizer23, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer24Static = new wxStaticBox(itemPanel1, wxID_ANY, _T(""));
    wxStaticBoxSizer* itemStaticBoxSizer24 = new wxStaticBoxSizer(itemStaticBoxSizer24Static, wxVERTICAL);
    itemBoxSizer23->Add(itemStaticBoxSizer24, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 3);

    wxBoxSizer* itemBoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer24->Add(itemBoxSizer25, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_ch_cursor_1_reset_control = new wxButton( itemPanel1, ID_CURSOR_1_RESET_BUTTON, _("0"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    m_ch_cursor_1_reset_control->SetHelpText(_("Reset cursor position"));
    if (ShowToolTips())
        m_ch_cursor_1_reset_control->SetToolTip(_("Reset cursor position"));
    m_ch_cursor_1_reset_control->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false, _T("Tahoma")));
    itemBoxSizer25->Add(m_ch_cursor_1_reset_control, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 2);

    m_set_cursor_1_position_control = new wxSpinButton( itemPanel1, ID_CURSOR_1_POSITION_SPINBUTTON, wxDefaultPosition, wxDefaultSize, wxSP_HORIZONTAL );
    m_set_cursor_1_position_control->SetHelpText(_("Set cursor position"));
    if (ShowToolTips())
        m_set_cursor_1_position_control->SetToolTip(_("Set cursor position"));
    itemBoxSizer25->Add(m_set_cursor_1_position_control, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 2);

    wxString* m_cursor_1_pos_multiplier_controlStrings = NULL;
    m_cursor_1_pos_multiplier_control = new wxChoice( itemPanel1, ID_CURSOR_1_POS_MULTIPLIER_CHOICE, wxDefaultPosition, wxSize(70, -1), 0, m_cursor_1_pos_multiplier_controlStrings, 0 );
    m_cursor_1_pos_multiplier_control->SetHelpText(_("Set cursor position multiplier factor"));
    if (ShowToolTips())
        m_cursor_1_pos_multiplier_control->SetToolTip(_("Set cursor position multiplier factor"));
    itemStaticBoxSizer24->Add(m_cursor_1_pos_multiplier_control, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxBoxSizer* itemBoxSizer29 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer23->Add(itemBoxSizer29, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5);

    wxBoxSizer* itemBoxSizer30 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer29->Add(itemBoxSizer30, 0, wxALIGN_RIGHT|wxALL, 0);

    wxStaticText* itemStaticText31 = new wxStaticText( itemPanel1, wxID_STATIC, _("T1 : "), wxDefaultPosition, wxSize(60, -1), wxALIGN_RIGHT );
    itemBoxSizer30->Add(itemStaticText31, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    m_cursor_1_position_control = new wxStaticText( itemPanel1, wxID_STATIC, _("0"), wxDefaultPosition, wxSize(70, -1), 0 );
    m_cursor_1_position_control->SetHelpText(_("Cursor position (uSec)"));
    if (ShowToolTips())
        m_cursor_1_position_control->SetToolTip(_("Cursor position (uSec)"));
    m_cursor_1_position_control->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false, _T("Tahoma")));
    itemBoxSizer30->Add(m_cursor_1_position_control, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxStaticText* itemStaticText33 = new wxStaticText( itemPanel1, wxID_STATIC, _("uS"), wxDefaultPosition, wxSize(20, -1), 0 );
    itemBoxSizer30->Add(itemStaticText33, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxBoxSizer* itemBoxSizer34 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer29->Add(itemBoxSizer34, 0, wxALIGN_RIGHT|wxALL, 0);

    wxStaticText* itemStaticText35 = new wxStaticText( itemPanel1, wxID_STATIC, _("V1 : "), wxDefaultPosition, wxSize(60, -1), wxALIGN_RIGHT );
    itemBoxSizer34->Add(itemStaticText35, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    m_cursor_1_value_control = new wxStaticText( itemPanel1, wxID_STATIC, _("0"), wxDefaultPosition, wxSize(70, -1), 0 );
    m_cursor_1_value_control->SetHelpText(_("Signal value at cursor position (mV)"));
    if (ShowToolTips())
        m_cursor_1_value_control->SetToolTip(_("Signal value at cursor position (mV)"));
    m_cursor_1_value_control->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false, _T("Tahoma")));
    itemBoxSizer34->Add(m_cursor_1_value_control, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxStaticText* itemStaticText37 = new wxStaticText( itemPanel1, wxID_STATIC, _("mV"), wxDefaultPosition, wxSize(20, -1), 0 );
    itemBoxSizer34->Add(itemStaticText37, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxBoxSizer* itemBoxSizer38 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer7->Add(itemBoxSizer38, 0, wxALIGN_RIGHT|wxALL, 5);

    wxStaticText* itemStaticText39 = new wxStaticText( itemPanel1, wxID_STATIC, _("T2 - T1 : "), wxDefaultPosition, wxSize(60, -1), wxALIGN_RIGHT );
    itemBoxSizer38->Add(itemStaticText39, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    m_delta_position_control = new wxStaticText( itemPanel1, wxID_STATIC, _("0"), wxDefaultPosition, wxSize(70, -1), 0 );
    m_delta_position_control->SetHelpText(_("Cursors' position difference (uSec)"));
    if (ShowToolTips())
        m_delta_position_control->SetToolTip(_("Cursors' position difference (uSec)"));
    m_delta_position_control->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false, _T("Tahoma")));
    itemBoxSizer38->Add(m_delta_position_control, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxStaticText* itemStaticText41 = new wxStaticText( itemPanel1, wxID_STATIC, _("uS"), wxDefaultPosition, wxSize(20, -1), 0 );
    itemBoxSizer38->Add(itemStaticText41, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxBoxSizer* itemBoxSizer42 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer7->Add(itemBoxSizer42, 0, wxALIGN_RIGHT|wxALL, 5);

    wxStaticText* itemStaticText43 = new wxStaticText( itemPanel1, wxID_STATIC, _("V2 - V1 : "), wxDefaultPosition, wxSize(60, -1), wxALIGN_RIGHT );
    itemBoxSizer42->Add(itemStaticText43, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    m_delta_value_control = new wxStaticText( itemPanel1, wxID_STATIC, _("0"), wxDefaultPosition, wxSize(70, -1), 0 );
    m_delta_value_control->SetHelpText(_("Signals' value difference at cursors' position (mV)"));
    if (ShowToolTips())
        m_delta_value_control->SetToolTip(_("Signals' value difference at cursors' position (mV)"));
    m_delta_value_control->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false, _T("Tahoma")));
    itemBoxSizer42->Add(m_delta_value_control, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

    wxStaticText* itemStaticText45 = new wxStaticText( itemPanel1, wxID_STATIC, _("mV"), wxDefaultPosition, wxSize(20, -1), 0 );
    itemBoxSizer42->Add(itemStaticText45, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 2);

////@end CursorChControl content construction

	// Helper storage
    m_helper_ch_cursor_reset_control[ 0]= m_ch_cursor_0_reset_control;
    m_helper_ch_cursor_reset_control[ 1]= m_ch_cursor_1_reset_control;

    m_helper_set_cursor_position_control[ 0]= m_set_cursor_0_position_control;
    m_helper_set_cursor_position_control[ 1]= m_set_cursor_1_position_control;

	m_helper_cursor_pos_multiplier_control[ 0]= m_cursor_0_pos_multiplier_control;
	m_helper_cursor_pos_multiplier_control[ 1]= m_cursor_1_pos_multiplier_control;

	m_helper_cursor_position_control[ 0]= m_cursor_0_position_control;
	m_helper_cursor_position_control[ 1]= m_cursor_1_position_control;

	m_helper_cursor_value_control[ 0]= m_cursor_0_value_control;
	m_helper_cursor_value_control[ 1]= m_cursor_1_value_control;

	m_cursor_enable_control->SetValue( false);
	m_cursor_enable_control->SetLabel( _("Enable"));
	for( int cursor_index= 0; cursor_index< SCOPE_NUM_CURSORS; cursor_index++)
	{
		m_helper_set_cursor_position_control[cursor_index]->SetRange( -999999999, 999999999);

		m_helper_cursor_pos_multiplier_control[cursor_index]->Append( _("x   1"));
		m_helper_cursor_pos_multiplier_control[cursor_index]->Append( _("x  10"));
		m_helper_cursor_pos_multiplier_control[cursor_index]->Append( _("x 100"));
		m_helper_cursor_pos_multiplier_control[cursor_index]->Append( _("x1000"));

		m_helper_cursor_pos_multiplier_control[cursor_index]->SetSelection( 0);
	}
}

/*!
 * Should we show tooltips?
 */

bool CursorChControl::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CursorChControl::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CursorChControl bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CursorChControl bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CursorChControl::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CursorChControl icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CursorChControl icon retrieval
}
/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_TOGGLEBUTTON
 */

void CursorChControl::OnCursorTogglebuttonClick( wxCommandEvent& /* event*/ )
{
	UpdateChannelEnable( );
}
void CursorChControl::UpdateChannelEnable( )
{
	if(( m_scope_index< 0)|| !m_p_board_channel) return;
	m_p_board_channel->m_cursor_enabled[ this->m_scope_index]= m_cursor_enable_control->GetValue( );
	m_cursor_enable_control->SetLabel( m_cursor_enable_control->GetValue( )? _("Disable"): _("Enable"));
	(m_p_board_channel->ScopeRefresh)( this->m_scope_index, true);
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
 */

void CursorChControl::OnCursor0ResetButtonClick( wxCommandEvent& /*event*/ )
{
	m_last_cursor_pos[0]= 0;
	m_helper_set_cursor_position_control[0]->SetValue( m_last_cursor_pos[0]);
	UpdateCursorPosition( m_last_cursor_pos[0], 0);
}

/*!
 * wxEVT_COMMAND_SPINCTRL_UPDATED event handler for ID_SPINBUTTON1
 */

void CursorChControl::OnCursor0PositionSpinbuttonUpdated( wxSpinEvent& /*event*/ )
{
	OnCursorPositionChanged( 0);
}

void CursorChControl::OnCursorPositionChanged( int cursor_index)
{
	int new_pos= m_helper_set_cursor_position_control[cursor_index]->GetValue( );
	m_last_cursor_pos[cursor_index]+= ( new_pos- this->m_last_cursor_pos[cursor_index])* GetCursorMultipler(cursor_index);
	m_helper_set_cursor_position_control[cursor_index]->SetValue( this->m_last_cursor_pos[cursor_index]);

	this->UpdateCursorPosition( m_helper_set_cursor_position_control[cursor_index]->GetValue( ), cursor_index);
}


bool CursorChControl::SetupBoard( GenericBoard* p_board)
{
	wxMutexLocker lock( *m_mutex);

	// Remove previous board if any
	if(( m_scope_index>= 0)&& m_p_board_channel)
	{
		this->m_p_board_channel->m_cursor_enabled[ m_scope_index]= false;
		this->m_p_board_channel->m_p_cursor_ch_control[ m_scope_index]= NULL;
	}
	m_channel_control->Clear();
	// Initialize channel selection combo
	for( size_t i= 0; i< p_board->m_channel_array.Count(); i++)
	{
		GenericBoardChannel* channel= (GenericBoardChannel*)p_board->m_channel_array[i];
		m_channel_control->Append( wxString::Format( _T("Ch %d"), i), (void*) channel);
	}
	for( size_t i= 0; i< p_board->m_virtual_channel_array.Count(); i++)
	{
		GenericBoardChannel* channel= (GenericBoardChannel*)p_board->m_virtual_channel_array[i];
		m_channel_control->Append( wxString::Format( _T("Virt. Ch %d"), i), (void*) channel);
	}

	this->m_p_board= p_board;
	m_channel_control->SetSelection(0);
	SetupChannel( false);
	UpdateChannelEnable( );
	return true;
}

int CursorChControl::GetCursorMultipler( int cursor_index)
{
	const int MULTIPLIER_TABLE[]=
	{
		1,
		10,
		100,
		1000,
	};
	int multiplier= 100;
	if( m_helper_cursor_pos_multiplier_control[cursor_index]->GetSelection()< ( sizeof( MULTIPLIER_TABLE)/ sizeof( MULTIPLIER_TABLE[0])))
	{
		multiplier= MULTIPLIER_TABLE[ m_helper_cursor_pos_multiplier_control[cursor_index]->GetSelection()];
	}
	return multiplier;
}
bool CursorChControl::UpdateCursorPosition( int cursor_position, int cursor_index)
{
	if(( m_scope_index< 0)|| !m_p_board_channel) return false;
	this->m_p_board_channel->m_cursor_position[ this->m_scope_index][cursor_index]= cursor_position;
	(this->m_p_board_channel->ScopeRefresh)( this->m_scope_index, true);

	double position_usec= this->m_p_board_channel->Sample2Sec( cursor_position)* 1000000.0;
	m_helper_cursor_position_control[cursor_index]->SetLabel( wxString::Format( _T("%.3f"), position_usec));

	// Update the delta position value
	double other_position_usec= this->m_p_board_channel->Sample2Sec( this->m_p_board_channel->m_cursor_position[m_scope_index][ cursor_index? 0: 1])* 1000000.0;
	double delta_pos= cursor_index? position_usec- other_position_usec: other_position_usec- position_usec;
	m_delta_position_control->SetLabel( wxString::Format( _T("%.3f"), delta_pos));
	
	return true;
}

/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CURSOR_POS_MULTIPLIER_CHOICE
 */

void CursorChControl::OnCursor0PosMultiplierChoiceSelected( wxCommandEvent& /*event*/ )
{
	// this->UpdateCursorPosition( this->m_set_cursor_position_control->GetValue( ));
}

/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
 */

void CursorChControl::OnChannelChoiceSelected( wxCommandEvent& /*event*/ )
{
	SetupChannel( true);
}
void CursorChControl::SetupChannel( bool do_lock)
{
	if( do_lock) 
	{
		wxMutexLocker lock( *m_mutex);
	}
	if(( m_scope_index>= 0)&& m_p_board_channel) 
	{
		this->m_p_board_channel->m_cursor_enabled[ m_scope_index]= false;
		this->m_p_board_channel->m_p_cursor_ch_control[ m_scope_index]= NULL;
		this->m_p_board_channel= NULL;
	}
	int sel_ch= m_channel_control->GetSelection();
	if( sel_ch< 0)
	{
		return;
	}
	this->m_p_board_channel= (GenericBoardChannel*)m_channel_control->GetClientData( sel_ch);
	this->m_p_board_channel->m_p_cursor_ch_control[ this->m_scope_index]= this;
	this->m_p_board_channel->m_cursor_enabled[ this->m_scope_index]= m_cursor_enable_control->GetValue();
	for( int i= 0; i< SCOPE_NUM_CURSORS; i++)
	{
		this->m_p_board_channel->m_cursor_position[ this->m_scope_index][i]= m_last_cursor_pos[i];
	}
	(this->m_p_board_channel->ScopeRefresh)( this->m_scope_index, true);
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void CursorChControl::OnCursor1ResetButtonClick( wxCommandEvent& /*event*/ )
{
	m_last_cursor_pos[1]= 0;
	m_helper_set_cursor_position_control[1]->SetValue( m_last_cursor_pos[1]);
	UpdateCursorPosition( m_last_cursor_pos[1], 0);
}

/*!
 * wxEVT_COMMAND_SPINCTRL_UPDATED event handler for ID_SPINBUTTON
 */

void CursorChControl::OnCursor1PositionSpinbuttonUpdated( wxSpinEvent& /*event */)
{
	OnCursorPositionChanged( 1);
}

/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
 */

void CursorChControl::OnCursor1PosMultiplierChoiceSelected( wxCommandEvent& /*event*/ )
{
}

void CursorChControl::SetCursorValues( double cursor_values[SCOPE_NUM_CURSORS])
{
	for( int i= 0; i< SCOPE_NUM_CURSORS; i++)
	{
		m_helper_cursor_value_control[i]->SetLabel( wxString::Format( _T("%.3f"), cursor_values[i]));
	}
	// Update the delta value
	double delta_value= cursor_values[1]- cursor_values[0];
	m_delta_value_control->SetLabel( wxString::Format( _T("%.3f"), delta_value));
}


