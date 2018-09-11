
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_IWINDOW_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_IWINDOW_H
/*
*	@Remark:������ƽ̨�޹صĴ��ڽӿ�
*/
#include"Common\Utils\MString.hpp"
#include"Common\Utils\MDelegate.hpp"
#include"Common\Core\Geometries/MRect.hpp"
#include"Common\Core\Events.hpp"
#include"Interface\Interface.hpp"
#include"Common\Core\IUnknown.hpp"

#define CRTII_NAME_IWINDOW "CRTII_WINDOW"

namespace MDUILib
{
	m_interface IWindow :
		m_implements IUnknown
	{
	public:

		virtual ~IWindow() {}
		virtual void InitWindow(const String &wndTittleName, const MRect &positionRect) = 0;
		virtual IWindow* CreateSubWindow(const String &subWndTittleName, \
			const MRect& relativePositionRect, bool bModal = false) = 0;
		virtual void SetTittle(const String& wndTittleName) = 0;
		virtual String GetTittle() const = 0;
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
		*	@Remarks:��ƽ̨��صĲ���MNativeEvent����ͬ��ϵͳ��ײ�ʵ�ֲ�ͬ��
		*/
		virtual bool PreNativeEventFilter(const MNativeEvent &e) = 0;
		virtual bool PostNativeEventFilter(const MNativeEvent &e) = 0;
		virtual bool IsModal() const = 0;
		/*
		*	@Remark:���ô���Timer��ÿ���uElapse���뽫����һ��EVENT_TIMER��Ϣ�����EVENT_TIMER����Ϣ������OnTimer�л�ȡ��
		*/
		virtual void SetTimer(int timerID, MUINT uElapse) = 0;
		virtual void KillTimer(int timerID) = 0;

		virtual AString GetInterfaceName() const override;
		virtual IUnknown* GetInterface(const AString& riiName) override
		{
			if (riiName.Compare(CRTII_NAME_IWINDOW) == 0)
				return this;
			return IUnknown::GetInterface(riiName);
		}
	};
}
#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_IWINDOW_H
