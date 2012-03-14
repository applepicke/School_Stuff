<%@ Page Language="C#" MasterPageFile="~/AtmMasterRegular.master" Theme="AtmTheme" AutoEventWireup="true" CodeFile="Report.aspx.cs" Inherits="Report" %>

<asp:Content ContentPlaceHolderID="mainContent" runat="server">
    
    <h2>Transaction History</h2>
    <asp:LinqDataSource ID="transactionSource" 
                        ContextTypeName="ATM2.ATMDataContext"
                        TableName="Transaction"
                        runat="server"/>
    <asp:GridView ID="transactionGrid"
                  DataSourceID="transactionSource"
                  AllowPaging="false"
                  AllowSorting="false"
                  runat="server" />
                  

</asp:Content>
