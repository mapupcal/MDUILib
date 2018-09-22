
#ifndef MDUILIB_FRAMEWORK_COMMON_LAYOUTS_VERTICALLAYOUT_H
#define MDUILIB_FRAMEWORK_COMMON_LAYOUTS_VERTICALLAYOUT_H

#include "BaseLayout.hpp"

namespace MDUILib
{
	class VerticalLayout : m_extends BaseLayout
	{
	private:
		virtual void CalculateElemsPos() override;
	};
}

#endif //MDUILIB_FRAMEWORK_COMMON_LAYOUTS_HORIZONTALLAYOUT_H