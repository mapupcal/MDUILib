
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H

#include"Framework/Common/Core/Controls/BaseControl.hpp"

namespace MDUILib
{
	//@Noted:	加入到Layout当中的控件将放弃其位置的属性，其位置将相应布局器在绘制
	//			之前自动修改其自身的位置。
	//			某些布局器甚至还具备修改其元素控件绘制MRect的能力。
	class BaseLayout : m_extends BaseControl
	{
	public:
		BaseLayout();
		virtual void AddControl(IControl* pControl);
		virtual void RemoveControl(IControl* pControl);
		virtual void OnPaint() override;
		virtual void Update() override;
		//@Rmarks:设置两个元素外边距之间应有的距离。
		void SetStrech(MUINT pix = 0);
		int GetStrech() const;
	private:
		virtual void CalculateElemsPos();
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
	private:
		MUINT m_uStrechPix;
	};
}

#endif //MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H