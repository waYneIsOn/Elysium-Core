#include "CppUnitTest.h"

#include "DatabaseTestBase.hpp"

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVECONNECTION
#include "../../../Libraries/01-Shared/Elysium.Core.Data.SqlNativeClient.OleDB/SqlNativeConnection.hpp"
#endif

#ifndef ELYSIUM_CORE_DATA_SQLNATIVECLIENT_OLEDB_SQLNATIVEEXCEPTION
#include "../../../Libraries/01-Shared/Elysium.Core.Data.SqlNativeClient.OleDB/SqlNativeException.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#endif

#ifndef MS_CPP_UNITTESTFRAMEWORK_ASSERT_EXTENSION
#include "CppUnitTestFrameworkExtension.hpp"
#endif

using namespace Elysium::Core;
using namespace Elysium::Core::Data::SqlNativeClient::OleDb;

#define STRINGIFY(x) L#x
#define EXPAND(x) STRINGIFY(x)

namespace SqlNativeClient
{
	TEST_CLASS(OleDbTests), DatabaseTestBase
	{
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			try
			{
				// create the connection and set it up so we can work with it
				SqlNativeConnection Connection = SqlNativeConnection();
				Connection.SetConnectionString(L"Driver={SQL Server Native Client 11.0};Application Name=Elysium Framework;Server=localhost;Database=master;Trusted_Connection=Yes;");
				Connection.Open();

				// make sure the test database doesn't exist
				try
				{
					std::unique_ptr<IDbCommand> DropDatabaseCommand = Connection.CreateCommand();
					DropDatabaseCommand->SetCommandText(L"DROP DATABASE IF EXISTS Test");
					size_t Result = DropDatabaseCommand->ExecuteNonQuery();
				}
				catch (SqlNativeException&)
				{
					// we don't care about any errors here
				}

				// create test database
				std::unique_ptr<IDbCommand> CreateDatabaseCommand = Connection.CreateCommand();
				CreateDatabaseCommand->SetCommandText(L"If(db_id(N'Test') IS NULL) CREATE DATABASE Test ON (NAME = Test_dat, FILENAME = 'C:\\Program Files\\Microsoft SQL Server\\MSSQL14.MSSQLSERVER\\MSSQL\\DATA\\Test.mdf', SIZE = 10, MAXSIZE = 500, FILEGROWTH = 5) LOG ON (NAME = Test_log, FILENAME = 'C:\\Program Files\\Microsoft SQL Server\\MSSQL14.MSSQLSERVER\\MSSQL\\DATA\\Test.ldf', SIZE = 5MB, MAXSIZE = 250MB, FILEGROWTH = 5MB)");
				size_t Result = CreateDatabaseCommand->ExecuteNonQuery();

				// create the test table that we will be using
				std::unique_ptr<IDbCommand> CreateTableCommand = Connection.CreateCommand();
				CreateTableCommand->SetCommandText(L"USE Test; CREATE TABLE AllDataTypes ([bigintNotNull][bigint] NOT NULL, [bigintNull][bigint] NULL, [binaryNotNull][binary] NOT NULL, [binaryNull][binary] NULL, [bitNotNull][bit] NOT NULL, [bitNull][bit] NULL, [charNotNull][char] NOT NULL, [charNull][char] NULL, [dateNotNull][date] NOT NULL, [dateNull][date] NULL, [datetime2NotNull][datetime2] NOT NULL, [datetime2Null][datetime2] NULL, [datetimeNotNull][datetime] NOT NULL, [datetimeNull][datetime] NULL, [datetimeoffsetNotNull][datetimeoffset] NOT NULL, [datetimeoffsetNull][datetimeoffset] NULL, [decimalNotNull][decimal] NOT NULL, [decimalNull][decimal] NULL, [floatNotNull][float] NOT NULL, [floatNull][float] NULL, [geographyNotNull][geography] NOT NULL, [geographyNull][geography] NULL, [geometryNotNull][geometry] NOT NULL, [geometryNull][geometry] NULL, [hierarchyidNotNull][hierarchyid] NOT NULL, [hierarchyidNull][hierarchyid] NULL, [imageNotNull][image] NOT NULL, [imageNull][image] NULL, [intNotNull][int] NOT NULL, [intNull][int] NULL, [moneyNotNull][money] NOT NULL, [moneyNull][money] NULL, [ncharNotNull][nchar] NOT NULL, [ncharNull][nchar] NULL, [ntextNotNull][ntext] NOT NULL, [ntextNull][ntext] NULL, [numericNotNull][numeric] NOT NULL, [numericNull][numeric] NULL, [nvarcharNotNull][nvarchar] NOT NULL, [nvarcharNull][nvarchar] NULL, [realNotNull][real] NOT NULL, [realNull][real] NULL, [smalldatetimeNotNull][smalldatetime] NOT NULL, [smalldatetimeNull][smalldatetime] NULL, [smallintNotNull][smallint] NOT NULL, [smallintNull][smallint] NULL, [smallmoneyNotNull][smallmoney] NOT NULL, [smallmoneyNull][smallmoney] NULL, [sql_variantNotNull][sql_variant] NOT NULL, [sql_variantNull][sql_variant] NULL, [sysnameNotNull][sysname] NOT NULL, [sysnameNull][sysname] NULL, [textNotNull][text] NOT NULL, [textNull][text] NULL, [timeNotNull][time] NOT NULL, [timeNull][time] NULL, [timestampNotNull][timestamp] NOT NULL, [tinyintNotNull][tinyint] NOT NULL, [tinyintNull][tinyint] NULL, [uniqueidentifierNotNull][uniqueidentifier] NOT NULL, [uniqueidentifierNull][uniqueidentifier] NULL, [varbinaryNotNull][varbinary] NOT NULL, [varbinaryNull][varbinary] NULL, [varcharNotNull][varchar] NOT NULL, [varcharNull][varchar] NULL, [xmlNotNull][xml] NOT NULL, [xmlNull][xml] NULL)");
				Result = CreateTableCommand->ExecuteNonQuery();

				Connection.Close();
			}
			catch (SqlNativeException& ex)
			{
				LogSqlNativeException(ex);
				Assert::Fail();
			}
		}
		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			try
			{
				// create the connection and set it up so we can work with it
				SqlNativeConnection Connection = SqlNativeConnection();
				Connection.SetConnectionString(L"Driver={SQL Server Native Client 11.0};Application Name=Elysium Framework;Server=localhost;Database=master;Trusted_Connection=Yes;");
				Connection.Open();

				// delete test database
				std::unique_ptr<IDbCommand> DropDatabaseCommand = Connection.CreateCommand();
				DropDatabaseCommand->SetCommandText(L"DROP DATABASE IF EXISTS Test");
				size_t Result = DropDatabaseCommand->ExecuteNonQuery();

				Connection.Close();
			}
			catch (SqlNativeException& ex)
			{
				Logger::WriteMessage("ClassCleanup\r\n");
				LogSqlNativeException(ex);
				Assert::Fail();
			}
		}

		TEST_METHOD_INITIALIZE(Initialize)
		{
			// create the connection and set it up so we can work with it
			_Connection = SqlNativeConnection();
			_Connection.SetConnectionString(L"Driver={SQL Server Native Client 11.0};Application Name=Elysium Framework;Server=localhost;Database=ElysiumTest;Trusted_Connection=Yes;");
		}

		TEST_METHOD(TransactionCreation)
		{
			PerformTransactionCreationTests(&_Connection);
		}
		TEST_METHOD(CommandCreation)
		{
			PerformCommandCreationTests(&_Connection);
		}
		TEST_METHOD(ChangeDatabase)
		{
			_Connection.Open();
			_Connection.ChangeDatabase(L"Test");
			try
			{
				_Connection.ChangeDatabase(L"NonExistantDatabase");
				Assert::Fail();
			}
			catch (Exception&)
			{
  }
_Connection.ChangeDatabase(L"master");
_Connection.Close();
}

		TEST_METHOD(CRUDWithoutParameters)
		{
			try
			{
				// get the project path so we can get the FQPN to the test-image
				std::wstring ProjectPath = EXPAND(UNITTESTPRJ);
				ProjectPath.erase(0, 1); // erase the first quote
				ProjectPath.erase(ProjectPath.size() - 2); // erase the last quote and the dot

				_Connection.Open();

				// perform C test
				std::unique_ptr<IDbCommand> InsertCommand = _Connection.CreateCommand();
				InsertCommand->SetCommandText(L"SET ANSI_WARNINGS OFF; USE Test; INSERT INTO AllDataTypes ([bigintNotNull], [bigintNull], [binaryNotNull], [binaryNull], [bitNotNull], [bitNull], [charNotNull], [charNull], [dateNotNull], [dateNull], [datetime2NotNull], [datetime2Null], [datetimeNotNull], [datetimeNull], [datetimeoffsetNotNull], [datetimeoffsetNull], [decimalNotNull], [decimalNull], [floatNotNull], [floatNull], [geographyNotNull], [geographyNull], [geometryNotNull], [geometryNull], [hierarchyidNotNull], [hierarchyidNull], [imageNotNull], [imageNull], [intNotNull], [intNull], [moneyNotNull], [moneyNull], [ncharNotNull], [ncharNull], [ntextNotNull], [ntextNull], [numericNotNull], [numericNull], [nvarcharNotNull], [nvarcharNull], [realNotNull], [realNull], [smalldatetimeNotNull], [smalldatetimeNull], [smallintNotNull], [smallintNull], [smallmoneyNotNull], [smallmoneyNull], [sql_variantNotNull], [sql_variantNull], [sysnameNotNull], [sysnameNull], [textNotNull], [textNull], [timeNotNull], [timeNull], [timestampNotNull], [tinyintNotNull], [tinyintNull], [uniqueidentifierNotNull], [uniqueidentifierNull], [varbinaryNotNull], [varbinaryNull], [varcharNotNull], [varcharNull], [xmlNotNull], [xmlNull]) VALUES (9223372036854775807, NULL, CONVERT(varbinary(9), N'varbinary'), NULL, 1, NULL, 'a', NULL, CONVERT(date, '18-06-12', 5), NULL, CONVERT(datetime2,'18-06-12 10:34:09 PM', 5), NULL, CONVERT(datetime,'18-06-12 10:34:09 PM', 5), NULL, CONVERT(datetimeoffset,'12-10-25 12:32:10 +01:00'), NULL, 1.35, NULL, 0.27, NULL, geography::Point(47.65100, -122.34900, 4326), NULL, geometry::STGeomFromText('POINT (22.9901232886963 87.5953903123242)', 4326), NULL, HierarchyID::GetRoot(), NULL, (SELECT * FROM OPENROWSET(BULK N'" + ProjectPath + L"\\TestImage.png', SINGLE_BLOB) AS Image), NULL, 23, NULL, 37.56, NULL, N'n', NULL, N't', NULL, 99.1, NULL, N'n', NULL, 23.56, NULL, '02/10/2010 12:30', NULL, 23, NULL, 75.45, NULL, 'v', NULL, N's', NULL, 's', NULL, '13:37:27', NULL, DEFAULT, 17, NULL, CONVERT(uniqueidentifier, 'AE019609-99E0-4EF5-85BB-AD90DC302E70'), NULL, CAST('wahid' AS VARBINARY(5)), NULL, 'v', NULL, CONVERT(XML, N'<?xml version=\"1.0\" encoding=\"UTF-16\"?><root/>'), NULL)");
				PerformDataInsertionTest(InsertCommand.get());

				// perform R test
				std::unique_ptr<IDbCommand> SelectCommand = _Connection.CreateCommand();
				SelectCommand->SetCommandText(L"SELECT [bigintNotNull], [bigintNull], [binaryNotNull], [binaryNull], [bitNotNull], [bitNull], [charNotNull], [charNull], [dateNotNull], [dateNull], [datetime2NotNull], [datetime2Null], [datetimeNotNull], [datetimeNull], [datetimeoffsetNotNull], [datetimeoffsetNull], [decimalNotNull], [decimalNull], [floatNotNull], [floatNull], [geographyNotNull], [geographyNull], [geographyNotNull].Lat As Latitude, [geographyNotNull].Long As Longitude, [geographyNotNull].M As Magnitude, [geographyNotNull].Z As Depth, [geometryNotNull], [geometryNull], [hierarchyidNotNull], [hierarchyidNull], [hierarchyidNotNull].ToString() AS HierarchyPath, [hierarchyidNotNull].GetLevel() AS HierarchyLevel, [imageNotNull], [imageNull], [intNotNull], [intNull], [moneyNotNull], [moneyNull], [ncharNotNull], [ncharNull], [ntextNotNull], [ntextNull], [numericNotNull], [numericNull], [nvarcharNotNull], [nvarcharNull], [realNotNull], [realNull], [smalldatetimeNotNull], [smalldatetimeNull], [smallintNotNull], [smallintNull], [smallmoneyNotNull], [smallmoneyNull], [sql_variantNotNull], [sql_variantNull], [sysnameNotNull], [sysnameNull], [textNotNull], [textNull], [timeNotNull], [timeNull], [timestampNotNull], [tinyintNotNull], [tinyintNull], [uniqueidentifierNotNull], [uniqueidentifierNull], [varbinaryNotNull], [varbinaryNull], [varcharNotNull], [varcharNull], [xmlNotNull], [xmlNull] FROM AllDataTypes");
				TestReader(SelectCommand);

				// perform U test
				std::unique_ptr<IDbCommand> UpdateCommand = _Connection.CreateCommand();
				UpdateCommand->SetCommandText(L"UPDATE AllDataTypes SET [bigintNull] = 123");
				UpdateCommand->ExecuteNonQuery();

				// perform D test
				std::unique_ptr<IDbCommand> DeleteCommand = _Connection.CreateCommand();
				DeleteCommand->SetCommandText(L"DELETE FROM AllDataTypes");
				DeleteCommand->ExecuteNonQuery();

				_Connection.Close();
			}
			catch (SqlNativeException& ex)
			{
				LogSqlNativeException(ex);
				Assert::Fail();
			}
			catch (Exception& ex)
			{
				Logger::WriteMessage(ex.GetExceptionMessage().GetCharArray());
				Assert::Fail();
			}
		}
		TEST_METHOD(CRUDWithUnnamedParameters)
		{
			try
			{
				// get the project path so we can get the FQPN to the test-image
				std::wstring ProjectPath = EXPAND(UNITTESTPRJ);
				ProjectPath.erase(0, 1); // erase the first quote
				ProjectPath.erase(ProjectPath.size() - 2); // erase the last quote and the dot

				_Connection.Open();

				// perform C test
				std::unique_ptr<IDbCommand> InsertCommand = _Connection.CreateCommand();
				InsertCommand->SetCommandText(L"SET ANSI_WARNINGS OFF; USE Test; INSERT INTO AllDataTypes ([bigintNotNull], [bigintNull], [binaryNotNull], [binaryNull], [bitNotNull], [bitNull], [charNotNull], [charNull], [dateNotNull], [dateNull], [datetime2NotNull], [datetime2Null], [datetimeNotNull], [datetimeNull], [datetimeoffsetNotNull], [datetimeoffsetNull], [decimalNotNull], [decimalNull], [floatNotNull], [floatNull], [geographyNotNull], [geographyNull], [geometryNotNull], [geometryNull], [hierarchyidNotNull], [hierarchyidNull], [imageNotNull], [imageNull], [intNotNull], [intNull], [moneyNotNull], [moneyNull], [ncharNotNull], [ncharNull], [ntextNotNull], [ntextNull], [numericNotNull], [numericNull], [nvarcharNotNull], [nvarcharNull], [realNotNull], [realNull], [smalldatetimeNotNull], [smalldatetimeNull], [smallintNotNull], [smallintNull], [smallmoneyNotNull], [smallmoneyNull], [sql_variantNotNull], [sql_variantNull], [sysnameNotNull], [sysnameNull], [textNotNull], [textNull], [timeNotNull], [timeNull], [timestampNotNull], [tinyintNotNull], [tinyintNull], [uniqueidentifierNotNull], [uniqueidentifierNull], [varbinaryNotNull], [varbinaryNull], [varcharNotNull], [varcharNull], [xmlNotNull], [xmlNull]) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 1.35, NULL, ?, ?, geography::Point(47.65100, -122.34900, 4326), NULL, geometry::STGeomFromText('POINT (22.9901232886963 87.5953903123242)', 4326), NULL, HierarchyID::GetRoot(), NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 99.1, NULL, ?, ?, ?, ?, '02/10/2010 12:30', NULL, ?, ?, ?, ?, 'v', NULL, ?, ?, 's', NULL, ?, ?, DEFAULT, ?, ?, ?, ?, CAST('wahid' AS VARBINARY(5)), NULL, 'v', NULL, ?, ?)");

				// __int64 (bigint)
				std::unique_ptr<IDataParameter> Int64Parameter = InsertCommand->CreateParameter();
				Int64Parameter->SetValue(9223372036854775807);
				InsertCommand->GetParameters()->Add(Int64Parameter.get());

				std::unique_ptr<IDataParameter> Int64NullParameter = InsertCommand->CreateParameter();
				Int64NullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(Int64NullParameter.get());

				// BYTE (binary)
				std::unique_ptr<IDataParameter> ByteParameter = InsertCommand->CreateParameter();
				ByteParameter->SetValue((BYTE)'v');	//0x76
				InsertCommand->GetParameters()->Add(ByteParameter.get());

				std::unique_ptr<IDataParameter> ByteNullParameter = InsertCommand->CreateParameter();
				ByteNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(ByteNullParameter.get());

				// bool (bit)
				std::unique_ptr<IDataParameter> BoolParameter = InsertCommand->CreateParameter();
				BoolParameter->SetValue(true);
				InsertCommand->GetParameters()->Add(BoolParameter.get());

				std::unique_ptr<IDataParameter> BoolNullParameter = InsertCommand->CreateParameter();
				BoolNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(BoolNullParameter.get());

				// char (option 1)
				/*
				std::unique_ptr<IDataParameter> CharParameter = InsertCommand->CreateParameter();
				CharParameter->SetValue('a');
				InsertCommand->GetParameters()->Add(CharParameter.get());

				std::unique_ptr<IDataParameter> CharNullParameter = InsertCommand->CreateParameter();
				CharNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(CharNullParameter.get());
				*/
				// char (option 2)
				/*
				std::unique_ptr<IDataParameter> StringParameter = InsertCommand->CreateParameter();
				StringParameter->SetValue(&std::string("a - mssql will trim automatically"));
				InsertCommand->GetParameters()->Add(StringParameter.get());

				std::unique_ptr<IDataParameter> StringNullParameter = InsertCommand->CreateParameter();
				StringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(StringNullParameter.get());
				*/
				// char (option 3)
				Elysium::Core::IO::MemoryStream StringStream;
				StringStream.Write((const BYTE*)"a - mssql won't trim automatically so set the length correctly!!!!", 0, 1);
				StringStream.SetPosition(0);

				std::unique_ptr<IDataParameter> StreamedStringParameter = InsertCommand->CreateParameter();
				StreamedStringParameter->SetValue(&StringStream);
				InsertCommand->GetParameters()->Add(StreamedStringParameter.get());

				std::unique_ptr<IDataParameter> StreamedStringNullParameter = InsertCommand->CreateParameter();
				StreamedStringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(StreamedStringNullParameter.get());

				// DateTime (date)
				std::unique_ptr<IDataParameter> DateParameter = InsertCommand->CreateParameter();
				DateParameter->SetValue(&DateTime(2012, 06, 18));
				DateParameter->SetDbType(DbType::Date);
				InsertCommand->GetParameters()->Add(DateParameter.get());

				std::unique_ptr<IDataParameter> DateNullParameter = InsertCommand->CreateParameter();
				DateNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(DateNullParameter.get());

				// DateTime (datetime2)
				std::unique_ptr<IDataParameter> DateTime2Parameter = InsertCommand->CreateParameter();
				DateTime2Parameter->SetValue(&DateTime(2012, 06, 18, 22, 34, 9));
				DateTime2Parameter->SetDbType(DbType::DateTime2);
				InsertCommand->GetParameters()->Add(DateTime2Parameter.get());

				std::unique_ptr<IDataParameter> DateTime2NullParameter = InsertCommand->CreateParameter();
				DateTime2NullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(DateTime2NullParameter.get());

				// DateTime (datetime)
				std::unique_ptr<IDataParameter> DateTimeParameter = InsertCommand->CreateParameter();
				DateTimeParameter->SetValue(&DateTime(2012, 06, 18, 22, 34, 9));
				DateTimeParameter->SetDbType(DbType::DateTime);
				InsertCommand->GetParameters()->Add(DateTimeParameter.get());

				std::unique_ptr<IDataParameter> DateTimeNullParameter = InsertCommand->CreateParameter();
				DateTimeNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(DateTimeNullParameter.get());

				// DateTimeOffset (datetimeoffset)
				std::unique_ptr<IDataParameter> DateTimeOffsetParameter = InsertCommand->CreateParameter();
				DateTimeOffsetParameter->SetValue(&DateTimeOffset(DateTime(2025, 12, 10, 12, 32, 10), TimeSpan::FromHours(1.0)));
				InsertCommand->GetParameters()->Add(DateTimeOffsetParameter.get());

				std::unique_ptr<IDataParameter> DateTimeOffsetNullParameter = InsertCommand->CreateParameter();
				DateTimeOffsetNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(DateTimeOffsetNullParameter.get());
				/*
				// decimal
				decimal DecimalValue;
				DecimalValue.LowPart = (__int64)1;
				DecimalValue.HighPart = (__int64)35;

				std::unique_ptr<IDataParameter> DecimalParameter = InsertCommand->CreateParameter();
				DecimalParameter->SetValue(&DecimalValue);
				InsertCommand->GetParameters()->Add(DecimalParameter.get());

				std::unique_ptr<IDataParameter> DecimalNullParameter = InsertCommand->CreateParameter();
				DecimalNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(DecimalNullParameter.get());
				*/
				// float
				std::unique_ptr<IDataParameter> SingleParameter = InsertCommand->CreateParameter();
				SingleParameter->SetValue(0.27f);
				InsertCommand->GetParameters()->Add(SingleParameter.get());

				std::unique_ptr<IDataParameter> SingleNullParameter = InsertCommand->CreateParameter();
				SingleNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(SingleNullParameter.get());

				// geography - ToDo: mssql specific type

				// geometry - ToDo: mssql specific type

				// hierarchyid - ToDo: mssql specific type

				// image
				Elysium::Core::IO::FileStream ImageStream(Elysium::Core::String((ProjectPath + L"\\TestImage.png").c_str()), Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read, Elysium::Core::IO::FileShare::Read);
				std::unique_ptr<IDataParameter> ImageParameter = InsertCommand->CreateParameter();
				ImageParameter->SetValue(&ImageStream);
				InsertCommand->GetParameters()->Add(ImageParameter.get());

				std::unique_ptr<IDataParameter> ImageNullParameter = InsertCommand->CreateParameter();
				ImageNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(ImageNullParameter.get());

				// __int32 (int)
				std::unique_ptr<IDataParameter> Int32Parameter = InsertCommand->CreateParameter();
				Int32Parameter->SetValue((__int32)23);
				InsertCommand->GetParameters()->Add(Int32Parameter.get());

				std::unique_ptr<IDataParameter> Int32NullParameter = InsertCommand->CreateParameter();
				Int32NullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(Int32NullParameter.get());

				// money
				std::unique_ptr<IDataParameter> MoneyParameter = InsertCommand->CreateParameter();
				MoneyParameter->SetValue(37.56);
				InsertCommand->GetParameters()->Add(MoneyParameter.get());

				std::unique_ptr<IDataParameter> MoneyNullParameter = InsertCommand->CreateParameter();
				MoneyNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(MoneyNullParameter.get());

				// nchar (option 1)
				/*
				std::unique_ptr<IDataParameter> WCharParameter = InsertCommand->CreateParameter();
				WCharParameter->SetValue(L'n');
				InsertCommand->GetParameters()->Add(WCharParameter.get());

				std::unique_ptr<IDataParameter> WCharNullParameter = InsertCommand->CreateParameter();
				WCharNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(WCharNullParameter.get());
				*/
				// nchar (option 2)
				/*
				std::unique_ptr<IDataParameter> WStringParameter = InsertCommand->CreateParameter();
				WStringParameter->SetValue(&std::wstring(L"n - mssql will trim automatically"));
				InsertCommand->GetParameters()->Add(WStringParameter.get());

				std::unique_ptr<IDataParameter> WStringNullParameter = InsertCommand->CreateParameter();
				WStringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(WStringNullParameter.get());
				*/
				// nchar (option 3)
				Elysium::Core::IO::MemoryStream WStringStream;
				WStringStream.Write((const BYTE*)L"n - mssql won't trim automatically so set the length correctly!!!!", 0, 2);
				WStringStream.SetPosition(0);

				std::unique_ptr<IDataParameter> StreamedWStringParameter = InsertCommand->CreateParameter();
				StreamedWStringParameter->SetValue(&WStringStream);
				InsertCommand->GetParameters()->Add(StreamedWStringParameter.get());

				std::unique_ptr<IDataParameter> StreamedWStringNullParameter = InsertCommand->CreateParameter();
				StreamedWStringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(StreamedWStringNullParameter.get());

				// ntext (option 1)
				/*
				std::unique_ptr<IDataParameter> WTextParameter = InsertCommand->CreateParameter();
				WTextParameter->SetValue(L't - mssql will trim automatically');
				InsertCommand->GetParameters()->Add(WTextParameter.get());

				std::unique_ptr<IDataParameter> WTextNullParameter = InsertCommand->CreateParameter();
				WTextNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(WTextNullParameter.get());
				*/
				// ntext (option 2)
				/*
				std::unique_ptr<IDataParameter> WTextStringParameter = InsertCommand->CreateParameter();
				WTextStringParameter->SetValue(&std::wstring(L"t - mssql will trim automatically"));
				InsertCommand->GetParameters()->Add(WTextStringParameter.get());

				std::unique_ptr<IDataParameter> WTextStringNullParameter = InsertCommand->CreateParameter();
				WTextStringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(WTextStringNullParameter.get());
				*/
				// ntext (option 3)
				Elysium::Core::IO::MemoryStream WTextStringStream;
				WTextStringStream.Write((const BYTE*)L"t - mssql won't trim automatically so set the length correctly!!!!", 0, 2);
				WTextStringStream.SetPosition(0);

				std::unique_ptr<IDataParameter> StreamedWTextStringParameter = InsertCommand->CreateParameter();
				StreamedWTextStringParameter->SetValue(&WTextStringStream);
				InsertCommand->GetParameters()->Add(StreamedWTextStringParameter.get());

				std::unique_ptr<IDataParameter> StreamedWTextStringNullParameter = InsertCommand->CreateParameter();
				StreamedWTextStringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(StreamedWTextStringNullParameter.get());

				// numeric (decimal)

				// nvarchar
				std::unique_ptr<IDataParameter> NVarCharParameter = InsertCommand->CreateParameter();
				NVarCharParameter->SetValue(L'n');
				InsertCommand->GetParameters()->Add(NVarCharParameter.get());

				std::unique_ptr<IDataParameter> NVarCharNullParameter = InsertCommand->CreateParameter();
				NVarCharNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(NVarCharNullParameter.get());

				// real
				std::unique_ptr<IDataParameter> RealParameter = InsertCommand->CreateParameter();
				RealParameter->SetValue(23.559999465942383f);
				InsertCommand->GetParameters()->Add(RealParameter.get());

				std::unique_ptr<IDataParameter> RealNullParameter = InsertCommand->CreateParameter();
				RealNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(RealNullParameter.get());
				/*
				// smalldatetime - ToDo: mssql specific type
				std::unique_ptr<IDataParameter> SmallDateTimeParameter = InsertCommand->CreateParameter();
				SmallDateTimeParameter->SetValue(&DateTime(2010, 02, 10, 12, 30, 0));
				SmallDateTimeParameter->SetDbType(DbType::SmallDateTime);
				InsertCommand->GetParameters()->Add(SmallDateTimeParameter.get());

				std::unique_ptr<IDataParameter> SmallDateTimeNullParameter = InsertCommand->CreateParameter();
				SmallDateTimeNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(SmallDateTimeNullParameter.get());
				*/
				// int16 (smallint)
				std::unique_ptr<IDataParameter> Int16Parameter = InsertCommand->CreateParameter();
				Int16Parameter->SetValue(23);
				InsertCommand->GetParameters()->Add(Int16Parameter.get());

				std::unique_ptr<IDataParameter> Int16NullParameter = InsertCommand->CreateParameter();
				Int16NullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(Int16NullParameter.get());

				// float (smallmoney)
				std::unique_ptr<IDataParameter> SmallmoneyParameter = InsertCommand->CreateParameter();
				SmallmoneyParameter->SetValue(75.45f);
				InsertCommand->GetParameters()->Add(SmallmoneyParameter.get());

				std::unique_ptr<IDataParameter> SmallmoneyNullParameter = InsertCommand->CreateParameter();
				SmallmoneyNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(SmallmoneyNullParameter.get());

				// sql_variant

				// sysname

				// text (option 1)
				/*
				std::unique_ptr<IDataParameter> TextParameter = InsertCommand->CreateParameter();
				TextParameter->SetValue('s');
				InsertCommand->GetParameters()->Add(TextParameter.get());

				std::unique_ptr<IDataParameter> TextNullParameter = InsertCommand->CreateParameter();
				TextNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(TextNullParameter.get());
				*/
				// text (option 2)
				/*
				std::unique_ptr<IDataParameter> TextStringParameter = InsertCommand->CreateParameter();
				TextStringParameter->SetValue(&std::string("s - mssql will trim automatically"));
				InsertCommand->GetParameters()->Add(TextStringParameter.get());

				std::unique_ptr<IDataParameter> TextStringNullParameter = InsertCommand->CreateParameter();
				TextStringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(TextStringNullParameter.get());
				*/
				// ntext (option 3)
				Elysium::Core::IO::MemoryStream TextStringStream;
				TextStringStream.Write((const BYTE*)L"s - mssql won't trim automatically so set the length correctly!!!!", 0, 2);
				TextStringStream.SetPosition(0);

				std::unique_ptr<IDataParameter> StreamedTextStringParameter = InsertCommand->CreateParameter();
				StreamedTextStringParameter->SetValue(&TextStringStream);
				InsertCommand->GetParameters()->Add(StreamedTextStringParameter.get());

				std::unique_ptr<IDataParameter> StreamedTextStringNullParameter = InsertCommand->CreateParameter();
				StreamedTextStringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(StreamedTextStringNullParameter.get());

				// time
				std::unique_ptr<IDataParameter> TimeParameter = InsertCommand->CreateParameter();
				TimeParameter->SetValue(&TimeSpan(13, 37, 27));
				InsertCommand->GetParameters()->Add(TimeParameter.get());

				std::unique_ptr<IDataParameter> TimeNullParameter = InsertCommand->CreateParameter();
				TimeNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(TimeNullParameter.get());
				/*
				// timestamp - this datatype equals a 'rowversion' and doesn't contain DateTime-information as the name might imply
				std::unique_ptr<IDataParameter> RowVersionParameter = InsertCommand->CreateParameter();
				RowVersionParameter->SetValue((__int64)345345345);
				InsertCommand->GetParameters()->Add(RowVersionParameter.get());
				*/
				// BYTE (tinyint)
				std::unique_ptr<IDataParameter> TinyIntParameter = InsertCommand->CreateParameter();
				TinyIntParameter->SetValue((unsigned short)17);
				InsertCommand->GetParameters()->Add(TinyIntParameter.get());

				std::unique_ptr<IDataParameter> TinyIntNullParameter = InsertCommand->CreateParameter();
				TinyIntNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(TinyIntNullParameter.get());

				// GUID (uniqueidentifier)
				std::unique_ptr<IDataParameter> GuidParameter = InsertCommand->CreateParameter();
				GuidParameter->SetValue(&Guid::Parse("ae019609-99e0-4ef5-85bb-ad90dc302e70"));
				InsertCommand->GetParameters()->Add(GuidParameter.get());

				//Assert::AreEqual("ae019609-99e0-4ef5-85bb-ad90dc302e70", Guid::Parse("ae019609-99e0-4ef5-85bb-ad90dc302e70").ToString().c_str());

				std::unique_ptr<IDataParameter> GuidNullParameter = InsertCommand->CreateParameter();
				GuidNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(GuidNullParameter.get());

				// varbinary

				// vchar

				// xml
				std::unique_ptr<IDataParameter> XmlParameter = InsertCommand->CreateParameter();
				XmlParameter->SetValue(&std::string("<?xml version=\"1.0\" encoding=\"UTF-16\"?><root/>"));
				//XmlParameter->SetDbType(DbType::Xml);
				InsertCommand->GetParameters()->Add(XmlParameter.get());

				std::unique_ptr<IDataParameter> XmlNullParameter = InsertCommand->CreateParameter();
				XmlNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters()->Add(XmlNullParameter.get());

				PerformDataInsertionTest(InsertCommand.get());

				// perform R test
				std::unique_ptr<IDbCommand> SelectCommand = _Connection.CreateCommand();
				SelectCommand->SetCommandText(L"SELECT [bigintNotNull], [bigintNull], [binaryNotNull], [binaryNull], [bitNotNull], [bitNull], [charNotNull], [charNull], [dateNotNull], [dateNull], [datetime2NotNull], [datetime2Null], [datetimeNotNull], [datetimeNull], [datetimeoffsetNotNull], [datetimeoffsetNull], [decimalNotNull], [decimalNull], [floatNotNull], [floatNull], [geographyNotNull], [geographyNull], [geographyNotNull].Lat As Latitude, [geographyNotNull].Long As Longitude, [geographyNotNull].M As Magnitude, [geographyNotNull].Z As Depth, [geometryNotNull], [geometryNull], [hierarchyidNotNull], [hierarchyidNull], [hierarchyidNotNull].ToString() AS HierarchyPath, [hierarchyidNotNull].GetLevel() AS HierarchyLevel, [imageNotNull], [imageNull], [intNotNull], [intNull], [moneyNotNull], [moneyNull], [ncharNotNull], [ncharNull], [ntextNotNull], [ntextNull], [numericNotNull], [numericNull], [nvarcharNotNull], [nvarcharNull], [realNotNull], [realNull], [smalldatetimeNotNull], [smalldatetimeNull], [smallintNotNull], [smallintNull], [smallmoneyNotNull], [smallmoneyNull], [sql_variantNotNull], [sql_variantNull], [sysnameNotNull], [sysnameNull], [textNotNull], [textNull], [timeNotNull], [timeNull], [timestampNotNull], [tinyintNotNull], [tinyintNull], [uniqueidentifierNotNull], [uniqueidentifierNull], [varbinaryNotNull], [varbinaryNull], [varcharNotNull], [varcharNull], [xmlNotNull], [xmlNull] FROM AllDataTypes");
				TestReader(SelectCommand);

				// perform U test
				std::unique_ptr<IDbCommand> UpdateCommand = _Connection.CreateCommand();
				UpdateCommand->SetCommandText(L"UPDATE AllDataTypes SET [bigintNull] = ?");
				std::unique_ptr<IDataParameter> UpdateParameter = UpdateCommand->CreateParameter();
				UpdateParameter->SetValue((__int64)123);
				UpdateCommand->GetParameters()->Add(UpdateParameter.get());
				UpdateCommand->ExecuteNonQuery();

				// perform D test
				std::unique_ptr<IDbCommand> DeleteCommand = _Connection.CreateCommand();
				DeleteCommand->SetCommandText(L"DELETE FROM AllDataTypes");
				DeleteCommand->ExecuteNonQuery();

				_Connection.Close();
			}
			catch (SqlNativeException& ex)
			{
				LogSqlNativeException(ex);
				Assert::Fail();
			}
			catch (Exception& ex)
			{
				Logger::WriteMessage(ex.GetExceptionMessage().GetCharArray());
				Assert::Fail();
			}
		}
		TEST_METHOD(CRUDWithNamedParameters)
		{
			// oledb doesn't support named parameters. therefore just do nothing here.
		}
private:
	SqlNativeConnection _Connection;

	static void TestReader(const std::unique_ptr<IDbCommand>& Command)
	{
		std::unique_ptr<IDataReader> Reader = Command->ExecuteReader();

		// test a few reader methods before actually starting to read
		{
			//Assert::AreSame(10L, Reader->GetRecordsAffected());

			std::wstring ColumnDataTypeName;
			std::wstring ColumnName;
			unsigned __int64 ColumnOrdinal;

			Reader->GetDataTypeName(5, &ColumnDataTypeName);
			Assert::AreEqual(L"DBTYPE_BOOL", ColumnDataTypeName.data());

			Reader->GetName(0, &ColumnName);
			Assert::AreEqual(L"bigintNotNull", ColumnName.data());

			Reader->GetOrdinal(L"binaryNull", &ColumnOrdinal);
			Assert::AreEqual(3ULL, ColumnOrdinal);
		}

		__int64 AvailableBytes;
		int64_t BigIntValue;
		std::vector<BYTE> BytesValue(1);
		bool BitValue;
		std::string CharValues = std::string(1, '\0');
		DateTime DatetimeValue = DateTime(0);
		DateTimeOffset DateTimeOffsetValue = DateTimeOffset(DatetimeValue);
		TimeSpan TimeSpanValue = TimeSpan(0);
		Decimal DecimalValue;
		float FloatValue;
		double DoubleValue;
		std::wstring WCharValues = std::wstring(1, '\0');
		int16_t Int16Value;
		int IntValue;
		byte GuidData[16];
		Guid GUIDValue = Guid(GuidData);
		while (Reader->Read())
		{
			// bigint
			Reader->GetInt64(0, &BigIntValue);
			Assert::AreEqual(9223372036854775807, BigIntValue);
			Assert::IsFalse(Reader->IsDBNull(0));
			Assert::IsTrue(Reader->IsDBNull(1));

			// binary
			Reader->GetByte(2, BytesValue.data());
			Assert::AreEqual((BYTE)'v', BytesValue[0]);
			AvailableBytes = Reader->GetBytes(2, 0, nullptr, 0, 1);
			BytesValue.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetBytes(2, 0, BytesValue.data(), 0, 1);
			Assert::AreEqual((BYTE)'v', BytesValue.data()[0]);
			Assert::IsFalse(Reader->IsDBNull(2));
			Assert::IsTrue(Reader->IsDBNull(3));

			// bit
			Reader->GetBoolean(4, &BitValue);
			Assert::AreEqual(true, BitValue);
			Assert::IsFalse(Reader->IsDBNull(4));
			Assert::IsTrue(Reader->IsDBNull(5));

			// char
			Reader->GetChar(6, CharValues.data());
			Assert::AreEqual('a', CharValues.data()[0]);
			AvailableBytes = Reader->GetChars(6, 0, nullptr, 0, 0);
			CharValues.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetChars(6, 0, CharValues.data(), 0, (size_t)AvailableBytes);
			Assert::AreEqual('a', CharValues.data()[0]);
			Assert::IsFalse(Reader->IsDBNull(6));
			Assert::IsTrue(Reader->IsDBNull(7));

			// date
			Reader->GetDateTime(8, &DatetimeValue);
			DatetimeValue.GetDay(&IntValue);
			Assert::AreEqual(18, IntValue);
			DatetimeValue.GetMonth(&IntValue);
			Assert::AreEqual(6, IntValue);
			DatetimeValue.GetYear(&IntValue);
			Assert::AreEqual(2012, IntValue);
			Assert::IsFalse(Reader->IsDBNull(8));
			Assert::IsTrue(Reader->IsDBNull(9));

			// datetime2
			Reader->GetDateTime(10, &DatetimeValue);
			DatetimeValue.GetDay(&IntValue);
			Assert::AreEqual(18, IntValue);
			DatetimeValue.GetMonth(&IntValue);
			Assert::AreEqual(6, IntValue);
			DatetimeValue.GetYear(&IntValue);
			Assert::AreEqual(2012, IntValue);
			DatetimeValue.GetHour(&IntValue);
			Assert::AreEqual(22, IntValue);
			DatetimeValue.GetMinute(&IntValue);
			Assert::AreEqual(34, IntValue);
			DatetimeValue.GetSecond(&IntValue);
			Assert::AreEqual(9, IntValue);
			Assert::IsFalse(Reader->IsDBNull(10));
			Assert::IsTrue(Reader->IsDBNull(11));

			// datetime
			Reader->GetDateTime(12, &DatetimeValue);
			DatetimeValue.GetDay(&IntValue);
			Assert::AreEqual(18, IntValue);
			DatetimeValue.GetMonth(&IntValue);
			Assert::AreEqual(6, IntValue);
			DatetimeValue.GetYear(&IntValue);
			Assert::AreEqual(2012, IntValue);
			DatetimeValue.GetHour(&IntValue);
			Assert::AreEqual(22, IntValue);
			DatetimeValue.GetMinute(&IntValue);
			Assert::AreEqual(34, IntValue);
			DatetimeValue.GetSecond(&IntValue);
			Assert::AreEqual(9, IntValue);
			Assert::IsFalse(Reader->IsDBNull(12));
			Assert::IsTrue(Reader->IsDBNull(13));

			// datetimeoffset
			Reader->GetDateTimeOffset(14, &DateTimeOffsetValue);
			DateTimeOffsetValue.GetDateTime().GetDay(&IntValue);
			Assert::AreEqual(10, IntValue);
			DateTimeOffsetValue.GetDateTime().GetMonth(&IntValue);
			Assert::AreEqual(12, IntValue);
			DateTimeOffsetValue.GetDateTime().GetYear(&IntValue);
			Assert::AreEqual(2025, IntValue);
			DateTimeOffsetValue.GetDateTime().GetHour(&IntValue);
			Assert::AreEqual(12, IntValue);
			DateTimeOffsetValue.GetDateTime().GetMinute(&IntValue);
			Assert::AreEqual(32, IntValue);
			DateTimeOffsetValue.GetDateTime().GetSecond(&IntValue);
			Assert::AreEqual(10, IntValue);
			Assert::AreEqual(1, DateTimeOffsetValue.GetOffset().GetHours());
			Assert::AreEqual(0, DateTimeOffsetValue.GetOffset().GetMinutes());
			Assert::AreEqual(0, DateTimeOffsetValue.GetOffset().GetSeconds());
			Assert::IsFalse(Reader->IsDBNull(14));
			Assert::IsTrue(Reader->IsDBNull(15));

			// decimal
			Reader->GetDecimal(16, &DecimalValue);
			Assert::AreEqual((__int64)1, *DecimalValue.GetHighPart());
			Assert::AreEqual((__int64)0, *DecimalValue.GetLowPart());
			Assert::IsFalse(Reader->IsDBNull(16));
			Assert::IsTrue(Reader->IsDBNull(17));

			// float
			Reader->GetFloat(18, &FloatValue);
			Assert::AreEqual(0.27f, FloatValue);
			/*
			Reader->GetDouble(18, &DoubleValue);
			Assert::AreEqual(0.27, DoubleValue);
			*/
			Assert::IsFalse(Reader->IsDBNull(18));
			Assert::IsTrue(Reader->IsDBNull(19));

			// geography
			AvailableBytes = Reader->GetBytes(20, 0, nullptr, 0, 0);
			BytesValue.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetBytes(20, 0, BytesValue.data(), 0, BytesValue.capacity());
			// ToDo: test somehow or create specific type?
			Assert::IsFalse(Reader->IsDBNull(20));
			Assert::IsTrue(Reader->IsDBNull(21));
			Reader->GetFloat(22, &FloatValue);	// Latitude
			Assert::AreEqual(47.651f, FloatValue);
			Reader->GetDouble(22, &DoubleValue);	// Latitude
			Assert::AreEqual(47.651, DoubleValue);
			Reader->GetDouble(23, &DoubleValue);	// Longitude
			Assert::AreEqual(-122.349, DoubleValue);
			Reader->GetDouble(24, &DoubleValue);	// Magnitude
			Assert::AreEqual(0.0, DoubleValue);
			Reader->GetDouble(25, &DoubleValue);	// Depth
			Assert::AreEqual(0.0, DoubleValue);

			// geometry
			AvailableBytes = Reader->GetBytes(26, 0, nullptr, 0, 0);
			BytesValue.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetBytes(26, 0, BytesValue.data(), 0, BytesValue.capacity());
			AvailableBytes = Reader->GetChars(26, 0, nullptr, 0, 0);
			CharValues.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetChars(26, 0, CharValues.data(), 0, CharValues.capacity());
			// ToDo: test somehow or create specific type?
			Assert::IsFalse(Reader->IsDBNull(26));
			Assert::IsTrue(Reader->IsDBNull(27));

			// hierarchyid
			AvailableBytes = Reader->GetBytes(28, 0, nullptr, 0, 0);	// ToDo: why do we get zero bytes?
			//BytesValue.resize(AvailableBytes);
			//AvailableBytes = Reader->GetBytes(28, 0, BytesValue.data(), 0, 2048);
			Assert::IsFalse(Reader->IsDBNull(28));
			Assert::IsTrue(Reader->IsDBNull(29));
			AvailableBytes = Reader->GetWChars(30, 0, nullptr, 0, 0);	// HierarchyPath
			WCharValues.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetWChars(30, 0, WCharValues.data(), 0, (size_t)AvailableBytes);	// HierarchyPath
			Assert::AreEqual(L'/', WCharValues[0]);
			Reader->GetInt16(31, &Int16Value);	// HierarchyLevel
			Assert::AreEqual((int16_t)0, Int16Value);

			// image
			AvailableBytes = Reader->GetBytes(32, 0, nullptr, 0, 0);
			BytesValue.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetBytes(32, 0, BytesValue.data(), 0, (size_t)AvailableBytes);
			Assert::IsFalse(Reader->IsDBNull(32));
			Assert::IsTrue(Reader->IsDBNull(33));

			// int
			Reader->GetInt32(34, &IntValue);
			Assert::AreEqual(23, IntValue);
			Assert::IsFalse(Reader->IsDBNull(34));
			Assert::IsTrue(Reader->IsDBNull(35));

			// money
			Reader->GetDouble(36, &DoubleValue);
			Assert::AreEqual(37.56, DoubleValue);
			Reader->GetFloat(36, &FloatValue);
			Assert::AreEqual(37.56f, FloatValue);
			Assert::IsFalse(Reader->IsDBNull(36));
			Assert::IsTrue(Reader->IsDBNull(37));

			// nchar
			Reader->GetWChar(38, WCharValues.data());
			Assert::AreEqual(L'n', WCharValues.data()[0]);
			AvailableBytes = Reader->GetWChars(38, 0, nullptr, 0, 0);
			WCharValues.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetWChars(38, 0, WCharValues.data(), 0, (size_t)AvailableBytes);
			Assert::AreEqual(L'n', WCharValues.data()[0]);
			Assert::IsFalse(Reader->IsDBNull(38));
			Assert::IsTrue(Reader->IsDBNull(39));

			// ntext
			AvailableBytes = Reader->GetWChars(40, 0, nullptr, 0, 0);
			WCharValues.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetWChars(40, 0, WCharValues.data(), 0, (size_t)AvailableBytes);
			Assert::AreEqual(L't', WCharValues.data()[0]);
			Assert::IsFalse(Reader->IsDBNull(40));
			Assert::IsTrue(Reader->IsDBNull(41));

			// numeric
			Reader->GetDecimal(42, &DecimalValue);
			Assert::AreEqual((__int64)99, *DecimalValue.GetHighPart());
			Assert::AreEqual((__int64)0, *DecimalValue.GetLowPart());
			Assert::IsFalse(Reader->IsDBNull(42));
			Assert::IsTrue(Reader->IsDBNull(43));

			// nvarchar
			AvailableBytes = Reader->GetWChars(44, 0, nullptr, 0, 0);
			WCharValues.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetWChars(44, 0, WCharValues.data(), 0, (size_t)AvailableBytes);
			Assert::AreEqual(L'n', WCharValues.data()[0]);
			Assert::IsFalse(Reader->IsDBNull(44));
			Assert::IsTrue(Reader->IsDBNull(45));

			// real
			Reader->GetFloat(46, &FloatValue);
			Assert::AreEqual(23.559999465942383f, FloatValue);
			Reader->GetDouble(46, &DoubleValue);
			Assert::AreEqual(23.559999465942383, DoubleValue);
			Assert::IsFalse(Reader->IsDBNull(46));
			Assert::IsTrue(Reader->IsDBNull(47));

			// smalldatetime
			Reader->GetDateTime(48, &DatetimeValue);
			DatetimeValue.GetDay(&IntValue);
			Assert::AreEqual(10, IntValue);
			DatetimeValue.GetMonth(&IntValue);
			Assert::AreEqual(2, IntValue);
			DatetimeValue.GetYear(&IntValue);
			Assert::AreEqual(2010, IntValue);
			DatetimeValue.GetHour(&IntValue);
			Assert::AreEqual(12, IntValue);
			DatetimeValue.GetMinute(&IntValue);
			Assert::AreEqual(30, IntValue);
			DatetimeValue.GetSecond(&IntValue);
			Assert::AreEqual(0, IntValue);
			Assert::IsFalse(Reader->IsDBNull(48));
			Assert::IsTrue(Reader->IsDBNull(49));

			// smallint
			Reader->GetInt16(50, &Int16Value);
			Assert::AreEqual((short)23, Int16Value);
			Assert::IsFalse(Reader->IsDBNull(50));
			Assert::IsTrue(Reader->IsDBNull(51));

			// smallmoney
			Reader->GetFloat(52, &FloatValue);
			Assert::AreEqual(75.45f, FloatValue);
			Reader->GetDouble(52, &DoubleValue);
			Assert::AreEqual(75.45, DoubleValue);
			Assert::IsFalse(Reader->IsDBNull(52));
			Assert::IsTrue(Reader->IsDBNull(53));

			// sql_variant
			AvailableBytes = Reader->GetBytes(54, 0, nullptr, 0, 0);	// ToDo: why do we get zero bytes?
			//BytesValue.resize(AvailableBytes);
			//AvailableBytes = Reader->GetBytes(54, 0, BytesValue.data(), 0, AvailableBytes); // ToDo: test somehow or create specific type?
			Assert::IsFalse(Reader->IsDBNull(54));
			Assert::IsTrue(Reader->IsDBNull(55));

			// sysname
			AvailableBytes = Reader->GetWChars(56, 0, nullptr, 0, 0);
			WCharValues.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetWChars(56, 0, WCharValues.data(), 0, (size_t)AvailableBytes);
			Assert::AreEqual(L's', WCharValues.data()[0]);
			Assert::IsFalse(Reader->IsDBNull(56));
			Assert::IsTrue(Reader->IsDBNull(57));

			// text
			AvailableBytes = Reader->GetChars(58, 0, nullptr, 0, 0);
			CharValues.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetChars(58, 0, CharValues.data(), 0, (size_t)AvailableBytes);
			Assert::AreEqual('s', CharValues.data()[0]);
			Assert::IsFalse(Reader->IsDBNull(58));
			Assert::IsTrue(Reader->IsDBNull(59));

			// time
			Reader->GetTimeSpan(60, &TimeSpanValue);
			Assert::AreEqual(13, TimeSpanValue.GetHours());
			Assert::AreEqual(37, TimeSpanValue.GetMinutes());
			Assert::AreEqual(27, TimeSpanValue.GetSeconds());

			Reader->GetDateTime(60, &DatetimeValue);
			DatetimeValue.GetDay(&IntValue);
			Assert::AreEqual(1, IntValue);
			DatetimeValue.GetMonth(&IntValue);
			Assert::AreEqual(1, IntValue);
			DatetimeValue.GetYear(&IntValue);
			Assert::AreEqual(1, IntValue);
			DatetimeValue.GetHour(&IntValue);
			Assert::AreEqual(13, IntValue);
			DatetimeValue.GetMinute(&IntValue);
			Assert::AreEqual(37, IntValue);
			DatetimeValue.GetSecond(&IntValue);
			Assert::AreEqual(27, IntValue);
			Assert::IsFalse(Reader->IsDBNull(60));
			Assert::IsTrue(Reader->IsDBNull(61));

			// timestamp - this datatype equals a 'rowversion' and doesn't contain DateTime-information as the name might imply
			Reader->GetInt64(62, &BigIntValue);
			//Assert::AreEqual(-3384736594945638400, BigIntValue);	// ToDo: different value for each row each time
			Assert::IsFalse(Reader->IsDBNull(62));

			// tinyint
			Reader->GetInt16(63, &Int16Value);
			Assert::AreEqual((short)17, Int16Value);
			Assert::IsFalse(Reader->IsDBNull(63));
			Assert::IsTrue(Reader->IsDBNull(64));

			// GUID (uniqueidentifier)
			Reader->GetGuid(65, &GUIDValue);
			//Assert::AreEqual("ae019609-99e0-4ef5-85bb-ad90dc302e70", GUIDValue.ToString().c_str());
			Assert::IsFalse(Reader->IsDBNull(65));
			Assert::IsTrue(Reader->IsDBNull(66));

			// varbinary
			AvailableBytes = Reader->GetBytes(67, 0, nullptr, 0, 0);	// ToDo: why do we get zero bytes? (same as sql_variant)
			//BytesValue.resize(AvailableBytes);
			//AvailableBytes = Reader->GetBytes(54, 0, BytesValue.data(), 0, AvailableBytes); // ToDo: test somehow or create specific type?
			Assert::IsFalse(Reader->IsDBNull(67));
			Assert::IsTrue(Reader->IsDBNull(68));

			// vchar 
			AvailableBytes = Reader->GetChars(69, 0, nullptr, 0, 0);
			CharValues.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetChars(69, 0, CharValues.data(), 0, (size_t)AvailableBytes);
			Assert::AreEqual('v', CharValues.data()[0]);
			Assert::IsFalse(Reader->IsDBNull(69));
			Assert::IsTrue(Reader->IsDBNull(70));

			// xml
			AvailableBytes = Reader->GetWChars(71, 0, nullptr, 0, 0);
			WCharValues.resize((unsigned int)AvailableBytes);
			AvailableBytes = Reader->GetWChars(71, 0, WCharValues.data(), 0, (size_t)AvailableBytes);
			//Assert::AreEqual(L"<root\>", WCharValues.data());	// ToDo: encoding-problematic?
			Assert::IsFalse(Reader->IsDBNull(71));
			Assert::IsTrue(Reader->IsDBNull(72));
		}

		Reader->Close();
	}
	static void LogSqlNativeException(SqlNativeException& ex)
	{
		Logger::WriteMessage(ex.GetExceptionMessage().GetCharArray());
		Logger::WriteMessage(std::to_string(ex.GetErrorCode()).c_str());
		for (unsigned int i = 0; i < ex.GetErrors().GetCount(); i++)
		{
			SqlNativeError Error = ex.GetErrors()[i];
			Logger::WriteMessage(("\tErrorSpecificErrorCode: " + std::to_string(Error.GetErrorSpecificErrorCode())).c_str());
			Logger::WriteMessage(("\tProviderSpecificErrorCode: " + std::to_string(Error.GetProviderSpecificErrorCode())).c_str());
			//Logger::WriteMessage(("\tClassId: " + std::to_string(Error.GetClassId())).c_str());
			//Logger::WriteMessage(("\tInterfaceId: " + std::to_string(Error.GetInterfaceId())).c_str());
			Logger::WriteMessage(("\tDisplayId: " + std::to_string(Error.GetDisplayId())).c_str());

			//Logger::WriteMessage(("\tDescription: " + std::to_string(Error.GetDescription())).c_str());
			//Logger::WriteMessage(("\tGUID: " + std::to_string(Error.GetGUID())).c_str());
			Logger::WriteMessage(("\tHelpContext: " + std::to_string(Error.GetHelpContext())).c_str());
			Logger::WriteMessage((L"\tHelpFile: " + Error.GetHelpFile()).c_str());
			Logger::WriteMessage((L"\tSource: " + Error.GetSource()).c_str());

			Logger::WriteMessage((L"\tSqlState: " + Error.GetSqlState()).c_str());
			Logger::WriteMessage(("\tErrorCode: " + std::to_string(Error.GetErrorCode())).c_str());
			Logger::WriteMessage((L"\tSSError: " + Error.GetSSError()).c_str());
			Logger::WriteMessage((L"\tServer: " + Error.GetServer()).c_str());
			Logger::WriteMessage((L"\tProcedure: " + Error.GetProcedure()).c_str());
			Logger::WriteMessage(("\tNumber: " + std::to_string(Error.GetNumber())).c_str());
			Logger::WriteMessage(("\tState: " + std::to_string(Error.GetState())).c_str());
			Logger::WriteMessage(("\tErrorSeverity: " + std::to_string(Error.GetErrorSeverity())).c_str());
			Logger::WriteMessage(("\tLineNumber: " + std::to_string(Error.GetLineNumber())).c_str());

			Logger::WriteMessage("\t---");
		}
	}
	};
}
