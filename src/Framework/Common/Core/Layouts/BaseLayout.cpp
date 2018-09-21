#include "BaseLayout.hpp"

namespace MDUILib
{
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
		//Calculate the pChild's Pos and Size.
	}
}