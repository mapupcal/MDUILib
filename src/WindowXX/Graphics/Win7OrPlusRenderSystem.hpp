#ifndef MDUILIB_WINDOWXX_GRAPHICS_WIN7ORPLUSRENDERSYSTEM_H
#define MDUILIB_WINDOWXX_GRAPHICS_WIN7ORPLUSRENDERSYSTEM_H

#include "Framework\Common\Core\Graphics\IRenderSystem.hpp"
#include "Framework\Common\Core\Object.hpp"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#ifndef HINST_THISCOMPONENT
	EXTERN_C IMAGE_DOS_HEADER __ImageBase;
	#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif //HINST_THISCOMPONENT
namespace MDUILib
{
	class Win7OrPlusRenderSystem : m_extends Object, m_implements IRenderSystem
	{
	public:
		virtual ~Win7OrPlusRenderSystem();
		virtual void BindTargetWindow(IWindow *pWindow) override;
		virtual void DrawLine(MPoint startPt, MPoint endPt, MWORD wStrokeStyle) override;
		virtual void DrawRect(MRect rect, MColor color, MWORD wStrokeStyle) override;
		virtual void DrawRoundedRect(MRect rect, short radiusX, short radiusY, MColor color, MWORD wStrokeStyle) override;
		virtual void FillRect(MRect rect, MColor color) override;
		virtual void FillRoundedRect(MRect rect, short radiusX, short radiusY, MColor color) override;
		virtual void DrawTextString(MRect rect, const String &text, const Font &font, short size, MWORD wStyle) override;
		virtual void DrawImage(MRect rect, const String& imageFullPath) override;
		virtual MHandleType GetNativeRenderHandle() const override;
	private:
		IWindow* m_pRenderTargetWindow;
		ID2D1HwndRenderTarget *m_pHwndRenderTarget;
		ID2D1Factory *m_pD2d1Factory;
		IDWriteFactory *m_pDWriteFactory;
		HRESULT __CreateD2DDeviceIndependentResources();
		HRESULT __CreateD2DDeviceResources();
		void __ReleaseResources();
	};
}

#endif // !MDUILIB_WINDOWXX_GRAPHICS_WIN7ORPLUSRENDERSYSTEM_H