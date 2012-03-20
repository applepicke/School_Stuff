<%@ Page Language="C#" MasterPageFile="~/AtmMasterRegular.master" Theme="AtmTheme" AutoEventWireup="true" CodeFile="Report.aspx.cs" Inherits="Report" %>

<asp:Content ContentPlaceHolderID="mainContent" runat="server">    
    <h2>Transaction History</h2>

    <asp:GridView ID="transactionGrid"
                  AllowPaging="false"
                  AllowSorting="false"
                  runat="server" />
    <br />
    <br />     
</asp:Content>
