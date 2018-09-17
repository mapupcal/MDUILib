
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_GRAPHICS_MCOLOR_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_GRAPHICS_MCOLOR_H

namespace MDUILib
{
	//@Remark:MDUILib default color modal using argb.
	typedef struct tagMColorARGB
	{
		tagMColorARGB();
		tagMColorARGB(unsigned char A,
			unsigned char R,
			unsigned char G,
			unsigned char B);
		unsigned char a;
		unsigned char r;
		unsigned char g;
		unsigned char b;
		const static tagMColorARGB WHITE;
		const static tagMColorARGB RED;
		const static tagMColorARGB BLUE;
		const static tagMColorARGB GREEN;
		const static tagMColorARGB FULL_TRANSPARENT;
		friend bool operator==(const tagMColorARGB& lhs, const tagMColorARGB& rhs);
		friend bool operator!=(const tagMColorARGB& lhs, const tagMColorARGB& rhs);
	}MColor;
	//@Remark:Line interpolate for color.t belong to float in [0,1].
	MColor LineInterp(MColor start, MColor finish, float t);
}

#endif 
