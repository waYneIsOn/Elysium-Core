/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_DATA_COMMON_DBPARAMETERCOLLECTION
#define ELYSIUM_CORE_DATA_COMMON_DBPARAMETERCOLLECTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETERCOLLECTION
#include "IDataParameterCollection.hpp"
#endif

#ifndef _VECTOR_
#include <vector>
#endif

namespace Elysium::Core::Data::Common
{
	class ELYSIUM_CORE_DATA_API DbParameterCollection : public IDataParameterCollection
	{
	public:
		virtual ~DbParameterCollection() {}

		virtual const Elysium::Core::size GetCount() const override;
		virtual const bool GetIsReadOnly()const  override;

		virtual void Add(const IDataParameter& Item) override;
		virtual void Clear() override;
		virtual bool Contains(const IDataParameter& Item) const override;
		virtual const Elysium::Core::size IndexOf(const IDataParameter& Item) const override;
		virtual void Insert(const Elysium::Core::size Index, const IDataParameter& Item) override;
		virtual bool Remove(const IDataParameter& Item) override;
		virtual void RemoveAt(const Elysium::Core::size Index) override;

		virtual IDataParameter& operator[](const Elysium::Core::size Index) const override;
	protected:
		DbParameterCollection();
	private:
		std::vector<const IDataParameter*> _InternalVector;
	};
}
#endif
