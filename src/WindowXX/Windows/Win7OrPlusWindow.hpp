
#ifndef MDUILIB_WINDOWXX_WINDOWS_WIN7ORPLUSWINDOW_H
#define MDUILIB_WINDOWXX_WINDOWS_WIN7ORPLUSWINDOW_H

#include"WindowXX\Windows\WinXXWindow.hpp"

namespace MDUILib
{
	class Win7OrPlusWindow : m_extends WinXXWindow
	{
	public:
		Win7OrPlusWindow();
		~Win7OrPlusWindow();
		virtual IWindow * CreateSubWindow(const String & subWndTittleName, const MRect & relativePositionRect, bool bModal = false) override;
	};
}

#endif // !MDUILIB_WINDOWXX_WINDOWS_WIN7ORPLUSWINDOW_H
