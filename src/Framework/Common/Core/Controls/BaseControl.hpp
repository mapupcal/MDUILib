
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_BASECONTROL_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_BASECONTROL_H

#include"IControl.hpp"
#include"Framework/Common/Utils/MDelegate.hpp"
#include "Framework/Common/Core/Object.hpp"
#include "Framework/Common/Core/Geometries/MRect.hpp"
#include "Framework/Common/Core/Graphics/MColor.hpp"

namespace MDUILib
{
	/*
	*	@Remark:盒子模型
	*	-------------------------------------
	*	|				 M					|
	*	|	-------------B---------------	|
	*	|	|			 P				|	|
	*	|	|	---------------------	|	|
	*	|	|	|					|	|	|
	*	| M	B P |		 C			| P	B M |
	*	|	|	|					|	|	|
	*	|	|	---------------------	|	|
	*	|	|			 P				|	|
	*	|	-------------B---------------	|
	*	|				 M					|
	*	-------------------------------------
	*	@Noted:	M Margin	外边界，由父控件负责绘制。
	*			B Border	边界
	*			P Padding	内边界
	*			C Content	内容，可以是图片，文本....
	*	@Noted:	这些Rect都是位于Client区域当中的位置
	*/
	enum class ControlFloatAlignmentType
	{
		CFAT_INVALID = 0,
		CFAT_LEFT,
		CFAT_RIGHT,
		CFAT_TOP,
		CFAT_BOTTOM
	};
	class BaseControl : m_extends Object, m_implements IControl
	{
	public:
		BaseControl(IControl *pParent);
		virtual ~BaseControl();
		typedef IControl::IControlList IControlList;
		typedef DelegateNotifyers<IControl*, MEvent*> EventNotifyerType;
		//Box Modal
		void SetContentRc(const MRect &rcContent);
		MRect GetContentRc() const;
		void SetPaddingRc(const MRect &rcPadding);
		MRect GetPaddingRc() const;
		void SetBorderRc(const MRect &rcBorder);
		MRect GetBorderRc() const;
		void SetMarginRc(const MRect &rcMargin);
		MRect GetMarginRc() const;
		//@Noted:	Floating 浮动，只有当控件被放入Layout中才会起作用。主要有四个方向的浮动：
		//			1.CFAT_LEFT:向左对齐的的浮动，控件总是在Layout中向左对齐。
		//			2.CFAT_RIGHT:向右对齐
		//			3.CFAT_TOP:向上对齐
		//			4.CFAT_BOTTOM:向下对齐
		//@Remark:	浮动使得控件的位置由其所属的Layout负责控制，一般Layout不会对控件的显示区域进行更改。
		void SetFloating(bool bFloat);
		bool GetFloating() const;
		void SetFloatAlignment(ControlFloatAlignmentType cfat);
		ControlFloatAlignmentType GetFloatAlignment() const;
		//Draw Color
		void SetContentColor(MColor color);
		MColor GetContentColor() const;
		void SetPaddingColor(MColor color);
		MColor GetPaddingColor() const;
		void SetBorderColor(MColor color);
		MColor GetBorderColor() const;
		void SetMarginColor(MColor color);
		MColor GetMarginColor() const;
		void SetFocusMaskColor(MColor color);
		MColor GetFocusMaskColor() const;

		bool IsMousePointerHitted(MPoint pt) const;
		
		//@Remark:获取相对于主窗口的相对位置，坐标轴为主窗口的左上角。
		void SetPos(MPoint pt);
		MPoint GetPos() const;
		//@Remark:获取相对与父控件的相对位置,坐标轴为父控件盒子Content的左上角（ContentRc.left,ContentRc.top）.
		void SetRelativePos(MPoint pt);
		MPoint GetRelativePos() const;

		MRect::data_type GetWidth() const;
		MRect::data_type GetHeight() const;

		//@Remark:EventFilter Method serve for Derived class.
		//		  OnEvent Serve for all Obj in the program.
		EventNotifyerType OnEvent;

		//Via IControl
		virtual void Init() override;
		virtual bool Active() const override;
		virtual void SetText(const String& text) override;
		virtual String GetText() const override;
		virtual void SetName(const String &name) override;
		virtual String GetName() const override;
		virtual void SetTooltip(const String& tooltip) override;
		virtual String GetToolTip() const override;
		virtual void SetImageName(const String& imageName) override;
		virtual String GetImageName() const override;
		virtual void SetFocus() override;
		virtual void KillFocus() override;
		virtual bool IsFocus() const override;
		virtual void SetUseContextMenu(bool bUseContextMenu) override;
		virtual bool IsUseContextMenu() const override;
		//Attributs
		virtual void SetVisible(bool bVisible) override;
		virtual bool GetVisible() const override;
		virtual void SetEnable(bool nEnable) override;
		virtual bool GetEnable() const override;
		//IControl UI Tree.
		virtual void SetParent(IControl *pParent) override;
		virtual IControl* GetParent() const override;
		virtual void AddChild(IControl* pChildren) override;
		virtual void RemoveChild(IControl* pChildren) override;
		virtual IControlList GetChildren() const override;
		//Aux Method.
		virtual IControl *FindChild(const String& name) override;
		virtual IControlList FindChildren(const String& name) override;
		virtual IControl *FindChild(const MPoint &pt) override;
		virtual IControlList FindChildren(const MPoint &pt) override;

		virtual void SetControlManager(ControlManager *pControlMgr) override;
		virtual ControlManager* GetControlManager() const override;
		//Draw
		void Paint();
		void PaintAll();
		virtual void OnPaint() override;
		virtual void Validate() override;
		virtual void Invalidate() override;
		virtual bool IsValidated() const override;
		virtual void NeedUpdate() override;
		virtual void NeedParentUpdate() override;
		virtual bool IsUpdateNeeded() const override;
		virtual void Update() override;
	protected:
		virtual bool EventFilter(MEvent *e) override;
		virtual void DoAcceptEvent(MEvent *e) override;
		virtual void OnMouseEnter() override;
		virtual void OnMouseLeave() override;
	protected:
		//Template Method.
		void AcceptEvent(MEvent *pEvent)
		{
			if (!EventFilter(pEvent))
			{
				DoAcceptEvent(pEvent);
				RaiseEvent(OnEvent, pEvent);
			}
		}
		//@Remark:If there is a Button Control that need to expose some callbak，like OnClicked.
		//		  try using the method as follow e.g.
		//			class Button : public BaseControl
		//			{	...
		//			public:
		//				DelegateNotifyers<IControl*,ButtonEvent*> OnClicked;
		//				public ... SomeSpecialFunc(...)
		//				{
		//					ButtonEvent e;
		//					RaiseEvent(OnClicked,&e);
		//				}
		//			}
		//			//Register your Callback.
		//			pButton->OnClicked += [](IControl* pWhich,ButtonEvent Event*)
		//			{ 
		//				...//Do your thing here.
		//			};
		template<typename EventArgs>
		void RaiseEvent(
			DelegateNotifyers<IControl*, EventArgs> &notifyers,
			EventArgs &eventArgs)
		{
			for (const auto& handler : notifyers)
				handler(this, eventArgs);
		}
	private:
		//Internal Method.
		IControlList __FindChildren_IF(const std::function<bool(IControl*)> &Preb);
	protected:
		MRect m_rcContent;
		MRect m_rcPadding;
		MRect m_rcBorder;
		MRect m_rcMargin;
		MColor m_ContentColor;
		MColor m_PaddingColor;
		MColor m_BorderColor;
		MColor m_MarginColor;

		MColor m_FocusMaskColor;

		IControl* m_pParent;
		IControlList m_lstpChildren;
		String m_szName;
		String m_szText;
		String m_szTooltip;
		String m_szImageName;

		bool m_bVisible;
		bool m_bEnable;
		bool m_bValidate;
		bool m_bUpdateNeeded;
		bool m_bFocus;
		bool m_bUseContextMenu;
		bool m_bFloating;
		ControlFloatAlignmentType m_ControlFloatingAlignmentType;
		ControlManager *m_pControlMgr;
	};

}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_BASECONTROL_H
