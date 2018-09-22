#include"HorizontalLayout.hpp"
#include<algorithm>

namespace MDUILib
{
	void HorizontalLayout::CalculateElemsPos()
	{
		BaseControl* pLastRightControl = nullptr;
		BaseControl* pLastLeftControl = nullptr;
		auto iter = m_lstpChildren.cbegin();
		auto iter_left = m_lstpChildren.cbegin();
		MPoint destPt(0, 0);

		while (iter != m_lstpChildren.cend())
		{
			iter = std::find_if(iter,m_lstpChildren.cend(),
				[](IControl* pC) -> bool{
				return static_cast<BaseControl*>(pC)->GetFloating()
					&& (static_cast<BaseControl*>(pC)->GetFloatAlignment() == ControlFloatAlignmentType::CFAT_RIGHT);
			});
			while (iter_left != iter)
			{
				auto pBaseControl = static_cast<BaseControl*>(*iter_left);
				auto rc = pBaseControl->GetMarginRc();
				if (!pLastLeftControl)
				{
					destPt = MPoint(GetContentRc().left, GetContentRc().top);
				}
				else
				{
					destPt = MPoint(pLastLeftControl->GetMarginRc().right + GetStrech(),
						GetContentRc().top);
				}
				pBaseControl->SetPos(destPt);
				pLastLeftControl = pBaseControl;
				iter_left++;
			}
			if (iter != m_lstpChildren.cend())
			{
				auto pBaseControl = static_cast<BaseControl*>(*iter);
				auto rc = pBaseControl->GetMarginRc();
				if (!pLastRightControl)
				{
					destPt = MPoint(GetContentRc().right - pBaseControl->GetWidth(), GetContentRc().top);
				}
				else
				{
					destPt = MPoint(pLastRightControl->GetMarginRc().left - pBaseControl->GetWidth() - GetStrech(),
						GetContentRc().top);
				}
				pBaseControl->SetPos(destPt);
				pLastRightControl = pBaseControl;
				iter++;
			}
			iter_left = iter;
		}
	}
}