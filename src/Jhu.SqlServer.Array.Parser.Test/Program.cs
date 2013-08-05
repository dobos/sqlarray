using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Jhu.SqlServer.Array.Parser;

namespace Jhu.SqlServer.Array.Parser.Test
{
    class Program
    {
        static void Main(string[] args)
        {
            ArrayParser p = new ArrayParser();

            string[] buffer = {
                                  "[ 1,2,-3.13e-9 ]",
                                  "  [ [ 1,2 ] ,[3  , 4] ]     ",
                                  "[[1,2,3],[4,5,6]]",
                                  "[[[1,2],[1,2]],[[1,2],[1,2]],[[5,6],[5,6]],[[7,8],[7,8]]]",
                                  "[1+2i,2+1i,3+0i]",
                              };

            for (int i = 0; i < buffer.Length; i++)
            {
                Token[] a;
                int[] length;
                p.Parse(ref buffer[i], out length, out a);
            }

            Console.ReadLine();
        }
    }
}
