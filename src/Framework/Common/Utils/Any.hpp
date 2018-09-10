
#ifndef MDUILIB_FRAMEWORK_UTILS_ANY_H
#define MDUILIB_FRAMEWORK_UTILS_ANY_H

#include <typeinfo>
#include <algorithm>

namespace MDUILib
{
	class Any
	{
	private:
		//@Remark:Low level data structure definitions.
		class PlaceHolderBase
		{
		public:
			virtual ~PlaceHolderBase() {};
			virtual const std::type_info &GetType() const { return typeid(void);};
			virtual PlaceHolderBase* Clone() const { return nullptr;};
		};

		template<typename ValueType>
		class PlaceHolder : public PlaceHolderBase
		{
		public:
			PlaceHolder(const ValueType& val)
				:m_value(val)
			{

			}
			const std::type_info &GetType() const
			{
				return typeid(ValueType);
			}
			PlaceHolderBase* Clone() const
			{
				return new PlaceHolder<ValueType>(m_value);
			}

			ValueType m_value;

		private:
			PlaceHolder& operator=(const PlaceHolder&);
		};
	public:

		Any()
			:m_pHolder(nullptr)
		{

		}
		//@Remark:Constructor Accept any Type.
		template<typename ValueType>
		Any(const ValueType &val)
			:m_pHolder(new PlaceHolder<ValueType>(val))
		{

		}

		Any(const Any &other)
			: m_pHolder(other.m_pHolder ? other.m_pHolder->Clone() : nullptr)
		{

		}
		Any(Any &&other)
			:m_pHolder(other.m_pHolder)
		{
			other.m_pHolder = nullptr;
		}

		~Any()
		{
			if(m_pHolder)
				delete m_pHolder;
			m_pHolder = nullptr;
		}

		//@Remark:Check whehter the low level value fit this value type or not.
		template<typename ValueType>
		bool CanCast() const
		{
			return m_pHolder &&
				typeid(ValueType) == m_pHolder->GetType();
		}
		
		//@Remark:Safe cast to the value type.If the low level value could not cast to the
		//		  target value type,an Exception Raise.
		//@Noted: .e.g 
		//		Any any = 1;
		//		if(any.CanCast<int>())
		//			int* one = any.CastTo<int>();				//	safe cast
		//		if(any.CanCast<int>())
		//			int* one = any.ForceCastTo<int>();			//	unsafe cast,but efficient in this context.
		//		std::string* one = any.CastTo<std::string>();	//	An Exception Raise.
		template<typename ValueType>
		ValueType* CastTo() const
		{
			if(m_pHolder && typeid(ValueType) == m_pHolder->GetType())
			{
				return &(static_cast<PlaceHolder<ValueType>*>(m_pHolder))->m_value;
			}
			else
			{
				throw std::bad_cast();
			}
		}

		//@Remark:Unsafe cast.This Method does not promise the cast will succeeded.If the low level value does not 
		//		  fit the target value type, return nullptr.
		//@Noted: .e.g
		//		Any any = 1;
		//		if(any.CanCast<int>())
		//			int* one = any.ForceCastTo<int>();	//best practice.

		//		int* one = any.ForceCastTo<int>();		//well excecuted.
		//		std::string* one_str = any.ForceCastTo<std::string>();	//access error.
		//@Noted:While you certainly believe that you realize that the low level value can Cast to the target value type,
		//		 This Method will perform more effiently.
		template<typename ValueType>
		ValueType* ForceCastTo() const
		{
			return m_pHolder ? &(static_cast<PlaceHolder<ValueType>*>(m_pHolder))->m_value
				: nullptr;
		}

		void Swap(Any &other)
		{
			std::swap(m_pHolder,other.m_pHolder);
		}

		template<typename ValueType>
		Any& operator=(const ValueType &val)
		{
			Any(val).Swap(*this);
			return *this;
		}

		Any& operator=(Any &&other)
		{
			Any(other).Swap(*this);
		}

	private:
		PlaceHolderBase *m_pHolder;
	};
}

#endif //MDUILIB_FRAMEWORK_UTILS_ANY_H