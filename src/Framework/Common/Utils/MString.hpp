
#ifndef MDUILIB_FRAMEWORK_COMMON_UTILS_MSTRING_H
#define MDUILIB_FRAMEWORK_COMMON_UTILS_MSTRING_H

#include"Utils.hpp"
#include<vector>
#include<codecvt>
/*
*	@Remark:重新写一个字符串类（模板），添加处理字符串方便的辅助函数。
*/
namespace MDUILib
{
	/*
	*	@EnumClassName:CaseSensitity
	*	@EnumValue:CaseSensitive
	*	@EnumValue:CaseInSensitive
	*/
	enum class CaseSensitivity
	{
		CaseSensitive,
		CaseInSensitive
	};

	/*
	*	@EnumClassName:IntegerBase
	*	@EnumValue:BINARY,二进制
	*	@EnumValue：OCTAL,八进制
	*	@EnumValue:DECIMAL，十进制
	*	@EnumValue：HEXDECIMAL,十六进制
	*/

	enum class IntegerBase
	{
		BINARY,
		OCTAL,
		DECIMAL,
		HEXADECIMAL
	};

	/*
	*	@GernericClassName:MStringTextCodec[CharType]
	*	@Remark:该模板类用于处理字符串的编解码
	*/

	template<typename CharType>
	struct MStringTextCodec;

	/*
	*	@GernericClassName:MString[Type]
	*	@StaticAttribute:null[Type],常量指针指向nullptr，表示空字符串指向的位置。
	*	@Attribute:counter[size_t],引用计数所使用的计数器。
	*	@Attribute:buffer[Type],指向字符串的缓存的位置，一般是堆内存。
	*	@Attribute:strStart[size_type=unsigned int],buffer+start表示该字符串的开始。
	*	@Attribute：len[size_type=unsigned int],表示字符串的长度
	*	@Attribute：allocLen[size_type=unsigned int],表示buffer的大小。
	*	@Remark:该字符串模板类是不可变的字符串类，当对字符串进行写的时候，会自动复制一份。
	*	@Remark:buffer的内存管理使用引用计数的方式。
	*/

	template<typename CharType>
	class MString
	{
	public:
		using type = CharType;
		using size_type = unsigned int;
		using StringList = std::vector<MString>;
		using const_iterator = const type*;
		friend struct MStringTextCodec<CharType>;
	private:
		mutable volatile size_t *counter;
		mutable type* buffer;
		mutable size_type strStart;
		mutable size_type len;
		mutable size_type allocLen;

		static size_t _CountCStr(const type *c_str)
		{
			size_t cnt = 0;
			while (*c_str++) cnt++;
			return cnt;
		}
		static void _Fill(type *dst, type val, int num)
		{
			MDUILIB_ASSERT(num > 0);
			while (num-- > 0)
				*dst++ = val;
		}

		MString(size_type allocLength)
		{
			MDUILIB_ASSERT(allocLength >= 0);

			if (allocLength > 0)
			{
				buffer = reinterpret_cast<type*>(malloc(allocLength * sizeof(type)));
				MDUILIB_ASSERT(buffer != nullptr);
			}
			counter = new size_t(1);
			MDUILIB_ASSERT(counter != nullptr);
			strStart = 0;
			len = 0;
			allocLen = allocLength;
		}

		int __XXXXIndexOf(const_iterator(MString::*begIterFunc)()const, \
			const_iterator(MString::*endIterFunc)()const, \
			const MString &str, int from = 0, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			MDUILIB_ASSERT(str.Length() > 0u);
			MDUILIB_ASSERT(static_cast<size_type>(from) <= Length());
			const_iterator this_iter, this_end, str_iter, str_end;
			this_iter = (this->*begIterFunc)() + from;
			this_end = (this->*endIterFunc)();
			str_end = (str.*endIterFunc)();
			int index = -1;
			while (this_iter != this_end && (this_end - this_iter) >= str.Length())
			{
				auto current_beg = this_iter;
				str_iter = (str.*begIterFunc)();
				while (str_iter != str_end)
				{
					if (MStringTextCodec<type>::Compare(*current_beg, *str_iter, cs) == 0)
					{
						current_beg++;
						str_iter++;
					}
					else
					{
						break;
					}
				}
				if (str_iter == str_end)
				{
					index = this_iter - (this->*begIterFunc)();
					break;
				}
				this_iter++;
			}
			return index;
		}

	public:
		/*
		*	@FuncName:Swap
		*	@Parameter:other[MSTring&],另外一个字符串的引用。
		*	@Remark：与other交换数据
		*/
		void Swap(MString &other)
		{
			std::swap(buffer, other.buffer);
			std::swap(counter, other.counter);
			std::swap(len, other.len);
			std::swap(allocLen, other.allocLen);
			std::swap(strStart, other.strStart);
		}
		/*
		*	@FunctionName:DefaultConstructor
		*/
		MString()
			:buffer(nullptr), strStart(0), len(0), allocLen(0)
		{
			counter = new size_t(1);
			MDUILIB_ASSERT(counter != nullptr);
		}

		
		/*
		*	@FuncName:Constructor
		*	@Parameter:c_str[type*],c语言格式的字符串。
		*	@Remark:从c语言格式的字符串构造出一个MString。
		*/
		MString(const type *c_str)
		{
			auto bytesSize = _CountCStr(c_str) * sizeof(type);
			if (bytesSize != 0)
			{
				buffer = reinterpret_cast<type*>(malloc(bytesSize));
				MDUILIB_ASSERT(buffer != nullptr);
				errno_t r = memcpy_s(buffer, bytesSize, c_str, bytesSize);
				MDUILIB_ASSERT(r == 0);
			}
			else
			{
				buffer = nullptr;
			}
			counter = new size_t(1);
			MDUILIB_ASSERT(counter != nullptr);
			strStart = 0;
			len = allocLen = static_cast<size_type>(bytesSize / sizeof(type));
		}
		/*
		*	@FuncName:Contructor
		*	@Parameter:c_str[type*],c语言格式的字符串。
		*	@Parameter:length,表示字符串的长度。
		*	@Remark:从c语言格式的字符串构造出一个MString。
		*/
		MString(type *c_str, size_type length)
		{
			MDUILIB_ASSERT(length != 0);
			auto bytesSize = length * sizeof(type);
			buffer = reinterpret_cast<type*>(malloc(bytesSize));
			MDUILIB_ASSERT(buffer != nullptr);
			errno_t r = memcpy_s(buffer, bytesSize, c_str, bytesSize);
			MDUILIB_ASSERT(r == 0);
			counter = new size_t(1);
			MDUILIB_ASSERT(counter != nullptr);
			strStart = 0;
			len = allocLen = static_cast<size_type>(length);
		}

		/*
		*	@FuncName:Contructor
		*	@Parameter:ch[type]
		*	@Parameter:num[size_t]
		*	@Remark:产生num个连续字符ch的字符串。
		*/
		MString(type ch, size_t num)
		{
			MDUILIB_ASSERT(num > 0);
			buffer = reinterpret_cast<type*>(malloc(num * sizeof(type)));
			MDUILIB_ASSERT(buffer != nullptr);
			strStart = 0;
			counter = new size_t(1);
			MDUILIB_ASSERT(counter != nullptr);
			len = allocLen = static_cast<size_type>(num);
			_Fill(buffer, ch, static_cast<int>(num));
		}

		/*
		*	@FuncName：Copy Constructor
		*	@Remark：递增引用计数。
		*/
		MString(const MString &other)
		{
			counter = other.counter;
			strStart = other.strStart;
			len = other.len;
			allocLen = other.AllocLength();
			buffer = other.buffer;
			MDUILIB_ASSERT(counter != nullptr);
			(*counter)++;
		}
		/*
		*	@FuncName:Move Constructor
		*	@Remark:移动构造函数，无需递增引用计数。但将右值的指针置为nullptr
		*/
		MString(MString &&other)
		{
			counter = other.counter;
			strStart = other.strStart;
			len = other.len;
			allocLen = other.allocLen;
			buffer = other.buffer;
			other.buffer = nullptr;
			other.counter = nullptr;
		}
		/*
		*	@FuncName:Deconstructor
		*	@Remark:递减引用计数，若再无其它对象引用该buffer，delete之。
		*/
		~MString()
		{
			if (counter != nullptr)
			{
				MDUILIB_ASSERT((*counter > 0));
				(*counter)--;
				if (*counter == 0)
				{
					if (buffer != nullptr)
					{
						::free((void*)buffer);
						buffer = nullptr;
					}
					delete counter;
					counter = nullptr;
				}
			}
		}

		/*
		*	@FuncName:Copy Assign Operator
		*	@Remark:CopyAndSwap
		*/
		MString &operator=(const MString& rhs)
		{
			MString temp(rhs);
			Swap(temp);
			return *this;
		}

		/*
		*	@FuncName:Move Assign Operator
		*	@Remark:CopyAndSwap
		*/
		MString &operator=(MString &&rhs)
		{
			MString temp(static_cast<MString&>(rhs));
			Swap(temp);
			return *this;
		}

		/*
		*	@FuncName:Append
		*	@ReturnType：MString&,指向自己的字符串。
		*	@Parameter:str[MString],要接到该字符串末尾的字符串。
		*	@Remark:注意，该方法将返回一个新buffer的字符串。除非该字符独占buffer并且buffer足够大，此时，将尝试在原有的buffer中修改自身。
		*	@Remark:特殊情况，当添加到末尾的字符串为空字符串，此时什么也不会修改。
		*/
		MString& Append(const MString &str)
		{
			return Insert(static_cast<int>(len), str);
		}

		/*
		*	@FuncName:Append
		*	@ReturnType：MString&,指向自己的字符串。
		*	@Parameter:ch[type],要追加的字符。
		*	@Parameter:num[size_t],追加的字符数量。
		*	@Remark:注意，该方法将返回一个新buffer的字符串。除非该字符独占buffer并且buffer足够大，此时，将尝试在原有的buffer中修改自身。
		*/
		MString& Append(type ch, size_t num = 1)
		{
			MDUILIB_ASSERT(num > 0);
			return Insert(static_cast<int>(len), ch, num);
		}

		MString& Prepend(const MString &str)
		{
			return Insert(0, str);
		}

		/*
		*	@FuncName:Prepend
		*	@ReturnType：MString&,指向自己的字符串。
		*	@Parameter:ch[type],要前置追加的字符。
		*	@Parameter:num[size_t],追加的字符数量。
		*	@Remark:注意，该方法将返回一个新buffer的字符串。除非该字符独占buffer并且buffer足够大，此时，将尝试在原有的buffer中修改自身。
		*/
		MString& Prepend(type ch, size_t num = 1)
		{
			MDUILIB_ASSERT(num > 0);
			return Insert(0, ch, num);
		}

		/*
		*	@FuncName:CharAt
		*	@ReturnType:type
		*	@Parameter:index[int]
		*	@Remark:返回对应下标的字符。
		*/
		const type CharAt(int index) const
		{
			MDUILIB_ASSERT(index >= 0);
			MDUILIB_ASSERT(index < static_cast<int>(Length()));
			return (buffer + strStart)[index];
		}

		/*
		*	@FuncNameInsert
		*	@ReturnType:MString&,指向当前字符串
		*	@Parameter:position[size_type]
		*	@Parameter:str[MString],插入的字符串
		*	@Remark:在原本的字符串的position处插入相应的字符。如果原本的字符串是被当前对象独享，并且buffer够大，可不需要重新分配内存。
		*/
		MString& Insert(int position, const MString &str)
		{
			if (str.Length() <= 0)
				return *this;
			MDUILIB_ASSERT(position >= 0);
			size_type truncLen = static_cast<size_type>(position);
			MDUILIB_ASSERT(truncLen <= len);
			MDUILIB_ASSERT(counter != nullptr);
			if (*counter == 1 && AllocLength() >= Length() + str.Length())
			{
				errno_t r = 0;
				//	拷贝前半部分
				if (strStart != 0)
					r = memmove_s(buffer + 0, truncLen*sizeof(type), buffer + strStart, truncLen * sizeof(type));
				MDUILIB_ASSERT(r == 0);
				//	拷贝后半部分
				r = memmove_s(buffer + truncLen + str.Length(), (Length() - truncLen) * sizeof(type), \
					buffer + strStart + truncLen, (Length() - truncLen) * sizeof(type));
				MDUILIB_ASSERT(r == 0);
				//	将字符串复制到对应内存中
				r = memcpy_s(buffer + position, str.Length() * sizeof(type), \
					str.buffer + str.strStart, str.Length() * sizeof(type));
				MDUILIB_ASSERT(r == 0);
				strStart = 0;
				len = Length() + str.Length();
				return *this;
			}
			else
			{
				MString temp((Length() + str.Length()) * 2);
				//	前半部分
				errno_t r = memcpy_s(temp.buffer, truncLen * sizeof(type), buffer + strStart, truncLen * sizeof(type));
				MDUILIB_ASSERT(r == 0);
				//	对应字符串
				r = memcpy_s(temp.buffer + position, str.Length() * sizeof(type), \
					str.buffer + str.strStart, str.Length() * sizeof(type));
				MDUILIB_ASSERT(r == 0);
				//	后半部分
				r = memcpy_s(temp.buffer + position + str.Length(), (Length() - truncLen) * sizeof(type), \
					buffer + strStart + position, (Length() - truncLen) * sizeof(type));
				MDUILIB_ASSERT(r == 0);
				temp.len = Length() + str.Length();
				strStart = 0;
				Swap(temp);
				return *this;
			}
		}
		MString& Insert(int position, type ch, size_t num = 1)
		{
			MDUILIB_ASSERT(num > 0);
			MString temp(ch, num);
			return Insert(position, temp);
		}

		/*
		*	@FuncName:Compare
		*	@ReturnType:int
		*	@Parameter:other[MString],比较的字符串
		*	@Parameter:cs[enum CaseSensitivity],是否忽略大小写
		*	@Remark:比较两个字符串。如果相等则返回0。逐字符比较，当两字符相等事比较下一个字符。
		*	@Remark:如果两字符串的一系列字符都相等，则按长度比较，长度较大的“大于”长度小的。
		*	@Remark:如果比other大，返回1，如果比other小，返回-1。与other相等返回0。
		*/
		int Compare(const MString &other, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			const_iterator this_beg, this_end, other_beg, other_end;
			this_beg = cbegin();
			this_end = cend();
			other_beg = other.cbegin();
			other_end = other.cend();
			while (this_beg != this_end && other_beg != other_end)
			{
				if (MStringTextCodec<type>::Compare(*this_beg, *other_beg, cs) == 0)
				{
					this_beg++;
					other_beg++;
				}
				else
					return MStringTextCodec<type>::Compare(*this_beg, *other_beg, cs);
			}
			if (this_beg != this_end)
				return 1;
			if (other_beg != other_end)
				return -1;
			return 0;
		}

		/*
		*	@FuncName:IsContains
		*	@ReturnType:bool
		*	@Parameter:str[MString]
		*	@Parameter:cs[CaseSensitivity]
		*	@Remark:检测字符串是否包含str。
		*/

		bool IsContains(const MString& str, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			return IndexOf(str, 0, cs) != -1;
		}

		/*
		*	@FuncName:Count
		*	@ReturnType:int
		*	@Parameter:str[MString]
		*	@Parameter:cs[CaseSensitivity]
		*	@Remark:检测str在字符串中出现的次数。
		*/
		int Count(const MString& str, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			int cnt = 0;
			int index = -1;
			MString temp_str = *this;
			while ((temp_str.Length() != 0u) && ((index = temp_str.IndexOf(str, 0, cs)) != -1))
			{
				cnt++;
				temp_str = temp_str.Right(temp_str.Length() - static_cast<size_type>(index) - str.Length());
				index = -1;
			}
			return cnt;
		}
		int Count(type ch, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			return Count(MString(ch, 1), cs);
		}
		/*
		*	@FuncName:IsStartsWith
		*	@ReturnType:bool
		*	@Parameter:str[const MString&]
		*	@Parameter:cs[enum CaseSensitivity],表示是否忽略大小写。
		*	@Remark:判断字符串是否以str开头，若是返回true,否则返回false.
		*/
		bool IsStartsWith(const MString &str, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			if (Length() < str.Length())
				return false;
			MString prefix = Left(str.Length());
			int r = prefix.Compare(str, cs);
			return r == 0;
		}
		/*
		*	@FuncName:IsStartsWith
		*	@ReturnType:bool
		*	@Parameter:ch[type]
		*	@Parameter:cs[enum CaseSensitivity],表示是否忽略大小写。
		*	@Remark:判断字符串是否以ch开头，若是返回true,否则返回false.
		*/
		bool IsStartsWith(type ch,
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			if (Length() < 1)
				return false;
			type src_ch = CharAt(0);
			int r = MStringTextCodec<type>::Compare(src_ch, ch, cs);
			return r == 0;
		}
		/*
		*	@FuncName:IsEndsWith
		*	@ReturnType:bool
		*	@Parameter:str[const MString&]
		*	@Parameter:cs[enum CaseSensitivity],表示是否忽略大小写。
		*	@Remark:判断字符串是否以str结束，若是返回true,否则返回false.
		*/
		bool IsEndsWith(const MString &str, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			if (Length() < str.Length())
				return false;
			MString prefix = Right(str.Length());
			int r = prefix.Compare(str, cs);
			return r == 0;
		}
		/*
		*	@FuncName:IsEndsWith
		*	@ReturnType:bool
		*	@Parameter:ch[type]
		*	@Parameter:cs[enum CaseSensitivity],表示是否忽略大小写。
		*	@Remark:判断字符串是否以ch结束，若是返回true,否则返回false.
		*/
		bool IsEndsWith(type ch,
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			if (Length() < 1)
				return false;
			type src_ch = CharAt(Length() - 1);
			int r = MStringTextCodec<type>::Compare(src_ch, ch, cs);
			return r == 0;
		}

		/*
		*	@FuncName:Fill
		*	@Parameter:ch[type]
		*	@Parameter:size[size_type],填充的长度,默认为-1,此时根据字符串长度填充。
		*	@Remark：此时这个字符串已经是全新的字符串了。
		*/
		MString& Fill(type ch, size_type size = 0)
		{
			if (size == 0)
			{
				MString temp(ch, Length());
				Swap(temp);
				return *this;
			}

			MString temp(ch, static_cast<size_t>(size));
			Swap(temp);
			return *this;
		}

		/*
		*	@FuncName:IndexOf
		*	@ReturnType:int
		*	@Parameter:str[MString],需要寻找的子串
		*	@Parameter:from[int],开始寻找的偏移量
		*	@Parameter:cs[CaseSensitivity],是否忽略大小写。
		*	@Remark:在字符串中寻找str串，并且返回该str在字符串中的偏移量。
		*	@Remark：如果找不到，将返回-1
		*/

		int IndexOf(const MString &str, int from = 0, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			return __XXXXIndexOf(&MString::cbegin, &MString::cend, str, from, cs);
		}
		int IndexOf(type ch, int from = 0, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			return IndexOf(MString(ch, 1), from, cs);
		}
		int LastIndexOf(const MString& str, int from = -1, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const;
		int LastIndexOf(type ch, int from = -1, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const;

		/*
		*	@FuncName:IsNull
		*	@ReturnType:bool
		*	@Remark:如果该字符串为空串，返回true。否则返回false。
		*/
		bool IsNull() const
		{
			return Length() == 0;
		}

		/*
		*	@FuncName:Left
		*	@ReturnType:MString
		*	@Parameter:n[size_type]
		*	@Remark:获取原字符串左边开始，长度为n的子字符串。这种方式递增调用对象的引用计数，不重新分配内存。
		*/
		const MString Left(size_type n) const
		{
			MDUILIB_ASSERT((n >= 0) && (n <= len));
			return Mid(n, 0);
		}

		/*
		*	@FuncName:Right
		*	@ReturnType:MString
		*	@Parameter:n[size_type]
		*	@Remark:获取原字符串右边开始，长度为n的子字符串。这种方式递增调用对象的引用计数，不重新分配内存。
		*/
		const MString Right(size_type n) const
		{
			MDUILIB_ASSERT((n >= 0) && (n <= len));
			return Mid(n, Length() - n);
		}

		/*
		*	@FuncName:Mid
		*	@ReturnType:MString
		*	@Parameter:n[size_type]
		*	@Parameter:pos[size_type]，起始位置。
		*	@Remark:获取原字符串指定位置开始，长度为n的子字符串。这种方式递增调用对象的引用计数，不重新分配内存。
		*	@Noted:相当于STL中string::substr，但不重新分配内存。
		*/
		const MString Mid(size_type n, size_type pos = 0) const
		{
			MDUILIB_ASSERT(pos + n <= len);
			MDUILIB_ASSERT(n >= 0);
			MString temp(*this);
			temp.len = n;
			temp.strStart += pos;
			return temp;
		}

		/*
		*	@FuncName:Repeated
		*	@ReturnType:MString
		*	@Parameter:times[size_type],重复次数。
		*	@Remark:用原字符串作为模板，构造重复多次的全新字符串。这个过程需要分配内存。
		*/

		const MString Repeated(size_type times) const
		{
			if (Length() == 0 || times == 0)
				return MString();
			size_type newStrLength = times * Length();
			MString newStr(newStrLength);
			type* buf = newStr.buffer;
			while (times-- > 0)
			{
				memcpy_s(buf, Length() * sizeof(type), buffer + strStart, Length() * sizeof(type));
				buf += Length();
			}
			newStr.len = newStrLength;
			newStr.strStart = 0;
			return newStr;
		}

		/*
		*	@FuncName:Length
		*	@ReturnType:size_type
		*	@Remark:返回该字符串的长度。
		*/
		size_type Length() const
		{
			return len;
		}

		/*
		*	@FuncName:AllocLength
		*	@ReturnType:size_type
		*	@Remark:返回该字符串Buffer的长度。
		*/
		size_type AllocLength() const
		{
			return allocLen;
		}

		/*
		*	@FuncName:RefCount
		*	@ReturnType:size_t
		*	@Remark:返回该字符串指向的内存buffer的引用计数。
		*/
		size_t RefCount() const
		{
			MDUILIB_ASSERT(counter != nullptr);
			return *counter;
		}

		/*
		*	@FuncName:AddRefCount
		*	@Remark:buffer内存的手动管理，增加引用计数。
		*/
		void AddRefCount()
		{
			MDUILIB_ASSERT(counter != nullptr);
			*counter++;
		}
		/*
		*	@FuncName:DefRefCount
		*	@Remark:buffer内存的手动管理，减少引用计数。
		*/
		void DeRefCount()
		{
			MDUILIB_ASSERT(counter != nullptr);
			MDUILIB_ASSERT(*counter != 0);
			*counter--;
		}

		/*
		*	@FuncName:Buffer
		*	@Remark:buffer内存的手动管理。配合AddRefCount和DeRefCount使用。
		*/
		const type *Buffer() const
		{
			MDUILIB_ASSERT(buffer != nullptr);
			return buffer;
		}

		/*
		*	@FuncName:Replace
		*	@ReturnType:MString&,指向自己的指针
		*	@Parameter:before[const MString&],after[const MString&]
		*	@Remark:用after子串替换掉原字符串的before子串部分。
		*/

		MString &Replace(const MString &before, const MString &after, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive)
		{
			if (IsNull())
				return *this;
			std::vector<int> indices;
			int from = 0;
			int index = -1;
			//	找出所有匹配的索引
			while (static_cast<size_type>(from) < Length() && \
				((index = IndexOf(before, from, cs)) != -1))
			{
				indices.push_back(index);
				from = index + before.Length();
				index = -1;
			}
			if (indices.empty())
				return *this;

			MString temp(Length() - indices.size()*before.Length() + indices.size()*after.Length());
			temp.Append(Mid(indices[0], 0));
			temp.Append(after);
			for (size_t i = 1; i < indices.size(); i++)
			{
				temp.Append(Mid(indices[i] - indices[i - 1] - before.Length(), indices[i - 1] + before.Length()));
				temp.Append(after);
			}
			temp.Append(Mid(Length() - before.Length() - indices[indices.size() - 1], indices[indices.size() - 1] + before.Length()));
			Swap(temp);
			return *this;
		}
		MString &Replace(type ch, const MString& after, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive)
		{
			return Replace(MString(ch, 1), after, cs);
		}

		/*
		*	@FuncName:SetNum
		*	@ReturnType:MString&,指向自己的字符串
		*	@Parameter:n[int|unsigned int]
		*	@Parameter:base[int],进制,默认为10。
		*	@Remark:将数字转化成字符串，默认为十进制。
		*/
		MString &SetNum(int n, IntegerBase base = IntegerBase::DECIMAL)
		{
			MString temp = MString::Number(n, base);
			Swap(temp);
			return *this;
		}
		MString &SetNum(unsigned int n, IntegerBase base = IntegerBase::DECIMAL)
		{
			MString temp = MString::Number(n, base);
			Swap(temp);
			return *this;
		}

		/*
		*	@FuncName:SetNum
		*	@ReturnType:MString&,指向自己的字符串
		*	@Parameter:n[float|double]
		*	@Parameter:format,格式。
		*	@Parameter:precision,保留精度，默认为小数点后六位。
		*	@Remark:将小数转化成字符串。
		*/
		MString &SetNum(float n, char format = 'g', int precision = 6)
		{
			MString temp = MString::Number(n, base);
			Swap(temp);
			return *this;
		}
		MString &SetNum(double n, char format = 'g', int precision = 6)
		{
			MString temp = MString::Number(n, base);
			Swap(temp);
			return *this;
		}

		/*
		*	@FuncName:Splict
		*	@ReturnType:StringList[vector<MString>]
		*	@Parameter:seq[MString]
		*	@Parameter:cs[CaseSensitivity]
		*	@Remark:以str为模板，切分字符串。返回切分后的字符串列表。
		*/
		StringList Splict(const MString &seq, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive) const
		{
			if (IsNull())
				return {};
			std::vector<int> indices;
			int from = 0;
			int index = -1;
			//	找出所有匹配的索引
			while (static_cast<size_type>(from) < Length() && \
				((index = IndexOf(seq, from, cs)) != -1))
			{
				indices.push_back(index);
				from = index + seq.Length();
				index = -1;
			}
			if (indices.empty())
				return { *this };
			StringList list;
			if (indices[0] != 0)
				list.push_back(Mid(indices[0], 0));
			for (size_t i = 1; i < indices.size(); i++)
			{
				MString s = Mid(indices[i] - indices[i - 1] - seq.Length(), indices[i - 1] + seq.Length());
				if (!s.IsNull())
					list.push_back(s);
			}
			int lastIndex = indices[indices.size() - 1];
			if (lastIndex + seq.Length() < Length())
				list.push_back(Mid(Length() - lastIndex - seq.Length(), lastIndex + seq.Length()));
			return list;
		}
		StringList Splict(type ch, \
			CaseSensitivity cs = CaseSensitivity::CaseSensitive)const
		{
			return Splict(MString(ch, 1), cs);
		}

		/*
		*	@FuncName:Clone
		*	@Remark:复制一份与之相同的MString。这份MString对象使用新的buffer和引用计数，即其为全新的字符串。
		*	@Noted:注意其和复制构造函数的区别。
		*/
		MString Clone(size_t PrependSize = 0, size_t AppendSize = 0) const
		{
			MString str;
			str.buffer = static_cast<type*>(malloc((Length() + PrependSize + AppendSize) * sizeof(type)));
			MDUILIB_ASSERT(str.buffer != nullptr);
			errno_t r = memcpy_s(str.buffer + PrependSize, Length() * sizeof(type), buffer, Length() * sizeof(type));
			MDUILIB_ASSERT(r == 0);
			str.counter = new size_t(1);
			MDUILIB_ASSERT(str.counter != nullptr);
			str.strStart = static_cast<size_type>(PrependSize);
			str.len = Length();
			str.allocLen = Length() + static_cast<size_type>(PrependSize + AppendSize);
			return str;
		}

		/*
		*	@FuncName:ToUpper
		*	@ReturnType:MString
		*	@Remark:返回一个全新的字母大写的字符串。
		*/
		MString ToUpper() const
		{
			return MStringTextCodec<type>::Upper(*this);
		}

		/*
		*	@FuncName:ToLower
		*	@ReturnType:MString
		*	@Remark:返回一个全新的字母小写的字符串。
		*/
		MString ToLower() const
		{
			return MStringTextCodec<type>::Lower(*this);
		}

		/*
		*	@FuncName:MakeUpper
		*	@ReturnType:MString&,指向自己的字符串。
		*	@Remark:将自己变成一个全新的字母小写的字符串。
		*/
		MString &MakeUpper()
		{
			MString temp = ToUpper();
			Swap(temp);
			return *this;
		}
		/*
		*	@FuncName:MakeLower
		*	@ReturnType:MString&,指向自己的字符串。
		*	@Remark:将自己变成一个全新的字母小写的字符串。
		*/
		MString &MakeLower()
		{
			MString temp = ToLower();
			Swap(temp);
			return *this;
		}

		const_iterator cbegin() const
		{
			return buffer + strStart;
		}
		const_iterator cend() const
		{
			return cbegin() + Length();
		}

		/*
		*	@FuncName:ToStdString
		*	@Remark:转换成标准库的string
		*/
		std::string ToStdString() const
		{
			return MStringTextCodec<type>::ToStdString(*this);
		}

		/*
		*	@FuncName:ToStdWString
		*	@Remark:转换成标准库的wstring
		*/
		std::wstring ToStdWString() const
		{
			return MStringTextCodec<type>::ToStdWString(*this);
		}

		static MString Number(int n, IntegerBase base = IntegerBase::DECIMAL)
		{
			return MStringTextCodec<CharType>::FromInt(n, base);
		}
		static MString Number(unsigned int n, IntegerBase base = IntegerBase::DECIMAL)
		{
			return MStringTextCodec<CharType>::FromUint(n, base);
		}
		static MString Number(float n, char format = 'g', int precision = 6)
		{
			return MStringTextCodec<CharType>::FromFloat(n, format, precision);
		}
		static MString Number(double n, char format = 'g', int precision = 6)
		{
			return MStringTextCodec<CharType>::FromDouble(n, format, precision);
		}

		//	@Remark:重载各种方便的operator+函数
		friend MString operator+(const MString& lhs, const MString &rhs)
		{
			MString temp = lhs.Clone(0, rhs.Length());
			temp.Append(rhs);
			return temp;
		}
		friend MString operator+(const MString& str, int num)
		{
			return str + MString::Number(num);
		}
		friend MString operator+(int num, const MString &str)
		{
			return MString::Number(num) + str;
		}
		friend MString operator+(const MString &str, double real)
		{
			return str + MString::Number(real);
		}
		friend MString operator+(double real, const MString& str)
		{
			return MString::Number(real) + str;
		}

		friend bool operator==(const MString& lhs, const MString &rhs)
		{
			return lhs.Compare(rhs) == 0;
		}
		friend bool operator<(const MString& lhs, const MString &rhs)
		{
			return lhs.Compare(rhs) == -1;
		}
		friend bool operator>(const MString& lhs, const MString &rhs)
		{
			return lhs.Compare(rhs) == 1;
		}
	};

	/***********************************************
	*	@TypeName:AString[MString<char>]
	*	@TypeName:WString[MString<wchar_t>]
	*	@Remark:AString,表示以ASCII编码的字符串。
	*	@Remark:WString,表示以宽字符编码的字符串。
	************************************************/
	using AString = MString<char>;
	using WString = MString<wchar_t>;

#ifdef _UNICODE
	using String = WString;
#else 
	using String = AString;
#endif // _UNICODE


	template<typename CharType>
	struct MStringTextCodec {};

	/*
	*	@SpecializedClassName:MStringTextCodec[char]
	*/
	template<>
	struct MStringTextCodec<char>
	{
		using CharType = char;
		using BufferPointerType = CharType*;
		inline static bool IsDigit(CharType ch)
		{
			return ch >= '0'&&ch <= '9';
		}
		inline static bool IsAlphabet(CharType ch)
		{
			return (ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z');
		}
		static int ToInt(const MString<CharType> &intStr);
		static unsigned int ToUInt(const MString<CharType> &uintStr);
		static float ToFloat(const MString<CharType> &floatStr);
		static double ToDouble(const MString<CharType> &doubleStr);
		static MString<CharType> FromInt(int num, IntegerBase base = IntegerBase::DECIMAL)
		{
			MString<CharType> temp(33);
			temp.strStart = temp.len = 0;
			if (num < 0)
			{
				temp.Append('-');
				num = -num;
			}
			unsigned int absNum = static_cast<unsigned int>(num);
			temp.Append(FromUint(absNum, base));
			return temp;
		}
		static MString<CharType> FromUint(unsigned int num, IntegerBase base = IntegerBase::DECIMAL)
		{
			switch (base)
			{
			case IntegerBase::BINARY:
			{
				if (num == 0u)
					return MString<CharType>("0");
				MString<CharType> temp(32u);
				BufferPointerType ptail = temp.buffer + 31u;
				CharType chars[2u] = { '0','1' };
				while (num != 0u)
				{
					*ptail-- = chars[num & 0x1u];
					num >>= 1u;
				}
				temp.strStart = static_cast<MString<CharType>::size_type>(ptail - temp.buffer + 1u);
				temp.len = 32u - temp.strStart;
				return temp;
			}
			break;
			case IntegerBase::OCTAL:
			{
				if (num == 0u)
					return MString<CharType>("00");
				CharType chars[8u] = { '0','1','2','3','4','5','6','7' };
				MString<CharType> temp(20u);
				BufferPointerType ptail = temp.buffer + 19u;
				while (num != 0u)
				{
					*ptail-- = chars[(num % 8u)];
					num /= 8u;
				}
				*ptail-- = '0';
				temp.strStart = static_cast<MString<CharType>::size_type>(ptail - temp.buffer + 1u);
				temp.len = 20u - temp.strStart;
				return temp;
			}
			break;
			case IntegerBase::DECIMAL:
			{
				if (num == 0u)
					return MString<CharType>("0");
				CharType chars[10u] = { '0','1','2','3','4','5','6','7','8','9' };
				MString<CharType> temp(12u);
				BufferPointerType ptail = temp.buffer + 11u;
				while (num != 0u)
				{
					*ptail-- = chars[(num % 10u)];
					num /= 10u;
				}
				temp.strStart = static_cast<MString<CharType>::size_type>(ptail - temp.buffer + 1u);
				temp.len = 12u - temp.strStart;
				return temp;
			}
			break;
			case IntegerBase::HEXADECIMAL:
			{
				if (num == 0u)
					return MString<CharType>("0x0");
				CharType chars[16u] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
				MString<CharType> temp(10u);
				BufferPointerType ptail = temp.buffer + 9u;
				while (num != 0u)
				{
					*ptail-- = chars[(num % 16u)];
					num /= 16u;
				}
				*ptail-- = 'x';
				*ptail-- = '0';
				temp.strStart = static_cast<MString<CharType>::size_type>(ptail - temp.buffer + 1u);
				temp.len = 10u - temp.strStart;
				return temp;
			}
			break;
			default:
				return MString<CharType>();
				break;
			}
		}
		static MString<CharType> FromFloat(float num, char format = 'g', int precision = 6)
		{
			return FromDouble(static_cast<double>(num), format, precision);
		}
		static MString<CharType> FromDouble(double num, char format = 'g', int precision = 6)
		{
			AString temp;
			if (num < 0.0f)
			{
				temp.Append('-');
				num = abs(num);
			}
			unsigned int integer = static_cast<unsigned int>(trunc(num));
			num = round(pow(10, precision)*((num - trunc(num))));
			unsigned int frac = static_cast<unsigned int>(num);
			AString IntegerPart = AString::Number(integer);
			AString FracPart = AString::Number(frac);
			AString ZeroPart;
			if (FracPart.Length() < static_cast<AString::size_type>(precision))
				ZeroPart = AString('0', static_cast<AString::size_type>(precision) - FracPart.Length());
			temp = temp.Clone(0, temp.Length() + IntegerPart.Length() + ZeroPart.Length() + 1);
			temp.Append(IntegerPart).Append('.').Append(ZeroPart).Append(FracPart);
			return temp;
		}

		static MString<CharType> Upper(const MString<CharType> &str)
		{
			if (str.IsNull())
				return str;
			BufferPointerType beg = str.buffer + str.strStart;
			BufferPointerType en = beg + str.Length();
			MString<CharType> temp(str.Length());
			BufferPointerType dst = temp.buffer;
			while (beg != en)
			{
				if ((*beg >= 'a') && (*beg <= 'z'))
				{
					*dst++ = (*beg++) - 'a' + 'A';
					continue;
				}
				*dst++ = (*beg++);
			}
			temp.len = str.Length();
			return temp;
		}
		static MString<CharType> Lower(const MString<CharType> &str)
		{
			if (str.IsNull())
				return str;
			BufferPointerType beg = str.buffer + str.strStart;
			BufferPointerType en = beg + str.Length();
			MString<CharType> temp(str.Length());
			BufferPointerType dst = temp.buffer;
			while (beg != en)
			{
				if ((*beg >= 'A') && (*beg <= 'Z'))
				{
					*dst++ = (*beg++) - 'A' + 'a';
					continue;
				}
				*dst++ = (*beg++);
			}
			temp.len = str.Length();
			return temp;
		}

		static int Compare(CharType ch1, CharType ch2, CaseSensitivity cs = CaseSensitivity::CaseSensitive)
		{
			switch (cs)
			{
			case CaseSensitivity::CaseSensitive:
				break;
			case CaseSensitivity::CaseInSensitive:
			{
				auto AlphabetToLower = [](CharType ch) -> CharType
				{
					if (ch >= 'A' && ch <= 'Z')
						return ch - 'A' + 'a';
					return ch;
				};
				ch1 = AlphabetToLower(ch1);
				ch2 = AlphabetToLower(ch2);
			}
			break;
			default:
				break;
			}
			if (ch1 > ch2)
				return 1;
			if (ch1 < ch2)
				return -1;
			return 0;
		}

		static std::string ToStdString(const MString<CharType> &str)
		{
			return std::string(str.cbegin(), str.cend());
		}

		static std::wstring ToStdWString(const MString<CharType> &str)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wide_string = converter.from_bytes(str.cbegin(), str.cend());
			return wide_string;
		}
	};

	/*
	*	@SpecializedClassName:MStringTextCodec[wchar_t]
	*/
	template<>
	struct MStringTextCodec<wchar_t>
	{
		using CharType = wchar_t;
		using BufferPointerType = CharType*;
		inline static bool IsDigit(CharType ch)
		{
			return ch >= L'0'&&ch <= L'9';
		}
		inline static bool IsAlphabet(CharType ch)
		{
			return (ch >= L'a'&&ch <= L'z') || (ch >= L'A'&&ch <= L'Z');
		}
		static int ToInt(const MString<CharType> &intStr);
		static unsigned int ToUInt(const MString<CharType> &uintStr);
		static float ToFloat(const MString<CharType> &floatStr);
		static double ToDouble(const MString<CharType> &doubleStr);
		static MString<CharType> FromInt(int num, IntegerBase base = IntegerBase::DECIMAL)
		{
			MString<CharType> temp(33);
			temp.strStart = temp.len = 0;
			if (num < 0)
			{
				temp.Append(L'-');
				num = -num;
			}
			unsigned int absNum = static_cast<unsigned int>(num);
			temp.Append(FromUint(absNum, base));
			return temp;
		}
		static MString<CharType> FromUint(unsigned int num, IntegerBase base = IntegerBase::DECIMAL)
		{
			switch (base)
			{
			case IntegerBase::BINARY:
			{
				if (num == 0u)
					return MString<CharType>(L"0");
				MString<CharType> temp(32u);
				BufferPointerType ptail = temp.buffer + 31u;
				CharType chars[2u] = { L'0',L'1' };
				while (num != 0u)
				{
					*ptail-- = chars[num & 0x1u];
					num >>= 1u;
				}
				temp.strStart = static_cast<MString<CharType>::size_type>(ptail - temp.buffer + 1u);
				temp.len = 32u - temp.strStart;
				return temp;
			}
			break;
			case IntegerBase::OCTAL:
			{
				if (num == 0u)
					return MString<CharType>(L"00");
				CharType chars[8u] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7' };
				MString<CharType> temp(20u);
				BufferPointerType ptail = temp.buffer + 19u;
				while (num != 0u)
				{
					*ptail-- = chars[(num % 8u)];
					num /= 8u;
				}
				*ptail-- = L'0';
				temp.strStart = static_cast<MString<CharType>::size_type>(ptail - temp.buffer + 1u);
				temp.len = 20u - temp.strStart;
				return temp;
			}
			break;
			case IntegerBase::DECIMAL:
			{
				if (num == 0u)
					return MString<CharType>(L"0");
				CharType chars[10u] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9' };
				MString<CharType> temp(12u);
				BufferPointerType ptail = temp.buffer + 11u;
				while (num != 0u)
				{
					*ptail-- = chars[(num % 10u)];
					num /= 10u;
				}
				temp.strStart = static_cast<MString<CharType>::size_type>(ptail - temp.buffer + 1u);
				temp.len = 12u - temp.strStart;
				return temp;
			}
			break;
			case IntegerBase::HEXADECIMAL:
			{
				if (num == 0u)
					return MString<CharType>(L"0x0");
				CharType chars[16u] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9',L'a',L'b',L'c',L'd',L'e',L'f' };
				MString<CharType> temp(10u);
				BufferPointerType ptail = temp.buffer + 9u;
				while (num != 0u)
				{
					*ptail-- = chars[(num % 16u)];
					num /= 16u;
				}
				*ptail-- = L'x';
				*ptail-- = L'0';
				temp.strStart = static_cast<MString<CharType>::size_type>(ptail - temp.buffer + 1u);
				temp.len = 10u - temp.strStart;
				return temp;
			}
			break;
			default:
				return MString<CharType>();
				break;
			}
		}
		static MString<CharType> FromFloat(float num, char format = 'g', int precision = 6)
		{
			return FromDouble(static_cast<double>(num), format, precision);
		}
		static MString<CharType> FromDouble(double num, char format = 'g', int precision = 6)
		{
			WString temp;
			if (num < 0.0f)
			{
				temp.Append(L'-');
				num = abs(num);
			}
			unsigned int integer = static_cast<unsigned int>(trunc(num));
			num = round(pow(10, precision)*((num - trunc(num))));
			unsigned int frac = static_cast<unsigned int>(num);
			WString IntegerPart = WString::Number(integer);
			WString FracPart = WString::Number(frac);
			WString ZeroPart;
			if (FracPart.Length() < static_cast<WString::size_type>(precision))
				ZeroPart = WString(L'0', static_cast<WString::size_type>(precision) - FracPart.Length());
			temp = temp.Clone(0, temp.Length() + IntegerPart.Length() + ZeroPart.Length() + 1);
			temp.Append(IntegerPart).Append(L'.').Append(ZeroPart).Append(FracPart);
			return temp;
		}

		static MString<CharType> Upper(const MString<CharType> &str)
		{
			if (str.IsNull())
				return str;
			BufferPointerType beg = str.buffer + str.strStart;
			BufferPointerType en = beg + str.Length();
			MString<CharType> temp(str.Length());
			BufferPointerType dst = temp.buffer;
			while (beg != en)
			{
				if ((*beg >= L'a') && (*beg <= L'z'))
				{
					*dst++ = (*beg++) - L'a' + L'A';
					continue;
				}
				*dst++ = (*beg++);
			}
			temp.len = str.Length();
			return temp;
		}
		static MString<CharType> Lower(const MString<CharType> &str)
		{
			if (str.IsNull())
				return str;
			BufferPointerType beg = str.buffer + str.strStart;
			BufferPointerType en = beg + str.Length();
			MString<CharType> temp(str.Length());
			BufferPointerType dst = temp.buffer;
			while (beg != en)
			{
				if ((*beg >= L'A') && (*beg <= L'Z'))
				{
					*dst++ = (*beg++) - L'A' + L'a';
					continue;
				}
				*dst++ = (*beg++);
			}
			temp.len = str.Length();
			return temp;
		}

		static int Compare(CharType ch1, CharType ch2, CaseSensitivity cs = CaseSensitivity::CaseSensitive)
		{
			switch (cs)
			{
			case CaseSensitivity::CaseSensitive:
				break;
			case CaseSensitivity::CaseInSensitive:
			{
				auto AlphabetToLower = [](CharType ch) -> CharType
				{
					if (ch >= L'A' && ch <= L'Z')
						return ch - L'A' + L'a';
					return ch;
				};
				ch1 = AlphabetToLower(ch1);
				ch2 = AlphabetToLower(ch2);
			}
			break;
			default:
				break;
			}
			if (ch1 > ch2)
				return 1;
			if (ch1 < ch2)
				return -1;
			return 0;
		}

		static std::wstring ToStdWString(const MString<CharType> &str)
		{
			return std::wstring(str.cbegin(), str.cend());
		}

		static std::string ToStdString(const MString<CharType> &str)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::string utf8_string = converter.to_bytes(str.cbegin(), str.cend());
			return utf8_string;
		}
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_UTILS_MSTRING_H
