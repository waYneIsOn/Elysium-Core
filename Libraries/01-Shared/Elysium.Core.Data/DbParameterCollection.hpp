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

		virtual const size_t GetCount() const override;
		virtual const bool GetIsReadOnly()const  override;

		virtual void Add(const IDataParameter& Item) override;
		virtual void Clear() override;
		virtual bool Contains(const IDataParameter& Item) const override;
		virtual const size_t IndexOf(const IDataParameter& Item) const override;
		virtual void Insert(const size_t Index, const IDataParameter& Item) override;
		virtual bool Remove(const IDataParameter& Item) override;
		virtual void RemoveAt(const size_t Index) override;

		virtual IDataParameter& operator[](const size_t Index) const override;
	protected:
		DbParameterCollection();
	private:
		std::vector<const IDataParameter*> _InternalVector;
	};
}
#endif
