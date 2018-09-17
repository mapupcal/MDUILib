
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_GRAPHICS_MCOLOR_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_GRAPHICS_MCOLOR_H
#include"Framework\Common\Utils\Utils.hpp"
namespace MDUILib
{
	//@Remark:MDUILib default color modal using argb.
	typedef struct tagMColorARGB
	{
		tagMColorARGB();
		tagMColorARGB(MDWORD HEX_ARGB);
		tagMColorARGB(unsigned char A,
			unsigned char R,
			unsigned char G,
			unsigned char B);
		unsigned char a;
		unsigned char r;
		unsigned char g;
		unsigned char b;

		friend bool operator==(const tagMColorARGB& lhs, const tagMColorARGB& rhs);
		friend bool operator!=(const tagMColorARGB& lhs, const tagMColorARGB& rhs);

		//@Remark:The Follow PreDefined Color Value copy from https://docs.microsoft.com/en-us/previous-versions/windows/silverlight/dotnet-windows-silverlight/ms653064%28v%3dvs.95%29

		const static tagMColorARGB Black;
		const static tagMColorARGB Blue;
		const static tagMColorARGB Brown;
		const static tagMColorARGB Cyan;
		const static tagMColorARGB DarkGray;
		const static tagMColorARGB Gray;
		const static tagMColorARGB Green;
		const static tagMColorARGB LightGray;
		const static tagMColorARGB Magenta;
		const static tagMColorARGB Orange;
		const static tagMColorARGB Purple;
		const static tagMColorARGB Red;
		const static tagMColorARGB Transparent;
		const static tagMColorARGB White;
		const static tagMColorARGB Yellow;
	}MColor;
	//@Remark:Line interpolate for color.t belong to float in [0,1].
	MColor LineInterp(MColor start, MColor finish, float t);
}

#endif 
