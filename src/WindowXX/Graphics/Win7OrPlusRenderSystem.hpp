#ifndef MDUILIB_WINDOWXX_GRAPHICS_WIN7ORPLUSRENDERSYSTEM_H
#define MDUILIB_WINDOWXX_GRAPHICS_WIN7ORPLUSRENDERSYSTEM_H

#include "Framework\Common\Core\Graphics\IRenderSystem.hpp"
#include "Framework\Common\Core\Object.hpp"
#include "WindowXX/Utils.hpp"

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
		virtual void DrawBegin() override;
		virtual void DrawEnd()override;
		virtual void Clear(MColor color) override;
		virtual void DrawLine(MPoint startPt, MPoint endPt, MColor color, \
			int lineWidth, MStrokeStyle wStrokeStyle) override;
		virtual void DrawRect(MRect rect, MColor color, \
			int lineWidth, MStrokeStyle wStrokeStyle) override;
		virtual void DrawRoundedRect(MRect rect, short radiusX, short radiusY, MColor color, \
			int lineWidth, MStrokeStyle wStrokeStyle) override;
		virtual void FillRect(MRect rect, MColor color) override;
		virtual void FillRoundedRect(MRect rect, short radiusX, short radiusY, MColor color) override;
		virtual void DrawGradientRect(MRect rect, MColor colorBegin, MColor colorEnd, \
			int lineWidth, MStrokeStyle wStrokeStyle, bool bRadius, LinearGradientRenderType lgrt) override;
		virtual void FillGradientRect(MRect rect, MColor colorBegin, MColor colorEnd, \
			bool bRadius, LinearGradientRenderType lgrt) override;
		virtual void DrawGradientRoundedRect(MRect rect, short radiusX, short radiusY, \
			MColor colorBegin, MColor colorEnd, int lineWidth, MStrokeStyle wStrokeStyle, bool bRadius, LinearGradientRenderType lgrt) override;
		virtual void FillGradientRoundedRect(MRect rect, short radiusX, short radiusY, \
			MColor colorBegin, MColor colorEnd, bool bRadius, LinearGradientRenderType lgrt) override;
		virtual void DrawTextString(MRect rect, const String &text,const MFont &font, \
			MColor color, short size, MWORD wStyle) override;
		virtual void DrawImage(MRect rect, const String& imageFullPath) override;
		virtual MHandleType GetNativeRenderHandle() const override;
	private:
		HRESULT __CreateD2DDeviceIndependentResources();
		HRESULT __CreateD2DDeviceResources();
		ComPtr<ID2D1StrokeStyle> __CreateStrokeStyle(MStrokeStyle wStyle);
		ComPtr<ID2D1SolidColorBrush> __CreateSolidColorBrush(MColor color);
		ComPtr<ID2D1Brush> __CreateGradientColorBrush(MRect rect, MColor colorBegin, MColor colorEnd, \
			bool bRadius, LinearGradientRenderType lgrt);
	private:
		IWindow* m_pRenderTargetWindow;
		
		ComPtr<ID2D1HwndRenderTarget> m_pHwndRenderTarget;
		ComPtr<ID2D1Factory> m_pD2d1Factory;
		ComPtr<IDWriteFactory> m_pDWriteFactory;
	};
}

#endif // !MDUILIB_WINDOWXX_GRAPHICS_WIN7ORPLUSRENDERSYSTEM_H
