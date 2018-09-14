#include"MColor.hpp"

namespace MDUILib
{
	MColor LineInterp(MColor start, MColor finish, float t)
	{
		MColor ret;
		ret.a = static_cast<unsigned char>((start.a*t + finish.a*(1.0f - t)));
		ret.r = static_cast<unsigned char>((start.r*t + finish.r*(1.0f - t)));
		ret.g = static_cast<unsigned char>((start.g*t + finish.g*(1.0f - t)));
		ret.b = static_cast<unsigned char>((start.b*t + finish.b*(1.0f - t)));
		return ret;
	}
}