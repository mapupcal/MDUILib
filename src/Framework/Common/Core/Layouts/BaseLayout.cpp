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
		//Doing Nothing.
	}
	void BaseLayout::Update()
	{
		auto pBaseParent = static_cast<BaseControl*>(GetParent());
		SetMarginRc(pBaseParent->GetMarginRc());
		SetBorderRc(pBaseParent->GetBorderRc());
		SetPaddingRc(pBaseParent->GetPaddingRc());
		SetContentRc(pBaseParent->GetContentRc());
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
	void BaseLayout::CalculateElemsPos()
	{
		//empty impl.
	}
}