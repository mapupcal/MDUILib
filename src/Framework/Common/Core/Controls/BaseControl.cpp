#include"BaseControl.hpp"
#include<algorithm>

namespace MDUILib
{
	BaseControl::BaseControl(IControl * pParent)
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
	MRect BaseControl::GetContetnRc() const
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
	MPoint BaseControl::GetPos() const
	{
		return MPoint(GetContetnRc().left, GetContetnRc().top);
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

		//TODO:ԶԶδ��ɵ��¼�����������
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
	}
	IControl * BaseControl::GetParent() const
	{
		return m_pParent;
	}
	void BaseControl::AddChild(IControl * pChild)
	{
		for (auto p : m_lstpChildren)
		{
			if (p == pChild)
			{
				return;
			}
		}
		m_lstpChildren.push_back(pChild);
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
			if (IsPointInRect(pt, (static_cast<BaseControl*>(p))->GetBorderRc()))
			{
				return p;
			}
		}
	}

	BaseControl::IControlList BaseControl::FindChildren(const MPoint & pt)
	{
		return __FindChildren_IF(
			[=](IControl* p)
			{
				return IsPointInRect(pt, (static_cast<const BaseControl*>(p))->GetBorderRc());
			});
	}

	void BaseControl::OnPaint()
	{
		//TODO:
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
		OnPaint();
		m_bUpdateNeeded = false;
		Validate();
	}
}