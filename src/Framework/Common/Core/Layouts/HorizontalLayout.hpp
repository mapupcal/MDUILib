
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_HORIZONTALLAYOUT_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_HORIZONTALLAYOUT_H

#include"BaseLayout.hpp"

namespace MDUILib
{
	//@Commit:ˮƽ��������Ĭ�ϴ���������һ���У�������Ԫ��Խ������⡣
	class HorizontalLayout : m_extends BaseLayout
	{
	private:
		virtual void CalculateElemsPos() override;
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_HORIZONTALLAYOUT_H
