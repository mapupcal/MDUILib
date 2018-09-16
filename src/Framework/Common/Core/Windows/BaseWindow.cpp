#include"BaseWindow.hpp"
#include"Framework\Common\Core\Controls\ControlManager.hpp"
#include"Framework\Common\Core\Graphics\IRenderSystem.hpp"

namespace MDUILib
{
	BaseWindow::BaseWindow() {
		m_pControlManager = new ControlManager(this);
		OnMessage += [=](IWindow*, MEvent *e)
		{
			this->GetControlManager()->TranslateEvent(e);
		};
	}
	BaseWindow::~BaseWindow()
	{
		for (auto pW : m_ModalSubWnds)
		{
			delete pW;
		}

		for (auto pW : m_ModalessSubWnds)
		{
			delete pW;
		}
	}
	void BaseWindow::InitWindow(const String & wndTittleName, const MRect & positionRect)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	IWindow * BaseWindow::CreateSubWindow(const String & subWndTittleName, const MRect & relativePositionRect, bool bModal /*= false*/)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
		return nullptr;
	}
	void BaseWindow::SetTitle(const String & wndTittleName)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	String BaseWindow::GetTitle() const
	{
		return m_WndTitle;
	}
	void BaseWindow::Show()
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	void BaseWindow::Resize(MUINT width, MUINT height)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	void BaseWindow::Maximize()
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	void BaseWindow::Minimize()
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	void BaseWindow::CenterWindow()
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	void BaseWindow::Close()
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	void BaseWindow::Move(MUINT pX, MUINT pY)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	MHandleType BaseWindow::GetNativeWindowHandle() const
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
		return nullptr;
	}
	MHandleType BaseWindow::GetNativeRenderTarget() const
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
		return nullptr;
	}
	bool BaseWindow::PreNativeEventFilter(const MNativeEvent & e)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
		return false;
	}
	bool BaseWindow::IsModal() const
	{
		return m_bModal;
	}
	void BaseWindow::SetTimer(int timerID, MUINT uElapse)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	void BaseWindow::KillTimer(int timerID)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}

	ControlManager * BaseWindow::GetControlManager() const
	{
		return m_pControlManager;
	}

	IRenderSystem* BaseWindow::GetRenderSystem() const
	{
		return m_pRenderSystem;
	}

	const MRect::data_type BaseWindow::GetX() const
	{
		return GetWndRect().left;
	}
	const MRect::data_type BaseWindow::GetY() const
	{
		return GetWndRect().top;
	}
	const MRect::data_type BaseWindow::GetClientX() const
	{
		return GetClientRect().left;
	}
	const MRect::data_type BaseWindow::GetClientY() const
	{
		return GetClientRect().top;
	}

	const MRect BaseWindow::GetWndRect() const
	{
		return m_WindowRect;
	}
	const MRect BaseWindow::GetClientRect() const
	{
		return m_ClientRect;
	}
	MRect::data_type BaseWindow::GetWidth() const
	{
		return GetRectWidth(GetWndRect());
	}
	MRect::data_type BaseWindow::GetHeigth() const
	{
		return GetRectHeight(GetWndRect());
	}
	MRect::data_type BaseWindow::GetClientWidth() const
	{
		return GetRectWidth(GetClientRect());
	}
	MRect::data_type BaseWindow::GetClientHeight() const
	{
		return GetRectHeight(GetClientRect());
	}
}