#include "WinXXWindow.hpp"

namespace MDUILib
{
	void WinXXWindow::InitWindow(const String & wndTitleName, const MRect & positionRect)
	{
		MDUILIB_ASSERT_MSG(
			SUCCEEDED(__Initialize(NULL, wndTitleName, positionRect)),
			"Failed to Initialize Windows Platform Windows!");
		m_WndTitle = wndTitleName;
		m_bModal = false;
		
		RECT rect;
		::GetClientRect(m_hWnd, &rect);
		m_ClientRect = FromWinRect(rect);
		::GetWindowRect(m_hWnd, &rect);
		m_WindowRect = FromWinRect(rect);
	}
	IWindow * WinXXWindow::CreateSubWindow(const String & subWndTittleName, \
		const MRect & relativePositionRect, bool bModal /*= false*/)
	{
		MDUILIB_ASSERT_MSG(true, "Not impl.");
		return nullptr;
	}
	void WinXXWindow::SetTitle(const String & wndTitleName)
	{
		std::string title = wndTitleName.ToStdString();
		::SetWindowTextA(m_hWnd,title.c_str());
		m_WndTitle = wndTitleName;
	}
	void WinXXWindow::Show()
	{
		if (m_hWnd)
		{
			::ShowWindow(m_hWnd, SW_SHOWNORMAL);
			::UpdateWindow(m_hWnd);
		}
		else
		{
			MDUILIB_OUT_ERROR("WinXXWindow Object has not been initialized.");
		}
	}
	void WinXXWindow::Resize(MUINT width, MUINT height)
	{
		::MoveWindow(m_hWnd, m_WindowRect.left, m_WindowRect.top,
			width, height, true);
	}
	void WinXXWindow::Maximize()
	{
		if (m_hWnd)
		{
			::ShowWindow(m_hWnd, SW_MAXIMIZE);
			::UpdateWindow(m_hWnd);
		}
		else
		{
			MDUILIB_OUT_ERROR("WinXXWindow Object has not been initialized.");
		}
	}
	void WinXXWindow::Minimize()
	{
		if (m_hWnd)
		{
			::ShowWindow(m_hWnd, SW_MINIMIZE);
		}
		else
		{
			MDUILIB_OUT_ERROR("WinXXWindow Object has not been initialized.");
		}
	}
	void WinXXWindow::CenterWindow()
	{

	}
	void WinXXWindow::Close()
	{
		if (m_hWnd)
		{
			::DestroyWindow(m_hWnd);
			m_hWnd = NULL;
		}
	}
	void WinXXWindow::Move(MUINT pX, MUINT pY)
	{
		auto xOffset = m_WindowRect.left - pX;
		auto yOffset = m_WindowRect.top - pY;
		//	@Commit:更改m_WindowRect将在WndProc里面。
		::MoveWindow(m_hWnd, pX, pY, \
			GetRectWidth(m_WindowRect), GetRectHeight(m_WindowRect), false);
	}
	MHandleType WinXXWindow::GetNativeWindowHandle() const
	{
		return static_cast<MHandleType>(m_hWnd);
	}
	MHandleType WinXXWindow::GetNativeRenderTarget() const
	{
		return nullptr;
	}
	bool WinXXWindow::PreNativeEventFilter(const MNativeEvent & e)
	{
		return false;
	}

	void WinXXWindow::SetTimer(int timerID, MUINT uElapse)
	{
		if (m_hWnd)
		{
			::SetTimer(m_hWnd, timerID, uElapse, NULL);
		}
		else
		{
			MDUILIB_OUT_ERROR("WARNNING:WinXXWindow has not been initialized.");
		}
	}
	void WinXXWindow::KillTimer(int timerID)
	{
		if (m_hWnd != NULL)
		{
			BOOL result = ::KillTimer(m_hWnd, timerID);
			MDUILIB_ASSERT_MSG(result, "WARNNING:This Timer ID Not Exsited.");
		}
		else
		{
			MDUILIB_OUT_ERROR("WARNNING:WinXXWindow has not been initialized.");
		}
	}
	HRESULT WinXXWindow::__WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return ::DefWindowProc(hWnd, message, wParam, lParam);
	}
	HRESULT WinXXWindow::__Initialize(HWND hParent, const String & owndTitleName, const MRect & positionRect)
	{
		//	@Commit:注册Win平台的 window class.
		WNDCLASSEXA wcex = { sizeof(WNDCLASSEXA) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WinXXWindow::__WinProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = NULL;
		wcex.hIcon = NULL;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursorA(NULL, IDI_APPLICATION);
		wcex.lpszClassName = "MDUILIB_WINDOW";
		RegisterClassExA(&wcex);

		auto title = owndTitleName.ToStdString();

		m_hWnd = CreateWindowEx(
			0,
			"MDUILIB_WINDOW",
			title.c_str(),
			WS_OVERLAPPEDWINDOW,
			static_cast<UINT>(positionRect.left),
			static_cast<UINT>(positionRect.top),
			static_cast<UINT>(GetRectWidth(positionRect)),
			static_cast<UINT>(GetRectHeight(positionRect)),
			hParent,
			NULL,
			NULL,
			this
		);
		auto hr = m_hWnd ? S_OK : E_FAIL;
		MDUILIB_ASSERT_MSG(SUCCEEDED(hr), "Failed Create Window Platform Windows.");
		return hr;
	}
}