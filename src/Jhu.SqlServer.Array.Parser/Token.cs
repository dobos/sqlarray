using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Jhu.SqlServer.Array.Parser
{
    public struct Token
    {
        private static readonly Regex DoubleNumber = new Regex(@"\G[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?", RegexOptions.Compiled);
        private static readonly Regex ComplexNumber = new Regex(@"\G([-+]?[0-9]*\.?[0-9]+(?:[eE][-+]?[0-9]+)?)(?:\s*([+-])\s*([-+]?[0-9]*\.?[0-9]+(?:[eE][-+]?[0-9]+)?)i)?", RegexOptions.Compiled);

        public TokenType Type;
        public int Position;
        public int Length;

        public Token(TokenType type, int position, int length)
        {
            this.Type = type;
            this.Position = position;
            this.Length = length;
        }

        public static Token Null
        {
            get
            {
                Token t = new Token();
                t.Type = TokenType.Null;

                return t;
            }
        }

        public static Token Match(TokenType type, ref string buffer, int position)
        {
            // Try to match the given token
            switch (type)
            {
                case TokenType.LeftBracket:
                    return MatchLeftBracket(ref buffer, position);
                case TokenType.RightBracket:
                    return MatchRightBracket(ref buffer, position);
                case TokenType.Separator:
                    return MatchSeparator(ref buffer, position);
                case TokenType.Whitespace:
                    return MatchWhitespace(ref buffer, position);
/*                case TokenType.PlusOperator:
                    return MatchPlusOperator(ref buffer, position);
                case TokenType.MinusOperator:
                    return MatchMinusOperator(ref buffer, position);*/
                case TokenType.Number:
                    return MatchNumber(ref buffer, position);
/*                case TokenType.ImaginaryUnit:
                    return MatchImaginaryUnit(ref buffer, position);*/
                case TokenType.ComplexNumber:
                    return MatchComplexNumber(ref buffer, position);
                default:
                    throw new NotImplementedException();
            }
        }

        private static Token MatchLeftBracket(ref string buffer, int position)
        {
            if (buffer[position] == '[')
            {
                return new Token(TokenType.LeftBracket, position, 1);
            }
            else
            {
                return Token.Null;
            }
        }

        private static Token MatchRightBracket(ref string buffer, int position)
        {
            if (buffer[position] == ']')
            {
                return new Token(TokenType.RightBracket, position, 1);
            }
            else
            {
                return Token.Null;
            }
        }

        private static Token MatchSeparator(ref string buffer, int position)
        {
            if (buffer[position] == ',')
            {
                return new Token(TokenType.Separator, position, 1);
            }
            else
            {
                return Token.Null;
            }
        }

        private static Token MatchWhitespace(ref string buffer, int position)
        {
            int p = position;
            while (p < buffer.Length && buffer[p] == ' ')
            {
                p++;
            }

            if (p > position)
            {
                return new Token(TokenType.Whitespace, position, p - position);
            }
            else
            {
                return new Token(TokenType.Whitespace, position, 0);
            }
        }

        /*
        private static Token MatchPlusOperator(ref string buffer, int position)
        {
            if (buffer[position] == '+')
            {
                return new Token(TokenType.PlusOperator, position, 1);
            }
            else
            {
                return Token.Null;
            }
        }

        private static Token MatchMinusOperator(ref string buffer, int position)
        {
            if (buffer[position] == '-')
            {
                return new Token(TokenType.MinusOperator, position, 1);
            }
            else
            {
                return Token.Null;
            }
        }*/

        private static Token MatchNumber(ref string buffer, int position)
        {
            Match m = DoubleNumber.Match(buffer, position);
            if (m.Success)
            {
                return new Token(TokenType.Number, position, m.Length);
            }
            else
            {
                return Token.Null;
            }
        }

        /*
        private static Token MatchImaginaryUnit(ref string buffer, int position)
        {
            if (buffer[position] == 'i' || buffer[position] == 'I')
            {
                return new Token(TokenType.ImaginaryUnit, position, 1);
            }
            else
            {
                return Token.Null;
            }
        }*/

        private static Token MatchComplexNumber(ref string buffer, int position)
        {
            Match m = ComplexNumber.Match(buffer, position);
            if (m.Success)
            {
                return new Token(TokenType.ComplexNumber, position, m.Length);
            }
            else
            {
                return Token.Null;
            }
        }
    }
}
