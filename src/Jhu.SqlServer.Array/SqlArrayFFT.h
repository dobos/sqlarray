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
	/// Implements entry points to FFTW
	/// </summary>
	template <class T, class B>
	[Jhu::SqlServer::Array::SqlArrayAttribute]
	public value class SqlArrayFFT
	{

	public:

		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT FFTForward(typename B::SqlBufferT data);

		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT FFTBackward(typename B::SqlBufferT data);

		/*
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT RealToComplex(typename B::SqlBufferT data);
		*/

		/*
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT ComplexToComplex(typename B::SqlBufferT data);

		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT ComplexToComplexInverse(typename B::SqlBufferT data);
		*/

		/*
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT ComplexToReal(typename B::SqlBufferT data);
		*/
	};
}
} }