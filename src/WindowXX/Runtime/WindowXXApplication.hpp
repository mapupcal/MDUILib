
#ifndef MDUILIB_WINDOWXX_WINDOWXXAPPLICATION_H
#define MDUILIB_WINDOWXX_WINDOWXXAPPLICATION_H

#include "Framework\Interface\Interface.hpp"
#include "Framework\Common\Runtime\BaseApplication.hpp"

namespace MDUILib
{
	class WindowXXApplication : m_extends BaseApplication
	{
	public:
		int Initialize() override;
		void Finalize() override;
	private:
		void Tick() override;
	};
}

#endif // !MDUILIB_WINDOWXX_WINDOWXXAPPLICATION_H
