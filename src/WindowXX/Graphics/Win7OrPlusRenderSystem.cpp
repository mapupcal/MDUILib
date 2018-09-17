#include "Win7OrPlusRenderSystem.hpp"
#include"WindowXX\Windows\WinXXWindow.hpp"
#include"Framework\Common\Core\Graphics\MFont.hpp"

namespace MDUILib
{

	inline D2D1::ColorF D2DColorF_FromMColor(MColor color)
	{
		D2D1::ColorF cf(color.r, color.g, color.b, color.a / 255.0f);
		return cf;
	}

	inline D2D1_POINT_2F D2DPoint2F_FromMPoint(MPoint pt)
	{
		return D2D1::Point2F(pt.x, pt.y);
	}

	inline D2D1_RECT_F D2DRectF_FromMRect(MRect rect)
	{
		return D2D1::RectF(rect.left, rect.top, rect.right, rect.bottom);
	}

	inline D2D1_ROUNDED_RECT D2D1RoundedRect_FromMRect(MRect rect, int radiusX, int radiusY)
	{
		return D2D1::RoundedRect(
			D2DRectF_FromMRect(rect),
			static_cast<float>(radiusX),
			static_cast<float>(radiusY)
		);
	}

	HRESULT Win7OrPlusRenderSystem::__CreateD2DDeviceIndependentResources()
	{
		HRESULT hr = S_OK;
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2d1Factory);
		MDUILIB_ASSERT_MSG(SUCCEEDED(hr), "Failed Create D2D1 Factory.");
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<::IUnknown**>(&m_pDWriteFactory)
		);
		return hr;
	}
	HRESULT Win7OrPlusRenderSystem::__CreateD2DDeviceResources()
	{
		HRESULT hr = S_OK;
		if (!m_pHwndRenderTarget && m_pRenderTargetWindow)
		{
			HWND hWnd = (HWND)m_pRenderTargetWindow->GetNativeWindowHandle();
			RECT rc;
			::GetClientRect(hWnd, &rc);
			D2D1_SIZE_U size = D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top
			);
			//	@Commit:³õÊ¼»¯m_pRenderTarget
			hr = m_pD2d1Factory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(hWnd, size),
				&m_pHwndRenderTarget
			);
			MDUILIB_ASSERT_MSG(SUCCEEDED(hr), "D2D Failed to Initialize the Render Target Window.");
		}
		return hr;
	}
	ComPtr<ID2D1StrokeStyle> Win7OrPlusRenderSystem::__CreateStrokeStyle(MStrokeStyle wStyle)
	{
		ComPtr<ID2D1StrokeStyle> pStyle(0);
		if (wStyle == MStrokeStyle::STD_DASH)
		{
			float dashes[] = { 2.0f, 2.0f, 2.0f };
			HRESULT hr = m_pD2d1Factory->CreateStrokeStyle(
				D2D1::StrokeStyleProperties(
					D2D1_CAP_STYLE_FLAT,
					D2D1_CAP_STYLE_FLAT,
					D2D1_CAP_STYLE_ROUND,
					D2D1_LINE_JOIN_MITER,
					10.0f,
					D2D1_DASH_STYLE_CUSTOM,
					0.0f),
				dashes,
				ARRAYSIZE(dashes),
				&pStyle
			);
		}
		return pStyle;
	}
	ComPtr<ID2D1SolidColorBrush> Win7OrPlusRenderSystem::__CreateSolidColorBrush(MColor color)
	{
		ComPtr<ID2D1SolidColorBrush> pSolidColorBrush;
		HRESULT hr = m_pHwndRenderTarget->CreateSolidColorBrush(
			D2DColorF_FromMColor(color),
			&pSolidColorBrush
		);
		MDUILIB_ASSERT_MSG(SUCCEEDED(hr), "Failed to CreateSolidColorBrush");
		return pSolidColorBrush;
	}
	Win7OrPlusRenderSystem::~Win7OrPlusRenderSystem()
	{

	}
	void Win7OrPlusRenderSystem::BindTargetWindow(IWindow * pWindow)
	{
		MDUILIB_ASSERT_MSG((pWindow && pWindow->GetNativeWindowHandle()),
			"Window Did Not Initialzed.");
		m_pRenderTargetWindow = pWindow;
		__CreateD2DDeviceIndependentResources();
		__CreateD2DDeviceResources();
		WinXXWindow* pWinXXWindow = static_cast<WinXXWindow*>(pWindow);
		pWinXXWindow->OnSize += [&](IWindow*pW, MEvent*e)
		{
			ControlNotifyEvent *pNe = static_cast<ControlNotifyEvent*>(e);
			if (pNe->GetControlNotifyEventType()
				== ControlNotifyEvent::ControlNotifyEventType::CNET_SIZE)
			{
				auto rc = pNe->GetRect();
				D2D1_SIZE_U targetRc;
				targetRc.height = GetRectHeight(rc);
				targetRc.width = GetRectWidth(rc);
				this->m_pHwndRenderTarget->Resize(targetRc);
			}
		};
	}

	void Win7OrPlusRenderSystem::DrawBegin()
	{
		MDUILIB_ASSERT(m_pHwndRenderTarget);
		this->__CreateD2DDeviceResources();
		m_pHwndRenderTarget->BeginDraw();
		m_pHwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	void Win7OrPlusRenderSystem::DrawEnd()
	{
		MDUILIB_ASSERT(m_pHwndRenderTarget);
		m_pHwndRenderTarget->EndDraw();
	}

	void Win7OrPlusRenderSystem::Clear(MColor color)
	{
		MDUILIB_ASSERT(m_pHwndRenderTarget);
		DrawBegin();
		m_pHwndRenderTarget->Clear(
			D2DColorF_FromMColor(color)
		);
		DrawEnd();
	}

	void Win7OrPlusRenderSystem::DrawLine(MPoint startPt, MPoint endPt, MColor color, int lineWidth, MStrokeStyle wStrokeStyle)
	{
		if (m_pHwndRenderTarget.Get() && m_pD2d1Factory.Get())
		{
			auto pSolidColorBrush = __CreateSolidColorBrush(color);
			ComPtr<ID2D1StrokeStyle> pStyle = __CreateStrokeStyle(wStrokeStyle);
			m_pHwndRenderTarget->DrawLine(
				D2DPoint2F_FromMPoint(startPt),
				D2DPoint2F_FromMPoint(endPt),
				pSolidColorBrush,
				static_cast<float>(lineWidth),
				pStyle
			);
		}
	}

	void Win7OrPlusRenderSystem::DrawRect(MRect rect, MColor color, int lineWidth, MStrokeStyle wStrokeStyle)
	{
		if (m_pHwndRenderTarget.Get() && m_pD2d1Factory.Get())
		{
			auto pSolidColorBrush = __CreateSolidColorBrush(color);
			auto pStyle = __CreateStrokeStyle(wStrokeStyle);
			m_pHwndRenderTarget->DrawRectangle(
				D2DRectF_FromMRect(rect),
				pSolidColorBrush,
				static_cast<float>(lineWidth),
				pStyle
			);
		}
	}

	void Win7OrPlusRenderSystem::DrawRoundedRect(MRect rect, short radiusX, short radiusY, MColor color, int lineWidth, MStrokeStyle wStrokeStyle)
	{
		if (m_pHwndRenderTarget.Get() && m_pD2d1Factory.Get())
		{
			auto pSolidColorBrush = __CreateSolidColorBrush(color);
			auto pStyle = __CreateStrokeStyle(wStrokeStyle);
			m_pHwndRenderTarget->DrawRoundedRectangle(
				D2D1RoundedRect_FromMRect(rect, radiusX, radiusY),
				pSolidColorBrush,
				static_cast<float>(lineWidth),
				pStyle
			);
		}
	}

	void Win7OrPlusRenderSystem::FillRect(MRect rect, MColor color)
	{
		if (m_pHwndRenderTarget.Get() && m_pD2d1Factory.Get())
		{
			auto pSolidColorBrush = __CreateSolidColorBrush(color);
			m_pHwndRenderTarget->FillRectangle(
				D2DRectF_FromMRect(rect),
				pSolidColorBrush
			);
		}
	}

	void Win7OrPlusRenderSystem::FillRoundedRect(MRect rect, short radiusX, short radiusY, MColor color)
	{
		if (m_pHwndRenderTarget.Get() && m_pD2d1Factory.Get())
		{
			auto pSolidColorBrush = __CreateSolidColorBrush(color);
			m_pHwndRenderTarget->FillRoundedRectangle(
				D2D1RoundedRect_FromMRect(rect, radiusX, radiusY),
				pSolidColorBrush
			);
		}
	}

	void Win7OrPlusRenderSystem::DrawTextString(MRect rect, const String & text, const MFont & font, MColor color, short size, MWORD wStyle)
	{
		ComPtr<IDWriteTextFormat> pTextFormat;
		auto pBrush = __CreateSolidColorBrush(color);
		DWRITE_TRIMMING trim;
		m_pDWriteFactory->CreateTextFormat(
			L"Î¢ÈíÑÅºÚ",
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			size,
			L"zh-cn",
			&pTextFormat
		);
		ComPtr<IDWriteInlineObject> pIDWInlineObj;
		m_pDWriteFactory->CreateEllipsisTrimmingSign(pTextFormat, &pIDWInlineObj);
		pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		pTextFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_CHARACTER);
		trim.granularity = DWRITE_TRIMMING_GRANULARITY_CHARACTER;
		trim.delimiter = 1;
		trim.delimiterCount = 10;
		pTextFormat->SetTrimming(&trim, pIDWInlineObj);
		
		auto wide_string = text.ToStdWString();
		m_pHwndRenderTarget->DrawTextA(
			wide_string.c_str(),
			wide_string.length(),
			pTextFormat,
			D2DRectF_FromMRect(rect),
			pBrush
		);
	}

	void Win7OrPlusRenderSystem::DrawImage(MRect rect, const String & imageFullPath)
	{
		//TODO:
	}

	MHandleType Win7OrPlusRenderSystem::GetNativeRenderHandle() const
	{
		return m_pHwndRenderTarget.Get();
	}
}
