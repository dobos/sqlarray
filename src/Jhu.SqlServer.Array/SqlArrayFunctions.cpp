#include "stdafx.h"
#include "SqlArrayFunctions.h"

namespace Jhu { namespace SqlServer { namespace Array
{

#pragma region String conversion functions

	template <class T, class B>
	SqlChars^ SqlArrayFunctions<T, B>::GetString(typename B::SqlBufferT data)
	{
		return gcnew SqlChars(SqlArray<T, B>(data, ArrayLoadMethod::AllData).ToString(Globalization::CultureInfo::CurrentCulture));
	}

	template <class T, class B>
	SqlChars^ SqlArrayFunctions<T, B>::GetStringInvariant(typename B::SqlBufferT data)
	{
		return gcnew SqlChars(SqlArray<T, B>(data, ArrayLoadMethod::AllData).ToString(Globalization::CultureInfo::InvariantCulture));
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Parse(SqlChars^ data)
	{
		return SqlArray<T, B>::FromString(data->ToSqlString().Value, Globalization::CultureInfo::CurrentCulture).ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::ParseInvariant(SqlChars^ data)
	{
		return SqlArray<T, B>::FromString(data->ToSqlString().Value, Globalization::CultureInfo::InvariantCulture).ToSqlBuffer();
	}
	
#pragma endregion
#pragma region Basic array constructors

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Vector_1(PARLIST_1(T, v))
	{
		SqlArray<T, B> u(1);
		u.WriteData(VARLIST_1(v));
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Vector_2(PARLIST_2(T, v))
	{
		SqlArray<T, B> u(2);
		u.WriteData(VARLIST_2(v));
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Vector_3(PARLIST_3(T, v))
	{
		SqlArray<T, B> u(3);
		u.WriteData(VARLIST_3(v));
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Vector_4(PARLIST_4(T, v))
	{
		SqlArray<T, B> u(4);
		u.WriteData(VARLIST_4(v));
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Vector_5(PARLIST_5(T, v))
	{
		SqlArray<T, B> u(5);
		u.WriteData(VARLIST_5(v));
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Vector_6(PARLIST_6(T, v))
	{
		SqlArray<T, B> u(6);
		u.WriteData(VARLIST_6(v));
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Vector_7(PARLIST_7(T, v))
	{
		SqlArray<T, B> u(7);
		u.WriteData(VARLIST_7(v));
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Vector_8(PARLIST_8(T, v))
	{
		SqlArray<T, B> u(8);
		u.WriteData(VARLIST_8(v));
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Vector_9(PARLIST_9(T, v))
	{
		SqlArray<T, B> u(9);
		u.WriteData(VARLIST_9(v));
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Vector_10(PARLIST_10(T, v))
	{
		SqlArray<T, B> u(10);
		u.WriteData(VARLIST_10(v));
		return u.ToSqlBuffer();
	}

	//--

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Matrix_2(PARLIST_4(T, v))
	{
		SqlArray<T, B> u(2, 2);
		u.WriteData(VARLIST_4(v));
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Matrix_3(PARLIST_9(T, v))
	{
		SqlArray<T, B> u(3, 3);
		u.WriteData(VARLIST_9(v));
		return u.ToSqlBuffer();
	}

#pragma endregion
#pragma region Array properties

	template <class T, class B>
	typename B::RankT SqlArrayFunctions<T, B>::Rank(typename B::SqlBufferT data)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		return u.m_rank;
	}

	template <class T, class B>
	typename B::IndexT SqlArrayFunctions<T, B>::TotalLength(typename B::SqlBufferT data)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		return u.m_length;
	}

	template <class T, class B>
	typename B::IndexT SqlArrayFunctions<T, B>::Length(typename B::SqlBufferT data, typename B::RankT i)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		return u.GetLengths()[i];
	}

	template <class T, class B>
	typename ShortArray::SqlBufferT SqlArrayFunctions<T, B>::Lengths(typename B::SqlBufferT data)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		return SqlArray<typename B::IndexT, ShortArray>::FromArray(u.GetLengths()).ToSqlBuffer();
	}

#pragma endregion
#pragma region Buffer manipulation functions

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Cast(typename B::SqlBufferT data, typename B::IndexT offset, typename ShortArray::SqlBufferT length)
	{
		array<B::IndexT>^ ilength = SqlArray<B::IndexT, ShortArray>(length).ToArray();
		SqlArray<T, B> u(ilength);
		u.CastBuffer(B::GetBuffer(data, ArrayLoadMethod::AllData), offset);
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Raw(typename B::SqlBufferT data)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);
		array<B::BufferT>^ buffer = gcnew array<B::BufferT>(u.m_length * sizeof(T));
		Buffer::BlockCopy(u.m_buffer, u.GetDataOffset(), buffer, 0, buffer->Length);
		return B::ToSqlBuffer(buffer);
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Reshape(typename B::SqlBufferT data, typename ShortArray::SqlBufferT length)
	{
		array<typename B::IndexT>^ ilength = SqlArray<typename B::IndexT, ShortArray>(length).ToArray();
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);

		u.Reshape(ilength);

		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Transpose(typename B::SqlBufferT data)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);

		return u.Transpose().ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Permute(typename B::SqlBufferT data, typename ShortArray::SqlBufferT indexlist)
	{
		array<typename B::RankT>^ il = SqlArray<typename B::RankT, ShortArray>(indexlist).ToArray();
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);

		return u.Permute(il).ToSqlBuffer();
	}

#pragma endregion
#pragma region Item accessors

	template <class T, class B>
	T SqlArrayFunctions<T, B>::Empty(typename B::SqlBufferT data, PARLIST_1(typename B::IndexT, i))
	{
		return (T)0;
	}

	template <class T, class B>
	T SqlArrayFunctions<T, B>::Item(typename B::SqlBufferT data, typename B::IndexT index)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		u.LoadData(data, index);
		return u.GetDataPointer()[index];
	}

	template <class T, class B>
	T SqlArrayFunctions<T, B>::Item_N(typename B::SqlBufferT data, typename ShortArray::SqlBufferT indexes)
	{
		SqlArray<typename B::IndexT, ShortArray> i(indexes);
		
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		typename B::IndexT index = u.GetLinearIndex(i.ToArray());
		u.LoadData(data, index);
		return u.GetDataPointer()[index];
	}

	template <class T, class B>
	T SqlArrayFunctions<T, B>::Item_1(typename B::SqlBufferT data, PARLIST_1(typename B::IndexT, i))
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		typename B::IndexT index = u.GetLinearIndex(VARLIST_1(i));
		u.LoadData(data, index);
		return u.GetDataPointer()[index];
	}

	template <class T, class B>
	T SqlArrayFunctions<T, B>::Item_2(typename B::SqlBufferT data, PARLIST_2(typename B::IndexT, i))
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		typename B::IndexT index = u.GetLinearIndex(VARLIST_2(i));
		u.LoadData(data, index);
		return u.GetDataPointer()[index];
	}

	template <class T, class B>
	T SqlArrayFunctions<T, B>::Item_3(typename B::SqlBufferT data, PARLIST_3(typename B::IndexT, i))
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		typename B::IndexT index = u.GetLinearIndex(VARLIST_3(i));
		u.LoadData(data, index);
		return u.GetDataPointer()[index];
	}

		template <class T, class B>
	T SqlArrayFunctions<T, B>::Item_4(typename B::SqlBufferT data, PARLIST_4(typename B::IndexT, i))
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		typename B::IndexT index = u.GetLinearIndex(VARLIST_4(i));
		u.LoadData(data, index);
		return u.GetDataPointer()[index];
	}

		template <class T, class B>
	T SqlArrayFunctions<T, B>::Item_5(typename B::SqlBufferT data, PARLIST_5(typename B::IndexT, i))
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		typename B::IndexT index = u.GetLinearIndex(VARLIST_5(i));
		u.LoadData(data, index);
		return u.GetDataPointer()[index];
	}

		template <class T, class B>
	T SqlArrayFunctions<T, B>::Item_6(typename B::SqlBufferT data, PARLIST_6(typename B::IndexT, i))
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		typename B::IndexT index = u.GetLinearIndex(VARLIST_6(i));
		u.LoadData(data, index);
		return u.GetDataPointer()[index];
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateItem(typename B::SqlBufferT data, typename B::IndexT index, T value)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);
		u.GetDataPointer()[index] = value;
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateItem_N(typename B::SqlBufferT data, typename ShortArray::SqlBufferT indexes, T value)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);
		SqlArray<typename B::IndexT, ShortArray> i(indexes);
		typename B::IndexT index = u.GetLinearIndex(i.ToArray());
		u.GetDataPointer()[index] = value;
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateItem_1(typename B::SqlBufferT data, PARLIST_1(typename B::IndexT, i), T value)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);
		u.GetDataPointer()[u.GetLinearIndex(VARLIST_1(i))] = value;
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateItem_2(typename B::SqlBufferT data, PARLIST_2(typename B::IndexT, i), T value)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);
		u.GetDataPointer()[u.GetLinearIndex(VARLIST_2(i))] = value;
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateItem_3(typename B::SqlBufferT data, PARLIST_3(typename B::IndexT, i), T value)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);
		u.GetDataPointer()[u.GetLinearIndex(VARLIST_3(i))] = value;
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateItem_4(typename B::SqlBufferT data, PARLIST_4(typename B::IndexT, i), T value)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);
		u.GetDataPointer()[u.GetLinearIndex(VARLIST_4(i))] = value;
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateItem_5(typename B::SqlBufferT data, PARLIST_5(typename B::IndexT, i), T value)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);
		u.GetDataPointer()[u.GetLinearIndex(VARLIST_5(i))] = value;
		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateItem_6(typename B::SqlBufferT data, PARLIST_6(typename B::IndexT, i), T value)
	{
		SqlArray<T, B> u(data, ArrayLoadMethod::AllData);
		u.GetDataPointer()[u.GetLinearIndex(VARLIST_6(i))] = value;
		return u.ToSqlBuffer();
	}

#pragma endregion
#pragma region Multiple item accessors

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Items(typename B::SqlBufferT data, typename B::SqlBufferT indexes)
	{
		SqlArray<T, B> d(data);
		SqlArray<B::IndexT, B> ix(indexes);

		array<B::IndexT>^ ixlen = ix.GetLengths();

		// Check index array format
		if (ixlen->Length != 2)
		{
			throw gcnew SqlArrayException("Array indexing elements must be two dimensional.");	// ****
		}
		if (ixlen[0] != d.m_rank)
		{
			throw gcnew SqlArrayException("Dimension of the indexed array and dimension of the indices do not match");	// ****
		}

		array<array<B::IndexT>^>^ ixa = (array<array<B::IndexT>^>^)ix.ToJaggedArray();

		return d.GetItems(ixa).ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateItems(typename B::SqlBufferT data, typename B::SqlBufferT indexes, typename B::SqlBufferT values)
	{
		SqlArray<T, B> d(data);

		// Indexes

		SqlArray<B::IndexT, B> ix(indexes);
		array<B::IndexT>^ ixlen = ix.GetLengths();

		// --- Check index array format
		if (ixlen->Length != 2)
		{
			throw gcnew SqlArrayException("Array indexing elements must be two dimensional.");	// ****
		}
		if (ixlen[0] != d.m_rank)
		{
			throw gcnew SqlArrayException("Dimension of the indexed array and dimension of the indices do not match");	// ****
		}

		array<array<B::IndexT>^>^ ixa = (array<array<B::IndexT>^>^)ix.ToJaggedArray();

		// Values
		SqlArray<T, B> v(values);
		array<T>^ va = v.ToArray();


		// --- Check compatibility
		if (ixa->Length != va->Length)
		{
			throw gcnew SqlArrayException("Number of indices and number of values do not match.");	// ****
		}

		//
		d.SetItems(ixa, va);

		return d.ToSqlBuffer();
	}

#pragma endregion
#pragma region Subarray manipulation functions

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Subarray(typename B::SqlBufferT data, typename ShortArray::SqlBufferT offset, typename ShortArray::SqlBufferT length, Int16 collapse)
	{
		array<B::IndexT>^ ioffset = SqlArray<B::IndexT, ShortArray>(offset).ToArray();
		array<B::IndexT>^ ilength = SqlArray<B::IndexT, ShortArray>(length).ToArray();
		
		// Compute last item to be loaded
		array<B::IndexT>^ ito = gcnew array<B::IndexT>(ioffset->Length);
		for (B::IndexT i = 0; i < ito->Length; i ++)
		{
			ito[i] = ioffset[i] + ilength[i] - 1;
		}

		SqlArray<T, B> u(data, ArrayLoadMethod::HeaderOnly);
		u.LoadData(data, ioffset, ito);
		return u.GetSubarray(ioffset, ilength, collapse != 0).ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Subarrays(typename B::SqlBufferT data, typename B::SqlBufferT offsets, typename ShortArray::SqlBufferT length, Int16 collapse)
	{
		array<array<B::IndexT>^>^ ixa = (array<array<B::IndexT>^>^)SqlArray<B::IndexT, B>(offsets).ToJaggedArray();
		array<B::IndexT>^ lena = (array<B::IndexT>^)SqlArray<B::IndexT, ShortArray>(length).ToArray();

		// Determine the first and last item to be loaded
		array<B::IndexT>^ imin = gcnew array<B::IndexT>(lena->Length);
		array<B::IndexT>^ imax = gcnew array<B::IndexT>(lena->Length);
		
		for (B::IndexT k = 0; k < ixa->Length; k++)
		{
			for (B::RankT i = 0; i < imin->Length; i ++)
			{
				imin[i] = imin[i] < ixa[k][i] ? imin[i] : ixa[k][i];
				imax[i] = imax[i] > ixa[k][i] + lena[i] - 1 ? imax[i] : ixa[k][i] + lena[i] - 1;
			}
		}

		// Load main array
		SqlArray<T, B> d(data, ArrayLoadMethod::HeaderOnly);
		d.LoadData(data, imin, imax);

		return d.GetSubarrays(ixa, lena, collapse != 0).ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateSubarray(typename B::SqlBufferT data, typename ShortArray::SqlBufferT offset, typename B::SqlBufferT value)
	{
		// Load original array
		SqlArray<T, B> d(data);

		// Load index array and subarray
		array<B::IndexT>^ ix = (array<B::IndexT>^)SqlArray<B::IndexT, ShortArray>(offset).ToArray();
		SqlArray<T, B> sa(value);

		// Update subarray
		d.SetSubarray(ix, sa);

		// Return results
		return d.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::UpdateSubarrays(typename B::SqlBufferT data, typename B::SqlBufferT offsets, typename B::SqlBufferT values)
	{
		// Offsets to insert at
		array<array<B::IndexT>^>^ ixa = (array<array<B::IndexT>^>^)SqlArray<B::IndexT, B>(offsets).ToJaggedArray();

		// Original array
		SqlArray<T, B> d(data);

		// Subarrays to insert
		SqlArray<T, B> sa(values);

		d.SetSubarrays(ixa, sa);

		return d.ToSqlBuffer();
	}

#pragma endregion
#pragma region Array to table functions

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::ToTable(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayEnumerator<T, B>(SqlArray<T, B>(data));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::ToTable_FillRow(Object^ o, typename B::IndexT% li, typename ShortArray::SqlBufferT% i, T% v)
	{
		SqlIndexItemPair<T, B> p = (SqlIndexItemPair<T, B>)o;
		li = p.LinearIndex;
		i = SqlArray<B::IndexT, ShortArray>::FromArray(p.Index).ToSqlBuffer();
		v = p.Item;
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::ToTable_1(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::ToTable_1_FillRow(Object^ o, typename B::IndexT% li, PARLIST_1(typename B::IndexT%, i), T% v)
	{
		SqlIndexItemPair<T, B> p = (SqlIndexItemPair<T, B>)o;
		li = p.LinearIndex;
		i0 = p.Index[0];
		v = p.Item;
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::ToTable_2(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::ToTable_2_FillRow(Object^ o, typename B::IndexT% li, PARLIST_2(typename B::IndexT%, i), T% v)
	{
		SqlIndexItemPair<T, B> p = (SqlIndexItemPair<T, B>)o;
		li = p.LinearIndex;
		i0 = p.Index[0];
		i1 = p.Index[1];
		v = p.Item;
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::ToTable_3(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::ToTable_3_FillRow(Object^ o, typename B::IndexT% li, PARLIST_3(typename B::IndexT%, i), T% v)
	{
		SqlIndexItemPair<T, B> p = (SqlIndexItemPair<T, B>)o;
		li = p.LinearIndex;
		i0 = p.Index[0];
		i1 = p.Index[1];
		i2 = p.Index[2];
		v = p.Item;
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::ToTable_4(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::ToTable_4_FillRow(Object^ o, typename B::IndexT% li, PARLIST_4(typename B::IndexT%, i), T% v)
	{
		SqlIndexItemPair<T, B> p = (SqlIndexItemPair<T, B>)o;
		li = p.LinearIndex;
		i0 = p.Index[0];
		i1 = p.Index[1];
		i2 = p.Index[2];
		i3 = p.Index[3];
		v = p.Item;
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::ToTable_5(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::ToTable_5_FillRow(Object^ o, typename B::IndexT% li, PARLIST_5(typename B::IndexT%, i), T% v)
	{
		SqlIndexItemPair<T, B> p = (SqlIndexItemPair<T, B>)o;
		li = p.LinearIndex;
		i0 = p.Index[0];
		i1 = p.Index[1];
		i2 = p.Index[2];
		i3 = p.Index[3];
		i4 = p.Index[4];
		v = p.Item;
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::ToTable_6(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::ToTable_6_FillRow(Object^ o, typename B::IndexT% li, PARLIST_6(typename B::IndexT%, i), T% v)
	{
		SqlIndexItemPair<T, B> p = (SqlIndexItemPair<T, B>)o;
		li = p.LinearIndex;
		i0 = p.Index[0];
		i1 = p.Index[1];
		i2 = p.Index[2];
		i3 = p.Index[3];
		i4 = p.Index[4];
		i5 = p.Index[5];
		v = p.Item;
	}


	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::MatrixToTable_2(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayMatrixEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::MatrixToTable_2_FillRow(Object^ o, typename B::IndexT% i, PARLIST_2(T%, v))
	{
		SqlIndexItemPair<array<T>^, B> p = (SqlIndexItemPair<array<T>^, B>)o;
		i = p.LinearIndex;
		v0 = p.Item[0];
		v1 = p.Item[1];
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::MatrixToTable_3(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayMatrixEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::MatrixToTable_3_FillRow(Object^ o, typename B::IndexT% i, PARLIST_3(T%, v))
	{
		SqlIndexItemPair<array<T>^, B> p = (SqlIndexItemPair<array<T>^, B>)o;
		i = p.LinearIndex;
		v0 = p.Item[0];
		v1 = p.Item[1];
		v2 = p.Item[2];
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::MatrixToTable_4(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayMatrixEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::MatrixToTable_4_FillRow(Object^ o, typename B::IndexT% i, PARLIST_4(T%, v))
	{
		SqlIndexItemPair<array<T>^, B> p = (SqlIndexItemPair<array<T>^, B>)o;
		i = p.LinearIndex;
		v0 = p.Item[0];
		v1 = p.Item[1];
		v2 = p.Item[2];
		v3 = p.Item[3];
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::MatrixToTable_5(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayMatrixEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::MatrixToTable_5_FillRow(Object^ o, typename B::IndexT% i, PARLIST_5(T%, v))
	{
		SqlIndexItemPair<array<T>^, B> p = (SqlIndexItemPair<array<T>^, B>)o;
		i = p.LinearIndex;
		v0 = p.Item[0];
		v1 = p.Item[1];
		v2 = p.Item[2];
		v3 = p.Item[3];
		v4 = p.Item[4];
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::MatrixToTable_6(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayMatrixEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::MatrixToTable_6_FillRow(Object^ o, typename B::IndexT% i, PARLIST_6(T%, v))
	{
		SqlIndexItemPair<array<T>^, B> p = (SqlIndexItemPair<array<T>^, B>)o;
		i = p.LinearIndex;
		v0 = p.Item[0];
		v1 = p.Item[1];
		v2 = p.Item[2];
		v3 = p.Item[3];
		v4 = p.Item[4];
		v5 = p.Item[5];
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::MatrixToTable_7(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayMatrixEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::MatrixToTable_7_FillRow(Object^ o, typename B::IndexT% i, PARLIST_7(T%, v))
	{
		SqlIndexItemPair<array<T>^, B> p = (SqlIndexItemPair<array<T>^, B>)o;
		i = p.LinearIndex;
		v0 = p.Item[0];
		v1 = p.Item[1];
		v2 = p.Item[2];
		v3 = p.Item[3];
		v4 = p.Item[4];
		v5 = p.Item[5];
		v6 = p.Item[6];
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::MatrixToTable_8(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayMatrixEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::MatrixToTable_8_FillRow(Object^ o, typename B::IndexT% i, PARLIST_8(T%, v))
	{
		SqlIndexItemPair<array<T>^, B> p = (SqlIndexItemPair<array<T>^, B>)o;
		i = p.LinearIndex;
		v0 = p.Item[0];
		v1 = p.Item[1];
		v2 = p.Item[2];
		v3 = p.Item[3];
		v4 = p.Item[4];
		v5 = p.Item[5];
		v6 = p.Item[6];
		v7 = p.Item[7];
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::MatrixToTable_9(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayMatrixEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::MatrixToTable_9_FillRow(Object^ o, typename B::IndexT% i, PARLIST_9(T%, v))
	{
		SqlIndexItemPair<array<T>^, B> p = (SqlIndexItemPair<array<T>^, B>)o;
		i = p.LinearIndex;
		v0 = p.Item[0];
		v1 = p.Item[1];
		v2 = p.Item[2];
		v3 = p.Item[3];
		v4 = p.Item[4];
		v5 = p.Item[5];
		v6 = p.Item[6];
		v7 = p.Item[7];
		v8 = p.Item[8];
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::MatrixToTable_10(typename B::SqlBufferT data)
	{
		return gcnew SqlArrayMatrixEnumerator<T, B>(SqlArray<T, B>(data, ArrayLoadMethod::AllData));
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::MatrixToTable_10_FillRow(Object^ o, typename B::IndexT% i, PARLIST_10(T%, v))
	{
		SqlIndexItemPair<array<T>^, B> p = (SqlIndexItemPair<array<T>^, B>)o;
		i = p.LinearIndex;
		v0 = p.Item[0];
		v1 = p.Item[1];
		v2 = p.Item[2];
		v3 = p.Item[3];
		v4 = p.Item[4];
		v5 = p.Item[5];
		v6 = p.Item[6];
		v7 = p.Item[7];
		v8 = p.Item[8];
		v9 = p.Item[9];
	}

	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::Split(typename B::SqlBufferT data, typename ShortArray::SqlBufferT offset, typename ShortArray::SqlBufferT length, Int16 collapse)
	{
		SqlArray<T, B> d(data);
		SqlArraySliceEnumerator<T, B>^ en = gcnew SqlArraySliceEnumerator<T, B>(d);

		en->Offset = (array<B::IndexT>^)SqlArray<B::IndexT, ShortArray>(offset).ToArray();
		en->Length = (array<B::IndexT>^)SqlArray<B::IndexT, ShortArray>(length).ToArray();
		en->Collapse = (collapse != 0);

		return en;
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::Split_FillRow(Object^ o, typename ShortArray::SqlBufferT% ci, typename ShortArray::SqlBufferT% i, typename B::SqlBufferT% v)
	{
		SqlIndexItemPair<SqlArray<T, B>, B> p = (SqlIndexItemPair<SqlArray<T, B>, B>)o;

		ci = SqlArray<B::IndexT, ShortArray>::FromArray(p.CollapsedIndex).ToSqlBuffer();
		i = SqlArray<B::IndexT, ShortArray>::FromArray(p.Index).ToSqlBuffer();
		v = p.Item.ToSqlBuffer();
	}


	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::ItemsToTable(typename B::SqlBufferT data, typename B::SqlBufferT indexes)
	{
		SqlArray<T, B> d(data);
		array<array<B::IndexT>^>^ ixa = (array<array<B::IndexT>^>^)SqlArray<B::IndexT, B>(indexes).ToJaggedArray();
		
		SqlArrayItemEnumerator<T, B>^ en = gcnew SqlArrayItemEnumerator<T, B>(d, ixa);

		return en;
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::ItemsToTable_FillRow(Object^ o, typename B::IndexT% li, typename ShortArray::SqlBufferT% i, typename T% v)
	{
		SqlIndexItemPair<T, B> p = (SqlIndexItemPair<T, B>)o;

		li = p.LinearIndex;
		i = SqlArray<B::IndexT, ShortArray>::FromArray(p.Index).ToSqlBuffer();
		v = p.Item;
	}


	template <class T, class B>
	System::Collections::IEnumerable^ SqlArrayFunctions<T, B>::SubarraysToTable(typename B::SqlBufferT data, typename B::SqlBufferT offsets, typename ShortArray::SqlBufferT length, Int16 collapse)
	{
		
		array<array<B::IndexT>^>^ ixa = (array<array<B::IndexT>^>^)SqlArray<B::IndexT, B>(offsets).ToJaggedArray();
		array<B::IndexT>^ lena = (array<B::IndexT>^)SqlArray<B::IndexT, ShortArray>(length).ToArray();

		// Determine the first and last item to be loaded
		array<B::IndexT>^ imin = gcnew array<B::IndexT>(lena->Length);
		array<B::IndexT>^ imax = gcnew array<B::IndexT>(lena->Length);
		
		for (B::IndexT k = 0; k < ixa->Length; k++)
		{
			for (B::RankT i = 0; i < imin->Length; i ++)
			{
				imin[i] = imin[i] < ixa[k][i] ? imin[i] : ixa[k][i];
				imax[i] = imax[i] > ixa[k][i] + lena[i] - 1 ? imax[i] : ixa[k][i] + lena[i] - 1;
			}
		}

		SqlArray<T, B> d(data, ArrayLoadMethod::HeaderOnly);
		d.LoadData(data, imin, imax);

		SqlArraySubarrayEnumerator<T, B>^ en = gcnew SqlArraySubarrayEnumerator<T, B>(d, ixa);
		en->Length = lena;
		en->Collapse = (collapse != 0);

		return en;
	}

	template <class T, class B>
	void SqlArrayFunctions<T, B>::SubarraysToTable_FillRow(Object^ o, typename B::IndexT% li, typename ShortArray::SqlBufferT% i, typename B::SqlBufferT% v)
	{
		SqlIndexItemPair<SqlArray<T, B>, B> p = (SqlIndexItemPair<SqlArray<T, B>, B>)o;

		li = p.LinearIndex;
		i = SqlArray<B::IndexT, ShortArray>::FromArray(p.Index).ToSqlBuffer();
		v = p.Item.ToSqlBuffer();
	}

#pragma endregion
#pragma region Scalar arithmetics

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::ScaMul(typename B::SqlBufferT a, T m)
	{
		SqlArray<T, B> u(a);

		interior_ptr<T> p = u.GetDataPointer();

		for (B::IndexT i = 0; i < u.m_length; i ++)
		{
			*p++ *= m;
		}

		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::ScaDiv(typename B::SqlBufferT a, T m)
	{
		SqlArray<T, B> u(a);

		interior_ptr<T> p = u.GetDataPointer();

		for (B::IndexT i = 0; i < u.m_length; i ++)
		{
			*p++ /= m;
		}

		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::ScaAdd(typename B::SqlBufferT a, T m)
	{
		SqlArray<T, B> u(a);

		interior_ptr<T> p = u.GetDataPointer();

		for (B::IndexT i = 0; i < u.m_length; i ++)
		{
			*p++ += m;
		}

		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::ScaSub(typename B::SqlBufferT a, T m)
	{
		SqlArray<T, B> u(a);

		interior_ptr<T> p = u.GetDataPointer();

		for (B::IndexT i = 0; i < u.m_length; i ++)
		{
			*p++ -= m;
		}

		return u.ToSqlBuffer();
	}

#pragma endregion
#pragma region Itemwise arithmetics

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::FromScalar(typename ShortArray::SqlBufferT length, T m)
	{
		array<B::IndexT>^ lena = SqlArray<B::IndexT, ShortArray>(length).ToArray();
		SqlArray<T, B> u(lena);

		interior_ptr<T> pd = u.GetDataPointer();

		for (B::IndexT i = 0; i < u.m_length; i ++)
		{
			*pd++ = m;
		}

		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Mul(typename B::SqlBufferT a, typename B::SqlBufferT b)
	{
		SqlArray<T, B> aa(a);
		SqlArray<T, B> ba(b);

		if (!aa.IsSameShape(ba))
		{
			throw gcnew SqlArrayException(ExceptionMessages::GetString(L"IncompatibleShape"));
		}

		interior_ptr<T> ap = aa.GetDataPointer();
		interior_ptr<T> bp = ba.GetDataPointer();

		for (B::IndexT i = 0; i < aa.m_length; i ++)
		{
			*ap++ *= *bp++;
		}

		return aa.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Div(typename B::SqlBufferT a, typename B::SqlBufferT b)
	{
		SqlArray<T, B> aa(a);
		SqlArray<T, B> ba(b);

		if (!aa.IsSameShape(ba))
		{
			throw gcnew SqlArrayException(ExceptionMessages::GetString(L"IncompatibleShape"));
		}

		interior_ptr<T> ap = aa.GetDataPointer();
		interior_ptr<T> bp = ba.GetDataPointer();

		for (B::IndexT i = 0; i < aa.m_length; i ++)
		{
			*ap++ /= *bp++;
		}

		return aa.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Add(typename B::SqlBufferT a, typename B::SqlBufferT b)
	{
		SqlArray<T, B> aa(a);
		SqlArray<T, B> ba(b);

		if (!aa.IsSameShape(ba))
		{
			throw gcnew SqlArrayException(ExceptionMessages::GetString(L"IncompatibleShape"));
		}

		interior_ptr<T> ap = aa.GetDataPointer();
		interior_ptr<T> bp = ba.GetDataPointer();

		for (B::IndexT i = 0; i < aa.m_length; i ++)
		{
			*ap++ += *bp++;
		}

		return aa.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::Sub(typename B::SqlBufferT a, typename B::SqlBufferT b)
	{
		SqlArray<T, B> aa(a);
		SqlArray<T, B> ba(b);

		if (!aa.IsSameShape(ba))
		{
			throw gcnew SqlArrayException(ExceptionMessages::GetString(L"IncompatibleShape"));
		}

		interior_ptr<T> ap = aa.GetDataPointer();
		interior_ptr<T> bp = ba.GetDataPointer();

		for (B::IndexT i = 0; i < aa.m_length; i ++)
		{
			*ap++ -= *bp++;
		}

		return aa.ToSqlBuffer();
	}

#pragma endregion
#pragma region Vector arithmetics

		template <class T, class B>
		T SqlArrayFunctions<T, B>::DotProd(typename B::SqlBufferT a, typename B::SqlBufferT b)
		{
			SqlArray<T, B> aa(a);
			SqlArray<T, B> ba(b);

			// Make sure a and b are vectors of the same size
			if (aa.m_rank != 1 || ba.m_rank != 1 ||
				*aa.GetLengthsPointer() != *ba.GetLengthsPointer())
			{
				throw gcnew SqlArrayException("Not vectors of the same size");	//******
			}

			interior_ptr<T> pa = aa.GetDataPointer();
			interior_ptr<T> pb = ba.GetDataPointer();

			T res = T(0);
			for (B::IndexT i = 0; i < aa.m_length; i ++)
			{
				res += *pa++ * *pb++;
			}

			return res;
		}

		template <class T, class B>
		typename B::SqlBufferT SqlArrayFunctions<T, B>::CrossProd(typename B::SqlBufferT a, typename B::SqlBufferT b)
		{
			SqlArray<T, B> aa(a);
			SqlArray<T, B> ba(b);

			// Make sure a and b are vectors of the same size
			if (aa.m_rank != 1 || ba.m_rank != 1 ||
				*aa.GetLengthsPointer() != 3 || *ba.GetLengthsPointer() != 3)
			{
				throw gcnew SqlArrayException("Not vectors with 3 elements");	//******
			}

			SqlArray<T, B> res(3);

			interior_ptr<T> pa = aa.GetDataPointer();
			interior_ptr<T> pb = ba.GetDataPointer();
			interior_ptr<T> pr = res.GetDataPointer();

			pr[0] = pa[1] * pb[2] - pa[2] * pb[1];
			pr[1] = pa[2] * pb[0] - pa[0] * pb[2];
			pr[2] = pa[0] * pb[1] - pa[1] * pb[0];

			return res.ToSqlBuffer();
		}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::TensorProd(typename B::SqlBufferT a, typename B::SqlBufferT b)
	{
		SqlArray<T, B> aa(a);
		SqlArray<T, B> ba(b);

		return SqlArray<T, B>::TensorProduct(aa, ba).ToSqlBuffer();
	}

#pragma endregion
#pragma region Matrix arithmetics

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::MatProd(typename B::SqlBufferT a, typename B::SqlBufferT b)
	{
		SqlArray<T, B> aa(a);
		SqlArray<T, B> ba(b);

		// Make sure a and b are compatible matrices
		if (aa.m_rank != 2 || ba.m_rank != 2 ||
			aa.GetLengthsPointer()[1] != ba.GetLengthsPointer()[0])
		{
			throw gcnew SqlArrayException("Matrices are not compatible");	//******
		}

		throw gcnew NotImplementedException();
	}

#pragma endregion
#pragma region Higher order tensor functions
		
	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::InnerProd(typename B::SqlBufferT a, typename B::SqlBufferT b)
	{
		SqlArray<T, B> aa(a);
		SqlArray<T, B> ba(b);

		return SqlArray<T, B>::InnerProduct(aa, ba).ToSqlBuffer();
	}

#pragma endregion
#pragma region Array functionals

	template <class T, class B>
	Double SqlArrayFunctions<T, B>::Avg(typename B::SqlBufferT data)
	{
		SqlArray<T, B> u(data);
		interior_ptr<T> dp = u.GetDataPointer();

		double sum = 0;
		for (B::IndexT i = 0; i < u.m_length; i ++)
		{
			sum += double(*dp++);
		}

		return sum / u.m_length;
	}

	template <class T, class B>
	T SqlArrayFunctions<T, B>::Min(typename B::SqlBufferT data)
	{
		SqlArray<T, B> u(data);
		interior_ptr<T> dp = u.GetDataPointer();

		T min = T::MaxValue;
		for (B::IndexT i = 0; i < u.m_length; i ++)
		{
			min = *dp < min ? *dp : min;
			dp++;
		}

		return min;
	}

	template <class T, class B>
	T SqlArrayFunctions<T, B>::Max(typename B::SqlBufferT data)
	{
		SqlArray<T, B> u(data);
		interior_ptr<T> dp = u.GetDataPointer();

		T max = T::MinValue;
		for (B::IndexT i = 0; i < u.m_length; i ++)
		{
			max = *dp > max ? *dp : max;
			dp++;
		}

		return max;
	}

	template <class T, class B>
	Double SqlArrayFunctions<T, B>::StDev(typename B::SqlBufferT data)
	{
		return Math::Sqrt(Var(data));
	}

	template <class T, class B>
	T SqlArrayFunctions<T, B>::Sum(typename B::SqlBufferT data)
	{
		SqlArray<T, B> u(data);
		interior_ptr<T> dp = u.GetDataPointer();

		T sum = (T)0;
		for (B::IndexT i = 0; i < u.m_length; i ++)
		{
			sum += *dp++;
		}

		return sum;
	}

	template <class T, class B>
	Double SqlArrayFunctions<T, B>::Var(typename B::SqlBufferT data)
	{
		SqlArray<T, B> u(data);
		interior_ptr<T> dp = u.GetDataPointer();

		double sum = 0;
		double sum2 = 0;
		for (B::IndexT i = 0; i < u.m_length; i ++)
		{
			double x = double(*dp++);
			sum += x;
			sum2 += x * x;
		}

		return sum2 / u.m_length - (sum / u.m_length) * (sum / u.m_length);
	}

	template <class T, class B>
	T SqlArrayFunctions<T, B>::Med(typename B::SqlBufferT data)	
	{
		array<T>^ u = SqlArray<T, B>(data).ToArray();
		System::Array::Sort(u);

		return u[u->Length / 2];
	}

#pragma endregion
#pragma region Table to array functions

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::FromTable(SqlChars^ table, typename ShortArray::SqlBufferT length)
	{
		// TODO: add boundary checks


		array<B::IndexT>^ newlength = SqlArray<B::IndexT, ShortArray>(length).ToArray();

		SqlConnection^ cn = gcnew SqlConnection("context connection=true");
		cn->Open();

		String^ query = String::Format(L"SELECT t.* FROM {0} AS t", table->ToSqlString().Value);

		SqlCommand^ cmd = gcnew SqlCommand(query, cn);
		SqlDataReader^ dr = cmd->ExecuteReader();

		if (!dr->HasRows || dr->FieldCount == 0)
		{
			throw gcnew Exception("No input data or zero columns"); //******
		}

		// Initialize new array
		SqlArray<T, B> u(newlength);
		B::IndexT uoff = u.GetDataOffset();
		interior_ptr<T> up = u.GetDataPointer();


		// CASE I: @li, @v
		if (dr->FieldCount == 2 && dr->GetFieldType(0) == B::IndexT::typeid && dr->GetFieldType(1) == T::typeid)
		{
			while (dr->Read())
			{
				up[(B::IndexT)dr->GetValue(0)] = (T)dr->GetValue(1);
			}
		}
		else

		// CASE II:   @i[], @v
		if (dr->FieldCount == 2 && dr->GetDataTypeName(0)->StartsWith(L"varbinary") && dr->GetFieldType(1) == T::typeid)
		{
			// table format: 1 * index  varbinary
			//				 1 * scalar T

			while (dr->Read())
			{
				array<B::IndexT>^ index = SqlArray<B::IndexT, ShortArray>(ShortArray::GetSqlBuffer(dr, 0)).ToArray();
				up[u.GetLinearIndex(index)] = (T)dr->GetValue(1);
			}
		}
		// CASE III: @i1, @i2, ... @in, @v
		else if (dr->FieldCount == newlength->Length + 1 && dr->GetFieldType(newlength->Length) == T::typeid)
		{
			// table format: rank * index  IndexT
			//                  1 * scalar T

			array<B::IndexT>^ index = gcnew array<B::IndexT>(newlength->Length);

			while (dr->Read())
			{
				for (int i = 0; i < index->Length; i ++)
				{
					index[i] = (B::IndexT)dr->GetValue(i);
				}

				up[u.GetLinearIndex(index)] = (T)dr->GetValue(index->Length);
			}
		}
		else
		{
			// Incompatible format
			throw gcnew Exception("Incompatible format");	//*******
		}


		dr->Close();
		cn->Close();

		return u.ToSqlBuffer();
	}

	template <class T, class B>
	typename B::SqlBufferT SqlArrayFunctions<T, B>::FromSubarrayTable(SqlChars^ table, typename ShortArray::SqlBufferT length)
	{
		array<B::IndexT>^ newlength = SqlArray<B::IndexT, ShortArray>(length).ToArray();

		SqlConnection^ cn = gcnew SqlConnection("context connection=true");
		cn->Open();

		String^ query = String::Format(L"SELECT t.* FROM {0} AS t", table->ToSqlString().Value);

		SqlCommand^ cmd = gcnew SqlCommand(query, cn);
		SqlDataReader^ dr = cmd->ExecuteReader();

		if (!dr->HasRows || dr->FieldCount == 0)
		{
			throw gcnew Exception("No input data or zero columns"); //******
		}

		// Initialize new array
		SqlArray<T, B> u(newlength);

		if (dr->FieldCount == 2 &&
			dr->GetDataTypeName(0)->StartsWith(L"varbinary") &&
			dr->GetDataTypeName(1)->StartsWith(L"varbinary"))
		{
			while (dr->Read())
			{
				SqlArray<B::IndexT, ShortArray> ix(ShortArray::GetSqlBuffer(dr, 0));
				SqlArray<T, B> sa(B::GetSqlBuffer(dr, 1));
				
				array<B::IndexT>^ index = ix.ToArray();

				u.SetSubarray(index, sa);
			}
		}
		else
		{
			// Incompatible format
			throw gcnew Exception("Incompatible format");	//*******
		}

		dr->Close();
		cn->Close();

		return u.ToSqlBuffer();
	}

#pragma endregion

	
	// ----------

#define SPECIALIZE_SQLARRAYFUNCTIONS(T) \
	template Jhu::SqlServer::Array::SqlArrayFunctions<T, ShortArray>; \
	template Jhu::SqlServer::Array::SqlArrayFunctions<T, MaxArray>;


	SPECIALIZE_SQLARRAYFUNCTIONS(Byte)
	SPECIALIZE_SQLARRAYFUNCTIONS(Int16)
	SPECIALIZE_SQLARRAYFUNCTIONS(Int32)
	SPECIALIZE_SQLARRAYFUNCTIONS(Int64)
	SPECIALIZE_SQLARRAYFUNCTIONS(Single)
	SPECIALIZE_SQLARRAYFUNCTIONS(Double)
	SPECIALIZE_SQLARRAYFUNCTIONS(SqlComplex<Single>)
	SPECIALIZE_SQLARRAYFUNCTIONS(SqlComplex<Double>)

} } }