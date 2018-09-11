#include"BaseWindow.hpp"
#include"Common\Utils\Utils.hpp"

namespace MDUILib
{
	void BaseWindow::InitWindow(const String & wndTittleName, const MRect & positionRect)
	{
		MDUILIB_ASSERT_MSG(false,"Not Impl.");
	}
	IWindow * BaseWindow::CreateSubWindow(const String & subWndTittleName, const MRect & relativePositionRect, bool bModal /*= false*/)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
		return nullptr;
	}
	void BaseWindow::SetTittle(const String & wndTittleName)
	{
		MDUILIB_ASSERT(false);
	}
	String BaseWindow::GetTittle() const
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
		return String();
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
	bool BaseWindow::PostNativeEventFilter(const MNativeEvent & e)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
		return false;
	}
	bool BaseWindow::IsModal() const
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
		return false;
	}
	void BaseWindow::SetTimer(int timerID, MUINT uElapse)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}
	void BaseWindow::KillTimer(int timerID)
	{
		MDUILIB_ASSERT_MSG(false, "Not Impl.");
	}

	inline const MRect::data_type BaseWindow::GetX() const
	{
		return GetWndRect().left;
	}
	inline const MRect::data_type BaseWindow::GetY() const
	{
		return GetWndRect().top;
	}
	inline const MRect::data_type BaseWindow::GetClientX() const
	{
		return GetClientRect().left;
	}
	inline const MRect::data_type BaseWindow::GetClientY() const
	{
		return GetClientRect().top;
	}

	inline const MRect BaseWindow::GetWndRect() const
	{
		return m_WindowRect;
	}
	inline const MRect BaseWindow::GetClientRect() const
	{
		return m_ClientRect;
	}
	inline MRect::data_type BaseWindow::GetWidth() const
	{
		return GetRectWidth(GetWndRect());
	}
	inline MRect::data_type BaseWindow::GetHeigth() const
	{
		return GetRectHeight(GetWndRect());
	}
	inline MRect::data_type BaseWindow::GetClientWidth() const
	{
		return GetRectWidth(GetClientRect());
	}
	inline MRect::data_type BaseWindow::GetClientHeight() const
	{
		return GetRectHeight(GetClientRect());
	}
}