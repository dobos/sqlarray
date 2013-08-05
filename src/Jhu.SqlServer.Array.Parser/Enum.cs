using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Jhu.SqlServer.Array.Parser
{
	public enum TokenType
	{
        Null,
		LeftBracket,
		RightBracket,
		Separator,
		Whitespace,
//		PlusOperator,
//		MinusOperator,
		Number,
//		ImaginaryUnit,
        ComplexNumber,
	}
}
