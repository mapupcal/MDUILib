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
				auto detalMB = pBaseControl->GetMarginRc().GetLeftTopPoint()
					- pBaseControl->GetBorderRc().GetLeftTopPoint();
				auto deltaBP = pBaseControl->GetBorderRc().GetLeftTopPoint()
					- pBaseControl->GetPaddingRc().GetLeftTopPoint();
				auto deltaPC = pBaseControl->GetPaddingRc().GetLeftTopPoint()
					- pBaseControl->GetContentRc().GetLeftTopPoint();
				MRect baseContentRc;
				auto rc = pBaseControl->GetMarginRc();
				//左边还没有排列控件
				if (!pLastLeftControl)
				{
					baseContentRc = GetContentRc();
					rc = TranslateToPos(rc, baseContentRc.left  +  GetStrech(), baseContentRc.top + GetStrech());
				}
				else
				{
					baseContentRc = static_cast<BaseControl*>(pLastLeftControl)->GetMarginRc();
					rc = TranslateToPos(rc, baseContentRc.right + GetStrech(), baseContentRc.top + GetStrech());
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
				pLastLeftControl = pBaseControl;
				iter_left++;
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
				//左边还没有排列控件
				if (!pLastRightControl)
				{
					baseContentRc = GetContentRc();
					rc = TranslateToPos(rc, baseContentRc.right - rc.GetWidth() - GetStrech(), baseContentRc.top + GetStrech());
				}
				else
				{
					baseContentRc = static_cast<BaseControl*>(pLastRightControl)->GetMarginRc();
					rc = TranslateToPos(rc, baseContentRc.left - rc.GetWidth() - GetStrech(), baseContentRc.top + GetStrech());
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
				pLastRightControl = pBaseControl;
				iter++;
			}
		}
	}
}