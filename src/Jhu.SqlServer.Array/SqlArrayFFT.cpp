#include "stdafx.h"
#include "macro.h"
#include "ShortArray.h"
#include "MaxArray.h"
#include "SqlArrayAttribute.h"
#include "SqlArray.h"
#include "SqlArrayFFT.h"
#include "FFTW.h"

namespace Jhu { namespace SqlServer { namespace Array
{

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFFT<T, B>::FFTForward(typename B::SqlBufferT data)
	{
		throw gcnew NotImplementedException();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFFT<T, B>::FFTBackward(typename B::SqlBufferT data)
	{
		throw gcnew NotImplementedException();
	}

	template <>
	typename MaxArray::SqlBufferT SqlArrayFFT<Double, MaxArray>::FFTForward(typename MaxArray::SqlBufferT data)
	{
		return FFTW<Double, MaxArray>::Forward(SqlArray<Double, MaxArray>(data, ArrayLoadMethod::AllData)).ToSqlBuffer();
	}


	/*template <class T, class B>
	typename B::SqlBufferT SqlArrayFFT<T, B>::RealToComplex(typename B::SqlBufferT data)
	{
		return FFTW<T, B>::RealToComplex(SqlArray<T, B>(data, ArrayLoadMethod::AllData, 0, 0)).ToSqlBuffer();
	}*/

	/*
	template <class T, class B>
	typename B::SqlBufferT SqlArrayFFT<T, B>::ComplexToComplex(typename B::SqlBufferT data)
	{
		return FFTW<T, B>::ComplexToComplex(SqlArray<SqlComplex<T>, B>(data, ArrayLoadMethod::AllData), Jhu::SqlServer::Array::Wrappers::fftw_direction::Forward).ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFFT<T, B>::ComplexToComplexInverse(typename B::SqlBufferT data)
	{
		return FFTW<T, B>::ComplexToComplex(SqlArray<SqlComplex<T>, B>(data, ArrayLoadMethod::AllData), Jhu::SqlServer::Array::Wrappers::fftw_direction::Backward).ToSqlBuffer();
	}

	/*
	template <class T, class B>
	typename B::SqlBufferT SqlArrayFFT<T, B>::ComplexToReal(typename B::SqlBufferT data)
	{
		return FFTW<T, B>::ComplexToReal(SqlArray<SqlComplex<T>, B>(data, ArrayLoadMethod::AllData, 0, 0)).ToSqlBuffer();
	}*/

	template SqlArrayFFT<Double, MaxArray>;
}
} }