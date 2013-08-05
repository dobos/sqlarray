#include "stdafx.h"
#include "macro.h"
#include "SqlComplex.h"
#include "ShortArray.h"
#include "MaxArray.h"
#include "SqlArrayAttribute.h"
#include "SqlArray.h"
#include "SqlArrayTypeConverter.h"

using namespace System;
using namespace System::Text;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;
using namespace Jhu::SqlServer::Array::Parser;

namespace Jhu { namespace SqlServer { namespace Array
{
	template <class F, class B, class T, class C>
	SqlArray<T, C> SqlArrayTypeConverter<F, B, T, C>::Convert(SqlArray<F, B> v)
	{
		String^ msg;
		IntPtr ipf;
		IntPtr ipt;

		pin_ptr<F> pf = nullptr;
		pin_ptr<T> pt = nullptr;

		try
		{

			array<B::IndexT>^ oldlength = v.GetLengths();
			array<C::IndexT>^ newlength = gcnew array<C::IndexT>(v.m_rank);
		
			for (B::RankT i = 0; i < oldlength->Length; i ++)
			{
				newlength[i] = (C::IndexT)oldlength[i];
			}
		
			SqlArray<T, C> u(newlength);

			pf = v.GetDataPointer();
			pt = u.GetDataPointer();
		
			ipf = IntPtr(pf);
			ipt = IntPtr(pt);
			msg = String::Format("{0} {1}", ipf, ipt);

			typename B::IndexT len = v.TotalLength;

			for (typename B::IndexT i = 0; i < len; i ++)
			{
				*pt++ = T(*pf++);
			}

			return u;
		}
		catch (AccessViolationException^ ex)
		{
			ipf = IntPtr(pf);
			ipt = IntPtr(pt);
			throw gcnew Exception(String::Format("{0} | {1} {2}", msg, ipf, ipt), ex);
		}
	}

	template <class F, class B, class T, class C>
	typename C::SqlBufferT SqlArrayTypeConverter<F, B, T, C>::ConvertTo(typename B::SqlBufferT data)
	{
		SqlArray<F, B> u(data, ArrayLoadMethod::AllData);
		
		return Convert(u).ToSqlBuffer();
	}

#define SPECIALIZE_SQLARRAYTYPECONVERTER_1(T) \
	template Jhu::SqlServer::Array::SqlArrayTypeConverter<T, ShortArray, T, MaxArray>; \
	template Jhu::SqlServer::Array::SqlArrayTypeConverter<T, MaxArray, T, ShortArray>; \

#define SPECIALIZE_SQLARRAYTYPECONVERTER_2(F, T) \
	template Jhu::SqlServer::Array::SqlArrayTypeConverter<F, ShortArray, T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArrayTypeConverter<F, MaxArray, T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArrayTypeConverter<F, ShortArray, T, MaxArray>; \
	template Jhu::SqlServer::Array::SqlArrayTypeConverter<F, MaxArray, T, MaxArray>; 

	SPECIALIZE_SQLARRAYTYPECONVERTER_1(Byte)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Byte, Int16)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Byte, Int32)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Byte, Int64)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Byte, Single)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Byte, Double)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Byte, SqlComplex<Single>)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Byte, SqlComplex<Double>)

	SPECIALIZE_SQLARRAYTYPECONVERTER_1(Int16)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int16, Byte)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int16, Int32)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int16, Int64)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int16, Single)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int16, Double)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int16, SqlComplex<Single>)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int16, SqlComplex<Double>)

	SPECIALIZE_SQLARRAYTYPECONVERTER_1(Int32)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int32, Byte)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int32, Int16)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int32, Int64)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int32, Single)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int32, Double)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int32, SqlComplex<Single>)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int32, SqlComplex<Double>)

	SPECIALIZE_SQLARRAYTYPECONVERTER_1(Int64)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int64, Byte)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int64, Int16)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int64, Int32)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int64, Single)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int64, Double)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int64, SqlComplex<Single>)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Int64, SqlComplex<Double>)

	SPECIALIZE_SQLARRAYTYPECONVERTER_1(Single)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Single, Double)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Single, SqlComplex<Single>)

	SPECIALIZE_SQLARRAYTYPECONVERTER_1(Double)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Double, Single)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Double, SqlComplex<Single>)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Double, SqlComplex<Double>)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(Double, SqlComplex<Double>)

	SPECIALIZE_SQLARRAYTYPECONVERTER_1(SqlComplex<Single>)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(SqlComplex<Single>, SqlComplex<Double>)

	SPECIALIZE_SQLARRAYTYPECONVERTER_1(SqlComplex<Double>)
	SPECIALIZE_SQLARRAYTYPECONVERTER_2(SqlComplex<Double>, SqlComplex<Single>)
	
}
} }