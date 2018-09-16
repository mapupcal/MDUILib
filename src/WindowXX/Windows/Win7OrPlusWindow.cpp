#include"Win7OrPlusWindow.hpp"
#include"WindowXX\Graphics\Win7OrPlusRenderSystem.hpp"

namespace MDUILib
{
	Win7OrPlusWindow::Win7OrPlusWindow()
	{
		m_pRenderSystem = new Win7OrPlusRenderSystem();
	}
	Win7OrPlusWindow::~Win7OrPlusWindow()
	{
		delete m_pRenderSystem;
	}
}