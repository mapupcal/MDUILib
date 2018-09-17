#include"Label.hpp"
#include"Framework\Common\Core\Graphics\IRenderSystem.hpp"
#include"Framework\Common\Core\Windows\IWindow.hpp"
#include"Framework\Common\Core\Controls\ControlManager.hpp"

namespace MDUILib
{
	Label::Label(IControl * pParent)
		:BaseControl(pParent)
		,m_Tat(TextAlignmentType::TAT_LEFT)
		,m_TextSize(9)
		,m_BackGroundColor(MColor::FULL_TRANSPARENT)
		,m_TextColor(MColor::WHITE)
		,m_TextFont()
	{
	}
	void Label::SetTextAlignment(TextAlignmentType tat)
	{
		m_Tat = tat;
	}
	TextAlignmentType Label::GetTextAlignment() const
	{
		return m_Tat;
	}
	void Label::SetFont(MFont font)
	{
		m_TextFont = font;
	}
	void Label::SetTextSize(int size)
	{
		m_TextSize = size;
	}
	int Label::GetTextSize() const
	{
		return m_TextSize;
	}
	MFont Label::GetFont() const
	{
		return m_TextFont;
	}
	void Label::SetTextColor(MColor color)
	{
		m_TextColor = color;
	}
	MColor Label::GetTextColor() const
	{
		return m_TextColor;
	}
	void Label::SetBackGroundColor(MColor color)
	{
		m_BackGroundColor = color;
	}
	MColor Label::GetBackGroundColor() const
	{
		return m_BackGroundColor;
	}
	void Label::OnPaint()
	{
		auto pRender = GetControlManager()->GetHostWindow()->GetRenderSystem();
		pRender->DrawBegin();
		if (GetVisible())
		{
			if (GetBackGroundColor() != MColor::FULL_TRANSPARENT)
			{
				pRender->FillRect(GetContentRc(), GetBackGroundColor());
			}
			pRender->DrawTextString(GetContentRc(), GetText(), GetFont(), GetTextColor(), GetTextSize(), 0);
		}
		pRender->DrawEnd();
	}
	bool Label::EventFilter(MEvent * e)
	{
		return true;
	}
	void Label::OnMouseEnter()
	{
	}
	void Label::OnMouseLeave()
	{
	}
}