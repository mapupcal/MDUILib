#ifndef MDUILIB_WINDOWXX_UTILS_H
#define MDUILIB_WINDOWXX_UTILS_H

namespace MDUILib
{
	//@Remark:Comptr ÷«ƒ‹÷∏’Î
	template<typename ComInterface>
	class ComPtr
	{
	public:
		ComPtr()
			:m_pComInterface(nullptr) {}
		ComPtr(ComInterface* pRaw)
			:m_pComInterface(pRaw)
		{
			if (m_pComInterface)
				m_pComInterface->AddRef();
		}
		ComPtr(const ComPtr &other)
		{
			if (other->m_pComInterface)
			{
				m_pComInterface = other->m_pComInterface;
				m_pComInterface->AddRef();
			}
		}
		~ComPtr()
		{
			if (m_pComInterface)
				m_pComInterface->Release();
		}
		//&
		ComInterface **operator&()
		{
			return &m_pComInterface;
		}
		//->
		ComInterface* operator->()
		{
			return m_pComInterface;
		}
		//=
		ComPtr& operator=(const ComPtr& other)
		{
			ComPtr(other).Swap(*this);
		}
		operator ComInterface*()
		{
			return m_pComInterface;
		}
		void Swap(ComPtr &other)
		{
			std::swap(m_pComInterface, other.m_pComInterface);
		}
		ComInterface* Get() const
		{
			return m_pComInterface;
		}
		friend bool operator==(const ComPtr& lhs, const ComPtr& rhs)
		{
			return lhs.m_pComInterce == rhs.m_pComInterface;
		}
		friend bool operator!=(const ComPtr& lhs, const ComPtr& rhs)
		{
			return !(lhs == rhs)
		}
	private:
		ComInterface *m_pComInterface;
	};
}

#endif // !MDUILIB_WINDOWXX_UTILS_H
