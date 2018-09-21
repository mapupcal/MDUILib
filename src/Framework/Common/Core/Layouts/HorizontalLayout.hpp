
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_HORIZONTALLAYOUT_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_HORIZONTALLAYOUT_H

#include"BaseLayout.hpp"

namespace MDUILib
{
	//@Commit:水平布局器，默认从左往右逐一排列，不考虑元素越界的问题。
	class HorizontalLayout : m_extends BaseLayout
	{
	private:
		virtual void CalculateElemsPos() override;
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_HORIZONTALLAYOUT_H
