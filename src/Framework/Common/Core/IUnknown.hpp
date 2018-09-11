
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_IUNKNOWN_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_IUNKNOWN_H

#include"Framework\Common\Utils\MString.hpp"

#define CRTII_NAME_IUNKNOWN "CRTII_IUNKNOWN"

namespace MDUILib
{
	struct IUnknown
	{
		virtual ~IUnknown() {}
		/*
		*	@Remark:获取最左接口的类型字符串。
		*/
		virtual AString GetInterfaceName() const
		{
			return CRTII_NAME_IUNKNOWN;
		}
		/*
		*	@Remark:查询该对象是否具备输入类名的接口。用于指针向下转型，配合GetClassName，使用者必须知道继承链。
		*	@Noted:	比如，有继承链 IUnknownUI <- IControl <- Button.
		*			我们获得了一个IUnknown类型的指针pObj（指向Button），先通过GetClassName获得该派生类类型字符串(maybe. "MDUILIB_BUTTON")，在继承链中-
		*			我们想要使用该对象的IControl(maybe. "MDUILIB_ICONTROL")的一个SetText接口，则利用以下语法：
		*			IControl* pCtrl = static_cast<IControl*>(pOj->GetInterface("MDUILIB_ICONTROL"))
		*			pCtrl->SetText("XXXX");
		*/
		virtual IUnknown* GetInterface(const AString& riiName)
		{
			if (riiName.Compare(CRTII_NAME_IUNKNOWN) == 0)
				return this;
			return nullptr;
		}
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_IUNKNOWN_H
