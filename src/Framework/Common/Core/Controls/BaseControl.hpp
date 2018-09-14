
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_BASECONTROL_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_BASECONTROL_H

#include"IControl.hpp"
#include"Framework/Common/Utils/MDelegate.hpp"
#include "Framework/Common/Core/Object.hpp"
#include "Framework/Common/Core/Geometries/MRect.hpp"
#include "Framework/Common/Core/Graphics/MColor.hpp"

namespace MDUILib
{
	//@Remark:Box Modal.

	class BaseControl : m_extends Object, m_implements IControl
	{
	public:
		BaseControl(IControl *pParent);
		typedef IControl::IControlList IControlList;
		typedef DelegateNotifyers<IControl*,MEvent*> EventNotifyerType;
		//Box Modal
		void SetContentRc(const MRect &rcContent);
		MRect GetContetnRc() const;
		void SetPaddingRc(const MRect &rcPadding);
		MRect GetPaddingRc() const;
		void SetBorderRc(const MRect &rcBorder);
		MRect GetBorderRc() const;
		void SetMarginRc(const MRect &rcMargin);
		MRect GetMarginRc() const;

		//Draw Color
		void SetContentColor(MColor color);
		MColor GetContentColor() const;
		void SetPaddingColor(MColor color);
		MColor GetPaddingColor() const;
		void SetBorderColor(MColor color);
		MColor GetBorderColor() const;
		void SetMarginColor(MColor color);
		MColor GetMarginColor()const;

		//@Remark:获取相对于主窗口的相对位置，坐标轴为主窗口的左上角。
		MPoint GetPos() const;
		//@Remark:获取相对与父控件的相对位置,坐标轴为父控件盒子Content的左上角（ContentRc.left,ContentRc.top）.
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
		virtual void SetFocus() override;
		virtual void KillFocus() override;
		virtual bool IsFocus() const override;
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

		//Draw
		virtual void OnPaint() override;
		virtual void Validate() override;
		virtual void Invalidate() override;
		virtual bool IsValidated() const override;
		virtual void NeedUpdate() override;
		virtual bool IsUpdateNeeded() const override;
		virtual void Update() override;
	protected:
		virtual bool EventFilter(MEvent *e) override;
		virtual void DoAcceptEvent(MEvent *e) override;

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
			const DelegateNotifyers<IControl*, EventArgs*> &notifyers,
			EventArgs *pEventArgs)
		{
			for (const auto handler : notifyers)
				handler(this, pEventArgs);
		}
	private:
		//Internal Method.
		IControlList __FindChildren_IF(const std::function<bool(IControl*)>& Preb);
	protected:
		MRect m_rcContent;
		MRect m_rcPadding;
		MRect m_rcBorder;
		MRect m_rcMargin;
		MColor m_ContentColor;
		MColor m_PaddingColor;
		MColor m_BorderColor;
		MColor m_MarginColor;

		IControl* m_pParent;
		IControlList m_lstpChildren;
		String m_szName;
		String m_szText;
		String m_szTooltip;

		bool m_bVisible;
		bool m_bEnable;
		bool m_bValidate;
		bool m_bUpdateNeeded;
		bool m_bFocus;
	};

}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_BASECONTROL_H
