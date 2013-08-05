using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Jhu.SqlServer.Array.Parser
{
    public abstract class Node
    {
        protected int position;
        protected Stack<Node> stack;

        public Node()
        {
            stack = new Stack<Node>();
        }

        public abstract bool Match(ref string buffer, ref int position);

        protected bool MatchNode(Node node, ref string buffer, ref int position)
        {
            if (node.Match(ref buffer, ref position))
            {
                if (stack.Count == 0)
                {
                    this.position = node.position;
                }
                stack.Push(node);
                return true;
            }
            else
            {
                return false;
            }
        }

        protected void Pop(ref int position)
        {
            position = stack.Pop().position;
        }

        protected void Cancel(ref int position)
        {
            while (stack.Count > 0)
            {
                position = stack.Pop().position;
            }
        }

        public void Write(TextWriter output, int level)
        {
            for (int i = 0; i < level; i++)
                output.Write("---");
            output.WriteLine(this.ToString());

            foreach (Node n in stack.Reverse())
            {
                n.Write(output, level + 1);
            }
        }
    }
}
