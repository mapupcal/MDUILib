#include"VerticalLayout.hpp"

namespace MDUILib
{
	void VerticalLayout::CalculateElemsPos()
	{
		BaseControl* pLastBottomControl = nullptr;
		BaseControl* pLastTopControl = nullptr;
		auto iter = m_lstpChildren.cbegin();
		auto iter_top = m_lstpChildren.cbegin();
		MPoint destPt(0, 0);

		while (iter != m_lstpChildren.cend())
		{
			iter = std::find_if(iter, m_lstpChildren.cend(),
				[](IControl* pC) -> bool {
				return static_cast<BaseControl*>(pC)->GetFloating()
					&& (static_cast<BaseControl*>(pC)->GetFloatAlignment() == ControlFloatAlignmentType::CFAT_BOTTOM);
			});
			while (iter_top != iter)
			{
				auto pBaseControl = static_cast<BaseControl*>(*iter_top);
				if (!pLastTopControl)
				{
					destPt = MPoint(GetContentRc().left, GetContentRc().top);
				}
				else
				{
					destPt = MPoint(GetContentRc().left, pLastTopControl->GetMarginRc().bottom + GetStrech());
				}
				pBaseControl->SetPos(destPt);
				pLastTopControl = pBaseControl;
				iter_top++;
			}
			if (iter != m_lstpChildren.cend())
			{
				auto pBaseControl = static_cast<BaseControl*>(*iter);
				if (!pLastBottomControl)
				{
					destPt = MPoint(GetContentRc().left, GetContentRc().bottom - pBaseControl->GetHeight());
				}
				else
				{
					destPt = MPoint(GetContentRc().left, pLastBottomControl->GetMarginRc().top - pBaseControl->GetHeight() - GetStrech());
				}
				pBaseControl->SetPos(destPt);
				pLastBottomControl = pBaseControl;
				iter++;
			}
			iter_top = iter;
		}
	}
}