#include"VerticalLayout.hpp"

namespace MDUILib
{
	void VerticalLayout::CalculateElemsPos()
	{
		BaseControl* pLastBottomControl = nullptr;
		BaseControl* pLastTopControl = nullptr;
		auto iter = m_lstpChildren.cbegin();
		auto iter_top = m_lstpChildren.cbegin();
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
				auto detalMB = pBaseControl->GetMarginRc().GetLeftTopPoint()
					- pBaseControl->GetBorderRc().GetLeftTopPoint();
				auto deltaBP = pBaseControl->GetBorderRc().GetLeftTopPoint()
					- pBaseControl->GetPaddingRc().GetLeftTopPoint();
				auto deltaPC = pBaseControl->GetPaddingRc().GetLeftTopPoint()
					- pBaseControl->GetContentRc().GetLeftTopPoint();
				MRect baseContentRc;
				auto rc = pBaseControl->GetMarginRc();
				//上边边还没有排列控件
				if (!pLastTopControl)
				{
					baseContentRc = GetContentRc();
					rc = TranslateToPos(rc, baseContentRc.left, baseContentRc.top);
				}
				else
				{
					baseContentRc = static_cast<BaseControl*>(pLastTopControl)->GetMarginRc();
					rc = TranslateToPos(rc, baseContentRc.left, baseContentRc.bottom + GetStrech());
				}
				pBaseControl->SetMarginRc(rc);
				rc = pBaseControl->GetBorderRc();
				rc = TranslateToPos(rc, pBaseControl->GetMarginRc().GetLeftTopPoint() - detalMB);
				pBaseControl->SetBorderRc(rc);
				rc = pBaseControl->GetPaddingRc();
				rc = TranslateToPos(rc, pBaseControl->GetBorderRc().GetLeftTopPoint() - deltaBP);
				pBaseControl->SetPaddingRc(rc);
				rc = pBaseControl->GetContentRc();
				rc = TranslateToPos(rc, pBaseControl->GetPaddingRc().GetLeftTopPoint() - deltaPC);
				pBaseControl->SetContentRc(rc);
				pLastTopControl = pBaseControl;
				iter_top++;
			}
			if (iter != m_lstpChildren.cend())
			{
				auto pBaseControl = static_cast<BaseControl*>(*iter);
				auto detalMB = pBaseControl->GetMarginRc().GetLeftTopPoint()
					- pBaseControl->GetBorderRc().GetLeftTopPoint();
				auto deltaBP = pBaseControl->GetBorderRc().GetLeftTopPoint()
					- pBaseControl->GetPaddingRc().GetLeftTopPoint();
				auto deltaPC = pBaseControl->GetPaddingRc().GetLeftTopPoint()
					- pBaseControl->GetContentRc().GetLeftTopPoint();
				MRect baseContentRc;
				auto rc = pBaseControl->GetMarginRc();
				//下边还没有排列控件
				if (!pLastBottomControl)
				{
					baseContentRc = GetContentRc();
					rc = TranslateToPos(rc, baseContentRc.left, baseContentRc.bottom - pBaseControl->GetHeight());
				}
				else
				{
					baseContentRc = static_cast<BaseControl*>(pLastBottomControl)->GetMarginRc();
					rc = TranslateToPos(rc, baseContentRc.left, baseContentRc.top - pBaseControl->GetHeight() - GetStrech());
				}
				pBaseControl->SetMarginRc(rc);
				rc = pBaseControl->GetBorderRc();
				rc = TranslateToPos(rc, pBaseControl->GetMarginRc().GetLeftTopPoint() - detalMB);
				pBaseControl->SetBorderRc(rc);
				rc = pBaseControl->GetPaddingRc();
				rc = TranslateToPos(rc, pBaseControl->GetBorderRc().GetLeftTopPoint() - deltaBP);
				pBaseControl->SetPaddingRc(rc);
				rc = pBaseControl->GetContentRc();
				rc = TranslateToPos(rc, pBaseControl->GetPaddingRc().GetLeftTopPoint() - deltaPC);
				pBaseControl->SetContentRc(rc);
				pLastBottomControl = pBaseControl;
				iter++;
			}
			iter_top = iter;
		}
	}
}