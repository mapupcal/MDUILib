
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_IUNKNOWN_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_IUNKNOWN_H

#include"Framework\Common\Utils\MString.hpp"

namespace MDUILib
{
	struct IUnknown
	{
		virtual ~IUnknown() {}
		/*
		*	@Remark:��ȡ����ӿڵ������ַ�����
		*/
		virtual AString GetInterfaceName() const
		{
			return m_interface_name(IUnknown);
		}
		/*
		*	@Remark:��ѯ�ö����Ƿ�߱����������Ľӿڡ�����ָ������ת�ͣ����GetClassName��ʹ���߱���֪���̳�����
		*	@Noted:	���磬�м̳��� IUnknownUI <- IControl <- Button.
		*			���ǻ����һ��IUnknown���͵�ָ��pObj��ָ��Button������ͨ��GetClassName��ø������������ַ���(maybe. "MDUILIB_BUTTON")���ڼ̳�����-
		*			������Ҫʹ�øö����IControl(maybe. "MDUILIB_ICONTROL")��һ��SetText�ӿڣ������������﷨��
		*			IControl* pCtrl = static_cast<IControl*>(pOj->GetInterface("MDUILIB_ICONTROL"))
		*			pCtrl->SetText("XXXX");
		*/
		virtual IUnknown* GetInterface(const AString& riiName)
		{
			if (riiName.Compare(m_interface_name(IUnknown)) == 0)
				return this;
			return nullptr;
		}
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_IUNKNOWN_H
