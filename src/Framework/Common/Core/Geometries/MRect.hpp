
#ifndef MDUILIB_FRAMEWORK_COMMON_CORE_GEOMETRIES_MRECT_H
#define MDUILIB_FRAMEWORK_COMMON_CORE_GEOMETRIES_MRECT_H


/*
*	@Remark�������ڼ򵥼�����ص����ݽṹ�Լ��㷨��
*/

namespace MDUILib
{
	struct MPOINT;
	/*
	*	@ClassName:MRect
	*	@Remark:��ʾ���ε����ݽṹ��
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
	*	@Remark:��ȡ��ȡ�
	*/
	MRect::data_type GetRectWidth(const MRect& rect);

	/*
	*	@FunctionName:GetRectHeightth
	*	@ReturnType:MRect::data_type
	*	@Remark:��ȡ�߶ȡ�
	*/
	MRect::data_type GetRectHeight(const MRect& rect);

	/*
	*	@FunctionName:TranslateX(Y)
	*	@Remark:ˮƽλ�ƺ���ֱλ�ơ�
	*/
	MRect Translate(const MRect& rect, MRECT::data_type xOffset, MRect::data_type yOffset);
	MRect TranslateX(const MRect& rect, MRect::data_type xOffset);
	MRect TranslateY(const MRect& rect, MRect::data_type yOffset);
	/*
	*	@ClassName:MPoint
	*	@Remark:��ʾ���������ݽṹ��
	*	p(x,y)
	*	@Property:x[short]
	*	@Property:y[short]
	*	@Remark:ˮƽ����Ϊ��x�ᣬ��ֱ����Ϊ��y�ᡣSee Also[MRect].
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
	*	@Remark�����������������ڸ�������MRect�������Note��
	*	@Noted: ʹ�� MRect result = {top,bottom,left,right}; ����Թ���Rect,�����ܻṹ������Ϸ���Rect���ú�������Debugģʽ�¼��Rect�Ƿ�Ϸ���
	*/
	MRect CreateRect(MRect::data_type top, MRect::data_type bottom, MRect::data_type left, MRect::data_type right);

	/*
	*	@FunctionName:UnionRect
	*	@ReturnType:MRect
	*	@Parameter:validRect1[MRect],validRect2[MRect]
	*	@Remark:�������Ϸ�����opRect1��opRect2�Ĳ������Σ����ص�MRect����opRect1��opRect2����������
	*/
	MRect UnionRect(const MRect& validRect1, const MRect& validRect2);

	/*
	*	@FunctionName:IntersectRect
	*	@ReturnType:MRect
	*	@Parameter:opRect1[MRect],opRect2[MRect]
	*	@Remark:�������Ϸ�����opRect1��opRect2�Ľ������Σ����ص�MRect����opRect1��opRect2�Ĺ�������
	*	@Noted:opRect1��opRect2����û�н�������ʱ�����ص�MRect�����ǲ��Ϸ��ģ���ʹ��{bool IsValidRect(const MRect& rect)}�����жϡ�
	*/
	MRect IntersectRect(const MRect& validRect1, const MRect& validRect2);

	/*
	*	@FunctionName:IsValidRect
	*	@ReturnType:bool
	*	@Parameter:rect[MRect]
	*	@Remark:�Ϸ��ľ��α���������¹��򣬴�ʱ����true�������ǲ��Ϸ��ģ�����false��
	*	@Noted:0<=top<=bottom && 0<=left<=right
	*/
	bool IsValidRect(const MRect& rect);

	/*
	*	@FunctionName:IsPointInRect
	*	@ReturnType:bool
	*	@Parameter:point[MPoint],rect[MRect]
	*	@Remark:����point(x,y)λ�ھ����ڲ������߽磩������true�����򷵻�false
	*/
	bool IsPointInRect(const MPoint& point, const MRect& rect);

	/*
	*	@FunctionName:RectHitTest
	*	@ReturnType:bool
	*	@Parameter:rect1[MRect],rect2[MRect]
	*	@Remark:�ж����������Ƿ��ཻ���Ƿ�߱��غϵ����򣩣������ڣ�����true�����򷵻�false
	*	@Noted:�����ʹ��InterectRect�ķ��ؽ�����IsValidRect������HitTesting����ʹ��RectHitTest���졣
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
