/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER
#define ELYSIUM_CORE_TEMPLATE_MEMORY_UNIQUEPOINTER

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Memory
{
	template <class T>
	class UniquePointer
	{
	public:
		using Pointer = T*;
	private:
		//UniquePointer(Pointer Data);
	public:
		UniquePointer(const UniquePointer& Source) = delete;
		UniquePointer(UniquePointer&& Right) noexcept = delete;
		~UniquePointer();

		UniquePointer<T>& operator=(const UniquePointer& Source) = delete;
		UniquePointer<T>& operator=(UniquePointer&& Right) noexcept = delete;
	private:
		//Pointer _Data;
	};

	template<class T>
	inline UniquePointer<T>::~UniquePointer()
	{ }
}
#endif
