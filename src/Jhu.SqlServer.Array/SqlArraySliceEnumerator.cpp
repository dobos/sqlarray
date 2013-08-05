#include "stdafx.h"
#include "SqlArraySliceEnumerator.h"

namespace Jhu { namespace SqlServer { namespace Array
{
	template <class T, class B>
	array<typename B::IndexT>^ SqlArraySliceEnumerator<T, B>::Offset::get()
	{
		return offset;
	}

	template <class T, class B>
	void SqlArraySliceEnumerator<T, B>::Offset::set(array<typename B::IndexT>^ value)
	{
		offset = value;

		if (offset->Length != dataLength->Length)
		{
			throw gcnew ArgumentOutOfRangeException();	//***
		}
	}

	template <class T, class B>
	array<typename B::IndexT>^ SqlArraySliceEnumerator<T, B>::Length::get()
	{
		return length;
	}

	template <class T, class B>
	void SqlArraySliceEnumerator<T, B>::Length::set(array<typename B::IndexT>^ value)
	{
		length = value;

		if (length->Length != dataLength->Length)
		{
			throw gcnew ArgumentOutOfRangeException();	//***
		}
	}

	template <class T, class B>
	bool SqlArraySliceEnumerator<T, B>::Collapse::get()
	{
		return collapse;
	}

	template <class T, class B>
	void SqlArraySliceEnumerator<T, B>::Collapse::set(bool value)
	{
		collapse = value;
	}

	// ---

	template <class T, class B>
	SqlArraySliceEnumerator<T, B>::SqlArraySliceEnumerator(SqlArray<T, B> data)
	{
		this->data = data;

		this->current = nullptr;
		this->dataLength = data.GetLengths();
	}

	template <class T, class B>
	Object^ SqlArraySliceEnumerator<T, B>::Current::get()
	{
		return Current2::get();
	}

	template <class T, class B>
	SqlIndexItemPair<SqlArray<T, B>, B> SqlArraySliceEnumerator<T, B>::Current2::get()
	{
		for (B::RankT r = 0; r < start->Length; r++)
		{
			start[r] = offset[r] + current[r] * length[r];
		}

		return SqlIndexItemPair<SqlArray<T, B>, B>(start, current, data.GetSubarray(start, length, collapse));
	}

	template <class T, class B>
	bool SqlArraySliceEnumerator<T, B>::MoveNext()
	{
		if (current == nullptr)
		{
			current = gcnew array<B::IndexT>(data.m_rank);
			start = gcnew array<B::IndexT>(data.m_rank);
			slices = gcnew array<B::IndexT>(data.m_rank);
			
			// Compute number of blocks along each rank
			bool hasitem = true;
			for (B::RankT r = 0; r < slices->Length; r++)
			{
				slices[r] = (dataLength[r] - offset[r]) / length[r];
				hasitem &= slices[r] > 0;
			}

			return hasitem;
		}

		for (B::RankT r = 0; r < current->Length; r++)
		{
			if (current[r] < slices[r] - 1)
			{
				current[r]++;
				return true;
			}
			else
			{
				if (r == data.m_rank - 1)
				{
					return false;
				}
				else
				{
					current[r] = 0;
				}
			}
		}

		throw gcnew Exception();	//**** should not reach this
	}

	template <class T, class B>
	void SqlArraySliceEnumerator<T, B>::Reset()
	{
		this->current = nullptr;
	}

	template <class T, class B>
	System::Collections::IEnumerator^ SqlArraySliceEnumerator<T, B>::GetEnumerator()
	{
		return this;
	}

	template <class T, class B>
	System::Collections::Generic::IEnumerator<SqlIndexItemPair<SqlArray<T, B>, B>>^ SqlArraySliceEnumerator<T, B>::GetEnumerator2()
	{
		return this;
	}

#define SPECIALIZE_SQLARRAYENUMERATOR(T) \
	template Jhu::SqlServer::Array::SqlArraySliceEnumerator<T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArraySliceEnumerator<T, MaxArray>;


	SPECIALIZE_SQLARRAYENUMERATOR(Byte)
	SPECIALIZE_SQLARRAYENUMERATOR(Int16)
	SPECIALIZE_SQLARRAYENUMERATOR(Int32)
	SPECIALIZE_SQLARRAYENUMERATOR(Int64)
	SPECIALIZE_SQLARRAYENUMERATOR(Single)
	SPECIALIZE_SQLARRAYENUMERATOR(Double)
	SPECIALIZE_SQLARRAYENUMERATOR(SqlComplex<Single>)
	SPECIALIZE_SQLARRAYENUMERATOR(SqlComplex<Double>)

}
} }