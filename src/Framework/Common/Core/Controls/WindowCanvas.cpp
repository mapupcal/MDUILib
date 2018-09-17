#include"WindowCanvas.hpp"
#include"ControlManager.hpp"
#include"Common\Core\Windows\BaseWindow.hpp"

namespace MDUILib
{
	WindowCanvas::WindowCanvas(ControlManager * pManager)
		:BaseControl(nullptr)
	{
		m_pControlMgr = pManager;
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
	}
}