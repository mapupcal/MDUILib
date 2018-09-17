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

	tagMColorARGB::tagMColorARGB()
		:a(0),r(0),g(0),b(0){}
	tagMColorARGB::tagMColorARGB(MDWORD HEX_ARGB)
	{
		a = static_cast<unsigned char>((HEX_ARGB >> 24) & 0xFF);
		r = static_cast<unsigned char>((HEX_ARGB >> 16) & 0xFF);
		g = static_cast<unsigned char>((HEX_ARGB >> 8) & 0xFF);
		b = static_cast<unsigned char>(HEX_ARGB & 0xFF);
	}
	tagMColorARGB::tagMColorARGB(unsigned char A, unsigned char R, unsigned char G, unsigned char B)
		:a(A),r(R),g(G),b(B){}

	MColor const MColor::Black = MColor(0xFF000000);
	MColor const MColor::Blue = MColor(0xFF0000FF);
	MColor const MColor::Brown = MColor(0xFFA52A2A);
	MColor const MColor::Cyan = MColor(0xFF00FFFF);
	MColor const MColor::DarkGray = MColor(0xFFA9A9A9);
	MColor const MColor::Gray = MColor(0xFF808080);
	MColor const MColor::Green = MColor(0xFF008000);
	MColor const MColor::LightGray = MColor(0xFFD3D3D3);
	MColor const MColor::Magenta = MColor(0xFFFF00FF);
	MColor const MColor::Orange = MColor(0xFFFFA500);
	MColor const MColor::Purple = MColor(0xFF800080);
	MColor const MColor::Red = MColor(0xFFFF0000);
	MColor const MColor::Transparent = MColor(0xFFFFFF);
	MColor const MColor::White = MColor(0xFFFFFFFF);
	MColor const MColor::Yellow = MColor(0xFFFFFF00);
}