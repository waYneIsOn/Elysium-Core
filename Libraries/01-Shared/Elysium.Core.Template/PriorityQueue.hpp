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
#include "SequenceContainer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_OPERATORS_LESS
#include "Less.hpp"
#endif

namespace Elysium::Core::Template::Container
{
	template<class T, Elysium::Core::Template::Concepts::SequenceContainer Container = Elysium::Core::Template::Container::Vector<T>, 
		class Compare = Elysium::Core::Template::Operators::Less<typename Container::Value>>
	class PriorityQueue
	{
	public:
		PriorityQueue();

		PriorityQueue(const PriorityQueue& Source) = delete;

		PriorityQueue(PriorityQueue&& Right) noexcept = delete;

		~PriorityQueue();
	public:
		PriorityQueue& operator=(const PriorityQueue& Source) = delete;

		PriorityQueue& operator=(PriorityQueue&& Right) noexcept = delete;
	private:
		Container _Container;
	};

	template<class T, Elysium::Core::Template::Concepts::SequenceContainer Container, class Compare>
	inline PriorityQueue<T, Container, Compare>::PriorityQueue()
		: _Container()
	{ }

	template<class T, Elysium::Core::Template::Concepts::SequenceContainer Container, class Compare>
	inline PriorityQueue<T, Container, Compare>::~PriorityQueue()
	{ }
}
#endif
