#include "Win7OrPlusRenderSystem.hpp"
#include"WindowXX\Utils.hpp"
#include"WindowXX\Windows\WinXXWindow.hpp"

namespace MDUILib
{
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
		pWinXXWindow->OnSize += [=](IWindow*pW, MEvent*e)
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
	void Win7OrPlusRenderSystem::DrawLine(MPoint startPt, MPoint endPt, MWORD wStrokeStyle)
	{
	}
	void Win7OrPlusRenderSystem::DrawRect(MRect rect, MColor color, MWORD wStrokeStyle)
	{
	}
	void Win7OrPlusRenderSystem::DrawRoundedRect(MRect rect, short radiusX, short radiusY, MColor color, MWORD wStrokeStyle)
	{
	}
	void Win7OrPlusRenderSystem::FillRect(MRect rect, MColor color)
	{
	}
	void Win7OrPlusRenderSystem::FillRoundedRect(MRect rect, short radiusX, short radiusY, MColor color)
	{
	}
	void Win7OrPlusRenderSystem::DrawTextString(MRect rect, const String & text, const Font & font, short size, MWORD wStyle)
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
