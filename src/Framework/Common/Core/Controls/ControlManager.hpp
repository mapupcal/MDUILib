#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_CONTROLMANAGER_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_CONTROLMANAGER_H

#include"Framework\Common\Core\Controls\IControl.hpp"
#include"Framework\Common\Core\Object.hpp"

namespace MDUILib
{
	//@Remarks:�붥�㴰��Э�����������㴰���ʹ��ϵͳ�¼���
	//			1.�������ؼ�����������ؼ��������ɣ����ڽ���xml�ļ�ֱ�ӽ������ؼ�����
	//			2.���ɿؼ��¼�����Ӧ�Ŀؼ���
	//			3.���пؼ��Ļ��ƹ�����
	//@Commit:	�ݶ�������Contorl��û���ƻ�������ĺ���������ControlManager����Ĭ�ϵĻ������̡�ControlManager����һ���ÿؼ��������пռ��OnPaint������

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