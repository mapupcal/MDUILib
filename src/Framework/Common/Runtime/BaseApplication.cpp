#include "BaseApplication.hpp"

int MDUILib::BaseApplication::Initialize()
{
    m_bQuit = false;
    return 0;
}

void MDUILib::BaseApplication::Finalize()
{

}

void MDUILib::BaseApplication::Quit()
{
	m_bQuit = true;
}

void MDUILib::BaseApplication::Run()
{
	while (!IsQuit())
		Tick();
}

void MDUILib::BaseApplication::Tick()
{

}

bool MDUILib::BaseApplication::IsQuit() const
{
    return m_bQuit;
}
