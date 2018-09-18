
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_IWINDOW_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_IWINDOW_H
/*
*	@Remark:定义与平台无关的窗口接口
*/
#include"FrameWork\Common\Utils\MString.hpp"
#include"FrameWork\Common\Utils\MDelegate.hpp"
#include"FrameWork\Common\Core\Geometries/MRect.hpp"
#include"FrameWork\Common\Core\Events.hpp"
#include"FrameWork\Interface\Interface.hpp"
#include"FrameWork\Common\Core\IUnknown.hpp"

namespace MDUILib
{
	class ControlManager;
	m_interface IRenderSystem;

	m_interface IWindow :
		m_implements IUnknown
	{
	public:

		virtual ~IWindow() {}
		virtual void InitWindow(const String &wndTittleName, const MRect &positionRect) = 0;
		virtual IWindow* CreateSubWindow(const String &subWndTitleName, \
			const MRect& relativePositionRect, bool bModal = false) = 0;
		virtual void SetTitle(const String& wndTitleName) = 0;
		virtual String GetTitle() const = 0;
		virtual void Show() = 0;
		virtual void Resize(MUINT width, MUINT height) = 0;
		virtual void Maximize() = 0;
		virtual void Minimize() = 0;
		virtual void CenterWindow() = 0;
		virtual void Close() = 0;
		virtual void Move(MUINT pX, MUINT pY) = 0;
		virtual MHandleType GetNativeWindowHandle() const = 0;
		virtual MHandleType GetNativeRenderTarget() const = 0;
		/*
		*	@Remarks:与平台相关的参数MNativeEvent，不同的系统其底层实现不同。
		*/
		virtual bool PreNativeEventFilter(const MNativeEvent &e) = 0;
		virtual bool IsModal() const = 0;
		/*
		*	@Remark:设置窗口Timer，每间隔uElapse毫秒将产生一个EVENT_TIMER消息，这个EVENT_TIMER的信息可以在OnTimer中获取。
		*/
		virtual void SetTimer(int timerID, MUINT uElapse) = 0;
		virtual void KillTimer(int timerID) = 0;

		//@Remark:提示用户某件事情发生，nCnt表示闪烁次数。
		virtual void FlashWindow(int nCnt) = 0;

		virtual ControlManager* GetControlManager() const = 0;
		virtual IRenderSystem* GetRenderSystem() const = 0;
		virtual AString GetInterfaceName() const override
		{
			return m_interface_name(IWindow);
		}
		virtual IUnknown* GetInterface(const AString& riiName) override
		{
			if (riiName.Compare(m_interface_name(IWindow)) == 0)
				return this;
			return IUnknown::GetInterface(riiName);
		}
	};
}
#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_IWINDOW_H
