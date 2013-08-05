#include "stdafx.h"
#include "SqlArrayMatrixEnumerator.h"

namespace Jhu { namespace SqlServer { namespace Array
{

	template <class T, class B>
	SqlArrayMatrixEnumerator<T, B>::SqlArrayMatrixEnumerator(SqlArray<T, B> data)
	{
		this->data = data;
		this->dataLength = data.GetLengths();

		this->current = -1;
	}

	template <class T, class B>
	Object^ SqlArrayMatrixEnumerator<T, B>::Current::get()
	{
		return Current2::get();
	}

	template <class T, class B>
	SqlIndexItemPair<array<T>^, B> SqlArrayMatrixEnumerator<T, B>::Current2::get()
	{
		array<T>^ currentvector = gcnew array<T>(dataLength[0]);
		Buffer::BlockCopy(data.m_buffer, data.GetDataOffset() + current * dataLength[0] * sizeof(T), currentvector, 0, dataLength[0] * sizeof(T));

		return SqlIndexItemPair<array<T>^, B>(current, currentvector);
	}

	template <class T, class B>
	bool SqlArrayMatrixEnumerator<T, B>::MoveNext()
	{
		current++;
		return (current < dataLength[1]);
	}

	template <class T, class B>
	void SqlArrayMatrixEnumerator<T, B>::Reset()
	{
		this->current = -1;
	}

	template <class T, class B>
	System::Collections::IEnumerator^ SqlArrayMatrixEnumerator<T, B>::GetEnumerator()
	{
		return this;
	}

	template <class T, class B>
	System::Collections::Generic::IEnumerator<SqlIndexItemPair<array<T>^, B>>^ SqlArrayMatrixEnumerator<T, B>::GetEnumerator2()
	{
		return this;
	}

#define SPECIALIZE_SQLARRAYMATRIXENUMERATOR(T) \
	template Jhu::SqlServer::Array::SqlArrayMatrixEnumerator<T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArrayMatrixEnumerator<T, MaxArray>;


	SPECIALIZE_SQLARRAYMATRIXENUMERATOR(Byte)
	SPECIALIZE_SQLARRAYMATRIXENUMERATOR(Int16)
	SPECIALIZE_SQLARRAYMATRIXENUMERATOR(Int32)
	SPECIALIZE_SQLARRAYMATRIXENUMERATOR(Int64)
	SPECIALIZE_SQLARRAYMATRIXENUMERATOR(Single)
	SPECIALIZE_SQLARRAYMATRIXENUMERATOR(Double)
	SPECIALIZE_SQLARRAYMATRIXENUMERATOR(SqlComplex<Single>)
	SPECIALIZE_SQLARRAYMATRIXENUMERATOR(SqlComplex<Double>)

}
} }