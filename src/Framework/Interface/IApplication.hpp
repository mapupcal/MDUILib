
#ifndef MDUILIB_FRAMEWORK_INTERFACE_IAPPLICATION_H
#define MDUILIB_FRAMEWORK_INTERFACE_IAPPLICATION_H

#include "Interface.hpp"
#include "IRuntime.hpp"
#include "Framework\Common\Core\IUnknown.hpp"

namespace MDUILib
{
	m_interface IApplication : 
			m_implements IRuntimeModule
	{
		virtual int Initialize() = 0;
		virtual void Finalize() = 0;
		//@Remark:主消息循环中的一个循环。
		virtual void Tick() = 0;

		//@Remark:强制退出
		virtual void Quit() = 0;

		//@Remark:询问当前程序是否需要推出。
		virtual bool IsQuit() const = 0;

		virtual AString GetInterfaceName() const override
		{
			return m_interface_name(IApplication);
		}
		virtual IUnknown* GetInterface(const AString& riiName) override
		{
			if (riiName.Compare(m_interface_name(IApplication)) == 0)
				return this;
			return IRuntimeModule::GetInterface(riiName);
		}
	};
}
#endif //MDUILIB_FRAMEWORK_INTERFACE_IAPPLICATION_H