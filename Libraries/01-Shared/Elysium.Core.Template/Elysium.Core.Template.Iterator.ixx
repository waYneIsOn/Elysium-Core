export module Elysium.Core.Template.Iterator;

import <new>;

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_BACKWARDITERATOR
#include "Iterator/BackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTBACKWARDITERATOR
#include "Iterator/ConstBackwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTFORWARDITERATOR
#include "Iterator/ConstForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_CONSTLINKEDLISTFORWARDITERATOR
#include "Iterator/ConstLinkedListForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITEATOR_FORWARDITERATOR
#include "Iterator/ForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_LINKEDLISTFORWARDITERATOR
#include "Iterator/LinkedListForwardIterator.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_ITERATOR_UNORDEREDMAPFORWARDITERATOR
#include "Iterator/UnorderedMapForwardIterator.hpp"
#endif
}
