#pragma once

#include "macro.h"
#include "SqlArrayHeader.h"
#include "enum.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;
using namespace Jhu::SqlServer::Array::Parser;

namespace Jhu { namespace SqlServer { namespace Array
{
	/// <summary>
	/// Implements buffer handling functions for arrays stored in varbinary(n &lt; 8000)
	/// </summary>
	public value class ShortArray
	{
	internal:
		typedef SqlBinary				SqlBufferT;
		typedef unsigned char			BufferT;
		typedef unsigned char			RankT;
		typedef unsigned char			DataTypeT;
		typedef Int16					IndexT;
		typedef SqlArrayHeader<IndexT>	HeaderT;

	internal:
		static const unsigned char HeaderType = 1;
		static const int ArrayAggregateSize = 8000;

	internal:

		/// <summary>
		/// Serializes data into a SQL Server buffer
		/// </summary>
		static SqlBufferT ToSqlBuffer(array<BufferT>^ data);

		/// <summary>
		/// Deserializes data from a SQL Server buffer
		/// </summary>
		static array<BufferT>^ GetBuffer(SqlBufferT sqlBuffer, ArrayLoadMethod method);

		/// <summary>
		/// Gets the SQL Server buffer from a DataReader
		/// </summary>
		static SqlBufferT GetSqlBuffer(SqlDataReader^ dr, int column);

		/// <summary>
		/// Loads data from the SQL Server buffer into a byte buffer
		/// </summary>
		static void LoadBuffer(SqlBufferT sqlBuffer, array<BufferT>^ buffer, IndexT start, IndexT end);
		
		// ---

		/// <summary>
		/// Returns the offset of the header in bytes inside the byte buffer
		/// </summary>
		static IndexT GetHeaderOffset();

		/// <summary>
		/// Returns the offset of the list of lenghts in bytes inside the byte buffer
		/// </summary>
		static IndexT GetLengthsOffset();

		/// <summary>
		/// Returns the offset of the data in bytes inside the byte buffer
		/// </summary>
		static IndexT GetDataOffset(RankT rank);

		/// <summary>
		/// Returns the required size of the byte buffer based on the lengths of the array.
		/// </summary>
		static IndexT GetBufferSize(RankT rank, IndexT length, size_t itemSize);
	};
}
} }