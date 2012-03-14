<%@ Page Language="C#" MasterPageFile="~/AtmMasterRegular.master" Theme="AtmTheme" AutoEventWireup="true" CodeFile="DepositMoney.aspx.cs" Inherits="DepositMoney" %>

<asp:Content ContentPlaceHolderID="mainContent" runat="server">

    <h2>Deposit</h2>
    <table>
        <tr>
            <td>
                <p>Amount: $</p>
            </td>
            <td>
                <asp:TextBox ID="Deposit" runat="server" />
            </td>
        </tr>    
    </table>
    <asp:Button OnClick="DepositAmount" Text="Deposit" runat="server" />
    

</asp:Content>

