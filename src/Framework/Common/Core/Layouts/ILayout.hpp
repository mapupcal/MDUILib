
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H

#include"Framework/Common/Core/Controls/IControl.hpp"

namespace MDUILib
{
	m_interface ILayout : m_implements IControl
	{
	public:
		virtual void AddControl(IControl* pControl) = 0;
		virtual void RemoveControl(IControl* pControl) = 0;
		virtual void OnPaint() = 0;
		//Via IUnknown
		virtual IUnknown* GetInterface(const String& riiName) override
		{
			if (riiName.Compare(m_interface_name(ILayout)) == 0)
				return this;
			return IControl::GetInterface(riiName);
		}
		virtual String GetInterfaceName() const override
		{
			return m_interface_name(ILayout);
		}
	private:
		//@Remarks:Hide IControl's Method.
		
	};
}

#endif //MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H