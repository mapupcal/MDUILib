
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_BASEWINDOW_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_BASEWINDOW_H

#include"IWindow.hpp"
#include"Framework\Common\Utils\Utils.hpp"
#include"Framework\Common\Core\Object.hpp"
#include"Framework\Common\Core\Geometries\MRect.hpp"
#include"Framework\Common\Utils\MString.hpp"
#include"Framework\Common\Utils\MDelegate.hpp"
#include"Framework\Common\Core\Events.hpp"

namespace MDUILib
{
	class BaseWindow : m_extends Object, m_implements IWindow
	{
	public:
		/*
		*	@Attribute：WindowProcNotifyers
		*	@Remark:向相应的事件注册Notifyer，窗口发生相应事件时，将通知Notifyer。
		*	@Noted:注册的Notifyer必须具备Callable接口void(IWindows*,MEvent&),See Also class MEvent.
		*/
		using WindowProcNotifyers = DelegateNotifyers<IWindow*, MEvent&>;

		BaseWindow();
		// Inherited via IWindow
		virtual void InitWindow(const String & wndTitleName, const MRect & positionRect) override;
		virtual IWindow * CreateSubWindow(const String & subWndTitleName, const MRect & relativePositionRect, bool bModal = false) override;
		virtual void SetTitle(const String & wndTitleName) override;
		virtual String GetTitle() const override;
		virtual void Show() override;
		virtual void Resize(MUINT width, MUINT height) override;
		virtual void Maximize() override;
		virtual void Minimize() override;
		virtual void CenterWindow() override;
		virtual void Close() override;
		virtual void Move(MUINT pX, MUINT pY) override;
		virtual MHandleType GetNativeWindowHandle() const override;
		virtual MHandleType GetNativeRenderTarget() const override;
		virtual bool PreNativeEventFilter(const MNativeEvent & e) override;
		virtual bool IsModal() const override;
		virtual void SetTimer(int timerID, MUINT uElapse) override;
		virtual void KillTimer(int timerID) override;

		/*
		*	@Remark:获取矩形位置
		*/
		const MRect::data_type GetX() const;
		const MRect::data_type GetY() const;
		const MRect::data_type GetClientX() const;
		const MRect::data_type GetClientY() const;
		/*
		*	@Remark:获取窗口矩形属性、Client矩形属性。
		*/
		const MRect GetWndRect() const;
		const MRect GetClientRect() const;
		MRect::data_type GetWidth() const;
		MRect::data_type GetHeigth() const;
		MRect::data_type GetClientWidth()  const;
		MRect::data_type GetClientHeight()  const;
		//	@Remark:WindowNotifyers
		WindowProcNotifyers OnClose;
		WindowProcNotifyers OnSize;
		WindowProcNotifyers OnMove;
		WindowProcNotifyers OnMessage;
		WindowProcNotifyers OnTimer;
	protected:
		MRect m_WindowRect;
		MRect m_ClientRect;
		bool m_bModal;
		String m_WndTitle;
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_BASEWINDOW_H
