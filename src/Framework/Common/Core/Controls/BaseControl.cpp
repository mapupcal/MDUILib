#include"BaseControl.hpp"
#include<algorithm>
#include "Framework/Common/Core/Controls/ControlManager.hpp"
#include "Framework/Common/Core/Windows/IWindow.hpp"
#include "Framework/Common/Core/Graphics/IRenderSystem.hpp"
#include "Framework\Common\Core\Graphics\MFont.hpp"
namespace MDUILib
{
	BaseControl::BaseControl(IControl * pParent)
		:m_rcContent(MRect::ZERO_RECT)
		,m_rcPadding(MRect::ZERO_RECT)
		,m_rcBorder(MRect::ZERO_RECT)
		,m_rcMargin(MRect::ZERO_RECT)
		,m_ContentColor(MColor::White)
		,m_PaddingColor(MColor::White)
		,m_BorderColor(MColor::White)
		,m_MarginColor(MColor::White)
		,m_FocusMaskColor(MColor::White)
		,m_pControlMgr(nullptr)
		,m_pParent(nullptr)
		,m_bUpdateNeeded(false)
		,m_bEnable(true)
		,m_bVisible(true)
		,m_bValidate(false)
		,m_bUseContextMenu(false)
		,m_bFocus(false)
		,m_bFloating(false)
	{
		if (pParent)
		{
			pParent->AddChild(this);
			m_pParent = pParent;
		}
	}
	BaseControl::~BaseControl()
	{
		//@Remark:It's the Parent responsibility to release the child's shit.
		for (auto child : m_lstpChildren)
		{
			delete child;
		}
	}
	void BaseControl::SetContentRc(const MRect & rcContent)
	{
		m_rcContent = rcContent;
	}
	MRect BaseControl::GetContentRc() const
	{
		return m_rcContent;
	}
	void BaseControl::SetPaddingRc(const MRect & rcPadding)
	{
		m_rcPadding = rcPadding;
	}
	MRect BaseControl::GetPaddingRc() const
	{
		return m_rcPadding;
	}
	void BaseControl::SetBorderRc(const MRect & rcBorder)
	{
		m_rcBorder = rcBorder;
	}
	MRect BaseControl::GetBorderRc() const
	{
		return m_rcBorder;
	}
	void BaseControl::SetMarginRc(const MRect & rcMargin)
	{
		m_rcMargin = rcMargin;
	}
	MRect BaseControl::GetMarginRc() const
	{
		return m_rcMargin;
	}
	void BaseControl::SetFloating(bool bFloat)
	{
		m_bFloating = bFloat;
	}
	bool BaseControl::GetFloating() const
	{
		return m_bFloating;
	}
	void BaseControl::SetFloatAlignment(ControlFloatAlignmentType cfat)
	{
		m_ControlFloatingAlignmentType = cfat;
	}
	ControlFloatAlignmentType BaseControl::GetFloatAlignment() const
	{
		return m_ControlFloatingAlignmentType;
	}
	void BaseControl::SetContentColor(MColor color)
	{
		m_ContentColor = color;
	}
	MColor BaseControl::GetContentColor() const
	{
		return m_ContentColor;
	}
	void BaseControl::SetPaddingColor(MColor color)
	{
		m_PaddingColor = color;
	}
	MColor BaseControl::GetPaddingColor() const
	{
		return m_PaddingColor;
	}
	void BaseControl::SetBorderColor(MColor color)
	{
		m_BorderColor = color;
	}
	MColor BaseControl::GetBorderColor() const
	{
		return m_BorderColor;
	}
	void BaseControl::SetMarginColor(MColor color)
	{
		m_MarginColor = color;
	}
	MColor BaseControl::GetMarginColor() const
	{
		return m_MarginColor;
	}
	void BaseControl::SetFocusMaskColor(MColor color)
	{
		m_FocusMaskColor = color;
	}
	MColor BaseControl::GetFocusMaskColor() const
	{
		return m_FocusMaskColor;
	}
	bool BaseControl::IsMousePointerHitted(MPoint pt) const
	{
		return IsPointInRect(pt, GetBorderRc());
	}
	MPoint BaseControl::GetPos() const
	{
		return MPoint(GetContentRc().left, GetContentRc().top);
	}
	MPoint BaseControl::GetRelativePos() const
	{
		if (m_pParent)
		{
			MPoint parentPt = (static_cast<BaseControl*>(m_pParent))->GetPos();
			return GetPos() - parentPt;
		}
		return { 0,0 };
	}
	MRect::data_type BaseControl::GetWidth() const
	{
		return GetRectWidth(m_rcContent);
	}
	MRect::data_type BaseControl::GetHeight() const
	{
		return GetRectHeight(m_rcContent);
	}
	bool BaseControl::EventFilter(MEvent *e)
	{
		return false;
	}
	void BaseControl::DoAcceptEvent(MEvent * e)
	{
		typedef MouseEvent::MouseEventType MET;
		typedef KeyboardEvent::KeyboardEventType KET;
		typedef NotifyEvent::NotifyEventType NET;
		typedef ControlNotifyEvent::ControlNotifyEventType CNET;

		//TODO:远远未完成的事件解析函数。
		switch (e->GetType())
		{
		case MEventType::ET_MOUSE:
		{
			MouseEvent *pme = static_cast<MouseEvent*>(e);
		}
			break;
		case MEventType::ET_KEYBOARD:
			break;
		case MEventType::ET_NOTIFY:
		{
			NotifyEvent *pne = static_cast<NotifyEvent*>(e);
			if (pne->GetNotifyEventType() == NET::NET_SETFOCUS)
			{
				SetFocus();
			}
			else if (pne->GetNotifyEventType() == NET::NET_KILLFOCUS)
			{
				KillFocus();
			}
		}
			break;
		case MEventType::ET_CONTROL_NOTIFY:
		{
			ControlNotifyEvent *pcne = static_cast<ControlNotifyEvent*>(e);
			if (pcne->GetControlNotifyEventType() == CNET::CNET_PAINT)
			{
				Update();
			}
		}
			break;
		default:
			break;
		}
	}
	void BaseControl::OnMouseEnter()
	{
		printf("Not Impl.BaseControl::OnMouseEnter()!");
	}
	void BaseControl::OnMouseLeave()
	{
		printf("Not Impl.BaseControl::OnMouseLeave()!");
	}
	BaseControl::IControlList BaseControl::__FindChildren_IF(const std::function<bool(IControl*)> &Preb)
	{
		IControlList matchedChildren;
		auto iter = m_lstpChildren.cbegin();
		while (iter != m_lstpChildren.cend())
		{
			iter = std::find_if(m_lstpChildren.cbegin(), m_lstpChildren.cend(), Preb);
			if (iter != m_lstpChildren.cend())
			{
				matchedChildren.push_back(*iter);
				iter++;
			}
		}
		return matchedChildren;
	}
	void BaseControl::Init()
	{
		//TODO:
	}
	bool BaseControl::Active() const
	{
		return false;
	}
	void BaseControl::SetText(const String & text)
	{
		m_szText = text;
	}
	String BaseControl::GetText() const
	{
		return m_szText;
	}
	void BaseControl::SetName(const String & name)
	{
		m_szName = name;
	}
	String BaseControl::GetName() const
	{
		return m_szName;
	}
	void BaseControl::SetTooltip(const String & tooltip)
	{
		m_szTooltip = tooltip;
	}
	String BaseControl::GetToolTip() const
	{
		return m_szTooltip;
	}
	void BaseControl::SetImageName(const String & imageName)
	{
		m_szImageName = imageName;
	}
	String BaseControl::GetImageName() const
	{
		return m_szImageName;
	}
	void BaseControl::SetFocus()
	{
		m_bFocus = true;
	}
	void BaseControl::KillFocus()
	{
		m_bFocus = false;
	}
	bool BaseControl::IsFocus() const
	{
		return m_bFocus;
	}
	void BaseControl::SetUseContextMenu(bool bUseContextMenu)
	{
		m_bUseContextMenu = bUseContextMenu;
	}
	bool BaseControl::IsUseContextMenu() const
	{
		return m_bUseContextMenu;
	}
	void BaseControl::SetVisible(bool bVisible)
	{
		m_bVisible = bVisible;
	}
	bool BaseControl::GetVisible() const
	{
		return m_bVisible;
	}
	void BaseControl::SetEnable(bool nEnable)
	{
		m_bEnable = nEnable;
	}

	bool BaseControl::GetEnable() const
	{
		return m_bEnable;
	}
	void BaseControl::SetParent(IControl * pParent)
	{
		if (m_pParent)
		{
			m_pParent->RemoveChild(this);
		}
		m_pParent = pParent;
		m_pParent->AddChild(this);
		SetControlManager(pParent->GetControlManager());
	}
	IControl * BaseControl::GetParent() const
	{
		return m_pParent;
	}
	void BaseControl::AddChild(IControl * pChild)
	{
		if (pChild && pChild->GetParent() != this)
		{
			pChild->SetParent(this);
			m_lstpChildren.push_back(pChild);
		}
	}
	void BaseControl::RemoveChild(IControl * pChild)
	{
		auto iter = std::find(m_lstpChildren.cbegin(), m_lstpChildren.cend(), pChild);
		if (iter == m_lstpChildren.cend())
		{
			m_lstpChildren.erase(iter);
		}
	}
	BaseControl::IControlList BaseControl::GetChildren() const
	{
		return m_lstpChildren;
	}
	IControl * BaseControl::FindChild(const String & name)
	{
		auto iter = std::find_if(m_lstpChildren.cbegin(), m_lstpChildren.cend(),
			[=](const IControl* p) ->bool
			{
			return (name.Compare(p->GetName()) == 0);
			});

		if (iter != m_lstpChildren.cend())
		{
			return *iter;
		}
		return nullptr;
	}
	BaseControl::IControlList BaseControl::FindChildren(const String & name)
	{
		return __FindChildren_IF(
			[=](IControl* p) -> bool
			{
				return (name.Compare(p->GetName()) == 0);
			});
	}

	IControl * BaseControl::FindChild(const MPoint & pt)
	{
		for (auto p : m_lstpChildren)
		{
			if (static_cast<const BaseControl*>(p)->IsMousePointerHitted(pt))
			{
				return p;
			}
		}
		return nullptr;
	}

	BaseControl::IControlList BaseControl::FindChildren(const MPoint & pt)
	{
		return __FindChildren_IF(
			[=](IControl* p)
			{
				return static_cast<const BaseControl*>(p)->IsMousePointerHitted(pt);
			});
	}

	void BaseControl::SetControlManager(ControlManager * pControlMgr)
	{
		m_pControlMgr = pControlMgr;
		for (auto pChild : m_lstpChildren)
		{
			pChild->SetControlManager(m_pControlMgr);
		}
	}

	ControlManager * BaseControl::GetControlManager() const
	{
		return m_pControlMgr;
	}

	void BaseControl::Paint()
	{
		GetControlManager()->Paint(this);
	}

	//@Remark:控件应该在自己绘制自身。
	//		  e.g.auto pRender = GetControlManager()->GetRenderSystem();
	//			  //Do some thing draw.
	void BaseControl::OnPaint()
	{
		auto pRender = GetControlManager()->GetHostWindow()->GetRenderSystem();
		//Draw MySelf
		if (m_bVisible)
		{
			if (m_bEnable)
			{
				//TODO:Efficiency to improve.Using Draw.
				pRender->FillRect(GetMarginRc(), GetMarginColor());
				pRender->FillRect(GetBorderRc(), GetBorderColor());
				pRender->FillRect(GetPaddingRc(), GetPaddingColor());
				pRender->FillRect(GetContentRc(), GetContentColor());
				pRender->DrawTextString(GetContentRc(), GetText(), MFont(), MColor::White, 12);
			}
		}
		else
		{
			//DrawNothing.
		}
	}
	void BaseControl::Validate()
	{
		m_bValidate = true;
	}
	void BaseControl::Invalidate()
	{
		m_bValidate = false;
	}
	bool BaseControl::IsValidated() const
	{
		return m_bValidate;
	}
	void BaseControl::NeedUpdate()
	{
		m_bUpdateNeeded = true;
	}
	void BaseControl::NeedParentUpdate()
	{
		if (m_pParent)
		{
			m_pParent->NeedUpdate();
		}
	}
	bool BaseControl::IsUpdateNeeded() const
	{
		return m_bUpdateNeeded;
	}
	void BaseControl::Update()
	{
		if (m_pParent && m_pParent->IsUpdateNeeded())
		{
			m_pParent->Update();
		}
		else
		{
			m_bUpdateNeeded = false;
			Paint();
			Validate();
		}
	}
}