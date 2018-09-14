#ifndef MDUILIB_WINDOWXX_UTILS_H
#define MDUILIB_WINDOWXX_UTILS_H

namespace MDUILib
{
	//	@Remark:��ȫ�ͷ�Com���
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
