
#ifndef MDUILIB_WINDOWXX_WINDOWS_WINXXWINDOW_H
#define MDUILIB_WINDOWXX_WINDOWS_WINXXWINDOW_H

#include"Framework\Common\Core\Windows\BaseWindow.hpp"
#include"Framework\Interface\Interface.hpp"

namespace MDUILib
{
	class WinXXWindow : m_extends BaseWindow
	{
	public:
		WinXXWindow();
		~WinXXWindow();
		virtual void InitWindow(const String & wndTitleName, const MRect & positionRect) override;
		virtual IWindow * CreateSubWindow(const String & subWndTittleName, const MRect & relativePositionRect, bool bModal = false) override;
		virtual void SetTitle(const String & wndTittleName) override;
		virtual void Show() override;
		virtual void Resize(MUINT width, MUINT height) override;
		virtual void Maximize() override;
		virtual void Minimize() override;
		virtual void CenterWindow() override;
		virtual void Close() override;
		virtual void Move(MUINT pX, MUINT pY) override;
		virtual MHandleType GetNativeWindowHandle() const override;
		virtual MHandleType GetNativeRenderTarget() const override;
		virtual bool PreNativeEventFilter(const MNativeEvent &e) override;
		virtual void SetTimer(int timerID, MUINT uElapse) override;
		virtual void KillTimer(int timerID) override;
		virtual void FlashWindow(int nCnt) override;
	private:
		static LRESULT CALLBACK __WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		virtual HRESULT __Initialize(HWND hParent, const String &owndTitleName,const MRect& positionRect);
	protected:
		HWND m_hWnd;

		//@Remark:为了产生WM_MOUSELEVE\WM_MOUSEHOVER消息，然后利用这两个消息生成自定义的Enter事件
	private:
		bool m_bMouseNowInClientRect;
		bool m_bIsMouseTracking;

		void __StartMouseTracking();
	};
}

#endif // !MDUILIB_WINDOWXX_WINDOWS_WINXXWINDOW_H
