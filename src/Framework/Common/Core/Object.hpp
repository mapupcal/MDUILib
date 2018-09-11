
#ifndef MDUILIB_FRAMEWORK_CORE_OBJECT_H
#define MDUILIB_FRAMEWORK_CORE_OBJECT_H

#include"Framework\Common\Utils\MString.hpp"
#include"Framework\Common\Utils\Utils.hpp"
#include"Framework\Common\Utils\Any.hpp"

namespace MDUILib
{
	struct NoCopyable
	{
		NoCopyable() {}
		NoCopyable(const NoCopyable &other) = delete;
	};

	class Object : public NoCopyable
	{
	public:
		Object();
		virtual ~Object();
		//@Remark:Use these Method to attach properties to the Object.
		//.e.g	Object* pObj = .... 
		//		MString data1_str = "data1_str_data_blahblah..."
		//		pObj->SetProperty("data1",data1_str)
		//		...;	//doing something.
		//		Any any = pObj->GetProperty("data1");
		//		if((!any.Empty()) && any.CanCast<MString>())
		//			MString *p_str = any.ForceCastTo<MString>();
		void SetProperty(const String &propertyField, const Any &anyValue);
		Any GetProperty(const String &propertyField) const;
	private:
		Any *pPropertiesMaps;
	};
}

#endif // !MDUILIB_FRAMEWORK_CORE_OBJECT_H
