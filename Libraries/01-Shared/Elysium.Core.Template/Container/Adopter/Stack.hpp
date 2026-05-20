/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_STACK
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_STACK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "../../Concepts/NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SEQUENCECONTAINER
#include "../../Concepts/SequenceContainer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DOUBLEENDEDQUEUE
#include "../DoubleEndedQueue.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template <Concepts::NonConstant T, Elysium::Core::Template::Concepts::SequenceContainer Container = DoubleEndedQueue<T>>
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
		constexpr Stack() = default;

		constexpr Stack(const Stack& Source) = delete;

		constexpr Stack(Stack&& Right) noexcept = delete;

		constexpr ~Stack() = default;
	public:
		constexpr Stack<T, Container>& operator=(const Stack& Source) = delete;

		constexpr Stack<T, Container>& operator=(Stack&& Right) noexcept = delete;
	public:
		inline constexpr const bool GetIsEmpty() const noexcept (noexcept(_Container.GetIsEmpty()))
		{
			return _Container.GetIsEmpty();
		}

		inline constexpr const Elysium::Core::Template::System::size GetLength() const noexcept(noexcept(_Container.GetLength()))
		{
			return _Container.GetLength();
		}

		inline constexpr Reference GetTop()
		{
			return _Container.GetFront();
		}

		inline constexpr ConstReference GetTop() const
		{
			return _Container.GetFront();
		}
	public:
		inline void Push(ConstReference Item)
		{
			_Container.PushBack(Item);
		}

		inline void Push(RValueReference Item)
		{
			_Container.PushBack(Item);
		}

		inline void Pop() noexcept(noexcept(_Container.PopFront()))
		{
			_Container.PopFront();
		}
	private:
		Container _Container{};
	};
}
#endif