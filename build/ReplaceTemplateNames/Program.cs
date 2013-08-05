using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;
using System.Reflection;

namespace ReplaceTemplateNames
{
    class Program
    {
        static string[] BinaryType = { "Jhu::SqlServer::Array::ShortArray", "Jhu::SqlServer::Array::MaxArray" };
        static string[] BinaryName = { "", "Max" };

        static string[] CppCliName = { "unsigned char", "short", "int", "__int64", "float", "double", "Jhu::SqlServer::Array::SqlFloatComplex", "Jhu::SqlServer::Array::SqlRealComplex" };
        static string[] DotNetName = { "Byte", "Int16", "Int32", "Int64", "Single", "Double", "DoubleComplex", "SingleComplex" };
        static string[] SqlName = { "TinyInt", "SmallInt", "Int", "BigInt", "Real", "Float", "FloatComplex", "RealComplex" };

        static void Main(string[] args)
        {
            Console.WriteLine("Replacing template names...");

            StringBuilder b = new StringBuilder(File.ReadAllText(args[0]));
            Assembly a = Assembly.LoadFrom(args[1]);

            //b.Replace("SqlComplex<float>", "SqlSingleComplex");
            //b.Replace("SqlComplex<double>", "SqlDoubleComplex");

            b.Replace("SqlComplex<float>", "SqlRealComplex");
            b.Replace("SqlComplex<double>", "SqlFloatComplex");

            Regex regex2 = new Regex(@"SqlArray([a-z0-9]*)<([a-z:\s_0-9]+),([a-z:\s_0-9]+)>", RegexOptions.IgnoreCase);
            Regex regex4 = new Regex(@"SqlArray([a-z0-9]*)<([a-z:\s_0-9]+),([a-z:\s_0-9]+),([a-z:\s_0-9]+),([a-z:\s_0-9]+)>", RegexOptions.IgnoreCase);

            foreach (Type t in a.GetTypes())
            {

                if (t.IsPublic)
                {
                    string tname = t.Name.Replace(@"\,", @",");
                    tname = tname.Replace("Jhu::SqlServer::Array::SqlComplex<double>", "Jhu::SqlServer::Array::SqlFloatComplex");
                    tname = tname.Replace("Jhu::SqlServer::Array::SqlComplex<float>", "Jhu::SqlServer::Array::SqlRealComplex");

                    Match m = regex2.Match(tname);
                    if (m.Success)
                    {
                        string functionname = m.Groups[1].Value;
                        string typename = m.Groups[2].Value;
                        string storagename = m.Groups[3].Value;

                        typename = SqlName[Array.IndexOf(CppCliName, typename)];
                        storagename = BinaryName[Array.IndexOf(BinaryType, storagename)];

                        if (functionname != "")
                        {
                            functionname = "_" + functionname;
                        }

                        string newname = String.Format(
                            "Sql{0}Array{1}{2}",
                            typename,
                            storagename,
                            functionname);

                        b.Replace(tname, newname);
                    }

                    m = regex4.Match(tname);
                    if (m.Success)
                    {
                        string functionname = m.Groups[1].Value;
                        string typename1 = m.Groups[2].Value;
                        string storagename1 = m.Groups[3].Value;
                        string typename2 = m.Groups[4].Value;
                        string storagename2 = m.Groups[5].Value;

                        typename1 = SqlName[Array.IndexOf(CppCliName, typename1)];
                        storagename1 = BinaryName[Array.IndexOf(BinaryType, storagename1)];
                        typename2 = SqlName[Array.IndexOf(CppCliName, typename2)];
                        storagename2 = BinaryName[Array.IndexOf(BinaryType, storagename2)];

                        if (functionname != "")
                        {
                            functionname = "_" + functionname;
                        }

                        string newname = String.Format(
                            "Sql{0}Array{1}To{2}Array{3}{4}",
                            typename1,
                            storagename1,
                            typename2,
                            storagename2,
                            functionname);

                        b.Replace(tname, newname);
                    }
                }

            }

            /*for (int i = 0; i < CppCliName.Length; i++)
{
    for (int j = 0; j < BinaryType.Length; j++)
    {
        b.Replace(
            String.Format("SqlArray<{0},{1}>", CppCliName[i], BinaryType[j]),
            String.Format("Sql{0}{1}Array", DotNetName[i], BinaryName[j]));

        b.Replace(
            String.Format("SqlArrayFunctions<{0},{1}>", CppCliName[i], BinaryType[j]),
            String.Format("Sql{0}{1}ArrayFunctions", DotNetName[i], BinaryName[j]));

        b.Replace(
            String.Format("SqlArrayConcat<{0},{1}>", CppCliName[i], BinaryType[j]),
            String.Format("Sql{0}{1}ArrayConcat", DotNetName[i], BinaryName[j]));

        b.Replace(
            String.Format("SqlArrayConcatSubarrays<{0},{1}>", CppCliName[i], BinaryType[j]),
            String.Format("Sql{0}{1}ArrayConcatSubarrays", DotNetName[i], BinaryName[j]));

        b.Replace(
            String.Format("SqlArrayLinalg<{0},{1}>", CppCliName[i], BinaryType[j]),
            String.Format("Sql{0}{1}LinalgFunctions", DotNetName[i], BinaryName[j]));

        b.Replace(
            String.Format("SqlArrayFFT<{0},{1}>", CppCliName[i], BinaryType[j]),
            String.Format("Sql{0}{1}FFTFunctions", DotNetName[i], BinaryName[j]));

        for (int k = 0; k < CppCliName.Length; k++)
        {
            for (int l = 0; l < BinaryType.Length; l++)
            {
                b.Replace(
                    String.Format("SqlArrayTypeConverter<{0},{1},{2},{3}>", CppCliName[i], BinaryType[j], CppCliName[k], BinaryType[l]),
                    String.Format("Sql{0}{1}ArrayTo{2}{3}ArrayConverter", DotNetName[i], BinaryName[j], DotNetName[k], BinaryName[l]));
            }
        }
    }
}*/

            //b.Replace("SqlArrayAvg<double>", "SqlDoubleArrayAvg");
            //b.Replace("SqlArrayAvg<float>", "SqlSingleArrayAvg");

            //b.Replace("SqlArrayFunctions<double>", "SqlDoubleArrayFunctions");

            File.WriteAllText(args[0], b.ToString());
        }
    }
}
