
#ifndef MDUILIB_FRAMEWORK_COMMON_UTILS_MDELEGATE_H
#define MDUILIB_FRAMEWORK_COMMON_UTILS_MDELEGATE_H

/*
*	@Remark:定义C++的委托类型。
*	@Remark:委托的类型可以是普通函数，类成员函数，类静态函数，以及lambda闭包。
*/

#include"Utils.hpp"
#include<functional>
#include<vector>
#include<memory>
#include<type_traits>
namespace MDUILib
{
	/*
	*	@TemplateClassName:Delegate[std::function]
	*	@TemplateParameters:Callable,表示调用的形式。见Remark。
	*	@Remark:Callable表示一个函数或者函数对象的调用形式。
	*	@Noted:int(int,double),表示该Delegate接受两个参数，第一个参数类型为int,第二个参数类型为double，这个Delegate返回值为void。
	*	@SeeAlso:C++11 Function
	*/
	template<typename Callable>
	using Delegate = std::function<Callable>;

	/*
	*	@TemplateClassName:DelegateIndirectInvoker
	*	@TemplateParameters:BasedType,基类对象类型
	*	@TemplateParameters:DerivedType,子类对象类型
	*	@TemplateParameters:Ret,返回值类型
	*	@TemplateParameters:...Args,调用时函数参数的类型列表。
	*	@Remark:DelegateIndirectInvoker是为了解决类对象成员函数委托而设计的中间类，重载了operator()，属于Functor类别。
	*	@Noted:DelegateIndirectInvoker的引入主要是解决std::bind占位符语法的问题而引入的，仅用于MakeDelegate函数内部。
	*/
	template<typename BasedType,typename DerivedType,typename Ret,typename ...Args>
	class DelegateIndirectInvoker
	{
	private:
		using MemberFunctionType = Ret(BasedType::*)(Args...);
		using ConstMemberFunctionType = Ret(BasedType::*)(Args...) const;
		/*
		*	@Remark:For non-const成员函数
		*/
		DelegateIndirectInvoker(
			const std::shared_ptr<DerivedType> pObj,
			MemberFunctionType pFunc
		) : pObject(pObj), pMemberFunction(*(void**)&pFunc) {}
		/*
		*	@Remark:For const成员函数
		*/
		DelegateIndirectInvoker(
			const std::shared_ptr<DerivedType> pObj,
			ConstMemberFunctionType pFunc
		) : pObject(pObj), pMemberFunction(*(void**)&pFunc) {}
	public:

		//	@Commit:For MakeDelegate access private constructor.
		template<typename B, typename D, typename R, typename...A>
		friend Delegate<R(A...)> MakeDelegate(
			const std::shared_ptr<B> &pObject,
			R(D::*pMemberFunction)(A...)
			);

		template<typename B,typename D ,typename R, typename...A>
		friend Delegate<R(A...)> MakeDelegate(
			const std::shared_ptr<D> &pObject,
			R(B::*pMemberFunction)(A...)const
		);

		template<typename B, typename D, typename R, typename...A>
		friend Delegate<R(A...)> MakeDelegate(
			const std::shared_ptr<D> &pObject,
			R(B::*pMemberFunction)(A...)
		);

		template<typename B, typename D, typename R, typename...A>
		friend Delegate<R(A...)> MakeDelegate(
			const std::shared_ptr<B> &pObject,
			R(D::*pMemberFunction)(A...)const
		);

		template<typename O, typename R, typename...A>
		friend Delegate<R(A...)> MakeDelegate(
			const std::shared_ptr<O> &pObject,
			R(O::*pMemberFunction)(A...)
		);

		template<typename O, typename R, typename...A>
		friend Delegate<R(A...)> MakeDelegate(
			const std::shared_ptr<O> &pObject,
			R(O::*pMemberFunction)(A...)const
		);

		DelegateIndirectInvoker(const DelegateIndirectInvoker& other)
			:pObject(other.pObject), pMemberFunction(other.pMemberFunction) {}
		DelegateIndirectInvoker(DelegateIndirectInvoker &&other)
			:pObject(std::move(other.pObject)), pMemberFunction(other.pMemberFunction) {}

		Ret operator()(Args&&... params)
		{
			//	@Commit:这里存在些许的从void*转型到实际成员函数地址的开销。
			union 
			{
				void* pVoid;
				MemberFunctionType pMemberFunction;
				//ConstMemberFunctionType pConstMemberFunction;//See Below.
			} func = { pMemberFunction };
			//	@Commit:只要获得函数的地址，并且知道相应的函数签名类型即可调用该函数。
			(pObject.get()->*(func.pMemberFunction))(std::forward<Args>(params)...);
		}
	private:
		std::shared_ptr<DerivedType> pObject;
		void* pMemberFunction;
	};


	/*
	*	@FunctionName:MakeDelgate
	*	@Parameter:pObject[const std::shared_ptr<ObjectType> &]
	*	@Parameter:pMemberFunction[Ret(ObjectType::*)(Args...)]
	*	@Remark:用于构造对象成员函数的Delegate。
	*	@Noted:使用智能指针作为对象输入参数，主要是为了pObject的生命周期至少和Delegate对象的生命周期一样长。
	*/

	template<typename ObjectType, typename Ret, typename ...Args>
	Delegate<Ret(Args...)> MakeDelegate(
		const std::shared_ptr<ObjectType> &pObject,
		Ret(ObjectType::*pMemberFunction)(Args...))
	{
		return DelegateIndirectInvoker<ObjectType,ObjectType,Ret,Args...>(pObject, pMemberFunction);
	}

	template<typename ObjectType, typename Ret, typename ...Args>
	Delegate<Ret(Args...)> MakeDelegate(
		const std::shared_ptr<ObjectType> &pObject,
		Ret(ObjectType::*pMemberFunction)(Args...)const) 
	{
		return DelegateIndirectInvoker<ObjectType,ObjectType, Ret, Args...>(pObject, pMemberFunction);
	}

	/*
	*	@Remark:可用于委托子类对象调用基类定义的public函数，包括virtual。
	*/
	template<typename Based,typename Derived,typename Ret,typename ...Args>
	Delegate<Ret(Args...)> MakeDelegate(
		const std::shared_ptr<Derived> &pObject,
		Ret(Based::*pMemberFunction)(Args...)
	)
	{
		static_assert(std::is_base_of<Based, Derived>(), "Derived must derive from Based.");
		return DelegateIndirectInvoker<Based, Derived, Ret, Args...>(pObject, pMemberFunction);
	}

	template<typename Based, typename Derived, typename Ret, typename ...Args>
	Delegate<Ret(Args...)> MakeDelegate(
		const std::shared_ptr<Derived> &pObject,
		Ret(Based::*pMemberFunction)(Args...) const
	)
	{
		static_assert(std::is_base_of<Based, Derived>(), "Derived must derive from Based.");
		return DelegateIndirectInvoker<Based, Derived, Ret, Args...>(pObject, pMemberFunction);
	}

	/*
	*	@TemplateClassName DelegateNotifyers<SenderType,Args>
	*	@Remark:For Call Backs.
	*/

	template<typename SenderType,typename Args>
	class DelegateNotifyers
	{
		using NotifyerType = Delegate<void(SenderType, Args)>;
		using ContainerType = std::vector<NotifyerType>;
		using Iterator = typename ContainerType::iterator;
		using ConstIterator = typename ContainerType::const_iterator;
	public:
		DelegateNotifyers() {}
		DelegateNotifyers& operator+=(const NotifyerType &notifyer)
		{
			m_Notifyers.push_back(notifyer);
			return *this;
		}
		Iterator begin()
		{
			return m_Notifyers.begin();
		}
		Iterator end()
		{
			return m_Notifyers.end();
		}
		ConstIterator cbegin() const
		{
			return m_Notifyers.cbegin();
		}
		ConstIterator cend() const
		{
			return m_Notifyers.cend();
		}
	private:
		ContainerType m_Notifyers;
	};
}

#endif // !MDUILIB_FRAMEWORK_COMMON_UTILS_MDELEGATE_H
