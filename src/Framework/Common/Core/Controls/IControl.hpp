
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_ICONTROL_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_ICONTROL_H

#include"Framework\Interface\Interface.hpp"
#include"Common\Core\IUnknown.hpp"

namespace MDUILib
{
	m_interface IControl : m_implements IUnknown
	{
		//TODO:�ؼ��Ĺ����ӿ�
		virtual void SetText(const String& text) = 0;
		virtual void GetText() const = 0;

		AString GetInterfaceName() const override
		{
			return m_interface_name(IControl);
		}
		IUnknown* GetInterface(const AString &riiName) override
		{
			if (riiName.Compare(m_interface_name(IControl)))
				return this;
			return IUnknown::GetInterface(riiName);
		}
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_CONTROLS_ICONTROL_H
