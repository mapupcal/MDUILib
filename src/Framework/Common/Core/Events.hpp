
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_EVENTS_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_EVENTS_H

/*
*	@Remarks:定义事件消息类型。
*/
#include"Geometries\MRect.hpp"
#include"Framework\Common\Utils\Utils.hpp"
#include"FrameWork\Common\Utils\MDelegate.hpp"
#include"Framework\Common\Core\Object.hpp"
#include"Framework\Interface\Interface.hpp"

#ifdef _WIN32
	#include <Windows.h>
#endif //_WIN32
namespace MDUILib
{
	namespace MKeyState
	{
		//MouseMove
		const MWORD kMK_NORMAL = 0x0000;		//正常状态
		const MWORD kMK_LBUTTON		= 0x0001;	//左键按下
		const MWORD kMK_RBUTTON		= 0x0002;	//右键按下
		const MWORD kMK_SHIFT		= 0x0004;	//shift
		const MWORD kMK_CONTROL		= 0x0008;	//ctrl
		const MWORD kMK_MBUTTON		= 0x0010;	//鼠标中键
		const MWORD kMK_XBUTTON1	= 0x0020;	//扩展鼠标1键
		const MWORD kMK_XBUTTON2	= 0x0040;	//扩展鼠标2建
	}
	enum class MEventType : int
	{
		ET_MOUSE,
		ET_KEYBOARD,
		ET_NOTIFY,
		ET_CONTROL_NOTIFY
	};

	/*
	*	@Remark:IControl负责处理解析相应的事件。
	*/

	class MEvent : m_extends Object
	{
	public:
		MEvent(MEventType et, Object* sender)
			:m_eventType(et),m_pSender(sender)	{}
		MEventType GetType() const
		{
			return m_eventType;
		}
		Object *GetSender() const
		{
			return m_pSender;
		}
	private:
		MEventType m_eventType;
		Object* m_pSender;
	};

	class MouseEvent : m_extends MEvent
	{
	public:
		enum class MouseEventType
		{
			MET_MOVE,
			MET_LEAVE,
			MET_ENTER,
			MET_HOVER,
			MET_LBUTTON_UP,
			MET_LBUTTON_DOWN,
			MET_RBUTTON_UP,
			MET_RBUTTON_DOWN,
			MET_SCROLL_WHEEL
		};

		MouseEvent(MPoint ptMouse, MouseEventType met, \
			MWORD wKeyState = MKeyState::kMK_NORMAL)
			:	MEvent(MEventType::ET_MOUSE,nullptr),
				m_ptMouse(ptMouse), m_wKeyState(wKeyState), m_MouseEventType(met)
		{

		}
		MPoint GetMousePos() const
		{
			return m_ptMouse;
		}
		MouseEventType GetMouseEventType() const
		{
			return m_MouseEventType;
		}
		MWORD GetKeyState() const
		{
			return m_wKeyState;
		}
	private:
		MPoint m_ptMouse;
		MWORD m_wKeyState;
		MouseEventType m_MouseEventType;
	};

	class KeyboardEvent : m_extends MEvent
	{
	public:
		enum class KeyboardEventType
		{
			KET_KEY_DOWN,
			KET_KEY_UP,
			KET_CHAR,
			KET_SYSCHAR
		};
		KeyboardEvent(KeyboardEventType ket, WCHAR chKey)
			: MEvent(MEventType::ET_KEYBOARD,nullptr),
			m_KBEventType(ket), m_ChKey(chKey){}
		WCHAR GetInputKey() const
		{
			return m_ChKey;
		}
		KeyboardEventType GetKeyboardEventType() const
		{
			return m_KBEventType;
		}
	private:
		WCHAR m_ChKey;//Remarks:如果是用户输入的字符，此字符为UTF_16编码的正常字符。
		KeyboardEventType m_KBEventType;
	};

	class NotifyEvent : m_extends MEvent
	{
	public:
		enum class NotifyEventType
		{
			NET_SETFOCUS,
			NET_KILLFOCUS,
			NET_TIMER,
			NET_NOTIFY,
			NET_COMMAND 
		};

		//@Remark:dwParam means that the param related with the NET.
		//		  extra params could pass by Object::SetProperty("XXXX",XXXX)
		NotifyEvent(NotifyEventType net, Object *sender, MDWORD dwParam)
			: MEvent(MEventType::ET_NOTIFY, sender), m_dwParam(dwParam),m_NotifyEventType(net){}
		NotifyEventType GetNotifyEventType() const
		{
			return m_NotifyEventType;
		}
		MDWORD GetParam() const
		{
			return m_dwParam;
		}
	private:
		MDWORD m_dwParam;
		NotifyEventType m_NotifyEventType;
	};

	class ControlNotifyEvent : m_extends MEvent
	{
	public:
		enum class ControlNotifyEventType
		{
			CNET_PAINT,
			CNET_MOVE,
			CNET_SIZE,
			CNET_WINDOW_CLOSE
		};
		ControlNotifyEvent(ControlNotifyEventType cnet, MRect rect)
			: MEvent(MEventType::ET_CONTROL_NOTIFY, nullptr), m_cnet(cnet),
			m_rect(rect){}
		ControlNotifyEventType GetControlNotifyEventType() const
		{
			return m_cnet;
		}
		MRect GetRect() const
		{
			return m_rect;
		}
	private:
		ControlNotifyEventType m_cnet;
		MRect m_rect;
	};

	struct IControl;

	/*
	*	@TemplateClassName:NotifyEvents<EventArgs>
	*	@Remark:控件某事件的回调注册器。
	*	@Noted:注意该类型允许重复注册某一个回调函数，这些回调函数会按照注册的顺序调用。
	*/
	template<typename EventArgs>
	using EventNotifyers = DelegateNotifyers<IControl*, EventArgs&>;

	/*
	*	@ClassName:tagNativeEvent
	*	@Remark:平台相关的事件。主要用于NativeEventFilter方法的参数。
	*/

	typedef struct tagMNativeEvent
	{
#ifdef _WIN32
		HWND hWnd;
		UINT message;
		WPARAM wParam;
		LPARAM lParam;
#endif // _WIN32

	} MNativeEvent;
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_EVENTS_H
