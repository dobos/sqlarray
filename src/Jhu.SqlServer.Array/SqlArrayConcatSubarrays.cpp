#include "stdafx.h"
#include "SqlArrayConcatSubarrays.h"

namespace Jhu { namespace SqlServer { namespace Array
{

	template <class T, class B>
	void SqlArrayConcatSubarrays<T, B>::Init()
	{
		initialized = false;
	}

	template <class T, class B>
	void SqlArrayConcatSubarrays<T, B>::Accumulate(typename ShortArray::SqlBufferT length, typename ShortArray::SqlBufferT index, typename B::SqlBufferT value)
	{
		if (!initialized)
		{
			array<B::IndexT>^ len = (array<B::IndexT>^)SqlArray<B::IndexT, ShortArray>(length).ToArray();
			data = SqlArray<T, B>(len);

			initialized = true;
		}

		array<B::IndexT>^ ix = (array<B::IndexT>^)SqlArray<B::IndexT, ShortArray>(index).ToArray();
		SqlArray<T, B> sa(value);

		data.SetSubarray(ix, sa);
	}

	template <class T, class B>
	void SqlArrayConcatSubarrays<T, B>::Merge(SqlArrayConcatSubarrays group)
	{
		if (group.initialized)
		{
			// Merge two arrays by adding values
			// This will cause problems with duplicate rows, processing order is undeterministic!
			interior_ptr<T> sp = group.data.GetDataPointer();
			interior_ptr<T> dp = data.GetDataPointer();

			for (B::IndexT i = 0; i < data.m_length; i ++)
			{
				*dp++ += *sp;
			}
		}
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayConcatSubarrays<T, B>::Terminate()
	{
		return data.ToSqlBuffer();
	}

	template <class T, class B>
	void SqlArrayConcatSubarrays<T, B>::Read(System::IO::BinaryReader^ r)
	{
		if (r->BaseStream->Length == 0)
		{
			initialized = false;
		}
		else
		{
			initialized = true;

			array<B::BufferT>^ buffer = gcnew array<B::BufferT>((int)r->BaseStream->Length); 
			r->Read(buffer, 0, buffer->Length);

			data.InitBuffer(buffer);
		}
	}

	template <class T, class B>
	void SqlArrayConcatSubarrays<T, B>::Write(System::IO::BinaryWriter^ w)
	{
		if (initialized)
		{
			w->Write(data.m_buffer);
		}
	}

#define SPECIALIZE_SQLARRAYCONCATSUBARRAYS(T) \
	template Jhu::SqlServer::Array::SqlArrayConcatSubarrays<T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArrayConcatSubarrays<T, MaxArray>;


	SPECIALIZE_SQLARRAYCONCATSUBARRAYS(Byte)
	SPECIALIZE_SQLARRAYCONCATSUBARRAYS(Int16)
	SPECIALIZE_SQLARRAYCONCATSUBARRAYS(Int32)
	SPECIALIZE_SQLARRAYCONCATSUBARRAYS(Int64)
	SPECIALIZE_SQLARRAYCONCATSUBARRAYS(Single)
	SPECIALIZE_SQLARRAYCONCATSUBARRAYS(Double)
	SPECIALIZE_SQLARRAYCONCATSUBARRAYS(SqlComplex<Single>)
	SPECIALIZE_SQLARRAYCONCATSUBARRAYS(SqlComplex<Double>)

}
} }