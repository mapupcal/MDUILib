#include "BaseApplication.hpp"

namespace MDUILib
{
	int BaseApplication::Initialize()
	{
		m_bQuit = false;
		return 0;
	}

	void BaseApplication::Finalize()
	{

	}

	void BaseApplication::Quit()
	{
		m_bQuit = true;
	}

	void BaseApplication::Run()
	{
		while (!IsQuit())
			Tick();
	}

	void BaseApplication::Tick()
	{

	}

	bool BaseApplication::IsQuit() const
	{
		return m_bQuit;
	}
}
