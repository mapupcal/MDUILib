
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_EVENTS_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_EVENTS_H

/*
*	@Remarks:定义事件消息类型。
*/
#include"Geometries\MRect.hpp"
#include"Common\Utils\Utils.hpp"
#include"Common\Utils\MDelegate.hpp"
#ifdef _WIN32
	#include <Windows.h>
#endif //_WIN32
namespace MDUILib
{
	namespace MKeyState
	{
		//MouseMove
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
		//Keyboard
		EVENT_KEY_DOWN = 1,
		EVENT_KEY_UP,
		EVENT_CHAR,
		EVENT_SYSKEY,
		//mouse
		EVENT_MOUSE_MOVE,
		EVENT_MOUSE_LEAVE,
		EVENT_MOUSE_ENTER,
		EVENT_MOUSE_HOVER,
		EVENT_LBUTTON_UP,
		EVENT_LBUTTON_DOWN,
		EVENT_RBUTTON_UP,
		EVENT_RBUTTON_DOWN,
		EVENT_L_DOUBLE_CLICK,
		EVENT_CONTEX_MENU,
		EVENT_SCROLL_WHEEL,
		//Window Event
		EVENT_WINDOW_PAINT,
		EVENT_WINDOW_SIZE,
		EVENT_WINDOW_MOVE,
		//other notifier event
		EVENT_SETFOCUS,
		EVENT_KILLFOCUS,
		EVENT_SETCURSOR,
		EVENT_TIMER,
		EVENT_NOTIFY,
		EVENT_COMMAND
	};

	/*
	*	@Remark:MDUILib内部使用的事件结构。
	*	@Remark:IControl负责处理解析相应的事件。
	*/

	typedef struct tagMEvent
	{
		MEventType Type;
		MDWORD dwTimestamp;
		MPoint ptMouse;
		MCHAR chKey;
		MWORD wKeyState;
		MWPARAM wParam;
		MLPARAM lParam;
	} MEvent;

	class IControl;

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
