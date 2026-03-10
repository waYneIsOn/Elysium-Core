export module Elysium.Core.Template.TypeTraits;

export
{
#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_CONDITIONAL
#include "TypeTraits/Conditional.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_DISJUNCTION
#include "TypeTraits/Disjunction.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORBITWISEAND
#include "TypeTraits/HasOperatorBitwiseAnd.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORBITWISEOR
#include "TypeTraits/HasOperatorBitwiseOr.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_HASOPERATORCALL
#include "TypeTraits/HasOperatorCall.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INTEGRALCONSTANT
#include "TypeTraits/IntegralConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_INVOKERESULT
#include "TypeTraits/InvokeResult.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISAGGREGATE
#include "TypeTraits/IsAggregate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISANYOF
#include "TypeTraits/IsAnyOf.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISARITHMETIC
#include "TypeTraits/IsArithemtic.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISARRAY
#include "TypeTraits/IsArray.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISBOOLEAN
#include "TypeTraits/IsBoolean.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCHARACTER
#include "TypeTraits/IsCharacter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCLASS
#include "TypeTraits/IsClass.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCOMPLETELYDEFINED
#include "TypeTraits/IsCompletelyDefined.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONSTANT
#include "TypeTraits/IsConstant.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCONVERTIBLE
#include "TypeTraits/IsConvertible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCOPYASSIGNABLE
#include "TypeTraits/IsCopyAssignable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISCOPYCONSTRUCTIBLE
#include "TypeTraits/IsCopyConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISDERIVEDFROM
#include "TypeTraits/IsDerivedFrom.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISENUMERATION
#include "TypeTraits/IsEnumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLAGENUMERATION
#include "TypeTraits/IsFlagEnumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFLOATINGPOINT
#include "TypeTraits/IsFloatingPoint.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFUNCTION
#include "TypeTraits/IsFunction.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISFUNDAMENTAL
#include "TypeTraits/IsFundamental.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGER
#include "TypeTraits/IsInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISINTEGRAL
#include "TypeTraits/IsIntegral.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISLAMBDA
#include "TypeTraits/IsLambda.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMEMBERFUNCTIONPOINTER
#include "TypeTraits/IsMemberFunctionPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVEASSIGNABLE
#include "TypeTraits/IsMoveAssignable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISMOVECONSTRUCTIBLE
#include "TypeTraits/IsMoveConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISNOTHROWINVOCABLE
#include "TypeTraits/IsNoThrowInvocable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISNOTHROWDEFAULTCONSTRUCTIBLE
#include "TypeTraits/IsNothrowDefaultConstructible.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISNULLPOINTER
#include "TypeTraits/IsNullPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISPOINTER
#include "TypeTraits/IsPointer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISREFERENCE
#include "TypeTraits/IsReference.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSAME
#include "TypeTraits/IsSame.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSCOPEDENUMERATION
#include "TypeTraits/IsScopedEnumeration.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSIGNED
#include "TypeTraits/IsSigned.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISSIGNEDINTEGER
#include "TypeTraits/IsSignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIAL
#include "TypeTraits/IsTrivial.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISTRIVIALLYCOPYABLE
#include "TypeTraits/IsTriviallyCopyable.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISUNICODECHARACTER
#include "TypeTraits/IsUnicodeCharacter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISUNION
#include "TypeTraits/IsUnion.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISUNSIGNEDINTEGER
#include "TypeTraits/IsUnsignedInteger.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVALUE
#include "TypeTraits/IsValue.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVOID
#include "TypeTraits/IsVoid.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_ISVOLATILE
#include "TypeTraits/IsVolatile.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_SELECT
#include "TypeTraits/Select.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_UNDERLYINGTYPE
#include "TypeTraits/UnderlyingType.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS_VOIDTYPE
#include "TypeTraits/VoidType.hpp"
#endif
}
