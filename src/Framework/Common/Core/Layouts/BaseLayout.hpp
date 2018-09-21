
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_LAYOUTS_ILAYOUT_H

#include"Framework/Common/Core/Controls/BaseControl.hpp"

namespace MDUILib
{
	//@Noted:	���뵽Layout���еĿؼ���������λ�õ����ԣ���λ�ý���Ӧ�������ڻ���
	//			֮ǰ�Զ��޸��������λ�á�
	//			ĳЩ�������������߱��޸���Ԫ�ؿؼ�����MRect��������
	class BaseLayout : m_extends BaseControl
	{
	public:
		BaseLayout();
		virtual void AddControl(IControl* pControl);
		virtual void RemoveControl(IControl* pControl);
		virtual void OnPaint() override;
		virtual void Update() override;
		//@Rmarks:��������Ԫ����߾�֮��Ӧ�еľ��롣
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