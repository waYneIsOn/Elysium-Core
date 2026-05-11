/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_PRIORITYQUEUE
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_PRIORITYQUEUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SEQUENCECONTAINER
#include "../Concepts/SequenceContainer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_LESS
#include "../Operators/Less.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template<class T, Elysium::Core::Template::Concepts::SequenceContainer Container = Elysium::Core::Template::Container::Vector<T>, 
		class Compare = Elysium::Core::Template::Operators::Less<typename Container::Value>>
		requires Elysium::Core::Template::Concepts::Allocatable<T>
	class PriorityQueue
	{
	public:
		using Value = Container::Value;
		using ConstPointer = Container::ConstPointer;
		using ConstReference = Container::ConstReference;
	public:
		constexpr PriorityQueue() = default;

		constexpr PriorityQueue(const PriorityQueue& Source) = delete;

		constexpr PriorityQueue(PriorityQueue&& Right) noexcept = delete;

		constexpr ~PriorityQueue() = default;
	public:
		constexpr PriorityQueue& operator=(const PriorityQueue& Source) = delete;

		constexpr PriorityQueue& operator=(PriorityQueue&& Right) noexcept = delete;
	public:
		inline constexpr const bool GetIsEmpty() const noexcept (noexcept(_Container.GetIsEmpty()))
		{
			return _Container.GetIsEmpty();
		}

		inline constexpr const Elysium::Core::Template::System::size GetLength() const noexcept(noexcept(_Container.GetLength()))
		{
			return _Container.GetLength();
		}
	public:
		/*
		inline constexpr Reference Front()
		{
			return _Container.Front();
		}

		inline constexpr ConstReference Front() const
		{
			return _Container.Front();
		}
		*/
	public:
		inline void Push(ConstReference Item)
		{
			_Container.PushBack(Item);
		}

		inline void PushRange(ConstPointer FirstItem, const System::size Length)
		{
			_Container.PushBackRange(FirstItem, Length);
		}
		/*
		inline void Emplace()
		{

		}
		*/
		inline void Pop()
		{
			_Container.PopBack();
		}
		/*
		inline void Swap()
		{

		}
		*/
	private:
		Container _Container{};
		Compare _Compare{};
	};
}
#endif
