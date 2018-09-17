#include"BaseControl.hpp"
#include"IControl.hpp"
#include"Framework\Common\Core\Windows\IWindow.hpp"
#include"Framework\Common\Core\Windows\BaseWindow.hpp"
#include"Framework\Common\Core\Graphics\IRenderSystem.hpp"
#include"WindowCanvas.hpp"
#include "ControlManager.hpp"

namespace MDUILib
{
	ControlManager::ControlManager(IWindow * pWindow)
		:	m_pHostWindow(pWindow),
			m_pControlMouseCurrentHitted(nullptr),
			m_pWindowCanvas(nullptr)
	{
		m_pWindowCanvas = new WindowCanvas(this);
		m_pWindowCanvas->SetControlManager(this);
		static_cast<BaseWindow*>(pWindow)->OnSize += [=](IWindow *pWindow, MEvent *e)
		{
			static_cast<BaseControl*>(this->m_pWindowCanvas)
				->SetBorderRc(static_cast<ControlNotifyEvent*>(e)->GetRect());
		};
	}
	ControlManager::~ControlManager()
	{
		delete m_pWindowCanvas;
	}
	IWindow* ControlManager::GetHostWindow() const
	{
		return m_pHostWindow;
	}
	void ControlManager::SetControlRoot(IControl * pControlRoot)
	{
		m_pWindowCanvas->AddChild(pControlRoot);
		m_pControlMouseCurrentHitted = m_pWindowCanvas;
	}
	IControl* ControlManager::GetControlRoot() const
	{
		return m_pWindowCanvas;
	}
	void ControlManager::Paint()
	{
		for (auto pC : m_pWindowCanvas->GetChildren())
			Paint(pC);
	}
	void ControlManager::Paint(IControl * pControl)
	{
		pControl->OnPaint();
		for (auto pChild : pControl->GetChildren())
		{
			pChild->Update();
		}
	}
	IControl* ControlManager::FindContorlByName(const String & controlName)
	{
		return nullptr;
	}
	ControlManager::IControlList ControlManager::FindAllControlsByName(const String & controlName)
	{
		return IControlList();
	}
	IControl* ControlManager::GetControlMouseCurrentHitted() const
	{
		return nullptr;
	}
	//@Commit:	对于鼠标事件（移动、点击），可考虑不必对UI树进行遍历，而靠树上移动的方式去定位。
	//			1.记录当前停留的控件，m_pControlMouseCurrentHitted.
	//			2.鼠标移动的时候，将产生以下情况：
	//				a.鼠标位置仍然在该控件中，此时需考察是否进入了其孩子控件。
	//					a1.若进入到孩子控件：将m_pControlMouseCurrentHitted 设为对应孩子控件,给孩子控件发送进入事件。
	//					a2.若并没有进入孩子控件，Do nothing.
	//				b.若鼠标位置已经不在该控件中，此时只需考察其父控件P。（给该控件发送离开事件)
	//					b0.若P为nullptr，什么也不做。
	//					b1.若此时鼠标位置命中P父控件的某个孩子节点C，将m_pControlMouseCurrentHitted 设为C,给C发送进入事件。
	//					b2.若并无命中P的任何孩子节点，将m_pControlMouseCurrentHitted设为P
	void ControlManager::TranslateEvent(MEvent * e)
	{
		//鼠标事件
		if (e->GetType() == MEventType::ET_MOUSE)
		{
			//Step1.Locate which Control hitted
			MouseEvent *pne = static_cast<MouseEvent*>(e);
			auto ptMouse = pne->GetMousePos();
			auto t = pne->GetMouseEventType();
			IControl* pControlHitted;
			if (pne->GetMouseEventType() == MouseEvent::MouseEventType::MET_LEAVE)
			{
				m_pControlMouseCurrentHitted->OnMouseLeave();
				m_pControlMouseCurrentHitted = m_pWindowCanvas;
			}
			else if (pne->GetMouseEventType() == MouseEvent::MouseEventType::MET_ENTER)
			{
				if (m_pControlMouseCurrentHitted != m_pWindowCanvas)
				{
					m_pControlMouseCurrentHitted->OnMouseLeave();
				}
				IControl* pControl = m_pWindowCanvas;
				while ((pControl = pControl->FindChild(ptMouse)) != nullptr)
				{
					m_pControlMouseCurrentHitted = pControl;
				}
				m_pControlMouseCurrentHitted->OnMouseEnter();
			}
			else
			{
				//a
				if (static_cast<BaseControl*>(m_pControlMouseCurrentHitted)
					->IsMousePointerHitted(ptMouse))
				{
					//a1
					if ((pControlHitted = m_pControlMouseCurrentHitted->FindChild(ptMouse))
						!= nullptr)
					{
						m_pControlMouseCurrentHitted = pControlHitted;
						pControlHitted->OnMouseEnter();
					}
					//a2	Doing Nothing.
				}
				//b
				else
				{
					m_pControlMouseCurrentHitted->OnMouseLeave();
					IControl *pParent = m_pControlMouseCurrentHitted->GetParent();
					//b0
					if (pParent == nullptr)
						return;
					if (static_cast<BaseControl*>(pParent)->IsMousePointerHitted(ptMouse))
					{
						//b1
						if ((pControlHitted = pParent->FindChild(ptMouse)) != nullptr)
						{
							pControlHitted->OnMouseEnter();
							m_pControlMouseCurrentHitted = pControlHitted;
						}
						else
						{
							m_pControlMouseCurrentHitted = pParent;
						}
					}
				}
				m_pControlMouseCurrentHitted->EventFilter(e);
				m_pControlMouseCurrentHitted->DoAcceptEvent(e);
			}
		}
		//键盘
		else if (e->GetType() == MEventType::ET_KEYBOARD)
		{

		}
		//窗口通知
		else if (e->GetType() == MEventType::ET_CONTROL_NOTIFY)
		{
			ControlNotifyEvent *pcne = static_cast<ControlNotifyEvent*>(e);
			if (pcne->GetControlNotifyEventType() == ControlNotifyEvent::ControlNotifyEventType::CNET_PAINT)
			{
				Paint();
			}
		}
	}
	bool ControlManager::PreTranslateEvent(MEvent * e)
	{
		return false;
	}
}