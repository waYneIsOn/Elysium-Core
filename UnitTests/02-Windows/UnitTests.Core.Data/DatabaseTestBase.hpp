#pragma once

#include "CppUnitTest.h"

#ifndef ELYSIUM_CORE_DATA_IDBCONNECTION
#include "../../../Libraries/01-Shared/Elysium.Core.Data/IDbConnection.hpp"
#endif

using namespace Elysium::Core::Data;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class DatabaseTestBase
{
public:
	DatabaseTestBase();
	~DatabaseTestBase();
protected:
	void PerformTransactionCreationTests(IDbConnection* Connection);
	void PerformCommandCreationTests(IDbConnection* Connection);

	void PerformDataInsertionTest(IDbCommand* Command);
};

