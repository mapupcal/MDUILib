#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_CONTROLMANAGER_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_CONTROLMANAGER_H

#include"Framework\Common\Core\Controls\IControl.hpp"
#include"Framework\Common\Core\Object.hpp"

namespace MDUILib
{
	//@Remarks:与顶层窗口协助，解析顶层窗口送达的系统事件。
	//			1.负责管理控件树（不参与控件树的生成，后期将由xml文件直接解析出控件树）
	//			2.分派控件事件给对应的控件。
	//			3.进行控件的绘制工作。
	//@Commit:	暂定方案：Contorl若没定制绘制自身的函数，将由ControlManager调用默认的绘制流程。ControlManager会逐一调用控件树上所有空间的OnPaint函数。

	m_interface IWindow;
	class WindowCanvas;

	class ControlManager : m_extends Object
	{
	public:
		ControlManager(IWindow* pWindow);
		virtual ~ControlManager();
		typedef IControl::IControlList IControlList;

		IWindow* GetHostWindow() const;
		//@Remarks:BindControl Tree.
		void SetControlRoot(IControl *pControlRoot);
		IControl* GetControlRoot() const;
		//@Remarks: This Method Will traverse the Control Tree,And Check
		//			the Control's IsUpdateNeeded Method.then call the OnPaint's Update Method if true retruned.
		void Paint();
		void Paint(IControl* pControl);
		IControl *FindContorlByName(const String &controlName);
		IControlList FindAllControlsByName(const String &controlName);
		IControl *GetControlMouseCurrentHitted() const;
		
		//@Remarks:Translate the MEvent From IWindow.
		void TranslateEvent(MEvent* e);
		virtual bool PreTranslateEvent(MEvent* e);
	private:
		WindowCanvas *m_pWindowCanvas;
		IControl *m_pControlMouseCurrentHitted;
		IWindow *m_pHostWindow;
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_CONTROLMANAGER_H