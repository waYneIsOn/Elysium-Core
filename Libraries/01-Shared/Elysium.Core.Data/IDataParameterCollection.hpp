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

#ifndef ELYSIUM_CORE_COLLECTIONS_ILIST
#include "../Elysium.Core/IList.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_IDATAPARAMETER
#include "IDataParameter.hpp"
#endif

namespace Elysium::Core::Data
{
	class ELYSIUM_CORE_DATA_API IDataParameterCollection : public Collections::IList<IDataParameter>
	{
	public:
		virtual ~IDataParameterCollection() {}
	protected:
		IDataParameterCollection() {}
	};
}
#endif
