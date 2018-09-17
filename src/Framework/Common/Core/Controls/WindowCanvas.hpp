#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_WINDOWCANVAS_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_WINDOWCANVAS_H

#include"BaseControl.hpp"

namespace MDUILib
{
	class ControlManager;
	class WindowCanvas : m_extends BaseControl
	{
	public:
		WindowCanvas(ControlManager *pManager);
		virtual void OnMouseEnter() override;
		virtual void OnMouseLeave() override;
		virtual void OnPaint() override;
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_WINDOWCANVAS_H
