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
		auto pWndTitle = new Label(nullptr);
		pWndTitle->SetText("DemoAppBlahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblahblah");
		pWndTitle->SetTextAlignment(TextAlignmentType::TAT_LEFT);
		auto pCloseButton = new Button(nullptr);
		auto pMaximizeButton = new Button(nullptr);
		auto pMinimizeButton = new Button(nullptr);
		pCloseButton->SetText("x");
		pMaximizeButton->SetText("+");
		pMinimizeButton->SetText("-");
		auto InitRectSize = [](Label *pb, int width, int height)
		{
			pb->SetMarginRc(CreateRect(0, height, 0, width));
			pb->SetBorderRc(CreateRect(0, height, 0, width));
			pb->SetPaddingRc(CreateRect(0, height, 0, width));
			pb->SetContentRc(CreateRect(0, height, 0, width));
			pb->SetContentColor(MColor::Blue);
			pb->SetFocusMaskColor(MColor::Red);
			pb->SetTextSize(16);
			pb->SetBackGroundColor(MColor::Purple);
		};
		InitRectSize(pWndTitle, 400, 20);
		InitRectSize(pMaximizeButton, 20, 20);
		InitRectSize(pMinimizeButton, 20, 20);
		InitRectSize(pCloseButton, 20, 20);
		pWndTitle->SetFloating(true);
		pWndTitle->SetFloatAlignment(ControlFloatAlignmentType::CFAT_LEFT);
		pMaximizeButton->SetFloating(true);
		pMaximizeButton->SetFloatAlignment(ControlFloatAlignmentType::CFAT_RIGHT);
		pCloseButton->SetFloating(true);
		pCloseButton->SetFloatAlignment(ControlFloatAlignmentType::CFAT_RIGHT);
		pMinimizeButton->SetFloating(true);
		pMinimizeButton->SetFloatAlignment(ControlFloatAlignmentType::CFAT_RIGHT);

		//Bind Callback
		pCloseButton->OnClicked +=
			[=](IControl* pSelf, MEvent *e)
		{
			pWindow->Close();
		};
		pMaximizeButton->OnClicked +=
			[=](IControl* pSelf, MEvent *e)
		{
			pWindow->Maximize();
		};
		pMinimizeButton->OnClicked +=
			[=](IControl*pSelf, MEvent *e)
		{
			pWindow->Minimize();
		};
		auto *pHL = new HorizontalLayout();
		pHL->AddControl(pWndTitle);
		pHL->AddControl(pCloseButton);
		pHL->AddControl(pMaximizeButton);
		pHL->AddControl(pMinimizeButton);
		//pHL->SetFixedSize(pWndTitle->GetWidth() + pCloseButton->GetWidth() * 3, pWndTitle->GetHeight());
		pWindow->OnSize += [=](IWindow *p, MEvent *e)
		{
			pWndTitle->SetWidth(static_cast<BaseWindow*>(p)->GetClientWidth() - 3 * pCloseButton->GetWidth());
		};
		//pHL->SetStrech(5);
		pWindow->GetControlManager()->SetControlRoot(pHL);
		pWindow->GetControlManager()->SetBackgroundColor(MColor::Black);
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