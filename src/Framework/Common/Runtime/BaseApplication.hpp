#ifndef MDUILIB_FRAMEWORK_COMMON_BASEAPPLICATION_H
#define MDUILIB_FRAMEWORK_COMMON_BASEAPPLICATION_H

#include "Framework\Interface\IApplication.hpp"
#include "Framework\Common\Core\Object.hpp"
#include "Framework\Common\Core\Windows\BaseWindow.hpp"

namespace MDUILib
{
    class BaseApplication : m_extends Object, m_implements IApplication
    {
	public:
		void Run();
    public:
        virtual int Initialize() override;
        virtual void Finalize() override;
		virtual void Quit() override;
	private:
        virtual void Tick() override;
        virtual bool IsQuit() const override;
    protected:
        //@Remark:是否需要退出应用主循环的标识。
		BaseWindow *m_pMainWindow;
        bool m_bQuit;
	};
}
#endif //MDUILIB_FRAMEWORK_COMMON_BASEAPPLICATION_H