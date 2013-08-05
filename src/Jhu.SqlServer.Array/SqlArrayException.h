#pragma once

#include "macro.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;
using namespace Jhu::SqlServer::Array::Parser;

namespace Jhu { namespace SqlServer { namespace Array
{

	/// <summary>
	/// Implements an exception that's returned by the library on invalid input data.
	/// </summary>
	public ref class SqlArrayException : public Exception
	{
		public: SqlArrayException() : Exception() {};
		public: SqlArrayException(String^ message) : Exception(message) {};
		public: SqlArrayException(String^ message, Exception^ innerException) : Exception(message, innerException) {};
	};
}
} }