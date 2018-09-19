
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
		void SetPushImage(const String &imgName);
		String GetPushImage() const;
		void SetForeImage(const String &imgName);
		String GetForImage() const;
		CallbackType OnClicked;
	private:
		bool m_bButtonDownIn;
		String m_szPushImageName;
		String m_szForeImageName;
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_BUTTON_H
