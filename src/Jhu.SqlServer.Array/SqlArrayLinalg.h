#pragma once

#include "macro.h"
#include "SqlArrayAttribute.h"
#include "SqlArray.h"
#include "enum.h"

using namespace System;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;
using namespace Jhu::SqlServer::Array::Parser;

namespace Jhu { namespace SqlServer { namespace Array
{
	
	/// <summary>
	/// Implements entry points to the LAPACK library.
	/// </summary>
	template <class T, class B>
	[Jhu::SqlServer::Array::SqlArrayAttribute]
	public value class SqlArrayLinalg
	{

	public:

		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "SVD_FillRow")]
		static System::Collections::IEnumerable^ SVD(typename B::SqlBufferT data);

		static void SVD_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::SqlBufferT% s,
			[System::Runtime::InteropServices::OutAttribute] typename B::SqlBufferT% U,
			[System::Runtime::InteropServices::OutAttribute] typename B::SqlBufferT% Vt);

	};
}
} }