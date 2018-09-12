
#ifndef MDUILIB_FRAMEWORK_INTERFACE_IRUNTIME_H
#define MDUILIB_FRAMEWORK_INTERFACE_IRUNTIME_H

#include "Interface.hpp"
#include "Framework\Common\Core\IUnknown.hpp"

namespace MDUILib
{
    m_interface IRuntimeModule : m_implements IUnknown
    {
        virtual ~IRuntimeModule() {};
        virtual int Initialize() = 0;
        virtual void Finalize() = 0;
        virtual void Tick() = 0;

		virtual AString GetInterfaceName() const override
		{
			return m_interface_name(IRuntimeModule);
		}
		virtual IUnknown* GetInterface(const AString& riiName) override
		{
			if (riiName.Compare(m_interface_name(IRuntimeModule)) == 0)
				return this;
			return IUnknown::GetInterface(riiName);
		}
	};
}
#endif //MDUILIB_FRAMEWORK_INTERFACE_IRUNTIME_H