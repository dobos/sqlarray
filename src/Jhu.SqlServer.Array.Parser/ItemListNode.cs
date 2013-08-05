using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Jhu.SqlServer.Array.Parser
{
    public class ItemListNode : Node
    {
        private ItemNode it;
        private ItemListNode il;
        private bool hasNextItemList = false;

        public ItemNode ItemNode
        {
            get { return it; }
        }

        public override bool Match(ref string buffer, ref int position)
        {
            TokenNode ws1 = new TokenNode(TokenType.Whitespace);
            if (MatchNode(ws1, ref buffer, ref position))
            {
                it = new ItemNode();
                if (MatchNode(it, ref buffer, ref position))
                {
                    // Optionally match
                    TokenNode ws2 = new TokenNode(TokenType.Whitespace);
                    if (MatchNode(ws2, ref buffer, ref position))
                    {
                        TokenNode sp = new TokenNode(TokenType.Separator);
                        if (MatchNode(sp, ref buffer, ref position))
                        {
                            il = new ItemListNode();
                            if (MatchNode(il, ref buffer, ref position))
                            {
                                hasNextItemList = true;
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

        public IEnumerable<ItemNode> Rollup()
        {
            ItemListNode n = this;
            do
            {
                yield return n.ItemNode;
                if (!n.hasNextItemList) break;
                n = n.il;
            }
            while (true);
        }
    }
}
