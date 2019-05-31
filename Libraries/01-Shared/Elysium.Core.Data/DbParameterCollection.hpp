/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_COMMON_DBPARAMETERCOLLECTION
#define ELYSIUM_CORE_DATA_COMMON_DBPARAMETERCOLLECTION

#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETERCOLLECTION
#include "IDataParameterCollection.hpp"
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#pragma warning(disable : 4251)

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			namespace Common
			{
				class EXPORT DbParameterCollection : public IDataParameterCollection
				{
				public:
					/// <summary>
					/// Destroy the object using the virtual destructor
					/// </summary>
					virtual ~DbParameterCollection() {}

					virtual const size_t GetCount() const override;
					virtual const bool GetIsReadOnly()const  override;

					virtual void Add(const IDataParameter& Item) override;
					virtual void Add(const IDataParameter* Item) override;
					virtual void Clear() override;
					virtual bool Contains(const IDataParameter& Item) override;
					virtual const size_t IndexOf(const IDataParameter& Item) const override;
					virtual void Insert(size_t Index, const IDataParameter& Item) override;
					virtual bool Remove(const IDataParameter& Item) override;
					virtual void RemoveAt(size_t Index) override;

					virtual IDataParameter& operator[](size_t Index) const override;
				protected:
					DbParameterCollection();
				private:
					std::vector<const IDataParameter*> _InternalVector;
				};
			}
		}
	}
}
#endif
