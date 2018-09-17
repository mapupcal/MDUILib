
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_BUTTON_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_BUTTON_H

#include "Label.hpp"
#include "Framework\Common\Utils\MDelegate.hpp"
#include "Framework\Common\Core\Events.hpp"

namespace MDUILib
{
	class Button : m_extends Label
	{
	public:
		typedef DelegateNotifyers<IControl*,MEvent*> CallbackType;

		Button(IControl* pParent);
		virtual bool EventFilter(MEvent *e) override;
		virtual void OnMouseEnter() override;
		virtual void OnMouseLeave() override;
		virtual void OnPaint() override;

		CallbackType OnClicked;
	private:
		bool m_bButtonDownIn;
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_BUTTON_H
