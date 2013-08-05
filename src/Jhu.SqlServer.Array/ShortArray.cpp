#include "stdafx.h"
#include "macro.h"
#include "ShortArray.h"

namespace Jhu { namespace SqlServer { namespace Array
{
	inline ShortArray::SqlBufferT ShortArray::ToSqlBuffer(array<ShortArray::BufferT>^ data)
	{
		return SqlBinary(data);
	}

	inline array<ShortArray::BufferT>^ ShortArray::GetBuffer(ShortArray::SqlBufferT sqlBuffer, ArrayLoadMethod method)
	{
		// Return everything that's already in memory, regardless of parameters
		return sqlBuffer.Value;
	}

	inline ShortArray::SqlBufferT ShortArray::GetSqlBuffer(SqlDataReader^ dr, int column)
	{
		return dr->GetSqlBinary(column);
	}

	inline void ShortArray::LoadBuffer(SqlBufferT sqlBuffer, array<BufferT>^ buffer, IndexT start, IndexT end)
	{
		// do nothing, short array doesn't support partial loading
	}

	inline ShortArray::IndexT ShortArray::GetHeaderOffset()
	{
		return 0;
	}

	inline ShortArray::IndexT ShortArray::GetLengthsOffset()
	{
		return sizeof(HeaderT);
	}

	inline ShortArray::IndexT ShortArray::GetDataOffset(ShortArray::RankT rank)
	{
		//return sizeof(HeaderT) + rank * sizeof(IndexT);
		return sizeof(HeaderT) + 16;
	}

	inline ShortArray::IndexT ShortArray::GetBufferSize(RankT rank, IndexT length, size_t itemSize)
	{
		//return (ShortArray::IndexT)(sizeof(HeaderT) + rank * sizeof(IndexT) + length * itemSize);
		return (ShortArray::IndexT)(sizeof(HeaderT) + 16 + length * itemSize);
	}

}
} }