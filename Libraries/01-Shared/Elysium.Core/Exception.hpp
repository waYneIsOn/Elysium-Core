/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_EXCEPTION
#define ELYSIUM_CORE_EXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

//#pragma warning(disable : 4275)

namespace Elysium::Core
{
	namespace Collections::Template
	{
		template <typename T>
		class StringBase;
	}
	using String = Collections::Template::StringBase<char>;

	class ELYSIUM_CORE_API Exception
	{
	public:
		// constructors & destructor
		Exception();
		Exception(const char* Message);
		Exception(String&& Message);
		virtual ~Exception();

		// properties - getter
		const Exception* GetInnerException() const;

		// methods
		const String& GetExceptionMessage() const;
	private:
		String* _Message;
		Exception* _InnerException;
	};
}
#endif
