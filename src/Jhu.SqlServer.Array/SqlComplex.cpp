#include "stdafx.h"
#include "macro.h"
#include "SqlComplex.h"

namespace Jhu { namespace SqlServer { namespace Array
{

	template <class T>
	String^ SqlComplex<T>::ToString()
	{
		return String::Format("{0:0.0000} {2} {1:0.0000}i",
			Re,
			Math::Abs(Im),
			Math::Sign(Im) < 0 ? "-" : "+");
	}

	template <class T>
	inline SqlComplex<T> SqlComplex<T>::operator +(SqlComplex<T> a, SqlComplex<T> b)
	{
		return SqlComplex<T>(a.Re + b.Re, a.Im + b.Im);
	}

	template <class T>
	inline SqlComplex<T> SqlComplex<T>::operator -(SqlComplex<T> a, SqlComplex<T> b)
	{
		return SqlComplex<T>(a.Re - b.Re, a.Im - b.Im);
	}

	template <class T>
	inline SqlComplex<T> SqlComplex<T>::operator *(SqlComplex<T> a, SqlComplex<T> b)
	{
		return SqlComplex<T>(a.Re * b.Re - a.Im * b.Im, a.Im * b.Re + a.Re * b.Im);
	}

	template <class T>
	inline SqlComplex<T> SqlComplex<T>::operator /(SqlComplex<T> a, SqlComplex<T> b)
	{
		return SqlComplex<T>(
			(a.Re * b.Re + a.Im * b.Im) / (b.Re * b.Re + b.Im * b.Im),
			(a.Im * b.Re - a.Re * b.Im) / (b.Re * b.Re + b.Im * b.Im));
	}

	template <class T>
	SqlComplex<T> SqlComplex<T>::Parse(SqlString value)
	{
		Regex^ cn =	gcnew Regex(
				"\\G([-+]?[0-9]*\\.?[0-9]+(?:[eE][-+]?[0-9]+)?)(?:\\s*([+-])\\s*([-+]?[0-9]*\\.?[0-9]+(?:[eE][-+]?[0-9]+)?)i)?",
				RegexOptions::Compiled);

		Match^ m = cn->Match(value.Value);

		if (m->Success)
		{
			T re = T::Parse(m->Groups[1]->Value);
			
			if (m->Groups[2]->Success)
			{
				T sign = m->Groups[2]->Value == "+" ? (T)1 : (T)-1;
				T im = T::Parse(m->Groups[3]->Value);
				return SqlComplex<T>(re, sign * im);
			}
			else
			{
				return SqlComplex<T>(re, 0);
			}

			
		}
		else
		{
			throw gcnew System::FormatException();
		}
	}


	template SqlComplex<Single>;
	template SqlComplex<Double>;

}
} }