#include "Button.hpp"
#include "ControlManager.hpp"
#include"Framework\Common\Core\Windows\IWindow.hpp"
#include "Framework\Common\Core\Graphics\IRenderSystem.hpp"
namespace MDUILib
{
	Button::Button(IControl * pParent)
		:Label(pParent)
		,m_bButtonDownIn(false)
	{
	}
	bool Button::EventFilter(MEvent * e)
	{
		if (e->GetType() == MEventType::ET_MOUSE)
		{
			MouseEvent* pme = static_cast<MouseEvent*>(e);
			if (pme->GetMouseEventType() == MouseEvent::MouseEventType::MET_LBUTTON_DOWN ||
				pme->GetMouseEventType() == MouseEvent::MouseEventType::MET_RBUTTON_DOWN)
			{
				m_bButtonDownIn = true;
				Update();
			}
			if (m_bButtonDownIn &&
				pme->GetMouseEventType() == MouseEvent::MouseEventType::MET_LBUTTON_UP ||
				pme->GetMouseEventType() == MouseEvent::MouseEventType::MET_RBUTTON_UP)
			{
				m_bButtonDownIn = false;
				Update();
				RaiseEvent(OnClicked, e);
			}
		}
		return true;
	}
	void Button::OnMouseEnter()
	{

	}
	void Button::OnMouseLeave()
	{
		m_bButtonDownIn = false;
		Update();
	}
	void Button::OnPaint()
	{
		auto pRender = GetControlManager()->GetHostWindow()->GetRenderSystem();
		pRender->FillRect(GetMarginRc(), GetMarginColor());
		pRender->FillRect(GetBorderRc(), GetBorderColor());
		pRender->FillRect(GetPaddingRc(), GetBorderColor());
		if (m_bButtonDownIn)
		{
			pRender->FillRect(GetContentRc(), GetFocusMaskColor());
		}
		else
		{
			pRender->FillRect(GetContentRc(), GetContentColor());
		}
		pRender->DrawTextString(GetContentRc(), GetText(), GetFont(), GetTextColor(), GetTextSize(), GetTextAlignment());
	}
	void Button::SetPushImage(const String & imgName)
	{
		m_szPushImageName = imgName;
	}
	String Button::GetPushImage() const
	{
		return m_szPushImageName;
	}
	void Button::SetForeImage(const String & imgName)
	{
		m_szForeImageName = imgName;
	}
	String Button::GetForImage() const
	{
		return m_szForeImageName;
	}
}