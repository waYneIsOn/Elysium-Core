/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETERCOLLECTION
#define ELYSIUM_CORE_DATA_IDATAPARAMETERCOLLECTION

#ifndef ELYSIUM_CORE_COLLECTIONS_ILIST
#include "../Elysium.Core/IList.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETER
#include "IDataParameter.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Data
		{
			class EXPORT IDataParameterCollection : public Collections::IList<IDataParameter>
			{
			public:
				/// <summary>
				/// Destroy the object using the virtual destructor
				/// </summary>
				virtual ~IDataParameterCollection() {}
			protected:
				IDataParameterCollection() {}
			};
		}
	}
}
#endif
