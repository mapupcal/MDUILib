
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_IWINDOWFACTORY_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_IWINDOWFACTORY_H

//@Remark:We Could not Draw The Platform Specifics Windows.So We Need the Windows Factory Class
//		  to Create the Platform Specifics Windows.

#include"Framework\Common\Core\Windows\IWindow.hpp"
#include"Framework\Common\Core\IUnknown.hpp"
#include"Framework\Common\Utils\MString.hpp"

namespace MDUILib
{
	m_interface IWindowFactory : m_implements IUnknown
	{
		virtual IWindow* CreateBaseWindow() = 0;
		
		virtual AString GetInterfaceName() const override
		{
			return m_interface_name(IWindowFactory);
		}
		virtual IUnknown* GetInterface(const AString &riiName) override
		{
			if (riiName.Compare(m_interface_name(IWindowFactory)) == 0)
				return this;
			return IUnknown::GetInterface(riiName);
		}
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_WINDOWS_IWINDOWFACTORY_H
