#ifndef MDUILIB_WINDOWXX_UTILS_H
#define MDUILIB_WINDOWXX_UTILS_H

namespace MDUILib
{
	//	@Remark:安全释放Com组件
	template<typename Interface>
	inline void SafeRelease(Interface **ppInterfaceToRelease)
	{
		if (*ppInterfaceToRelease != NULL)
		{
			(*ppInterfaceToRelease)->Release();
			(*ppInterfaceToRelease) = NULL;
		}
	}
}

#endif // !MDUILIB_WINDOWXX_UTILS_H
