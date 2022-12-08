#include "SqlNativeErrorCollection.hpp"

Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeErrorCollection::SqlNativeErrorCollection(IUnknown* ErrorObject)
	: _Errors(Elysium::Core::Template::Container::Vector<SqlNativeError>())
{
	HRESULT HResult;
	ISupportErrorInfo* SupportsErrorInfo;
	if (SUCCEEDED(HResult = ErrorObject->QueryInterface(IID_ISupportErrorInfo, (void**)&SupportsErrorInfo)))
	{
		unsigned long LCID = GetSystemDefaultLCID();

		IErrorInfo* NativeErrorInfoFactory;
		HResult = GetErrorInfo(0, &NativeErrorInfoFactory);
		if (NativeErrorInfoFactory != nullptr)
		{
			IErrorRecords* NativeErrorRecords;
			if (SUCCEEDED(HResult = NativeErrorInfoFactory->QueryInterface(IID_IErrorRecords, (void**)&NativeErrorRecords)))
			{
				// prepare are variables that can possibly be read
				HRESULT ErrorSpecificErrorCode = 0;
				unsigned long ProviderSpecificErrorCode = 0;
				GUID ClassId;
				GUID InterfaceId;
				long DisplayId;

				wchar_t* Description = nullptr;
				GUID GUID;
				unsigned long HelpContext = 0;
				wchar_t* HelpFile = nullptr;
				wchar_t* Source = nullptr;

				wchar_t* NativeSqlState = nullptr;
				long NativeErrorCode = 0;
				wchar_t* NativeSSError = nullptr;
				wchar_t* Server = nullptr;
				wchar_t* Procedure = nullptr;
				long ErrorNumber = 0;
				BYTE State = NULL;
				BYTE ErrorSeverity = NULL;
				unsigned short LineNumber = 0;

				// gather information for each error record
				unsigned long NumberOfErrors;
				NativeErrorRecords->GetRecordCount(&NumberOfErrors);
				for (unsigned long i = 0; i < NumberOfErrors; i++)
				{
					// get basic error information
					ERRORINFO NativeErrorInfo;
					if (SUCCEEDED(HResult = NativeErrorRecords->GetBasicErrorInfo(i, &NativeErrorInfo)))
					{
						ErrorSpecificErrorCode = NativeErrorInfo.hrError;
						ProviderSpecificErrorCode = NativeErrorInfo.dwMinor;
						ClassId = NativeErrorInfo.clsid;
						InterfaceId = NativeErrorInfo.iid;
						DisplayId = NativeErrorInfo.dispid;
					}

					// get most of the basic information associated with an the error
					IErrorInfo* NativeIErrorInfoRecord;
					if (SUCCEEDED(HResult = NativeErrorRecords->GetErrorInfo(i, LCID, &NativeIErrorInfoRecord)))
					{
						NativeIErrorInfoRecord->GetDescription(&Description);
						NativeIErrorInfoRecord->GetGUID(&GUID);
						NativeIErrorInfoRecord->GetHelpContext(&HelpContext);
						NativeIErrorInfoRecord->GetHelpFile(&HelpFile);
						NativeIErrorInfoRecord->GetSource(&Source);

						NativeIErrorInfoRecord->Release();
					}

					// get sql specific error information
					ISQLErrorInfo* NativeSQLErrorInfo;
					NativeErrorRecords->GetCustomErrorObject(i, IID_ISQLErrorInfo, (IUnknown**)&NativeSQLErrorInfo);
					if (NativeSQLErrorInfo != nullptr)
					{
						HResult = NativeSQLErrorInfo->GetSQLInfo(&NativeSqlState, &NativeErrorCode);

						ISQLServerErrorInfo* NativeISQLServerErrorInfo = nullptr;
						NativeSQLErrorInfo->QueryInterface(IID_ISQLServerErrorInfo, (void**)&NativeISQLServerErrorInfo);
						if (NativeISQLServerErrorInfo != nullptr)
						{
							SSERRORINFO* NativeSSErrorInfo = nullptr;
							NativeISQLServerErrorInfo->GetErrorInfo(&NativeSSErrorInfo, &NativeSSError);
							if (NativeSSErrorInfo != nullptr)
							{
								Server = NativeSSErrorInfo->pwszServer;
								Procedure = NativeSSErrorInfo->pwszProcedure;
								ErrorNumber = NativeSSErrorInfo->lNative;
								State = NativeSSErrorInfo->bState;
								ErrorSeverity = NativeSSErrorInfo->bClass;
								LineNumber = NativeSSErrorInfo->wLineNumber;
							}
							NativeISQLServerErrorInfo->Release();
						}

						// clean-up
						NativeSQLErrorInfo->Release();
					}

					// populate the error collection with another entry
					_Errors.PushBack(SqlNativeError(ErrorSpecificErrorCode, ProviderSpecificErrorCode, ClassId, InterfaceId, DisplayId,
						Description, GUID, HelpContext, HelpFile, Source,
						NativeSqlState, NativeErrorCode, NativeSSError, Server, Procedure, ErrorNumber, State, ErrorSeverity, LineNumber));

					// reset all variables for the next error record
					if (Source != nullptr)
					{
						SysFreeString(Source);
						Source = nullptr;
					}
					if (Description != nullptr)
					{
						SysFreeString(Description);
						Description = nullptr;
					}
					if (HelpFile != nullptr)
					{
						SysFreeString(HelpFile);
						HelpFile = nullptr;
					}
					if (NativeSqlState != nullptr)
					{
						SysFreeString(NativeSqlState);
						NativeSqlState = nullptr;
					}
					if (NativeSSError != nullptr)
					{
						// no need to SysFreeString(NativeSSError);
						NativeSSError = nullptr;
					}
				}
				NativeErrorRecords->Release();
			}
			NativeErrorInfoFactory->Release();
		}
		SupportsErrorInfo->Release();
	}
}
Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeErrorCollection::~SqlNativeErrorCollection()
{
}

const Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeError & Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeErrorCollection::operator[](Elysium::Core::size i) const
{
	return _Errors.GetAt(i);
}

const Elysium::Core::size Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeErrorCollection::GetLength() const
{
	return _Errors.GetLength();
}
const bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeErrorCollection::GetIsReadOnly() const
{
	return false;
}

void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeErrorCollection::Add(const SqlNativeError & Item)
{
	throw 1;
}
void Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeErrorCollection::Clear()
{
	throw 1;
}
bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeErrorCollection::Contains(const SqlNativeError & Item) const
{
	throw 1;
}
bool Elysium::Core::Data::SqlNativeClient::OleDb::SqlNativeErrorCollection::Remove(const SqlNativeError & Item)
{
	throw 1;
}
