
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H

#include"Framework/Common/Core/Controls/BaseControl.hpp"

namespace MDUILib
{
	m_interface BaseLayout : m_extends BaseControl
	{
	public:
		BaseLayout();
		virtual void AddControl(IControl* pControl);
		virtual void RemoveControl(IControl* pControl);
		virtual void OnPaint() override;
		virtual void Update() override;
		//Via IUnknown
		virtual IUnknown* GetInterface(const String& riiName) override
		{
			if (riiName.Compare(m_interface_name(BaseLayout)) == 0)
				return this;
			return IControl::GetInterface(riiName);
		}
		virtual String GetInterfaceName() const override
		{
			return m_interface_name(BaseLayout);
		}
	private:
		//@Commit:Hide Some useless BaseControl Method.

	};
}

#endif //MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H