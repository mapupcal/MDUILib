#include "Framework\Common\Runtime\BaseApplication.hpp"
#include "WindowXXApplication.hpp"
#include <Windows.h>
#include "Framework\Common\Utils\Any.hpp"
#include "Windows\WinXXWindow.hpp"

#include "WindowXX\Graphics\Win7OrPlusRenderSystem.hpp"

namespace MDUILib
{
    WindowXXApplication g_App;
    BaseApplication* g_pApp = &g_App;
}

namespace MDUILib
{
	int WindowXXApplication::Initialize()
	{
		WinXXWindow *pWindow = new WinXXWindow();
		pWindow->InitWindow("???", { 0,100,0,100 });
		pWindow->Show();
		pWindow->OnClose += [&](IWindow* pWindow, MEvent*e)
		{
			this->Quit();
		};
		Win7OrPlusRenderSystem *pWin7RS = new Win7OrPlusRenderSystem();
		pWin7RS->BindTargetWindow(pWindow);
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