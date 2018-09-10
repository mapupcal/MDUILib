#ifndef MDUILIB_FRAMEWORK_INTERFACE_IAPPLICATION_H
#define MDUILIB_FRAMEWORK_INTERFACE_IAPPLICATION_H

#include "Interface.hpp"
#include "IRuntime.hpp"

namespace MDUILib
{
    interface IApplication : implements IRuntimeModule
    {
        virtual int Initialize() = 0;
        virtual void Finalize() = 0;
        //@Remark:主消息循环中的一个循环。
        virtual void Tick() = 0;

		//@Remark:强制退出
		virtual void Quit() = 0;

        //@Remark:询问当前程序是否需要推出。
        virtual bool IsQuit() const = 0;
	};
}
#endif //MDUILIB_FRAMEWORK_INTERFACE_IAPPLICATION_H