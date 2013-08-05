#include "stdafx.h"
#include "SqlArrayConcat.h"

namespace Jhu { namespace SqlServer { namespace Array
{

	template <class T, class B>
	void SqlArrayConcat<T, B>::Init()
	{
		initialized = false;
	}

	template <class T, class B>
	void SqlArrayConcat<T, B>::Accumulate(typename ShortArray::SqlBufferT length, typename ShortArray::SqlBufferT index, T value)
	{
		if (!initialized)
		{
			initialized = true;
			array<B::IndexT>^ len = (array<B::IndexT>^)SqlArray<B::IndexT, ShortArray>(length).ToArray();
			data = SqlArray<T, B>(len);
		}

		array<B::IndexT>^ ix = (array<B::IndexT>^)SqlArray<B::IndexT, ShortArray>(index).ToArray();

		data[ix] = value;
	}

	template <class T, class B>
	void SqlArrayConcat<T, B>::Merge(SqlArrayConcat group)
	{
		if (group.initialized)
		{
			// Merge two arrays by adding values
			// This will cause problems with duplicate rows
			interior_ptr<T> sp = group.data.GetDataPointer();
			interior_ptr<T> dp = data.GetDataPointer();

			for (B::IndexT i = 0; i < data.m_length; i ++)
			{
				*dp++ += *sp;
			}
		}
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayConcat<T, B>::Terminate()
	{
		return data.ToSqlBuffer();
	}

	template <class T, class B>
	void SqlArrayConcat<T, B>::Read(System::IO::BinaryReader^ r)
	{
		array<B::BufferT>^ buffer = gcnew array<B::BufferT>((int)r->BaseStream->Length); 
		r->Read(buffer, 0, buffer->Length);

		data.InitBuffer(buffer);
	}

	template <class T, class B>
	void SqlArrayConcat<T, B>::Write(System::IO::BinaryWriter^ w)
	{
		w->Write(data.m_buffer);
	}

#define SPECIALIZE_SQLARRAYCONCAT(T) \
	template Jhu::SqlServer::Array::SqlArrayConcat<T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArrayConcat<T, MaxArray>;


	SPECIALIZE_SQLARRAYCONCAT(Byte)
	SPECIALIZE_SQLARRAYCONCAT(Int16)
	SPECIALIZE_SQLARRAYCONCAT(Int32)
	SPECIALIZE_SQLARRAYCONCAT(Int64)
	SPECIALIZE_SQLARRAYCONCAT(Single)
	SPECIALIZE_SQLARRAYCONCAT(Double)
	SPECIALIZE_SQLARRAYCONCAT(SqlComplex<Single>)
	SPECIALIZE_SQLARRAYCONCAT(SqlComplex<Double>)

}
} }