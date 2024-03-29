#include "DatabaseTestBase.hpp"

#ifndef ELYSIUM_CORE_INVALIDOPERATIONEXCEPTION
#include "../../../Libraries/01-Shared/Elysium.Core/InvalidOperationException.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_COMMON_DBEXCEPTION
#include "../../../Libraries/01-Shared/Elysium.Core.Data/DbException.hpp"
#endif

using namespace Elysium::Core;

DatabaseTestBase::DatabaseTestBase()
{
}
DatabaseTestBase::~DatabaseTestBase()
{
}

void DatabaseTestBase::PerformTransactionCreationTests(IDbConnection* Connection)
{
	// test 1: create a transaction after an existing one has run out of scope
	try
	{
		Connection->Open();
		{
			Template::Memory::UniquePointer<IDbTransaction> Transaction1 = Connection->BeginTransaction();
		}
		Template::Memory::UniquePointer<IDbTransaction> Transaction2 = Connection->BeginTransaction();
		Connection->Close();
	}
	catch (InvalidOperationException& ex)
	{
		Connection->Close();
		//Logger::WriteMessage(ex.GetExceptionMessage().GetCharArray());
		Assert::Fail();
	}

	// test 2: create a transaction while another one still exists
	try
	{
		Connection->Open();
		Template::Memory::UniquePointer<IDbTransaction> Transaction1 = Connection->BeginTransaction();
		Template::Memory::UniquePointer<IDbTransaction> Transaction2 = Connection->BeginTransaction();
		Connection->Close();

		// if no InvalidOperationException was thrown when creating the second transaction, this test has failed
		Assert::Fail();
	}
	catch (InvalidOperationException&)
	{
		Connection->Close();
	}
}
void DatabaseTestBase::PerformCommandCreationTests(IDbConnection * Connection)
{
	Connection->Open();
	Template::Memory::UniquePointer<IDbCommand> AdHocCommand1 = Connection->CreateCommand();
	Template::Memory::UniquePointer<IDbCommand> AdHocCommand2 = Connection->CreateCommand();

	Template::Memory::UniquePointer<IDbTransaction> Transaction = Connection->BeginTransaction();
	Template::Memory::UniquePointer<IDbCommand> TransactionAdHocCommand = Transaction->CreateCommand();

	Connection->Close();
}

void DatabaseTestBase::PerformDataInsertionTest(IDbCommand * Command)
{
	for (int i = 0; i < 10; i++)
	{
		Command->ExecuteNonQuery();
	}
}
