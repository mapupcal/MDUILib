
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_GEOMETRIES_MRECT_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_GEOMETRIES_MRECT_H


/*
*	@Remark：定义于简单几何相关的数据结构以及算法。
*/

namespace MDUILib
{
	struct MPOINT;
	/*
	*	@ClassName:MRect
	*	@Remark:表示矩形的数据结构。
	*	----------top------------
	*	|						|
	*	|						|
	*  left					  right
	*	|						|
	*	|						|
	*	---------bottom----------
	*	@Property:top[short]
	*	@Property:bottom[short]
	*	@Property:left[short]
	*	@Property:right[short]
	*/
	typedef struct MRECT
	{
		using data_type = short;
		MRECT();
		MRECT(data_type top, data_type bottom, data_type left, data_type right);
		data_type top;
		data_type bottom;
		data_type left;
		data_type right;

		void MoveToPos(MPOINT pt);
	} MRect;

	const static MRect DEFAULT_RECT = { 0, 480, 0, 640 };
	/*
	*	@FunctionName:GetRectWidth
	*	@ReturnType:MRect::data_type
	*	@Remark:获取宽度。
	*/
	MRect::data_type GetRectWidth(const MRect& rect);

	/*
	*	@FunctionName:GetRectHeightth
	*	@ReturnType:MRect::data_type
	*	@Remark:获取高度。
	*/
	MRect::data_type GetRectHeight(const MRect& rect);

	/*
	*	@FunctionName:TranslateX(Y)
	*	@Remark:水平位移和竖直位移。
	*/
	MRect Translate(const MRect& rect, MRECT::data_type xOffset, MRect::data_type yOffset);
	MRect TranslateX(const MRect& rect, MRect::data_type xOffset);
	MRect TranslateY(const MRect& rect, MRect::data_type yOffset);
	/*
	*	@ClassName:MPoint
	*	@Remark:表示坐标点的数据结构。
	*	p(x,y)
	*	@Property:x[short]
	*	@Property:y[short]
	*	@Remark:水平向右为正x轴，竖直向下为正y轴。See Also[MRect].
	*/
	typedef struct MPOINT
	{
		using data_type = short;
		data_type x;
		data_type y;
		MPOINT(data_type X, data_type Y);
		friend MPOINT operator-(const MPOINT& lhs, const MPOINT &rhs);
		friend MPOINT operator+(const MPOINT& lhs, const MPOINT &rhs);
		friend float operator*(const MPOINT& lhs, const MPOINT& rhs);
	} MPoint,MVector;

	/*
	*	@FunctionName:CreateRect
	*	@RetuernType:MRect
	*	@Parameter:top[short],bottom[short],left[short],right[short]
	*	@Remark：内联函数，仅用于辅助构造MRect，详情见Note。
	*	@Noted: 使用 MRect result = {top,bottom,left,right}; 亦可以构造Rect,但可能会构造出不合法的Rect。该函数能在Debug模式下检查Rect是否合法。
	*/
	MRect CreateRect(MRect::data_type top, MRect::data_type bottom, MRect::data_type left, MRect::data_type right);

	/*
	*	@FunctionName:UnionRect
	*	@ReturnType:MRect
	*	@Parameter:validRect1[MRect],validRect2[MRect]
	*	@Remark:求两个合法矩形opRect1和opRect2的并集矩形，返回的MRect包含opRect1和opRect2的所有区域。
	*/
	MRect UnionRect(const MRect& validRect1, const MRect& validRect2);

	/*
	*	@FunctionName:IntersectRect
	*	@ReturnType:MRect
	*	@Parameter:opRect1[MRect],opRect2[MRect]
	*	@Remark:求两个合法矩形opRect1和opRect2的交集矩形，返回的MRect包含opRect1和opRect2的共有区域。
	*	@Noted:opRect1和opRect2可能没有交集，此时，返回的MRect可能是不合法的，可使用{bool IsValidRect(const MRect& rect)}函数判断。
	*/
	MRect IntersectRect(const MRect& validRect1, const MRect& validRect2);

	/*
	*	@FunctionName:IsValidRect
	*	@ReturnType:bool
	*	@Parameter:rect[MRect]
	*	@Remark:合法的矩形必须符合以下规则，此时返回true，否则将是不合法的，返回false。
	*	@Noted:0<=top<=bottom && 0<=left<=right
	*/
	bool IsValidRect(const MRect& rect);

	/*
	*	@FunctionName:IsPointInRect
	*	@ReturnType:bool
	*	@Parameter:point[MPoint],rect[MRect]
	*	@Remark:若点point(x,y)位于矩形内部（含边界），返回true。否则返回false
	*/
	bool IsPointInRect(const MPoint& point, const MRect& rect);

	/*
	*	@FunctionName:RectHitTest
	*	@ReturnType:bool
	*	@Parameter:rect1[MRect],rect2[MRect]
	*	@Remark:判断两个矩形是否相交（是否具备重合的区域），若存在，返回true。否则返回false
	*	@Noted:你可以使用InterectRect的返回结果配合IsValidRect来进行HitTesting，但使用RectHitTest更快。
	*/
	bool RectHitTest(const MRect& rect1, const MRect& rect2);


	/*
	*	@ClassName:MSize
	*	@Property:Width
	*	@Property:Height
	*/
	typedef struct MSIZE
	{
		using SizeType = short;
		SizeType Width;
		SizeType Height;
	} MSize;
}

#ifdef _WIN32
#include<Windows.h>
namespace MDUILib
{
	MRect FromWinRect(const RECT &rect);
}
#endif // _WIN32


#endif // !MDUILIB_FRAMEWORK_COMMON_CORE_GEOMETRIES_MRECT_H
