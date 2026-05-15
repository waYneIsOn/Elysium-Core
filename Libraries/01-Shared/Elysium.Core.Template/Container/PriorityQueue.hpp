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

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_SWAP
#include "../Functional/Swap.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_LESS
#include "../Operators/Less.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	/// <summary>
	/// A queue guaranteeing that the "most valuable" item (according to given comparison-operator) always resides at the very front.
	/// 
	/// Note:
	/// As only the first, most valuable item really matters, the rest of the underlying container is not being sorted as an optimization.
	/// Index arithmetic is what "orders" all items within the container as a tree-like structure, ensuring the first item
	/// will always remain the most valuable one.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Compare"></typeparam>
	/// <typeparam name="Container"></typeparam>
	template<class T, Elysium::Core::Template::Concepts::SequenceContainer Container = Elysium::Core::Template::Container::Vector<T>, 
		class Compare = Elysium::Core::Template::Operators::Less<typename Container::Value>>
		requires Elysium::Core::Template::Concepts::Allocatable<T>
	class PriorityQueue
	{
	public:
		using Value = Container::Value;

		using Pointer = Container::Pointer;
		using ConstPointer = Container::ConstPointer;

		using Reference = Container::Reference;
		using ConstReference = Container::ConstReference;

		using RValueReference = Container::RValueReference;
	public:
		constexpr PriorityQueue() = default;

		constexpr PriorityQueue(const InitializerList<T>& InitializerList) noexcept
		{
			const T* Iterator = InitializerList.begin();
			const T* LastElement = InitializerList.end();
			for (; Iterator != LastElement; ++Iterator)
			{
				Push(*Iterator);
			}
		}

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

			// At this point the first item might not be the most valuable one. To achieve this again, 
			// I need to "sift up" by doing the following steps:
			// - Start with current index being the last one (as it's the new item that needs to be compared to others)
			// - As long as the current index is not zero (that would mean the first item is the most valuable one), do the following:
			//		- Grab the parent to compare it to the current item.
			//		- If current item is less valuable, cancel the loop.
			//		- Otherwise swap both items and update the current index.
			Elysium::Core::Template::System::size CurrentIndex = _Container.GetLength() - 1;
			while (CurrentIndex > 0)
			{
				Elysium::Core::Template::System::size ParentIndex = (CurrentIndex - 1) / 2;

				T& CurrentItem = _Container.GetUnsafeAt(CurrentIndex);
				T& ParentItem = _Container.GetUnsafeAt(ParentIndex);

				if (!_Compare(ParentItem, CurrentItem))
				{
					return;
				}

				Elysium::Core::Template::Functional::Swap(CurrentItem, ParentItem);
				CurrentIndex = ParentIndex;
			}
		}
		/*
		inline void PushRange(ConstPointer FirstItem, const System::size Length)
		{

		}
		
		inline void Emplace()
		{

		}
		*/
		inline void Pop()
		{
			const Elysium::Core::Template::System::size ContainerLength = _Container.GetLength();
			if (0 == ContainerLength)
			{
				return;
			}

			const Elysium::Core::Template::System::size ContainerLengthAfterRemoval = ContainerLength - 1;

			// Since the "largest" item resides at index 0, I simply swap it with the last one and than remove that new last one.
			// Doing it this way, there is no need to copy/move items from index 1 to n.
			Elysium::Core::Template::Functional::Swap(_Container[0], _Container[ContainerLengthAfterRemoval]);
			_Container.PopBack();

			// At this point the first item might not be the most valuable one. To achieve this again, 
			// I need to "sift down" by doing the following steps:
			// - Start with current index being 0 (as it's the new item that needs to be compared to others)
			// - Grab the current, left and right child items
			// - Compare current and left item. If the left child is less valuable, update next index.
			// - Compare current and right item. If the right child is less valuable, update next index.
			// - If next index equals current index, cancel the loop.
			// - Swap current and next item and update current index.
			Elysium::Core::Template::System::size CurrentIndex = 0;
			while (true)
			{
				Elysium::Core::Template::System::size LeftChildIndex = (2 * CurrentIndex) + 1;
				Elysium::Core::Template::System::size RightChildIndex = LeftChildIndex + 1;
				Elysium::Core::Template::System::size NextIndex = CurrentIndex;
				
				T& LeftItem = _Container.GetUnsafeAt(LeftChildIndex);
				T& RightItem = _Container.GetUnsafeAt(RightChildIndex);
				T& NextItem = _Container.GetUnsafeAt(NextIndex);

				if (LeftChildIndex < ContainerLengthAfterRemoval && _Compare(NextItem, LeftItem))
				{
					NextIndex = LeftChildIndex;
				}

				if (RightChildIndex < ContainerLengthAfterRemoval && _Compare(NextItem, RightItem))
				{
					NextIndex = RightChildIndex;
				}

				if (NextIndex == CurrentIndex)
				{
					break;
				}

				Elysium::Core::Template::Functional::Swap(_Container[CurrentIndex], _Container[NextIndex]);

				CurrentIndex = NextIndex;
			}

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
