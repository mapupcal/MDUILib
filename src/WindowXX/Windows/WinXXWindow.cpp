#include "WinXXWindow.hpp"
#include <Windows.h>
#include <Windowsx.h>
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
	LRESULT WinXXWindow::__WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		LRESULT hr = 0;

		MNativeEvent ne;
		ne.hWnd = hWnd;
		ne.message = message;
		ne.wParam = wParam;
		ne.lParam = lParam;

		if (message == WM_CREATE)
		{
			//	@Commit:将IWindow与hWnd相关联。
			LPCREATESTRUCTA pcs = (LPCREATESTRUCTA)lParam;
			WinXXWindow *pWindow = static_cast<WinXXWindow*>(pcs->lpCreateParams);
			::SetWindowLongPtr(
				hWnd,
				GWLP_USERDATA,
				reinterpret_cast<long long>(pWindow)
			);
			hr = 1;
		}
		else
		{
			//	@Commit:获取和hWnd相关联的IWindow指针。
			WinXXWindow * pWindow = reinterpret_cast<WinXXWindow*>(
				static_cast<LONG_PTR>(
					::GetWindowLongPtr(
						hWnd,
						GWLP_USERDATA
					)
					)
				);
			//	@Commit:处理其它消息。
			bool wasHandled = false;
			if (pWindow)
			{
				if (pWindow->PreNativeEventFilter(ne))
				{
					return ::DefWindowProcA(hWnd, message, wParam, lParam);
				}

				switch (message)
				{
					//	@Commit:窗口移动
				case WM_MOVE:
				{
					RECT rc;
					//	@Commit:获取当前窗口的区域位置。
					::GetWindowRect(hWnd, &rc);
					//	@Commit：设置当前的m_WindowRect。
					MRect& rect = pWindow->m_WindowRect;
					rect = FromWinRect(rc);
					//	@Commit：通知OnMove注册的Notifyers
					ControlNotifyEvent e(
						ControlNotifyEvent::ControlNotifyEventType::CNET_MOVE,
						rect);

					for (const auto &handler : pWindow->OnMove)
						handler(pWindow, &e);
					wasHandled = true;
				}
				break;

				//	@Commit:窗口缩放
				case WM_SIZE:
				{
					RECT rc;
					//	@Commit:获取当前Window位置。
					::GetWindowRect(hWnd, &rc);
					//	@Commit:修改m_WindowRect。
					MRect& rect = pWindow->m_WindowRect;
					rect = FromWinRect(rc);
					//	@Commit:获取Client的区域。
					::GetClientRect(hWnd, &rc);
					pWindow->m_ClientRect = FromWinRect(rc);
					//	@Commit:通知OnSize注册的Notifyers
					ControlNotifyEvent e(ControlNotifyEvent::ControlNotifyEventType::CNET_SIZE,
						rect);
					for (const auto& handler : pWindow->OnSize)
						handler(pWindow, &e);
					wasHandled = true;
				}
				break;
				//	@Commit:窗口需要被重新绘制
				case WM_PAINT:
				{
					//	@Commit:重新绘制窗口由外部Handler负责。
					ControlNotifyEvent e(ControlNotifyEvent::ControlNotifyEventType::CNET_PAINT, 
						{0,0,0,0 });
					for (const auto &handler : pWindow->OnMessage)
						handler(pWindow, &e);

					::ValidateRect(hWnd, NULL);
					wasHandled = true;
				}
				break;
				//	@Commit:鼠标移动操作
				case WM_MOUSEMOVE:
					//	@Commit:鼠标停留
				case WM_MOUSEHOVER:
					//	@Commit:鼠标左键按下
				case WM_LBUTTONDOWN:
					//	@Commit:鼠标左键松开
				case WM_LBUTTONUP:
					//	@Commit:鼠标右键按下
				case WM_RBUTTONDOWN:
					//	@Commit:鼠标右键松开
				case WM_RBUTTONUP:
				{
					auto mouseX = GET_X_LPARAM(lParam);
					auto mouseY = GET_Y_LPARAM(lParam);
					MPoint ptMouse;
					ptMouse.x = mouseX;
					ptMouse.y = mouseX;
					MouseEvent::MouseEventType t;
					//	@Commit:see MSDN WM_MOUSEMOVE\WM_MOUSEHOVER wParam
					MDWORD keyState = static_cast<MWORD>(wParam);
					if (message == WM_MOUSEMOVE)
					{
						t = MouseEvent::MouseEventType::MET_MOVE;
					}
					else if (message == WM_MOUSEHOVER)
					{
						t = MouseEvent::MouseEventType::MET_HOVER;
					}
					else if (message == WM_LBUTTONDOWN)
					{
						t = MouseEvent::MouseEventType::MET_LBUTTON_DOWN;
					}
					else if (message == WM_LBUTTONUP)
					{
						t = MouseEvent::MouseEventType::MET_LBUTTON_UP;
					}
					else if (message == WM_RBUTTONDOWN)
					{
						t = MouseEvent::MouseEventType::MET_RBUTTON_DOWN;
					}
					else if (message == WM_RBUTTONUP)
					{
						t = MouseEvent::MouseEventType::MET_RBUTTON_UP;
					}
					MouseEvent e(ptMouse, t, keyState);
					for (const auto & handler : pWindow->OnMessage)
						handler(pWindow, &e);
					wasHandled = true;
				}
				break;
				//	@Commit:字符输入
				//	@Remark:统一转换成UTF16编码的字符返回，其UTF16编码的字符保存在e.chKey中
				case WM_CHAR:
				{
					wasHandled = true;
					wchar_t wch;
					//	@Remark:标记该输入字符是否为多字节编码的字符
					//	@Buggy:会不会造成多窗口的并发问题？
					static bool multiBytes = false;
					static char bytes[2];
					unsigned char byte = (unsigned char)(wParam);
					if (multiBytes)
					{
						//	@Commit:多字节输入
						bytes[1] = byte;
						wchar_t ch;
						::MultiByteToWideChar(::GetACP(), 0, bytes, 2, &ch, 1);
						wch = ch;
						multiBytes = false;
					}
					else
					{
						bytes[0] = byte;
						if (byte <= 127)
						{
							wch = byte;
						}
						else
						{
							multiBytes = true;
							break;
						}
					}
					KeyboardEvent e(KeyboardEvent::KeyboardEventType::KET_CHAR, wch);
					for (const auto &handler : pWindow->OnMessage)
						handler(pWindow, &e);
					wasHandled = true;
				}
				break;
				//	@Commit:窗口接收到关闭消息
				case WM_CLOSE:
				{
					//	@Commit:该窗口具备模态子窗口，抖动所有模态窗口以通知用户。
					if (!pWindow->m_ModalSubWnds.empty())
					{
						for (auto &w : pWindow->m_ModalSubWnds)
						{
							//w->Jitter();
							//TODO:以何种方式通知用户？
						}
						wasHandled = true;
					}
				}
				break;
				//	@Commit:计时器消息
				case WM_TIMER:
				{

					MWORD mwParam = wParam;	//TimerID;
					NotifyEvent e(NotifyEvent::NotifyEventType::NET_TIMER, pWindow, wParam);
					for (const auto &handler : pWindow->OnTimer)
						handler(pWindow, &e);
					wasHandled = true;
				}
				break;
				//	@Commit:窗口被销毁。
				case WM_DESTROY:
				{
					ControlNotifyEvent e(
						ControlNotifyEvent::ControlNotifyEventType::CNET_WINDOW_CLOSE,
						pWindow->m_WindowRect);
					for (const auto&handler : pWindow->OnClose)
						handler(pWindow, &e);
					wasHandled = true;
				}
				break;
				case WM_DISPLAYCHANGE:
				{
					::InvalidateRect(hWnd, NULL, FALSE);
					hr = 0;
					wasHandled = true;
				}

				break;
				default:
					break;
				}
			}
			if (!wasHandled)
			{
				hr = ::DefWindowProcA(hWnd, message, wParam, lParam);
			}
		}
		return hr;
	}
	HRESULT WinXXWindow::__Initialize(HWND hParent, const String & owndTitleName, const MRect & positionRect)
	{
		//	@Commit:注册Win平台的 window class.
		WNDCLASSEXA wcex = { sizeof(WNDCLASSEXA) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = &WinXXWindow::__WinProc;
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