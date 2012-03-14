<%@ Page Language="C#" MasterPageFile="~/AtmMasterRegular.master" Theme="AtmTheme" AutoEventWireup="true" CodeFile="Overview.aspx.cs" Inherits="Overview" %>

<asp:Content ContentPlaceHolderID="mainContent" runat="server">

    <h2>Overview</h2>
    <h3>Balance</h3>
    <p>$12.00</p>
        
    <h3>Last 3 Transactions</h3>
    <table border="1">
        <tr>
            <td>
                <p>1</p>
            </td>
            <td>
                <p>Deposit</p>
            </td>
            <td>
                <p>$10.00</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>2</p>
            </td>
            <td>
                <p>Withdraw</p>
            </td>
            <td>
                <p>$5.00</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>3</p>
            </td>
            <td>
                <p>Deposit</p>
            </td>
            <td>
                <p>$12.00</p>
            </td>
        </tr>
    </table>

</asp:Content>
