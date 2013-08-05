
using System;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;

/// <summary>
///		Summary description for Footer.
/// </summary>
public partial class Footer : System.Web.UI.UserControl
{

    protected void Page_Load(object sender, System.EventArgs e)
    {
        /*
        System.Reflection.Assembly asm = System.Reflection.Assembly.GetExecutingAssembly();
        Release.Text = asm.GetName().Version.ToString();        
         * */

        Release.Text = "1.0";
    }


}
