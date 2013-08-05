using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlTypes;
using System.Data.SqlClient;
using Jhu.SqlServer.Array;

namespace Jhu.SqlServer.Array.Test
{
    class Program
    {
        static void Main(string[] args)
        {
            SqlArrayTest.Run();
            //AdoNetTest();

            Console.ReadLine();
        }

      
        /*static void AdoNetTest()
        {
            string cstr = "Data Source=localhost;Initial Catalog=SqlArrayTest;Integrated Security=true;";

            using (SqlConnection cn = new SqlConnection(cstr))
            {
                cn.Open();

                string sql = "SELECT TOP 100 ObjID, FloatArray.Vector_5(u, g, r, i, z) AS photo FROM PhotoObjAll";

                using (SqlCommand cmd = new SqlCommand(sql, cn))
                {
                    using (SqlDataReader dr = cmd.ExecuteReader())
                    {
                        while (dr.Read())
                        {
                            long objid = dr.GetInt64(0);
                            SqlFloatArray a = new SqlFloatArray(dr.GetSqlBinary(1));
                            double[] aa = a.ToArray();
                            double[] aaa = (double[])a.ToJaggedArray();

                            SqlBinary x = a.ToSqlBuffer();

                            Console.WriteLine("{0} {1}", objid, aa[2]);
                        }
                    }
                }
            }

        }*/
    }
}
