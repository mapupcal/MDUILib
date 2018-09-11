#include"Object.hpp"
#include<map>

using namespace std;

namespace MDUILib
{
	Object::Object()
	{
		pPropertiesMaps = new Any(map<String, Any>());
	}
	Object::~Object()
	{
		delete pPropertiesMaps;
	}
	void Object::SetProperty(const String &propertyField, const Any &anyValue)
	{
		auto pMaps = pPropertiesMaps->ForceCastTo<map<String, Any>>();
		(*pMaps)[propertyField] = anyValue;
	}
	Any Object::GetProperty(const String &propertyField) const
	{
		auto pMaps = pPropertiesMaps->ForceCastTo<map<String, Any>>();
		auto pMapsIter = pMaps->find(propertyField);
		if (pMapsIter != pMaps->cend())
			return pMapsIter->second;
		return Any();
	}
}