
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_LABEL_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_LABEL_H

#include"BaseControl.hpp"
#include"Framework\Common\Core\Graphics\IRenderSystem.hpp"
#include"Framework\Common\Core\Graphics\MFont.hpp"

namespace MDUILib
{
	class Label : m_extends BaseControl
	{
	public:
		Label(IControl *pParent);
		void SetTextAlignment(TextAlignmentType tat);
		TextAlignmentType GetTextAlignment() const;
		void SetFont(MFont font);
		void SetTextSize(int size);
		int GetTextSize() const;
		MFont GetFont() const;
		void SetTextColor(MColor color);
		MColor GetTextColor() const;
		void SetBackGroundColor(MColor color);
		MColor GetBackGroundColor() const;

		virtual void OnPaint() override;
		virtual bool EventFilter(MEvent *e) override;
		virtual void OnMouseEnter() override;
		virtual void OnMouseLeave() override;
	private:
		TextAlignmentType m_Tat;
		MColor m_TextColor;
		MColor m_BackGroundColor;
		MFont m_TextFont;
		int m_TextSize;
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_LABEL_H
