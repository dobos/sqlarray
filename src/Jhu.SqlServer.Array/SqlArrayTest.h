#pragma once

#include "macro.h"
#include "SqlComplex.h"
#include "Lapack.h"
#include "FFTW.h"
#include "SqlArrayTypeConverter.h"
#include "SqlArray.h"
#include "SqlArraySliceEnumerator.h"

using namespace System;
using namespace System::Text;
using namespace System::Data::SqlTypes;
using namespace Microsoft::SqlServer::Server;

namespace Jhu { namespace SqlServer { namespace Array
{

	public value class SqlArrayTest
	{
	public:
		static void Run();
	private:
		static bool TestHeader();
		static bool TestFromArray();
		static bool TestParse();
		static bool TestToString();
		static bool TestToJaggedArray();
		static bool TestToMultiDArray();
		static bool TestReshape();
		static bool TestTranspose();
		static bool TestPermute();
		static bool TestGetItems();
		static bool TestSetItems();
		static bool TestGetSubarray();
		static bool TestGetSubarrays();
		static bool TestSplit();
		static bool TestSetSubarray();
		static bool TestSetSubarrays();
		static bool TestConvert();
		static bool TestEnumerators();
		static bool TestSVD();
		static bool TestFFT();
		static bool TestInnerProduct();

		static array<Double>^ SampleVector();
		static array<Double,2>^ SampleMatrix();
		static array<Double,2>^ SampleNonRectMatrix();
		static array<Double,3>^ SampleTensor();
		static array<Double,3>^ SampleTensorBig();


		static void Assert(bool condition);
	};

}
} }