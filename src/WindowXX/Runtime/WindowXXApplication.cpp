#include "Framework\Common\Runtime\BaseApplication.hpp"
#include "WindowXXApplication.hpp"
#include <Windows.h>
#include "Framework\Common\Utils\Any.hpp"
#include "Windows\WinXXWindow.hpp"
#include "WindowXX\Graphics\Win7OrPlusRenderSystem.hpp"
#include "Framework\Common\Core\Controls\BaseControl.hpp"
#include "Framework\Common\Core\Controls\ControlManager.hpp"
#include "Windows\Win7OrPlusWindow.hpp"
namespace MDUILib
{
    WindowXXApplication g_App;
    BaseApplication* g_pApp = &g_App;
}

namespace MDUILib
{
	int WindowXXApplication::Initialize()
	{
		WinXXWindow *pWindow = new Win7OrPlusWindow();
		pWindow->InitWindow("???", { 0,100,0,100 });
		pWindow->Show();
		pWindow->OnClose += [&](IWindow* pWindow, MEvent*e)
		{
			this->Quit();
		};
		BaseControl *pControl = new BaseControl(nullptr);
		pControl->SetBorderRc(CreateRect(0, 100, 0, 100));
		pControl->SetPaddingRc(CreateRect(20, 80, 20, 80));
		pControl->SetContentRc(CreateRect(21, 79, 21, 79));
		pControl->SetBorderColor(MColor::WHITE);
		pControl->SetPaddingColor(MColor::BLUE);
		pControl->SetContentColor(MColor::GREEN);
		ControlManager* pManager =  pWindow->GetControlManager();
		pManager->SetControlRoot(pControl);
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