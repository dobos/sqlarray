#include "stdafx.h"
#include "SqlArrayCultureFormatter.h"

namespace Jhu { namespace SqlServer { namespace Array 
{

	template <typename T>
	String^ SqlArrayCultureFormatter::ToString(T obj, IFormatProvider^ formatProvider)
	{
		return obj.ToString(formatProvider);
	}

	//Could not use an overloaded function, since the template argument deduction does not work here
	//So explicit template specialization had to be done
	template <>
	String^ SqlArrayCultureFormatter::ToString(SqlComplex<Single> obj, IFormatProvider^ formatProvider)
	{
		return obj.ToStringWithProvider(formatProvider);
	}

	template <>
	String^ SqlArrayCultureFormatter::ToString(SqlComplex<Double> obj, IFormatProvider^ formatProvider)
	{
		return obj.ToStringWithProvider(formatProvider);
	}

	template <typename T>
	T SqlArrayCultureFormatter::Parse(String^ value, IFormatProvider^ formatProvider)
	{
		return T::Parse(value, formatProvider);
	}

	//Could not use an overloaded function, since the template argument deduction does not work here
	//So explicit template specialization had to be done
	template <>
	SqlComplex<Single> SqlArrayCultureFormatter::Parse(String^ value, IFormatProvider^ formatProvider)
	{
		return SqlComplex<Single>::ParseWithProvider(value, formatProvider);
	}

	template <>
	SqlComplex<Double> SqlArrayCultureFormatter::Parse(String^ value, IFormatProvider^ formatProvider)
	{
		return SqlComplex<Double>::ParseWithProvider(value, formatProvider);
	}

	// ---- Template specializations
#define SPECIALIZE_SQLARRAYCULTUREFORMATTER(T) \
	template String^ SqlArrayCultureFormatter::ToString(T, IFormatProvider^); \
	template T SqlArrayCultureFormatter::Parse(String^, IFormatProvider^);

	SPECIALIZE_SQLARRAYCULTUREFORMATTER(Byte)
	SPECIALIZE_SQLARRAYCULTUREFORMATTER(Int16)
	SPECIALIZE_SQLARRAYCULTUREFORMATTER(Int32)
	SPECIALIZE_SQLARRAYCULTUREFORMATTER(Int64)
	SPECIALIZE_SQLARRAYCULTUREFORMATTER(Single)
	SPECIALIZE_SQLARRAYCULTUREFORMATTER(Double)
	/*
	//These are explicitly specialized
	SPECIALIZE_SQLARRAYCULTUREFORMATTER(SqlComplex<Single>)
	SPECIALIZE_SQLARRAYCULTUREFORMATTER(SqlComplex<Double>)
	*/
	

} } }