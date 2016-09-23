#pragma once

#include "macro.h"
#include "ShortArray.h"
#include "MaxArray.h"
#include "SqlArrayAttribute.h"
#include "SqlArrayHeader.h"
#include "SqlComplex.h"
#include "enum.h"
#include "SqlArrayException.h"
#include "ExceptionMessages.h"
//#include "SqlArrayEnumerator.h"

using namespace System;
using namespace System::Text;
using namespace System::Globalization;
using namespace System::Collections::Generic;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;
using namespace Jhu::SqlServer::Array::Parser;

namespace Jhu { namespace SqlServer { namespace Array
{

	/// <summary>
	/// Implements strongly typed array functionality around a SQL Server byte buffer.
	/// </summary>
	template <class T, class B>
	public value class SqlArray : IBinarySerialize
	{
#pragma region Member variables

		/// <summary>
		/// Contains the local buffer that stores header and raw data
		/// </summary>
		internal: array<typename B::BufferT>^ m_buffer;

		/// <summary>
		/// Rank (number of indices) of the array.
		/// </summary>
		/// <remarks>
		/// Value read from the header upon array load and written to it upon serialization.
		/// </remarks>
		internal: typename B::RankT	m_rank;

		/// <summary>
		/// Total number of items in the array.
		/// </summary>
		/// <remarks>
		/// Value read from the header upon array load and written to it upon serialization.
		/// </remarks>
		internal: typename B::IndexT	m_length;

#pragma endregion
#pragma region Properties

		/// <summary>
		/// Gets an internal data id of the item type
		/// </summary>
		internal: static property typename B::DataTypeT DataType { typename B::DataTypeT get(); };

		/// <summary>
		/// Gets the total number of items.
		/// </summary>
		public: property typename B::IndexT TotalLength { typename B::IndexT get(); };

#pragma endregion
#pragma region Constructors
		
		/// <summary>
		/// Initializes a one rank array.
		/// </summary>
		public: SqlArray(PARLIST_1(typename B::IndexT, i));

		/// <summary>
		/// Initializes a two rank array.
		/// </summary>
		public: SqlArray(PARLIST_2(typename B::IndexT, i));

		/// <summary>
		/// Initializes an array with an arbitrary rank.
		/// </summary>
		public: SqlArray(array<typename B::IndexT>^ length);

		/// <summary>
		/// Initializes the array wrapper around a SQL Server buffer.
		/// </summary> 
		/// <remarks>
		/// Wraps the entire buffer or loads the entire stream.
		/// </remarks>
		public: SqlArray(typename B::SqlBufferT data);

		/// <summary>
		/// Initializes the array wrapper around a SQL Server buffer.
		/// </summary>
		/// <remarks>
		/// If the underlying data structure is a SQL buffer, the whole
		/// buffer will be wrapped. If the underlying data is in a stream
		/// (as for varbinary(max)) loading of the data is optional and
		/// determined by the method parameter
		/// </remarks>
		public: SqlArray(typename B::SqlBufferT data, ArrayLoadMethod method);

#pragma endregion
#pragma region Member functions

		/// <summary>
		/// Returns a managed pointer to the array header.
		/// </summary>
		internal: interior_ptr<typename B::HeaderT> GetHeaderPointer();

		/// <summary>
		/// Returns a managed pointer to list of rank lengths.
		/// </summary>
		internal: interior_ptr<typename B::IndexT> GetLengthsPointer();

		/// <summary>
		/// Returns a managed pointer to the data.
		/// </summary>
		internal: interior_ptr<T> GetDataPointer();

		/// <summary>
		/// Returns the byte offset if the rank length within the buffer.
		/// </summary>
		internal: typename B::IndexT GetLengthsOffset();

		/// <summary>
		/// Returns the byte offset if the data within the buffer.
		/// </summary>
		internal: typename B::IndexT GetDataOffset();


		/// <summary>
		/// Initializes the internal buffer from a managed byte array.
		/// </summary>
		/// <remarks>
		/// The SqlArray class references the array without copying the
		/// data from the source array. The header is read and member variables
		/// are intialized.
		/// </remarks>
		internal: void InitBuffer(array<typename B::BufferT>^ buffer);
		
		/// <summary>
		/// Initializes the data inside the local buffer based on the
		/// managed array passed. The array header must be initialized first.
		/// </summary>
		internal: void CastBuffer(array<typename B::BufferT>^ buffer, typename B::IndexT offset);


		/// <summary>
		/// Allocates the internal buffer based on the rank length passed.
		/// </summary>
		internal: void AllocBuffer(array<typename B::IndexT>^ length);

		/// <summary>
		/// Allocates the internal buffer based on the rank length passed.
		/// </summary>
		internal: void AllocBuffer(PARLIST_1(typename B::IndexT, length));

		/// <summary>
		/// Allocates the internal buffer based on the rank length passed.
		/// </summary>
		internal: void AllocBuffer(PARLIST_2(typename B::IndexT, length));


		/// <summary>
		/// Reads the signature bytes from the beginning of the byte buffer.
		/// </summary>
		/// <remarks>
		/// The functions loads header information into the local variables and
		/// checks data type compatibility.
		/// </remarks>
		internal: void ReadSignature();

		/// <summary>
		/// Writes header information into the byte buffer.
		/// </summary>
		internal: void WriteSignature();


		/// <summary>
		/// Writes rank lengths into the byte buffer.
		/// </summary>
		internal: void WriteLengths(array<typename B::IndexT>^ length);

		/// <summary>
		/// Writes rank lengths into the byte buffer.
		/// </summary>
		internal: void WriteLengths(PARLIST_1(typename B::IndexT, i));

		/// <summary>
		/// Writes rank lengths into the byte buffer.
		/// </summary>
		internal: void WriteLengths(PARLIST_2(typename B::IndexT, i));

		/// <summary>
		/// Used internally to itarate through the index values of an array
		/// <summary>
		internal: bool IterateCounter(array<typename B::IndexT>^ counter, array<typename B::IndexT>^ length, typename B::RankT rank);


		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(array<T>^ data);

		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(PARLIST_1(T, i));

		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(PARLIST_2(T, i));

		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(PARLIST_3(T, i));

		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(PARLIST_4(T, i));

		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(PARLIST_5(T, i));

		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(PARLIST_6(T, i));

		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(PARLIST_7(T, i));

		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(PARLIST_8(T, i));

		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(PARLIST_9(T, i));

		/// <summary>
		/// Writes data into the byte buffer.
		/// </summary>
		internal: void WriteData(PARLIST_10(T, i));


		/// <summary>
		/// Loads the contents of the byte buffer from a SQL Server buffer.
		/// </summary>
		/// <remarks>
		/// Exact behaviour depends on the type of the buffer. If streaming is
		/// supported only data between start and end are loaded, otherwise the
		/// entire buffer is references and no data copy occures. The indices
		/// specify linear offsets in the typed array and no offsets in the 
		/// byte buffer.
		/// </remarks>
		internal: void LoadData(typename B::SqlBufferT data, array<typename B::IndexT>^ start, array<typename B::IndexT>^ end);

		/// <summary>
		/// Loads a single item from the SQL Server buffer into the byte buffer.
		/// </summary>
		/// <remarks>
		/// This is used only for single item loads where only one linear index
		/// is calculated.
		/// </remarks>
		internal: void LoadData(typename B::SqlBufferT data, typename B::IndexT start);


		/// <summary>
		/// Gets the total number of items in an array
		/// </summary>
		internal: static typename B::IndexT GetTotalLength(array<typename B::IndexT>^ length);


		/// <summary>
		/// Returns the linear offset of an array item specified by
		/// multiple indices.
		/// </summary>
		/// <remarks>
		/// Uses column major indexing a la Fortran and Matlab.
		/// </remarks>
		internal: typename B::IndexT GetLinearIndex(array<typename B::IndexT>^ indexes);

		/// <summary>
		/// Returns the linear offset of an array item specified by
		/// multiple indices.
		/// </summary>
		/// <remarks>
		/// Uses column major indexing a la Fortran and Matlab.
		/// </remarks>
		internal: typename B::IndexT GetLinearIndex(PARLIST_1(typename B::IndexT, i));

		/// <summary>
		/// Returns the linear offset of an array item specified by
		/// multiple indices.
		/// </summary>
		/// <remarks>
		/// Uses column major indexing a la Fortran and Matlab.
		/// </remarks>
		internal: typename B::IndexT GetLinearIndex(PARLIST_2(typename B::IndexT, i));

		/// <summary>
		/// Returns the linear offset of an array item specified by
		/// multiple indices.
		/// </summary>
		/// <remarks>
		/// Uses column major indexing a la Fortran and Matlab.
		/// </remarks>
		internal: typename B::IndexT GetLinearIndex(PARLIST_3(typename B::IndexT, i));

		/// <summary>
		/// Returns the linear offset of an array item specified by
		/// multiple indices.
		/// </summary>
		/// <remarks>
		/// Uses column major indexing a la Fortran and Matlab.
		/// </remarks>
		internal: typename B::IndexT GetLinearIndex(PARLIST_4(typename B::IndexT, i));

		/// <summary>
		/// Returns the linear offset of an array item specified by
		/// multiple indices.
		/// </summary>
		/// <remarks>
		/// Uses column major indexing a la Fortran and Matlab.
		/// </remarks>
		internal: typename B::IndexT GetLinearIndex(PARLIST_5(typename B::IndexT, i));

		/// <summary>
		/// Returns the linear offset of an array item specified by
		/// multiple indices.
		/// </summary>
		/// <remarks>
		/// Uses column major indexing a la Fortran and Matlab.
		/// </remarks>
		internal: typename B::IndexT GetLinearIndex(PARLIST_6(typename B::IndexT, i));


		/// <summary>
		/// Initializes the byte buffer from a binary stream.
		/// </summary>
		public: virtual void Read(System::IO::BinaryReader^ r);

		/// <summary>
		/// Serializes the byte buffer into a binary stream.
		/// </summary>
		public: virtual void Write(System::IO::BinaryWriter^ w);


		/// <summary>
		/// Returns the rank lengths as a managed array.
		/// </summary>
		public: array<typename B::IndexT>^ GetLengths();


		/// <summary>
		/// Converts the byte buffer into a SQL Server buffer.
		/// </summary>
		public: typename B::SqlBufferT ToSqlBuffer();

		/// <summary>
		/// Returns the represented array as a managed jagged array.
		/// </summary>
		public: System::Array^ ToJaggedArray();


		/// <summary>
		/// Internal function called recursively by ToJaggedArray
		/// </summary>
		private: System::Array^ ToJaggedArray_Subarray(interior_ptr<typename B::IndexT> lp, typename B::IndexT% dp, typename B::RankT r);

		/// <summary>
		/// Returns the represented array as a managed multidimensional array.
		/// </summary>
		/// <remarks>
		/// As the function only does a memory block copy, index order will be reversed.
		/// </remarks>
		public: System::Array^ ToMultiDArray();

		/// <summary>
		/// Returns the represented array as a one dimensional managed array.
		/// </summary>
		public: array<T>^ ToArray();

		/// <summary>
		/// Returns the string representation of the array, using the current culture format
		/// </summary>
		//This is here because a default parameter cannot be specified in C++/CLI for the culture
		public: virtual String^ ToString() override;

		/// <summary>
		/// Returns the string representation of the array, using a specified culture format
		/// </summary>
		public: virtual String^ ToString(CultureInfo^ culture);

		/// <summary>
		/// Internal function called recursively by ToString
		/// </summary>
		public: interior_ptr<T> ToString_Subarray(StringBuilder^ sb, interior_ptr<typename B::IndexT> lp, interior_ptr<T> dp, typename B::RankT r, CultureInfo^ culture);

		/// <summary>
		/// Internal function called recursively by FromArray
		/// </summary>
		public: void SqlArray<T, B>::FromArray_Subarray(typename B::IndexT% p, typename B::RankT rank, array<typename B::IndexT>^ length, System::Array^ data);


		/// <summary>
		/// Item accessor
		/// </summary>
		public: property T default[REPEAT_1(typename B::IndexT)] { T get(PARLIST_1(typename B::IndexT, i)); void set(PARLIST_1(typename B::IndexT, i), T value); };

		/// <summary>
		/// Item accessor
		/// </summary>
		public: property T default[REPEAT_2(typename B::IndexT)] { T get(PARLIST_2(typename B::IndexT, i)); void set(PARLIST_2(typename B::IndexT, i), T value); };

		/// <summary>
		/// Item accessor
		/// </summary>
		public: property T default[REPEAT_3(typename B::IndexT)] { T get(PARLIST_3(typename B::IndexT, i)); void set(PARLIST_3(typename B::IndexT, i), T value); };

		/// <summary>
		/// Item accessor
		/// </summary>
		public: property T default[REPEAT_4(typename B::IndexT)] { T get(PARLIST_4(typename B::IndexT, i)); void set(PARLIST_4(typename B::IndexT, i), T value); };

		/// <summary>
		/// Item accessor
		/// </summary>
		public: property T default[REPEAT_5(typename B::IndexT)] { T get(PARLIST_5(typename B::IndexT, i)); void set(PARLIST_5(typename B::IndexT, i), T value); };

		/// <summary>
		/// Item accessor
		/// </summary>
		public: property T default[REPEAT_6(typename B::IndexT)] { T get(PARLIST_6(typename B::IndexT, i)); void set(PARLIST_6(typename B::IndexT, i), T value); };

		/// <summary>
		/// Item accessor
		/// </summary>
		public: property T default[array<typename B::IndexT>^] { T get(array<typename B::IndexT>^ i); void set(array<typename B::IndexT>^ i, T value); };

		/// <summary>
		/// Returns true if the other array has the same rank and same lengths.
		/// </summary>
		internal: bool IsSameShape(SqlArray<T, B> other);

		/// <summary>
		/// Changes the rank lengths of the array by keeping the data
		/// intact.
		/// </summary>
		public: void Reshape(array<typename B::IndexT>^ length);

		/// <summary>
		/// Transposes a two index array by swapping indices.
		/// </summary>
		/// <remarks>
		/// </remarks>
		public: SqlArray<T, B> Transpose();

		/// <summary>
		/// Transposes the array by permuting indices.
		/// </summary>
		/// <remarks>
		/// This function performs a generalized transpose on the array by
		/// exhanging original indices with indices as they are listed in
		/// the parameter. The parameter should contain every index only once.
		/// </remarks>
		public: SqlArray<T, B> Permute(array<typename B::RankT>^ indices);

		/// <summary>
		/// Returns the indexed items as an array
		/// </summary>
		public: SqlArray<T, B> GetItems(array<array<typename B::IndexT>^>^ indices);

		/// <summary>
		/// Updates the indexed items
		/// </summary>
		public: void SetItems(array<array<typename B::IndexT>^>^ indices, array<typename T>^ values);

		/// <summary>
		/// Returns a subarray defined by index ranges.
		/// </summary>
		/// <remarks>
		/// If collapse is true, ranks with size of 1 are removed.
		/// </remarks>
		public: SqlArray<T, B> GetSubarray(array<typename B::IndexT>^ from, array<typename B::IndexT>^ size, bool collapse);

		/// <summary>
		/// Get subarrays defined by a size and list of offsets.
		/// </summary>
		/// <remarks>
		/// If collapse is true, ranks with size of 1 are removed.
		/// </remarks>
		public: SqlArray<T, B> GetSubarrays(array<array<typename B::IndexT>^>^ from, array<typename B::IndexT>^ size, bool collapse);

		/// <summary>
		/// Sets the subarray at the specified index.
		/// </summary>
		/// <remarks>
		/// The rank of both arrays must be the same.
		/// </remarks>
		public: void SetSubarray(array<typename B::IndexT>^ from, SqlArray<T, B> value);

		/// <summary>
		/// Sets the subarray at the specified index.
		/// </summary>
		/// <remarks>
		/// The rank of both arrays must be the same.
		/// </remarks>
		public: void SetSubarrays(array<array<typename B::IndexT>^>^ from, SqlArray<T, B> value);

#pragma endregion
#pragma region Algebra functions
						
		public: static SqlArray<T, B> TensorProduct(SqlArray<T, B> a, SqlArray<T, B> b);

		public: static SqlArray<T, B> InnerProduct(SqlArray<T, B> a, SqlArray<T, B> b);

#pragma endregion
#pragma region Static functions to interface with .Net

		/// <summary>
		/// Gets the rank lengths of a multi dimensional managed array
		/// </summary>
		internal: static array<typename B::IndexT>^ GetTotalLengthFromArray(System::Array^ data);

		/// <summary>
		/// Creates a SQL Server array from a managed array (either multi
	    /// dimensional or jagged.
		/// </summary>
		public: static SqlArray<T, B> FromArray(System::Array^ data);

		/// <summary>
		/// Creates a SQL Server array from a string representation, using the current culture format
		/// </summary>
		//This is here because a default parameter cannot be specified in C++/CLI for the culture
		public: static SqlArray<T, B> FromString(String^ data);

		/// <summary>
		/// Creates a SQL Server array from a string representation, using a specified culture format
		/// </summary>
		public: static SqlArray<T, B> FromString(String^ data, CultureInfo^ culture);

		/// <summary>
		/// Creates a SQL Server array with a given size of all zeros
		/// </summary>
		public: static SqlArray<T, B> Zeros(array<typename B::IndexT>^ length);

#pragma endregion
	};

} } }