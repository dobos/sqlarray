using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Jhu.SqlServer.Array.Parser
{
    public class ArrayParser
    {
        private string tokenSeparator;
        private string decimalPoint;

        /// <summary>
        /// Creates the ArrayParser object, with an optionally specified list separator string
        /// </summary>
        /// <param name="aTokenSeparator">The string that separates fields in the list, default: ","</param>
        public ArrayParser(string aTokenSeparator=",", string aDecimalPoint=".")
        {
            tokenSeparator = aTokenSeparator;
            decimalPoint = aDecimalPoint;
        }

        /// <summary>
        /// Returns the rank length of the parser array and a consecutive
        /// list of tokens
        /// </summary>
        /// <param name="buffer">The string representation of the array.</param>
        /// <param name="length">The length of the ranks.</param>
        /// <param name="data">The consecutive list of tokens representing the array items.</param>
        public void Parse(ref string buffer, out int[] length, out Token[] data)
        {
            // Math an array node at the beginning
            int position = 0;
            ArrayNode root = new ArrayNode(tokenSeparator, decimalPoint);
            bool res = root.Match(ref buffer, ref position);

            // Trailing white spaces
            TokenNode ws = new TokenNode(TokenType.Whitespace);
            res &= ws.Match(ref buffer, ref position);

            // Check if there's anything after the trailing white spaces
            res &= position == buffer.Length;

            if (!res)
            {
                throw new Exception("Invalid format");  // ****
            }

            // Get the list of item tokens from the parsing tree
            GetArray(root, out length, out data);
        }

        /// <summary>
        /// Gets the array rank sizes and the list of consecutive number tokens
        /// </summary>
        /// <param name="a">A subarray node of the parsing tree</param>
        /// <param name="length">Length of the ranks</param>
        /// <param name="data">Consecutive list of the array item tokens</param>
        private void GetArray(ArrayNode a, out int[] length, out Token[] data)
        {
            int rank;

            if (!a.HasSubarray)
            {
                // Simple 1D array
                rank = 1;
                length = new int[] { a.ItemList.Rollup().Count() };
                data = GetTokens(a, rank, 0, length).ToArray();
            }
            else
            {
                // Multi-D array

                // Determine rank and length
                rank = 1;
                List<int> len = new List<int>();
                ArrayNode b = a;
                do
                {
                    rank++;
                    len.Add(b.SubarrayList.Rollup().Count());
                    b = b.SubarrayList.Rollup().First();
                }
                while (b.HasSubarray);
                len.Add(b.ItemList.Rollup().Count());

                length = len.ToArray();

                data = GetTokens(a, rank, 0, length).ToArray();
            }

            // Rank lengths are collected in reverse order
            length = length.Reverse().ToArray();
        }

        private IEnumerable<Token> GetTokens(ArrayNode a, int rank, int r, int[] length)
        {
            if (!a.HasSubarray && r == rank - 1)
            {
                int l = 0;
                foreach (Token t in a.ItemList.Rollup().Select(i => i.Number.Token))
                {
                    l++;
                    yield return t;
                }

                if (l != length[r])
                {
                    throw new Exception("Length mismatch");  // *** length mismatch
                }
            }
            else if (a.HasSubarray && rank > 1)
            {
                foreach (ArrayNode sa in a.SubarrayList.Rollup())
                {
                    foreach (Token t in GetTokens(sa, rank, r + 1, length))
                    {
                        yield return t;
                    }
                }
            }
            else
            {
                throw new Exception();  // **** rank mismatch
            }
        }


    }
}
