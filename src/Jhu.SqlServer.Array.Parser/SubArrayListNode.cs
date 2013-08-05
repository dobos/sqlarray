using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Jhu.SqlServer.Array.Parser
{
    public class SubArrayListNode : Node
    {
        private ArrayNode ar;
        private SubArrayListNode sa;
        private bool hasNextSubarray = false;

        public override bool Match(ref string buffer, ref int position)
        {
            TokenNode ws1 = new TokenNode(TokenType.Whitespace);
            if (MatchNode(ws1, ref buffer, ref position))
            {
                ar = new ArrayNode();
                if (MatchNode(ar, ref buffer, ref position))
                {
                    // Optionally match
                    TokenNode ws2 = new TokenNode(TokenType.Whitespace);
                    if (MatchNode(ws2, ref buffer, ref position))
                    {
                        TokenNode sp = new TokenNode(TokenType.Separator);
                        if (MatchNode(sp, ref buffer, ref position))
                        {
                            sa = new SubArrayListNode();
                            if (MatchNode(sa, ref buffer, ref position))
                            {
                                hasNextSubarray = true;
                            }
                            else
                            {
                                Pop(ref position);
                            }
                        }
                        else
                        {
                            Pop(ref position);
                        }
                    }

                    return true;
                }
            }

            Cancel(ref position);
            return false;
        }

        public IEnumerable<ArrayNode> Rollup()
        {
            SubArrayListNode n = this;
            do
            {
                yield return n.ar;
                if (!n.hasNextSubarray) break;
                n = n.sa;
            }
            while (true);
        }
    }
}
