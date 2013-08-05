#pragma once

#include "macro.h"
#include "enum.h"
#include "SqlArray.h"
#include "SqlArrayEnumerator.h"
#include "SqlArrayMatrixEnumerator.h"
#include "SqlArraySliceEnumerator.h"
#include "SqlArrayItemEnumerator.h"
#include "SqlArraySubarrayEnumerator.h"
#include "SqlArrayAttribute.h"
#include "ShortArray.h"
#include "MaxArray.h"

using namespace System;
using namespace System::Collections;
using namespace System::Text;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;
using namespace Jhu::SqlServer::Array::Parser;

namespace Jhu { namespace SqlServer { namespace Array
{
	/// <summary>
	/// Implements basic array manipulation functions.
	/// </summary>
	template <class T, class B>
	[Jhu::SqlServer::Array::SqlArrayAttribute]
	public value class SqlArrayFunctions
	{

	public:

#pragma region String conversion functions

		/// <summary>
		/// Returns the string representation of the array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			Name=L"ToString")]
		static SqlChars^ GetString(typename B::SqlBufferT data);

		/// <summary>
		/// Converts the string representation into an array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Parse(SqlChars^ data);

#pragma endregion
#pragma region Basic array constructors

		/// <summary>
		/// Creates a vector from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Vector_1(PARLIST_1(T, v));

		/// <summary>
		/// Creates a vector from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Vector_2(PARLIST_2(T, v));

		/// <summary>
		/// Creates a vector from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Vector_3(PARLIST_3(T, v));

		/// <summary>
		/// Creates a vector from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Vector_4(PARLIST_4(T, v));

		/// <summary>
		/// Creates a vector from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Vector_5(PARLIST_5(T, v));

		/// <summary>
		/// Creates a vector from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Vector_6(PARLIST_6(T, v));

		/// <summary>
		/// Creates a vector from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Vector_7(PARLIST_7(T, v));

		/// <summary>
		/// Creates a vector from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Vector_8(PARLIST_8(T, v));

		/// <summary>
		/// Creates a vector from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Vector_9(PARLIST_9(T, v));

		/// <summary>
		/// Creates a vector from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Vector_10(PARLIST_10(T, v));

		// ---

		/// <summary>
		/// Creates a matrix from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Matrix_2(PARLIST_4(T, v));

		/// <summary>
		/// Creates a matrix from the items passed as parameters.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Matrix_3(PARLIST_9(T, v));

#pragma endregion
#pragma region Array properties

		/// <summary>
		/// Returns the rank (i.e. dimension or number of indices)
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::RankT Rank(typename B::SqlBufferT data);

		/// <summary>
		/// Returns the total number of items.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::IndexT TotalLength(typename B::SqlBufferT data);

		/// <summary>
		/// Returns the length of the given rank (i.e. the range of the given index)
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::IndexT Length(typename B::SqlBufferT data, typename B::RankT i);

		/// <summary>
		/// Returns all the lengths of the ranks as a vector.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static ShortArray::SqlBufferT Lengths(typename B::SqlBufferT data);

#pragma endregion
#pragma region Buffer manipulation functions

		/// <summary>
		/// Casts a RAW binary blob to an array my prefixing with a header.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Cast(typename B::SqlBufferT data, typename B::IndexT offset, typename ShortArray::SqlBufferT length);

		/// <summary>
		/// Returns the raw part of the byte buffer by dropping the header.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Raw(typename B::SqlBufferT data);

		/// <summary>
		/// Changes the length values of the array.
		/// </summary>
		/// <remarks>
		/// Reshaping is only possible if the  original and the resulting total number of
		/// items is the same. No buffer leallocation will happen if the header sizes
		/// are the same.
		/// </remarks>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Reshape(typename B::SqlBufferT data, typename ShortArray::SqlBufferT length);

		/// <summary>
		/// Performes a transpose operation on a two index array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Transpose(typename B::SqlBufferT data);

		/// <summary>
		/// Performes a general transpose (index reorder) operation on the array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Permute(typename B::SqlBufferT data, typename ShortArray::SqlBufferT indexlist);

#pragma endregion
#pragma region Item accessors

		/// <summary>
		/// Returns zero, used for performance testing.
		/// </summary>
		[SqlFunction( DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Empty(typename B::SqlBufferT data, PARLIST_1(typename B::IndexT, i));

		/// <summary>
		/// Returns a single item of the array identified by its linear index.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Item(typename B::SqlBufferT data, typename B::IndexT index);

		/// <summary>
		/// Returns a single item of the array identified by its index in the form of a vector.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Item_N(typename B::SqlBufferT data, typename ShortArray::SqlBufferT indexes);

		/// <summary>
		/// Returns a single item of the array.
		/// </summary>
		[SqlFunction( DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Item_1(typename B::SqlBufferT data, PARLIST_1(typename B::IndexT, i));

		/// <summary>
		/// Returns a single item of the array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Item_2(typename B::SqlBufferT data, PARLIST_2(typename B::IndexT, i));

		/// <summary>
		/// Returns a single item of the array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Item_3(typename B::SqlBufferT data, PARLIST_3(typename B::IndexT, i));

		/// <summary>
		/// Returns a single item of the array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Item_4(typename B::SqlBufferT data, PARLIST_4(typename B::IndexT, i));

		/// <summary>
		/// Returns a single item of the array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Item_5(typename B::SqlBufferT data, PARLIST_5(typename B::IndexT, i));

		/// <summary>
		/// Returns a single item of the array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Item_6(typename B::SqlBufferT data, PARLIST_6(typename B::IndexT, i));

		/// <summary>
		/// Updates a single item (identified by its linear index) of the array and returnes the modified array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateItem(typename B::SqlBufferT data, typename B::IndexT index, T value);

		/// <summary>
		/// Updates a single item of the array and returnes the modified array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateItem_N(typename B::SqlBufferT data, typename ShortArray::SqlBufferT indexes, T value);

		/// <summary>
		/// Updates a single item of the array and returnes the modified array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateItem_1(typename B::SqlBufferT data, PARLIST_1(typename B::IndexT, i), T value);

		/// <summary>
		/// Updates a single item of the array and returnes the modified array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateItem_2(typename B::SqlBufferT data, PARLIST_2(typename B::IndexT, i), T value);

		/// <summary>
		/// Updates a single item of the array and returnes the modified array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateItem_3(typename B::SqlBufferT data, PARLIST_3(typename B::IndexT, i), T value);

		/// <summary>
		/// Updates a single item of the array and returnes the modified array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateItem_4(typename B::SqlBufferT data, PARLIST_4(typename B::IndexT, i), T value);

		/// <summary>
		/// Updates a single item of the array and returnes the modified array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateItem_5(typename B::SqlBufferT data, PARLIST_5(typename B::IndexT, i), T value);

		/// <summary>
		/// Updates a single item of the array and returnes the modified array.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateItem_6(typename B::SqlBufferT data, PARLIST_6(typename B::IndexT, i), T value);

#pragma endregion
#pragma region Multiple item accessors

		/// <summary>
		/// Returns a vector of items as listed in another array.
		/// </summary>
		/// <param name="data">The source array</param>
		/// <param name="indexes">
		/// An array containing the indices of the items to be returned. This array has to be a two
		/// index array, the first index indexing the items. The length of the second rank has to
		/// be the rank of the source array.
		/// </param>
		/// <returns>A vector containing the items listes in the parameter data.</returns>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Items(typename B::SqlBufferT data, typename B::SqlBufferT indexes);

		/// <summary>
		/// Updates the items listed and returns the array.
		/// </summary>
		/// <param name="data">The source array</param>
		/// <param name="indexes">
		/// An array containing the indices of the items to be updated. This array has to be a two
		/// index array, the first index indexing the items. The length of the second rank has to
		/// be the rank of the source array.
		/// </param>
		/// <param name="values">
		/// A vector containing the new value of the items listed in the parameter indexes.
		/// The length of this vector has to be the same as the length of the first rank of the
		/// indexes parameter.
		/// </param>
		/// <returns>The original array with the listed item updated.</returns>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateItems(typename B::SqlBufferT data, typename B::SqlBufferT indexes, typename B::SqlBufferT values);

#pragma endregion
#pragma region Subarray manipulation functions

		/// <summary>
		/// Returns a subarray of an array.
		/// </summary>
		/// <param name="data">The original array</param>
		/// <param name="offset">The origin of the subarray in the form of a vector listing index values.</param>
		/// <param name="length">Lengths of the subarray to be extracted.</param>
		/// <param name="collapse">
		/// If not equal to zero, indexes (ranks) with length of 1 will be removed and the
		/// returned subarray will have less indices.
		/// </param>
		/// <returns>A subarray.</returns>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Subarray(typename B::SqlBufferT data, typename ShortArray::SqlBufferT offset, typename ShortArray::SqlBufferT length, Int16 collapse);

		/// <summary>
		/// Updates a subarray of an array an returns the whole updated array.
		/// </summary>
		/// <param name="data">The original array</param>
		/// <param name="offset">The origin of the subarray in the form of a vector listing index values.</param>
		/// <param name="value">New value of the subarray.</param>
		/// <returns>The updated array.</returns>
		/// <remarks>The rank of the value parameter and the data parameter has to be the same.</remarks>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateSubarray(typename B::SqlBufferT data, typename ShortArray::SqlBufferT offset, typename B::SqlBufferT value);

		/// <summary>
		/// Returns a list subarray of an array.
		/// </summary>
		/// <param name="data">The original array</param>
		/// <param name="offsest">
		/// The list of the origins of the subarrays in the form of a matrix listing index values.
		/// The first index indexes the subarrays to be returned.
		/// </param>
		/// <param name="length">Lengths of the subarray to be extracted.</param>
		/// <param name="collapse">
		/// If not equal to zero, indexes (ranks) with length of 1 will be removed and the
		/// returned subarray will have less indices.
		/// </param>
		/// <returns>An array listing the subarrays.</returns>
		/// <remarks>Only subarrays of the same size can be extracted.</remarks>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Subarrays(typename B::SqlBufferT data, typename B::SqlBufferT offsets, typename ShortArray::SqlBufferT length, Int16 collapse);

		/// <summary>
		/// Updates subarrays of an array an returns the whole updated array.
		/// </summary>
		/// <param name="data">The original array</param>
		/// <param name="offset">The origin of the subarrays in the form of a matrix listing index values.</param>
		/// <param name="value">New value of the subarrays.</param>
		/// <returns>The updated array.</returns>
		/// <remarks>The rank of the value parameter has to be one more than the rank of data parameter.</remarks>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT UpdateSubarrays(typename B::SqlBufferT data, typename B::SqlBufferT offsets, typename B::SqlBufferT values);

#pragma endregion
#pragma region Array to table functions

		/// <summary>
		/// Converts the array into a SQL table, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "ToTable_FillRow")]
		static System::Collections::IEnumerable^ ToTable(typename B::SqlBufferT data);

		/// <param name="li">Linear index of the item</param>
		/// <param name="i">Index of the item as an array.</param>
		/// <param name="v">Value of the item.</param>
		static void ToTable_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% li,
			[System::Runtime::InteropServices::OutAttribute] typename ShortArray::SqlBufferT% i,
			[System::Runtime::InteropServices::OutAttribute] T% v);


		/// <summary>
		/// Converts the array into a SQL table, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "ToTable_1_FillRow")]
		static System::Collections::IEnumerable^ ToTable_1(typename B::SqlBufferT data);

		/// <param name="i">Index of the item</param>
		/// <param name="v">Value of the item</param>
		static void ToTable_1_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% li,
			PARLIST_1([System::Runtime::InteropServices::OutAttribute] typename B::IndexT%, i),
			[System::Runtime::InteropServices::OutAttribute] T% v);

		/// <summary>
		/// Converts the array into a SQL table, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "ToTable_2_FillRow")]
		static System::Collections::IEnumerable^ ToTable_2(typename B::SqlBufferT data);

		/// <param name="i0..n">Indexes of the item</param>
		/// <param name="v">Value of the item</param>
		static void ToTable_2_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% li,
			PARLIST_2([System::Runtime::InteropServices::OutAttribute] typename B::IndexT%, i),
			[System::Runtime::InteropServices::OutAttribute] T% v);

		/// <summary>
		/// Converts the array into a SQL table, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "ToTable_3_FillRow")]
		static System::Collections::IEnumerable^ ToTable_3(typename B::SqlBufferT data);

		/// <param name="i0..n">Indexes of the item</param>
		/// <param name="v">Value of the item</param>
		static void ToTable_3_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% li,
			PARLIST_3([System::Runtime::InteropServices::OutAttribute] typename B::IndexT%, i),
			[System::Runtime::InteropServices::OutAttribute] T% v);

		/// <summary>
		/// Converts the array into a SQL table, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "ToTable_4_FillRow")]
		static System::Collections::IEnumerable^ ToTable_4(typename B::SqlBufferT data);

		/// <param name="i0..n">Indexes of the item</param>
		/// <param name="v">Value of the item</param>
		static void ToTable_4_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% li,
			PARLIST_4([System::Runtime::InteropServices::OutAttribute] typename B::IndexT%, i),
			[System::Runtime::InteropServices::OutAttribute] T% v);

		/// <summary>
		/// Converts the array into a SQL table, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "ToTable_5_FillRow")]
		static System::Collections::IEnumerable^ ToTable_5(typename B::SqlBufferT data);

		/// <param name="i0..n">Indexes of the item</param>
		/// <param name="v">Value of the item</param>
		static void ToTable_5_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% li,
			PARLIST_5([System::Runtime::InteropServices::OutAttribute] typename B::IndexT%, i),
			[System::Runtime::InteropServices::OutAttribute] T% v);

		/// <summary>
		/// Converts the array into a SQL table, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "ToTable_6_FillRow")]
		static System::Collections::IEnumerable^ ToTable_6(typename B::SqlBufferT data);

		/// <param name="i0..n">Indexes of the item</param>
		/// <param name="v">Value of the item</param>
		static void ToTable_6_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% li,
			PARLIST_6([System::Runtime::InteropServices::OutAttribute] typename B::IndexT%, i),
			[System::Runtime::InteropServices::OutAttribute] T% v);

		/// <summary>
		/// Converts the matrix into a SQL table, column-by-column.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "MatrixToTable_2_FillRow")]
		static System::Collections::IEnumerable^ MatrixToTable_2(typename B::SqlBufferT data);

		/// <param name="i0..n">Index of the column</param>
		/// <param name="v0..n">Values of the column</param>
		static void MatrixToTable_2_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% i,
			PARLIST_2([System::Runtime::InteropServices::OutAttribute] T%, v));

		/// <summary>
		/// Converts the matrix into a SQL table, column-by-column.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "MatrixToTable_3_FillRow")]
		static System::Collections::IEnumerable^ MatrixToTable_3(typename B::SqlBufferT data);

		/// <param name="i0..n">Index of the column</param>
		/// <param name="v0..n">Values of the column</param>
		static void MatrixToTable_3_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% i,
			PARLIST_3([System::Runtime::InteropServices::OutAttribute] T%, v));

		/// <summary>
		/// Converts the matrix into a SQL table, column-by-column.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "MatrixToTable_4_FillRow")]
		static System::Collections::IEnumerable^ MatrixToTable_4(typename B::SqlBufferT data);

		/// <param name="i0..n">Index of the column</param>
		/// <param name="v0..n">Values of the column</param>
		static void MatrixToTable_4_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% i,
			PARLIST_4([System::Runtime::InteropServices::OutAttribute] T%, v));

		/// <summary>
		/// Converts the matrix into a SQL table, column-by-column.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "MatrixToTable_5_FillRow")]
		static System::Collections::IEnumerable^ MatrixToTable_5(typename B::SqlBufferT data);

		/// <param name="i0..n">Index of the column</param>
		/// <param name="v0..n">Values of the column</param>
		static void MatrixToTable_5_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% i,
			PARLIST_5([System::Runtime::InteropServices::OutAttribute] T%, v));

		/// <summary>
		/// Converts the matrix into a SQL table, column-by-column.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "MatrixToTable_6_FillRow")]
		static System::Collections::IEnumerable^ MatrixToTable_6(typename B::SqlBufferT data);

		/// <param name="i0..n">Index of the column</param>
		/// <param name="v0..n">Values of the column</param>
		static void MatrixToTable_6_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% i,
			PARLIST_6([System::Runtime::InteropServices::OutAttribute] T%, v));

		/// <summary>
		/// Converts the matrix into a SQL table, column-by-column.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "MatrixToTable_7_FillRow")]
		static System::Collections::IEnumerable^ MatrixToTable_7(typename B::SqlBufferT data);

		/// <param name="i0..n">Index of the column</param>
		/// <param name="v0..n">Values of the column</param>
		static void MatrixToTable_7_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% i,
			PARLIST_7([System::Runtime::InteropServices::OutAttribute] T%, v));

		/// <summary>
		/// Converts the matrix into a SQL table, column-by-column.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "MatrixToTable_8_FillRow")]
		static System::Collections::IEnumerable^ MatrixToTable_8(typename B::SqlBufferT data);

		/// <param name="i0..n">Index of the column</param>
		/// <param name="v0..n">Values of the column</param>
		static void MatrixToTable_8_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% i,
			PARLIST_8([System::Runtime::InteropServices::OutAttribute] T%, v));

		/// <summary>
		/// Converts the matrix into a SQL table, column-by-column.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "MatrixToTable_9_FillRow")]
		static System::Collections::IEnumerable^ MatrixToTable_9(typename B::SqlBufferT data);

		/// <param name="i0..n">Index of the column</param>
		/// <param name="v0..n">Values of the column</param>
		static void MatrixToTable_9_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% i,
			PARLIST_9([System::Runtime::InteropServices::OutAttribute] T%, v));

		/// <summary>
		/// Converts the matrix into a SQL table, column-by-column.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "MatrixToTable_10_FillRow")]
		static System::Collections::IEnumerable^ MatrixToTable_10(typename B::SqlBufferT data);

		/// <param name="i0..n">Index of the column</param>
		/// <param name="v0..n">Values of the column</param>
		static void MatrixToTable_10_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% i,
			PARLIST_10([System::Runtime::InteropServices::OutAttribute] T%, v));

		// ---

		/// <summary>
		/// Splits the array into equally sized subarrays and returnes them as a table.
		/// </summary>
		/// <param name="data">The original array</param>
		/// <param name="offset">The offset where splitting should start</param>
		/// <param name="length">Lengths of the subarrays.</param>
		/// <param name="collapse">If not equal to zero, ranks with length of 1 will be removed from the resulting subarrays.</param>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "Split_FillRow")]
		static System::Collections::IEnumerable^ Split(typename B::SqlBufferT data, typename ShortArray::SqlBufferT offset, typename ShortArray::SqlBufferT length, Int16 collapse);

		/// <param name="ci">Collapsed index of the subarray.</param>
		/// <param name="i">Original index of the first item of the subarray.</param>
		/// <param name="ci">The subarray.</param>
		static void Split_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename ShortArray::SqlBufferT% ci,
			[System::Runtime::InteropServices::OutAttribute] typename ShortArray::SqlBufferT% i,
			[System::Runtime::InteropServices::OutAttribute] typename B::SqlBufferT% v);

		/// <summary>
		/// Returns a list of items of and array as a SQL table.
		/// </summary>
		/// <param name="data">The array</param>
		/// <param name="indexes">An array listing the indices of items to be returned.</param>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "ItemsToTable_FillRow")]
		static System::Collections::IEnumerable^ ItemsToTable(typename B::SqlBufferT data, typename B::SqlBufferT indexes);

		/// <param name="li">Index of the item in the original indexes array.</param>
		/// <param name="i">Original index of the item.</param>
		/// <param name="v">Value of the item.</param>
		static void ItemsToTable_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% li,
			[System::Runtime::InteropServices::OutAttribute] typename ShortArray::SqlBufferT% i,
			[System::Runtime::InteropServices::OutAttribute] typename T% v);

		/// <summary>
		/// Returns a list of subarrays of and array as a SQL table.
		/// </summary>
		/// <param name="data">The array</param>
		/// <param name="offsets">An array listing the indices of the origins of the subarrays to be returned.</param>
		/// <param name="length">The lengths of the subarrays. Same for all.</param>
		/// <param name="collapse">If not equal to zero, ranks with length of 1 will be removed.</param>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true,
			FillRowMethodName = "SubarraysToTable_FillRow")]
		static System::Collections::IEnumerable^ SubarraysToTable(typename B::SqlBufferT data, typename B::SqlBufferT offsets, typename ShortArray::SqlBufferT length, Int16 collapse);

		/// <param name="li">Index of the subarray in the original offsets array.</param>
		/// <param name="i">Original offset of the subarray.</param>
		/// <param name="v">Value of the subarray.</param>
		static void SubarraysToTable_FillRow(
			Object^ o,
			[System::Runtime::InteropServices::OutAttribute] typename B::IndexT% li,
			[System::Runtime::InteropServices::OutAttribute] typename ShortArray::SqlBufferT% i,
			[System::Runtime::InteropServices::OutAttribute] typename B::SqlBufferT% v);

#pragma endregion
#pragma region Table to array functions

		[SqlFunction(DataAccess = DataAccessKind::Read, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT FromTable(SqlChars^ table, typename ShortArray::SqlBufferT length);

		[SqlFunction(DataAccess = DataAccessKind::Read, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT FromSubarrayTable(SqlChars^ table, typename ShortArray::SqlBufferT length);

#pragma endregion
#pragma region Scalar arithmetics

		/// <summary>
		/// Multiplies the array by a scalar value.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT ScaMul(typename B::SqlBufferT a, T m);

		/// <summary>
		/// Divides the array by a scalar value.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT ScaDiv(typename B::SqlBufferT a, T m);

		/// <summary>
		/// Adds a scalar value to the array items.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT ScaAdd(typename B::SqlBufferT a, T m);

		/// <summary>
		/// Subtracts a scalar value from the array items.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT ScaSub(typename B::SqlBufferT a, T m);

#pragma endregion
#pragma region Itemwise arithmetics

		/// <summary>
		/// Creates an array and initializes the items to a given value.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT FromScalar(typename ShortArray::SqlBufferT length, T m);

		/// <summary>
		/// Multiplies to arrays, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Mul(typename B::SqlBufferT a, typename B::SqlBufferT b);

		/// <summary>
		/// Divides one array by another, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Div(typename B::SqlBufferT a, typename B::SqlBufferT b);

		/// <summary>
		/// Adds to arrays together, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Add(typename B::SqlBufferT a, typename B::SqlBufferT b);

		/// <summary>
		/// Subtracts an array from another, item-by-item.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT Sub(typename B::SqlBufferT a, typename B::SqlBufferT b);

#pragma endregion
#pragma region Vector arithmetics

		/// <summary>
		/// Calculates the dot product of two vectors.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T DotProd(typename B::SqlBufferT a, typename B::SqlBufferT b);

		/// <summary>
		/// Calculates the cross product of two vectors.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT CrossProd(typename B::SqlBufferT a, typename B::SqlBufferT b);

		/// <summary>
		/// Calculates the tensor product of two vectors.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT TensorProd(typename B::SqlBufferT a, typename B::SqlBufferT b);

#pragma endregion
#pragma region Matrix arithmetics

		/// <summary>
		/// Calculates the product of two matrices.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT MatProd(typename B::SqlBufferT a, typename B::SqlBufferT b);

#pragma endregion
#pragma region Higher order tensor functions

		/// <summary>
		/// Calculates the inner product of a vector and a tensor
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static typename B::SqlBufferT InnerProd(typename B::SqlBufferT a, typename B::SqlBufferT b);

#pragma endregion
#pragma region Array functionals

		/// <summary>
		/// Calculates the average of the array elements.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static Double Avg(typename B::SqlBufferT data);

		/// <summary>
		/// Returns the minimum of the array elements.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Min(typename B::SqlBufferT data);

		/// <summary>
		/// Returns the maximum of the array elements.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Max(typename B::SqlBufferT data);

		/// <summary>
		/// Returns the standard deviation of the array elements.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static Double StDev(typename B::SqlBufferT data);

		/// <summary>
		/// Returns the sum of the array elements.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Sum(typename B::SqlBufferT data);

		/// <summary>
		/// Returns the variance of the array elements.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static Double Var(typename B::SqlBufferT data);

		/// <summary>
		/// Returns the median of the array elements.
		/// </summary>
		[SqlFunction(DataAccess = DataAccessKind::None, SystemDataAccess = SystemDataAccessKind::None, IsDeterministic = true)]
		static T Med(typename B::SqlBufferT data);

#pragma endregion


	};

}
} }