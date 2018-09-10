#ifndef MDUILIB_FRAMEWORK_INTERFACE_IRUNTIME_H
#define MDUILIB_FRAMEWORK_INTERFACE_IRUNTIME_H

#include "Interface.hpp"

namespace MDUILib
{
    interface IRuntimeModule
    {
        virtual ~IRuntimeModule() {};
        virtual int Initialize() = 0;
        virtual void Finalize() = 0;
        virtual void Tick() = 0;
	};
}
#endif //MDUILIB_FRAMEWORK_INTERFACE_IRUNTIME_H