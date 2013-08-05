using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Jhu.SqlServer.Array.Parser
{
    public class ItemNode : Node
    {
        private TokenNode nm;

        public TokenNode Number
        {
            get { return nm; }
        }

        public override bool Match(ref string buffer, ref int position)
        {
            TokenNode ws1 = new TokenNode(TokenType.Whitespace);
            if (MatchNode(ws1, ref buffer, ref position))
            {
                nm = new TokenNode(TokenType.ComplexNumber);
                if (MatchNode(nm, ref buffer, ref position))
                {
                    return true;
                }
                else
                {
                    nm = new TokenNode(TokenType.Number);
                    if (MatchNode(nm, ref buffer, ref position))
                    {
                        return true;
                    }
                }
            }

            Cancel(ref position);
            return false;
        }
    }
}
