using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Jhu.SqlServer.Array.Parser
{
    public class ArrayNode : Node
    {
        private bool hasSubarray;
        private ItemListNode il;
        private SubArrayListNode sa;

        private string tokenSeparator;
        private string decimalPoint;

        public ArrayNode(string aTokenSeparator = ",", string aDecimalPoint = ".")
        {
            tokenSeparator = aTokenSeparator;
            decimalPoint = aDecimalPoint;
        }

        public bool HasSubarray
        {
            get { return hasSubarray; }
        }

        public ItemListNode ItemList
        {
            get { return il; }
        }

        public SubArrayListNode SubarrayList
        {
            get { return sa; }
        }

        public override bool Match(ref string buffer, ref int position)
        {
            TokenNode ws1 = new TokenNode(TokenType.Whitespace);
            if (MatchNode(ws1, ref buffer, ref position))
            {
                TokenNode lb = new TokenNode(TokenType.LeftBracket);
                if (MatchNode(lb, ref buffer, ref position))
                {
                    bool alt = false;

                    il = new ItemListNode(tokenSeparator, decimalPoint);
                    if (MatchNode(il, ref buffer, ref position))
                    {
                        hasSubarray = false;
                        alt = true;
                    }
                    else
                    {
                        sa = new SubArrayListNode(tokenSeparator, decimalPoint);
                        if (MatchNode(sa, ref buffer, ref position))
                        {
                            hasSubarray = true;
                            alt = true;
                        }
                    }

                    if (alt)
                    {
                        TokenNode ws2 = new TokenNode(TokenType.Whitespace);
                        if (MatchNode(ws2, ref buffer, ref position))
                        {
                            TokenNode rb = new TokenNode(TokenType.RightBracket);
                            if (MatchNode(rb, ref buffer, ref position))
                            {
                                return true;
                            }
                        }
                    }
                }
            }

            Cancel(ref position);
            return false;
        }
    }
}
