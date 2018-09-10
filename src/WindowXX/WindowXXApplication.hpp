
#ifndef MDUILIB_WINDOWXX_WINDOWXXAPPLICATION_H
#define MDUILIB_WINDOWXX_WINDOWXXAPPLICATION_H

#include "BaseApplication.hpp"

namespace MDUILib
{
	class WindowXXApplication : extends BaseApplication
	{
	public:
		int Initialize() override;
		void Finalize() override;
	private:
		void Tick() override;
	};
}

#endif // !MDUILIB_WINDOWXX_WINDOWXXAPPLICATION_H
