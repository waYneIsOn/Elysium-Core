#include "CppUnitTest.h"
#include "CppUnitTestFrameworkExtension.hpp"

#include "DatabaseTestBase.hpp"

#include "../../../Libraries/01-Shared/Elysium.Core/List.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Data/DbDataReader.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Data.SqlNativeClient.OleDB/SqlNativeConnection.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Data.SqlNativeClient.OleDB/SqlNativeException.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.IO/MemoryStream.hpp"
#include "../../../Libraries/01-Shared/Elysium.Core.Text/StringBuilder.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Core::Data::Common;
using namespace Elysium::Core::Data::SqlNativeClient::OleDb;
using namespace Elysium::Core::Text;

#define STRINGIFY(x) u8#x
#define EXPAND(x) STRINGIFY(x)

namespace UnitTests::Core::Data::SqlNativeClient
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
				Connection.SetConnectionString(u8"Driver={SQL Server Native Client 11.0};Application Name=Elysium Framework;Server=localhost;Database=master;Trusted_Connection=Yes;");
				Connection.Open();

				// make sure the test database doesn't exist
				try
				{
					Template::Memory::UniquePointer<IDbCommand> DropDatabaseCommand = Connection.CreateCommand();
					DropDatabaseCommand->SetCommandText(u8"DROP DATABASE IF EXISTS Test");
					Elysium::Core::size Result = DropDatabaseCommand->ExecuteNonQuery();
				}
				catch (SqlNativeException&)
				{
					// we don't care about any errors here
				}

				// create test database
				Template::Memory::UniquePointer<IDbCommand> CreateDatabaseCommand = Connection.CreateCommand();
				CreateDatabaseCommand->SetCommandText(u8"If(db_id(N'Test') IS NULL) CREATE DATABASE Test ON (NAME = Test_dat, FILENAME = 'C:\\Program Files\\Microsoft SQL Server\\MSSQL14.MSSQLSERVER\\MSSQL\\DATA\\Test.mdf', SIZE = 10, MAXSIZE = 500, FILEGROWTH = 5) LOG ON (NAME = Test_log, FILENAME = 'C:\\Program Files\\Microsoft SQL Server\\MSSQL14.MSSQLSERVER\\MSSQL\\DATA\\Test.ldf', SIZE = 5MB, MAXSIZE = 250MB, FILEGROWTH = 5MB)");
				Elysium::Core::size Result = CreateDatabaseCommand->ExecuteNonQuery();

				// create the test table that we will be using
				Template::Memory::UniquePointer<IDbCommand> CreateTableCommand = Connection.CreateCommand();
				CreateTableCommand->SetCommandText(u8"USE Test; CREATE TABLE AllDataTypes ([bigintNotNull][bigint] NOT NULL, [bigintNull][bigint] NULL, [binaryNotNull][binary] NOT NULL, [binaryNull][binary] NULL, [bitNotNull][bit] NOT NULL, [bitNull][bit] NULL, [charNotNull][char] NOT NULL, [charNull][char] NULL, [dateNotNull][date] NOT NULL, [dateNull][date] NULL, [datetime2NotNull][datetime2] NOT NULL, [datetime2Null][datetime2] NULL, [datetimeNotNull][datetime] NOT NULL, [datetimeNull][datetime] NULL, [datetimeoffsetNotNull][datetimeoffset] NOT NULL, [datetimeoffsetNull][datetimeoffset] NULL, [decimalNotNull][decimal] NOT NULL, [decimalNull][decimal] NULL, [floatNotNull][float] NOT NULL, [floatNull][float] NULL, [geographyNotNull][geography] NOT NULL, [geographyNull][geography] NULL, [geometryNotNull][geometry] NOT NULL, [geometryNull][geometry] NULL, [hierarchyidNotNull][hierarchyid] NOT NULL, [hierarchyidNull][hierarchyid] NULL, [imageNotNull][image] NOT NULL, [imageNull][image] NULL, [intNotNull][int] NOT NULL, [intNull][int] NULL, [moneyNotNull][money] NOT NULL, [moneyNull][money] NULL, [ncharNotNull][nchar] NOT NULL, [ncharNull][nchar] NULL, [ntextNotNull][ntext] NOT NULL, [ntextNull][ntext] NULL, [numericNotNull][numeric] NOT NULL, [numericNull][numeric] NULL, [nvarcharNotNull][nvarchar] NOT NULL, [nvarcharNull][nvarchar] NULL, [realNotNull][real] NOT NULL, [realNull][real] NULL, [smalldatetimeNotNull][smalldatetime] NOT NULL, [smalldatetimeNull][smalldatetime] NULL, [smallintNotNull][smallint] NOT NULL, [smallintNull][smallint] NULL, [smallmoneyNotNull][smallmoney] NOT NULL, [smallmoneyNull][smallmoney] NULL, [sql_variantNotNull][sql_variant] NOT NULL, [sql_variantNull][sql_variant] NULL, [sysnameNotNull][sysname] NOT NULL, [sysnameNull][sysname] NULL, [textNotNull][text] NOT NULL, [textNull][text] NULL, [timeNotNull][time] NOT NULL, [timeNull][time] NULL, [timestampNotNull][timestamp] NOT NULL, [tinyintNotNull][tinyint] NOT NULL, [tinyintNull][tinyint] NULL, [uniqueidentifierNotNull][uniqueidentifier] NOT NULL, [uniqueidentifierNull][uniqueidentifier] NULL, [varbinaryNotNull][varbinary] NOT NULL, [varbinaryNull][varbinary] NULL, [varcharNotNull][varchar] NOT NULL, [varcharNull][varchar] NULL, [xmlNotNull][xml] NOT NULL, [xmlNull][xml] NULL)");
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
				Connection.SetConnectionString(u8"Driver={SQL Server Native Client 11.0};Application Name=Elysium Framework;Server=localhost;Database=master;Trusted_Connection=Yes;");
				Connection.Open();

				// delete test database
				Template::Memory::UniquePointer<IDbCommand> DropDatabaseCommand = Connection.CreateCommand();
				DropDatabaseCommand->SetCommandText(u8"DROP DATABASE IF EXISTS Test");
				Elysium::Core::size Result = DropDatabaseCommand->ExecuteNonQuery();

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
			_Connection.SetConnectionString(u8"Driver={SQL Server Native Client 11.0};Application Name=Elysium Framework;Server=localhost;Database=ElysiumTest;Trusted_Connection=Yes;");
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
			_Connection.ChangeDatabase(u8"Test");
			try
			{
				_Connection.ChangeDatabase(u8"NonExistantDatabase");
				Assert::Fail();
			}
			catch (Exception&)
			{
			}

			_Connection.ChangeDatabase(u8"master");
			_Connection.Close();
		}

		TEST_METHOD(CRUDWithoutParameters)
		{
			try
			{
				// get the project path so we can get the FQPN to the test-image
				String ProjectPath = EXPAND(UNITTESTPRJ);
				ProjectPath = ProjectPath.Substring(1, ProjectPath.GetLength() - 3); // no need for the first as well as the last quote and the dot
				//ProjectPath.erase(0, 1); // erase the first quote
				//ProjectPath.erase(ProjectPath.GetLength() - 2); // erase the last quote and the dot

				_Connection.Open();

				// perform C test
				StringBuilder Builder = StringBuilder();
				Builder.Append(u8"SET ANSI_WARNINGS OFF; USE Test; INSERT INTO AllDataTypes ([bigintNotNull], [bigintNull], [binaryNotNull], [binaryNull], [bitNotNull], [bitNull], [charNotNull], [charNull], [dateNotNull], [dateNull], [datetime2NotNull], [datetime2Null], [datetimeNotNull], [datetimeNull], [datetimeoffsetNotNull], [datetimeoffsetNull], [decimalNotNull], [decimalNull], [floatNotNull], [floatNull], [geographyNotNull], [geographyNull], [geometryNotNull], [geometryNull], [hierarchyidNotNull], [hierarchyidNull], [imageNotNull], [imageNull], [intNotNull], [intNull], [moneyNotNull], [moneyNull], [ncharNotNull], [ncharNull], [ntextNotNull], [ntextNull], [numericNotNull], [numericNull], [nvarcharNotNull], [nvarcharNull], [realNotNull], [realNull], [smalldatetimeNotNull], [smalldatetimeNull], [smallintNotNull], [smallintNull], [smallmoneyNotNull], [smallmoneyNull], [sql_variantNotNull], [sql_variantNull], [sysnameNotNull], [sysnameNull], [textNotNull], [textNull], [timeNotNull], [timeNull], [timestampNotNull], [tinyintNotNull], [tinyintNull], [uniqueidentifierNotNull], [uniqueidentifierNull], [varbinaryNotNull], [varbinaryNull], [varcharNotNull], [varcharNull], [xmlNotNull], [xmlNull]) VALUES (9223372036854775807, NULL, CONVERT(varbinary(9), N'varbinary'), NULL, 1, NULL, 'a', NULL, CONVERT(date, '18-06-12', 5), NULL, CONVERT(datetime2,'18-06-12 10:34:09 PM', 5), NULL, CONVERT(datetime,'18-06-12 10:34:09 PM', 5), NULL, CONVERT(datetimeoffset,'12-10-25 12:32:10 +01:00'), NULL, 1.35, NULL, 0.27, NULL, geography::Point(47.65100, -122.34900, 4326), NULL, geometry::STGeomFromText('POINT (22.9901232886963 87.5953903123242)', 4326), NULL, HierarchyID::GetRoot(), NULL, (SELECT * FROM OPENROWSET(BULK N'");
				Builder.Append(ProjectPath);
				Builder.Append(u8"\\TestImage.png', SINGLE_BLOB) AS Image), NULL, 23, NULL, 37.56, NULL, N'n', NULL, N't', NULL, 99.1, NULL, N'n', NULL, 23.56, NULL, '02/10/2010 12:30', NULL, 23, NULL, 75.45, NULL, 'v', NULL, N's', NULL, 's', NULL, '13:37:27', NULL, DEFAULT, 17, NULL, CONVERT(uniqueidentifier, 'AE019609-99E0-4EF5-85BB-AD90DC302E70'), NULL, CAST('wahid' AS VARBINARY(5)), NULL, 'v', NULL, CONVERT(XML, N'<?xml version=\"1.0\" encoding=\"UTF-16\"?><root/>'), NULL)");
				String Command = Builder.ToString();
				Template::Memory::UniquePointer<IDbCommand> InsertCommand = _Connection.CreateCommand();
				InsertCommand->SetCommandText(Command);
				PerformDataInsertionTest(InsertCommand.GetUnderlyingPointer());

				// perform R test
				Template::Memory::UniquePointer<IDbCommand> SelectCommand = _Connection.CreateCommand();
				SelectCommand->SetCommandText(u8"SELECT [bigintNotNull], [bigintNull], [binaryNotNull], [binaryNull], [bitNotNull], [bitNull], [charNotNull], [charNull], [dateNotNull], [dateNull], [datetime2NotNull], [datetime2Null], [datetimeNotNull], [datetimeNull], [datetimeoffsetNotNull], [datetimeoffsetNull], [decimalNotNull], [decimalNull], [floatNotNull], [floatNull], [geographyNotNull], [geographyNull], [geographyNotNull].Lat As Latitude, [geographyNotNull].Long As Longitude, [geographyNotNull].M As Magnitude, [geographyNotNull].Z As Depth, [geometryNotNull], [geometryNull], [hierarchyidNotNull], [hierarchyidNull], [hierarchyidNotNull].ToString() AS HierarchyPath, [hierarchyidNotNull].GetLevel() AS HierarchyLevel, [imageNotNull], [imageNull], [intNotNull], [intNull], [moneyNotNull], [moneyNull], [ncharNotNull], [ncharNull], [ntextNotNull], [ntextNull], [numericNotNull], [numericNull], [nvarcharNotNull], [nvarcharNull], [realNotNull], [realNull], [smalldatetimeNotNull], [smalldatetimeNull], [smallintNotNull], [smallintNull], [smallmoneyNotNull], [smallmoneyNull], [sql_variantNotNull], [sql_variantNull], [sysnameNotNull], [sysnameNull], [textNotNull], [textNull], [timeNotNull], [timeNull], [timestampNotNull], [tinyintNotNull], [tinyintNull], [uniqueidentifierNotNull], [uniqueidentifierNull], [varbinaryNotNull], [varbinaryNull], [varcharNotNull], [varcharNull], [xmlNotNull], [xmlNull] FROM AllDataTypes");
				TestReader(SelectCommand);

				// perform U test
				Template::Memory::UniquePointer<IDbCommand> UpdateCommand = _Connection.CreateCommand();
				UpdateCommand->SetCommandText(u8"UPDATE AllDataTypes SET [bigintNull] = 123");
				UpdateCommand->ExecuteNonQuery();

				// perform D test
				Template::Memory::UniquePointer<IDbCommand> DeleteCommand = _Connection.CreateCommand();
				DeleteCommand->SetCommandText(u8"DELETE FROM AllDataTypes");
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
				//Logger::WriteMessage(ex.GetExceptionMessage().GetCharArray());
				Assert::Fail();
			}
		}

		TEST_METHOD(CRUDWithUnnamedParameters)
		{
			try
			{
				// get the project path so we can get the FQPN to the test-image
				String ProjectPath = EXPAND(UNITTESTPRJ);
				ProjectPath = ProjectPath.Substring(1, ProjectPath.GetLength() - 3); // no need for the first as well as the last quote and the dot
				//ProjectPath.erase(0, 1); // erase the first quote
				//ProjectPath.erase(ProjectPath.size() - 2); // erase the last quote and the dot

				_Connection.Open();

				// perform C test
				Template::Memory::UniquePointer<IDbCommand> InsertCommand = _Connection.CreateCommand();
				InsertCommand->SetCommandText(u8"SET ANSI_WARNINGS OFF; USE Test; INSERT INTO AllDataTypes ([bigintNotNull], [bigintNull], [binaryNotNull], [binaryNull], [bitNotNull], [bitNull], [charNotNull], [charNull], [dateNotNull], [dateNull], [datetime2NotNull], [datetime2Null], [datetimeNotNull], [datetimeNull], [datetimeoffsetNotNull], [datetimeoffsetNull], [decimalNotNull], [decimalNull], [floatNotNull], [floatNull], [geographyNotNull], [geographyNull], [geometryNotNull], [geometryNull], [hierarchyidNotNull], [hierarchyidNull], [imageNotNull], [imageNull], [intNotNull], [intNull], [moneyNotNull], [moneyNull], [ncharNotNull], [ncharNull], [ntextNotNull], [ntextNull], [numericNotNull], [numericNull], [nvarcharNotNull], [nvarcharNull], [realNotNull], [realNull], [smalldatetimeNotNull], [smalldatetimeNull], [smallintNotNull], [smallintNull], [smallmoneyNotNull], [smallmoneyNull], [sql_variantNotNull], [sql_variantNull], [sysnameNotNull], [sysnameNull], [textNotNull], [textNull], [timeNotNull], [timeNull], [timestampNotNull], [tinyintNotNull], [tinyintNull], [uniqueidentifierNotNull], [uniqueidentifierNull], [varbinaryNotNull], [varbinaryNull], [varcharNotNull], [varcharNull], [xmlNotNull], [xmlNull]) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 1.35, NULL, ?, ?, geography::Point(47.65100, -122.34900, 4326), NULL, geometry::STGeomFromText('POINT (22.9901232886963 87.5953903123242)', 4326), NULL, HierarchyID::GetRoot(), NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 99.1, NULL, ?, ?, ?, ?, '02/10/2010 12:30', NULL, ?, ?, ?, ?, 'v', NULL, ?, ?, 's', NULL, ?, ?, DEFAULT, ?, ?, ?, ?, CAST('wahid' AS VARBINARY(5)), NULL, 'v', NULL, ?, ?)");

				IDataParameterCollection& col = InsertCommand->GetParameters();

				// __int64 (bigint)
				Template::Memory::UniquePointer<IDataParameter> Int64Parameter = InsertCommand->CreateParameter();
				Int64Parameter->SetValue(9223372036854775807);
				InsertCommand->GetParameters().Add(*Int64Parameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> Int64NullParameter = InsertCommand->CreateParameter();
				Int64NullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*Int64NullParameter.GetUnderlyingPointer());

				// BYTE (binary)
				Template::Memory::UniquePointer<IDataParameter> ByteParameter = InsertCommand->CreateParameter();
				ByteParameter->SetValue((BYTE)'v');	//0x76
				InsertCommand->GetParameters().Add(*ByteParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> ByteNullParameter = InsertCommand->CreateParameter();
				ByteNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*ByteNullParameter.GetUnderlyingPointer());

				// bool (bit)
				Template::Memory::UniquePointer<IDataParameter> BoolParameter = InsertCommand->CreateParameter();
				BoolParameter->SetValue(true);
				InsertCommand->GetParameters().Add(*BoolParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> BoolNullParameter = InsertCommand->CreateParameter();
				BoolNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*BoolNullParameter.GetUnderlyingPointer());

				// char (option 1)
				/*
				std::unique_ptr<IDataParameter> CharParameter = InsertCommand->CreateParameter();
				CharParameter->SetValue('a');
				InsertCommand->GetParameters().Add(CharParameter.get());

				std::unique_ptr<IDataParameter> CharNullParameter = InsertCommand->CreateParameter();
				CharNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters().Add(CharNullParameter.get());
				*/
				// char (option 2)
				/*
				std::unique_ptr<IDataParameter> StringParameter = InsertCommand->CreateParameter();
				StringParameter->SetValue(&std::string("a - mssql will trim automatically"));
				InsertCommand->GetParameters().Add(StringParameter.get());

				std::unique_ptr<IDataParameter> StringNullParameter = InsertCommand->CreateParameter();
				StringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters().Add(StringNullParameter.get());
				*/
				// char (option 3)
				Elysium::Core::IO::MemoryStream StringStream;
				StringStream.Write((const BYTE*)"a - mssql won't trim automatically so set the length correctly!!!!", 1);
				StringStream.SetPosition(0);

				Template::Memory::UniquePointer<IDataParameter> StreamedStringParameter = InsertCommand->CreateParameter();
				StreamedStringParameter->SetValue(&StringStream);
				InsertCommand->GetParameters().Add(*StreamedStringParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> StreamedStringNullParameter = InsertCommand->CreateParameter();
				StreamedStringNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*StreamedStringNullParameter.GetUnderlyingPointer());

				// DateTime (date)
				Template::Memory::UniquePointer<IDataParameter> DateParameter = InsertCommand->CreateParameter();
				DateParameter->SetValue(DateTime(2012, 06, 18));
				DateParameter->SetDbType(DbType::Date);
				InsertCommand->GetParameters().Add(*DateParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> DateNullParameter = InsertCommand->CreateParameter();
				DateNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*DateNullParameter.GetUnderlyingPointer());

				// DateTime (datetime2)
				Template::Memory::UniquePointer<IDataParameter> DateTime2Parameter = InsertCommand->CreateParameter();
				DateTime2Parameter->SetValue(DateTime(2012, 06, 18, 22, 34, 9));
				DateTime2Parameter->SetDbType(DbType::DateTime2);
				InsertCommand->GetParameters().Add(*DateTime2Parameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> DateTime2NullParameter = InsertCommand->CreateParameter();
				DateTime2NullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*DateTime2NullParameter.GetUnderlyingPointer());

				// DateTime (datetime)
				Template::Memory::UniquePointer<IDataParameter> DateTimeParameter = InsertCommand->CreateParameter();
				DateTimeParameter->SetValue(DateTime(2012, 06, 18, 22, 34, 9));
				DateTimeParameter->SetDbType(DbType::DateTime);
				InsertCommand->GetParameters().Add(*DateTimeParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> DateTimeNullParameter = InsertCommand->CreateParameter();
				DateTimeNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*DateTimeNullParameter.GetUnderlyingPointer());

				// DateTimeOffset (datetimeoffset)
				Template::Memory::UniquePointer<IDataParameter> DateTimeOffsetParameter = InsertCommand->CreateParameter();
				DateTimeOffsetParameter->SetValue(DateTimeOffset(DateTime(2025, 12, 10, 12, 32, 10), TimeSpan::FromHours(1.0)));
				InsertCommand->GetParameters().Add(*DateTimeOffsetParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> DateTimeOffsetNullParameter = InsertCommand->CreateParameter();
				DateTimeOffsetNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*DateTimeOffsetNullParameter.GetUnderlyingPointer());
				/*
				// decimal
				decimal DecimalValue;
				DecimalValue.LowPart = (__int64)1;
				DecimalValue.HighPart = (__int64)35;

				std::unique_ptr<IDataParameter> DecimalParameter = InsertCommand->CreateParameter();
				DecimalParameter->SetValue(&DecimalValue);
				InsertCommand->GetParameters().Add(DecimalParameter.get());

				std::unique_ptr<IDataParameter> DecimalNullParameter = InsertCommand->CreateParameter();
				DecimalNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters().Add(DecimalNullParameter.get());
				*/
				// float
				Template::Memory::UniquePointer<IDataParameter> SingleParameter = InsertCommand->CreateParameter();
				SingleParameter->SetValue(0.27f);
				InsertCommand->GetParameters().Add(*SingleParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> SingleNullParameter = InsertCommand->CreateParameter();
				SingleNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*SingleNullParameter.GetUnderlyingPointer());

				// geography - ToDo: mssql specific type

				// geometry - ToDo: mssql specific type

				// hierarchyid - ToDo: mssql specific type

				// image
				StringBuilder Builder = StringBuilder();
				Builder.Append(ProjectPath);
				Builder.Append(u8"\\TestImage.png");
				String ImagePath = Builder.ToString();
				Elysium::Core::IO::FileStream ImageStream(ImagePath, Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read, Elysium::Core::IO::FileShare::Read);
				Template::Memory::UniquePointer<IDataParameter> ImageParameter = InsertCommand->CreateParameter();
				ImageParameter->SetValue(&ImageStream);
				InsertCommand->GetParameters().Add(*ImageParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> ImageNullParameter = InsertCommand->CreateParameter();
				ImageNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*ImageNullParameter.GetUnderlyingPointer());

				// __int32 (int)
				Template::Memory::UniquePointer<IDataParameter> Int32Parameter = InsertCommand->CreateParameter();
				Int32Parameter->SetValue((__int32)23);
				InsertCommand->GetParameters().Add(*Int32Parameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> Int32NullParameter = InsertCommand->CreateParameter();
				Int32NullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*Int32NullParameter.GetUnderlyingPointer());

				// money
				Template::Memory::UniquePointer<IDataParameter> MoneyParameter = InsertCommand->CreateParameter();
				MoneyParameter->SetValue(37.56);
				InsertCommand->GetParameters().Add(*MoneyParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> MoneyNullParameter = InsertCommand->CreateParameter();
				MoneyNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*MoneyNullParameter.GetUnderlyingPointer());

				// nchar (option 1)
				/*
				std::unique_ptr<IDataParameter> WCharParameter = InsertCommand->CreateParameter();
				WCharParameter->SetValue(L'n');
				InsertCommand->GetParameters().Add(WCharParameter.get());

				std::unique_ptr<IDataParameter> WCharNullParameter = InsertCommand->CreateParameter();
				WCharNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters().Add(WCharNullParameter.get());
				*/
				// nchar (option 2)
				/*
				std::unique_ptr<IDataParameter> WStringParameter = InsertCommand->CreateParameter();
				WStringParameter->SetValue(&std::wstring(L"n - mssql will trim automatically"));
				InsertCommand->GetParameters().Add(WStringParameter.get());

				std::unique_ptr<IDataParameter> WStringNullParameter = InsertCommand->CreateParameter();
				WStringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters().Add(WStringNullParameter.get());
				*/
				// nchar (option 3)
				Elysium::Core::IO::MemoryStream WStringStream;
				WStringStream.Write((const BYTE*)L"n - mssql won't trim automatically so set the length correctly!!!!", 2);
				WStringStream.SetPosition(0);

				Template::Memory::UniquePointer<IDataParameter> StreamedWStringParameter = InsertCommand->CreateParameter();
				StreamedWStringParameter->SetValue(&WStringStream);
				InsertCommand->GetParameters().Add(*StreamedWStringParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> StreamedWStringNullParameter = InsertCommand->CreateParameter();
				StreamedWStringNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*StreamedWStringNullParameter.GetUnderlyingPointer());

				// ntext (option 1)
				/*
				std::unique_ptr<IDataParameter> WTextParameter = InsertCommand->CreateParameter();
				WTextParameter->SetValue(L't - mssql will trim automatically');
				InsertCommand->GetParameters().Add(WTextParameter.get());

				std::unique_ptr<IDataParameter> WTextNullParameter = InsertCommand->CreateParameter();
				WTextNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters().Add(WTextNullParameter.get());
				*/
				// ntext (option 2)
				/*
				std::unique_ptr<IDataParameter> WTextStringParameter = InsertCommand->CreateParameter();
				WTextStringParameter->SetValue(&std::wstring(L"t - mssql will trim automatically"));
				InsertCommand->GetParameters().Add(WTextStringParameter.get());

				std::unique_ptr<IDataParameter> WTextStringNullParameter = InsertCommand->CreateParameter();
				WTextStringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters().Add(WTextStringNullParameter.get());
				*/
				// ntext (option 3)
				Elysium::Core::IO::MemoryStream WTextStringStream;
				WTextStringStream.Write((const BYTE*)L"t - mssql won't trim automatically so set the length correctly!!!!", 2);
				WTextStringStream.SetPosition(0);

				Template::Memory::UniquePointer<IDataParameter> StreamedWTextStringParameter = InsertCommand->CreateParameter();
				StreamedWTextStringParameter->SetValue(&WTextStringStream);
				InsertCommand->GetParameters().Add(*StreamedWTextStringParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> StreamedWTextStringNullParameter = InsertCommand->CreateParameter();
				StreamedWTextStringNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*StreamedWTextStringNullParameter.GetUnderlyingPointer());

				// numeric (decimal)

				// nvarchar
				Template::Memory::UniquePointer<IDataParameter> NVarCharParameter = InsertCommand->CreateParameter();
				NVarCharParameter->SetValue(L'n');
				InsertCommand->GetParameters().Add(*NVarCharParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> NVarCharNullParameter = InsertCommand->CreateParameter();
				NVarCharNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*NVarCharNullParameter.GetUnderlyingPointer());

				// real
				Template::Memory::UniquePointer<IDataParameter> RealParameter = InsertCommand->CreateParameter();
				RealParameter->SetValue(23.559999465942383f);
				InsertCommand->GetParameters().Add(*RealParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> RealNullParameter = InsertCommand->CreateParameter();
				RealNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*RealNullParameter.GetUnderlyingPointer());
				/*
				// smalldatetime - ToDo: mssql specific type
				std::unique_ptr<IDataParameter> SmallDateTimeParameter = InsertCommand->CreateParameter();
				SmallDateTimeParameter->SetValue(&DateTime(2010, 02, 10, 12, 30, 0));
				SmallDateTimeParameter->SetDbType(DbType::SmallDateTime);
				InsertCommand->GetParameters().Add(SmallDateTimeParameter.get());

				std::unique_ptr<IDataParameter> SmallDateTimeNullParameter = InsertCommand->CreateParameter();
				SmallDateTimeNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters().Add(SmallDateTimeNullParameter.get());
				*/
				// int16 (smallint)
				Template::Memory::UniquePointer<IDataParameter> Int16Parameter = InsertCommand->CreateParameter();
				Int16Parameter->SetValue(23);
				InsertCommand->GetParameters().Add(*Int16Parameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> Int16NullParameter = InsertCommand->CreateParameter();
				Int16NullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*Int16NullParameter.GetUnderlyingPointer());

				// float (smallmoney)
				Template::Memory::UniquePointer<IDataParameter> SmallmoneyParameter = InsertCommand->CreateParameter();
				SmallmoneyParameter->SetValue(75.45f);
				InsertCommand->GetParameters().Add(*SmallmoneyParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> SmallmoneyNullParameter = InsertCommand->CreateParameter();
				SmallmoneyNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*SmallmoneyNullParameter.GetUnderlyingPointer());

				// sql_variant

				// sysname

				// text (option 1)
				/*
				std::unique_ptr<IDataParameter> TextParameter = InsertCommand->CreateParameter();
				TextParameter->SetValue('s');
				InsertCommand->GetParameters().Add(TextParameter.get());

				std::unique_ptr<IDataParameter> TextNullParameter = InsertCommand->CreateParameter();
				TextNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters().Add(TextNullParameter.get());
				*/
				// text (option 2)
				/*
				std::unique_ptr<IDataParameter> TextStringParameter = InsertCommand->CreateParameter();
				TextStringParameter->SetValue(&std::string("s - mssql will trim automatically"));
				InsertCommand->GetParameters().Add(TextStringParameter.get());

				std::unique_ptr<IDataParameter> TextStringNullParameter = InsertCommand->CreateParameter();
				TextStringNullParameter->SetValue(Elysium::Core::Data::DBNull::Value());
				InsertCommand->GetParameters().Add(TextStringNullParameter.get());
				*/
				// ntext (option 3)
				Elysium::Core::IO::MemoryStream TextStringStream;
				TextStringStream.Write((const BYTE*)L"s - mssql won't trim automatically so set the length correctly!!!!", 2);
				TextStringStream.SetPosition(0);

				Template::Memory::UniquePointer<IDataParameter> StreamedTextStringParameter = InsertCommand->CreateParameter();
				StreamedTextStringParameter->SetValue(&TextStringStream);
				InsertCommand->GetParameters().Add(*StreamedTextStringParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> StreamedTextStringNullParameter = InsertCommand->CreateParameter();
				StreamedTextStringNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*StreamedTextStringNullParameter.GetUnderlyingPointer());

				// time
				Template::Memory::UniquePointer<IDataParameter> TimeParameter = InsertCommand->CreateParameter();
				TimeParameter->SetValue(TimeSpan(13, 37, 27));
				InsertCommand->GetParameters().Add(*TimeParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> TimeNullParameter = InsertCommand->CreateParameter();
				TimeNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*TimeNullParameter.GetUnderlyingPointer());
				/*
				// timestamp - this datatype equals a 'rowversion' and doesn't contain DateTime-information as the name might imply
				std::unique_ptr<IDataParameter> RowVersionParameter = InsertCommand->CreateParameter();
				RowVersionParameter->SetValue((__int64)345345345);
				InsertCommand->GetParameters().Add(RowVersionParameter.get());
				*/
				// BYTE (tinyint)
				Template::Memory::UniquePointer<IDataParameter> TinyIntParameter = InsertCommand->CreateParameter();
				TinyIntParameter->SetValue((unsigned short)17);
				InsertCommand->GetParameters().Add(*TinyIntParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> TinyIntNullParameter = InsertCommand->CreateParameter();
				TinyIntNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*TinyIntNullParameter.GetUnderlyingPointer());

				// GUID (uniqueidentifier)
				Template::Memory::UniquePointer<IDataParameter> GuidParameter = InsertCommand->CreateParameter();
				GuidParameter->SetValue(Guid::Parse(u8"ae019609-99e0-4ef5-85bb-ad90dc302e70"));
				InsertCommand->GetParameters().Add(*GuidParameter.GetUnderlyingPointer());

				//Assert::AreEqual("ae019609-99e0-4ef5-85bb-ad90dc302e70", Guid::Parse("ae019609-99e0-4ef5-85bb-ad90dc302e70").ToString().c_str());

				Template::Memory::UniquePointer<IDataParameter> GuidNullParameter = InsertCommand->CreateParameter();
				GuidNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*GuidNullParameter.GetUnderlyingPointer());

				// varbinary

				// vchar

				// xml
				Template::Memory::UniquePointer<IDataParameter> XmlParameter = InsertCommand->CreateParameter();
				XmlParameter->SetValue(String(u8"<?xml version=\"1.0\" encoding=\"UTF-16\"?><root/>"));
				//XmlParameter->SetDbType(DbType::Xml);
				InsertCommand->GetParameters().Add(*XmlParameter.GetUnderlyingPointer());

				Template::Memory::UniquePointer<IDataParameter> XmlNullParameter = InsertCommand->CreateParameter();
				XmlNullParameter->SetValue(Elysium::Core::Data::DBNull::GetValue());
				InsertCommand->GetParameters().Add(*XmlNullParameter.GetUnderlyingPointer());

				PerformDataInsertionTest(InsertCommand.GetUnderlyingPointer());

				// perform R test
				Template::Memory::UniquePointer<IDbCommand> SelectCommand = _Connection.CreateCommand();
				SelectCommand->SetCommandText(u8"SELECT [bigintNotNull], [bigintNull], [binaryNotNull], [binaryNull], [bitNotNull], [bitNull], [charNotNull], [charNull], [dateNotNull], [dateNull], [datetime2NotNull], [datetime2Null], [datetimeNotNull], [datetimeNull], [datetimeoffsetNotNull], [datetimeoffsetNull], [decimalNotNull], [decimalNull], [floatNotNull], [floatNull], [geographyNotNull], [geographyNull], [geographyNotNull].Lat As Latitude, [geographyNotNull].Long As Longitude, [geographyNotNull].M As Magnitude, [geographyNotNull].Z As Depth, [geometryNotNull], [geometryNull], [hierarchyidNotNull], [hierarchyidNull], [hierarchyidNotNull].ToString() AS HierarchyPath, [hierarchyidNotNull].GetLevel() AS HierarchyLevel, [imageNotNull], [imageNull], [intNotNull], [intNull], [moneyNotNull], [moneyNull], [ncharNotNull], [ncharNull], [ntextNotNull], [ntextNull], [numericNotNull], [numericNull], [nvarcharNotNull], [nvarcharNull], [realNotNull], [realNull], [smalldatetimeNotNull], [smalldatetimeNull], [smallintNotNull], [smallintNull], [smallmoneyNotNull], [smallmoneyNull], [sql_variantNotNull], [sql_variantNull], [sysnameNotNull], [sysnameNull], [textNotNull], [textNull], [timeNotNull], [timeNull], [timestampNotNull], [tinyintNotNull], [tinyintNull], [uniqueidentifierNotNull], [uniqueidentifierNull], [varbinaryNotNull], [varbinaryNull], [varcharNotNull], [varcharNull], [xmlNotNull], [xmlNull] FROM AllDataTypes");
				TestReader(SelectCommand);

				// perform U test
				Template::Memory::UniquePointer<IDbCommand> UpdateCommand = _Connection.CreateCommand();
				UpdateCommand->SetCommandText(u8"UPDATE AllDataTypes SET [bigintNull] = ?");
				Template::Memory::UniquePointer<IDataParameter> UpdateParameter = UpdateCommand->CreateParameter();
				UpdateParameter->SetValue((__int64)123);
				UpdateCommand->GetParameters().Add(*UpdateParameter.GetUnderlyingPointer());
				UpdateCommand->ExecuteNonQuery();

				// perform D test
				Template::Memory::UniquePointer<IDbCommand> DeleteCommand = _Connection.CreateCommand();
				DeleteCommand->SetCommandText(u8"DELETE FROM AllDataTypes");
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
				//Logger::WriteMessage(ex.GetExceptionMessage().GetCharArray());
				Assert::Fail();
			}
		}

		TEST_METHOD(CRUDWithNamedParameters)
		{
			// oledb doesn't support named parameters. therefore just do nothing here.
		}
private:
	SqlNativeConnection _Connection = SqlNativeConnection();

	static void TestReader(const Template::Memory::UniquePointer<IDbCommand>& Command)
	{
		Template::Memory::UniquePointer<IDataReader> IReader = Command->ExecuteReader();
		DbDataReader* Reader = (DbDataReader*)IReader.GetUnderlyingPointer();

		// test a few reader methods before actually starting to read
		{
			//Assert::AreSame(10L, Reader->GetRecordsAffected());
			const String ColumnDataTypeName = Reader->GetDataTypeName(0);
			AssertExtended::AreEqual(u8"DBTYPE_I8", &ColumnDataTypeName[0]);

			const String ColumnName = Reader->GetName(0);
			AssertExtended::AreEqual(u8"bigintNotNull", &ColumnName[0]);

			const uint64_t ColumnOrdinal = Reader->GetOrdinal(String(u8"binaryNull"));
			Assert::AreEqual(3ULL, ColumnOrdinal);
		}

		__int64 AvailableBytes;
		int64_t BigIntValue;
		List<byte> BytesValue = List<byte>(1);
		bool BitValue;
		String CharValues = String(1);
		DateTime DatetimeValue = DateTime(0);
		DateTimeOffset DateTimeOffsetValue = DateTimeOffset(DatetimeValue);
		TimeSpan TimeSpanValue = TimeSpan(0);
		Decimal DecimalValue;
		float FloatValue;
		double DoubleValue;
		int16_t Int16Value;
		int IntValue;
		byte GuidData[16];
		Guid GUIDValue = Guid(GuidData);
		while (Reader->Read())
		{
			// bigint
			BigIntValue = Reader->GetInt64(0);
			AssertExtended::AreEqual(9223372036854775807, BigIntValue);
			Assert::IsFalse(Reader->IsDBNull(0));
			Assert::IsTrue(Reader->IsDBNull(1));

			// binary
			BytesValue[0] = Reader->GetByte(2);
			Assert::AreEqual((byte)'v', BytesValue[0]);
			AvailableBytes = Reader->GetBytes(2, 0, nullptr, 1);
			BytesValue = List<byte>(AvailableBytes);
			AvailableBytes = Reader->GetBytes(2, 0, &BytesValue[0], 1);
			Assert::AreEqual((byte)'v', BytesValue[0]);
			Assert::IsFalse(Reader->IsDBNull(2));
			Assert::IsTrue(Reader->IsDBNull(3));

			// bit
			BitValue = Reader->GetBoolean(4);
			Assert::AreEqual(true, BitValue);
			Assert::IsFalse(Reader->IsDBNull(4));
			Assert::IsTrue(Reader->IsDBNull(5));

			// char
			CharValues[0] = Reader->GetChar(6);
			Assert::AreEqual(u8'a', CharValues[0]);
			AvailableBytes = Reader->GetChars(6, 0, nullptr, 0);
			CharValues = String(AvailableBytes);
			AvailableBytes = Reader->GetChars(6, 0, &CharValues[0], (Elysium::Core::size)AvailableBytes);
			Assert::AreEqual(u8'a', CharValues[0]);
			Assert::IsFalse(Reader->IsDBNull(6));
			Assert::IsTrue(Reader->IsDBNull(7));

			// date
			DatetimeValue = Reader->GetDateTime(8);
			IntValue = DatetimeValue.GetDay();
			Assert::AreEqual(18, IntValue);
			IntValue = DatetimeValue.GetMonth();
			Assert::AreEqual(6, IntValue);
			IntValue = DatetimeValue.GetYear();
			Assert::AreEqual(2012, IntValue);
			Assert::IsFalse(Reader->IsDBNull(8));
			Assert::IsTrue(Reader->IsDBNull(9));

			// datetime2
			DatetimeValue = Reader->GetDateTime(10);
			IntValue = DatetimeValue.GetDay();
			Assert::AreEqual(18, IntValue);
			IntValue = DatetimeValue.GetMonth();
			Assert::AreEqual(6, IntValue);
			IntValue = DatetimeValue.GetYear();
			Assert::AreEqual(2012, IntValue);
			IntValue = DatetimeValue.GetHour();
			Assert::AreEqual(22, IntValue);
			IntValue = DatetimeValue.GetMinute();
			Assert::AreEqual(34, IntValue);
			IntValue = DatetimeValue.GetSecond();
			Assert::AreEqual(9, IntValue);
			Assert::IsFalse(Reader->IsDBNull(10));
			Assert::IsTrue(Reader->IsDBNull(11));

			// datetime
			DatetimeValue = Reader->GetDateTime(12);
			IntValue = DatetimeValue.GetDay();
			Assert::AreEqual(18, IntValue);
			IntValue = DatetimeValue.GetMonth();
			Assert::AreEqual(6, IntValue);
			IntValue = DatetimeValue.GetYear();
			Assert::AreEqual(2012, IntValue);
			IntValue = DatetimeValue.GetHour();
			Assert::AreEqual(22, IntValue);
			IntValue = DatetimeValue.GetMinute();
			Assert::AreEqual(34, IntValue);
			IntValue = DatetimeValue.GetSecond();
			Assert::AreEqual(9, IntValue);
			Assert::IsFalse(Reader->IsDBNull(12));
			Assert::IsTrue(Reader->IsDBNull(13));

			// datetimeoffset
			DateTimeOffsetValue = Reader->GetDateTimeOffset(14);
			IntValue = DateTimeOffsetValue.GetDateTime().GetDay();
			Assert::AreEqual(10, IntValue);
			IntValue = DateTimeOffsetValue.GetDateTime().GetMonth();
			Assert::AreEqual(12, IntValue);
			IntValue = DateTimeOffsetValue.GetDateTime().GetYear();
			Assert::AreEqual(2025, IntValue);
			IntValue = DateTimeOffsetValue.GetDateTime().GetHour();
			Assert::AreEqual(12, IntValue);
			IntValue = DateTimeOffsetValue.GetDateTime().GetMinute();
			Assert::AreEqual(32, IntValue);
			IntValue = DateTimeOffsetValue.GetDateTime().GetSecond();
			Assert::AreEqual(10, IntValue);
			Assert::AreEqual(1, DateTimeOffsetValue.GetOffset().GetHours());
			Assert::AreEqual(0, DateTimeOffsetValue.GetOffset().GetMinutes());
			Assert::AreEqual(0, DateTimeOffsetValue.GetOffset().GetSeconds());
			Assert::IsFalse(Reader->IsDBNull(14));
			Assert::IsTrue(Reader->IsDBNull(15));

			// decimal
			DecimalValue = Reader->GetDecimal(16);
			AssertExtended::AreEqual(1LL, DecimalValue.GetHighPart());
			AssertExtended::AreEqual(0ULL, DecimalValue.GetLowPart());
			Assert::IsFalse(Reader->IsDBNull(16));
			Assert::IsTrue(Reader->IsDBNull(17));

			// float
			FloatValue = Reader->GetFloat(18);
			Assert::AreEqual(0.27f, FloatValue);
			/*
			Reader->GetDouble(18, &DoubleValue);
			Assert::AreEqual(0.27, DoubleValue);
			*/
			Assert::IsFalse(Reader->IsDBNull(18));
			Assert::IsTrue(Reader->IsDBNull(19));

			// geography
			AvailableBytes = Reader->GetBytes(20, 0, nullptr, 0);
			BytesValue = List<byte>(AvailableBytes);
			AvailableBytes = Reader->GetBytes(20, 0, &BytesValue[0], BytesValue.GetCapacity());
			// ToDo: test somehow or create specific type?
			Assert::IsFalse(Reader->IsDBNull(20));
			Assert::IsTrue(Reader->IsDBNull(21));
			FloatValue = Reader->GetFloat(22);	// Latitude
			Assert::AreEqual(47.651f, FloatValue);
			DoubleValue = Reader->GetDouble(22);	// Latitude
			Assert::AreEqual(47.651, DoubleValue);
			DoubleValue = Reader->GetDouble(23);	// Longitude
			Assert::AreEqual(-122.349, DoubleValue);
			DoubleValue = Reader->GetDouble(24);	// Magnitude
			Assert::AreEqual(0.0, DoubleValue);
			DoubleValue = Reader->GetDouble(25);	// Depth
			Assert::AreEqual(0.0, DoubleValue);

			// geometry
			AvailableBytes = Reader->GetBytes(26, 0, nullptr, 0);
			BytesValue = List<byte>(AvailableBytes);
			AvailableBytes = Reader->GetBytes(26, 0, &BytesValue[0], BytesValue.GetCapacity());
			AvailableBytes = Reader->GetChars(26, 0, nullptr, 0);
			CharValues = String(AvailableBytes);
			AvailableBytes = Reader->GetChars(26, 0, &CharValues[0], CharValues.GetLength());
			// ToDo: test somehow or create specific type?
			Assert::IsFalse(Reader->IsDBNull(26));
			Assert::IsTrue(Reader->IsDBNull(27));

			// hierarchyid
			AvailableBytes = Reader->GetBytes(28, 0, nullptr, 0);	// ToDo: why do we get zero bytes?
			//BytesValue.resize(AvailableBytes);
			//AvailableBytes = Reader->GetBytes(28, 0, BytesValue.data(), 0, 2048);
			Assert::IsFalse(Reader->IsDBNull(28));
			Assert::IsTrue(Reader->IsDBNull(29));
			/*
			AvailableBytes = Reader->GetChars(30, 0, nullptr, 0);	// HierarchyPath
			CharValues = String(AvailableBytes);
			AvailableBytes = Reader->GetChars(30, 0, &CharValues[0], AvailableBytes);	// HierarchyPath
			Assert::AreEqual(u8'/', CharValues[0]);
			Int16Value = Reader->GetInt16(31);	// HierarchyLevel
			Assert::AreEqual((int16_t)0, Int16Value);
			*/
			// image
			AvailableBytes = Reader->GetBytes(32, 0, nullptr, 0);
			BytesValue = List<byte>(AvailableBytes);
			AvailableBytes = Reader->GetBytes(32, 0, &BytesValue[0], (Elysium::Core::size)AvailableBytes);
			Assert::IsFalse(Reader->IsDBNull(32));
			Assert::IsTrue(Reader->IsDBNull(33));

			// int
			IntValue = Reader->GetInt32(34);
			Assert::AreEqual(23, IntValue);
			Assert::IsFalse(Reader->IsDBNull(34));
			Assert::IsTrue(Reader->IsDBNull(35));

			// money
			DoubleValue = Reader->GetDouble(36);
			Assert::AreEqual(37.56, DoubleValue);
			FloatValue = Reader->GetFloat(36);
			Assert::AreEqual(37.56f, FloatValue);
			Assert::IsFalse(Reader->IsDBNull(36));
			Assert::IsTrue(Reader->IsDBNull(37));

			// nchar
			CharValues[0] = Reader->GetChar(38);
			Assert::AreEqual(u8'n', CharValues[0]);
			AvailableBytes = Reader->GetChars(38, 0, nullptr, 0);
			CharValues = String(AvailableBytes);
			AvailableBytes = Reader->GetChars(38, 0, &CharValues[0], AvailableBytes);
			Assert::AreEqual(u8'n', CharValues[0]);
			Assert::IsFalse(Reader->IsDBNull(38));
			Assert::IsTrue(Reader->IsDBNull(39));

			// ntext
			AvailableBytes = Reader->GetChars(40, 0, nullptr, 0);
			CharValues = String(AvailableBytes);
			AvailableBytes = Reader->GetChars(40, 0, &CharValues[0], AvailableBytes);
			Assert::AreEqual(u8't', CharValues[0]);
			Assert::IsFalse(Reader->IsDBNull(40));
			Assert::IsTrue(Reader->IsDBNull(41));

			// numeric
			DecimalValue = Reader->GetDecimal(42);
			AssertExtended::AreEqual(99LL, DecimalValue.GetHighPart());
			AssertExtended::AreEqual(0ULL, DecimalValue.GetLowPart());
			Assert::IsFalse(Reader->IsDBNull(42));
			Assert::IsTrue(Reader->IsDBNull(43));

			// nvarchar
			AvailableBytes = Reader->GetChars(44, 0, nullptr, 0);
			CharValues = String(AvailableBytes);
			AvailableBytes = Reader->GetChars(44, 0, &CharValues[0], AvailableBytes);
			Assert::AreEqual(u8'n', CharValues[0]);
			Assert::IsFalse(Reader->IsDBNull(44));
			Assert::IsTrue(Reader->IsDBNull(45));

			// real
			FloatValue = Reader->GetFloat(46);
			Assert::AreEqual(23.559999465942383f, FloatValue);
			DoubleValue = Reader->GetDouble(46);
			Assert::AreEqual(23.559999465942383, DoubleValue);
			Assert::IsFalse(Reader->IsDBNull(46));
			Assert::IsTrue(Reader->IsDBNull(47));

			// smalldatetime
			DatetimeValue = Reader->GetDateTime(48);
			IntValue = DatetimeValue.GetDay();
			Assert::AreEqual(10, IntValue);
			IntValue = DatetimeValue.GetMonth();
			Assert::AreEqual(2, IntValue);
			IntValue = DatetimeValue.GetYear();
			Assert::AreEqual(2010, IntValue);
			IntValue = DatetimeValue.GetHour();
			Assert::AreEqual(12, IntValue);
			IntValue = DatetimeValue.GetMinute();
			Assert::AreEqual(30, IntValue);
			IntValue = DatetimeValue.GetSecond();
			Assert::AreEqual(0, IntValue);
			Assert::IsFalse(Reader->IsDBNull(48));
			Assert::IsTrue(Reader->IsDBNull(49));

			// smallint
			Int16Value = Reader->GetInt16(50);
			Assert::AreEqual((short)23, Int16Value);
			Assert::IsFalse(Reader->IsDBNull(50));
			Assert::IsTrue(Reader->IsDBNull(51));

			// smallmoney
			FloatValue = Reader->GetFloat(52);
			Assert::AreEqual(75.45f, FloatValue);
			DoubleValue = Reader->GetDouble(52);
			Assert::AreEqual(75.45, DoubleValue);
			Assert::IsFalse(Reader->IsDBNull(52));
			Assert::IsTrue(Reader->IsDBNull(53));

			// sql_variant
			AvailableBytes = Reader->GetBytes(54, 0, nullptr, 0);	// ToDo: why do we get zero bytes?
			//BytesValue.resize(AvailableBytes);
			//AvailableBytes = Reader->GetBytes(54, 0, BytesValue.data(), 0, AvailableBytes); // ToDo: test somehow or create specific type?
			Assert::IsFalse(Reader->IsDBNull(54));
			Assert::IsTrue(Reader->IsDBNull(55));

			// sysname
			AvailableBytes = Reader->GetChars(56, 0, nullptr, 0);
			CharValues = String(AvailableBytes);
			AvailableBytes = Reader->GetChars(56, 0, &CharValues[0], AvailableBytes);
			Assert::AreEqual(u8's', CharValues[0]);
			Assert::IsFalse(Reader->IsDBNull(56));
			Assert::IsTrue(Reader->IsDBNull(57));

			// text
			AvailableBytes = Reader->GetChars(58, 0, nullptr, 0);
			CharValues = String(AvailableBytes);
			AvailableBytes = Reader->GetChars(58, 0, &CharValues[0], AvailableBytes);
			Assert::AreEqual(u8's', CharValues[0]);
			Assert::IsFalse(Reader->IsDBNull(58));
			Assert::IsTrue(Reader->IsDBNull(59));

			// time
			TimeSpanValue = Reader->GetTimeSpan(60);
			Assert::AreEqual(13, TimeSpanValue.GetHours());
			Assert::AreEqual(37, TimeSpanValue.GetMinutes());
			Assert::AreEqual(27, TimeSpanValue.GetSeconds());

			DatetimeValue = Reader->GetDateTime(60);
			IntValue = DatetimeValue.GetDay();
			Assert::AreEqual(1, IntValue);
			IntValue = DatetimeValue.GetMonth();
			Assert::AreEqual(1, IntValue);
			IntValue = DatetimeValue.GetYear();
			Assert::AreEqual(1, IntValue);
			IntValue = DatetimeValue.GetHour();
			Assert::AreEqual(13, IntValue);
			IntValue = DatetimeValue.GetMinute();
			Assert::AreEqual(37, IntValue);
			IntValue = DatetimeValue.GetSecond();
			Assert::AreEqual(27, IntValue);
			Assert::IsFalse(Reader->IsDBNull(60));
			Assert::IsTrue(Reader->IsDBNull(61));

			// timestamp - this datatype equals a 'rowversion' and doesn't contain DateTime-information as the name might imply
			BigIntValue = Reader->GetInt64(62);
			//Assert::AreEqual(-3384736594945638400, BigIntValue);	// ToDo: different value for each row each time
			Assert::IsFalse(Reader->IsDBNull(62));

			// tinyint
			Int16Value = Reader->GetInt16(63);
			Assert::AreEqual((short)17, Int16Value);
			Assert::IsFalse(Reader->IsDBNull(63));
			Assert::IsTrue(Reader->IsDBNull(64));

			// GUID (uniqueidentifier)
			GUIDValue = Reader->GetGuid(65);
			//Assert::AreEqual("ae019609-99e0-4ef5-85bb-ad90dc302e70", GUIDValue.ToString().c_str());
			Assert::IsFalse(Reader->IsDBNull(65));
			Assert::IsTrue(Reader->IsDBNull(66));

			// varbinary
			AvailableBytes = Reader->GetBytes(67, 0, nullptr, 0);	// ToDo: why do we get zero bytes? (same as sql_variant)
			//BytesValue.resize(AvailableBytes);
			//AvailableBytes = Reader->GetBytes(54, 0, BytesValue.data(), 0, AvailableBytes); // ToDo: test somehow or create specific type?
			Assert::IsFalse(Reader->IsDBNull(67));
			Assert::IsTrue(Reader->IsDBNull(68));

			// vchar 
			AvailableBytes = Reader->GetChars(69, 0, nullptr, 0);
			CharValues = String(AvailableBytes);
			AvailableBytes = Reader->GetChars(69, 0, &CharValues[0], AvailableBytes);
			Assert::AreEqual(u8'v', CharValues[0]);
			Assert::IsFalse(Reader->IsDBNull(69));
			Assert::IsTrue(Reader->IsDBNull(70));

			// xml
			AvailableBytes = Reader->GetChars(71, 0, nullptr, 0);
			CharValues = String(AvailableBytes);
			AvailableBytes = Reader->GetChars(71, 0, &CharValues[0], AvailableBytes);
			//Assert::AreEqual(L"<root\>", WCharValues.data());	// ToDo: encoding-problematic?
			Assert::IsFalse(Reader->IsDBNull(71));
			Assert::IsTrue(Reader->IsDBNull(72));
		}

		Reader->Close();
	}

	static void LogSqlNativeException(SqlNativeException& ex)
	{
		//Logger::WriteMessage(ex.GetExceptionMessage().GetCharArray());
		Logger::WriteMessage(std::to_string(ex.GetErrorCode()).c_str());
		for (unsigned int i = 0; i < ex.GetErrors().GetCount(); i++)
		{
			SqlNativeError Error = ex.GetErrors()[i];
			Logger::WriteMessage(("\tErrorSpecificErrorCode: " + std::to_string(Error.GetErrorSpecificErrorCode())).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage(("\tProviderSpecificErrorCode: " + std::to_string(Error.GetProviderSpecificErrorCode())).c_str());
			Logger::WriteMessage("\r\n");
			//Logger::WriteMessage(("\tClassId: " + std::to_string(Error.GetClassId())).c_str());
			//Logger::WriteMessage("\r\n");
			//Logger::WriteMessage(("\tInterfaceId: " + std::to_string(Error.GetInterfaceId())).c_str());
			//Logger::WriteMessage("\r\n");
			Logger::WriteMessage(("\tDisplayId: " + std::to_string(Error.GetDisplayId())).c_str());
			Logger::WriteMessage("\r\n");

			//Logger::WriteMessage(("\tDescription: " + std::to_string(Error.GetDescription())).c_str());
			//Logger::WriteMessage("\r\n");
			//Logger::WriteMessage(("\tGUID: " + std::to_string(Error.GetGUID())).c_str());
			//Logger::WriteMessage("\r\n");
			Logger::WriteMessage(("\tHelpContext: " + std::to_string(Error.GetHelpContext())).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage((L"\tHelpFile: " + Error.GetHelpFile()).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage((L"\tSource: " + Error.GetSource()).c_str());
			Logger::WriteMessage("\r\n");

			Logger::WriteMessage((L"\tSqlState: " + Error.GetSqlState()).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage(("\tErrorCode: " + std::to_string(Error.GetErrorCode())).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage((L"\tSSError: " + Error.GetSSError()).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage((L"\tServer: " + Error.GetServer()).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage((L"\tProcedure: " + Error.GetProcedure()).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage(("\tNumber: " + std::to_string(Error.GetNumber())).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage(("\tState: " + std::to_string(Error.GetState())).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage(("\tErrorSeverity: " + std::to_string(Error.GetErrorSeverity())).c_str());
			Logger::WriteMessage("\r\n");
			Logger::WriteMessage(("\tLineNumber: " + std::to_string(Error.GetLineNumber())).c_str());
			Logger::WriteMessage("\r\n");

			Logger::WriteMessage("\t---");
		}
	}
	};
}
