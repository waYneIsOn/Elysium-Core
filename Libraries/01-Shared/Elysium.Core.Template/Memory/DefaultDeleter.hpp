/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTDELETER
#define ELYSIUM_CORE_TEMPLATE_MEMORY_DEFAULTDELETER

#ifdef _MSC_VER
#pragma once
#endif

namespace Elysium::Core::Template::Memory
{
	template <class T>
	class DefaultDeleter
	{
	public:
		using Pointer = T*;
	public:
		DefaultDeleter();

		DefaultDeleter(const DefaultDeleter& Source) = delete;

		DefaultDeleter(DefaultDeleter&& Right) noexcept = delete;

		~DefaultDeleter();
	public:
		DefaultDeleter<T>& operator=(const DefaultDeleter& Source) = delete;

		DefaultDeleter<T>& operator=(DefaultDeleter&& Right) noexcept = delete;
	public:
		void operator()(Pointer Data) const noexcept;
	};

	template<class T>
	inline DefaultDeleter<T>::DefaultDeleter()
	{ }

	template<class T>
	inline DefaultDeleter<T>::~DefaultDeleter()
	{ }

	template<class T>
	inline void DefaultDeleter<T>::operator()(Pointer Data) const noexcept
	{
		delete Data;
	}

	template <class T>
	class DefaultDeleter<T[]>
	{
	public:
		using Pointer = T*;
	public:
		DefaultDeleter();

		DefaultDeleter(const DefaultDeleter& Source) = delete;

		DefaultDeleter(DefaultDeleter&& Right) noexcept = delete;

		~DefaultDeleter();
	public:
		DefaultDeleter<T>& operator=(const DefaultDeleter& Source) = delete;

		DefaultDeleter<T>& operator=(DefaultDeleter&& Right) noexcept = delete;
	public:
		void operator()(Pointer Data) const noexcept;
	};

	template<class T>
	inline DefaultDeleter<T[]>::DefaultDeleter()
	{ }

	template<class T>
	inline DefaultDeleter<T[]>::~DefaultDeleter()
	{ }

	template<class T>
	inline void DefaultDeleter<T[]>::operator()(Pointer Data) const noexcept
	{
		delete[] Data;
	}
}
#endif
