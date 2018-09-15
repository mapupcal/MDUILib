#include "Win7OrPlusRenderSystem.hpp"
#include"WindowXX\Utils.hpp"
#include"WindowXX\Windows\WinXXWindow.hpp"
#include<memory>
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
	void Win7OrPlusRenderSystem::__ReleaseResources()
	{
		SafeRelease(&m_pHwndRenderTarget);
		SafeRelease(&m_pD2d1Factory);
		SafeRelease(&m_pDWriteFactory);
	}
	Win7OrPlusRenderSystem::~Win7OrPlusRenderSystem()
	{
		__ReleaseResources();
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
				this->__CreateD2DDeviceResources();
				this->m_pHwndRenderTarget->Resize(targetRc);
				this->m_pHwndRenderTarget->BeginDraw();
				this->m_pHwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
				this->m_pHwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
				this->m_pHwndRenderTarget->EndDraw();
				printf("Client Rect (%d,%d,%d,%d)\n", rc.left, rc.right, rc.top, rc.bottom);
				MPoint ptS(0, targetRc.height / 2);
				MPoint ptE(targetRc.width, targetRc.height / 2);
				MColor red;
				red.a = red.r = 255;
				red.b = red.g = 0;
				this->DrawLine(ptS, ptE, red, 2, 0);
				ptS.x = ptE.x = targetRc.width / 2;
				ptS.y = 0;
				ptE.y = targetRc.height;
				this->DrawLine(ptS, ptE, red, 2, 0);
			}
		};
	}

	void Win7OrPlusRenderSystem::DrawBegin()
	{
		MDUILIB_ASSERT(m_pHwndRenderTarget);
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
		m_pHwndRenderTarget->BeginDraw();
		m_pHwndRenderTarget->Clear(
			D2DColorF_FromMColor(color)
		);
		m_pHwndRenderTarget->EndDraw();
	}

	void Win7OrPlusRenderSystem::DrawLine(MPoint startPt, MPoint endPt, MColor color, int lineWidth, MWORD wStrokeStyle)
	{
		HRESULT hr = S_OK;
		if (m_pHwndRenderTarget && m_pD2d1Factory)
		{
			hr = m_pHwndRenderTarget->CreateSolidColorBrush(
				D2DColorF_FromMColor(color),
				&m_pSolidColorBrush
			);
			MDUILIB_ASSERT_MSG(SUCCEEDED(hr), "Failed to CreateSolidColorBrush");
			ID2D1StrokeStyle *m_pStyle;
			float dashes[] = { 1.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f };
			hr = m_pD2d1Factory->CreateStrokeStyle(
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
				&m_pStyle
			);
			m_pHwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
			m_pHwndRenderTarget->DrawLine(
				D2DPoint2F_FromMPoint(startPt),
				D2DPoint2F_FromMPoint(endPt),
				m_pSolidColorBrush,
				lineWidth,
				m_pStyle
			);
			SafeRelease(&m_pStyle);
			SafeRelease(&m_pSolidColorBrush);
		}
	}

	void Win7OrPlusRenderSystem::DrawRect(MRect rect, MColor color, int lineWidth, MWORD wStrokeStyle)
	{
	}

	void Win7OrPlusRenderSystem::DrawRoundedRect(MRect rect, short radiusX, short radiusY, MColor color, int lineWidth, MWORD wStrokeStyle)
	{
	}

	void Win7OrPlusRenderSystem::FillRect(MRect rect, MColor color)
	{
	}

	void Win7OrPlusRenderSystem::FillRoundedRect(MRect rect, short radiusX, short radiusY, MColor color)
	{
	}

	void Win7OrPlusRenderSystem::DrawTextString(MRect rect, const String & text, const Font & font, MColor color, short size, MWORD wStyle)
	{
	}

	void Win7OrPlusRenderSystem::DrawImage(MRect rect, const String & imageFullPath)
	{
	}

	MHandleType Win7OrPlusRenderSystem::GetNativeRenderHandle() const
	{
		return m_pHwndRenderTarget;
	}
}
