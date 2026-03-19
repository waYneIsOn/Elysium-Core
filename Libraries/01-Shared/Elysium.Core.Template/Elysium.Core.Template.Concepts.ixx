module;

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ALLOCATABLE
#include "Concepts/Allocatable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ARITHMETIC
#include "Concepts/Arithmetic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ATOMICUSABLE
#include "Concepts/AtomicUsable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CHARACTER
#include "Concepts/Character.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_COMPOSITETYPE
#include "Concepts/CompositeType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_CONSTANT
#include "Concepts/Constant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_COPYASSIGNABLEANDCONSTRUCTIBLE
#include "Concepts/CopyAssignableAndConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_DERIVEDFROM
#include "Concepts/DerivedFrom.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATION
#include "Concepts/Enumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_ENUMERATIONORINTEGRAL
#include "Concepts/EnumerationOrIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLAGENUMERATION
#include "Concepts/FlagEnumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_FLOATINGPOINT
#include "Concepts/FloatingPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASHABLE
#include "Concepts/Hashable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HASMETHOD
#include "Concepts/HasMethod.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_HUFFMANCODEABLE
#include "Concepts/HuffmanCodeable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGER
#include "Concepts/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_INTEGRAL
#include "Concepts/Integral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_LAMBDA
#include "Concepts/Lambda.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MEMBERFUNCTIONPOINTER
#include "Concepts/MemberFunctionPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVEASSIGNABLE
#include "Concepts/MoveAssignable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVEASSIGNABLEANDCONSTRUCTIBLE
#include "Concepts/MoveAssignableAndConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_MOVECONSTRUCTIBLE
#include "Concepts/MoveConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_NONCONSTANT
#include "Concepts/NonConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_POINTER
#include "Concepts/Pointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_REFERENCE
#include "Concepts/Reference.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SAMEAS
#include "Concepts/SameAs.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SEQUENCECONTAINER
#include "Concepts/SequenceContainer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_SIGNEDINTEGER
#include "Concepts/SignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_TRIVIAL
#include "Concepts/Trivial.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_TRIVIALLYCOPYABLE
#include "Concepts/TriviallyCopyable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNICODECHARACTER
#include "Concepts/UnicodeCharacter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UNSIGNEDINTEGER
#include "Concepts/UnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_VALUE
#include "Concepts/Value.hpp"
#endif

export module Elysium.Core.Template.Concepts;

export
{
	using Elysium::Core::Template::Concepts::Allocatable;
	using Elysium::Core::Template::Concepts::Arithmetic;
	using Elysium::Core::Template::Concepts::AtomicUsable;
	using Elysium::Core::Template::Concepts::Character;
	using Elysium::Core::Template::Concepts::CompositeType;
	using Elysium::Core::Template::Concepts::Constant;
	using Elysium::Core::Template::Concepts::CopyAssignableAndConstructible;
	using Elysium::Core::Template::Concepts::DerivedFrom;
	using Elysium::Core::Template::Concepts::Enumeration;
	using Elysium::Core::Template::Concepts::EnumerationOrIntegral;
	using Elysium::Core::Template::Concepts::FlagEnumeration;
	using Elysium::Core::Template::Concepts::FloatingPoint;
	using Elysium::Core::Template::Concepts::Hashable;
	using Elysium::Core::Template::Concepts::HasMethod;
	using Elysium::Core::Template::Concepts::HuffmanCodeable;
	using Elysium::Core::Template::Concepts::Integer;
	using Elysium::Core::Template::Concepts::Integral;
	using Elysium::Core::Template::Concepts::Lambda;
	//using Elysium::Core::Template::Concepts::MemberFunctionPointer;
	using Elysium::Core::Template::Concepts::MoveAssignable;
	using Elysium::Core::Template::Concepts::MoveAssignableAndConstructible;
	using Elysium::Core::Template::Concepts::MoveConstructible;
	using Elysium::Core::Template::Concepts::NonConstant;
	using Elysium::Core::Template::Concepts::Pointer;
	using Elysium::Core::Template::Concepts::Reference;
	using Elysium::Core::Template::Concepts::SameAs;
	using Elysium::Core::Template::Concepts::SequenceContainer;
	using Elysium::Core::Template::Concepts::SignedInteger;
	using Elysium::Core::Template::Concepts::Trivial;
	using Elysium::Core::Template::Concepts::TriviallyCopyable;
	using Elysium::Core::Template::Concepts::UnicodeCharacter;
	using Elysium::Core::Template::Concepts::UnsignedInteger;
	using Elysium::Core::Template::Concepts::Value;
}
