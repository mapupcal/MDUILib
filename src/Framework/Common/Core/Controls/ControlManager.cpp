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
	//@Commit:	��������¼����ƶ�����������ɿ��ǲ��ض�UI�����б��������������ƶ��ķ�ʽȥ��λ��
	//			1.��¼��ǰͣ���Ŀؼ���m_pControlMouseCurrentHitted.
	//			2.����ƶ���ʱ�򣬽��������������
	//				a.���λ����Ȼ�ڸÿؼ��У���ʱ�迼���Ƿ�������亢�ӿؼ���
	//					a1.�����뵽���ӿؼ�����m_pControlMouseCurrentHitted ��Ϊ��Ӧ���ӿؼ�,�����ӿؼ����ͽ����¼���
	//					a2.����û�н��뺢�ӿؼ���Do nothing.
	//				b.�����λ���Ѿ����ڸÿؼ��У���ʱֻ�迼���丸�ؼ�P�������ÿؼ������뿪�¼�)
	//					b0.��PΪnullptr��ʲôҲ������
	//					b1.����ʱ���λ������P���ؼ���ĳ�����ӽڵ�C����m_pControlMouseCurrentHitted ��ΪC,��C���ͽ����¼���
	//					b2.����������P���κκ��ӽڵ㣬��m_pControlMouseCurrentHitted��ΪP
	void ControlManager::TranslateEvent(MEvent * e)
	{
		//����¼�
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
		//����
		else if (e->GetType() == MEventType::ET_KEYBOARD)
		{

		}
		//����֪ͨ
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