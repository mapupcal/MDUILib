#include"MColor.hpp"

namespace MDUILib
{
	bool operator==(const tagMColorARGB & lhs, const tagMColorARGB & rhs)
	{
		return (lhs.a == rhs.a) &&
			(lhs.r == rhs.r) &&
			(lhs.g == rhs.g) &&
			(lhs.b == rhs.b);
	}
	bool operator!=(const tagMColorARGB & lhs, const tagMColorARGB & rhs)
	{
		return !(lhs == rhs);
	}
	MColor LineInterp(MColor start, MColor finish, float t)
	{
		MColor ret;
		ret.a = static_cast<unsigned char>((start.a*t + finish.a*(1.0f - t)));
		ret.r = static_cast<unsigned char>((start.r*t + finish.r*(1.0f - t)));
		ret.g = static_cast<unsigned char>((start.g*t + finish.g*(1.0f - t)));
		ret.b = static_cast<unsigned char>((start.b*t + finish.b*(1.0f - t)));
		return ret;
	}

	MColor const MColor::WHITE = MColor{ 255, 255, 255, 255 };
	MColor const MColor::RED = MColor{ 255,255,0,0 };
	MColor const MColor::BLUE = MColor{ 255,0,0,255 };
	MColor const MColor::GREEN = MColor{ 255,0,255,0 };
	MColor const MColor::FULL_TRANSPARENT = MColor{ 0,0,0,0 };

	tagMColorARGB::tagMColorARGB()
		:a(0),r(0),g(0),b(0){}
	tagMColorARGB::tagMColorARGB(unsigned char A, unsigned char R, unsigned char G, unsigned char B)
		:a(A),r(R),g(G),b(B){}
}