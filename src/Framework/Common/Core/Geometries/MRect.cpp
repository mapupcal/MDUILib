#include"MRect.hpp"
#include"Common\Utils\Utils.hpp"

namespace MDUILib
{

	MRECT const MRECT::DEFAULT_RECT = { 0, 480, 0, 640 };
	MRECT const MRECT::ZERO_RECT = { 0,0,0,0 };
	MRect::data_type GetRectWidth(const MRect & rect)
	{
		return rect.right - rect.left;
	}

	MRect::data_type GetRectHeight(const MRect & rect)
	{
		return rect.bottom - rect.top;
	}

	MRect Translate(const MRect & rect, MRECT::data_type xOffset, MRect::data_type yOffset)
	{
		return CreateRect(rect.top + yOffset, rect.bottom + yOffset, \
			rect.left + xOffset, rect.right + xOffset);
	}
	MRect TranslateX(const MRect & rect, MRect::data_type xOffset)
	{
		return Translate(rect, xOffset, 0);
	}
	MRect TranslateY(const MRect & rect, MRect::data_type yOffset)
	{
		return Translate(rect, 0, yOffset);
	}
	MRect TranslateToPos(const MRect & rect, MRect::data_type x, MRect::data_type y)
	{
		return TranslateToPos(rect,MPoint(x, y));
	}
	MRect TranslateToPos(const MRect & rect, MPOINT pt)
	{
		MRect rc;
		auto h = GetRectHeight(rect);
		auto w = GetRectWidth(rect);
		rc.left = pt.x;
		rc.top = pt.y;
		rc.right = rc.left + w;
		rc.bottom = rc.top + h;
		return rc;
	}
	MRect ResizeRect(const MRect & rect, int width, int height)
	{
		MRect rc = rect;
		rc.right = rc.left + width;
		rc.bottom = rc.top + height;
		return rc;
	}
	MPOINT operator-(const MPOINT & lhs, const MPOINT & rhs)
	{
		return MPOINT(lhs.x - rhs.x, lhs.y - rhs.y);
	}
	MPOINT operator+(const MPOINT & lhs, const MPOINT & rhs)
	{
		return MPOINT(lhs.x + rhs.x, lhs.y + rhs.y);
	}
	float operator*(const MPOINT & lhs, const MPOINT & rhs)
	{
		return lhs.x * rhs.x * 1.0f + lhs.y * rhs.y * 1.0f;
	}
	MRect CreateRect(MRect::data_type top, MRect::data_type bottom,\
		MRect::data_type left, MRect::data_type right)
	{
		MRect result;
		result.top = top;
		result.bottom = bottom;
		result.left = left;
		result.right = right;
		MDUILIB_ASSERT(IsValidRect(result));
		return result;
	}

	MRect UnionRect(const MRect& opRect1, const MRect& opRect2)
	{
		MDUILIB_ASSERT(IsValidRect(opRect1) && IsValidRect(opRect2));
		MRect result;
		result.top = MDUILIB_MIN(opRect1.top, opRect2.top);
		result.bottom = MDUILIB_MAX(opRect1.bottom, opRect2.bottom);
		result.left = MDUILIB_MIN(opRect1.left, opRect2.left);
		result.right = MDUILIB_MAX(opRect1.right, opRect2.right);
		return result;
	}

	MRect IntersectRect(const MRect& opRect1, const MRect& opRect2)
	{
		MDUILIB_ASSERT(IsValidRect(opRect1) && IsValidRect(opRect2));
		MRect result;
		result.top = MDUILIB_MAX(opRect1.top, opRect2.top);
		result.bottom = MDUILIB_MIN(opRect1.bottom, opRect2.bottom);
		result.left = MDUILIB_MAX(opRect1.left, opRect2.left);
		result.right = MDUILIB_MIN(opRect1.right, opRect2.right);
		/*	MDUILIB_ASSERT(IsValidRect(result));
		*	It is the Caller's Duty to Check whether the result is valid or not.		*/
		return result;
	}

	bool IsValidRect(const MRect& rect)
	{
		return rect.left >= 0 && rect.right >= rect.left
			&&	rect.top >= 0 && rect.bottom >= rect.top;
	}
	
	bool IsPointInRect(const MPoint& point, const MRect &rect)
	{
		return point.x >= rect.left&&point.x <= rect.right
			&&point.y >= rect.top&&point.y <= rect.bottom;
	}

	bool RectHitTest(const MRect& rect1, const MRect& rect2)
	{
		return (rect1.right >= rect2.left) &&
			(rect1.left <= rect2.right) &&
			(rect1.bottom >= rect2.top) &&
			(rect1.top <= rect2.bottom);
	}
	MRECT::MRECT()
		:MRECT(0,0,0,0)
	{
	}
	MRECT::MRECT(data_type t, data_type b, data_type l, data_type r)
		:top(t),bottom(b),left(l),right(r)
	{
	}

	MPOINT MRECT::GetLeftTopPoint() const
	{
		return MPoint(left, top);
	}
	MPOINT MRECT::GetLeftBottomPoint() const
	{
		return MPoint(left,bottom);
	}
	MPOINT MRECT::GetRightTopPoint() const
	{
		return MPoint(right, top);
	}
	MPOINT MRECT::GetRightBottomPoint() const
	{
		return MPoint(right, bottom);
	}
	MPOINT MRECT::GetCenterPoint() const
	{
		return MPoint((left + right) / 2, (top + bottom) / 2);
	}
	MRECT::data_type MRECT::GetWidth() const
	{
		return GetRectWidth(*this);
	}
	MRECT::data_type MRECT::GetHeight() const
	{
		return GetRectHeight(*this);
	}
	MPOINT::MPOINT(data_type X, data_type Y)
		:x(X),y(Y){}
}

#ifdef _WIN32
#include<Windows.h>
namespace MDUILib
{
	MRect FromWinRect(const RECT &rect)
	{
		MRect r;
		r.left = static_cast<MRect::data_type>(rect.left);
		r.right = static_cast<MRect::data_type>(rect.right);
		r.top = static_cast<MRect::data_type>(rect.top);
		r.bottom = static_cast<MRect::data_type>(rect.bottom);
		return r;
	}
}
#endif // _WIN32

