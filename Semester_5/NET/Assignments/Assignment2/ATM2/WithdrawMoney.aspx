﻿<%@ Page Language="C#" MasterPageFile="~/AtmMasterRegular.master" Theme="AtmTheme" AutoEventWireup="true" CodeFile="WithdrawMoney.aspx.cs" Inherits="WithdrawMoney" %>

<asp:Content ContentPlaceHolderID="mainContent" runat="server">
    <h2>Withdraw</h2>
    <table>
        <tr>
            <td>
                <p>Amount: </p>
            </td>
            <td>
                $<asp:TextBox ID="Withdraw" runat="server" />
                <asp:Label ID="errors" CssClass="errors" runat="server" />
            </td>
        </tr>    
    </table>
    <asp:Button OnClick="WithdrawAmount" Text="Withdraw" runat="server" />
</asp:Content>
