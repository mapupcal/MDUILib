#include"Win7OrPlusWindow.hpp"
#include"WindowXX\Graphics\Win7OrPlusRenderSystem.hpp"

namespace MDUILib
{
	Win7OrPlusWindow::Win7OrPlusWindow()
	{
		m_pRenderSystem = new Win7OrPlusRenderSystem();
	}
	Win7OrPlusWindow::~Win7OrPlusWindow()
	{
		delete m_pRenderSystem;
	}
	IWindow * Win7OrPlusWindow::CreateSubWindow(const String & subWndTittleName, const MRect & relativePositionRect, bool bModal)
	{
		Win7OrPlusWindow *pChildWindow = new Win7OrPlusWindow();
		pChildWindow->InitWindow(subWndTittleName, Translate(relativePositionRect, GetX(), GetY()));
		pChildWindow->m_bModal = bModal;
		if (pChildWindow->IsModal())
		{
			m_ModalSubWnds.push_back(pChildWindow);
			pChildWindow->OnClose += [=](IWindow* pWindow, MEvent* e)
			{
				auto iter = std::find(this->m_ModalSubWnds.cbegin(), this->m_ModalSubWnds.cend(), pChildWindow);
				if (iter != this->m_ModalSubWnds.cend())
					this->m_ModalSubWnds.erase(iter);
			};
		}
		else
		{
			m_ModalessSubWnds.push_back(pChildWindow);
			pChildWindow->OnClose += [=](IWindow* pWindow, MEvent* e)
			{
				auto iter = std::find(this->m_ModalessSubWnds.cbegin(), this->m_ModalessSubWnds.cend(), pChildWindow);
				if (iter != this->m_ModalessSubWnds.cend())
					this->m_ModalessSubWnds.erase(iter);
			};
		}
		return pChildWindow;
	}
}