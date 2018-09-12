#include "Framework\Common\Runtime\BaseApplication.hpp"
#include "WindowXXApplication.hpp"
#include <Windows.h>
#include "Framework\Common\Utils\Any.hpp"
#include "Windows\WinXXWindow.hpp"

namespace MDUILib
{
    WindowXXApplication g_App;
    BaseApplication* g_pApp = &g_App;
}

namespace MDUILib
{
	int WindowXXApplication::Initialize()
	{
		auto pWindow = new WinXXWindow();
		pWindow->InitWindow("ABC", CreateRect(0, 100, 0, 100));
		pWindow->Show();
		return 0;
	}

	void WindowXXApplication::Finalize()
	{

	}

	void WindowXXApplication::Tick()
	{
		MSG msg;
		if (::GetMessage(&msg, NULL, 0, 0))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			return;
		}
		m_bQuit = true;
	}
}