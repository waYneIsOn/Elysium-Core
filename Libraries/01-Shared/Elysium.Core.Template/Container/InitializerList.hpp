/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef _INITIALIZER_LIST_
#include <initializer_list>
#endif

namespace Elysium::Core::Template::Container
{
	/*
	* The brace initialization {} is built into c++. A compiler will simply know it has to create a std::initializer_list<T>.
	* I could, as a result of that, wrap it but never replace it!
	* 
	* Therefore at the moment it makes sense to simply use std::initializer_list<T>!
	* 
	* @ToDo: look for compiler options
	*/

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	using InitializerList = std::initializer_list<T>;
	
	/*
	template <class T>
	class InitializerList
	{
	public:
		using ConstPointer = const T*;
	public:
		constexpr InitializerList() noexcept;
		
		template<typename ...Args>
		constexpr InitializerList(Args... Values) noexcept;
		
		constexpr InitializerList(const std::initializer_list<T>& Values) noexcept;

		constexpr InitializerList(ConstPointer First, ConstPointer Last) noexcept;

		//constexpr InitializerList(const InitializerList& Source) = delete;

		//constexpr InitializerList(InitializerList&& Right) noexcept = delete;

		constexpr ~InitializerList() noexcept;
	public:
		//InitializerList<T>& operator=(const InitializerList& Source) = delete;

		//InitializerList<T>& operator=(InitializerList&& Right) noexcept = delete;
	public:
		constexpr const Elysium::Core::Template::System::size GetLength() const noexcept;
	public:
		constexpr ConstPointer GetBegin() const noexcept;

		constexpr ConstPointer GetEnd() const noexcept;
	private:
		ConstPointer _First;
		ConstPointer _Last;
	};

	template<class T>
	inline constexpr InitializerList<T>::InitializerList() noexcept
		: _First(nullptr), _Last(nullptr)
	{ }
	
	template<class T>
	template<typename ...Args>
	inline constexpr InitializerList<T>::InitializerList(Args... Values) noexcept
		: _First(nullptr), _Last(nullptr)	// @ToDo
	{ }
	
	template<class T>
	inline constexpr InitializerList<T>::InitializerList(const std::initializer_list<T>& Values) noexcept
		: _First(Values.begin()), _Last(Values.end())
	{ }

	template<class T>
	inline constexpr InitializerList<T>::InitializerList(ConstPointer First, ConstPointer Last) noexcept
		: _First(First), _Last(Last)
	{ }
	
	template<class T>
	inline constexpr InitializerList<T>::~InitializerList() noexcept
	{ }

	template<class T>
	inline constexpr const Elysium::Core::Template::System::size InitializerList<T>::GetLength() const noexcept
	{
		return static_cast<Elysium::Core::Template::System::size>(_Last - _First);
	}

	template<class T>
	inline constexpr InitializerList<T>::ConstPointer InitializerList<T>::GetBegin() const noexcept
	{
		return _First;
	}

	template<class T>
	inline constexpr InitializerList<T>::ConstPointer InitializerList<T>::GetEnd() const noexcept
	{
		return _Last;
	}
	*/
}
#endif
