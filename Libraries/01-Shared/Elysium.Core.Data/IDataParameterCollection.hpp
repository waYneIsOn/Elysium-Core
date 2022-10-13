/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETERCOLLECTION
#define ELYSIUM_CORE_DATA_IDATAPARAMETERCOLLECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETER
#include "IDataParameter.hpp"
#endif

namespace Elysium::Core::Data
{
	class ELYSIUM_CORE_DATA_API IDataParameterCollection
	{
	protected:
		IDataParameterCollection() {}
	public:
		virtual ~IDataParameterCollection() {}

		virtual IDataParameter& operator[](const Elysium::Core::size Index) const = 0;

		virtual const Elysium::Core::size IndexOf(const IDataParameter& Item) const = 0;
		virtual void Insert(const Elysium::Core::size Index, const IDataParameter& Item) = 0;
		virtual void RemoveAt(const Elysium::Core::size Index) = 0;

		virtual const Elysium::Core::size GetLength() const = 0;
		virtual const bool GetIsReadOnly() const = 0;

		virtual void Add(const IDataParameter& Item) = 0;
		virtual void Clear() = 0;
		virtual bool Contains(const IDataParameter& Item) const = 0;
		virtual bool Remove(const IDataParameter& Item) = 0;
	};
}
#endif
