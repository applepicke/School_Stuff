<%@ Page Language="C#" MasterPageFile="~/AtmMasterRegular.master" Theme="AtmTheme" AutoEventWireup="true" CodeFile="Overview.aspx.cs" Inherits="Overview" %>

<asp:Content ContentPlaceHolderID="mainContent" runat="server">
    <h2>Overview</h2>
    <h3>Balance</h3>
    $<asp:Label ID="balance" runat="server" />
        
    <h3>Last 3 Transactions</h3>
    <asp:DataGrid ID="overviewGrid" runat="server" />
    <br />
    <br />
</asp:Content>
