#pragma once

#include "macro.h"

using namespace System;
using namespace System::Data::SqlTypes;
using namespace System::Text::RegularExpressions;
using namespace Microsoft::SqlServer::Server;

namespace Jhu { namespace SqlServer { namespace Array
{

	/// <summary>
	/// Implements a compex type.
	/// </summary>
	template <class T>
	[Serializable]
	[SqlUserDefinedType(Format::Native, IsByteOrdered=true, )]
	public value class SqlComplex : INullable
	{
	private:
		// Member variables
	public:
		T Re;
		T Im;

		// Properties
	public:
		virtual property bool IsNull { virtual bool get() { return false; } }
		static property SqlComplex Null { SqlComplex get() { return SqlComplex(0, 0); } }
		static property SqlComplex MaxValue { SqlComplex get() { throw gcnew NotImplementedException(); } }
		static property SqlComplex MinValue { SqlComplex get() { throw gcnew NotImplementedException(); } }

	public:
		SqlComplex(T re, T im) : Re(re), Im(im) {};

		virtual String^ ToString() override;
		virtual String^ ToStringInvariant();

	internal:
		virtual String^ ToStringWithProvider(IFormatProvider^ provider);

		// Operators
	public:

		static SqlComplex operator + (SqlComplex a, SqlComplex b);
		static SqlComplex operator - (SqlComplex a, SqlComplex b);
		static SqlComplex operator * (SqlComplex a, SqlComplex b);
		static SqlComplex operator / (SqlComplex a, SqlComplex b);
		
		static bool operator < (SqlComplex a, SqlComplex b) { throw gcnew NotImplementedException(); }
		static bool operator > (SqlComplex a, SqlComplex b) { throw gcnew NotImplementedException(); }

		explicit SqlComplex<T>(Byte a) : Re((T)a) {};
		explicit SqlComplex<T>(Int16 a) : Re((T)a) {};
		explicit SqlComplex<T>(Int32 a) : Re((T)a) {};
		explicit SqlComplex<T>(Int64 a) : Re((T)a) {};
		explicit SqlComplex<T>(Single a) : Re((T)a) {};
		explicit SqlComplex<T>(Double a) : Re((T)a) {};

		static explicit operator double(SqlComplex a) { throw gcnew NotImplementedException(); }

		template <class P>
		explicit SqlComplex<T>(SqlComplex<P> a) : Re((T)a.Re), Im((T)a.Im) {};

	public:
		static SqlComplex Parse(SqlString value);
		static SqlComplex ParseInvariant(SqlString value);

	internal:
		static SqlComplex ParseWithProvider(SqlString value, IFormatProvider^ provider);
	};
	
} } }