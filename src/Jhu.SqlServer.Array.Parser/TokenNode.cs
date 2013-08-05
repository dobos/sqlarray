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

        public Token Token
        {
            get { return token; }
        }

        public TokenNode(TokenType type)
        {
            this.type = type;
        }

        public override bool Match(ref string buffer, ref int position)
        {
            token = Token.Match(type, ref buffer, position);
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
