module;

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ARRAY
#include "Container/Array.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "Container/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DOUBLEENDEDQUEUE
#include "Container/DoubleEndedQueue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DOUBLEBUFFER
#include "Container/DoubleBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FIFOQUEUE
#include "Container/Adopter/FiFoQueue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_FUNCTION
#include "Container/Function.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_INITIALIZERLIST
#include "Container/InitializerList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_KEYVALUEPAIR
#include "Container/KeyValuePair.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLIST
#include "Container/LinkedList.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_LINKEDLISTNODE
#include "Container/LinkedListNode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_OBJECT
#include "Container/Object.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_ORDEREDMAP
#include "Container/OrderedMap.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_PRIORITYQUEUE
#include "Container/PriorityQueue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_REDBLACKTREE
#include "Container/RedBlackTree.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_RINGBUFFER
#include "Container/RingBuffer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_STACK
#include "Container/Adopter/Stack.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_TUPLE
#include "Container/Tuple.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_UNORDEREDMAP
#include "Container/UnorderedMap.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VARIANT
#include "Container/Variant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "Container/Vector.hpp"
#endif

export module Elysium.Core.Template.Container;

export
{
	using Elysium::Core::Template::Container::Array;
	using Elysium::Core::Template::Container::Delegate;
	using Elysium::Core::Template::Container::DoubleEndedQueue;
	using Elysium::Core::Template::Container::FiFoQueue;
	using Elysium::Core::Template::Container::KeyValuePair;
	using Elysium::Core::Template::Container::LinkedList;
	using Elysium::Core::Template::Container::LinkedListNode;
	using Elysium::Core::Template::Container::Object;
	//using Elysium::Core::Template::Container::OrderedMap;
	using Elysium::Core::Template::Container::PriorityQueue;
	//using Elysium::Core::Template::Container::RedBlackTree;
	using Elysium::Core::Template::Container::RingBuffer;
	using Elysium::Core::Template::Container::Stack;
	using Elysium::Core::Template::Container::Tuple;
	using Elysium::Core::Template::Container::UnorderedMap;
	//using Elysium::Core::Template::Container::Variant;
	using Elysium::Core::Template::Container::Vector;
}
