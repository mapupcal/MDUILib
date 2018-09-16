
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_ICONTROL_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_ICONTROL_H

#include"Framework\Interface\Interface.hpp"
#include"Framework/Common/Core/IUnknown.hpp"
#include"Framework/Common/Core/Events.hpp"

namespace MDUILib
{
	class ControlManager;

	m_interface IControl : m_implements IUnknown
	{
		typedef std::vector<IControl*> IControlList;
		typedef std::vector<IControl*>::size_type SizeType;
		//TODO:�ؼ��Ĺ����ӿ�
		virtual void Init() = 0;
		virtual bool Active() const = 0;
		virtual void SetText(const String& text) = 0;
		virtual String GetText() const = 0;
		virtual void SetName(const String &name) = 0;
		virtual String GetName() const = 0;
		virtual void SetTooltip(const String& tooltip) = 0;
		virtual String GetToolTip() const = 0;
		virtual void SetImageName(const String& imageName) = 0;
		virtual String GetImageName() const = 0;
		virtual void SetFocus() = 0;
		virtual void KillFocus() = 0;
		virtual bool IsFocus() const = 0;
		virtual void SetUseContextMenu(bool bUseContextMenu) = 0;
		virtual bool IsUseContextMenu() const = 0;
		//Attributs
		virtual void SetVisible(bool bVisible) = 0;
		virtual bool GetVisible() const = 0;
		virtual void SetEnable(bool nEnable) = 0;
		virtual bool GetEnable() const = 0;
		//IControl UI Tree.
		virtual void SetParent(IControl *pParent) = 0;
		virtual IControl* GetParent() const = 0;
		virtual void AddChild(IControl* pChildren) = 0;
		virtual void RemoveChild(IControl* pChildren) = 0;
		virtual IControlList GetChildren() const = 0;
		//Aux Method.
		virtual IControl *FindChild(const String& name) = 0;
		virtual IControlList FindChildren(const String& name) = 0;
		virtual IControl *FindChild(const MPoint &pt) = 0;
		virtual IControlList FindChildren(const MPoint &pt) = 0;
		//@Remarks:��ControlManager����
		virtual void SetControlManager(ControlManager *pControlMgr) = 0;
		virtual ControlManager* GetControlManager() const = 0;
		//Draw
		//@Remark:��������ؼ�Ӧ�ñ���λ��ơ��ײ���Ⱦģ��Ľ����ڴˡ�
		virtual void OnPaint() = 0;
		virtual void Validate() = 0;
		virtual void Invalidate() = 0;
		virtual bool IsValidated() const = 0;
		virtual void NeedUpdate() = 0;
		virtual void NeedParentUpdate() = 0;
		virtual bool IsUpdateNeeded() const = 0;
		//@Remark:��ǿ�Ƹ����ɸÿؼ�Ϊroot�����пؼ����ϵĽڵ㡣
		virtual void Update() = 0;
	protected:
		//Event
		//@Remark:�¼�����ؼ�ǰ���ɽ����¼����й��ˡ�
		//@Noted: ���ú�������true.��ʾ���¼��ѱ�������ˡ�
		virtual bool EventFilter(MEvent *e) = 0;
		//@Remark:��ܴ��ݸ��ÿؼ�ʱ��������ȷ�������¼���
		virtual void DoAcceptEvent(MEvent *e) = 0;
		//Aux Method.
		virtual void OnMouseEnter() = 0;
		virtual void OnMouseLeave() = 0;

	public:
		AString GetInterfaceName() const override
		{
			return m_interface_name(IControl);
		}
		IUnknown* GetInterface(const AString &riiName) override
		{
			if (riiName.Compare(m_interface_name(IControl)))
				return this;
			return IUnknown::GetInterface(riiName);
		}

		friend class ControlManager;
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_ICONTROL_H
