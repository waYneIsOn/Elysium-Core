/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_COLLECTIONS_INITIALIZERLIST
#define ELYSIUM_CORE_TEMPLATE_COLLECTIONS_INITIALIZERLIST

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

namespace Elysium::Core::Template::Collections
{
	// afaik I can neither implement a custom InitializerList, nor use an implicit cast operator
	
	template <class T>
	using InitializerList = std::initializer_list<T>;
	
	/*
	template <class T>
	class InitializerList
	{
	public:
		using ConstPointer = const T*;
	public:
		InitializerList() noexcept;
		InitializerList(ConstPointer First, ConstPointer Last) noexcept;
		InitializerList(const InitializerList& Source) = delete;
		InitializerList(InitializerList&& Right) noexcept = delete;
		~InitializerList() noexcept;

		InitializerList<T>& operator=(const InitializerList& Source) = delete;
		InitializerList<T>& operator=(InitializerList&& Right) noexcept = delete;

		constexpr const size_t GetLength() const noexcept;

		constexpr ConstPointer GetFirst() const noexcept;
		constexpr ConstPointer GetLast() const noexcept;
	private:
		ConstPointer _First;
		ConstPointer _Last;
	};

	template<class T>
	inline InitializerList<T>::InitializerList() noexcept
		: _First(nullptr), _Last(nullptr)
	{ }

	template<class T>
	inline InitializerList<T>::InitializerList(ConstPointer First, ConstPointer Last) noexcept
		: _First(First), _Last(Last)
	{ }

	template<class T>
	inline InitializerList<T>::~InitializerList() noexcept
	{ }

	template<class T>
	inline constexpr const size_t InitializerList<T>::GetLength() const noexcept
	{
		return static_cast<size_t>(_Last - _First);
	}

	template<class T>
	inline constexpr InitializerList<T>::ConstPointer InitializerList<T>::GetFirst() const noexcept
	{
		return _First;
	}

	template<class T>
	inline constexpr InitializerList<T>::ConstPointer InitializerList<T>::GetLast() const noexcept
	{
		return _Last;
	}
	*/
}
#endif
