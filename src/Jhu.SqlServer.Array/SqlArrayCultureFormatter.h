#pragma once

#include "SqlComplex.h"

using namespace System;
using namespace System::Globalization;
using namespace System::Data::SqlTypes;

namespace Jhu { namespace SqlServer { namespace Array

{

	public ref class SqlArrayCultureFormatter abstract sealed
	{
#pragma region Static member functions

		public:

			template <typename T>
			static String^ ToString(T obj, IFormatProvider^ formatProvider);

			template <typename T>
			static T Parse(String^ value, IFormatProvider^ formatProvider);

#pragma endregion
	};

	//Forward declaration of specializations so that they are not implicitly instantiated before the definition in the cpp
	//Put outside the class body so that they are not made inline (resulting in no definition for inline function warnings)
	template <>
	String^ SqlArrayCultureFormatter::ToString(SqlComplex<Single> obj, IFormatProvider^ formatProvider);
	template <>
	String^ SqlArrayCultureFormatter::ToString(SqlComplex<Double> obj, IFormatProvider^ formatProvider);
	template <>
	SqlComplex<Single> SqlArrayCultureFormatter::Parse(String^ value, IFormatProvider^ formatProvider);
	template <>
	SqlComplex<Double> SqlArrayCultureFormatter::Parse(String^ value, IFormatProvider^ formatProvider);


} } }

