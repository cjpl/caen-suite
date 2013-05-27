#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "wxBackgroundBitmap.h"
#endif

#include "./wxBackgroundBitmap.h"

bool wxBackgroundBitmap::ProcessEvent(wxEvent &Event)
{
	bool ret= Inherited::ProcessEvent( Event);
	if (Event.GetEventType() == wxEVT_ERASE_BACKGROUND) 
	{
		if( this->m_p_parent== 0)
			return ret;
		wxEraseEvent &EraseEvent = dynamic_cast<wxEraseEvent &>(Event);
		wxDC *dc= EraseEvent.GetDC();
		dc->DrawBitmap( this->m_bitmap, this->m_p_parent->GetClientSize().GetWidth()- this->m_bitmap.GetWidth(), 0, true);
		return true;
	} 
	return ret;
}
