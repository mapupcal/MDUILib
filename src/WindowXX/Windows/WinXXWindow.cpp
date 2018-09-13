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
		//	@Commit:����m_WindowRect����WndProc���档
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
			//	@Commit:��IWindow��hWnd�������
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
			//	@Commit:��ȡ��hWnd�������IWindowָ�롣
			WinXXWindow * pWindow = reinterpret_cast<WinXXWindow*>(
				static_cast<LONG_PTR>(
					::GetWindowLongPtr(
						hWnd,
						GWLP_USERDATA
					)
					)
				);
			//	@Commit:����������Ϣ��
			bool wasHandled = false;
			if (pWindow)
			{
				if (pWindow->PreNativeEventFilter(ne))
				{
					return ::DefWindowProcA(hWnd, message, wParam, lParam);
				}

				switch (message)
				{
					//	@Commit:�����ƶ�
				case WM_MOVE:
				{
					RECT rc;
					//	@Commit:��ȡ��ǰ���ڵ�����λ�á�
					::GetWindowRect(hWnd, &rc);
					//	@Commit�����õ�ǰ��m_WindowRect��
					MRect& rect = pWindow->m_WindowRect;
					rect = FromWinRect(rc);
					//	@Commit��֪ͨOnMoveע���Notifyers
					ControlNotifyEvent e(
						ControlNotifyEvent::ControlNotifyEventType::CNET_MOVE,
						rect);

					for (const auto &handler : pWindow->OnMove)
						handler(pWindow, &e);
					wasHandled = true;
				}
				break;

				//	@Commit:��������
				case WM_SIZE:
				{
					RECT rc;
					//	@Commit:��ȡ��ǰWindowλ�á�
					::GetWindowRect(hWnd, &rc);
					//	@Commit:�޸�m_WindowRect��
					MRect& rect = pWindow->m_WindowRect;
					rect = FromWinRect(rc);
					//	@Commit:��ȡClient������
					::GetClientRect(hWnd, &rc);
					pWindow->m_ClientRect = FromWinRect(rc);
					//	@Commit:֪ͨOnSizeע���Notifyers
					ControlNotifyEvent e(ControlNotifyEvent::ControlNotifyEventType::CNET_SIZE,
						rect);
					for (const auto& handler : pWindow->OnSize)
						handler(pWindow, &e);
					wasHandled = true;
				}
				break;
				//	@Commit:������Ҫ�����»���
				case WM_PAINT:
				{
					//	@Commit:���»��ƴ������ⲿHandler����
					ControlNotifyEvent e(ControlNotifyEvent::ControlNotifyEventType::CNET_PAINT, 
						{0,0,0,0 });
					for (const auto &handler : pWindow->OnMessage)
						handler(pWindow, &e);

					::ValidateRect(hWnd, NULL);
					wasHandled = true;
				}
				break;
				//	@Commit:����ƶ�����
				case WM_MOUSEMOVE:
					//	@Commit:���ͣ��
				case WM_MOUSEHOVER:
					//	@Commit:����������
				case WM_LBUTTONDOWN:
					//	@Commit:�������ɿ�
				case WM_LBUTTONUP:
					//	@Commit:����Ҽ�����
				case WM_RBUTTONDOWN:
					//	@Commit:����Ҽ��ɿ�
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
				//	@Commit:�ַ�����
				//	@Remark:ͳһת����UTF16������ַ����أ���UTF16������ַ�������e.chKey��
				case WM_CHAR:
				{
					wasHandled = true;
					wchar_t wch;
					//	@Remark:��Ǹ������ַ��Ƿ�Ϊ���ֽڱ�����ַ�
					//	@Buggy:�᲻����ɶര�ڵĲ������⣿
					static bool multiBytes = false;
					static char bytes[2];
					unsigned char byte = (unsigned char)(wParam);
					if (multiBytes)
					{
						//	@Commit:���ֽ�����
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
				//	@Commit:���ڽ��յ��ر���Ϣ
				case WM_CLOSE:
				{
					//	@Commit:�ô��ھ߱�ģ̬�Ӵ��ڣ���������ģ̬������֪ͨ�û���
					if (!pWindow->m_ModalSubWnds.empty())
					{
						for (auto &w : pWindow->m_ModalSubWnds)
						{
							//w->Jitter();
							//TODO:�Ժ��ַ�ʽ֪ͨ�û���
						}
						wasHandled = true;
					}
				}
				break;
				//	@Commit:��ʱ����Ϣ
				case WM_TIMER:
				{

					MWORD mwParam = wParam;	//TimerID;
					NotifyEvent e(NotifyEvent::NotifyEventType::NET_TIMER, pWindow, wParam);
					for (const auto &handler : pWindow->OnTimer)
						handler(pWindow, &e);
					wasHandled = true;
				}
				break;
				//	@Commit:���ڱ����١�
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
		//	@Commit:ע��Winƽ̨�� window class.
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