#include "BaseLayout.hpp"

namespace MDUILib
{
	BaseLayout::BaseLayout()
		:BaseControl(nullptr)
	{
	}
	void BaseLayout::AddControl(IControl* pControl)
	{
		AddChild(pControl);
	}
	void BaseLayout::RemoveControl(IControl * pControl)
	{
		RemoveChild(pControl);
	}
	void BaseLayout::OnPaint()
	{
		Update();
	}
	void BaseLayout::Update()
	{
		auto pBaseParent = static_cast<BaseControl*>(GetParent());
		//TODO:BUG TO FIXED.这里没有考虑周全，导致长和宽只要一个大于父控件，就会触发Fixed布局。
		//if (pBaseParent->GetWidth() < GetFixedWidth() || pBaseParent->GetHeight() < GetFixedHeight())
		{
			SetMarginRc(pBaseParent->GetContentRc());
			SetBorderRc(pBaseParent->GetContentRc());
			SetPaddingRc(pBaseParent->GetContentRc());
			SetContentRc(pBaseParent->GetContentRc());
		}
		CalculateElemsPos();
	}
	void BaseLayout::SetStrech(MUINT pix)
	{
		m_uStrechPix = pix;
	}
	int BaseLayout::GetStrech() const
	{
		return m_uStrechPix;
	}
	void BaseLayout::SetFixedSize(int width, int height)
	{
		m_FixedHeight = height;
		m_FixedWidth = width;
		m_rcContent = ResizeRect(m_rcContent, width, height);
		m_rcMargin = ResizeRect(m_rcMargin, width, height);
		m_rcPadding = ResizeRect(m_rcPadding, width, height);
		m_rcBorder = ResizeRect(m_rcBorder, width, height);
	}
	int BaseLayout::GetFixedWidth() const
	{
		return m_FixedWidth;
	}
	int BaseLayout::GetFixedHeight() const
	{
		return m_FixedHeight;
	}
	void BaseLayout::CalculateElemsPos()
	{
		//empty impl.
	}
}