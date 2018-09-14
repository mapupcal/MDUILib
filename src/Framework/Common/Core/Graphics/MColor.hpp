
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_GRAPHICS_MCOLOR_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_GRAPHICS_MCOLOR_H

namespace MDUILib
{
	//@Remark:MDUILib default color modal using argb.
	typedef struct tagMColorARGB
	{
		unsigned char a;
		unsigned char r;
		unsigned char g;
		unsigned char b;
	}MColor;

	//@Remark:Line interpolate for color.t belong to float in [0,1].
	MColor LineInterp(MColor start, MColor finish, float t);
}

#endif 
