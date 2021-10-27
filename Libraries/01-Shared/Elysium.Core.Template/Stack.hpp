/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
/*
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_STACK
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_STACK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "NonConstant.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <Concepts::NonConstant T>
	class Stack final
	{
	public:
		using Value = T;
		using ConstValue = const T;
		using Pointer = T*;
		using ConstPointer = const T*;
		using Reference = T&;
		using ConstReference = const T&;
		using RValueReference = T&&;
	public:
		Stack();
		Stack(const Stack& Source);
		Stack(Stack&& Right) noexcept;
		~Stack();

		Stack<T>& operator=(const Stack& Source);
		Stack<T>& operator=(Stack&& Right) noexcept;

		constexpr const Elysium::Core::size GetSize() const noexcept;
		constexpr const bool GetIsEmpty() const noexcept;

		Reference GetTop();
		ConstReference GetTop() const;

		void Push(ConstReference Item);
		void Push(RValueReference Item);

		void Pop();
	private:

	};
}
#endif
*/