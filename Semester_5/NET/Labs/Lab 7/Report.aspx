<%@ Page Title="" Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Report.aspx.cs" Inherits="Report" %>

<asp:Content ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">

    <asp:DropDownList ID="dropDown" runat="server" OnSelectedIndexChanged="UpdateData" AutoPostBack="true">
        <asp:ListItem Text="Show 3" />
        <asp:ListItem Text="Show 5" />
        <asp:ListItem Text="Show 10" />
    </asp:DropDownList>

    <asp:GridView ID="gridView" AutoGenerateColumns="true" runat="server" />

</asp:Content>

