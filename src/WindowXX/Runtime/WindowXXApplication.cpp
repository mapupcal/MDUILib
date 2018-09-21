#include "Framework\Common\Runtime\BaseApplication.hpp"
#include "WindowXXApplication.hpp"
#include <Windows.h>
#include "Framework\Common\Utils\Any.hpp"
#include "Windows\WinXXWindow.hpp"
#include "WindowXX\Graphics\Win7OrPlusRenderSystem.hpp"
#include "Framework\Common\Core\Controls\BaseControl.hpp"
#include "Framework\Common\Core\Controls\ControlManager.hpp"
#include "Windows\Win7OrPlusWindow.hpp"
#include "Framework\Common\Core\Controls\Label.hpp"
#include "Framework\Common\Core\Controls\Button.hpp"
#include "Framework\Common\Core\Layouts\HorizontalLayout.hpp"
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
		Label *pLabel = new Label(nullptr);
		pLabel->SetText("Label");
		pLabel->SetTextSize(12);
		pLabel->SetContentRc(CreateRect(100, 150, 100, 150));
		pLabel->SetMarginRc(pLabel->GetContentRc());
		pLabel->SetPaddingRc(pLabel->GetContentRc());
		pLabel->SetBorderRc(pLabel->GetContentRc());
		pLabel->SetTextColor(MColor::Red);
		pLabel->SetBackGroundColor(MColor::Blue);
		Button *pControl = new Button(nullptr);
		pControl->OnClicked += [=](IControl*p, MEvent *e)
		{
			auto pChild = pWindow->CreateSubWindow("Popup", CreateRect(0, 150, 0, 150), true);
			pChild->Show();
		};
		pControl->SetText("Demo");
		pControl->SetMarginRc(CreateRect(18, 62, 18, 82));
		pControl->SetMarginColor(MColor::Red);
		pControl->SetBorderRc(CreateRect(19, 61, 19, 81));
		pControl->SetPaddingRc(CreateRect(20, 60, 20, 80));
		pControl->SetContentRc(CreateRect(21, 59, 21, 79));
		pControl->SetBorderColor(MColor::White);
		pControl->SetPaddingColor(MColor::Green);
		pControl->SetContentColor(MColor::Blue);
		HorizontalLayout *pLayout = new HorizontalLayout();
		pLayout->AddControl(pControl);
		pLayout->AddControl(pLabel);
		pLayout->SetFixedSize(480, 600);
		pControl->SetFloating(true);
		pControl->SetFloatAlignment(ControlFloatAlignmentType::CFAT_RIGHT);
		pLabel->SetFloating(true);
		pLabel->SetFloatAlignment(ControlFloatAlignmentType::CFAT_RIGHT);
		ControlManager* pManager =  pWindow->GetControlManager();
		pControl->SetVisible(true);
		pManager->SetControlRoot(pLayout);
		pManager->SetBackgroundColor(MColor::Green);
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