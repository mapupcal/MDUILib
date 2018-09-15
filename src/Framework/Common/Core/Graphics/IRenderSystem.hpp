
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_GRAPHICS_IRENDERSYSTEM_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_GRAPHICS_IRENDERSYSTEM_H

#include"Framework\Interface\Interface.hpp"
#include"Framework\Common\Core\IUnknown.hpp"
#include"Framework\Common\Core\Geometries\MRect.hpp"
#include"Framework\Common\Core\Windows\IWindow.hpp"
#include"MColor.hpp"

namespace MDUILib
{
	struct Font;

	m_interface IRenderSystem : m_extends IUnknown
	{
		virtual ~IRenderSystem(){}
		virtual void BindTargetWindow(IWindow *pWindow) = 0;
		virtual void DrawLine(MPoint startPt, MPoint endPt, MWORD wStrokeStyle) = 0;
		virtual void DrawRect(MRect rect, MColor color, MWORD wStrokeStyle) = 0;
		virtual void DrawRoundedRect(MRect rect, short radiusX, short radiusY, MColor color, MWORD wStrokeStyle) = 0;
		virtual void FillRect(MRect rect, MColor color) = 0;
		virtual void FillRoundedRect(MRect rect, short radiusX, short radiusY, MColor color) = 0;
		virtual void DrawTextString(MRect rect, const String &text, const Font &font, short size, MWORD wStyle) = 0;
		virtual void DrawImage(MRect rect, const String& imageFullPath) = 0; 
		virtual MHandleType GetNativeRenderHandle() const = 0;
		//Via IUnknow
		String GetInterfaceName() const override
		{
			return m_interface_name(IRenderSystem);
		}
		IUnknown* GetInterface(const String &riiName) override
		{
			if (riiName.Compare(m_interface_name(IRenderSystem)))
			{
				return this;
			}
			return IUnknown::GetInterface(riiName);
		}
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_GRAPHICS_IRENDERSySTEM_H