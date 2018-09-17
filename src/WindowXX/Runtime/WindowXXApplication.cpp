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
		pWindow->OnClose += [&](IWindow* pWindow, MEvent*e)
		{
			this->Quit();
		};
		BaseControl *pControl = new BaseControl(nullptr);
		pControl->SetText("Demo");
		pControl->SetMarginRc(CreateRect(18, 62, 18, 82));
		pControl->SetMarginColor(MColor::RED);
		pControl->SetBorderRc(CreateRect(19, 61, 19, 81));
		pControl->SetPaddingRc(CreateRect(20, 60, 20, 80));
		pControl->SetContentRc(CreateRect(21, 59, 21, 79));
		pControl->SetBorderColor(MColor::WHITE);
		pControl->SetPaddingColor(MColor::GREEN);
		pControl->SetContentColor(MColor::BLUE);
		ControlManager* pManager =  pWindow->GetControlManager();
		pControl->SetVisible(true);
		pManager->SetControlRoot(pControl);
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