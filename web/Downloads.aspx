<%@ Page Title="" Language="C#" MasterPageFile="~/normal.master" AutoEventWireup="true"
    CodeFile="Downloads.aspx.cs" Inherits="Services" %>

<asp:Content ID="Content1" ContentPlaceHolderID="Middle" runat="Server">
    <form id="default" method="post" runat="server">
    <table align="center" width="98%">
        <tr>
            <td>
                <h2>Downloads</h2>

                <h3>Libraries</h3>
                <p>The SQL Array library is available for SQL Server 2008 x64 edition only. The 
                    download file below contains install script for the server and also the DLLs 
                    required to use from .net.</p>
                <p>Download <a href="Download/SqlArray-Debug-x64-1.0.zip">SqlArray-Debug-x64-1.0.zip</a><br />
                    Download <a href="Download/SqlArray-Release-x64-1.0.zip">SqlArray-Release-x64-1.0.zip</a></p>

                <h3>Documentation</h3>
                <p>Download <a href="Download/SqlArray.pdf">SqlArray.pdf</a></p>
            </td>
        </tr>
    </table>
    </form>
</asp:Content>
