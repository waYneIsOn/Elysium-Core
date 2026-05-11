/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIFOQUEUE
#define ELYSIUM_CORE_TEMPLATE_CONTAINER_FIFOQUEUE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SEQUENCECONTAINER
#include "../../Concepts/SequenceContainer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DEQUE
#include "../DoubleEndedQueue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "../InitializerList.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template<class T, Elysium::Core::Template::Concepts::SequenceContainer Container = Elysium::Core::Template::Container::DoubleEndedQueue<T>>
		requires Elysium::Core::Template::Concepts::Allocatable<T>
	class FiFoQueue
	{
	public:
		using Value = Container::Value;

		using Pointer = Container::Pointer;
		using ConstPointer = Container::ConstPointer;

		using Reference = Container::Reference;
		using ConstReference = Container::ConstReference;

		using RValueReference = Container::RValueReference;
	public:
		constexpr FiFoQueue() = default;

		constexpr FiFoQueue(const InitializerList<T>& InitializerList) noexcept
			: _Container(InitializerList)
		{ }

		constexpr FiFoQueue(const FiFoQueue& Source) = delete;

		constexpr FiFoQueue(FiFoQueue&& Right) noexcept = delete;

		constexpr ~FiFoQueue() = default;
	public:
		constexpr FiFoQueue& operator=(const FiFoQueue& Source) = delete;

		constexpr FiFoQueue& operator=(FiFoQueue&& Right) noexcept = delete;
	public:
		inline constexpr const bool GetIsEmpty() const noexcept (noexcept(_Container.GetIsEmpty()))
		{
			return _Container.GetIsEmpty();
		}

		inline constexpr const Elysium::Core::Template::System::size GetLength() const noexcept(noexcept(_Container.GetLength()))
		{
			return _Container.GetLength();
		}
		
		inline constexpr Reference GetFront()
		{
			return _Container.GetFront();
		}

		inline constexpr ConstReference GetFront() const
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
		/*
		inline void PushRange(ConstPointer FirstItem, const System::size Length)
		{
			_Container.PushBackRange(FirstItem, Length);
		}
		*/
		/*
		void Emplace()
		{

		}
		*/
		inline void Pop() noexcept(noexcept(_Container.PopFront()))
		{
			_Container.PopFront();
		}
		/*
		void Swap()
		{

		}
		*/
	private:
		Container _Container{};
	};
}
#endif
