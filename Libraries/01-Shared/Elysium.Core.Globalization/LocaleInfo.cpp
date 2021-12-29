#include "LocaleInfo.hpp"

#if defined ELYSIUM_CORE_OS_REQUIRES_FALLBACK_ON_GLOBALIZATION
Elysium::Core::Globalization::Internal::Fallback::LocaleInfo::LocaleInfo(Elysium::Core::int32_t&& Id, Elysium::Core::Utf8String&& Name)
	: _Id(Id), _Name(Name)
{ }
Elysium::Core::Globalization::Internal::Fallback::LocaleInfo::~LocaleInfo()
{ }
#endif

