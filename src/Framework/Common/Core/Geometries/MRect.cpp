#include"MRect.hpp"
#include"Utils.hpp"

namespace MDUILib
{
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
	MRect CreateRect(MRect::data_type top, MRect::data_type bottom,\
		MRect::data_type left, MRect::data_type right)
	{
		MRect result;
		result.top = top;
		result.bottom = bottom;
		result.left = left;
		result.right = right;
		MDUILib_ASSERT(IsValidRect(result));
		return result;
	}

	MRect UnionRect(const MRect& opRect1, const MRect& opRect2)
	{
		MDUILib_ASSERT(IsValidRect(opRect1) && IsValidRect(opRect2));
		MRect result;
		result.top = MDUILib_MIN(opRect1.top, opRect2.top);
		result.bottom = MDUILib_MAX(opRect1.bottom, opRect2.bottom);
		result.left = MDUILib_MIN(opRect1.left, opRect2.left);
		result.right = MDUILib_MAX(opRect1.right, opRect2.right);
		return result;
	}

	MRect IntersectRect(const MRect& opRect1, const MRect& opRect2)
	{
		MDUILib_ASSERT(IsValidRect(opRect1) && IsValidRect(opRect2));
		MRect result;
		result.top = MDUILib_MAX(opRect1.top, opRect2.top);
		result.bottom = MDUILib_MIN(opRect1.bottom, opRect2.bottom);
		result.left = MDUILib_MAX(opRect1.left, opRect2.left);
		result.right = MDUILib_MIN(opRect1.right, opRect2.right);
		/*	MDUILib_ASSERT(IsValidRect(result));
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
}