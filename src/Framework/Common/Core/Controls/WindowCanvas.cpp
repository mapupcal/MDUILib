#include"WindowCanvas.hpp"
#include"ControlManager.hpp"
#include"Framework\Common\Core\Windows\BaseWindow.hpp"
#include"Framework\Common\Core\Graphics\IRenderSystem.hpp"

namespace MDUILib
{
	WindowCanvas::WindowCanvas(ControlManager * pManager)
		:BaseControl(nullptr)
	{
		m_pControlMgr = pManager;
		m_ContentColor = MColor::White;
		static_cast<BaseWindow*>(
			m_pControlMgr->GetHostWindow())->OnSize +=
			[&](IWindow *pWindow, MEvent*e)
		{
			ControlNotifyEvent* pcne = static_cast<ControlNotifyEvent*>(e);
			SetMarginRc(pcne->GetRect());
			SetBorderRc(pcne->GetRect());
			SetPaddingRc(pcne->GetRect());
			SetContentRc(pcne->GetRect());
		};
	}
	void WindowCanvas::OnMouseEnter()
	{
	}
	void WindowCanvas::OnMouseLeave()
	{
	}
	void WindowCanvas::OnPaint()
	{
		auto pRender = GetControlManager()->GetHostWindow()->GetRenderSystem();
		pRender->DrawBegin();
		pRender->FillRect(GetContentRc(), GetContentColor());
		pRender->DrawEnd();
	}
}