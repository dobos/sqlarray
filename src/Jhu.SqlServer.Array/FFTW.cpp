#include "stdafx.h"
#include "macro.h"
#include "FFTW.h"
#include "ShortArray.h"
#include "MaxArray.h"

namespace Jhu { namespace SqlServer { namespace Array
{

	template <class T, class B>
	SqlArray<SqlComplex<T>, B> FFTW<T, B>::ComplexToComplex(SqlArray<SqlComplex<T>, B> data, fftw_direction direction)
	{
		IntPtr in = FFTWWrapper<T>::Malloc(sizeof(SqlComplex<T>) * data.m_length);
		IntPtr out = FFTWWrapper<T>::Malloc(sizeof(SqlComplex<T>) * data.m_length);

		SqlComplex<T>* pin = (SqlComplex<T>*)in.ToPointer();
		SqlComplex<T>* pout = (SqlComplex<T>*)out.ToPointer();
		interior_ptr<SqlComplex<T>> dp = data.GetDataPointer();

		for (int i = 0; i < data.m_length; i ++)
		{
			*pin++ = *dp++;
		}

		FFTWWrapper<T>::ComplexToComplex(
			data.m_rank,
			data.GetLengths(),
			in,
			out,
			direction);

		// Copy data to results		
		SqlArray<SqlComplex<T>, B> res(data.m_length);
		interior_ptr<SqlComplex<T>> rp = res.GetDataPointer();

		for (int i = 0; i < data.m_length; i ++)
		{
			*rp++ = *pout++;
		}

		FFTWWrapper<T>::Free(in);
		FFTWWrapper<T>::Free(out);

		return res;
	}

	template <class T, class B>
	SqlArray<SqlComplex<T>, B> FFTW<T, B>::Forward(SqlArray<SqlComplex<T>, B> data)
	{
		return ComplexToComplex(data, fftw_direction::Forward);
	}

	template <class T, class B>
	SqlArray<SqlComplex<T>, B> FFTW<T, B>::Backward(SqlArray<SqlComplex<T>, B> data)
	{
		return ComplexToComplex(data, fftw_direction::Backward);
	}

	template <class T, class B>
	SqlArray<SqlComplex<T>, B> FFTW<T, B>::Forward(SqlArray<T, B> data)
	{
		IntPtr in = FFTWWrapper<T>::Malloc(sizeof(T) * data.m_length);
		IntPtr out = FFTWWrapper<T>::Malloc(sizeof(SqlComplex<T>) * data.m_length);

		T* pin = (T*)in.ToPointer();
		SqlComplex<T>* pout = (SqlComplex<T>*)out.ToPointer();
		interior_ptr<T> dp = data.GetDataPointer();

		for (int i = 0; i < data.m_length; i ++)
		{
			*pin++ = *dp++;
		}

		FFTWWrapper<T>::RealToComplex(
			data.m_rank,
			data.GetLengths(),
			in,
			out);

		// Copy data to results		
		SqlArray<SqlComplex<T>, B> res(data.m_length);
		interior_ptr<SqlComplex<T>> rp = res.GetDataPointer();

		for (int i = 0; i < data.m_length; i ++)
		{
			*rp++ = *pout++;
		}

		FFTWWrapper<T>::Free(in);
		FFTWWrapper<T>::Free(out);

		return res;
	}

	// ---

	template <>
	void FFTWWrapper<Double>::ComplexToComplex(int rank, array<int>^ n, IntPtr input, IntPtr output, fftw_direction direction)
	{
		IntPtr plan = (IntPtr)fftw_plan_dft(rank, n, input, output, direction, fftw_flags::Estimate);
		fftw_execute(plan);
		fftw_destroy_plan(plan);
	}

	template <>
	void FFTWWrapper<Double>::RealToComplex(int rank, array<int>^ n, IntPtr input, IntPtr output)
	{
		IntPtr plan = (IntPtr)fftw_plan_dft_r2c(rank, n, input, output, fftw_flags::Estimate);
		fftw_execute(plan);
		fftw_destroy_plan(plan);
	}

	template <>
	IntPtr FFTWWrapper<Double>::Malloc(int size)
	{
		return (IntPtr)fftw_malloc(size);
	}

	template <>
	void FFTWWrapper<Double>::Free(IntPtr p)
	{
		fftw_free(p);
	}

	template <>
	void FFTWWrapper<Single>::ComplexToComplex(int rank, array<int>^ n, IntPtr input, IntPtr output, fftw_direction direction)
	{
		IntPtr plan = (IntPtr)fftwf_plan_dft(rank, n, input, output, direction, fftw_flags::Estimate);
		fftwf_execute(plan);
		fftwf_destroy_plan(plan);
	}

	template <>
	void FFTWWrapper<Single>::RealToComplex(int rank, array<int>^ n, IntPtr input, IntPtr output)
	{
		IntPtr plan = (IntPtr)fftwf_plan_dft_r2c(rank, n, input, output, fftw_flags::Estimate);
		fftwf_execute(plan);
		fftwf_destroy_plan(plan);
	}

	template <>
	IntPtr FFTWWrapper<Single>::Malloc(int size)
	{
		return (IntPtr)fftwf_malloc(size);
	}

	template <>
	void FFTWWrapper<Single>::Free(IntPtr p)
	{
		fftwf_free(p);
	}

	//template FFTW<Single, ShortArray>;
	//template FFTW<Double, ShortArray>;
	template FFTW<Single, MaxArray>;
	template FFTW<Double, MaxArray>;

}
} }