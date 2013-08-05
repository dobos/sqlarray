#include "stdafx.h"
#include "macro.h"
#include "MaxArray.h"

namespace Jhu { namespace SqlServer { namespace Array
{
	inline MaxArray::SqlBufferT MaxArray::ToSqlBuffer(array<MaxArray::BufferT>^ data)
	{
		return gcnew SqlBytes(data);
	}

	inline array<MaxArray::BufferT>^ MaxArray::GetBuffer(MaxArray::SqlBufferT sqlBuffer, ArrayLoadMethod method)
	{

		if (sqlBuffer->Storage == StorageState::Buffer)
		{
			return sqlBuffer->Buffer;
		}
		else
		{
			array<MaxArray::BufferT>^ buffer = gcnew array<MaxArray::BufferT>((int)sqlBuffer->Stream->Length);

			switch (method)
			{
			case ArrayLoadMethod::HeaderOnly:
				sqlBuffer->Stream->Read(buffer, 0, Math::Min(8000, buffer->Length));
				break;
			case ArrayLoadMethod::AllData:
				sqlBuffer->Stream->Read(buffer, 0, buffer->Length);
				break;
			}

			return buffer;
		}
	}

	inline MaxArray::SqlBufferT MaxArray::GetSqlBuffer(SqlDataReader^ dr, int column)
	{
		return dr->GetSqlBytes(column);
	}

	inline void MaxArray::LoadBuffer(SqlBufferT sqlBuffer, array<BufferT>^ buffer, IndexT start, IndexT end)
	{
		sqlBuffer->Stream->Seek(start, System::IO::SeekOrigin::Begin);
		sqlBuffer->Stream->Read(buffer, start, end - start);
	}

	inline MaxArray::IndexT MaxArray::GetHeaderOffset()
	{
		return 0;
	}

	inline MaxArray::IndexT MaxArray::GetLengthsOffset()
	{
		return sizeof(HeaderT);
	}

	inline MaxArray::IndexT MaxArray::GetDataOffset(MaxArray::RankT rank)
	{
		return sizeof(HeaderT) + rank * sizeof(IndexT);
	}

	inline MaxArray::IndexT MaxArray::GetBufferSize(RankT rank, IndexT length, size_t itemSize)
	{
		return (MaxArray::IndexT)(sizeof(HeaderT) + rank * sizeof(IndexT) + length * itemSize);
	}

}
} }