using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Jhu.SqlServer.Array.Parser
{
    public class TokenNode : Node
    {
        TokenType type;
        Token token;

        private string tokenSeparator;
        private string decimalPoint;

        public Token Token
        {
            get { return token; }
        }

        //The tokenSeparator only needs to be specified when aType==TokenType.Separator
        //The decimalPoint only needs to be specified when aType==TokenType.Number or aType==TokenType.ComplexNumber
        public TokenNode(TokenType aType, string aTokenSeparator = null, string aDecimalPoint = null)
        {
            type = aType;
            tokenSeparator = aTokenSeparator;
            decimalPoint = aDecimalPoint;
        }

        public override bool Match(ref string buffer, ref int position)
        {
            token = Token.Match(type, ref buffer, position, tokenSeparator, decimalPoint);
            if (token.Type != TokenType.Null)
            {
                this.position = token.Position;
                position += token.Length;
                return true;
            }
            else
            {
                return false;
            }
        }

        public override string ToString()
        {
            return String.Format("{0} : {1}", this.GetType().ToString(), token.Type);
        }
    }
}
