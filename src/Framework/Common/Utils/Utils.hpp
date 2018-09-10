#ifndef MDUILIB_FRAMEWORK_COMMON_UTILS_UTILS_H
#define MDUILIB_FRAMEWORK_COMMON_UTILS_UTILS_H

//	@MicroRemark:取最大或取最小值
#define MDUILIB_MAX(LhsNumber,RhsNumber) (LhsNumber > RhsNumber) ? LhsNumber : RhsNumber;  
#define MDUILIB_MIN(LhsNumber,RhsNumber) (LhsNumber < RhsNumber) ? LhsNumber : RhsNumber;
#define MDUILIB_OUT_ERROR(ErrorMsg) \
	do\
	{\
		printf(	"Error:%s\n" \
				"file:%s\n"  \
				"line:%d\n" ,\
				ErrorMsg,\
				__FILE__,\
				__LINE__\
			);\
	}while(0)\

#ifndef _DEBUG
#define MDUILIB_ASSERT(BoolExpression) /*Doing Nothing*/

#define MDUILIB_ASSERT_MSG(BoolExpression,MDUILIB_MSG) \
		do{\
			if(!(BoolExpression))\
			{\
				MDUILIB_OUT_ERROR(MDUILIB_MSG);\
			}\
		}while(0)\

#else
	#ifdef _MDUILIB_TEST
		#include<exception>
		#define MDUILIB_ASSERT(BoolExpression) /*For Testing,Throw a Exception.Help Test Exception TestCase.*/\
			(BoolExpression) ? "" : throw std::exception()

		#define MDUILIB_ASSERT_MSG(BoolExpression,MDUILIB_MSG) /*For Testing,Throw a Exception.Help Test Exception TestCase.*/\
			(BoolExpression) ? "" : throw std::exception()
	#else
		#include<stdlib.h>
		#define MDUILIB_ASSERT(BoolExpression) /*Aborted The Process while BoolExpression Result is false.*/ \
			(BoolExpression) ? "" : abort()

		#define MDUILIB_ASSERT_MSG(BoolExpression,MDUILIB_MSG) /*For Testing,Throw a Exception.Help Test Exception TestCase.*/\
			(BoolExpression) ? "" : abort()
	#endif // _MDUILIB_TEST
#endif // _DEBUG

namespace MDUILib
{
	using MByte = unsigned char;
	using MWORD = unsigned short;
	using MUINT = unsigned int;
	using MDWORD = unsigned long;
	using MWPARAM = MWORD;
	using MLPARAM = void*;
#ifdef _UNICODE
	using MCHAR = char;
#else
	using MCHAR = wchar_t;

#endif // _UNICODE

}

#endif // !MDUILIB_FRAMEWORK_COMMON_UTILS_UTILS_H
